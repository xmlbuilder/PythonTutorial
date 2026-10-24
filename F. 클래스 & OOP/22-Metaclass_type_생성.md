## 📘 Metaclass Type 생성
- Python의 가장 강력한 기능 중 하나인 동적 클래스 생성과 메타클래스 설계. 

### 📌 핵심 개념: type(name, bases, dict) – 클래스 생성자
- Python에서 type()은 단순히 객체의 타입을 확인하는 함수가 아니라, 클래스를 생성하는 메타클래스.

``` type
type('ClassName', (BaseClass,), {'attr': value, 'method': func})
```
- name: 클래스 이름
- bases: 상속할 부모 클래스 튜플
- dict: 클래스의 속성과 메소드 정의

### 📌 동적 클래스 생성 예시
#### 🔹 1. 기본 클래스 생성
```python
s1 = type('SampleA', (), {})
print(type(s1))  # <class 'type'>
print(s1.__base__)  # <class 'object'>
```
- SampleA라는 이름의 클래스를 생성
- 상속 없음 → 기본적으로 object를 상속

#### 🔹 2. 상속 포함 클래스 생성
```python
class Parent1: pass
s2 = type('Sample2', (Parent1,), {'attr1': 100, 'attr2': 'hi'})
```

- Parent1을 상속한 Sample2 클래스 생성
- 속성 attr1, attr2 포함

#### 🔹 3. 메소드 포함 클래스 생성
```python
s4 = type('Sample3', (object,), {
    'attr1': 30,
    'attr2': 100,
    'add': lambda x, y: x + y,
    'mul': lambda x, y: x * y
})
```

- 속성과 메소드를 모두 포함한 클래스 생성
- add, mul은 람다 함수로 정의

### 📌 구조 요약: 동적 클래스 생성

| 구성 요소       | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `type()`         | 클래스 생성자이자 메타클래스. `type(name, bases, dict)` 형식으로 클래스 생성 |
| `__base__`       | 생성된 클래스가 상속한 부모 클래스. 기본값은 `object`                    |
| `__dict__`       | 클래스의 속성과 메소드가 저장된 네임스페이스 딕셔너리                     |
| `__class__`      | 클래스의 타입 정보. 대부분 `type`으로 설정됨                             |


### 📌 메타클래스 설계의 장점

| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 동적 클래스 생성      | `type(name, bases, dict)`으로 런타임에 클래스 생성 가능 → 유연한 구조 설계에 적합     |
| 구조 검증 및 제어     | 클래스 정의 시점에 속성, 메소드, 네이밍 규칙 등을 강제 가능 → 실수 방지 및 안정성 확보   |
| 커스텀 메타클래스 생성 | `type`을 상속하여 클래스 생성 로직을 직접 제어 가능 → 프레임워크 설계에 핵심 역할       |
| 코드 일관성 유지      | 클래스 생성 로직을 중앙에서 통제 가능 → 전체 시스템의 구조적 일관성 확보               |
| 고급 기능 주입        | 클래스 정의 시 자동으로 속성 추가, 데코레이터 삽입 등 고급 기능 구현 가능               |


### 📌 실무에서 왜 중요한가?
| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 런타임 유연성 확보    | 실행 중에도 새로운 클래스 정의 가능 → 동적 시스템 설계에 적합                    |
| 유지보수 효율        | 클래스 생성 로직을 중앙에서 제어 가능 → 전체 구조 일관성 유지                    |
| 고급 기능 주입        | 클래스 정의 시 자동으로 속성 추가, 데코레이터 삽입 등 고급 기능 구현 가능         |
| 구조적 안정성        | 클래스 생성 시점에 규칙을 강제함으로써 실수 방지 및 안정성 확보                   |


### 📌 Type 생성 샘플 예제

#### 🔹 1. type 동적 클래스 생성 예제
- Name(이름), Bases(상속), Dct(속성)
```python
s1 = type('SampleA', (), {})
print('s1', s1)  # s1 <class '__main__.SampleA'>

print('s1 type', type(s1))  # s1 type <class 'type'>

print('s1.__base__', s1.__base__)  # s1.__base__ <class 'object'>

print('s1.__dict__', s1.__dict__)
```
#### 🔹 출력 결과
```
s1.__dict__ {'__module__': '__main__', '__dict__': <attribute '__dict__' of 'SampleA' objects>, '__weakref__':
<attribute '__weakref__' of 'SampleA' objects>, '__doc__': None}
```

#### 🔹 2. 동적 생성 + 상속
```python
class Parent1:
    pass

s2 = type('Sample2', (Parent1,), dict(attr1=100, attr2='hi'))

print(s2)  # <class '__main__.Sample2'>

s3 = type('Sample2', (Parent1,), {'attr1': 100, 'attr2': 'hi'})

print('s3', s3)  # <class '__main__.Sample2'>

print('s3 type', type(s3))  # s3 type <class 'type'>

print('s3 base', s3.__base__)  # s3 base <class '__main__.Parent1'>

print('s3 dict', s3.__dict__)  # s3 dict {'attr1': 100, 'attr2': 'hi', '__module__': '__main__', '__doc__': None}

print('s3 attr', s3.attr1, s3.attr2)  # s3 attr 100 hi
```

#### 🔹 3. type 동적 클래스 생성 + 메소드
```python
class SampleEx:
    attr1 = 30
    attr2 = 100
    def add(self, m, n):
        return m + n
    def mul(self, m, n):
        return m * n

ex = SampleEx()

print('attr1', ex.attr1)  # attr1 30

print('att2', ex.attr2)  # att2 100

print('100+200', ex.add(100, 200))  # 100+200 300

print('10*20', ex.mul(10, 20))  # 10*20 200

s4 = type('Sample3', (object,), dict(attr1=30, attr2=100, add=lambda x, y: x + y, mul=lambda x, y: x * y))

print('attr1', s4.attr1)  # attr1 30

print('att2', s4.attr2)  # att2 100

print('100+200', s4.add(100, 200))  # 100+200 300

print('10*20', s4.mul(10, 20))  # 10*20 200
```
```python
print(dir(s4))
```
#### 🔹 출력 결과
``` 
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', 
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', 
'__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', 
'__str__', '__subclasshook__', '__weakref__', 'add', 'attr1', 'attr2', 'mul'] 
```
---

