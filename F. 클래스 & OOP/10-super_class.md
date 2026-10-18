## 📘 super class
- Python의 super 클래스가 **다중 상속과 MRO(Method Resolution Order)** 에서 어떻게 동작하는지를 아주 명확하게 설명.  
- 아래에 핵심 개념과 동작 원리, 그리고 실전 요약을 정리.

### 📌 super 클래스 이해
#### 🔹 기본 개념
- super는 현재 클래스의 다음 MRO 클래스를 참조하는 객체
- super().method()는 MRO 순서에 따라 부모 클래스의 메서드를 호출
- print(super) → <class 'super'> → super는 실제로 클래스입니다
- isinstance(super, type) → True → super는 타입 객체

### 📌 전체 소스
```python
print(super)
```
#### 🔹 출력 결과 
```
<class 'super'>
```
```python
print(isinstance(super, type))
```
#### 🔹 출력 결과 
```
True
```
```python
class Animal:
    def say(self):
        print('Animal')
        return self._say

class Species:
    def say(self):
        print('Species')
        return self._say

class Dog(Animal, Species):
    def __init__(self, bark):
        self._say = bark
    def say(self):
        return super().say()

class Bird(Species, Animal):
    def __init__(self, sing):
        self._say = sing
    def say(self):
        return super().say()

d = Dog("Bark")

print(d.say())
```
#### 🔹 출력 결과 
```
Animal
Bark
```
```python
s = Bird("sing")
print(s.say())
```
#### 🔹 출력 결과 
```
Species
sing
```
```python
print(super(Dog, d))
```
#### 🔹 출력 결과 
```
<super: <class 'Dog'>, <Dog object>>
```
```python
print(Dog.mro())
```
#### 🔹 출력 결과 
```
[<class '__main__.Dog'>, <class '__main__.Animal'>, <class '__main__.Species'>, <class 'object'>]
```
```python
print(super(Bird, s))
```
- `super(Bird, s)`는 s의 MRO에서 Bird를 찾고, Bird 다음 클래스부터 메서드를 검색하는 super 객체를 반환합니다.
#### 🔹 출력 결과 
```
<super: <class 'Bird'>, <Bird object>>
```
```python
print(Bird.mro())
```
#### 🔹 출력 결과 
```
[<class '__main__.Bird'>, <class '__main__.Species'>, <class '__main__.Animal'>, <class 'object'>]
```
```python
print(Animal.say(d))
```
```
Animal
Bark
```
```python
print(Species.say(d))
```
```
Species
Bark
```

### 📌 예제 분석
#### 🔸 클래스 구조
```python
class Dog(Animal, Species)
class Bird(Species, Animal)
```

- Dog는 Animal → Species 순으로 상속
- Bird는 Species → Animal 순으로 상속
#### 🔸 MRO 확인
```python
Dog.mro()
```
```
[Dog, Animal, Species, object]
```
```python
Bird.mro()
```
```
[Bird, Species, Animal, object]
```

- super().say()는 MRO에서 자신 다음 클래스의 say()를 호출
#### 🔸 동작 결과
```python
d = Dog("Bark")
d.say()
```
```
Animal
Bark
```
```python
s = Bird("sing")
s.say()
```
```
Species
sing
```
- Dog의 super().say() → Animal.say()
- Bird의 super().say() → Species.say()

### 📌 핵심 요약 테이블
| 항목              | 설명                                           | 예시                          |
|-------------------|------------------------------------------------|-------------------------------|
| `super` 클래스     | 현재 클래스의 다음 MRO 클래스 참조              | `super(Dog, d)`               |
| `super().method()` | 부모 클래스의 메서드 호출 (MRO 기반)            | `super().say()`               |
| `mro()`            | 메서드 탐색 순서 리스트                         | `Dog.mro()`                   |
| 다중 상속 순서     | 상속 순서에 따라 `super()` 호출 대상이 달라짐    | `Dog(Animal, Species)` vs `Bird(Species, Animal)` |

### 📌 실전 팁
- super()는 단순히 **부모 클래스** 가 아니라 MRO에서 다음 클래스를 의미함
- 다중 상속 시 super()를 사용할 때는 반드시 mro()를 확인해서 의도한 클래스가 호출되는지 검증
- super()는 생성자뿐 아니라 모든 메서드에서 사용할 수 있음

---

