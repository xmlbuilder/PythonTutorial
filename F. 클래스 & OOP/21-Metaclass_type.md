# Metaclass Type

## 🧠 핵심 개념: Metaclass란?
클래스를 만드는 클래스
즉, 클래스가 객체라면 그 클래스를 생성하는 "설계자"가 바로 메타 클래스야.

- 객체 → 클래스 → 메타 클래스
- type은 기본 메타 클래스
- 커스텀 메타 클래스를 만들면 클래스 생성 과정을 제어할 수 있음

## 🔍 구조 이해: Class of Class
| 대상           | 클래스 정보 (`__class__`)         |
|----------------|------------------------------------|
| `obj1`         | `SampleA`                          |
| `SampleA`      | `type`                             |
| `type`         | `type` (자기 자신을 생성하는 메타 클래스) |

```python
obj = SampleA()
print(type(obj))               # <class '__main__.SampleA'>
print(type(SampleA))           # <class 'type'>
print(type(type))              # <class 'type'>
```

### 🧠 해석
- obj1은 SampleA 클래스의 인스턴스
- SampleA는 type이라는 메타 클래스에 의해 생성됨
- type 자체도 type에 의해 생성됨 → 자기 자신을 생성하는 특별한 객체


### ✅ 실무적 의미
- Python의 모든 클래스는 type에 의해 만들어짐
- type을 커스터마이징하면 클래스 생성 로직을 제어할 수 있음
- 이 구조 덕분에 동적 클래스 생성, 메타 클래스 기반 검증, 프레임워크 설계가 가능해짐

### 📌 메타 클래스의 역할
| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 클래스 생성 제어      | `__new__`, `__init__`을 통해 클래스 정의 시점에 속성, 메소드, 구조를 커스터마이징 가능 |
| 구조 검증 및 강제     | 클래스에 필수 메소드 존재 여부, 네이밍 규칙 등 검증 로직 삽입 가능                 |
| 동적 클래스 생성      | `type()`을 사용해 런타임에 클래스 생성 가능 → 플러그인, DSL, ORM 등에 활용         |
| 프레임워크 설계 기반   | Django, SQLAlchemy 등에서 모델 클래스 자동 처리 및 검증에 사용됨                  |
| 엄격한 설계 요구 대응  | 추상 메소드 강제, 상속 구조 통제 등 → 구조적이고 안정적인 코드 설계 가능             |



## 🔧 기본 예제: type()으로 클래스 생성
```python
MyClass = type('MyClass', (object,), {'x': 5, 'show': lambda self: print(self.x)})
obj = MyClass()
obj.show()  # 5
```

- type(name, bases, dict) 형식으로 클래스 생성
- 동적으로 클래스 정의 가능

## 🛠 커스텀 메타 클래스 예제
```python
class MetaCheck(type):
    def __new__(cls, name, bases, dct):
        if 'process' not in dct:
            raise TypeError("Must define 'process' method")
        return super().__new__(cls, name, bases, dct)

class ValidClass(metaclass=MetaCheck):
    def process(self): pass  # OK

class InvalidClass(metaclass=MetaCheck):
    pass  # TypeError 발생
```

- 클래스 정의 시 process 메소드가 없으면 예외 발생
- 클래스 생성 시점에 구조를 검증하는 방식

## ✅ 실무에서 왜 중요한가?

| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 클래스 구조 검증      | 클래스 정의 시 필수 메소드, 속성 존재 여부를 검사하여 실수 방지 가능               |
| 프레임워크 설계 기반   | Django, SQLAlchemy 등에서 모델 클래스 자동 처리 및 구조 강제에 활용됨             |
| 동적 클래스 생성      | `type()`이나 커스텀 메타 클래스를 통해 런타임에 클래스 생성 가능 → 유연한 설계 가능   |
| 코드 일관성 확보      | 클래스 생성 시점에 규칙을 강제함으로써 전체 시스템의 구조적 안정성 확보              |
| 고급 기능 주입        | 클래스 정의 시 자동으로 속성 추가, 데코레이터 삽입 등 고급 기능 구현 가능             |
| 유지보수 효율        | 클래스 생성 로직을 중앙에서 제어 가능 → 변경 시 전체 구조에 일관되게 반영 가능         |

## 🔍 관련 개념 요약

| 개념               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `type()`           | 클래스 생성 함수이자 기본 메타 클래스. `type(obj)`는 객체의 클래스 반환         |
| `__class__`        | 객체가 속한 클래스 정보. 예: `obj.__class__`                          |
| `__class__.__class__` | 클래스의 메타 클래스 정보. 대부분 `type`으로 설정됨                     |
| `isinstance()`     | 객체가 특정 클래스 또는 타입의 인스턴스인지 확인. 예: `isinstance(obj, Sample)` |
| `issubclass()`     | 클래스가 특정 클래스의 서브클래스인지 확인. 예: `issubclass(Sample, object)`   |


메타 클래스는 클래스를 설계하고 제어하는 고급 도구. 프레임워크나 라이브러리 설계, 구조적 검증, 동적 생성 등에서 핵심 역할을 함. 

## Type 사용법 샘플
```python
# type 예제
class SampleA:  # Class == Object
    def aaa(self):
        pass
    def bbb(self):
        pass

obj1 = SampleA()  # 변수에 할당, 복사 가능, 새로운 속성, 함수의 인자로 넘기기 가능
print(type(obj1))  # <class '__main__.SampleA'>

obj2 = SampleA()
print(type(obj2))  # <class '__main__.SampleA'>

print("obj class - ", obj1.__class__)  # obj class -  <class '__main__.SampleA'>

# SampleA 클래스는 누가 만들었는가 (Type)
print("obj class class", obj1.__class__.__class__)  # obj class class <class 'type'>

# Type 을 조작하면 동적으로 함수를 만들어 낼 수 있다.
print("", obj1.__class__ is type(obj1))  # True

print("", obj1.__class__.__class__ is type(obj1).__class__)  # True

print(type.__class__)  # <class 'type'>

# obj1 -> SampleA instance
# SampleA -> type meta class
# type -> type meta class

# int, dict

n = 10
d = {
    'a': 10,
    'b': 20
}

class SampleB():
    pass
obj2 = SampleB()

for o in (n, d, obj2):
    print('type info {} {} {}'.format(type(o), type(o) is o.__class__, o.__class__.__class__))
# type info <class 'int'> True <class 'type'>
# type info <class 'dict'> True <class 'type'>
# type info <class '__main__.SampleB'> True <class 'type'>

for t in int, float, list, tuple:
    print('type info {} {} {}'.format(type(t), type(t) is t.__class__, t.__class__.__class__))
# type info <class 'type'> True <class 'type'>
# type info <class 'type'> True <class 'type'>
# type info <class 'type'> True <class 'type'>
# type info <class 'type'> True <class 'type'>

class SampleA(object):
    pass

print(issubclass(SampleA, object))
'''True'''

print(issubclass(SampleA, type))
'''False'''

print(isinstance(SampleA, object))
'''True'''

print(isinstance(SampleA, type))
'''True'''

print(issubclass(type, object))
'''True'''

#print(dir(SampleA))

print(isinstance(object, type))
'''True'''

print(isinstance(int, type))
'''True'''

print(isinstance(dict, type))
'''True'''

class Sample:
    def __init__(self):
        pass

s = Sample()
print(s)
'''<__main__.Sample object at 0x0000025EACB9EE50>'''

print(type(s))
'''<class '__main__.Sample'>'''

print(id(s))
'''2605648047696'''

print(hex(id(s)))
'''0x25eacb9ee50'''

import types

print(type(Sample.__init__) == types.FunctionType)
'''True'''

print(type(s.__init__) == types.MethodType)
'''True'''

```

---

# __new__ vs __init__의 차이
Python에서 클래스 생성의 핵심인 __new__ vs __init__의 차이와, 추상 클래스 설계에 사용되는 ABCMeta 기반 구조를 깔끔하게 정리.

## 🔍 __new__ vs __init__ 차이

| 항목             | `__new__`                         | `__init__`                        |
|------------------|------------------------------------|-----------------------------------|
| 호출 시점         | 객체 생성 직전                     | 객체 생성 직후                    |
| 첫 번째 인자       | `cls` (클래스 자체)                | `self` (생성된 인스턴스)           |
| 반환값           | 인스턴스를 반환해야 함              | 반환값 없음 (`None`)              |
| 목적             | 인스턴스 생성 제어                 | 인스턴스 초기화                   |
| 사용 용도         | 메타 클래스, 싱글톤, 불변 객체 등 고급 제어 | 일반적인 속성 초기화               |
| 기본 구현         | `type.__new__`                     | `object.__init__`                 |

## 예시
```python
class Sample:
    def __new__(cls):
        print("Creating instance")
        return super().__new__(cls)

    def __init__(self):
        print("Initializing instance")
```
s = Sample()
# 출력:
# Creating instance
# Initializing instance

## 🧠 ABCMeta 기반 추상 클래스
추상 클래스는 공통 인터페이스를 정의하고, 서브클래스에서 반드시 구현해야 할 메소드를 지정하는 데 사용.

## 🔧 구조
```python
from abc import ABC, ABCMeta, abstractmethod

class BaseProcessor(ABC):  # ABCMeta가 메타클래스로 설정됨
    @abstractmethod
    def process(self, data):
        pass
```

- ABC는 ABCMeta를 메타클래스로 갖는 추상 클래스의 기본 베이스
- @abstractmethod를 붙이면 서브클래스에서 반드시 구현해야 함
- 구현하지 않으면 TypeError 발생


## ✅ 실무에서 왜 중요한가?

| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 클래스 구조 검증      | 클래스 정의 시 필수 메소드, 속성 존재 여부를 검사하여 실수 방지 가능               |
| 프레임워크 설계 기반   | Django, SQLAlchemy 등에서 모델 클래스 자동 처리 및 구조 강제에 활용됨             |
| 동적 클래스 생성      | `type()`이나 커스텀 메타 클래스를 통해 런타임에 클래스 생성 가능 → 유연한 설계 가능   |
| 코드 일관성 확보      | 클래스 생성 시점에 규칙을 강제함으로써 전체 시스템의 구조적 안정성 확보              |
| 고급 기능 주입        | 클래스 정의 시 자동으로 속성 추가, 데코레이터 삽입 등 고급 기능 구현 가능             |

### 🔍 관련 개념 요약 – 추상 클래스와 ABCMeta

| 개념               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `ABCMeta`          | 추상 클래스의 메타 클래스. `@abstractmethod`를 인식하고 구현 여부를 검사함       |
| `ABC`              | `ABCMeta`를 메타 클래스로 갖는 추상 클래스의 기본 베이스 클래스                 |
| `@abstractmethod`  | 서브클래스에서 반드시 구현해야 하는 메소드 지정. 미구현 시 인스턴스화 불가         |
| `TypeError`        | 추상 메소드를 구현하지 않은 클래스의 인스턴스를 생성하려고 할 때 발생하는 예외     |

__new__는 객체 생성을 제어하고, __init__은 초기화를 담당하며, ABCMeta는 클래스 구조를 강제하는 설계 도구. 

---
