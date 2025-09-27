# 📦 Basic Stacking — 배열 결합의 기본
## ✅ 핵심 목적
- 여러 배열을 하나로 합치는 방법
- 방향에 따라 수직(vstack), 수평(hstack), 열(column_stack) 등 다양한 방식 존재

## 샘플 예제
```python
import numpy as np
a = np.floor(10 * np.random.random((2, 2)))
b = np.floor(10 * np.random.random((2, 2)))
print(a)
'''
[[0. 2.]
 [2. 8.]]
 '''
print(b)
'''
[[1. 9.]
 [8. 2.]]

c = np.vstack((a, b))
print(c)
'''
[[0. 2.]
 [2. 8.]
 [1. 9.]
 [8. 2.]]
 '''
d = np.hstack((a, b))
print(d)
'''
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
'''
d = np.column_stack((a, b))
print(d)
'''
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
'''
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
c1 = np.column_stack((a1, b1))
print(c1)
'''
[[4. 3.]
 [2. 8.]]
 '''
d2 = np.hstack((a1, b1))
print(d2)
'''
[4. 2. 3. 8.]
'''
e1 = a1[:, np.newaxis]
print(e1)
'''
[[4.]
 [2.]]
 '''
f1 = np.column_stack((a1[:, np.newaxis], b1[:, np.newaxis]))
print(f1)
'''
[[4. 3.]
 [2. 8.]]
'''
g1 = np.hstack((a1[:, np.newaxis], b1[:, np.newaxis]))
'''
[[4. 3.]
 [2. 8.]]
'''
print(np.r_[1:4, 0, 4])
'''[1 2 3 0 4]'''
```


## 🔹 1. np.vstack() — 수직 결합
- 행 방향으로 쌓기
- 배열의 열 수가 같아야 함
```python
a = np.array([[0. 2.]
 [2. 8.]])

b = np.array([[1. 9.]
 [8. 2.]])

c = np.vstack((a, b))
```

### 결과:
```
[[0. 2.]
 [2. 8.]
 [1. 9.]
 [8. 2.]]
```


### 🔹 2. np.hstack() — 수평 결합
- 열 방향으로 붙이기
- 배열의 행 수가 같아야 함
```python
d = np.hstack((a, b))
```

### 결과:
```python
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
```


## 🔹 3. np.column_stack() — 열 단위 결합
- 1D 배열을 열 방향으로 붙일 때 유용
- 2D 배열에는 hstack()과 동일하게 작동

```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
c1 = np.column_stack((a1, b1))
```

### 결과:
```
[[4. 3.]
 [2. 8.]]
```


## 🔹 4. np.hstack() with 1D → 1D 연결
```python
d2 = np.hstack((a1, b1))
```

### 결과:
```
[4. 2. 3. 8.]
```


## 🔹 5. np.newaxis로 차원 확장
- 1D 배열을 2D로 변환해 열 단위 결합 가능
```python
a1 = np.array([4., 2.])
e1 = a1[:, np.newaxis]
```

### 결과:
```
[[4.]
 [2.]]
```


## 🔹 6. np.column_stack() with newaxis
```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
f1 = np.column_stack((a1[:, np.newaxis], b1[:, np.newaxis]))
```

### 결과:
```
[[4. 3.]
 [2. 8.]]
```


### 🔹 7. np.hstack() with newaxis
```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
g1 = np.hstack((a1[:, np.newaxis], b1[:, np.newaxis]))
```

### 결과:
```
[[4. 3.]
 [2. 8.]]
```


## 🔹 8. np.r_[] — 빠른 연결
- 슬라이싱과 값 나열을 한 번에 연결
```python
np.r_[1:4, 0, 4]
```

### 결과:
```
[1 2 3 0 4]
```

## 🧠 보강 포인트 요약
| 함수               | 설명                                      | 조건 또는 특징                     | 예시 결과 또는 형태               |
|--------------------|-------------------------------------------|------------------------------------|-----------------------------------|
| np.vstack()        | 행 방향으로 쌓기                          | 열 수 동일                         | [[a], [b]] 형태로 위아래로 결합   |
| np.hstack()        | 열 방향으로 붙이기                        | 행 수 동일                         | [[a b]] 형태로 좌우로 결합        |
| np.column_stack()  | 열 단위 결합 (1D → 2D 변환에 유용)        | 자동으로 열로 정렬                 | [[a1 b1], [a2 b2]] 형태           |
| np.r_[]            | 슬라이싱과 값 연결                        | 빠른 1D 배열 생성                  | [1 2 3 0 4]                       |
| np.newaxis         | 차원 확장                                 | 1D → 2D 변환                       | [1 2 3] → [[1], [2], [3]]         |


## 💬 한마디
배열 결합은 단순한 연결을 넘어서
데이터 정렬, 모델 입력 구성, 피처 병합에 핵심.
특히 column_stack과 newaxis는 1D 데이터를 2D로 바꿀 때 정말 유용.


---




