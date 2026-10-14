## 📘 Lambda, Map, Filter, Reduce
### 📌 lambda: 익명 함수
```python
cul = lambda a, b, c: a + b + c
print(cul(10, 15, 20))  # 45
```
- lambda는 이름 없는 함수를 한 줄로 정의할 때 사용
- 간단한 연산, 콜백 함수, 고차 함수 인자로 자주 활용됨

### 📌 map: 데이터 변환
```python
digits1 = [x * 10 for x in range(1, 11)]  # [10, 20, ..., 100]
result = map(lambda i: i ** 2, digits1)
print(list(result))  # [100, 400, ..., 10000]
```

- map(func, iterable)은 각 요소에 함수를 적용해 새로운 iterable 반환
- lambda 또는 일반 함수 모두 사용 가능
```python
def also_square(nums):
    def double(x):
        return x ** 2
    return map(double, nums)
```

- 위처럼 내부 함수와 함께 사용하면 클로저처럼 동작 가능

### 📌 filter: 조건 기반 추출
```python
even = filter(lambda i: i % 2 == 0, digits)
print(list(even))  # [2, 4, 6, 8, 10]
```

- filter(func, iterable)은 조건을 만족하는 요소만 추출
- lambda 또는 일반 함수로 조건 정의
```python
def also_evens(nums):
    def is_even(x):
        return x % 2 == 0
    return filter(is_even, nums)
```
- 실무에서는 데이터 정제, 유효성 검사에 자주 사용됨

```python
even = [i for i in digits if i % 2 == 0]
```
```python
result = []

for i in digits:
    if i % 2 == 0:
        result.append(i)
```

### 📌 reduce: 누적 처리
```python
from functools import reduce
digits3 = [x for x in range(1, 101)]
result = reduce(lambda x, y: x + y, digits3, 10)  # 5060
```

- reduce(func, iterable, initializer)는 누적 계산을 수행
- 초기값 10부터 시작해 모든 요소를 더함
```python
digits4 = ['a', 'b', 'c', 'd']
result = reduce(lambda x, y: x + ';' + y, digits4)  # 'a;b;c;d'
```

- 문자열 연결, 리스트 병합, 누적 통계 등 다양한 용도

### 📌 실무에서 왜 중요한가?

| 함수       | 실무 활용 예시                                                                 |
|------------|----------------------------------------------------------------------------------|
| `lambda`   | 간단한 연산, 정렬 기준, 이벤트 핸들러, 고차 함수 인자 등에서 **익명 함수로 빠르게 처리** 가능 |
| `map`      | 리스트, 튜플 등 반복 가능한 객체에 **일괄 변환 로직 적용** → 데이터 전처리, 형 변환, 벡터 연산 |
| `filter`   | 조건 기반으로 **데이터 정제 및 추출** → 유효성 검사, 로그 필터링, 사용자 권한 분류 등         |
| `reduce`   | 반복 요소에 대해 **누적 계산 수행** → 합계, 통계, 문자열 조합, 리스트 병합 등                 |

### 📌 요약
- lambda: 간단한 익명 함수
- map: 각 요소에 함수 적용
- filter: 조건에 맞는 요소 추출
- reduce: 누적 계산
