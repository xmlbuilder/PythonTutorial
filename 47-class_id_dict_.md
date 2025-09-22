# Python id / __class__/__dict__


id, __class__, __dict__, 네임스페이스 탐색, 클래스 변수와 인스턴스 변수의 관계까지 모두 포함해서 객체지향의 본질을 이해하는 데 매우 유익.  
아래에 각 개념을 체계적으로 정리.

## 🧠 객체 식별: id() 함수
- id(obj)는 객체의 고유 메모리 주소를 반환합니다.
- 서로 다른 인스턴스는 같은 속성을 갖더라도 id가 다릅니다.
```python
print(id(car1))  # 예: 4368969472
print(car1 is car2)  # False → 서로 다른 객체
```


## 🧩 클래스 정보: __class__ 속성
- obj.__class__는 해당 인스턴스가 어떤 클래스에서 생성되었는지 알려줍니다.
- 모든 인스턴스는 자신의 클래스에 대한 참조를 갖고 있으며, 이는 동일한 클래스일 경우 id도 같습니다.
```python
print(car1.__class__)  # <class '__main__.Car'>
print(car1.__class__ == car2.__class__)  # True
print(id(car1.__class__))  # 클래스 객체의 고유 ID
```


## 📦 인스턴스 내부 구조: __dict__
- obj.__dict__는 인스턴스의 속성들을 딕셔너리 형태로 보여줍니다.
- 클래스 변수는 포함되지 않으며, 인스턴스 변수만 나옵니다.
```python
print(car1.__dict__)
# {'_company': 'Ferrari', '_detail': {...}}
```


## 🧭 네임스페이스 탐색 원리
Python은 속성이나 메서드를 찾을 때 다음 순서로 탐색합니다:
- 인스턴스 네임스페이스 (obj.__dict__)
- 클래스 네임스페이스 (obj.__class__.__dict__)
- 상속된 부모 클래스 네임스페이스
```python
print(car1.car_count)  # 인스턴스에 없으면 클래스에서 검색
```

### 💡 동일한 이름의 속성을 인스턴스에 만들면 클래스 변수는 가려집니다.


## 🧮 클래스 변수 vs 인스턴스 변수

| 항목             | 클래스 변수                          | 인스턴스 변수                         |
|------------------|--------------------------------------|----------------------------------------|
| 정의 위치        | 클래스 내부에서 직접 정의             | 생성자 내부에서 `self`로 정의          |
| 접근 방식        | `클래스명.변수` 또는 `인스턴스명.변수` | `인스턴스명.변수` (`obj.var`)          |
| 저장 위치        | 클래스 네임스페이스                   | 인스턴스 네임스페이스 (`__dict__`)     |
| 공유 여부        | 모든 인스턴스가 공유                  | 각 인스턴스마다 독립적                 |
| 우선 탐색 순서   | 인스턴스에 없으면 클래스에서 탐색     | 항상 인스턴스에서 먼저 탐색            |

```python
Car.car_count  # 클래스 변수
car1.car_count  # 인스턴스에서 없으면 클래스에서 검색
```


## 🧾 클래스 문서화: __doc__
- 클래스 정의 상단의 문자열은 __doc__ 속성으로 저장됩니다.
- 문서 자동화, IDE 툴팁, help() 함수 등에 활용됩니다.
```python
print(Car.__doc__)
# Car class\nAuthor: THJ\nDate: 2024/12/04
```


## 🧠 메서드 호출 방식
- 인스턴스 메서드는 self를 자동으로 바인딩합니다.
- 클래스에서 직접 호출할 경우 self를 명시적으로 넘겨야 합니다.
```python
car1.detail_info()         # OK
Car.detail_info(car1)      # OK
Car.detail_info()          # ❌ TypeError: missing 'self'
```

## 📘 요약 테이블

| 속성/메서드     | 설명                                 | 사용 예시                  |
|------------------|--------------------------------------|-----------------------------|
| `id(obj)`        | 객체의 고유 메모리 주소 반환          | `id(car1)`                  |
| `__class__`      | 객체가 속한 클래스 정보               | `car1.__class__`            |
| `__dict__`       | 인스턴스의 속성 딕셔너리              | `car1.__dict__`             |
| `__doc__`        | 클래스 문서 문자열                    | `Car.__doc__`               |
| 클래스 변수 탐색 | 인스턴스에 없으면 클래스에서 탐색      | `car1.car_count`            |
| 인스턴스 메서드  | `self`를 명시적으로 넘겨 호출 가능     | `Car.detail_info(car1)`     |


## 참고 소스
```python
class Car:
    """
    Car class
    Author: THJ
    Date: 2024/12/04
    """

    def __init__(self, company, detail):
        self._company = company
        self._detail = detail

    def __str__(self):
        return 'str : {} - {}'.format(self._company, self._detail)

    def __repr__(self):
        return 'repr : {} - {}'.format(self._company, self._detail)

    def detail_info(self):
        print('Current ID : {}'.format(id(self)))

car1 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})
car2 = Car('Bmw', {'color': 'Black', 'horsepower': '270', 'price': 6000})
car3 = Car('Audi', {'color': 'Silver', 'horsepower': '300', 'price': 6000})
car4 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})

# ID 확인
print(id(car1))
print(id(car2))
print(id(car3))
print(id(car4))

'''
4368969472
4368969568
4368969520
4368969616
'''

print(car1._company == car2._company )
'''False'''

print(car1 is car2 ) # 인스턴스 자체를 비교
'''False'''

# dir & __dict__ 확인
print(dir(car1))
print(car1.__dict__)
'''
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_company', '_detail']

{'_company': 'Ferrari', '_detail': {'color': 'Black', 'horsepower': '270', 'price': 5000}}
'''

# Doctoring
print(Car.__doc__)
'''
    Car class
    Author: THJ
    Date: 2024/12/04
'''

car1.detail_info()
'''
4368969472
'''

print(car1.__class__)
'''<class '__main__.Car'>'''

print(car1.__class__ == car2.__class__)
'''True'''

print(id(car1.__class__), id(car2.__class__), id(car3.__class__), id(car4.__class__))
'''5016974896 5016974896 5016974896 5016974896'''


class Car:
    """
    Car class
    Author: THJ
    Date: 2024/12/04
    """
    # 클래스 변수
    car_count = 0

    def __init__(self, company, detail):
        self._company = company
        self._detail = detail
        Car.car_count += 1

    def __str__(self):
        return 'str : {} - {}'.format(self._company, self._detail)

    def __repr__(self):
        return 'repr : {} - {}'.format(self._company, self._detail)

    def detail_info(self):
        print('Current ID : {}'.format(id(self)))

    def __del__(self):
        Car.car_count -= 1


car1 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})
car2 = Car('Bmw', {'color': 'Black', 'horsepower': '270', 'price': 6000})
car3 = Car('Audi', {'color': 'Silver', 'horsepower': '300', 'price': 6000})
car4 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})

# Car.detail_info()
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 28, in <module>
    print(Car.detail_info())
          ^^^^^^^^^^^^^^^^^
TypeError: Car.detail_info() missing 1 required positional argument: 'self'
'''

Car.detail_info(car1)
'''Current ID : 4340658448'''

print(dir(car1))
'''
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', 
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', 
'__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', 
'__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_company', 
'_detail', 'car_count', 'detail_info']
'''

print(car1.car_count)
'''4'''

print(car1.__dict__)
'''
{'_company': 'Ferrari', '_detail': {'color': 'Black', 'horsepower': '270', 'price': 5000}}
'''<img width="987" height="2374" alt="image" src="https://github.com/user-attachments/assets/01d864e2-ff8a-4878-af1d-9bbb599f80ec" />

```

----

## 🧠 1. __slots__: 메모리 최적화
### ✅ 개념
- 인스턴스가 가질 수 있는 속성을 제한하여 메모리 사용을 줄이고 속도 향상.
- __dict__를 제거하고 고정된 속성만 허용.
### ✅ 예시
```python
class Car:
    __slots__ = ['_company', '_detail']

    def __init__(self, company, detail):
        self._company = company
        self._detail = detail
```

### ✅ 장점
- 메모리 절약 (특히 많은 객체 생성 시)
- 속성 오타 방지
#### ⚠️ 단점: 동적으로 속성 추가 불가, 상속 시 주의 필요


## 🧩 2. property: 속성처럼 보이는 메서드
### ✅ 개념
- 메서드를 속성처럼 접근 가능하게 만들어 캡슐화와 유효성 검사에 유용.
### ✅ 예시
```python
class Car:
    def __init__(self, company):
        self._company = company

    @property
    def company(self):
        return self._company

    @company.setter
    def company(self, value):
        if not value:
            raise ValueError("Company name cannot be empty")
        self._company = value

```

### ✅ 장점
- getter/setter를 깔끔하게 구현
- 외부에서는 속성처럼 사용 (car.company = "BMW")

## 🧬 3. dataclass: 자동화된 클래스 생성
### ✅ 개념
- __init__, __repr__, __eq__ 등을 자동 생성해주는 데이터 중심 클래스.
### ✅ 예시
```python
from dataclasses import dataclass

@dataclass
class Car:
    company: str
    color: str
    horsepower: int
    price: int
```

### ✅ 장점
- 코드 간결화
- 비교, 출력, 초기화 자동 처리
💡 frozen=True 옵션으로 불변 객체도 생성 가능


## ⚖️ 4. 객체 비교 메서드들

| 메서드     | 연산자 | 사용 예시         | 설명                               |
|------------|--------|-------------------|------------------------------------|
| `__eq__`   | `==`   | `car1 == car2`     | 두 객체가 같은지 비교               |
| `__ne__`   | `!=`   | `car1 != car2`     | 두 객체가 다른지 비교               |
| `__lt__`   | `<`    | `car1 < car2`      | 왼쪽 객체가 더 작은지 비교          |
| `__le__`   | `<=`   | `car1 <= car2`     | 왼쪽 객체가 작거나 같은지 비교      |
| `__gt__`   | `>`    | `car1 > car2`      | 왼쪽 객체가 더 큰지 비교            |
| `__ge__`   | `>=`   | `car1 >= car2`     | 왼쪽 객체가 크거나 같은지 비교      |

### ✅ 예시
```python
class Car:
    def __init__(self, price):
        self.price = price

    def __eq__(self, other):
        return self.price == other.price

    def __lt__(self, other):
        return self.price < other.price
```

## 📘 요약 테이블

| 기능         | 목적                          | 자동 생성 메서드                  | 사용 예시                     |
|--------------|-------------------------------|-----------------------------------|-------------------------------|
| `__slots__`  | 메모리 최적화, 속성 제한       | 없음                              | `__slots__ = ['a', 'b']`      |
| `property`   | 캡슐화된 속성 접근             | 없음                              | `@property`, `@setter`        |
| `dataclass`  | 데이터 중심 클래스 자동 생성   | `__init__`, `__repr__`, `__eq__` | `@dataclass`                  |
| 비교 메서드  | 객체 간 정렬/비교              | `__eq__`, `__lt__` 등             | `car1 == car2`, `car1 < car2` |

---



