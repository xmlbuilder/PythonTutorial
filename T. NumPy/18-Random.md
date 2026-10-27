## 📘 np.random이란?
- np.random은 **난수 생성기(Random Number Generator)** 를 제공하는 넘파이의 서브패키지.
- 여기서 생성하는 난수는:
    - 균등분포(uniform distribution)
    - 정규분포(normal distribution)
    - 정수 난수(random integers)
    - 배열 형태의 난수
    - 샘플링(random choice)

### 📌 np.random.random()의 의미
- np.random.random(size)
    - 0 이상 1 미만의 실수 난수를 생성한다.
- 즉, 범위는:

$$
0\leq x<1
$$

### 📌 np.random.random((3, 4)) 의 의미
```python
np.random.random((3, 4))
```

- 이건 3×4 크기의 배열을 만들고, 각 요소에 0~1 사이의 난수를 채워 넣는다는 뜻.
- 예시 출력:
```
array([
    [0.1234, 0.9821, 0.5532, 0.1123],
    [0.4421, 0.3312, 0.9981, 0.7712],
    [0.0192, 0.5521, 0.8812, 0.0044]
])
```

- 즉:
    - shape = (3, 4)
    - dtype = float
    - 값의 범위 = 0.0, 1.0)

### 📌 왜 shape를 튜플로 넣는가?
- 넘파이는 배열을 만들 때 항상 shape를 튜플로 표현.
- 예:
    - (3,) → 길이 3의 1차원 배열
    - (3, 4) → 3×4 2차원 배열
    - (2, 3, 4) → 2×3×4 3차원 배열
- 그래서 np.random.random((3, 4))는 **3행 4열짜리 난수 배열을 만들어라** 라는 뜻.

### 📌 np.random의 다른 대표 함수들
#### 🔹 1) 정수 난수
```python
np.random.randint(0, 10, size=(3, 4))
```
- 0~9 사이의 정수 난수 3×4 배열

#### 🔹 2) 정규분포 난수
```python
np.random.randn(3, 4)
```
- 평균 0, 표준편차 1의 정규분포 난수

```python
import numpy as np

# 평균 100, 표준편차 15, 난수 1000개
a = np.random.normal(loc=100, scale=15, size=1000)
print(np.mean(a))  # 약 100
print(np.std(a))   # 약 15
```

#### 🔹 3) 균등분포 범위 지정
```python
np.random.uniform(5, 10, size=(2, 3))
```
- 5~10 사이의 난수

#### 🔹 4) 랜덤 선택
```python
np.random.choice([1, 2, 3, 4], size=5)
```

### 📌 정리
| 코드                          | 설명                                      |
|------------------------------|-------------------------------------------|
| np.random.random()           | 0~1 사이의 난수 1개 생성                  |
| np.random.random(10)         | 길이 10의 1차원 난수 배열 생성            |
| np.random.random((3, 4))     | 3×4 크기의 0~1 난수 배열 생성             |
| np.random.randint(0, 10, (3,4)) | 0~9 정수 난수로 구성된 3×4 배열 생성   |
| np.random.randn(3, 4)        | 평균 0, 표준편차 1의 정규분포 난수 3×4 배열 |

---





