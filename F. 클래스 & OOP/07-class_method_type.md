## 📘 class method
- 메서드 유형 - 인스턴스 메서드, 클래스 메서드, 정적 메서드를 정리.  
- 아래에 각 메서드의 핵심 개념과 차이점, 그리고 실전 요약 테이블까지 정리.

### 📌 메서드 유형 정리
#### 1️⃣ Instance Method (인스턴스 메서드)
- 첫 번째 인자로 self를 받음
- **객체의 상태(속성)** 를 참조하거나 변경할 수 있음
- 객체마다 고유한 동작을 수행
```python
def get_price(self):
    return self._detail.get('price')
```

#### 2️⃣ Class Method (클래스 메서드) - `@classmethod`
- 첫 번째 인자로 cls를 받음
- 클래스 변수를 참조하거나 변경할 수 있음
- 클래스 전체에 영향을 주는 동작
```python
@classmethod
def raise_price(cls, per):
    cls.price_per_raise = max(per, 1.0)
```

#### 3️⃣ Static Method (정적 메서드) - `@staticmethod`
- self나 cls를 받지 않음
- 객체나 클래스 상태와 무관한 독립적인 기능을 수행
- 보통 유틸리티 함수로 사용됨
```python
@staticmethod
def is_bmw(instance):
    return instance._company == 'Bmw'
```

### 📌 메서드 유형 요약 테이블
| 메서드 유형       | 첫 인자 | 접근 대상       | 사용 목적                          | 예시 호출 방식           |
|------------------|--------|----------------|------------------------------------|--------------------------|
| Instance Method  | `self` | 인스턴스 변수   | 객체 고유 동작                     | `car1.get_price()`       |
| Class Method     | `cls`  | 클래스 변수     | 클래스 전체 설정 변경              | `Car.raise_price(1.3)`   |
| Static Method    | 없음   | 없음            | 독립적 기능 (유틸리티)             | `Car.is_bmw(car2)`       |


### 📌 실전 동작 흐름 요약
- car1.get_price() → 인스턴스의 가격 반환
- car1.get_price_cur() → 클래스 변수 price_per_raise 반영된 가격
- Car.raise_price(1.3) → 클래스 변수 변경
- Car.is_bmw(car2) → 특정 조건 판단 (BMW 여부)

### 📌 팁
- `@classmethod`은 팩토리 메서드로도 자주 사용됩니다 (from_dict, from_json 등)
- `@staticmethod`은 클래스 내부에 두되, 외부 의존성이 없는 기능을 캡슐화할 때 유용합니다
- `@property`와 함께 쓰면 속성처럼 보이는 메서드도 만들 수 있음


### 📌 전체 참고 소스
```python
class Car:
    """
    Car class
    Author: THJ
    Date: 2024/12/04
    Description: Class, Static, Instance Method
    """
    price_per_raise = 1.0

    def __init__(self, company, detail):
        self._company = company
        self._detail = detail

    def __str__(self):
        return 'str : {} - {}'.format(self._company, self._detail)

    def __repr__(self):
        return 'repr : {} - {}'.format(self._company, self._detail)

    # Instance Method
    # Self : 객체의 고유한 속성 값을 사용
    def detail_info(self):
        print('Current ID : {}'.format(id(self)))
        print('Car Detail : {} {}'.format(self._company, self._detail.get('price')))

    #Instance Method
    def get_price(self):
        return self._detail.get('price')

    def get_price_cur(self):
        return self._detail.get('price') * Car.price_per_raise

    # Class Method
    @classmethod
    def raise_price(cls, per):
        if per < 1: cls.price_per_raise = 1.0
        else: cls.price_per_raise = per

    # Static Method
    @staticmethod
    def is_bmw(instance):
        if instance._company == 'Bmw':
            return True
        else: return False

car1 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})
car2 = Car('Bmw', {'color': 'Black', 'horsepower': '270', 'price': 6000})
```

```python
car2.detail_info()
```
#### 🔹 출력 결과
```
Current ID : 4359925168
Car Detail : Bmw 6000
```
```python
print(car1.get_price())
print(car2.get_price())
```
#### 🔹 출력 결과
```
5000
6000
```
```python
Car.price_per_raise = 1.4
print(car1.get_price_cur())
print(car2.get_price_cur())
```
#### 🔹 출력 결과
```
7000.0
8400.0
```

```python
Car.raise_price(1.3)
print(car1.get_price_cur())
print(car2.get_price_cur())
```
#### 🔹 출력 결과
```
6500.0
7800.0
```

```python
print(car1.is_bmw(car1))
```
#### 🔹 출력 결과
```
False
```

```python
print(car1.is_bmw(car2))
```
#### 🔹 출력 결과
```
True
```
---
