## ✅ Python WebClient 패키지 구조
```
python_webclient/
│
├── webclient/
│   ├── __init__.py
│   ├── client.py        # WebClient 클래스
│   ├── html_parser.py   # HTML 파싱 유틸
│   ├── json_path.py     # JSONPath 유틸
│   └── exceptions.py
│
├── tests/
│   ├── test_client.py
│
├── pyproject.toml       # 패키지 설정
└── README.md
```


## ✅ Python WebClient 기능 요약
| 기능                         | 지원 |
|------------------------------|------|
| GET 요청                     | ✅   |
| POST JSON                    | ✅   |
| POST Form                    | ✅   |
| Multipart 파일 업로드        | ✅   |
| Form + 파일 동시 업로드      | ✅   |
| 대용량 스트리밍 업로드       | ✅   |
| HTML 파싱                    | ✅   |
| CSS Selector                 | ✅   |
| HTML attribute 추출          | ✅   |
| JSON key 접근                | ✅   |
| JSONPath 지원                | ✅   |
| 쿠키/세션 유지               | ✅   |
| 기본 헤더 자동 추가          | ✅   |
| Timeout 설정                 | ✅   |


## ✅ Python WebClient 구현

### 📌 webclient/client.py
```python
import aiohttp
import asyncio
from bs4 import BeautifulSoup
from .json_path import json_path_query


class WebClient:
    def __init__(self, url, timeout=30, headers=None):
        self.url = url
        self.timeout = timeout
        self.session = aiohttp.ClientSession(
            timeout=aiohttp.ClientTimeout(total=timeout),
            headers=headers or {
                "User-Agent": "PythonWebClient/1.0",
                "Accept": "*/*"
            }
        )
        self.html = None
        self.json = None

    async def _parse_response(self, resp):
        text = await resp.text()

        # JSON 자동 판별
        if text.strip().startswith("{"):
            try:
                self.json = await resp.json()
            except:
                self.html = BeautifulSoup(text, "html.parser")
        else:
            self.html = BeautifulSoup(text, "html.parser")

    # ✅ GET
    async def get(self):
        async with self.session.get(self.url) as resp:
            await self._parse_response(resp)
        return self

    # ✅ POST JSON
    async def post_json(self, data):
        async with self.session.post(self.url, json=data) as resp:
            await self._parse_response(resp)
        return self

    # ✅ POST Form
    async def post_form(self, form):
        async with self.session.post(self.url, data=form) as resp:
            await self._parse_response(resp)
        return self

    # ✅ Multipart 파일 업로드
    async def upload_files(self, files):
        form = aiohttp.FormData()
        for field, path, mime in files:
            form.add_field(
                field,
                open(path, "rb"),
                filename=path,
                content_type=mime
            )

        async with self.session.post(self.url, data=form) as resp:
            await self._parse_response(resp)
        return self

    # ✅ Form + 파일 업로드
    async def upload_form_and_files(self, form_fields, files):
        form = aiohttp.FormData()

        for k, v in form_fields.items():
            form.add_field(k, v)

        for field, path, mime in files:
            form.add_field(
                field,
                open(path, "rb"),
                filename=path,
                content_type=mime
            )

        async with self.session.post(self.url, data=form) as resp:
            await self._parse_response(resp)
        return self

    # ✅ 스트리밍 업로드
    async def upload_stream(self, field, path, mime):
        form = aiohttp.FormData()
        form.add_field(
            field,
            open(path, "rb"),
            filename=path,
            content_type=mime
        )

        async with self.session.post(self.url, data=form) as resp:
            await self._parse_response(resp)
        return self

    # ✅ HTML selector
    def select(self, selector):
        if not self.html:
            return []
        return [el.get_text(strip=True) for el in self.html.select(selector)]

    # ✅ HTML attribute
    def attr(self, selector, attr):
        if not self.html:
            return []
        return [el.get(attr) for el in self.html.select(selector) if el.get(attr)]

    # ✅ JSON key
    def json_key(self, key):
        if not self.json:
            return None
        return self.json.get(key)

    # ✅ JSONPath
    def json_path(self, path):
        if not self.json:
            return None
        return json_path_query(self.json, path)

    async def close(self):
        await self.session.close()
```
## ✅ JSONPath 구현 (Rust 버전과 동일)
### 📌 webclient/json_path.py
```python
def json_path_query(data, path):
    current = data
    for part in path.split("."):
        if "[" in part:
            key, idx = part[:-1].split("[")
            current = current.get(key)[int(idx)]
        else:
            current = current.get(part)
        if current is None:
            return None
    return current
```


## ✅ HTML 파싱은 BeautifulSoup 사용
- Rust의 scraper와 거의 동일한 기능 제공.

## ✅ Python 테스트 코드 (Rust 테스트와 동일)
### 📌 tests/test_client.py
```python
import pytest
import asyncio
from webclient.client import WebClient


@pytest.mark.asyncio
async def test_get():
    client = await WebClient("https://httpbin.org/get").get()
    assert client.json_key("url") is not None
    await client.close()
```

## ✅ Python 패키지 설정 (pyproject.toml)
```
[project]
name = "python-webclient"
version = "0.1.0"
description = "Unified HTTP WebClient for Python"
requires-python = ">=3.10"

dependencies = [
    "aiohttp",
    "beautifulsoup4",
    "pytest",
]

[tool.pytest.ini_options]
asyncio_mode = "auto"
```



