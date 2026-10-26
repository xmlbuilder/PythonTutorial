## 📘 데이터 타입

### 📌 NumPy 기본 데이터 타입 매핑
```
┌────────────────────────────┬────────────────────────────┬────────────────────────────────────────────────────────────┐
│ NumPy Type                 │ C Type                     │ Description                                                │
├────────────────────────────┼────────────────────────────┼────────────────────────────────────────────────────────────┤
│ np.bool_                   │ bool                       │ Boolean (True/False), stored as a byte                     │
│ np.byte                    │ signed char                │ Platform-defined                                           │
│ np.ubyte                   │ unsigned char              │ Platform-defined                                           │
│ np.short                   │ short                      │ Platform-defined                                           │
│ np.ushort                  │ unsigned short             │ Platform-defined                                           │
│ np.intc                    │ int                        │ Platform-defined                                           │
│ np.uintc                   │ unsigned int               │ Platform-defined                                           │
│ np.int_                    │ long                       │ Platform-defined                                           │
│ np.uint                    │ unsigned long              │ Platform-defined                                           │
│ np.longlong                │ long long                  │ Platform-defined                                           │
│ np.ulonglong               │ unsigned long long         │ Platform-defined                                           │
│ np.half / np.float16       │ —                          │ Half precision float (5-bit exponent, 10-bit mantissa)     │
│ np.single                  │ float                      │ Single precision float (8-bit exponent, 23-bit mantissa)   │
│ np.double                  │ double                     │ Double precision float (11-bit exponent, 52-bit mantissa)  │
│ np.longdouble              │ long double                │ Extended precision float                                   │
│ np.clongdouble             │ long double                │ Extended precision float                                   │
│ np.csingle                 │ float complex              │ Complex: 2 single-precision floats                         │
│ np.cdouble                 │ double complex             │ Complex: 2 double-precision floats                         │
│ np.clongdouble             │ long double complex        │ Complex: 2 extended-precision floats                       │
│ np.int8                    │ int8_t                     │ Integer (-128 to 127)                                      │
│ np.int16                   │ int16_t                    │ Integer (-32,768 to 32,767)                                │
│ np.int32                   │ int32_t                    │ Integer (-2,147,483,648 to 2,147,483,647)                  │
│ np.int64                   │ int64_t                    │ Integer (-9.2e18 to 9.2e18)                                │
│ np.uint8                   │ uint8_t                    │ Unsigned (0 to 255)                                        │
│ np.uint16                  │ uint16_t                   │ Unsigned (0 to 65,535)                                     │
│ np.uint32                  │ uint32_t                   │ Unsigned (0 to 4.2e9)                                      │
│ np.uint64                  │ uint64_t                   │ Unsigned (0 to 1.8e19)                                     │
│ np.intp                    │ intptr_t                   │ Integer for indexing (platform-dependent)                  │
│ np.uintp                   │ uintptr_t                  │ Unsigned integer for pointer-sized values                  │
│ np.float64 / np.float_     │ double                     │ Same precision as Python built-in `float`                  │
│ np.complex64               │ float complex              │ Complex: 2 × 32-bit floats                                 │
│ np.complex128 / np.complex_│ double complex             │ Same precision as Python built-in `complex`                │
└────────────────────────────┴────────────────────────────┴────────────────────────────────────────────────────────────┘
```

### 📌 추가 설명 및 실무 활용 팁

#### 🔹 정수형 (int8, int16, int32, int64)
- 메모리 최적화가 중요할 때 유용 (예: 이미지 처리에서 uint8)
- intp는 배열 인덱싱에 사용됨 → 플랫폼에 따라 32비트 또는 64비트

#### 🔹 부동소수점형 (float16, float32, float64, longdouble)
- float16: 메모리 절약용, 정확도 낮음 → 딥러닝에서 사용됨
- float64: 기본 float → 대부분의 수치 계산에 사용
- longdouble: 고정밀 계산용 → 플랫폼마다 다르게 동작할 수 있음

#### 🔹 복소수형 (complex64, complex128)
- 과학 계산, 신호 처리, 푸리에 변환 등에 사용
- complex128은 Python의 기본 complex와 동일한 정밀도

#### 🔹 논리형 (bool_)
- 마스크 연산, 조건 필터링 등에 사용됨 → array > 0 같은 표현에서 자주 등장

### 📌 한마디
- NumPy의 데이터 타입은 단순한 숫자 저장 그 이상.
- 메모리 효율, 계산 속도, 정확도까지 모두 좌우하는 핵심 요소.

----

### 📌 NumPy의 데이터 타입을 구체적으로 검증

### 📌 NumPy의 데이터 타입을 구체적으로 검증하는 목적:
- 배열의 dtype을 확인하거나 비교
- 특정 타입으로 변환 (astype)
- 타입별 범위나 메모리 크기 확인
- C 타입과의 호환성 체크


### 📌 NumPy 데이터 타입 검증 샘플
#### 🔹 1. 배열의 dtype 확인
```python
import numpy as np

arr = np.array([1, 2, 3], dtype=np.int32)
print(arr.dtype)  # 출력: int32
```

#### 🔹 2. dtype 비교
```python
if arr.dtype == np.int32:
    print("정수형 32비트 배열입니다.")
```

#### 🔹 3. dtype 변환 (astype)
```python
float_arr = arr.astype(np.float64)
print(float_arr.dtype)  # 출력: float64
```

#### 🔹 4. dtype의 메모리 크기 확인
```python
print(arr.itemsize)  # 출력: 4 (int32는 4바이트)
```

#### 🔹 5. dtype의 최대/최소값 확인
```python
print(np.iinfo(np.int32).min)  # -2147483648
print(np.iinfo(np.int32).max)  # 2147483647

print(np.finfo(np.float64).eps)  # float64의 최소 유효값
```

#### 🔹 6. dtype 종류 나열
```python
print(np.sctypeDict.keys())  # NumPy에서 지원하는 모든 dtype 키워드
```


### 📌 실무 팁

| 목적 또는 상황             | 활용 방법 또는 함수 설명                                         |
|----------------------------|------------------------------------------------------------------|
| 데이터 타입 확인           | `arr.dtype`, `type(arr[0])` → 배열 전체 또는 개별 요소의 타입 확인 |
| 타입 변환                  | `arr.astype(np.float64)` → 원하는 타입으로 배열 변환               |
| 메모리 최적화              | `arr.itemsize`, `np.uint8`, `np.float16` → 바이트 크기 및 경량 타입 활용 |
| 값 범위 검증               | `np.iinfo(np.int32)`, `np.finfo(np.float64)` → 정수/실수 타입의 min/max 확인 |
| C 코드와 연동              | `arr.ctypes.data_as()` → C 포인터로 NumPy 배열 전달 가능             |


### 📌 NumPy dtype 선택 기준

| 상황 또는 목적             | 추천 dtype                        | 설명 또는 선택 이유                                           |
|----------------------------|------------------------------------|---------------------------------------------------------------|
| 이미지 처리 (픽셀 값)       | `np.uint8`                         | 0~255 범위, 메모리 절약에 최적화                               |
| 대규모 정수 배열            | `np.int32`, `np.int64`             | 플랫폼에 따라 선택. 64비트 시스템이면 `int64` 권장              |
| 메모리 최적화가 중요한 경우 | `np.float16`, `np.uint8`           | 경량 타입으로 메모리 사용량 최소화                              |
| 고정밀 수치 계산            | `np.float64`                       | 과학 계산, 통계 분석, 머신러닝에서 기본적으로 사용됨            |
| 복소수 계산                | `np.complex64`, `np.complex128`    | 푸리에 변환, 신호 처리 등에서 사용됨                           |
| 인덱싱 또는 포인터 연산     | `np.intp`, `np.uintp`              | 시스템 포인터 크기와 일치 → 배열 인덱싱에 안정적                |
| C 코드와 연동              | `np.int32`, `np.float32`           | C의 `int`, `float`와 정확히 매칭되는 타입 선택 필요             |
| GPU 연산 (딥러닝 등)        | `np.float16`, `np.float32`         | GPU는 `float64`보다 `float32`에 최적화되어 있음                 |
| 시간 또는 날짜 처리         | `np.datetime64`, `np.timedelta64`  | 날짜/시간 연산에 특화된 dtype                                  |



### 📌 실무 팁
- 정수 vs 부동소수점: 정수는 정확한 값이 필요할 때, 부동소수점은 연산이 많은 경우에 사용
- 메모리 절약: float64 대신 float32 또는 float16을 쓰면 메모리 사용량이 절반 이하로 줄어듦
- 정밀도 요구: 금융, 과학 계산에서는 float64 이상을 권장
- 호환성 고려: 외부 라이브러리(C, GPU 등)와 연동 시 해당 환경의 타입과 맞춰야 함

### 📌 예시 비교
```python
import numpy as np
```
#### 🔹 메모리 비교
```python
a = np.ones((1000, 1000), dtype=np.float64)  # 약 8MB
b = np.ones((1000, 1000), dtype=np.float32)  # 약 4MB
c = np.ones((1000, 1000), dtype=np.float16)  # 약 2MB
```

#### 🔹 정밀도 비교
```python
print(np.finfo(np.float64).eps)  # 2.22e-16
print(np.finfo(np.float32).eps)  # 1.19e-07
print(np.finfo(np.float16).eps)  # 9.77e-04
```

#### 🔹 실제 예제 및 결과 출력

```python
import numpy as np

x = np.float32(1.0)
print(x)
```
#### 🔹 결과 출력

```
1.0
```
```python
y = np.int_([1, 2, 4])
print(y)
```
#### 🔹 결과 출력
```
[1 2 4]
```
```python
print(y.dtype)
```
#### 🔹 결과 출력
```
int64
```
```python
z = np.arange(3, dtype=np.uint8)
print(z, z.dtype)
```
#### 🔹 결과 출력
```
[0 1 2] uint8
```
```python
x1 = np.array([1, 2, 4], dtype='f')
print(x1, x1.dtype)
```
#### 🔹 결과 출력
```
[1. 2. 4.] float32
```
```python
x2 = z.astype('f')
print(x2, x2.dtype)
#### 🔹 결과 출력
```
[0. 1. 2.] float32
```

```python
d = np.dtype(int)
print(d)
```
#### 🔹 결과 출력
```
int64
```
```python
print(type(d))
```
#### 🔹 결과 출력
```
<class 'numpy.dtypes.Int64DType'>
```
```python
print(np.issubdtype(d, np.integer))
```
#### 🔹 결과 출력
```
True
```
```python
print(np.issubdtype(d, np.floating))
```
#### 🔹 결과 출력
```
False
```

#### 🔹 overflow
```python
print(np.power(100, 8, dtype=np.int64))
```
#### 🔹 결과 출력
```
10000000000000000
```

```python
print(np.power(100, 8, dtype=np.int32))
```
#### 🔹 결과 출력
```
1874919424
```
```python
print(np.iinfo(int))
```
#### 🔹 결과 출력
```
Machine parameters for int64
---------------------------------------------------------------
min = -9223372036854775808
max = 9223372036854775807
---------------------------------------------------------------
```
```python
print(np.iinfo(np.int32))
```
#### 🔹 결과 출력
```
Machine parameters for int32
---------------------------------------------------------------
min = -2147483648
max = 2147483647
---------------------------------------------------------------
```
```python
print(np.finfo(np.float64))
```
#### 🔹 결과 출력
```
---------------------------------------------------------------
precision =  15   resolution = 1.0000000000000001e-15
machep =    -52   eps =        2.2204460492503131e-16
negep =     -53   epsneg =     1.1102230246251565e-16
minexp =  -1022   tiny =       2.2250738585072014e-308
maxexp =   1024   max =        1.7976931348623157e+308
nexp =       11   min =        -max
smallest_normal = 2.2250738585072014e-308   smallest_subnormal = 4.9406564584124654e-324
---------------------------------------------------------------
```
```python
x = np.array([[1, 2.0], [0, 0], (1+1j, 3.0)])
print(x)
```
#### 🔹 결과 출력
```
[[1.+0.j 2.+0.j]
 [0.+0.j 0.+0.j]
 [1.+1.j 3.+0.j]]
```

```python
d = np.indices((3, 3))

print(d, d.shape)
```
#### 🔹 결과 출력
```
[[[0 0 0]
  [1 1 1]
  [2 2 2]]
 [[0 1 2]
  [0 1 2]
  [0 1 2]]]
  
  (2,3,3)
```

---

#### 🔹 np.indices((3, 3))
- np.indices((3, 3))를 사용해서 2차원 인덱스 배열을 생성. 
- 아래에 구조와 의미를 단계별로 분석.

#### 🔹 코드 분석
```python
import numpy as np
d = np.indices((3, 3))
print(d, d.shape)
```

#### 🔹 결과
```
array([[[0, 0, 0],
        [1, 1, 1],
        [2, 2, 2]],

       [[0, 1, 2],
        [0, 1, 2],
        [0, 1, 2]]])

d.shape → (2, 3, 3)
```


#### 🔹 구조 설명
- np.indices((3, 3))는 (3, 3) 크기의 배열에 대한 인덱스 좌표를 생성.
    - 결과는 2개의 배열로 구성됨:
    - 첫 번째 배열: 행 인덱스
    - 두 번째 배열: 열 인덱스

#### 🔹 시각적으로 보면:
- 이 함수는 2차원 배열의 각 위치에 대해 행 인덱스와 열 인덱스를 생성해주는 도구.

#### 🔹 행 인덱스 배열 (d[0])
| 행\열 | 0 | 1 | 2 |
|-------|---|---|---|
| 0     | 0 | 0 | 0 |
| 1     | 1 | 1 | 1 |
| 2     | 2 | 2 | 2 |

#### 🔹 열 인덱스 배열 (d[1])
| 행\열 | 0 | 1 | 2 |
|-------|---|---|---|
| 0     | 0 | 1 | 2 |
| 1     | 0 | 1 | 2 |
| 2     | 0 | 1 | 2 |

#### 🔹 결과 배열 의미
- d[0]: 행 인덱스 배열 → 각 위치의 행 번호
```
[[0 0 0]
[1 1 1]
[2 2 2]]
```

- d[1]: 열 인덱스 배열 → 각 위치의 열 번호
```
[[0 1 2]
[0 1 2]
[0 1 2]]
```


#### 🔹 실무 활용 예시
- 마스크 연산, 좌표 기반 계산, 그리드 생성 등에 자주 사용됨
- 예: 이미지 처리에서 각 픽셀의 위치를 기준으로 연산할 때

```python
rows, cols = np.indices((3, 3))
mask = (rows + cols) % 2 == 0  # 체스판 패턴처럼 만들기
```
---

