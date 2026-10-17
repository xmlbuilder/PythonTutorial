## 📘 사용자 정의 예외(Custom Exception) 선언과 사용법
- 사용자 정의 예외는 프로그램의 특정 오류 상황을 명확하게 구분하기 위해 개발자가 직접 만드는 예외 클래스입니다.
- 일반적으로 `Exception`을 상속하며, `raise`로 발생시키고 `try-except`로 처리합니다.

### 📌 사용자 정의 예외가 필요한 이유
- 파일 형식 오류, 데이터 검증 실패 등 **프로그램 고유의 오류** 를 구분할 수 있습니다.
- 호출자가 오류 종류에 따라 다른 처리를 할 수 있습니다.
- 예외 메시지와 추가 정보를 함께 전달할 수 있습니다.

### 📌 1. 기본 선언과 사용
```python
class InvalidGeometryError(Exception):
    pass

def check_length(length):
    if length < 0:
        raise InvalidGeometryError("길이는 음수가 될 수 없습니다.")
    return length

try:
    check_length(-2.0)
except InvalidGeometryError as e:
    print("Geometry 오류:", e)
```

#### 🔹 실행 결과
```text
Geometry 오류: 길이는 음수가 될 수 없습니다.
```

- `class InvalidGeometryError(Exception)`: 예외 클래스 선언
- `raise InvalidGeometryError(...)`: 예외 발생
- `except InvalidGeometryError as e`: 해당 예외만 처리

### 📌 2. 오류 정보를 포함하는 예외 클래스
```python
class InvalidEdgeLengthError(ValueError):
    def __init__(self, edge_id, length):
        self.edge_id = edge_id
        self.length = length
        super().__init__(
            f"Edge {edge_id}: 잘못된 길이 {length}"
        )


def add_edge(edge_id, length):
    if length < 0:
        raise InvalidEdgeLengthError(edge_id, length)


try:
    add_edge(101, -3.5)
except InvalidEdgeLengthError as e:
    print(e)
    print("Edge ID:", e.edge_id)
    print("Length:", e.length)
```

#### 🔹 실행 결과
```text
Edge 101: 잘못된 길이 -3.5
Edge ID: 101
Length: -3.5
```

- `ValueError`를 상속하면 기존 값 검증 오류 계층과도 호환됩니다.
- `super().__init__(...)`은 예외 메시지를 기본 예외 클래스에 전달합니다.

### 📌 3. 여러 예외를 계층적으로 선언
```python
class GeometryError(Exception):
    pass


class InvalidEdgeError(GeometryError):
    pass


class InvalidSurfaceError(GeometryError):
    pass


try:
    raise InvalidEdgeError("Edge 연결 정보가 잘못되었습니다.")
except GeometryError as e:
    print("Geometry 관련 오류:", e)
```

- `except GeometryError`는 `InvalidEdgeError`, `InvalidSurfaceError`를 모두 처리할 수 있습니다.
- 개별 예외를 따로 처리하려면 **구체적인 예외를 먼저** 작성합니다.

### 📌 4. 예외를 변환하여 다시 발생시키기
```python
class GeometryLoadError(Exception):
    pass


def load_geometry(path):
    try:
        with open(path, "r", encoding="utf-8") as f:
            return f.read()
    except OSError as e:
        raise GeometryLoadError(f"Geometry 파일 로드 실패: {path}") from e
```

- `raise ... from e`는 원래 발생한 예외를 원인으로 연결하여 디버깅에 도움을 줍니다.
- 현재 예외를 그대로 다시 전달할 때는 `raise`만 사용합니다.

### 📌 5. 사용 시 주의사항
- 일반적인 프로그램 오류에는 기존 `ValueError`, `TypeError` 등의 내장 예외를 우선 고려합니다.
- 사용자 정의 예외는 보통 `Exception` 또는 적절한 내장 예외를 상속합니다. `BaseException` 직접 상속은 피합니다.
- 예외를 무조건 잡거나 `except: pass`로 숨기지 않습니다.
- 처리할 수 없는 예외는 호출자에게 전달하고, 필요하면 상위 단계에서 로깅합니다.

### 📌 핵심 정리
| 목적 | 문법 |
|---|---|
| 예외 선언 | `class MyError(Exception): pass` |
| 예외 발생 | `raise MyError("message")` |
| 예외 처리 | `except MyError as e:` |
| 원인 연결 | `raise MyError("message") from e` |
| 예외 재발생 | `raise` |

> **기억할 점:** 사용자 정의 예외는 새로운 오류 처리 문법이 아니라, **오류의 의미를 구분하기 위한 클래스** 입니다.

---
