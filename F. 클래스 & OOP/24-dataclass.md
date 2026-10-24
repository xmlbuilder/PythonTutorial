## 📘 dataclass
## 📌 기본 개념: @dataclass
- dataclass는 Python에서 자동으로 생성자, 비교, 출력 메소드 등을 생성해주는 데코레이터.   
- 반복적인 코드를 줄이고, 선언형 스타일로 클래스 정의가 가능.  

```python
from dataclasses import dataclass

@dataclass
class Person:
    name: str
    age: int
```

### 📌 자동 생성되는 메소드들
- `__init__`: 생성자
- `__repr__`: 객체 출력 형식
- `__eq__`: 객체 비교
- `__hash__`: 해시 가능 여부 (기본은 None)
- `__lt__`, `__le__`, `__gt__`, `__ge__`: order=True일 때 생성됨

#### 🔹 출력 확인
```python
print(Person.__dict__)
print(Person.__dict__['__init__'])
```

#### 🔹 출력 예시
```
init=True, repr=True, hash=None, compare=True
<function Person.__init__ at 0x000001AB72FFA0C0>
```


#### 🔹 인스턴스 생성 및 접근
```python
p = Person('jhjeong', 22)
print(p.name)  # jhjeong
print(p.age)   # 22
```

### 📌 frozen=True → 불변 객체
```python
@dataclass(init=True, repr=True, eq=False, order=False, frozen=True)
class People:
    name: str
    age: int

pe = People('jhjeong', 22)
pe.sex = "Male"  # ❌ 오류 발생
```

#### 🔹 출력 결과
```
Traceback (most recent call last):
  ...
dataclasses.FrozenInstanceError: cannot assign to field 'sex'
```
- frozen=True이면 인스턴스 속성 변경이 불가능
- 실무에서 불변 객체, 해시 가능 객체, 보안성 강화에 유용

### 📌 주요 옵션 요약 – dataclass

| 옵션       | 동작 및 결과 설명                                      |
|------------|--------------------------------------------------------|
| `init`     | `__init__` 자동 생성 → 인스턴스 생성 시 필드 초기화 가능 (`True`) |
| `repr`     | `__repr__` 자동 생성 → 객체 출력 시 보기 좋은 문자열 반환 (`True`) |
| `eq`       | `__eq__` 자동 생성 → 객체 비교 가능 (`True`)                  |
| `order`    | `<`, `>`, `<=`, `>=` 비교 연산자 생성 (`False`면 생성 안 됨)     |
| `frozen`   | 속성 변경 불가 → `FrozenInstanceError` 발생 (`False`면 변경 가능) |

- 이 표는 @dataclass가 단순한 문법 설정보다 훨씬 더 강력한 자동화된 클래스 생성 도구라는 걸 보여줌  

### 📌 실무에서 왜 중요한가?
- 데이터 모델링: DTO, 설정 객체, API 응답 구조 등에서 자주 사용
- 불변 객체 설계: frozen=True로 안전한 상태 유지
- 자동 비교/정렬: eq, order로 객체 간 정렬 및 비교 가능
- 코드 간결화: 반복적인 생성자, 출력, 비교 코드 제거

### 📌 field
- dataclasses.field()를 활용한 고급 설정을 정리.    
- 기본값 설정, default_factory, metadata는 실무에서 매우 유용한 기능들.  

### 📌 field()란?
- field()는 @dataclass에서 각 필드의 동작을 세밀하게 제어할 수 있는 함수.  
- 기본값, 초기화 여부, 비교 여부, 메타데이터 등을 설정할 수 있음.  

```python
from dataclasses import dataclass, field
```


#### 🔹 1. 기본값 설정 – default
```python
@dataclass
class User:
    name: str
    age: int = field(default=20)

u = User('JungHwan')
print(u.age)  # 20
```

- age 필드에 기본값 20이 설정됨
- 생성자에서 생략 가능

#### 🔹 2. 동적 기본값 – default_factory

```python
from typing import List

@dataclass
class Group:
    members: List[str] = field(default_factory=list)

g = Group()
g.members.append('JungHwan')
print(g.members)  # ['JungHwan']
```

- default_factory는 함수를 호출해서 기본값을 생성함
- 리스트, 딕셔너리, set 등 mutable 객체에 필수적으로 사용해야 안전함

#### 🔹 3. 메타데이터 설정 – metadata
```python
@dataclass
class Product:
    name: str = field(metadata={'label': '상품명'})
    price: int = field(metadata={'unit': 'KRW'})

p = Product('Keyboard', 50000)
print(p.__dataclass_fields__['name'].metadata)   # {'label': '상품명'}
print(p.__dataclass_fields__['price'].metadata)  # {'unit': 'KRW'}
```

- metadata는 필드에 부가 정보를 담을 수 있는 딕셔너리
- 문서화, 유효성 검사, UI 라벨링 등에 활용 가능

### 📌 field() 주요 옵션 요약

| 옵션              | 동작 및 설명                                                                 |
|-------------------|------------------------------------------------------------------------------|
| `default`         | 기본값 지정. 생성자에서 생략 가능 → `field(default=값)`                         |
| `default_factory` | 함수 기반 기본값 생성 → `list`, `dict` 등 mutable 객체에 안전하게 사용 가능       |
| `init`            | 생성자에서 초기화할지 여부 → `False`면 생성자 인자에서 제외됨                     |
| `repr`            | `__repr__`에 포함할지 여부 → `True`면 출력에 포함됨                              |
| `compare`         | `__eq__`, `__lt__` 등 비교 연산에 포함할지 여부 → 정렬, 비교에 영향 줌              |
| `metadata`        | 필드에 부가 정보 삽입 → 문서화, UI 라벨링, 유효성 검사 등에 활용 가능               |


### 📌 실무에서 왜 중요한가?

| 활용 목적           | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| `default_factory`    | `list`, `dict` 같은 mutable 객체에 안전한 기본값 설정 → 공유 버그 방지           |
| `metadata`           | 필드에 의미 부여 → 문서화, UI 라벨링, 유효성 검사 등에 활용 가능                  |
| `init=False`         | 생성자에서 제외할 내부 속성 정의 가능 → 보안성 강화, 내부 상태 관리에 유용         |
| `compare`, `repr`    | 비교 및 출력 대상 필드 제어 가능 → 민감 정보 제외, 정렬 기준 설정 등 실무 요구 반영     |

#### 🔹 1. init=False로 생성자에서 제외

```python
from dataclasses import dataclass, field

@dataclass
class Config:
    name: str
    secret: str = field(default='hidden', init=False)

c = Config('JungHwan')
print(c.name)    # JungHwan
print(c.secret)  # hidden
```
#### 🔹 2. repr=False로 출력에서 제외

```python
from dataclasses import dataclass, field

@dataclass
class SecureUser:
    username: str
    password: str = field(repr=False)

su = SecureUser('jhjeong', '1234')
print(su)  # SecureUser(username='jhjeong')
```


#### 🔹 3. compare=False로 비교 제외
```python
from dataclasses import dataclass, field

@dataclass
class Item:
    id: int
    temp: int = field(compare=False)

i1 = Item(1, 100)
i2 = Item(1, 200)
print(i1 == i2)  # True → temp는 비교에서 제외됨
```
---








