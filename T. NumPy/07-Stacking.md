## 📘 Basic Stacking — 배열 결합의 기본
### 📌 핵심 목적
- 여러 배열을 하나로 합치는 방법
- 방향에 따라 수직(vstack), 수평(hstack), 열(column_stack) 등 다양한 방식 존재

### 📌 샘플 예제
```python
import numpy as np
a = np.floor(10 * np.random.random((2, 2)))
b = np.floor(10 * np.random.random((2, 2)))
print(a)
```
#### 🔹 출력 결과
```
[[0. 2.]
 [2. 8.]]
```
```python
print(b)
```
#### 🔹 출력 결과
```
[[1. 9.]
 [8. 2.]]
```
```python
c = np.vstack((a, b))
print(c)
```
#### 🔹 출력 결과
```
[[0. 2.]
 [2. 8.]
 [1. 9.]
 [8. 2.]]
```
```python
d = np.hstack((a, b))
print(d)
```
#### 🔹 출력 결과
```
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
```
```python
d = np.column_stack((a, b))
print(d)
```
#### 🔹 출력 결과
```
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
```
```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
c1 = np.column_stack((a1, b1))
print(c1)
```
#### 🔹 출력 결과
```
[[4. 3.]
 [2. 8.]]
```
```python
d2 = np.hstack((a1, b1))
print(d2)
```
#### 🔹 출력 결과
```
[4. 2. 3. 8.]
```
```python
e1 = a1[:, np.newaxis]
print(e1)
```
#### 🔹 출력 결과
```
[[4.]
 [2.]]
```
```python
f1 = np.column_stack((a1[:, np.newaxis], b1[:, np.newaxis]))
print(f1)
```
#### 🔹 출력 결과
```
[[4. 3.]
 [2. 8.]]
```
```python
g1 = np.hstack((a1[:, np.newaxis], b1[:, np.newaxis]))
```
#### 🔹 출력 결과
```
[[4. 3.]
 [2. 8.]]
```

```python
print(np.r_[1:4, 0, 4])
'''[1 2 3 0 4]'''
```
- np.r_[]는 NumPy에서 숫자 범위(range)와 배열, 개별 숫자를 하나의 배열로 연결하는 기능입니다.

#### 🔹 1. np.vstack() — 수직 결합
- 행 방향으로 쌓기
- 배열의 열 수가 같아야 함
```python
a = np.array([[0. 2.]
 [2. 8.]])

b = np.array([[1. 9.]
 [8. 2.]])

c = np.vstack((a, b))
```

#### 🔹 결과:
```
[[0. 2.]
 [2. 8.]
 [1. 9.]
 [8. 2.]]
```

#### 🔹 2. np.hstack() — 수평 결합
- 열 방향으로 붙이기
- 배열의 행 수가 같아야 함
```python
d = np.hstack((a, b))
```

#### 🔹 결과:
```python
[[0. 2. 1. 9.]
 [2. 8. 8. 2.]]
```

#### 🔹 3. np.column_stack() — 열 단위 결합
- 1D 배열을 열 방향으로 붙일 때 유용
- 2D 배열에는 hstack()과 동일하게 작동

```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
c1 = np.column_stack((a1, b1))
```

#### 🔹 결과:
```
[[4. 3.]
 [2. 8.]]
```

#### 🔹 4. np.hstack() with 1D → 1D 연결
```python
d2 = np.hstack((a1, b1))
```

#### 🔹 결과:
```
[4. 2. 3. 8.]
```

#### 🔹 5. np.newaxis로 차원 확장
- 1D 배열을 2D로 변환해 열 단위 결합 가능
```python
a1 = np.array([4., 2.])
e1 = a1[:, np.newaxis]
```

#### 결과:
```
[[4.]
 [2.]]
```

#### 🔹 6. np.column_stack() with newaxis
```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
f1 = np.column_stack((a1[:, np.newaxis], b1[:, np.newaxis]))
```

#### 🔹 결과:
```
[[4. 3.]
 [2. 8.]]
```


#### 🔹 7. np.hstack() with newaxis
```python
a1 = np.array([4., 2.])
b1 = np.array([3., 8.])
g1 = np.hstack((a1[:, np.newaxis], b1[:, np.newaxis]))
```

#### 🔹 결과:
```
[[4. 3.]
 [2. 8.]]
```


#### 🔹 8. np.r_[] — 빠른 연결
- 슬라이싱과 값 나열을 한 번에 연결
```python
np.r_[1:4, 0, 4]
```

#### 🔹 결과:
```
[1 2 3 0 4]
```

### 📌 보강 포인트 요약
| 함수               | 설명                                      | 조건 또는 특징                     | 예시 결과 또는 형태               |
|--------------------|-------------------------------------------|------------------------------------|-----------------------------------|
| `np.vstack()`        | 행 방향으로 쌓기                          | 열 수 동일                         | [[a], [b]] 형태로 위아래로 결합   |
| `np.hstack()`       | 열 방향으로 붙이기                        | 행 수 동일                         | [[a b]] 형태로 좌우로 결합        |
| `np.column_stack()`  | 열 단위 결합 (1D → 2D 변환에 유용)        | 자동으로 열로 정렬                 | [[a1 b1], [a2 b2]] 형태           |
| `np.r_[]`            | 슬라이싱과 값 연결                        | 빠른 1D 배열 생성                  | [1 2 3 0 4]                       |
| `np.newaxis`         | 차원 확장                                 | 1D → 2D 변환                       | [1 2 3] → [[1], [2], [3]]         |


### 📌 한마디
- 배열 결합은 단순한 연결을 넘어서 데이터 정렬, 모델 입력 구성, 피처 병합에 핵심.  
- 특히 column_stack과 newaxis는 1D 데이터를 2D로 바꿀 때 정말 유용.  

---

### 📌 hstack/column_stack 차이
- np.hstack()과 np.column_stack()은 둘 다 배열을 결합하는 함수이지만, 1차원 배열을 처리하는 방식이 다릅니다.

- 가장 중요한 차이는 다음과 같습니다.
 - np.hstack(): 1차원 배열은 옆으로 이어 붙여서 1차원 배열을 만듭니다.
 - np.column_stack(): 1차원 배열을 열 벡터로 변환한 다음 옆으로 결합하여 2차원 배열을 만듭니다.
 - 2차원 배열에서는 두 함수가 동일하게 동작합니다.
#### 🔹 1. 1차원 배열인 경우
```python
import numpy as np
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
np.hstack()
c = np.hstack((a, b))
print(c)
print(c.shape)
```

#### 🔹 결과:
```
[1 2 3 4 5 6]
(6,)
```

- 배열을 수평 방향으로 연결하지만 결과는 여전히 1차원입니다.
```
a = [1 2 3]
b = [4 5 6]

hstack → [1 2 3 4 5 6]
```
```python
np.column_stack()
c = np.column_stack((a, b))
print(c)
print(c.shape)
```
#### 🔹 결과:
```
[[1 4]
 [2 5]
 [3 6]]

(3, 2)
```

- 각 배열을 하나의 열로 취급합니다.
```
a      b       column_stack

1      4       1 4
2      5   →   2 5
3      6       3 6
```
- 즉, column_stack()은 1차원 배열을 (N, 1)로 변환한 후 결합하는 것과 같습니다.

#### 🔹 2. 2차원 배열인 경우
```python
a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6], [7, 8]])
```

- 이 경우 두 함수의 결과는 동일합니다.
```python
print(np.hstack((a, b)))
print(np.column_stack((a, b)))
```
#### 🔹 결과:
```
[[1 2 5 6]
 [3 4 7 8]]
```
- Shape는 (2, 4)입니다.


#### 🔹 3. 두 함수의 차이를 정리하면
| 입력 배열	| np.hstack()	| np.column_stack() |
|----------|-------------|--------------------|
| 1차원 | (3,), (3,)	| (6,)	| (3, 2) |
| 2차원 | (3, 2), (3, 2)	| (3, 4)	| (3, 4) |
| 2차원 | (3, 1), (3, 1)	| (3, 2)	| (3, 2) |
| 1차원 | (3,), 2차원 (3, 2)	| 오류	| (3, 3) |

- 특히 마지막 경우를 보면 차이가 분명해집니다.
```python
a = np.array([1, 2, 3])
b = np.array([[10, 20], [30, 40], [50, 60]])
print(np.column_stack((a, b)))
```
#### 🔹 결과:
```
[[ 1 10 20]
 [ 2 30 40]
 [ 3 50 60]]
```

- column_stack()은 a를 (3,1)로 변환하여 b와 결합합니다.
- 반면 hstack()은 1차원과 2차원 배열을 그대로 결합하려고 하므로 오류가 발생합니다.
#### 🔹 4. 내부 동작을 기준으로 이해하기
- 두 함수의 동작을 간략히 표현하면 다음과 같습니다.
#### 🔹 hstack()
```python
# 모든 입력이 1차원이면 axis=0
np.concatenate((a, b), axis=0)
# 2차원 이상의 입력이면 axis=1
np.concatenate((a, b), axis=1)
```
#### 🔹 column_stack()
```python
# 1차원 입력을 먼저 열 벡터로 변환
a2 = np.atleast_2d(a).T
b2 = np.atleast_2d(b).T
np.concatenate((a2, b2), axis=1)
```

- 위 column_stack() 예시는 두 입력이 모두 1차원일 때의 동작입니다.
- 이미 2차원인 입력은 전치하지 않고 그대로 사용합니다.

### 📌 결론: 
- 여러 개의 1차원 데이터를 각각 하나의 열(Column)로 만들어 2차원 데이터 테이블을 구성하려면 np.column_stack()이 적합합니다.
- 단순히 1차원 데이터를 길게 이어 붙이려면 np.hstack()을 사용하면 됩니다.





