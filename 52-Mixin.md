# Mixin 클래스

Python에서 Mixin 클래스의 개념과 **다중 상속 + MRO(Method Resolution Order)**의 동작에 대한 설명. 
아래에 mixin 클래스의 정의, 특징, 동작 방식, 실전 팁까지 자세히 정리.

## 🧠 Mixin 클래스란?
### ✅ 정의
- Mixin 클래스는 특정 기능만을 제공하는 보조 클래스입니다.
- 일반적으로 상태(속성) 없이 메서드만 정의되어 있으며, 단독으로 인스턴스화하지 않습니다.
- 주로 다중 상속을 통해 다른 클래스에 기능을 “섞어” 넣는 데 사용됩니다.
### ✅ 목적
- 코드 재사용
- 기능 분리
- 명확한 역할 분담

## 전체 코드
```python
class SayMixin:
    def say(self):
        print('SayMixin 호출')
        return self._say

class BarkMixin:
    def say(self):
        print('BarkMixin')
        return self._say


class Dog(BarkMixin, SayMixin):
    def __init__(self, bark):
        self._say = bark

class Bird(SayMixin, BarkMixin):
    def __init__(self, sing):
        self._say = sing

d = Dog('Bark')
print(d.say())
'''
BarMixin
Bark
'''

s = Bird('Sing')
print(s.say())
'''
SayMixin 호출
Sing
'''

```


### 🔍 예제 분석
```python
class SayMixin:
    def say(self):
        print('SayMixin 호출')
        return self._say

class BarkMixin:
    def say(self):
        print('BarkMixin')
        return self._say
```

- SayMixin, BarkMixin은 각각 say() 메서드만 제공하는 기능 단위 클래스
- Dog(BarkMixin, SayMixin) → BarkMixin의 say()가 먼저 호출됨
- Bird(SayMixin, BarkMixin) → SayMixin의 say()가 먼저 호출됨

#### MRO 확인
```python
Dog.mro()
# [Dog, BarkMixin, SayMixin, object]

Bird.mro()
# [Bird, SayMixin, BarkMixin, object]
```

- super().say() 없이 say() 호출 시, MRO 순서대로 탐색
- 따라서 Dog.say()는 BarkMixin.say()를, Bird.say()는 SayMixin.say()를 호출

## 📘 Mixin 클래스 요약
| 항목           | 설명                                           |
|----------------|------------------------------------------------|
| 정의           | 기능만 제공하는 보조 클래스                     |
| 특징           | 상태 없음, 메서드만 있음, 단독 인스턴스화 안 함 |
| 사용 방식      | 다중 상속으로 기능을 섞어 넣음                  |
| MRO 영향       | 상속 순서에 따라 메서드 탐색 순서가 달라짐       |
| 인터페이스 역할 | 외부에 공개된 메서드 집합으로 기능을 정의함       |



### 💡 실전 팁
- Mixin 클래스는 **단일 책임 원칙(SRP)**을 지키는 데 유용합니다.
- super()를 활용하면 여러 Mixin을 cooperative 방식으로 연결할 수 있습니다.
- Mixin은 기능 단위로 분리하되, 상태를 가지지 않도록 설계하는 것이 좋습니다.
- ABC 추상 클래스와 함께 쓰면 인터페이스 강제도 가능합니다.



### ✅ 이름에 Mixin을 붙이는 이유

| 항목         | 설명                                           |
|--------------|------------------------------------------------|
| 관례         | Python 커뮤니티에서 기능 클래스에 `Mixin`을 붙이는 것이 일반적 |
| 가독성 향상   | 클래스 이름만 보고 역할(보조 기능 제공)을 빠르게 파악 가능     |
| 유지보수 편의 | 협업 시 역할 구분이 쉬워지고 코드 탐색이 간편해짐             |
| 명시적 의도   | "이 클래스는 기능만 제공한다"는 의도를 이름으로 표현           |


### ❌ 꼭 붙여야 하는 건 아님
- Python은 동적이고 유연한 언어이기 때문에 이름에 제약이 없습니다
- Say, Loggable, Serializable 같은 이름도 충분히 Mixin 역할을 할 수 있어요
- 중요한 건 클래스의 역할과 설계, 이름은 의도를 잘 드러내면 충분

### 🧠 실전 예시
```python
class Timestamp:  # 이름에 Mixin 없음
    def now(self):
        return datetime.now()

class LogMixin:   # 이름에 Mixin 있음
    def log(self, msg):
        print(f"[LOG] {msg}")
```

둘 다 Mixin 역할을 하지만, 이름 스타일이 다를 뿐입니다.

## 📘 요약
| 항목               | 설명                                      |
|--------------------|-------------------------------------------|
| `Mixin` 이름 사용   | 관례적이며 가독성 향상에 도움됨             |
| 필수 여부           | 전혀 필수 아님, 역할만 명확하면 자유롭게 가능 |
| 실전 팁             | 기능 중심 클래스는 이름으로 의도를 드러내는 게 좋음 |

결론적으로, 이름에 Mixin을 붙이는 건 선택의 문제이고, 의도를 명확히 드러내는 것이 더 중요합니다. 
---

