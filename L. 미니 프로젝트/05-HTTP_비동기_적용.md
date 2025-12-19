# HTTP 비동기 방식
- 코드들을 기반으로, 동기 방식과 비동기 방식의 HTTP 요청 처리 흐름을 비교하고,  
- 비동기 방식의 전체 소스와 그 동작 원리를 자세히 설명.

## 🔁 동기 방식 vs 비동기 방식 비교
| 항목               | `requests` (동기 방식)                          | `aiohttp + asyncio` (비동기 방식)                     |
|--------------------|--------------------------------------------------|--------------------------------------------------------|
| 처리 방식           | 요청을 하나씩 순차적으로 처리                     | 여러 요청을 동시에 병렬로 처리                            |
| 실행 흐름           | 다음 요청은 이전 요청이 끝나야 시작됨               | 모든 요청을 동시에 시작하고, 응답을 기다림                  |
| 성능               | 느림. 요청 수가 많을수록 전체 처리 시간 증가         | 빠름. 요청 수가 많아도 병렬 처리로 전체 시간 단축 가능       |
| 코드 구조           | 간단하지만 병렬 처리에 불리함                      | `async/await` 구조로 병렬 처리 가능, 유지보수도 쉬움         |
| 사용 라이브러리      | `requests`                                     | `aiohttp`, `asyncio`                                   |
| 실무 활용 예시       | 단일 요청, 테스트용 스크립트, 간단한 작업             | 웹 크롤링, API 병렬 호출, 실시간 데이터 수집 등 고성능 작업     |


## ✅ 비동기 방식은 여러 HTTP 요청을 동시에 처리하므로 속도가 훨씬 빠름!

## 🧪 비동기 방식 전체 코드
```python
import asyncio
import aiohttp
import time
from random import randint

MAX_POKEMON = 898

async def _fetch(session, url):
    async with session.get(url) as response:
        return await response.json()

async def fetch(total):
    urls = [
        f"https://pokeapi.co/api/v2/pokemon/{randint(1, MAX_POKEMON)}"
        for _ in range(total)
    ]
    async with aiohttp.ClientSession() as session:
        tasks = [_fetch(session, url) for url in urls]
        responses = await asyncio.gather(*tasks)
        for response in responses:
            yield response["name"]

async def main():
    async for name in fetch(10):
        print(name)

start = time.time()
asyncio.run(main())
print(f"Time taken: {time.time() - start:.3f}s")
```

## 🔍 코드 설명
### 🔧 주요 구성
| 구성 요소               | 설명                                                                 |
|------------------------|----------------------------------------------------------------------|
| `aiohttp.ClientSession` | 비동기 HTTP 세션을 생성. 여러 요청을 효율적으로 관리하고 재사용 가능             |
| `_fetch()`              | 개별 URL에 비동기적으로 요청을 보내고 JSON 응답을 반환하는 함수                    |
| `asyncio.gather()`      | 여러 비동기 작업을 동시에 실행 → 병렬 처리의 핵심. 결과를 리스트로 반환             |
| `async for`             | 비동기 generator를 순회하며 결과를 하나씩 처리 → `yield` 기반 비동기 반복 구조       |
| `asyncio.run(main())`   | 비동기 루프를 시작하고 `main()` 코루틴을 실행 → 프로그램 진입점 역할               |


## 📤 실행 결과 예시
```
kabutops
frogadier
mankey
lucario
mienfoo
pancham
voltorb
nuzleaf
minccino
aurorus
Time taken: 0.411s
```

###  🎉 동기 방식보다 6배 이상 빠른 처리 속도를 보여줌!

## 📌 실무 적용 포인트

| 분야               | 비동기 처리 활용 예시                                               |
|--------------------|---------------------------------------------------------------------|
| 웹 크롤링           | 수백 개의 URL을 동시에 요청 → 빠른 데이터 수집, 크롤링 속도 향상             |
| API 클라이언트       | 외부 서비스에 병렬 요청 → 응답 지연 최소화, 대량 호출 시 서버 부하 감소         |
| 실시간 알림 시스템    | 이벤트 발생 시 빠르게 사용자에게 알림 전송 → 반응성 향상, 사용자 경험 개선         |
| 서버 백엔드          | 요청 처리, DB 접근, 파일 I/O 등을 병렬로 처리 → 서버 처리량 증가, 리소스 효율화     |
| 데이터 파이프라인     | 생산자-소비자 구조에서 비동기적으로 데이터 흐름 제어 → 병목 없이 안정적 처리 가능     |

- 이제 aiohttp와 asyncio를 활용한 비동기 HTTP 처리의 구조와 성능 이점이 확실히 이해

---

# AsyncIO은 Thread 방식이 아님
- Python의 비동기 방식(asyncio)은 전통적인 의미의 thread를 직접 사용.  
- 대신 단일 스레드 기반의 이벤트 루프를 활용해서 **동시성(concurrency)** 을 구현.

## 🔍 비동기 방식 vs 스레드 방식
| 항목             | `threading` (스레드 방식)                                 | `asyncio` (비동기 방식)                                  |
|------------------|-----------------------------------------------------------|-----------------------------------------------------------|
| 처리 방식         | 여러 스레드를 생성해 병렬 처리                              | 단일 스레드에서 이벤트 루프를 통해 동시성 구현               |
| 병렬성 구현 방식   | OS 스레드 기반 → GIL의 영향을 받음                         | 코루틴 기반 → GIL 영향 없음, I/O-bound에 최적화             |
| 자원 사용량       | 스레드마다 메모리와 컨텍스트 필요 → 자원 소모 큼             | 매우 가볍고 효율적 → 수천 개의 작업도 처리 가능              |
| 코드 복잡도       | 동기화 필요 → `Lock`, `Semaphore` 등 사용                   | `await` 기반 → 코드가 간결하고 직관적                        |
| 적합한 작업 유형   | CPU-bound 작업 (계산, 이미지 처리 등)                       | I/O-bound 작업 (HTTP 요청, 파일 읽기, DB 접근 등)            |
| 예시 라이브러리    | `threading`, `concurrent.futures`                         | `asyncio`, `aiohttp`, `aiomysql`, `aiofiles` 등              |



## 🧠 asyncio는 어떻게 동작하나?
- asyncio는 **이벤트 루프(event loop)** 를 통해 작업을 예약하고, await를 만나면 다른 작업으로 컨텍스트를 전환.
- 이 방식은 스레드를 생성하지 않고도 여러 작업을 동시에 처리하는 효과.
- 특히 **I/O-bound 작업(예: HTTP 요청, 파일 읽기)** 에 매우 효율적.

## ✅ 핵심 차이

| 항목             | `threading` (스레드 방식)                          | `asyncio` (비동기 방식)                                  |
|------------------|---------------------------------------------------|-----------------------------------------------------------|
| 병렬 처리 방식     | OS 스레드를 생성하여 병렬 처리                        | 단일 스레드에서 이벤트 루프를 통해 동시성 구현               |
| GIL 영향         | 있음 → CPU-bound 작업에 성능 제한                    | 없음 → I/O-bound 작업에 최적화됨                            |
| 자원 사용량       | 스레드마다 메모리와 컨텍스트 필요 → 자원 소모 큼        | 매우 가볍고 효율적 → 수천 개의 작업도 처리 가능              |
| 동기화 필요 여부   | `Lock`, `Semaphore` 등으로 동기화 필요                | 이벤트 루프가 자동으로 처리 → 복잡한 동기화 불필요            |
| 코드 구조         | 복잡하고 버그 발생 가능성 높음                        | `async/await` 기반으로 간결하고 직관적                       |


## 🔧 예시 비교
### threading 방식
```python
import threading

def task():
    print("Running in thread")

thread = threading.Thread(target=task)
thread.start()


asyncio 방식
import asyncio

async def task():
    print("Running in event loop")

asyncio.run(task())
```


### 💡 참고: asyncio 내부적으로 thread를 쓸 수도 있음
- asyncio.to_thread()를 사용하면 비동기 코드에서 백그라운드 스레드로 작업을 넘길 수 있음.
- 하지만 기본적으로는 스레드를 직접 생성하지 않고, 이벤트 루프 기반으로 동작함.

- 요약하자면, 비동기 방식은 스레드를 쓰지 않고도 동시성을 구현.


