## 📘 Magic Method 연산자 오버로딩
- Python의 Magic Method를 활용한 연산자 오버로딩을 설명. 
- 아래에 핵심 개념과 연산자별 대응 메서드, 그리고 실전 요약 테이블까지 정리.

### 📌 Magic Method Operator란?
- Python에서는 `+`, `-`, `*`, `==`, `<` 같은 연산자들이 내부적으로 Magic Method를 호출합니다.
- 클래스에 해당 Magic Method를 정의하면 연산자 오버로딩이 가능해집니다.
- 예제에서는 Fruit 클래스가 가격 기반으로 연산되도록 오버라이딩됨.

### 📌 예제 소스
```python
class Fruit:
    def __init__(self, name, price):
        self._name = name
        self._price = price

    def __str__(self):
        return f'Fruit Class Info {self._name} {self._price}'

    def __add__(self, other):
        return self._price + other._price

    def __sub__(self, other):
        return self._price - other._price

    def __mul__(self, other):
        return self._price * other._price

    def __le__(self, other):
        return self._price <= other._price

    def __ge__(self, other):
        return self._price >= other._price

    def __gt__(self, other):
        return self._price > other._price

    def __eq__(self, other):
        return self._price == other._price

    def __ne__(self, other):
        return self._price != other._price

    def __lt__(self, other):
        return self._price < other._price

s1 = Fruit('Apple', 100)
s2 = Fruit('Banana', 200)

print(s1 + s2)
```

#### 🔹 출력 내용
```
300
```
```python
print(s1 - s2)
```

#### 🔹 출력 내용
```
-100
```
```python
print(s1 * s2)
```
#### 🔹 출력 내용
```
20000
```

```python
print(s1 > s2)
```
#### 🔹 출력 내용
```
False
```
```python
print(s1 >= s2)
```
#### 🔹 출력 내용
```
False
```

```python
print(s1 < s2)
```
#### 🔹 출력 내용
```
True
```
```python
print(s1 <= s2)
```
#### 🔹 출력 내용
```
True
```
```python
print(s1 == s2)
```
#### 🔹 출력 내용
```
False
```


### 📌 예제 동작 요약
```python
s1 = Fruit('Apple', 100)
s2 = Fruit('Banana', 200)

s1 + s2       → s1.__add__(s2)       → 100 + 200 = 300
s1 - s2       → s1.__sub__(s2)       → 100 - 200 = -100
s1 * s2       → s1.__mul__(s2)       → 100 * 200 = 20000
s1 > s2       → s1.__gt__(s2)        → False
s1 <= s2      → s1.__le__(s2)        → True
```

- 모든 연산은 self._price 기준으로 비교 또는 계산됨
- `__str__()` 도 오버라이드되어 `print(s1)` 시 사용자 친화적 출력 가능

### 📌 Magic Method Operator 요약 테이블
| 연산자 | Magic Method     | 역할                         |
|--------|------------------|------------------------------|
| `+`    | `__add__`         | 덧셈                         |
| `-`    | `__sub__`         | 뺄셈                         |
| `*`    | `__mul__`         | 곱셈                         |
| `==`   | `__eq__`          | 같음 비교                    |
| `!=`   | `__ne__`          | 다름 비교                    |
| `<`    | `__lt__`          | 작음 비교                    |
| `<=`   | `__le__`          | 작거나 같음 비교             |
| `>`    | `__gt__`          | 큼 비교                      |
| `>=`   | `__ge__`          | 크거나 같음 비교             |
| `str()`| `__str__`         | 문자열 표현                  |


### 📌 실전 팁
- 연산자 오버로딩 시 타입 체크를 추가하면 더 안전합니다:

```python
def __add__(self, other):
    if isinstance(other, Fruit):
        return self._price + other._price
    return NotImplemented
```

- `__repr__()` 도 함께 정의하면 디버깅에 유용합니다
- `__radd__`, `__rmul__` 같은 역방향 연산자도 필요할 수 있음
- 일반적인 `__add__`, `__mul__` 과 달리 왼쪽 피연산자가 연산을 처리하지 못할 때 오른쪽 객체에서 호출되는 특수 메서드입니다.

```python
class Number:
    def __init__(self, value):
        self.value = value

    def __add__(self, other):
        print("__add__ called")
        if isinstance(other, Number):
            return Number(self.value + other.value)
        return NotImplemented

    def __radd__(self, other):
        print("__radd__ called")
        return Number(other + self.value)


a = Number(10)
b = Number(20)

c = a + b
print(c.value)

d = 5 + a
print(d.value)
```
#### 🔹 출력 내용
```
__add__ called
30
__radd__ called
15
```
---


