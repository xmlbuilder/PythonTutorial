## 📘 NumPy Basic Operation

### 📌 기본 배열 연산 요약

| 연산 표현     | 예시 코드 | 설명                                      |
|---------------|------------|-------------------------------------------|
| 덧셈          | `a + b`    | 각 요소끼리 더함                           |
| 뺄셈          | `a - b`    | 각 요소끼리 뺌                             |
| 곱셈          | `a * b`    | 각 요소끼리 곱함                           |
| 나눗셈        | `a / b`    | 각 요소끼리 나눔                           |
| 제곱          | `b ** 2`   | 각 요소를 제곱                             |
| 조건 비교     | `a < 35`   | 각 요소가 조건을 만족하는지 Boolean 반환   |

#### 🔹 예시 결과
```python
a = np.array([20, 30, 40, 50])
b = np.arange(4)

print(a + b)     # [20 31 42 53]
print(a - b)     # [20 29 38 47]
print(a * b)     # [ 0 30 80 150]
print(a / b)     # [inf 30. 20. 16.666...]  # b[0] = 0 → ZeroDivisionWarning
print(b ** 2)    # [0 1 4 9]
print(a < 35)    # [True True False False]
```
---


### 📌 2. 행렬 연산

| 연산 표현           | 예시 코드         | 설명                                                             |
|---------------------|-------------------|------------------------------------------------------------------|
| 요소별 곱 (Hadamard)| `A * B`           | 같은 위치의 요소끼리 곱함 → 배열 크기가 같아야 함                  |
| 행렬 곱 (Dot Product)| `A @ B` 또는 `A.dot(B)` | 선형대수의 행렬 곱 → 내적 계산, 차원 조건 필요 (`A.shape[1] == B.shape[0]`) |

#### 🔹 예시 결과
```python
a = np.array([20, 30, 40, 50])
b = np.arange(4)

print(a + b)     # [20 31 42 53]
print(a @ b)     # 260
```
---

### 📌 3. 브로드캐스팅 연산
- 브로드캐스팅 연산의 핵심 개념과 너가 작성한 코드의 동작을 단계별로 자세히 설명.  
- NumPy의 브로드캐스팅은 배열 간 연산을 훨씬 유연하게 만들어주는 강력한 기능.     
    - 배열의 shape가 완전히 같지 않아도 연산 가능   
    - 단, 차원 끝에서부터 비교해서 조건을 만족해야 함

```python
a1 = np.ones((2, 3), dtype=int)
b1 = np.random.random((2, 3))
a1 *= 3
b1 += a1
```

#### 🔹 단계별 설명
#### ① np.ones((2, 3), dtype=int)
- a1 생성:
```
[[1 1 1]
[1 1 1]]
```

#### ② np.random.random((2, 3))
- b1 생성:
````
[[0.29 0.05 0.95]
[0.67 0.51 0.47]]  # 예시 값
````

#### ③ a1 *= 3
- a1의 모든 요소를 3배로 곱함 → in-place 연산
```
[[3 3 3]
[3 3 3]]
```

#### ④ b1 += a1
- b1의 각 요소에 a1의 대응 요소를 더함
- int + float → 결과는 float으로 자동 형 변환됨
````
[[3.29 3.05 3.95]
[3.67 3.51 3.47]]
````
---

### 📌 데이터 타입 승격 규칙 (브로드캐스팅 연산 중)
| 연산 조합            | 결과 dtype       | 설명                                      |
|----------------------|------------------|-------------------------------------------|
| `int + float`        | `float`          | 정수와 실수 연산 시 → 실수로 승격됨         |
| `float + complex`    | `complex`        | 실수와 복소수 연산 시 → 복소수로 승격됨     |
| `int + complex`      | `complex`        | 정수와 복소수 연산 시 → 복소수로 승격됨     |
| `bool + int`         | `int`            | Boolean과 정수 연산 시 → 정수로 승격됨       |
| `float32 + float64`  | `float64`        | 낮은 정밀도의 실수는 높은 정밀도로 승격됨    |

#### 🔹 예시 코드
```python
import numpy as np

a = np.array([1, 2, 3], dtype=int)
b = np.array([0.5, 1.5, 2.5], dtype=float)
c = np.array([1+2j, 3+4j, 5+6j], dtype=complex)

print((a + b).dtype)  # → float64
print((b + c).dtype)  # → complex128
print((a + c).dtype)  # → complex128
```

### 📌 주의할 점
```python
a += b  # 오류 발생
```
- a은 int, b은 float
- +=는 in-place 연산이므로 dtype 변경 불가
- 해결 방법: a = a + b 또는 a = a1.astype(float); a += b


### 📌 4. dtype 자동 변환
```python
a = np.ones(3, dtype=np.int32) # [1, 1, 1]
b = np.linspace(0, np.pi, 3) # [0, 1.57079633, 3.14159265]
c = a + b  # → float64 # [1.0, 2.57079633, 4.14159265]
d = np.exp(c * 1j)  # → complex128
```
```python
c * 1j # [1.0j, 2.57079633j, 4.14159265j]
```

#### 🔹 np.exp()의 복소수 계산
- 오일러 공식은 다음과 같습니다.

$$
\boxed{e^{i\theta} = \cos\theta + i\sin\theta}
$$

- 따라서 `np.exp(c * 1j)`는 각 원소에 대해 다음을 계산합니다.

$$
d_k = \cos(c_k) + i\sin(c_k)
$$

| c	| 실수부 cos(c)	| 허수부 sin(c) |
|----|--------------|---------------|
| 1.0	| 0.540302	 | 0.841471 |
| 2.570796	| -0.841471	| 0.540302 |
| 4.141593	| -0.540302	| -0.841471 |

#### 🔹 출력 결과
```
[ 0.54030231+0.84147098j
 -0.84147098+0.54030231j
 -0.54030231-0.84147098j]
```

- 연산 결과에 따라 dtype이 자동으로 승격됨

---
### 📌 5. 수학 함수 적용

| 함수         | 기능 또는 수식 표현 | 설명                                      |
|--------------|---------------------|-------------------------------------------|
| `np.sin()`   | `sin(x)`            | 사인 함수 → 각 요소에 대해 사인값 계산       |
| `np.exp()`   | `e^x`               | 지수 함수 → 자연상수 e의 거듭제곱 계산       |
| `np.sqrt()`  | `√x`                | 제곱근 계산 → 음수 입력 시 NaN 발생 가능     |
| `np.add()`   | `x + y`             | 두 배열을 더함 → 브로드캐스팅 지원           |

#### 🔹 예시 코드
```python
import numpy as np

x = np.array([0, 1, 2])
y = np.array([2.0, -1, 4.])

print(np.sin(x))     # → [0.         0.84147098 0.90929743]
print(np.exp(x))     # → [1.         2.71828183 7.3890561 ]
print(np.sqrt(x))    # → [0.         1.         1.41421356]
print(np.add(x, y))  # → [2. 0. 6.]
```
---

### 📌 6. 집계 함수 (Aggregation)
```python
a = np.random.random((2, 3))
a.sum()       # 전체 합
a.min()       # 최소값
a.max()       # 최대값
```
#### 🔹 예시 출력
```python
import numpy as np

a = np.random.random((2, 3))
print("배열 a:")
print(a)
```
#### 🔹 출력 결과
```
배열 a:
[[0.08384666 0.01391259 0.94030646]
 [0.76205091 0.01548114 0.64392931]]
```
```python
print("\na.sum()       # 전체 합")
print(a.sum())
```
#### 🔹 출력 결과
```
a.sum()       # 전체 합
2.4595270759161374
```
```python
print("\na.min()       # 최소값")
print(a.min())
```
#### 🔹 출력 결과
```
a.min()       # 최소값
0.013912593930435424
```
```python
print("\na.max()       # 최대값")
print(a.max())
```
#### 🔹 출력 결과
```
a.max()       # 최대값
0.9403064643053698
```

### 📌 집계 함수 보강 포인트
| 함수       | 예시 코드     | 설명                                      |
|------------|---------------|-------------------------------------------|
| `sum()`    | `a.sum()`     | 전체 요소의 합                            |
| `min()`    | `a.min()`     | 전체 요소 중 최소값                       |
| `max()`    | `a.max()`     | 전체 요소 중 최대값                       |
| `mean()`   | `a.mean()`    | 평균값 → 통계 분석에 자주 사용됨           |
| `std()`    | `a.std()`     | 표준편차 → 데이터의 분산 정도를 나타냄     |
| `var()`    | `a.var()`     | 분산 → 표준편차의 제곱                     |

---

### 📌 7. 축(axis) 기반 연산
```python
b = np.arange(12).reshape(3, 4)
b.sum(axis=0)       # 열 기준 합
b.sum(axis=1)       # 행 기준 합
b.min(axis=0)       # 열 기준 최소값
b.cumsum(axis=0)    # 열 기준 누적합
b.cumsum(axis=1)    # 행 기준 누적합

```
#### 🔹 예시 출력
```python
import numpy as np

b = np.arange(12).reshape(3, 4)
print("배열 b:")
print(b)
```
#### 🔹 출력 결과 (배열 b:)
```
[[ 0  1  2  3]
 [ 4  5  6  7]
 [ 8  9 10 11]]
```
```python
print("\nb.sum(axis=0)       # 열 기준 합")
print(b.sum(axis=0))
```
#### 🔹 출력 결과 (b.sum(axis=0)       # 열 기준 합)
```
[12 15 18 21]
```
```python
print("\nb.sum(axis=1)       # 행 기준 합")
print(b.sum(axis=1))
```
#### 🔹 출력 결과 (b.sum(axis=1)       # 행 기준 합)
```
[ 6 22 38]
```
```python
print("\nb.min(axis=0)       # 열 기준 최소값")
print(b.min(axis=0))
```
#### 🔹 출력 결과 (b.min(axis=0)       # 열 기준 최소값)
```
[0 1 2 3]
```
```python
print("\nb.cumsum(axis=0)    # 열 기준 누적합")
print(b.cumsum(axis=0))
```
#### 🔹 출력 결과 (b.cumsum(axis=0)    # 열 기준 누적합)
```
[[ 0  1  2  3]
 [ 4  6  8 10]
 [12 15 18 21]]
```
```python
print("\nb.cumsum(axis=1)    # 행 기준 누적합")
print(b.cumsum(axis=1))
```
#### 🔹 출력 결과 (b.cumsum(axis=1)    # 행 기준 누적합)
```
[[ 0  1  3  6]
 [ 4  9 15 22]
 [ 8 17 27 38]]
```

---

### 📌 8. 기타 연산 함수

| 함수             | 기능 또는 수식 표현 | 설명                                      |
|------------------|---------------------|-------------------------------------------|
| `np.add()`       | `x + y`             | 두 배열을 더함 → 브로드캐스팅 지원           |
| `np.subtract()`  | `x - y`             | 두 배열을 뺌 → 요소별 차 계산                |
| `np.multiply()`  | `x * y`             | 두 배열을 곱함 → 요소별 곱 계산               |
| `np.divide()`    | `x / y`             | 두 배열을 나눔 → 요소별 나눗셈 계산            |
| `np.power()`     | `x ** y`            | 거듭제곱 계산 → `x`의 `y`승                   |

#### 🔹 예시 코드
```python
import numpy as np

x = np.array([2, 4, 6])
y = np.array([1, 2, 3])

print(np.add(x, y))       # → [3 6 9]
print(np.subtract(x, y))  # → [1 2 3]
print(np.multiply(x, y))  # → [2 8 18]
print(np.divide(x, y))    # → [2. 2. 2.]
print(np.power(x, y))     # → [2 16 216]
```

### 📌 한마디
- NumPy의 기본 연산은 단순한 사칙연산을 넘어서  
- 브로드캐스팅, dtype 승격, 축 기반 연산, 수학 함수 적용까지 포함.
- 이걸 자유자재로 다룰 수 있으면, 데이터 분석과 머신러닝까지 연결 가능.

---

### 📌 실전 샘플
```python
import numpy as np
a = np.array([20, 30 ,40, 50])
b = np.arange(4)
c = a - b

print(c)
```
#### 🔹 출력 결과
```
[20 29 38 47]
```
```python
d  = b ** 2
print(d)
```
#### 🔹 출력 결과
```
[0 1 4 9]
```
```python
e = 10 * np.sin(a)
print(e)
```
#### 🔹 출력 결과
```
[ 9.12945251 -9.88031624  7.4511316  -2.62374854]
```
```python
f = a < 35
print(f)
```
#### 🔹 출력 결과
```
[ True  True False False]
```
```python
A = np.array([[1,1],
              [0, 1]])

B = np.array([[2,0],
              [3, 4]])
C = A * B
print(C)
```
#### 🔹 출력 결과
```
[[2 0]
 [0 4]]
```
```python
D = A @ B
print(D)
```
#### 🔹 출력 결과
```
[[5 4]
 [3 4]]
```
```python
E = A.dot(B)
print(E)
```
#### 🔹 출력 결과
```
[[5 4]
 [3 4]]
```
```python
a1 = np.ones((2, 3), dtype=int)
b1 = np.random.random((2, 3))
print(b1)
```
#### 🔹 출력 결과
```
[[0.2927232  0.05930611 0.95716545]
 [0.67861961 0.5103508  0.47676085]]
```
```python
a1 *= 3
print(a1)
```
#### 🔹 출력 결과
```
[[3 3 3]
 [3 3 3]]
```
```python
b1 += a1
print(b1)
```
#### 🔹 출력 결과
```
[[3.2927232  3.05930611 3.95716545]
 [3.67861961 3.5103508  3.47676085]]
```
```python
a1 += b1
print(a1)
```
#### 🔹 출력 결과
```
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/numpy_test.py", line 49, in <module>
    b1 = np.random.rand((2, 3))
         ^^^^^^^^^^^^^^^^^^^^^^
  File "numpy/random/mtrand.pyx", line 1242, in numpy.random.mtrand.RandomState.rand
  File "numpy/random/mtrand.pyx", line 441, in numpy.random.mtrand.RandomState.random_sample
  File "_common.pyx", line 312, in numpy.random._common.double_fill
TypeError: 'tuple' object cannot be interpreted as an integer
```

```python
import numpy as np

a = np.ones(3, dtype=np.int32)
b = np.linspace(0, np.pi, 3)

print(a.dtype.name)
```
#### 🔹 출력 결과
```
int32
```
```python
print(b.dtype.name)
```
#### 🔹 출력 결과
```
float64
```
```python
c = a + b
print(c)
```
#### 🔹 출력 결과
```
[1.         2.57079633 4.14159265]
```
```python
print(c.dtype.name)
```
#### 🔹 출력 결과
```
float64
```
```python
d = np.exp(c*1j)
print(d)
```
#### 🔹 출력 결과
```
[ 0.54030231+0.84147098j -0.84147098+0.54030231j -0.54030231-0.84147098j]
```
```python
print(d.dtype.name)
```
#### 🔹 출력 결과
```
complex128
```

```python
import numpy as np

a = np.random.random((2, 3))
print(a)
```
#### 🔹 출력 결과
```
[[0.08384666 0.01391259 0.94030646]
 [0.76205091 0.01548114 0.64392931]]
```
```python
print(a.sum())
```
#### 🔹 출력 결과
```
2.4595270759161374
```
```python
print(a.min())
```
#### 🔹 출력 결과
```
0.013912593930435424
```

```python
print(a.max())
```
#### 🔹 출력 결과
```
0.9403064643053698
```

```python
import numpy as np
b = np.arange(12).reshape(3,4)
print(b)
```
#### 🔹 출력 결과
```
[[ 0  1  2  3]
 [ 4  5  6  7]
 [ 8  9 10 11]]
```
```python
print(b.sum(axis=0))
```
#### 🔹 출력 결과
```
[12 15 18 21]
```
```python
print(b.sum(axis=1))
```
#### 🔹 출력 결과
```
[ 6 22 38]
```
```python
print(b.min(axis=0))
```
#### 🔹 출력 결과
```
[0 1 2 3]
```
```python
print(b.min(axis=1))
```
#### 🔹 출력 결과
```
[0 4 8]
```
```python
print(b.cumsum(axis=0))
```
#### 🔹 출력 결과
```
[[ 0  1  2  3]
 [ 4  6  8 10]
 [12 15 18 21]]
```
```python
print(b.cumsum(axis=1))
```
#### 🔹 출력 결과
```
[[ 0  1  3  6]
 [ 4  9 15 22]
 [ 8 17 27 38]]
```

```python
import numpy as np

B = np.arange(3)
print(B)
```
#### 🔹 출력 결과
```
[0 1 2]
```
```python
print(np.exp(B))
```
#### 🔹 출력 결과
```
[1.         2.71828183 7.3890561 ]
```

```python
print(np.sqrt(B))
```
#### 🔹 출력 결과
```
[0.         1.         1.41421356]
```
```python
C = np.array([2.0, -1, 4.])
print(np.add(B, C))
```
#### 🔹 출력 결과
```
[2. 0. 6.]
```
---

### 📌  보강 포인드
| 표현 또는 함수        | 수학적 의미 또는 결과         | 설명                                                             |
|------------------------|-------------------------------|------------------------------------------------------------------|
| `d = np.exp(x * 1j)`       | `cos(x) + i·sin(x)`           | 오일러 공식 → 복소수 지수 함수로 회전 표현 가능                   |
| `1j`                   | `i`                           | 복소수 단위 허수 → `j`는 파이썬에서 허수 표현                     |
| `np.angle(d)`          | 복소수의 위상(phase)          | 복소수의 각도 반환 → `atan2(imag, real)`                         |
| `np.abs(d)`            | 복소수의 크기(magnitude)      | 복소수의 절댓값 → `sqrt(real² + imag²)`                          |

---





