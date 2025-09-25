
# assert
Python의 assert 문에 대한 문법과 동작 원리, 그리고 실전 예제 중심의 정리입니다.  
디버깅과 조건 검증에 매우 유용한 기능.

## ✅ assert 문법과 기능 정리
### 🔧 기본 문법
```
assert 조건식, "에러 메시지"
```

- 조건식이 True면 아무 일도 일어나지 않음
- 조건식이 False면 AssertionError 예외 발생
- "에러 메시지"는 선택 사항이며, 오류 발생 시 출력됨

## 📌 사용 목적

| 목적             | 설명                                           |
|------------------|------------------------------------------------|
| 디버깅           | 코드 실행 중 조건이 만족하는지 빠르게 확인       |
| 입력 검증        | 함수나 로직에 전달된 값이 예상된 타입/범위인지 확인 |
| 로직 검증        | 특정 상태나 흐름이 올바르게 유지되는지 확인       |
| 테스트 보조      | 단위 테스트에서 예상 결과를 검증하는 데 사용       |



### 🧪 예제 1: 단순 조건 검증
```python
assert 100 < 98, "Exception"
```

- 100 < 98은 False이므로 AssertionError: Exception 발생
- 실행 중단 + 명확한 오류 메시지 제공

### 🧪 예제 2: 타입 검증 함수
```python
def add(x, y):
    assert (type(x), type(y)) in [(int, int)], "정수가 아님"
    return x + y

add(10, 20)      # 정상 실행
add(10, 12.0)    # AssertionError: 정수가 아님
```

- assert를 통해 함수 인자의 타입을 강제
- 실수나 문자열이 들어오면 즉시 예외 발생

### 📘 고급 팁
- assert는 디버깅용으로 설계되었으며, -O 옵션으로 Python을 실행하면 무시됨
python -O script.py  # assert 문이 실행되지 않음
- 실무에서는 assert 대신 if + raise를 사용하는 경우도 많음 (예외 종류 지정 가능)
if not isinstance(x, int):
    raise TypeError("x는 정수여야 합니다")



## ⚠️ 주의사항

| 항목             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `-O` 옵션        | Python 실행 시 `-O`(Optimize) 옵션을 사용하면 `assert` 문이 무시됨     |
| `assert vs if+raise` | `assert`는 디버깅용, 실무에서는 `if` + `raise`로 예외 종류를 명확히 처리 |
| `AssertionError` | `assert` 실패 시 발생하는 기본 예외 타입                             |


## 📘 assert / raise 예시 비교

### ✅ assert 방식
```python
assert x > 0, "x는 0보다 커야 합니다"
```

## ✅ if + raise 방식

```python
if x <= 0:
    raise ValueError("x는 0보다 커야 합니다")
```

assert는 테스트나 내부 검증에 적합하고, if + raise는 사용자 입력 검증 등 실무에 적합합니다.

---

# 🧪 pytest에서의 assert 활용법
 Python 테스트 프레임워크인 pytest에서의 assert 활용법을 중심으로 정리한 문서입니다.

## ✅ 1. 기본 문법
```python
def test_add():
    assert 1 + 1 == 2
```

- assert가 실패하면 AssertionError 발생
- pytest는 실패한 assert의 좌우 값을 자동으로 비교 출력해줌

## 📌 2. 다양한 비교 예시
```python
def test_values():
    assert 10 > 5
    assert "Python" in "I love Python"
    assert [1, 2] == [1, 2]
    assert {"a": 1} == {"a": 1}
```

pytest는 리스트, 딕셔너리, 문자열 등 다양한 타입을 비교할 수 있으며, 실패 시 상세한 diff를 보여줍니다.


## 🧠 3. 실패 메시지 커스터마이징
```python
def test_fail_message():
    assert 100 < 98, "100은 98보다 작지 않습니다"
```

- 실패 시 "100은 98보다 작지 않습니다"라는 메시지가 함께 출력됨

## 🧪 4. 예외 발생 테스트 (pytest.raises)
```python
import pytest

def divide(x, y):
    return x / y

def test_zero_division():
    with pytest.raises(ZeroDivisionError):
        divide(10, 0)
```


- 특정 예외가 발생하는지 검증할 때 사용
- with pytest.raises(...) 블록 안에서 예외가 발생해야 테스트 통과

## 🧩 5. 타입 및 조건 검증
```python
def test_type_check():
    result = sum([1, 2, 3])
    assert isinstance(result, int)
    assert result == 6

```

## 📂 6. 파일 구조 예시
```
project/
├── app.py
├── test_app.py
```

## test_app.py
```python
from app import add

def test_add():
    assert add(2, 3) == 5
```

pytest는 test_*.py 또는 *_test.py 파일에서 test_로 시작하는 함수들을 자동으로 인식합니다.


## 🚀 실행 방법
```
pytest test_app.py
```

- 모든 테스트 실행
- 실패한 테스트는 상세한 비교 결과와 traceback을 출력

## 📘 고급 팁

| 옵션/기능                  | 설명                                                   |
|----------------------------|--------------------------------------------------------|
| `-v`                       | verbose 모드: 테스트 이름과 결과를 자세히 출력          |
| `-x`                       | 첫 번째 실패 발생 시 테스트 실행 중단                   |
| `--maxfail=3`              | 최대 3개 실패 후 테스트 실행 중단                      |
| `pytest.mark.parametrize` | 다양한 입력값으로 동일 테스트를 반복 실행할 수 있음     |



### ✅ pytest.mark.parametrize 예시
```python
import pytest

@pytest.mark.parametrize("x, y, expected", [
    (1, 2, 3),
    (2, 3, 5),
    (3, 4, 7)
])

def test_add(x, y, expected):
    assert x + y == expected
```

하나의 테스트 함수로 여러 케이스를 자동 실행할 수 있어 테스트 코드가 간결해지고 유지보수가 쉬워집니다.


