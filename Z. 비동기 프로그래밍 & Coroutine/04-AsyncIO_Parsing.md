# 🌐 AsyncIO 멀티 웹 스크래핑 + HTML 파싱 실습
## 🎯 목적
- 여러 웹사이트를 동시에 요청하고 HTML을 파싱하여 원하는 정보를 추출
- asyncio + ThreadPoolExecutor + BeautifulSoup 조합으로 비동기 웹 스크래핑 구현


## 🧠 핵심 개념

| 개념               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `asyncio`          | Python의 비동기 처리 프레임워크. 코루틴 기반으로 non-blocking 실행 가능 |
| `run_in_executor()`| 동기 함수를 별도 쓰레드/프로세스에서 실행하여 비동기처럼 처리함         |
| `ThreadPoolExecutor`| 백그라운드에서 병렬 작업을 처리할 쓰레드 풀 생성                      |
| `BeautifulSoup`    | HTML 파싱 라이브러리. 원하는 태그나 텍스트를 쉽게 추출 가능             |
| `asyncio.gather()` | 여러 코루틴을 동시에 실행하고 결과를 리스트로 반환                      |


## 🧪 통합 실습 코드
```python
import asyncio
import timeit
from urllib.request import urlopen
from concurrent.futures import ThreadPoolExecutor
import threading
from bs4 import BeautifulSoup

# 실행 시작 시간
start = timeit.default_timer()

# 대상 사이트 목록
urls = [
    'http://daum.net',
    'https://naver.com',
    'http://mlbpark.donga.com/',
    'https://tistory.com',
    'https://wemakeprice.com/'
]

# 개별 URL 처리 함수
async def fetch(url, executor):
    print('Thread Name :', threading.current_thread().name, 'Start', url)
    
    # urlopen은 블로킹 함수 → executor로 비동기 처리
    res = await loop.run_in_executor(executor, urlopen, url)
    
    # HTML 파싱
    soup = BeautifulSoup(res.read(), 'html.parser')
    
    print('Thread Name :', threading.current_thread().name, 'Done', url)
    
    # <title> 태그 추출
    return soup.title.string if soup.title else 'No Title Found'

# 메인 실행 함수
async def main():
    executor = ThreadPoolExecutor(max_workers=10)
    
    # 모든 작업을 future로 스케줄링
    futures = [asyncio.ensure_future(fetch(url, executor)) for url in urls]
    
    # 결과 취합
    results = await asyncio.gather(*futures)
    
    print('\n📄 Parsed Titles:')
    for url, title in zip(urls, results):
        print(f'- {url} → {title}')

# 실행
if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
    
    duration = timeit.default_timer() - start
    print(f'\n⏱️ Total Running Time: {duration:.2f} seconds')
```


## 🧭 AsyncIO 웹 스크래핑 + 파싱 절차 흐름 요약
### ① 준비 단계: 모듈 임포트 및 초기 설정
- 필요한 모듈을 불러온다:
- asyncio: 비동기 코루틴 실행
- timeit: 실행 시간 측정
- urlopen: 웹 요청 (동기 방식)
- ThreadPoolExecutor: 동기 함수를 비동기처럼 실행
- BeautifulSoup: HTML 파싱
- threading: 현재 쓰레드 확인용 (디버깅 목적)
```python
import asyncio, timeit, threading
from urllib.request import urlopen
from concurrent.futures import ThreadPoolExecutor
from bs4 import BeautifulSoup
```


### ② 타겟 URL 목록 정의
- 동시에 요청할 웹사이트 주소들을 리스트로 정의
```python
urls = ['http://daum.net', 'https://naver.com', ...]

```

### ③ 비동기 작업 함수 정의 (fetch)
- 각 URL에 대해 다음 작업을 수행:
- 현재 쓰레드 이름 출력 (디버깅용)
- urlopen()을 run_in_executor()로 비동기 실행
- 응답 HTML을 BeautifulSoup으로 파싱
- <title> 태그 추출 후 반환
```python
async def fetch(url, executor):
    res = await loop.run_in_executor(executor, urlopen, url)
    soup = BeautifulSoup(res.read(), 'html.parser')
    return soup.title.string if soup.title else 'No Title Found'
```


### ④ 메인 코루틴 정의 (main)
- 전체 작업을 관리하는 코루틴:
- ThreadPoolExecutor 생성
- 각 URL에 대해 fetch() 코루틴을 ensure_future()로 스케줄링
- asyncio.gather()로 모든 작업을 병렬 실행
- 결과 출력
```python
async def main():
    executor = ThreadPoolExecutor(max_workers=10)
    futures = [asyncio.ensure_future(fetch(url, executor)) for url in urls]
    results = await asyncio.gather(*futures)
```


### ⑤ 이벤트 루프 실행 및 시간 측정
- loop.run_until_complete(main())으로 코루틴 실행
- timeit으로 전체 실행 시간 측정
```python
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
duration = timeit.default_timer() - start

```


### ✅ 전체 흐름 요약

| 단계            | 설명                                                                 |
|-----------------|----------------------------------------------------------------------|
| 준비            | 필요한 모듈 임포트 및 URL 리스트 정의                                 |
| `fetch()`       | 각 URL에 대해 웹 요청 실행 (`urlopen`) + HTML 파싱 (`BeautifulSoup`) |
| `main()`        | 모든 `fetch()` 작업을 비동기로 스케줄링하고 `gather()`로 실행         |
| 결과 추출       | 각 HTML 문서에서 `<title>` 태그를 추출하여 결과 리스트로 반환         |
| 실행 및 측정    | `loop.run_until_complete()`로 코루틴 실행 + 전체 수행 시간 측정        |




## 📌 참고 사항
- urlopen()은 동기 함수이므로 aiohttp로 전환하면 더 효율적
- BeautifulSoup은 HTML 구조가 복잡한 사이트에서도 안정적으로 파싱 가능
- run_in_executor()는 기존 동기 함수를 비동기처럼 실행할 때 유용
- asyncio.gather()는 모든 작업이 완료될 때까지 기다림


## 전체 코드
```python
import asyncio
import timeit
from urllib.request import urlopen
from concurrent.futures import ThreadPoolExecutor
import threading

# 실행 시작 시간
start = timeit.default_timer()

# 서비스 방향이 비슷한 사이트로 실습 권장(예 : 게시판성 커뮤니티)
urls = ['http://daum.net', 'https://naver.com', 'http://mlbpark.donga.com/', 'https://tistory.com', 'https://wemakeprice.com/']

async def fetch(url, executor):
    # 쓰레드명 출력
    print('Thread Name :', threading.current_thread().name, 'Start', url)

    # 실행
    res = await loop.run_in_executor(executor, urlopen, url)
    print('Thread Name :', threading.current_thread().name, 'Done', url)

    # 결과 반환
    return res.read()[0:5]

async def main():

    # 쓰레드 풀 생성
    executor = ThreadPoolExecutor(max_workers=10)

    # future 객체 모아서 gather에서 실행
    futures = [
        asyncio.ensure_future(fetch(url, executor)) for url in urls
    ]
    
    # 결과 취합
    rst = await asyncio.gather(*futures)
    print()

    print('Result : ', rst)

if __name__ == '__main__':
    # 루프 초기화
    loop = asyncio.get_event_loop()

    # 작업 완료 까지 대기
    loop.run_until_complete(main())

    # 수행 시간 계산
    duration = timeit.default_timer() - start
    # 총 실행 시간
    print('Total Running Time : ', duration)

```
# loop.run_in_executor /asyncio.ensure_future/asyncio.gather/asyncio.get_event_loop

asyncio를 활용한 비동기 프로그래밍에서 자주 쓰이는 핵심 함수들—loop.run_in_executor, asyncio.ensure_future,  
asyncio.gather, asyncio.get_event_loop—이 각각 어떤 역할을 하는지 절차적으로 정리해볼게.

## 🧠 AsyncIO 핵심 함수 설명
### ① asyncio.get_event_loop()
- 역할: 현재 스레드에서 사용할 이벤트 루프를 가져옴
- 설명: 모든 코루틴은 이벤트 루프에서 실행되어야 하므로, 루프를 먼저 가져와야 함
- 사용 예시:

```python
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
```


### ② loop.run_in_executor(executor, func, *args)
- 역할: 동기 함수를 별도의 쓰레드나 프로세스에서 실행하여 비동기처럼 처리
- 설명:
- urlopen() 같은 블로킹 함수는 직접 await할 수 없음
- 대신 run_in_executor()로 쓰레드 풀에 넘겨서 병렬 처리
- 사용 예시:
```python
res = await loop.run_in_executor(executor, urlopen, url)
```


### ③ asyncio.ensure_future(coroutine)
- 역할: 코루틴을 Future 객체로 감싸서 스케줄링
- 설명:
- 코루틴을 실행 대기열에 등록
- gather()나 wait() 같은 함수에서 사용할 수 있도록 준비
- 사용 예시:
```python
futures = [asyncio.ensure_future(fetch(url, executor)) for url in urls]
```

###  ④ asyncio.gather(*futures)
- 역할: 여러 코루틴을 동시에 실행하고 결과를 리스트로 반환
- 설명:
- 모든 작업이 완료될 때까지 기다림
- 결과는 순서대로 정렬되어 반환됨
- 사용 예시:
```python
results = await asyncio.gather(*futures)
```


### ✅ 전체 흐름 요약
| 단계               | 함수                   | 역할 설명                                                                 |
|--------------------|------------------------|---------------------------------------------------------------------------|
| 이벤트 루프 준비   | `get_event_loop()`     | 현재 스레드에서 사용할 이벤트 루프를 가져옴                               |
| 동기 함수 비동기화 | `run_in_executor()`    | 블로킹 함수를 쓰레드/프로세스 풀에서 실행하여 비동기처럼 처리함           |
| 작업 스케줄링      | `ensure_future()`      | 코루틴을 `Future` 객체로 감싸서 이벤트 루프에 등록                        |
| 병렬 실행 및 수집  | `gather()`             | 여러 `Future`를 병렬로 실행하고 결과를 리스트로 반환                       |

---

## 🎁 Blackbox화 전략: 사용자 친화적 구조 만들기
### ✅ 1. 핵심 로직을 함수로 감싸기

복잡한 흐름을 하나의 함수로 추상화하면, 사용자는 내부 구조를 몰라도 쉽게 사용할 수 있음.
def scrape_titles(urls):
    loop = asyncio.get_event_loop()
    return loop.run_until_complete(_run_scraper(urls))


### ✅ 2. 내부 코루틴은 숨기기
실제 fetch, main, executor 등은 내부에서만 동작하게 하고, 외부에는 단순한 인터페이스만 제공.
```python
async def _run_scraper(urls):
    executor = ThreadPoolExecutor(max_workers=10)
    futures = [asyncio.ensure_future(_fetch(url, executor)) for url in urls]
    return await asyncio.gather(*futures)

async def _fetch(url, executor):
    res = await loop.run_in_executor(executor, urlopen, url)
    soup = BeautifulSoup(res.read(), 'html.parser')
    return soup.title.string if soup.title else 'No Title Found'
```            

### ✅ 3. 사용자는 이렇게만 쓰면 됨
```
urls = ['https://naver.com', 'https://daum.net']
titles = scrape_titles(urls)
print(titles)
```


### 🧠 장점

| 항목             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| 사용성 향상      | 복잡한 비동기 흐름을 함수 하나로 감싸 사용자에게 단순한 인터페이스 제공 |
| 유지보수 용이    | 내부 로직 변경 시 외부 사용 방식은 그대로 유지 가능                   |
| 테스트 편리      | 단일 함수 단위로 테스트 가능하여 안정성 확보                          |
| 확장성 확보      | 예외 처리, 로깅, 파싱 방식 변경 등 유연하게 추가 가능                 |
| `aiohttp` 전환   | `urlopen` 대신 `aiohttp` 사용 시 진정한 비동기 HTTP 요청 가능          |

---


