# Meta Class (Custom Class)
type()을 통한 동적 클래스 생성부터 type을 상속한 커스텀 메타클래스 설계.


## 핵심 개념: 메타클래스 상속과 동적 클래스 생성
type(name, bases, dict)
- name: 클래스 이름
- bases: 상속할 부모 클래스 튜플
- dict: 속성과 메소드 정의

## 🔍 구조 요약: 메타클래스 상속의 목적
| 구성 요소       | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `type`           | 모든 클래스의 기본 메타클래스. 커스텀 메타클래스는 이를 상속하여 생성됨             |
| `metaclass`      | 클래스 정의 시 어떤 메타클래스를 사용할지 지정하는 키워드                         |
| `__new__`        | 클래스 생성 직전 호출됨. 속성 추가, 메소드 삽입, 구조 검증 등 커스터마이징 가능       |
| `__init__`       | 클래스 생성 직후 호출됨. 초기화 작업 수행. 구조 수정은 불가능                     |
| `__call__`       | 클래스 인스턴스 생성 시 호출됨. 인스턴스 생성 로직을 제어할 수 있음                 |


## 🔧 예제 1: type()으로 동적 클래스 생성 (상속 X)
```python
CustomList1 = type('CustomList1', (list,), {
    'desc': 'Custom List1',
    'cus_mul': cus_mul,
    'cus_replace': cus_replace
})
```

- list를 상속한 새로운 클래스 생성
- cus_mul, cus_replace 메소드 추가
- 인스턴스 생성 후 커스텀 기능 사용 가능

## 🔧 예제 2: 커스텀 메타클래스 생성 (상속 O)
```python
class CustomListMeta(type):
    def __new__(cls, name, bases, namespace):
        namespace['desc'] = 'Custom List2'
        namespace['cus_mul'] = cus_mul
        namespace['cus_replace'] = cus_replace
        return super().__new__(cls, name, bases, namespace)

    def __init__(self, name, bases, namespace):
        super().__init__(name, bases, namespace)

    def __call__(self, *args, **kwargs):
        return super().__call__(*args, **kwargs)
```

- `__new__` : 클래스 생성 시 속성과 메소드 삽입
- `__init__` : 클래스 초기화
- `__call__` : 인스턴스 생성 시 동작 제어

```python
CustomList2 = CustomListMeta('CustomList2', (list,), {})
c2 = CustomList2([1, 2, 3, ...])
```

- CustomList2는 CustomListMeta에 의해 생성된 클래스
- 인스턴스 생성 시 __call__이 실행됨
- desc, cus_mul, cus_replace 자동 삽입됨

### ✅ 실무에서 왜 중요한가?

| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 클래스 구조 검증      | 클래스 정의 시 필수 메소드, 속성 존재 여부를 검사하여 실수 방지 가능               |
| 프레임워크 설계 기반   | Django, SQLAlchemy 등에서 모델 클래스 자동 처리 및 구조 강제에 활용됨             |
| 동적 클래스 생성      | `type()`이나 커스텀 메타클래스를 통해 런타임에 클래스 생성 가능 → 유연한 설계 가능   |
| 코드 일관성 유지      | 클래스 생성 로직을 중앙에서 통제 가능 → 전체 시스템의 구조적 일관성 확보               |
| 고급 기능 주입        | 클래스 정의 시 자동으로 속성 추가, 데코레이터 삽입 등 고급 기능 구현 가능             |
| 유지보수 효율        | 구조 검증과 기능 주입을 통해 코드 변경 시 전체 시스템에 일관되게 반영 가능             |


## 🔍 MRO 확인
```python
print(CustomList2.__mro__)
```
```
(<class '__main__.CustomList2'>, <class 'list'>, <class 'object'>)
```
- 클래스의 상속 순서를 보여줌
- 메소드 탐색 순서 확인에 유용
- type()은 클래스 생성자이자 메타클래스이며, 이를 상속한 커스텀 메타클래스를 통해 클래스 생성 로직을 완전히 제어할 수 있음. 
- 실무에서는 구조 검증, 자동 속성 삽입, 프레임워크 설계에 핵심 도구로 활용.


## Custom class 생성 예제
### 1. 커스텀 메타 클래스 생성 예제 (Type 상속 X)
```python
def cus_mul(self, d):
    for i in range(len(self)):
        self[i] = self[i] * d

def cus_replace(self, old, new):
    while old in self:
        self[self.index(old)] = new

CustomList1 = type('CustomList1',
                   (list,),
                   {'desc': 'Custom List1',
                    'cus_mul': cus_mul,
                    'cus_replace': cus_replace}
                   )

c1 = CustomList1([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
c1.cus_mul(100)
print(c1)
```
```
[100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
```
```python
c1.cus_replace(200, 120)
print(c1)
```
```
[120, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
```
```python
print(c1.desc)  # Custom List1
```

### 2. 커스텀 메타클래스 생성 예제 (Type 상속 O)

```python
# class MetaClassName(type):
#     def __new__(cls, name, bases, namespace):

class CustomListMeta(type):
    # 생성된 인스턴스 초기화
    def __init__(self, object_or_name, bases, dict):
        print('__init__ -> ', self, object_or_name, bases, dict)
        super().__init__(object_or_name, bases, dict)

    # 인스턴스 실행
    def __call__(self, *args, **kwargs):
        print('__call__ -> ', self,  *args, **kwargs)
        return super().__call__( *args, **kwargs)

    # 클래스 인스턴스 생성(메모리 초기화)
    def __new__(cls, name, bases, namespace):
        print('__new__ -> ', cls, name, bases, namespace)
        namespace['desc'] = 'Custom List2'
        namespace['cus_mul'] = cus_mul
        namespace['cus_replace'] = cus_replace
        return type.__new__(cls, name, bases, namespace)

CustomList2 = CustomListMeta('CustomList2', (list,), {})
```
```
__new__ ->  <class '__main__.CustomListMeta'> CustomList2 (<class 'list'>,) {}
__init__ ->  <class '__main__.CustomList2'> CustomList2 (<class 'list'>,) {'desc': 'Custom List2', 'cus_mul':
<function cus_mul at 0x100c7e340>, 'cus_replace': <function cus_replace at 0x100ccdbc0>}
__call__ ->  <class '__main__.CustomList2'> [1,2, 3, 4, 5, 6, 7, 8, 9, 10]
```
```python
c2 = CustomList2([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
c2.cus_mul(100)
print(c2)
```
```
[100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
```
```python
c2.cus_replace(200, 120)
print(c2)
```
```
[100, 120, 300, 400, 500, 600, 700, 800, 900, 1000]
```
```python
print(c2.desc)  # Custom List1
print(CustomList2.__mro__)  # (<class '__main__.CustomList2'>, <class 'list'>, <class 'object'>)
```

---
# metaclass & _prepare_

## 🔧 1. metaclass 키워드를 활용한 클래스 정의 방식
- Python에서는 클래스 정의 시 metaclass 키워드를 사용해 어떤 메타클래스를 적용할지 지정할 수 있음.

### ✅ 기본 구조
```python
class MyMeta(type):
    def __new__(cls, name, bases, namespace):
        # 클래스 생성 전 커스터마이징
        return super().__new__(cls, name, bases, namespace)

class MyClass(metaclass=MyMeta):
    pass
```

- MyMeta는 type을 상속한 메타클래스
- MyClass는 MyMeta에 의해 생성됨
- 클래스 생성 시점에 `__new__`, `__init__`, `__call__` 등을 통해 구조 제어 가능

## 🧠 2. `__prepare__` 를 통한 네임스페이스 제어
`__prepare__` 는 클래스 정의 시 사용되는 네임스페이스 딕셔너리를 커스터마이징할 수 있는 메타클래스의 특별한 메소드.

### ✅ 목적
- 클래스 정의 시점에 속성 순서 유지
- 속성 자동 삽입
- 속성 이름 필터링 또는 변형
### ✅ 기본 구조
```python
class OrderedMeta(type):
    @classmethod
    def __prepare__(metacls, name, bases):
        print(f'Preparing namespace for {name}')
        return dict()  # 또는 collections.OrderedDict()

    def __new__(cls, name, bases, namespace):
        print(f'Creating class {name} with namespace: {namespace}')
        return super().__new__(cls, name, bases, namespace)

class MyClass(metaclass=OrderedMeta):
    x = 1
    y = 2
```

- `__prepare__` 는 클래스 정의 시작 전에 호출됨
- 반환된 딕셔너리가 클래스 정의에 사용됨
- OrderedDict를 반환하면 속성 정의 순서를 유지할 수 있음

### 🔍 구조 요약: metaclass와 `__prepare__`
| 구성 요소       | 역할 및 설명                                                                 |
|------------------|------------------------------------------------------------------------------|
| `metaclass`      | 클래스 정의 시 어떤 메타클래스를 사용할지 지정하는 키워드                         |
| `__prepare__`     | 클래스 정의 시작 전에 네임스페이스 딕셔너리를 반환함 → 속성 순서 제어, 자동 삽입 가능     |
| `__new__`        | 클래스 생성 직전에 호출됨 → 속성 추가, 구조 검증, 클래스 수정 가능                   |
| `__init__`       | 클래스 생성 직후 호출됨 → 초기화 작업 수행, 로깅 등 가능                             |
| `__call__`       | 클래스 인스턴스 생성 시 호출됨 → 인스턴스 생성 로직 제어, 인자 검사 등 가능             |


### ✅ 실무 활용 예시
| 활용 방식                  | 설명                                                                 |
|----------------------------|----------------------------------------------------------------------|
| `__prepare__` + `OrderedDict` | 속성 정의 순서 유지 → 자동 문서화, API 명세 생성, 코드 생성기 등에 활용 가능     |
| `__prepare__` + `__new__`     | 속성 자동 삽입 및 네이밍 규칙 검사 → 클래스 정의 시점에 구조 검증 및 기능 주입 가능 |
| `__new__` + 로깅/등록 시스템   | 클래스 생성 시 자동 등록, 로깅 수행 → 플러그인 시스템, ORM 모델 관리에 활용         |
| `__call__` + 인스턴스 생성 제어| 인스턴스 생성 시 인자 검사, 초기화 로직 삽입 → 팩토리 패턴, 유효성 검증에 활용       |
| `metaclass` + DSL 설계        | 도메인 특화 언어(DSL)에서 사용자 정의 문법을 클래스 수준에서 구현 가능              |


metaclass 키워드는 클래스 생성의 제어권을 넘겨주는 도구, 
__prepare__는 클래스 정의의 시작점을 커스터마이징할 수 있는 고급 기능. 
이 둘을 활용하면 Python 클래스 설계를 정적 언어 수준의 구조적 안정성으로 끌어올릴 수 있음.


## 🧪 샘플 1: __prepare__ + OrderedDict → 속성 순서 유지
```python
from collections import OrderedDict

class OrderedMeta(type):
    @classmethod
    def __prepare__(metacls, name, bases):
        print(f'__prepare__ → {name}')
        return OrderedDict()

    def __new__(cls, name, bases, namespace):
        print(f'__new__ → {name}')
        print('속성 순서:', list(namespace.keys()))
        return super().__new__(cls, name, bases, namespace)

class MyClass(metaclass=OrderedMeta):
    a = 1
    b = 2
    c = 3
```

### ✅ 출력 결과
```
__prepare__ → MyClass
__new__ → MyClass
속성 순서: ['a', 'b', 'c']
```


## 🧪 샘플 2: __prepare__ + __new__ → 속성 자동 삽입
```python
class AutoMeta(type):
    @classmethod
    def __prepare__(metacls, name, bases):
        return {}

    def __new__(cls, name, bases, namespace):
        namespace['created_by'] = 'AutoMeta'
        namespace['version'] = 1.0
        return super().__new__(cls, name, bases, namespace)

class AutoClass(metaclass=AutoMeta):
    pass

print(AutoClass.created_by)  # AutoMeta
print(AutoClass.version)     # 1.0
```

### ✅ 출력 결과
```
AutoMeta
1.0
```


### 🧪 샘플 3: __call__ → 인스턴스 생성 제어
```python
class LoggingMeta(type):
    def __call__(cls, *args, **kwargs):
        print(f'Creating instance of {cls.__name__} with args={args}, kwargs={kwargs}')
        return super().__call__(*args, **kwargs)

class User(metaclass=LoggingMeta):
    def __init__(self, name):
        self.name = name

u = User('JungHwan')
print(u.name)
```


### ✅ 출력 결과
```
Creating instance of User with args=('JungHwan',), kwargs={}
JungHwan
```


## 🧪 샘플 4: 속성 네이밍 규칙 검사
```python
class NamingMeta(type):
    def __new__(cls, name, bases, namespace):
        for key in namespace:
            if not key.startswith('_') and not key.islower():
                raise ValueError(f'속성 "{key}"은 소문자로 시작해야 합니다.')
        return super().__new__(cls, name, bases, namespace)

class ValidClass(metaclass=NamingMeta):
    valid_name = 1
    _private = 2

print(ValidClass.valid_name)
```

### ✅ 출력 결과
```
1
```

## InvalidClass
```python
class InvalidClass(metaclass=NamingMeta):
    InvalidName = 3  # 대문자로 시작 → 예외 발생
```

### ❌ 출력 결과
```
ValueError: 속성 "InvalidName"은 소문자로 시작해야 합니다.
```
- 이런 샘플들은 실무에서 프레임워크 설계, 코드 자동화, 구조 검증, 인스턴스 생성 제어 등에 매우 유용



