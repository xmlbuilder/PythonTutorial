## 📘 타입 힌트란?
- Python은 동적 타입 언어지만, 타입 힌트를 통해 정적 타입처럼 명시적으로 타입을 지정할 수 있음
- 런타임에는 영향을 주지 않음 → 타입 오류가 있어도 실행은 됨
- 타입 힌트는 개발자와 도구를 위한 문서화 수단

### 📌 변수에 타입 힌트
```python
y: int = 100
```

- y는 int 타입으로 선언됨
- 타입 힌트는 : 뒤에 타입을 명시
- 실제로는 y = 100과 동일하게 동작하지만, IDE나 타입 검사 도구가 타입을 인식함

### 📌 함수에 타입 힌트
```python
def add(x: int, y: int) -> int:
    z: int = x + y
    return z
```

### 📌 타입 힌트 표현 요약
| 표현       | 의미 설명 |
|------------|------------|
| `x: int`   | 변수 `x`는 정수형 (`xint`) |
| `y: int`   | 변수 `y`는 정수형 (`yint`) |
| `-> int`   | 함수의 반환값은 정수형 (`int`) |
| `z: int`   | 지역 변수 `z`는 정수형 (`zint`) |


### 📌 타입 힌트의 효과
- IDE 지원 강화: 자동 완성, 경고, 리팩터링 도움
- 정적 검사 가능: mypy, pyright 등으로 타입 오류 사전 탐지
- 협업 시 명확한 의도 전달: 함수의 입력과 출력 타입이 명확함

### 📌 확장된 타입 힌트 예시
```python
from typing import List, Dict, Optional, Tuple

def process(data: List[int]) -> Dict[str, int]:
    return {"sum": sum(data), "count": len(data)}

def get_user(id: int) -> Optional[str]:
    return "JungHwan" if id == 1 else None

def get_name_and_age() -> Tuple[str, int]:
    return ("JungHwan", 30)
```


### 📌 타입 힌트 예시 요약
| 표현               | 설명 또는 의미                          |
|--------------------|------------------------------------------|
| `List[int]`        | 정수형 요소를 갖는 리스트                |
| `Dict[str, int]`   | 문자열 키와 정수 값을 갖는 딕셔너리      |
| `Optional[str]`    | 문자열 또는 `None` 가능 (`strNone`)      |
| `Tuple[str, int]`  | 문자열과 정수로 구성된 튜플              |



### 📌 주의사항
| 항목        | 설명 또는 위험 요소                                      |
|-------------|----------------------------------------------------------|
| `mypy`      | 타입 힌트 오류를 사전 검사하는 정적 분석 도구. 실행에는 영향 없음 |
| `typing`    | `List`, `Dict`, `Optional` 등 복합 타입 지정 시 반드시 사용해야 함 |
| 런타임 검사 없음 | 타입 힌트는 실행 시 강제되지 않음. 타입 오류가 있어도 코드 실행 가능 |
| 일관성 유지 | 힌트와 실제 타입이 다르면 혼란 발생 가능. 코드 전체에서 일관된 타입 사용 권장 |


--- 

### 📌 타입 검사 도구 사용 예시
mypy는 Python 코드에 작성된 **타입 힌트(Type Hint)** 를 기반으로 정적 타입 검사를 수행하는 도구
```
pip install mypy
mypy your_script.py
```
- mypy는 타입 힌트를 기반으로 코드의 타입 오류를 사전 탐지해줍니다

#### 🔹 1. mypy 설치
```
pip install mypy
```

#### 🔹 설치 후 버전 확인:
```
mypy --version
```

#### 🔹 2. 기본 사용법
```
mypy your_script.py
```

- 타입 힌트가 잘못된 부분을 찾아서 경고 또는 오류로 알려줍니다.
- 예: x: int = "hello" → 문자열을 정수로 선언했기 때문에 오류 발생

#### 🔹 3. 설정 파일 만들기
- mypy는 프로젝트 루트에 설정 파일을 두면 자동으로 인식. 
- 사용 가능한 파일 이름:
    - mypy.ini
    - .mypy.ini
    - setup.cfg
    - pyproject.toml (최근 버전에서 지원)

#### 🔹 예시: mypy.ini
```
[mypy]
python_version = 3.10
ignore_missing_imports = True
disallow_untyped_defs = True
check_untyped_defs = True
strict_optional = True
```

#### 🔹 mypy 설정 옵션 요약
| 옵션 이름               | 설명 또는 의미                          |
|-------------------------|------------------------------------------|
| `ignore_missing_imports` | 타입 정보가 없는 외부 모듈의 오류를 무시함 |
| `disallow_untyped_defs` | 타입 힌트가 없는 함수 정의를 허용하지 않음 |
| `check_untyped_defs`    | 타입 힌트가 없는 함수도 검사 대상으로 포함 |
| `strict_optional`       | `Optional` 타입을 엄격하게 검사함 (`None` 처리 포함) |

#### 🔹 4. 디렉토리 전체 검사
```
mypy src/ tests/
```

- 여러 디렉토리나 파일을 한 번에 검사 가능
- 설정 파일을 기반으로 검사 범위와 규칙을 자동 적용

#### 🔹 5. 실전 예제
```python
# test.py
def greet(name: str) -> str:
    return "Hello, " + name

greet(123)  # 타입 오류 발생
```

```
mypy test.py
```

#### 🔹출력 내용
```
# test.py:4: error: Argument 1 to "greet" has incompatible type "int"; expected "str"
```
---



