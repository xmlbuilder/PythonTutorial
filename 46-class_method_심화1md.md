# 클래스 기반 설계
이 예제는 클래스 기반 설계가 왜 중요한지, 그리고 __str__, __repr__, __dict__ 같은 메서드들이 어떻게 객체를 더 명확하게 표현하고 관리할 수 있게 해 주는지 설명.  
아래에 핵심 개념과 심화 내용을 정리.

## 🧠 클래스 메서드 심화: __str__, __repr__, __dict__
### ✅ 핵심 메서드 설명

| 메서드       | 사용 맥락            | 설명                                                                 |
|--------------|----------------------|----------------------------------------------------------------------|
| `__str__`    | `print()` / `str()`  | 사용자 친화적 문자열 반환. 사람이 읽기 쉬운 형식으로 객체 표현         |
| `__repr__`   | `repr()` / 디버깅     | 개발자 친화적 문자열 반환. 객체를 정확하게 재현할 수 있는 형식으로 표현 |
| `__dict__`   | `self.__dict__`      | 인스턴스의 모든 속성을 딕셔너리 형태로 보여줌                         |

### 💡 __str__()이 우선적으로 호출되며, 없으면 __repr__()이 대신 사용됩니다.
이 테이블은 객체를 출력하거나 디버깅할 때 어떤 메서드가 호출되는지, 그리고 각각의 역할이 무엇인지 명확하게 이해하는 데 도움

### 샘플 코드 (클래스를 써야 하는 이유)
```python

# 변수로 처리 할 경우 - 관리 불편
car_company1 = 'Ferrari'
car_detail_1 = [
    {'color' : 'White'},
    {'horsepower' : '400'},
    {'price', 8000}
]

car_company2 = 'Bmw'
car_detail_2 = [
    {'color' : 'Black'},
    {'horsepower' : '270'},
    {'price': 5000}
]

car_company3 = 'Audi'
car_detail_3 = [
    {'color' : 'Silver'},
    {'horsepower' : '300'},
    {'price': 6000}
]

# 리스트 구조
car_company_list = ['Ferrari', 'Bmw', 'Audi']
car_detail_list = [
    {'color' : 'White', 'horsepower' : '400', 'price': 8000},
    {'color' : 'Black', 'horsepower' : '270', 'price': 5000},
    {'color' : 'Silver', 'horsepower' : '300', 'price': 6000}
]

# 지우는 것도 불편 하다.
del car_company_list[0]
del car_detail_list[0]

print(car_company_list)
print(car_detail_list)
'''
['Bmw', 'Audi']
[{'color': 'Black', 'horsepower': '270', 'price': 5000}, {'color': 'Silver', 'horsepower': '300', 'price': 6000}]
'''

# 딕셔너리 구조
# 코드 반복 지속, 중첩 문제, 키 조회 예외 처리 등
car_dicts = [
    {'car_company' : 'Ferrai', 'car_detail' : {'color': 'Black', 'horsepower': '270', 'price': 5000}},
    {'car_company' : 'Bmw', 'car_detail' : {'color': 'Black', 'horsepower': '270', 'price': 6000}},
    {'car_company' : 'Audi', 'car_detail' : {'color' : 'Silver', 'horsepower' : '300', 'price': 6000}}
]

print(car_dicts)
'''
[{'car_company': 'Ferrai', 'car_detail': {'color': 'Black', 'horsepower': '270', 'price': 5000}}, 
{'car_company': 'Bmw', 'car_detail': {'color': 'Black', 'horsepower': '270', 'price': 6000}}, 
{'car_company': 'Audi', 'car_detail': {'color': 'Silver', 'horsepower': '300', 'price': 6000}}]
'''

del car_dicts[0]
print(car_dicts)
'''
[{'car_company': 'Bmw', 'car_detail': {'color': 'Black', 'horsepower': '270', 'price': 6000}}, 
{'car_company': 'Audi', 'car_detail': {'color': 'Silver', 'horsepower': '300', 'price': 6000}}]
'''

# 클래스 구조
# 구조 설계 후 재 사용성 중가, 코드 반복 최소화, 메소드 활용
class Car:
    def __init__(self, company, detail):
        self._company = company
        self._detail = detail
    def __str__(self):
        return 'str : {} - {}'.format(self._company, self._detail)
    def __repr__(self):
        return 'repr : {} - {}'.format(self._company, self._detail)

car1 = Car('Ferrari', {'color': 'Black', 'horsepower': '270', 'price': 5000})
print(car1.__dict__)
'''
{'_company': 'Ferrari', '_detail': {'color': 'Black', 'horsepower': '270', 'price': 5000}}
'''

print(car1)
'''
str : Ferrari - {'color': 'Black', 'horsepower': '270', 'price': 5000}
'''
'''
__str__ 이 우선이고 없으면 __repr__을 사용한다.
'''

print(car1.__repr__())
'''
repr : Ferrari - {'color': 'Black', 'horsepower': '270', 'price': 5000}
'''
car2 = Car('Bmw', {'color': 'Black', 'horsepower': '270', 'price': 6000})
car3 = Car('Audi', {'color': 'Silver', 'horsepower': '300', 'price': 6000})

print(car2.__dict__)
print(car3.__dict__)
'''
{'_company': 'Bmw', '_detail': {'color': 'Black', 'horsepower': '270', 'price': 6000}}
{'_company': 'Audi', '_detail': {'color': 'Silver', 'horsepower': '300', 'price': 6000}}
'''

# 리스트 선언

car_list = []
car_list.append(car1)
car_list.append(car2)
car_list.append(car3)

print(car_list)
'''
[repr : Ferrari - {'color': 'Black', 'horsepower': '270', 'price': 5000}, 
repr : Bmw - {'color': 'Black', 'horsepower': '270', 'price': 6000}, 
repr : Audi - {'color': 'Silver', 'horsepower': '300', 'price': 6000}]
'''

for x in car_list:
    print(x)
'''
str : Ferrari - {'color': 'Black', 'horsepower': '270', 'price': 5000}
str : Bmw - {'color': 'Black', 'horsepower': '270', 'price': 6000}
str : Audi - {'color': 'Silver', 'horsepower': '300', 'price': 6000}
'''
for x in car_list:
    print(repr(x))
'''
repr : Ferrari - {'color': 'Black', 'horsepower': '270', 'price': 5000}
repr : Bmw - {'color': 'Black', 'horsepower': '270', 'price': 6000}
repr : Audi - {'color': 'Silver', 'horsepower': '300', 'price': 6000}
'''<img width="933" height="2277" alt="image" src="https://github.com/user-attachments/assets/a22582fb-a71c-4b0f-ba9c-aaddff715405" />

```


## ✅ 클래스 기반 설계의 장점
| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 코드 재사용성       | 동일한 구조와 기능을 객체로 반복 생성 가능                            |
| 데이터 중심 관리    | 각 객체가 자신의 데이터를 갖고 있어 구조적 관리가 쉬움                |
| 기능 캡슐화         | 관련 기능을 클래스 내부 메서드로 묶어 유지보수와 확장에 유리             |
| 삭제/추가 용이      | 리스트나 컬렉션으로 객체를 관리하면 삭제, 필터링, 정렬 등이 쉬움         |
| 표현력 향상         | `__str__`, `__repr__`을 통해 객체 출력 시 가독성 향상                   |
| 내부 상태 확인      | `__dict__`를 통해 객체의 속성을 딕셔너리로 확인 가능                    |


## 📘 실전 팁
- __repr__은 리스트 출력, 디버깅, 로깅에 유용
- __str__은 사용자에게 보여줄 때 사용
- __dict__는 객체 내부 상태를 확인하거나 JSON 변환 시 활용
- 클래스 기반 설계는 이후 @classmethod, @staticmethod, property, __eq__, __lt__ 등으로 확장 가능

### 🔧 확장 예시: @classmethod 활용
```python
class Car:
    def __init__(self, company, detail):
        self._company = company
        self._detail = detail

    @classmethod
    def from_dict(cls, info):
        return cls(info['car_company'], info['car_detail'])

car_data = {'car_company': 'Hyundai', 'car_detail': {'color': 'Blue', 'horsepower': '180', 'price': 3000}}
car4 = Car.from_dict(car_data)
print(car4)
```

- from_dict()는 클래스 메서드로, 딕셔너리를 받아 객체 생성
- 팩토리 패턴으로 자주 사용됨

## 🔍 요약 테이블

| 기능            | 설명                                 | 사용 예시                                 |
|-----------------|--------------------------------------|--------------------------------------------|
| `__str__`       | 사용자 친화적 문자열 반환             | `print(obj)` → `"str : ..."`               |
| `__repr__`      | 개발자 친화적 문자열 반환             | `print([obj1, obj2])` → `"repr : ..."`     |
| `__dict__`      | 객체의 속성을 딕셔너리로 반환         | `obj.__dict__` → 내부 상태 확인, JSON 변환 |
| `@classmethod`  | 클래스 자체를 인자로 받아 객체 생성   | `Car.from_dict(data)` → 팩토리 메서드 활용 |

---

