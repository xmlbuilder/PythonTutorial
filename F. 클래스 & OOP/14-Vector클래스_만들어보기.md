## 📘 Vector 클래스 만들기
- Vector 클래스는 Python의 **Magic Method(연산자 오버로딩)** 를 활용해 벡터 연산을 직관적으로 표현한 예제.  
- 아래에 이 클래스의 핵심 기능과 개선 포인트를 정리하고 실제 몇가지를 개선.

### 📌 전체 소스
```python
class Vector(object):
    """
    Class Vector
    """

    def __init__(self, x, y, z):
        """
        Create a vector object.
        :param x:
        :param y:
        :param z:
        """
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y, self.z - other.z)

    def __mul__(self, other):
        return Vector(self.x * other, self.y * other, self.z * other)

    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    def cross(self, other):
        return Vector(self.y * other.z - self.z *other.y,
            self.z * other.x - self.x * other.z,
            self.x * other.y - self.y * other.x)

    def __str__(self):
        return "({0}, {1}, {2})".format(self.x, self.y, self.z)

    def __repr__(self):
        return "Vector({0}, {1}, {2})".format(self.x, self.y, self.z)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.z == other.z

    def __ne__(self, other):
        return self.x != other.x or self.y != other.y or self.z != other.z

    def __lt__(self, other):
        return self.x < other.x or self.y < other.y or self.z < other.z

    def __le__(self, other):
        return self.x <= other.x or self.y <= other.y or self.z <= other.z

    def __gt__(self, other):
        return self.x > other.x or self.y > other.y or self.z > other.z
    
    def __ge__(self, other):
        return self.x >= other.x or self.y >= other.y or self.z >= other.z

print(Vector.__doc__)
```
#### 🔹 출력 내용
```
    Class Vector
```
```python
print(Vector.__init__.__doc__)
```
#### 🔹 출력 내용
```
        Create a vector object.
        :param x:
        :param y:
        :param z:
```
```python
v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)

print(v1 + v2)
```
#### 🔹 출력 내용
```
(5, 7, 9)
```
```python
print(v1 - v2)
```
#### 🔹 출력 내용
```
(-3, -3, -3)
```
```python
print(v1 * 5)
```
#### 🔹 출력 내용
```
(5, 10, 15)
```
```python
v3 = v1.cross(v2)
print(v3.__dict__)
```
#### 🔹 출력 내용
```
{'x': -3, 'y': 6, 'z': -3}
```

### 📌 Vector 클래스 핵심 기능 요약
| 기능       | 메서드               | 설명                                  |
|------------|----------------------|---------------------------------------|
| 생성       | `__init__`           | `x`, `y`, `z` 좌표 초기화             |
| 덧셈       | `__add__`            | 벡터 + 벡터                           |
| 뺄셈       | `__sub__`            | 벡터 - 벡터                           |
| 스칼라 곱  | `__mul__`            | 벡터 × 숫자                           |
| 내적       | `dot()`              | `x1*x2 + y1*y2 + z1*z2`               |
| 외적       | `cross()`            | 3D 벡터 외적                          |
| 출력 표현  | `__str__`, `__repr__`| 사용자 친화적 출력 및 디버깅 표현     |
| 비교 연산  | `__eq__`, `__lt__`, `__gt__` | 좌표 또는 크기 기준 비교         |


### 📌 개선 포인트
#### 🔹 스칼라 곱 vs 벡터 곱 구분
- 현재 `__mul__` 은 스칼라 곱만 처리합니다. 
- 벡터 곱도 지원하려면 isinstance(other, Vector) 체크를 추가:

```python
def __mul__(self, other):
    if isinstance(other, (int, float)):
        return Vector(self.x * other, self.y * other, self.z * other)
    elif isinstance(other, Vector):
        return self.dot(other)  # 또는 cross product
    return NotImplemented
```

#### 🔹 역방향 연산자 지원
```python
def __rmul__(self, other):
    return self.__mul__(other)
```

- 이렇게 하면 5 * v1도 작동합니다.
#### 🔹 max() 지원
- max(v1, v2)를 지원하려면 `__lt__` 또는 `__gt__` 가 있어야 하며, 비교 기준을 명확히 해야 합니다.  
- 예를 들어 벡터 크기(norm) 기준으로 비교하려면:
```python
def norm(self):
    return (self.x**2 + self.y**2 + self.z**2)**0.5

def __lt__(self, other):
    return self.norm() < other.norm()
```

### 📌 실전 예시
```python
v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)

print(v1 + v2)      # (5, 7, 9)
print(v1 * 5)       # (5, 10, 15)
print(v1.dot(v2))   # 32
print(v1.cross(v2)) # Vector(-3, 6, -3)
print(max(v1, v2))  # norm 기준으로 큰 벡터
```

### 📌 Magic Method 적용 요약
| 연산자 | 메서드       | 설명                     |
|--------|--------------|--------------------------|
| `+`    | `__add__`     | 벡터 덧셈                |
| `-`    | `__sub__`     | 벡터 뺄셈                |
| `*`    | `__mul__`     | 스칼라 곱 또는 내적      |
| `==`   | `__eq__`      | 좌표 동일 여부 비교      |
| `<`    | `__lt__`      | norm 또는 좌표 비교       |
| `str()`| `__str__`     | 사용자 친화적 출력        |
| `repr()`| `__repr__`   | 디버깅용 표현             |


---

### 📌 Vector 개선
- 기존 Vector 클래스를 세 가지 방향으로 확장하거나 리팩토링하는 방식입니다.  
- 각각의 목적과 구현 예제를 함께 정리.

### 📌 1. norm() 기반 비교

#### 🔹 목적
- 벡터의 크기(길이)를 기준으로 <, >, == 등의 비교 연산을 수행
#### 🔹 구현
```python
import math

class Vector:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

    def norm(self):
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)

    def __lt__(self, other):
        return self.norm() < other.norm()

    def __eq__(self, other):
        return self.norm() == other.norm()

    def __gt__(self, other):
        return self.norm() > other.norm()
```

#### 🔹 결과
```python
v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)
print(v1 < v2)  # True
```

### 📌 2. __getitem__으로 인덱싱 지원
#### 🔹 목적
- v[0], v[1], v[2]처럼 배열처럼 접근 가능하게 만들기

#### 🔹 구현
```python
class Vector:
    def __init__(self, x, y, z):
        self._coords = [x, y, z]

    def __getitem__(self, index):
        return self._coords[index]

    def __setitem__(self, index, value):
        self._coords[index] = value

    def __str__(self):
        return str(tuple(self._coords))
```

#### 🔹 결과
```python
v = Vector(1, 2, 3)
print(v[0])  # 1
v[2] = 10
print(v)     # (1, 2, 10)
```

### 📌 3. dataclass로 리팩토링
#### 🔹 목적
- 코드 간결화, 자동 생성되는 __init__, __repr__, __eq__ 등 활용
#### 🔹 구현
```python
from dataclasses import dataclass
import math

@dataclass
class Vector:
    x: float
    y: float
    z: float

    def norm(self):
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y, self.z + other.z)

    def __getitem__(self, index):
        return (self.x, self.y, self.z)[index]
```

#### 🔹 결과
```python
v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)
print(v1 + v2)  # Vector(x=5, y=7, z=9)
print(v1[1])    # 2
```


### 📌 요약 테이블
| 확장 방식         | 목적                         | 핵심 메서드         |
|------------------|------------------------------|---------------------|
| norm 기반 비교    | 벡터 크기 기준 비교 연산       | `norm()`, `__lt__`, `__gt__` |
| 인덱싱 지원       | 배열처럼 접근 가능             | `__getitem__`, `__setitem__` |
| dataclass 리팩토링| 코드 간결화, 자동 메서드 생성  | `@dataclass`, `__add__`, `__repr__` |

---





