## 📘 Underscore를 이용한 Getter / Setter

### 📌 Python에서 언더스코어(_)의 의미
#### 🔹 1. 값 무시용 (_)
```python
x, _, y = (1, 2, 3)  # 중간 값 무시
for _ in range(10):  # 반복 횟수만 중요할 때
```
- 불필요한 값 무시할 때 사용
- 관례적으로 `_` 는 **이 값은 안 쓸 거야** 라는 의미

#### 🔹 2. 네이밍 패턴 (_name, __name)
| 패턴       | 접근 수준     | 의미 및 용도                                  | 실무 권장 사항                          |
|------------|----------------|-----------------------------------------------|------------------------------------------|
| `name`     | Public          | 누구나 접근 가능. 외부에서 자유롭게 사용 가능       | 외부 접근 허용. API, 속성 등 공개용에 적합     |
| `_name`    | Protected (비공식) | 내부용으로 사용. 외부 접근은 가능하지만 자제 권장     | 내부 구현용. 외부에서 직접 접근은 피하는 게 좋음 |
| `__name`   | Private (Name Mangling) | 클래스 내부 전용. `_ClassName__name`으로 변경됨 | 외부 접근 방지 목적. 캡슐화가 필요한 경우 사용   |

```python
class Sample:
    def __init__(self):
        self.x = 0          # public
        self._z = 1         # protected
        self.__y = 2        # private
```

- Python은 접근 제한을 강제하지 않음
- `__y` 는 내부적으로 `_ClassName__y` 로 변경됨 (Name Mangling)
- 외부에서 접근은 가능하지만 하지 않는 것이 원칙

#### 🔹 3. 네이밍 충돌 방지 / 국제화
```python
def _(): pass  # 인터프리터 내부용 또는 특별한 의미
```
- `_` 는 REPL에서 마지막 결과를 저장하는 변수로도 사용됨
- 국제화(i18n) 라이브러리에서 `_()` 는 번역 함수로 쓰이기도 함

### 📌 실무에서 underscore가 중요한 이유

| 패턴                      | 의미 및 용도                                                                 |
|---------------------------|------------------------------------------------------------------------------|
| `_`                       | 값 무시, 반복 변수, 번역 함수 등 불필요한 값 처리용 (`x, _, y`, `for _ in range(n)`) |
| `__`                      | 클래스 내부 전용(private). Name Mangling 발생 (`__y` → `_ClassName__y`)         |
| `_name`                   | 내부용(protected). 외부 접근은 가능하지만 자제하는 것이 규약                     |
| `__name`                  | private 변수. 외부 접근 방지 목적, 내부에서만 사용                              |
| `_ClassName__name`       | Name Mangling 결과. 외부에서 강제로 접근할 때 사용 가능 (`a._SampleA__y`)         |

### 📌 Getter / Setter로 접근 제어
```python
class SampleB:
    def __init__(self):
        self.__y = 0
    def get_y(self):
        return self.__y
    def set_x(self, value):
        self.__y = value
```
- 직접 접근 대신 메서드를 통해 제어
- 변수의 유효성 검사, 로깅, 트리거 처리 등을 추가할 수 있음

### 📌 요약 정리 
- Python 언더스코어 네이밍 패턴
  
| 패턴             | 접근 수준       | 실무 활용 예시                                |
|------------------|------------------|-----------------------------------------------|
| `_`              | 무시용 / 내부용   | `x, _, y`, `for _ in range(n)` – 값 무시, 반복 변수 |
| `_name`          | Protected (비공식) | 내부용 변수/메서드 – 외부 접근은 가능하지만 자제 권장 |
| `__name`         | Private (Name Mangling) | 클래스 내부 전용 – 외부 접근 방지 목적             |
| `_Class__name`   | Name Mangling 결과 | 외부에서 강제로 접근할 때 사용 (`obj._Class__name`) |

### 📌 예제 2: 로깅 및 변경 추적
```python
class Config:
    def __init__(self):
        self.__mode = "default"

    def get_mode(self):
        return self.__mode

    def set_mode(self, value):
        print(f"Mode changed from {self.__mode} to {value}")
        self.__mode = value
```
- 설정 변경 시 로그 출력
- 실시간 모니터링, 디버깅에 유용

### 📌 예제 3: 상태 동기화
```python
class TemperatureSensor:
    def __init__(self):
        self.__celsius = 0
        self.__fahrenheit = 32

    def get_celsius(self):
        return self.__celsius

    def set_celsius(self, value):
        self.__celsius = value
        self.__fahrenheit = (value * 9/5) + 32

    def get_fahrenheit(self):
        return self.__fahrenheit
```

- 섭씨 값을 설정하면 자동으로 화씨 값도 동기화
- 내부 상태 간의 일관성 유지

### 📌 예제 4: 외부 API 연동 시 값 검증
```python
class Payment:
    def __init__(self):
        self.__amount = 0

    def get_amount(self):
        return self.__amount

    def set_amount(self, value):
        if not isinstance(value, (int, float)):
            raise TypeError("Amount must be a number")
        if value <= 0:
            raise ValueError("Amount must be positive")
        self.__amount = value
```
- 외부에서 들어오는 값에 대해 타입과 범위 검증
- API 연동 시 데이터 안정성 확보

### 📌 예제 5: 트리거 처리 (자동 동작)
```python
class Alarm:
    def __init__(self):
        self.__status = "off"

    def get_status(self):
        return self.__status

    def set_status(self, value):
        self.__status = value
        if value == "on":
            self.activate_alarm()

    def activate_alarm(self):
        print("Alarm activated!")
```

- 상태 변경 시 자동으로 특정 동작 수행
- 이벤트 기반 시스템에 유용

### 📌 실무에서 Getter/Setter가 필요한 이유

| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 유효성 검사          | 값이 설정될 때 조건을 확인하고 잘못된 입력을 방지할 수 있음               |
| 로깅 및 변경 추적     | 값이 변경될 때 로그를 남기거나 변경 이력을 관리할 수 있음                 |
| 상태 동기화         | 하나의 속성 변경이 다른 속성에 영향을 줄 때 내부 상태를 자동으로 맞춰줌       |
| 외부 연동 안정화     | 외부 API나 DB와 연결 시 데이터 검증 및 포맷 변환을 안전하게 처리 가능         |
| 트리거 및 자동 처리   | 값이 변경될 때 특정 동작을 자동으로 실행할 수 있어 이벤트 기반 처리에 유용함   |

---

### 📌 @property란?
- 클래스 내부의 메서드를 속성처럼 사용할 수 있게 해주는 데코레이터
    - 외부에서는 obj.value처럼 접근하지만, 내부에서는 get_value()처럼 동작
    - **캡슐화(Encapsulation)** 를 유지하면서도 가독성과 사용성을 높여줌

### 📌 기본 예제: Getter, Setter, Deleter
```python
class Person:
    def __init__(self, name):
        self._name = name

    @property
    def name(self):  # Getter
        return self._name

    @name.setter
    def name(self, value):  # Setter
        if not value:
            raise ValueError("Name cannot be empty")
        self._name = value

    @name.deleter
    def name(self):  # Deleter
        print("Deleting name...")
        del self._name
```

#### 🔹 사용 예시
```python
p = Person("JungHwan")
print(p.name)       # Getter 호출 → JungHwan
p.name = "Copilot"  # Setter 호출
del p.name          # Deleter 호출
```


### 📌 특징 요약 – @property 캡슐화 방식

| 구성 요소             | 사용 방식            | 설명                                                                 |
|------------------------|----------------------|----------------------------------------------------------------------|
| `@property`            | `obj.value`          | Getter 역할. 속성처럼 읽기 가능. 내부 변수 반환 (`_name_value`)         |
| `@property.setter`     | `obj.value = x`      | Setter 역할. 속성처럼 값 할당 가능. 유효성 검사 및 내부 값 변경 가능     |
| `@property.deleter`    | `del obj.value`      | Deleter 역할. 속성 삭제 가능. 내부 변수 제거 또는 초기화 처리 가능       |
| 내부 변수              | `_name_value`        | 실제 데이터를 저장하는 보호된 변수. 외부에서 직접 접근은 자제 권장        |
| 캡슐화 효과            | 속성처럼 보이지만 내부 로직 숨김 | 외부 인터페이스는 깔끔하게 유지되며, 내부 구현은 자유롭게 변경 가능         |


### 📌 실무에서 왜 중요한가?

| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 캡슐화 유지          | 내부 상태를 직접 노출하지 않고 안전하게 제어 가능 (`_value` 보호)             |
| 속성처럼 접근 가능     | `obj.value`처럼 직관적인 문법으로 읽고 쓰기 가능. 외부 인터페이스가 깔끔함       |
| 유효성 검사          | Setter에서 값 검증, 예외 처리 가능. 잘못된 값 입력을 사전에 차단 가능           |
| 유지보수 및 확장성     | 내부 구현 변경 시에도 외부 코드는 그대로 유지 가능. API 안정성 확보              |
| 코드 가독성 향상      | `get_x()`, `set_x()`보다 `obj.x`가 더 자연스럽고 Pythonic함                   |


### 📌 실무 예제: 온도 변환기
```python
class Celsius:
    def __init__(self, temperature=0):
        self._temperature = temperature

    @property
    def temperature(self):
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        if value < -273.15:
            raise ValueError("Temperature below absolute zero!")
        self._temperature = value

    @property
    def fahrenheit(self):
        return (self._temperature * 9/5) + 32

```
#### 🔹 사용 예시
```python
c = Celsius()
c.temperature = 25
print(c.fahrenheit)  # 77.0
```


### 📌 @property vs Getter/Setter 비교
| 방식             | 접근 방식         | 코드 가독성 | 캡슐화 유지 | 확장성 | Pythonic 스타일 |
|------------------|------------------|-------------|--------------|--------|------------------|
| `@property`       | `obj.value`       | 높음        | 유지됨       | 우수함 | ✅ 매우 권장됨     |
| Getter/Setter 메서드 | `obj.get_value()` | 낮음        | 유지됨       | 보통   | ❌ Java 스타일     |

-  예외 발생
- 외부에서 직접 __age를 수정하지 못하게 보호

---

