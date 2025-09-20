# 클래스

클래스 정의와 관련된 핵심 개념들을 아래에 깔끔하게 정리. 
예제 코드도 함께 분석해서 실무적으로 이해할 수 있도록 구성.


## 🧱 클래스 정의 핵심 요약

| 개념              | 설명                                                   |
|-------------------|--------------------------------------------------------|
| 클래스(Class)     | 객체를 생성하기 위한 설계도. 속성과 메서드를 정의함     |
| 인스턴스(Instance)| 클래스를 기반으로 생성된 실제 객체                     |
| self              | 인스턴스 자신을 가리키는 예약어                        |
| __dict__          | 인스턴스의 네임스페이스(속성 저장 공간)                |
| 클래스 변수       | 클래스 전체에서 공유되는 변수                          |
| 인스턴스 변수     | 각 객체마다 별도로 존재하는 변수                       |


## 🐶 예제 분석: Dog 클래스
```python
class Dog:
    species = 'firstdog'  # 클래스 변수

    def __init__(self, name, age):  # 생성자
        self.name = name            # 인스턴스 변수
        self.age = age              # 인스턴스 변수
```

## ✅ 클래스 정보 확인
```python
print(Dog)         # <class '__main__.Dog'>
print(dir(Dog))    # 클래스의 속성과 메서드 목록
'''['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', 
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', 
'__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', 
'__subclasshook__', '__weakref__', 'species'] 
'''
```

## ✅ 인스턴스 생성
```python
a = Dog("mikky", 2)
b = Dog("baby", 3)
c = Dog("mikky", 2)
```

- a, b, c는 모두 Dog 클래스의 인스턴스
- a == c는 False → 기본적으로 객체 비교는 주소(id) 기준
## ✅ 네임스페이스 확인
```python
print(a.__dict__)  # {'name': 'mikky', 'age': 2}
print(b.__dict__)  # {'name': 'baby', 'age': 3}
```

- __dict__는 인스턴스 변수 저장 공간

## 🧠 클래스 변수 vs 인스턴스 변수
```python
print(Dog.species)  # firstdog
print(a.species)    # firstdog
print(b.species)    # firstdog
```

- species는 클래스 변수 → 모든 인스턴스가 공유
- name, age는 인스턴스 변수 → 각 객체마다 다름

## 🧪 실무 확장 예제: 클래스 변수로 인스턴스 수 추적
```python
class Dog:
    count = 0  # 클래스 변수

    def __init__(self, name):
        self.name = name
        Dog.count += 1

print(Dog.count)  # 0
d1 = Dog("A")
d2 = Dog("B")
print(Dog.count)  # 2
```


## 🔚 마무리 요약
| 항목             | 설명                                      |
|------------------|-------------------------------------------|
| 클래스 정의       | `class ClassName:`으로 정의                |
| 인스턴스 생성     | `obj = ClassName()`으로 객체 생성           |
| 클래스 변수       | 클래스 전체에서 공유 (`ClassName.var`)      |
| 인스턴스 변수     | 객체마다 별도 존재 (`self.var`)             |
| 네임스페이스      | `__dict__`로 확인 가능                      |

---



