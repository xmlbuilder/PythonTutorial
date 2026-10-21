## 📘 Method Overriding

### 📌 핵심 개념: Method Overriding
- 부모 클래스의 메소드를 자식 클래스에서 같은 이름으로 재정의하여 다른 동작을 수행하는 것
    - 다형성(polymorphism)의 대표적인 구현 방식
    - 자식 클래스에서 부모 메소드를 확장하거나 변경 가능
    - super()를 통해 부모 메소드 호출 가능

### 📌 메소드 오버라이딩 효과
| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 부모 메소드 호출     | `super()`를 통해 부모 클래스의 기능을 확장하거나 재사용 가능                 |
| 기능 재정의          | 자식 클래스에서 메소드를 새롭게 정의하여 다른 동작 수행 가능                  |
| 구조적 설계          | 공통 인터페이스 기반으로 다양한 구현 가능 → 추상화 설계에 적합                |
| 다형성 구현          | 동일한 메소드 이름으로 다양한 클래스가 각기 다른 동작 수행 가능               |
| 유지보수성 향상      | 부모 클래스 수정 시 자식 클래스에 자동 반영 가능 → 코드 일관성과 효율성 증가     |

### 📌 예제 소스
#### 🔹 기본 Overriding
```python
class ParentEx1:
    def __init__(self):
        self.value = 5
    def get_value(self):
        return self.value

class ChildEx1(ParentEx1):
    pass

parent = ParentEx1()
child = ChildEx1()
child.value = 2

print('value child: ', child.get_value())

print('value parent: ', parent.get_value())

print("Parent", dir(parent))
```
#### 🔹 출력 결과
```
Parent ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__',
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__',
'__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__',
'__str__', '__subclasshook__', '__weakref__', 'get_value', 'value']
```

```python
print("Child", dir(child))
```
#### 🔹 출력 결과
```
Child ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__',
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__',
'__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__',
'__str__', '__subclasshook__', '__weakref__', 'get_value', 'value']
```

```python
print("Parent Dict", ParentEx1.__dict__)
```
#### 🔹 출력 결과
```
Parent Dict {'__module__': '__main__', '__init__': <function ParentEx1.__init__ at 0x100f95bc0>, 'get_vaue':
<function ParentEx1.get_value at 0x10104d940>, '__dict__': <attribute '__dict__' of 'ParentEx1' objects>,
'__weakref__': <attribute '__weakref__' of 'ParentEx1' objects>, '__doc__': None}
```

```python
print("Child Dict", ChildEx1.__dict__)
```
#### 🔹 출력 결과
```
Child Dict {'__module__': '__main__', '__doc__': None}
```

### 📌 기본 Overriding 메소드 재 정의
```python
class ParentEx2:
    def __init__(self):
        self.value = 5
    def get_value(self):
        return self.value

class ChildEx2(ParentEx2):
    def get_value(self):
        return self.value * 10

child2 = ChildEx2()
child2.value = 10
print("child get_value {}".format(child2.get_value()))  # child get_value 100
```

### 📌 Overriding 예제
```python
import datetime
class Logger(object):
    def log(self, msg):
        print(msg)

class TimeStampLogger(Logger):
    def log(self, msg):
        message = "{ts} {msg}".format(ts=datetime.datetime.now(), msg=msg)
        super(TimeStampLogger, self).log(message)
        # super().log(message)

class DateLogger(Logger):
    def log(self, msg):
        message = "{ts} {msg}".format(ts=datetime.datetime.now().strftime("%Y-%m-%d"), msg=msg)
        super(DateLogger, self).log(message)

log1 = TimeStampLogger()
log1.log("Event")  # 2024-11-30 16:21:41.986335 Event

log2 = Logger()
log2.log("Event")  # Event

log3 = DateLogger()
log3.log("Event")  # 2024-11-30 Event
```

### 📌 예제 분석
#### 🔹 기본 상속 (오버라이딩 없이)
```python
class ParentEx1:
    def get_value(self): return self.value

class ChildEx1(ParentEx1):
    pass
```

- ChildEx1는 ParentEx1의 get_value()를 그대로 상속
- child.value = 2 → get_value()는 2 반환

#### 🔹 메소드 재정의 (오버라이딩)
```python
class ChildEx2(ParentEx2):
    def get_value(self): return self.value * 10
```

- 부모의 get_value()를 재정의하여 10배로 반환
- child2.value = 10 → get_value()는 100 반환

#### 🔹 실무 예제: 로깅 시스템
```python
class Logger:
    def log(self, msg): print(msg)

class TimeStampLogger(Logger):
    def log(self, msg):
        message = f"{datetime.datetime.now()} {msg}"
        super().log(message)

class DateLogger(Logger):
    def log(self, msg):
        message = f"{datetime.datetime.now().strftime('%Y-%m-%d')} {msg}"
        super().log(message)
```

- Logger는 기본 출력
- TimeStampLogger는 시간 포함 로그
- DateLogger는 날짜만 포함한 로그
- super().log()를 통해 부모 메소드 호출 후 확장

### 📌 특징 요약 – Method Overriding

| 요소            | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `super()` 호출     | 부모 클래스의 메소드를 호출하여 기존 기능을 확장하거나 재사용 가능             |
| 메소드 재정의       | 자식 클래스에서 동일한 이름의 메소드를 새롭게 정의하여 다른 동작 수행 가능       |
| 다형성 구현         | `log()` 같은 공통 메소드가 클래스마다 다르게 동작 → 인터페이스 일관성 유지        |
| 구조적 설계         | 추상화 기반 설계에 적합. 공통 인터페이스 정의 후 각 클래스에서 구체적 구현 가능   |
| 유지보수성 향상     | 부모 클래스 수정 시 자식 클래스에 자동 반영 가능 → 코드 일관성과 효율성 증가       |

### 📌 실무에서 왜 중요한가?

| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 기능 확장           | `super()`를 통해 기존 기능을 유지하면서 새로운 동작을 추가할 수 있음           |
| 공통 인터페이스 유지 | 동일한 메소드 이름으로 다양한 클래스가 일관된 방식으로 동작 → API 설계에 유리     |
| 유지보수 효율        | 부모 클래스만 수정해도 전체 구조에 반영 가능 → 코드 일관성과 효율성 증가         |
| 다형성 구현          | 다양한 객체가 동일한 메소드로 호출 가능 → 코드 재사용성과 유연성 향상           |
| 구조적 설계          | 추상 클래스 기반 설계 시 필수 → 팀 개발, 프레임워크 설계에 적합                 |
| 테스트 용이성        | 공통 인터페이스 기반으로 단위 테스트 및 확장 테스트가 쉬움                      |

---

### 📌 super(DateLogger, self).log(message) 의미

- super(DateLogger, self).log(message)는 Python에서 부모 클래스의 메소드를 호출하는 방식.  

### 📌 동작 설명
```python
super(DateLogger, self).log(message)
```
- DateLogger는 현재 클래스 이름
- self는 현재 인스턴스 (DateLogger의 객체)
- super(DateLogger, self)는 Logger 클래스(부모 클래스)를 기준으로 self 인스턴스에서 **다음 MRO(Method Resolution Order)** 를 찾아줌
- 즉, Logger.log(message)를 호출하는 것과 같음

### 📌 왜 이렇게 쓰는가?
- 다중 상속이나 복잡한 클래스 계층에서 super()는 정확한 부모 메소드를 찾아줌
- super()는 단순히 부모 클래스 이름을 직접 쓰는 것보다 유연하고 안전함
- Python 3에서는 super().log(message)처럼 더 간단하게 쓸 수 있음

### 📌 예시 비교
```python
class Logger:
    def log(self, msg):
        print("Logger:", msg)

class DateLogger(Logger):
    def log(self, msg):
        message = "DateLog: " + msg
        super(DateLogger, self).log(message)  # 부모 Logger의 log 호출
```

- DateLogger.log()는 메시지를 포맷한 후 Logger.log()를 호출
- 결과적으로 "Logger: DateLog: Event" 같은 출력이 나옴


### 📌 차이점 요약 – super() 사용 방식
| 버전        | 문법                                | 설명                                      | 실무 권장 여부 |
|-------------|-------------------------------------|-------------------------------------------|----------------|
| Python 2.x  | `super(ClassName, self).method()`   | 클래스 이름과 인스턴스를 명시해야 함         | ❌ (Python 3 권장) |
| Python 3.x  | `super().method()`                  | 자동으로 클래스와 인스턴스를 추론함          | ✅ (간결하고 안전함) |

---

