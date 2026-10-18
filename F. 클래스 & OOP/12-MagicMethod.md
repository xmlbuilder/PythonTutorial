## 📘 Magic Method

- Python의 핵심 기능 중 하나인 **Magic Method (Special Method)** 의 개념과 동작에 대한 설명. 
- 아래에 개념, 동작 원리, 주요 메서드, 실전 팁까지 깔끔하게 정리.

### 📌 Magic Method란?
#### 🔹 정의
- Python 클래스 내부에 `__이름__` 형태로 정의된 내장 특수 메서드
- 객체의 기본 동작을 오버라이드하거나 확장할 수 있음
- Python의 시퀀스, 반복, 함수, 클래스 동작의 핵심


#### 🔹 전체 코드
```python
print(int)
```
#### 🔹 출력 내용
```
<class 'int'>
```
```python
print(float)
```
#### 🔹 출력 내용
```
<class 'float'>
```
```python
print(dir(int))
```
#### 🔹 출력 내용
```
['__abs__', '__add__', '__and__', '__bool__', '__ceil__', '__class__', '__delattr__', '__dir__', '__divmod__',
'__doc__', '__eq__', '__float__', '__floor__', '__floordiv__', '__format__', '__ge__', '__getattribute__',
'__getnewargs__', '__getstate__', '__gt__', '__hash__', '__index__', '__init__', '__init_subclass__',
'__int__', '__invert__', '__le__', '__lshift__', '__lt__', '__mod__', '__mul__', '__ne__', '__neg__',
'__new__', '__or__', '__pos__', '__pow__', '__radd__', '__rand__', '__rdivmod__', '__reduce__',
'__reduce_ex__', '__repr__', '__rfloordiv__', '__rlshift__', '__rmod__', '__rmul__', '__ror__', '__round__',
'__rpow__', '__rrshift__', '__rshift__', '__rsub__', '__rtruediv__', '__rxor__', '__setattr__', '__sizeof__',
'__str__', '__sub__', '__subclasshook__', '__truediv__', '__trunc__', '__xor__', 'as_integer_ratio', 'bit_count',
'bit_length', 'conjugate', 'denominator', 'from_bytes', 'imag', 'is_integer', 'numerator', 'real', 'to_bytes']
```

```python
print(dir(float))
```
#### 🔹 출력 내용
```
['__abs__', '__add__', '__bool__', '__ceil__', '__class__', '__delattr__', '__dir__', '__divmod__', '__doc__', '__eq__',
'__float__', '__floor__', '__floordiv__', '__format__', '__ge__', '__getattribute__', '__getformat__', '__getnewargs__',
'__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__int__', '__le__', '__lt__', '__mod__', '__mul__',
'__ne__', '__neg__', '__new__', '__pos__', '__pow__', '__radd__', '__rdivmod__', '__reduce__', '__reduce_ex__', '__repr__',
'__rfloordiv__', '__rmod__', '__rmul__', '__round__', '__rpow__', '__rsub__', '__rtruediv__', '__setattr__', '__sizeof__',
'__str__', '__sub__', '__subclasshook__', '__truediv__', '__trunc__', 'as_integer_ratio', 'conjugate', 'fromhex', 'hex',
'imag', 'is_integer', 'real']
```
```python
n = 10
print(type(n))
```
#### 🔹 출력 내용
```
<class 'int'>
```
```python
print(n + 100)
```
#### 🔹 출력 내용
```
110
```
```python
a = n.__add__(100)
print(a)
```
#### 🔹 출력 내용
```
110
```
```python
print(n.__doc__)
```
#### 🔹 출력 내용
```
 … 
```
```python
print(n.__bool__(), bool(n))
```
#### 🔹 출력 내용
```
True True
```
```python
print(n * 100, n.__mul__(100))
```
#### 🔹 출력 내용
```
1000 1000
```

#### 🔹 예제 분석
```python
n = 10
print(n + 100)           # 110
print(n.__add__(100))    # 110
```

- n + 100은 내부적으로 n.__add__(100)을 호출
- 즉, + 연산자는 __add__() 메서드에 의해 정의됨

```python
print(n * 100, n.__mul__(100))  # 1000 1000
print(n.__bool__(), bool(n))    # True True
```

- `*` → `__mul__()`
- bool() → `__bool__()`

### 📌 Magic Method 요약 테이블
| 메서드         | 역할                         | 예시 표현         |
|----------------|------------------------------|-------------------|
| `__add__`       | 덧셈 연산자 `+`               | `a + b`           |
| `__mul__`       | 곱셈 연산자 `*`               | `a * b`           |
| `__bool__`      | `bool()` 호출 시               | `bool(a)`         |
| `__str__`       | `str()` 또는 `print()` 출력    | `str(a)`          |
| `__repr__`      | 객체 표현                     | `repr(a)`         |
| `__eq__`        | 비교 연산자 `==`              | `a == b`          |
| `__getitem__`   | 인덱싱 `[]`                   | `a[i]`            |
| `__iter__`      | 반복자                        | `for x in a`      |
| `__call__`      | 함수처럼 호출 가능             | `a()`             |
| `__len__`       | 길이 반환                     | `len(a)`          |



### 📌 Magic Method 핵심 카테고리
| 기능 영역     | 관련 Magic Method 예시                         |
|---------------|-------------------------------------------------|
| 시퀀스        | `__getitem__`, `__setitem__`, `__len__`         |
| 반복자        | `__iter__`, `__next__`                          |
| 함수 호출     | `__call__`                                      |
| 클래스 생성/소멸 | `__init__`, `__new__`, `__del__`, `__class__`   |
| 연산/비교     | `__eq__`, `__lt__`, `__add__`, `__mul__`        |
| 출력 표현     | `__str__`, `__repr__`                           |



### 📌 실전 팁
- Magic Method는 직접 호출하지 않고, Python이 자동으로 호출합니다
- 커스텀 클래스를 만들 때 `__str__`, `__repr__`, `__eq__` 등을 오버라이드하면 디버깅과 출력이 훨씬 편리
- dir(type) 또는 dir(int)처럼 내장 타입을 탐색하면 어떤 Magic Method가 구현되어 있는지 확인 가능


---

