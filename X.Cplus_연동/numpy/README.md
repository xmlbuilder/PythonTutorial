# numpy와 연동 

## 사용 에제

```python
import numpy as np
import mything

print("version:", mything.MyThing.version())  # "MyThing/2.0"

t = mything.MyThing(10)

# const 멤버 함수
print("peek:", t.peek())                       # 10
print("sum_with:", t.sum_with([1.5, 2.5]))     # 1.5+2.5+10 = 14.0

# 예외 변환 확인
try:
    t.increment(0)  # delta==0 -> C++ MyError 던짐 -> Python mything.MyError 로 변환
except mything.MyError as e:
    print("caught:", e)

# 정상 증가
print("increment:", t.increment(5))            # 15
print("value now:", t.value)                   # 15

# NumPy: 멤버 값(15)을 모든 원소에 더한 새 배열
arr = np.array([[1.0, 2.0],[3.0, 4.0]])
out = t.add_to_array(arr)
print("arr:\n", arr)
print("out:\n", out)     # 각 원소에 +15

# NumPy: 정적 메소드로 임의 스칼라 더하기
print(mything.MyThing.add_scalar(arr, 100.0))
```

## 내부적인 함수 설명

### 1. MyThing::sum_with(const std::vector<double>& data) const  
  → 독립 함수. 파이썬 list/tuple → std::vector<double>로 변환된 걸 받아 합계를 내고 value_를 더해 스칼라(double) 를 반환합니다. NumPy와 직접 연결 없음.  

### 2. add_scalar_to_array(py::array_t<double> arr, double val) (자유 함수)
  → 핵심 유틸. C-연속 double 배열을 받아 모든 원소에 val을 더한 새 배열을 만들어 돌려줍니다.  
  → 이걸 두 군데에서 재사용합니다:  

- 멤버 바인딩 MyThing.add_to_array(arr) (람다)
- 정적 바인딩 MyThing.add_scalar(arr, v) (람다)

### 3. MyThing.add_to_array(arr) (멤버 메소드 바인딩)
  → 내부에서 self.peek()로 현재 value_를 읽어서  
  → add_scalar_to_array(arr, self.peek()) 호출 후 결과 배열 반환  

- MyThing.add_scalar(arr, v) (정적 메소드 바인딩)  
  → add_scalar_to_array(arr, v) 를 그대로 호출 (인스턴스 상태와 무관)

## 요약 관계도:
```
MyThing.sum_with(...)   (독립: 벡터 합 + value_)
          ▲
          │ (pybind11이 list→vector 변환)
          │
Python list/tuple

MyThing.add_to_array(arr) ──▶ add_scalar_to_array(arr, self.peek())
                                     ▲
MyThing.add_scalar(arr, v) ──────────┘

# add_scalar_to_array: NumPy array_t<double> 받아 새 NumPy 배열을 만들어 반환
```

## 단계별 실행 흐름

### 1) t.add_to_array(arr) 를 호출할 때
- 파이썬에서 전달한 arr는 pybind11이 py::array_t<double>로 받습니다
- (바인딩에서 c_style | forcecast라 double로 강제 캐스팅 & C-연속성 보장).
- 람다 내부가 self.peek()을 호출해 현재 value_(정수)를 읽습니다. (const 멤버)
- 자유 함수 add_scalar_to_array(arr, (double)self.peek()) 호출.
  - add_scalar_to_array 내부:
  - request()로 버퍼 정보 획득 → shape 체크 (ndim >= 1 아니면 MyError 던짐).
  - 동일한 shape의 새 배열을 만들고 포인터로 전체 원소를 순회하며 + val.
  - 새 NumPy 배열을 파이썬으로 반환. (원본 arr는 변경되지 않음)
  - 포인트: 인스턴스의 상태(value_)를 스칼라로 끌어와 배열 연산에 쓰는 멤버-연동 버전.

### 2) MyThing.add_scalar(arr, v) 를 호출할 때
- 인스턴스가 없어도 됩니다(정적).
- 자유 함수 add_scalar_to_array(arr, v)를 그대로 호출합니다.
- 위와 동일한 방식으로 새 배열을 만들어 반환합니다.
- 포인트: 인스턴스 상태와 무관한 순수 함수 스타일 진입점.

### 3) t.sum_with([1.5, 2.5]) 를 호출할 때
- 파이썬의 list/tuple을 pybind11이 자동으로 std::vector<double>로 변환합니다.
- C++ sum_with는 벡터를 순회해 합계를 만들고, value_를 double로 캐스팅해 더합니다.
- 스칼라(double) 값을 반환합니다. (배열 반환 아님. NumPy와 독립)
- 포인트: 이건 배열-원소별 연산이 아니라 “합계 + 상태” 계산

## 예외 흐름 (참고)
- add_scalar_to_array는 ndim < 1이면 MyError를 던집니다.
- 모듈 초기화 시 py::exception<MyError> ex(m, "MyError"); 로 예외 매핑을 등록했기 때문에, 파이썬 쪽에서는 mything.MyError로 잡을 수 있습니다.

## 한 줄 정리
- 공통 핵심 로직은 add_scalar_to_array (자유 함수).
- 멤버 버전 add_to_array는 self.peek()로 꺼낸 현재 값으로 이 유틸을 호출.
- 정적 버전 add_scalar는 임의 스칼라로 이 유틸을 호출.
- sum_with는 배열 유틸과 별개로, 파이썬 시퀀스→std::vector 변환을 활용해 “합계 + 상태”를 계산하는 순수 스칼라 함수.
