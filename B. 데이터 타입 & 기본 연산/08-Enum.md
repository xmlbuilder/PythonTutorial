# 🧾 Python Enum 클래스 요약
```python
from enum import Enum

class Language(Enum):
    PYTHON = "Python"
    RUST = "Rust"
    JAVA = "Java"
    JAVASCRIPT = "Javascript"
    GO = "Go"

    def echo(self):
        print(self.name)   # 열거형 이름
        print(self.value)  # 열거형 값

language = Language.PYTHON
language.echo()
```
```
# 출력: PYTHON / Python
```

## 🔍 핵심 개념
| 항목                        | 설명 또는 예제 코드                                      |
|-----------------------------|----------------------------------------------------------|
| `Enum`                      | 열거형 클래스 정의를 위한 기본 클래스                    |
| `name`                      | 멤버 이름 (`PYTHON`, `RUST`, ...)                        |
| `value`                     | 멤버 값 (`"Python"`, `"Rust"`, ...)                      |
| 메서드 정의 가능            | `echo()` → 멤버의 `name`과 `value` 출력                  |
| 멤버 비교                   | `Language.PYTHON == Language['PYTHON']` → `True`         |
| 반복 가능                   | `for lang in Language:` → 모든 멤버 순회 가능             |



## ✅ 실전 활용 예시
### 🔹 반복문으로 전체 멤버 출력
```python
for lang in Language:
    print(lang.name, lang.value)
```

### 🔹 값으로 멤버 찾기
```python
print(Language("Python"))  # Language.PYTHON
```

### 🔹 auto()로 값 자동 할당
```python
from enum import Enum, auto

class Status(Enum):
    SUCCESS = auto()
    FAILURE = auto()
    PENDING = auto()
```


## 📌 Enum 사용 시 장점
- 코드 가독성 향상: 의미 있는 이름으로 값 표현
- 버그 예방: 고정된 값 집합으로 오타나 잘못된 값 방지
- 유지보수 용이: 값 변경 시 한 곳에서만 수정하면 됨

---

# IntEnum, Flag, auto(), unique()

## 🧮 IntEnum: 숫자처럼 동작하는 Enum
```python
from enum import IntEnum

class Number(IntEnum):
    ONE = 1
    TWO = 2
    THREE = 3

print(Number.THREE + 5)     # 8
print(Number.THREE == 3)    # True
```

- IntEnum은 Enum의 하위 클래스이며, 정수처럼 연산 가능
- ==, +, - 등 숫자 연산이 가능하지만, 결과는 일반 int가 됨
- Enum과 달리 숫자 기반 API와 호환성이 좋음

## 🧩 Flag: 비트 연산 가능한 Enum
```python
from enum import Flag, auto

class Permission(Flag):
    READ = auto()
    WRITE = auto()
    EXECUTE = auto()

perm = Permission.READ | Permission.WRITE
print(perm)  # Permission.READ|WRITE
```
- Flag는 비트 플래그를 표현할 때 사용
- 멤버를 조합할 수 있음 (|, &, ^)
- auto() 사용 시 내부적으로 2의 제곱수로 자동 할당됨

## ⚙️ auto(): 자동 값 할당
```python
from enum import Enum, auto

class Status(Enum):
    NEW = auto()
    IN_PROGRESS = auto()
    DONE = auto()
```

- auto()는 값을 자동으로 할당해줌
- Enum → 1부터 증가
- IntEnum → 1부터 증가
- Flag → 1, 2, 4, 8, ... (비트 연산용)
- 커스터마이징하려면 _generate_next_value_() 메서드를 오버라이딩 가능


## 🛡️ @unique: 값 중복 방지 데코레이터

```python
from enum import Enum, unique

@unique
class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3
    # RED_ALIAS = 1  # 오류 발생!
```

- @unique는 중복된 값이 있는 경우 오류 발생
- 실수로 같은 값을 여러 이름에 할당하는 것을 방지

## 📌 고급 Enum 기능 요약표
| 기능       | 설명                                       | 특징 요약                     |
|------------|--------------------------------------------|-------------------------------|
| `IntEnum`  | 숫자처럼 연산 가능한 Enum                  | `==`, `+`, `-` 가능            |
| `Flag`     | 비트 연산 가능한 Enum                      | `|`, `&`, `^` 조합 가능        |
| `auto()`   | 값 자동 할당                               | `Enum`: 1부터, `Flag`: 2의 제곱 |
| `@unique`  | 값 중복 방지                               | 중복 시 `ValueError` 발생      |

---





