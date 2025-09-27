# 🧪 Basic (Array Creation)
## 📌 기본 배열 생성 및 속성 확인

```python
import numpy as np

a = np.arange(15).reshape(3, 5)
print(a)
```

```
[[ 0  1  2  3  4]
 [ 5  6  7  8  9]
 [10 11 12 13 14]]
```

## ✅ 배열 속성 확인
```python
print(a.shape)        # (3, 5) → 3행 5열
print(a.ndim)         # 2 → 2차원 배열
print(a.dtype.name)   # int64 → 데이터 타입
print(a.itemsize)     # 8 → 각 요소의 바이트 크기
print(type(a))        # <class 'numpy.ndarray'>
```


## 📌 다양한 방식의 배열 생성
### 1. 정수 배열
```python
b = np.array([1, 2, 3, 4, 5])
print(b)              # [1 2 3 4 5]
print(type(b))        # <class 'numpy.ndarray'>
```

### 2. 실수 배열
```python
c = np.array([1.2, 3.5, 5.1])
print(c.dtype)        # float64
```

### 3. 잘못된 배열 생성 (오류 예시)
```python
# d = np.array(1.2, 3.5, 5.1)
```

TypeError: array() takes from 1 to 2 positional arguments but 3 were given

#### ✅ 올바른 방식: np.array([1.2, 3.5, 5.1]) 처럼 리스트나 튜플로 감싸야 함


### 📌 튜플을 이용한 2차원 배열
```python
e = np.array([(1.5, 2, 3), (4, 5, 6)])
print(e)


[[1.5 2.  3. ]
 [4.  5.  6. ]]


print(e.shape)        # (2, 3)

```

### 📌 복소수 배열 생성
```python
f = np.array([[1, 2], [3, 4]], dtype=complex)
print(f)


[[1.+0.j 2.+0.j]
 [3.+0.j 4.+0.j]]

```

## 🧠 보강 포인트

### 🔹 배열 생성 함수 요약
| 함수              | 설명                                                             |
|-------------------|------------------------------------------------------------------|
| `np.array()`      | 리스트나 튜플을 배열로 변환 → 가장 기본적인 배열 생성 방법           |
| `np.arange()`     | `range()`처럼 연속된 값 생성 → 정수 또는 실수 범위 지정 가능         |
| `np.zeros()`      | 모든 요소가 0인 배열 생성 → 초기화된 배열 만들 때 유용               |
| `np.ones()`       | 모든 요소가 1인 배열 생성 → 기본값으로 채운 배열 만들 때 사용         |
| `np.empty()`      | 초기화되지 않은 배열 생성 → 빠르지만 값이 랜덤일 수 있음             |
| `np.full()`       | 지정한 값으로 채운 배열 생성 → 특정 상수로 배열 초기화할 때 사용       |
| `np.eye()`        | 단위 행렬 생성 → 선형대수, 행렬 연산에서 자주 사용됨                 |
| `np.linspace()`   | 시작~끝 사이의 값을 일정 간격으로 나눈 배열 생성 → 그래프, 시뮬레이션 등 |


## 💬 한마디
배열 생성은 NumPy의 시작이자 끝이야.
다양한 방식으로 배열을 만들 수 있다는 건, 데이터를 자유롭게 다룰 수 있다는 뜻.



