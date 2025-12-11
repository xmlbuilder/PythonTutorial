# 🧠 Descriptor란?
- 클래스의 속성 접근을 제어할 수 있는 객체. `__get__`, `__set__`, `__delete__` 메소드를 구현하면 descriptor로 동작함.

## ✅ 핵심 특징
- 속성 접근 시 자동으로 메소드 호출 (get, set, del)
- 속성 값을 다른 객체에 위임 가능
- 읽기 전용, 유효성 검사, 로깅 등 다양한 기능 구현 가능

## 🔍 Descriptor 종류

| 종류               | 구현 메소드                        | 특징 및 동작 설명                                      |
|--------------------|------------------------------------|--------------------------------------------------------|
| Data Descriptor    | `__get__`, `__set__` 또는 `__delete__` | 인스턴스 속성보다 우선함 → 읽기/쓰기/삭제 모두 제어 가능         |
| Non-Data Descriptor| `__get__`만 구현됨                   | 인스턴스 속성이 있으면 그 값을 우선 사용 → 읽기 전용 속성 구현 가능 |


## 🔧 기본 예제: `__get__`, `__set__`, `__delete__`
```python
class DescriptorEx1:
    def __init__(self, name='Default'):
        self.name = name

    def __get__(self, obj, objType):
        return f'Get method called → name: {self.name}'

    def __set__(self, obj, name):
        print('Set method called.')
        if isinstance(name, str):
            self.name = name
        else:
            raise TypeError('Name must be a string.')

    def __delete__(self, obj):
        print('Delete method called.')
        self.name = None

class Sample:
    name = DescriptorEx1()

s1 = Sample()
s1.name = "Descriptor Text1"  # Set method called.
print(s1.name)                # Get method called → name: Descriptor Text1
del s1.name                   # Delete method called.
```

## 🔧 고급 예제: property()로 Descriptor 구현
```python
class DescriptorEx2:
    def __init__(self, value):
        self._name = value

    def getValue(self):
        return f'Get method called → value: {self._name}'

    def setValue(self, value):
        print('Set method called.')
        if isinstance(value, str):
            self._name = value
        else:
            raise TypeError('Name must be a string.')

    def delValue(self):
        print('Delete method called.')
        self._name = None

    name = property(getValue, setValue, delValue, 'Property Method Example')
```

- property()는 고수준 descriptor
- get, set, del, doc을 지정 가능

### 🔍 Descriptor vs Property

| 항목               | Descriptor (저수준)                          | Property (고수준)                           | self 접근 방식            |
|--------------------|----------------------------------------------|---------------------------------------------|---------------------------|
| 정의 방식           | `__get__`, `__set__`, `__delete__` 메소드 구현 | `property(fget, fset, fdel, doc)` 함수 사용 | property는 인스턴스 내부에서만 self 접근 |
| 재사용 가능성       | ✅ 여러 클래스에서 공유 가능                   | ❌ 클래스 내부에 고정됨                      | descriptor는 외부에서 self 접근 가능     |
| 제어 범위           | 속성 접근, 수정, 삭제 모두 세밀하게 제어 가능     | 간단한 속성 접근/수정 제어에 적합             | self는 descriptor 인스턴스에 직접 연결됨 |
| 실무 활용           | ORM, 로깅, 유효성 검사, 속성 추적 등 고급 제어     | 간단한 읽기/쓰기 속성에 적합                   | self는 descriptor 객체의 상태를 반영함   |



## 🧪 실무 예제 1: 디렉토리 파일 개수
```python
class DirectoryFileCount:
    def __get__(self, obj, objType=None):
        import os
        print(os.listdir(obj.dirname))
        return len(os.listdir(obj.dirname))

class DirectoryPath:
    size = DirectoryFileCount()
    def __init__(self, dirname):
        self.dirname = dirname

s = DirectoryPath('./')
print(s.size)  # 디렉토리 내 파일 개수 출력
```


## 🧪 실무 예제 2: 로깅 기능
```python
import logging
logging.basicConfig(format='%(asctime)s %(message)s', level=logging.INFO)

class LoggedScoreAccess:
    def __init__(self, value=50):
        self.value = value

    def __get__(self, obj, objType=None):
        logging.info(f'Access Score: {self.value}')
        return self.value

    def __set__(self, obj, value):
        self.value = value
        logging.info(f'Update Score: {self.value}')

class Student:
    score = LoggedScoreAccess()
    def __init__(self, name):
        self.name = name
```

- score 접근 시 로그 출력
- 실무에서 감사 로그, 변경 추적에 유용

## 🧪 실무 예제 3: 유효성 검사 (양수만 허용)
```python
class PositiveNumber:
    def __init__(self, value):
        self.value = value

    def __get__(self, instance, owner):
        return self.value

    def __set__(self, instance, value):
        if value < 0:
            raise ValueError("양수만 입력 가능합니다.")
        self.value = value

class Rectangle:
    width = PositiveNumber(0)
    height = PositiveNumber(0)

    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height
```

- width, height에 음수 입력 시 예외 발생
- 실무에서 데이터 유효성 검사에 매우 유용


##  ✅ Descriptor의 실무 장점 요약

| 활용 요소        | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `get/set/del`    | 속성 접근 시 자동으로 메소드 호출 → 읽기, 쓰기, 삭제 동작을 세밀하게 제어 가능       |
| 유효성 검사       | `__set__`에서 타입 체크, 범위 제한 등 → 안전한 데이터 입력 보장                     |
| 읽기 전용 속성     | `__get__`만 구현하면 읽기 전용 속성 생성 가능 → 불변 속성 설계에 유용               |
| 로깅 및 추적      | 접근/변경 시 로그 출력 가능 → 감사, 디버깅, 변경 이력 관리에 활용 가능               |
| 재사용 가능 구조   | 여러 클래스에서 동일한 descriptor 인스턴스를 공유 가능 → 코드 중복 제거             |
| 프레임워크 설계 기반 | ORM, 설정 시스템, API 모델 등에서 핵심 구조로 활용됨 → 속성 제어와 자동화에 최적화     |


## 실제 테스트 예제
```python
import os

class DirectoryFileCount:
    def __get__(self, obj, objType=None):
        print(os.listdir(obj.dirname))
        return len(os.listdir(obj.dirname))

class DirectoryPath:
    # Descriptor instance
    size = DirectoryFileCount()

    def __init__(self, dirname):
        self.dirname = dirname

s = DirectoryPath('./')

print(s.size)
```
```
['random_test.py', 'solution1.py', 'instance.py', 'list_str.py', 'test4.txt', 'list_str1.txt', 'array_test2.py',
'class_test.py', 'test3.txt', 'sort.py', 'string_test.py', '__pycache__', 'character1.py', 'sub', 'reverse_text1.py',
'variable_scope.py', 'self_test.py', 'PersonInfo.py', 'module_test.py', 'print.py', 'numpy_args.py', 'mymodule.py',
'max_test.py', 'str_list.py', 'module.py', 'array_test.py', 'list_str.txt', 'characte2.py', 'algorithm_sum.py', 'main.py',
'resource', 'numpy_tuple.py', 'min_in_list.py', 'sound', 'class_var1.py', 'test.obj', 'class_var.py', 'reverse_text.py', '.idea']
39
```
```python
g = DirectoryPath('../')
print(g.size)
```
```
['Sample2', 'Sample3', '.DS_Store', 'Tutorial2', 'pythonProject', 'OpenCVTest', 'CompVis1', '.ipynb_checkpoints', 'Turoial1']
9
```
```python
import logging

logging.basicConfig(
    format='%(asctime)s %(message)s',
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S'
)

class LoggedScoreAccess:
    def __init__(self, value=50):
        self.value = value

    def __get__(self, obj, objType=None):
        logging.info(f'Access Score Access: {self.value}')
        return self.value

    def __set__(self, obj, value):
        self.value = value
        logging.info(f'Update Score Access: {self.value}')

class Student:
    #Descriptor instance
    score = LoggedScoreAccess()

    def __init__(self, name):
        #self.score = LoggedScoreAccess()
        # Regular instance attribute
        self.name = name

s1 = Student('Kim')
s2 = Student('Lee')

print(s1.score)
s1.score = 20
print(s2.score)
s2.score = 100
print(s1.score)
print(vars(s1))
print(vars(s2))
```
```
50
20
100
{'name': 'Kim'}
{'name': 'Lee'}
2024-12-06 22:41:08 Access Score Access: 50
2024-12-06 22:41:08 Update Score Access: 20
2024-12-06 22:41:08 Access Score Access: 20
2024-12-06 22:41:08 Update Score Access: 100
2024-12-06 22:41:08 Access Score Access: 100
```
```python
class PositiveNumber:
    def __init__(self, value):
        self.value = value
    def __get__(self, instance, owner):
        return self.value
    def __set__(self, instance, value):
        if value < 0:
            raise ValueError("양수만 입력 가능합니다.")
        self.value = value

class Rectangle:
    width = PositiveNumber(0)
    height = PositiveNumber(0)

    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height

rect1 = Rectangle(10, 20)
rect2 = Rectangle(100, 200)
rect1.width = 20

print(rect1.width)
```
```
20
```
```python
print(rect2.width)
```
```
20
```

---


