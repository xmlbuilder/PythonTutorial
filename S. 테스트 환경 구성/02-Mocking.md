# Mocking
- **모킹(Mock)** 은 테스트에서 정말 자주 등장하는 개념인데, 특히 외부 의존성을 대체하거나 격리할 때 아주 유용. 
- 아래에 개념부터 실무 활용까지 자세히 설명해.

## 🧠 모킹(Mock)이란?
- 테스트 대상 코드가 의존하고 있는 외부 객체나 함수의 동작을 흉내내는 것.  
```python
assert result["name"] == "JungHwan"
```

## ✅ 여기서 일어난 일
- requests.get을 **가짜 함수(mock)** 로 바꿈
- 실제 API 호출 없이, 우리가 원하는 응답을 직접 지정
- 테스트는 빠르고 안정적으로 수행됨

## 🧰 모킹 도구 정리

| 모킹 도구           | 연결 대상 / 기능 설명                                      |
|---------------------|------------------------------------------------------------|
| `unittest.mock`     | `patch`, `MagicMock` 등으로 함수, 클래스, 모듈을 모킹 가능       |
| `pytest-mock`       | `pytest`와 통합된 모킹 도구 → `mocker` fixture로 간편하게 사용   |
| `responses`         | `requests` 라이브러리의 HTTP 요청을 모킹 → API 테스트에 특화됨   |

## 🔍 간단 설명
- unittest.mock: Python 내장 모듈. 가장 기본적인 모킹 도구로, 거의 모든 객체를 가짜로 바꿀 수 있음.
- pytest-mock: pytest 사용자에게 친화적인 모킹 방식. mocker.patch()로 더 깔끔하게 작성 가능.
- responses: requests.get() 같은 HTTP 요청을 가로채서 원하는 응답을 반환하게 해줌. 외부 API 테스트에 매우 유용.

## 🧪 예시 흐름
### unittest.mock 사용 예시
```python
from unittest.mock import patch

@patch("requests.get")
def test_api(mock_get):
    mock_get.return_value.json.return_value = {"status": "ok"}
    assert requests.get("https://example.com").json()["status"] == "ok"
```

### pytest-mock 사용 예시
```python
def test_api_with_mocker(mocker):
    mock_get = mocker.patch("requests.get")
    mock_get.return_value.json.return_value = {"status": "ok"}
    assert requests.get("https://example.com").json()["status"] == "ok"
```

### responses 사용 예시
```python
import responses

@responses.activate
def test_api_with_responses():
    responses.add(
        responses.GET,
        "https://example.com",
        json={"status": "ok"},
        status=200
    )
    resp = requests.get("https://example.com")
    assert resp.json()["status"] == "ok"
```


## 📌 실무 적용 팁

| 적용 상황               | 모킹 활용 예시                                                   |
|--------------------------|------------------------------------------------------------------|
| 외부 API 호출 테스트       | 실제 API 대신 응답을 모킹하여 빠르고 안정적인 테스트 수행               |
| DB 접근 테스트            | DB 연결 없이 쿼리 결과를 가짜로 반환 → 테스트 속도 향상 및 격리 가능       |
| 시간 기반 로직 테스트      | `datetime.now()`을 고정된 시간으로 모킹 → 시간 조건 테스트에 유리           |
| 파일 시스템 접근 테스트    | `open()`, `os.path.exists()` 등을 모킹 → 실제 파일 없이 로직 검증 가능       |
| 예외 상황 시뮬레이션       | 실패 응답, 네트워크 오류 등 다양한 예외를 인위적으로 만들어 테스트 가능       |


## 🔍 예시 흐름
### ⏰ 시간 모킹 (datetime.now())
```python
from unittest.mock import patch
from datetime import datetime

def get_today():
    return datetime.now().date()

@patch("datetime.datetime")
def test_get_today(mock_datetime):
    mock_datetime.now.return_value = datetime(2025, 9, 26)
    assert get_today() == datetime(2025, 9, 26).date()
```

## 📁 파일 존재 여부 모킹 (os.path.exists())
```python
from unittest.mock import patch
import os

def check_file(path):
    return os.path.exists(path)

@patch("os.path.exists")
def test_check_file(mock_exists):
    mock_exists.return_value = True
    assert check_file("/fake/path") == True
```

- 이처럼 모킹은 실무에서 불확실한 외부 요소를 제어하고, 테스트를 빠르고 안정적으로 수행할 수 있게 해주는 핵심 기술.
- 모킹은 단순히 **가짜로 만든다**는 개념을 넘어서, 테스트의 품질과 속도, 안정성을 높여주는 핵심 기술.




## 🧰 필수 설치 패키지
### 1. ✅ pytest – 테스트 프레임워크
```
pip install pytest
```

- 역할: Python 테스트를 자동화하고, 간결한 문법으로 다양한 케이스를 검증할 수 있게 해줌.
- 사용 예: assert, @pytest.mark.parametrize, pytest.raises() 등

### 2. 🧪 pytest-mock (선택 사항)
```
pip install pytest-mock
```

- 역할: pytest에서 모킹 기능을 더 쉽게 사용할 수 있게 해주는 플러그인
- 사용 예: mocker.patch()로 외부 함수나 객체를 가짜로 대체

### 3. 🌐 responses (선택 사항)
```
pip install responses
```

- 역할: requests 기반 HTTP 호출을 모킹할 수 있는 라이브러리
- 사용 예: 외부 API를 테스트할 때 실제 호출 없이 응답을 시뮬레이션

## 📦 설치 요약
- 사용 예
```
pip install pytest pytest-mock responses
```

- 위 명령어를 한 번에 실행하면 테스트 환경이 완성돼.
- 설치 후에는 pytest test.py로 테스트를 바로 실행할 수 있음

----






