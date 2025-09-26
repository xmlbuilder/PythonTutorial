# 🧵 Python 동시성 프로그래밍: concurrent.futures 활용 예제
## 🚀 개요
Python에서 비동기 작업을 효율적으로 처리하기 위해 concurrent.futures 모듈을 활용한 동시성 프로그래밍을 소개합니다.  
특히 파일 I/O, 네트워크 작업처럼 지연 시간이 큰 작업에서 CPU 리소스를 낭비하지 않고 성능을 극대화할 수 있습니다.
## 🔧 기존 방식의 한계
- threading, multiprocessing 모듈은 설정이 복잡하고 관리가 어렵습니다.
- GIL(Global Interpreter Lock)로 인해 멀티스레딩의 성능이 제한될 수 있습니다.
- 두 개 이상의 스레드가 하나의 자원을 동시에 접근할 경우 GIL이 전체 리소스를 잠금 → 문맥 교환(Context Switch) 발생
- 이 경우 multiprocessing을 통해 병렬 처리로 우회 가능

## #✅ concurrent.futures 장점
- 고수준 API 제공으로 사용이 간편함
- 멀티스레딩과 멀티프로세싱 API 통일
- 작업 취소, 완료 여부 체크, 타임아웃, 콜백 등 Promise 개념을 쉽게 구현 가능

## 🧪 실습 코드
import time
from concurrent import futures

# 테스트용 작업 리스트
WORK_LIST = [100000000, 1000000, 1000000, 1000000000, 10000000000]

# 누적 합계 계산 함수
```python
def sum_generator(n):
    return sum(n for n in range(1, n + 1))

def main():
    cntWorker = min(10, len(WORK_LIST))
    start = time.time()
    # ''' Result -> [500000500000, ...] Time : 약 0.20s '''



    # 멀티프로세싱 예시
    with futures.ProcessPoolExecutor(max_workers=cntWorker) as executor:
        results = executor.map(sum_generator, WORK_LIST)
    # ''' Result -> [500000500000, ...] Time : 약 0.52s '''
    
    

    end = time.time() - start
    print(f"\nResult -> {list(results)} Time : {end:.2f}s")

if __name__ == '__main__':
    main()
```


📌 참고 사항
- ThreadPoolExecutor는 I/O 바운드 작업에 적합
- ProcessPoolExecutor는 CPU 바운드 작업에 적합
- executor.map()은 입력 리스트를 병렬로 처리하며 결과를 순서대로 반환

---

# concurrent.futures의 원리
좋아, JungHwan! concurrent.futures의 원리를 좀 더 깊이 다룸. 
이 모듈은 Python에서 **동시성(concurrency)**을 쉽게 구현할 수 있도록 도와주는 고수준 API. 
핵심 개념은 Executor, Future, 그리고 비동기 실행 흐름.

## 🔍 핵심 구성 요소
### 1. Executor 클래스
- 작업을 실행할 스레드 풀 또는 프로세스 풀을 관리하는 객체야.
- 두 가지 구현체가 있어:
- ThreadPoolExecutor: I/O 바운드 작업에 적합 (예: 파일 읽기, 네트워크 요청)
- ProcessPoolExecutor: CPU 바운드 작업에 적합 (예: 수학 계산, 이미지 처리)
```python
executor = ThreadPoolExecutor(max_workers=5)
```


### 2. Future 객체
- 비동기 작업의 결과를 담는 컨테이너야.
- 작업이 완료되면 결과를 조회하거나, 예외를 확인할 수 있어.
- 마치 JavaScript의 Promise처럼 작동해.
```python
future = executor.submit(some_function, arg1, arg2)
result = future.result()  # 블로킹 호출, 작업 완료까지 기다림
\```

### 3. `submit()` vs `map()`

| 메서드     | 설명                                      |
|------------|-------------------------------------------|
| `submit()` | 개별 작업을 `Future` 객체로 반환함        |
|            | 작업 상태 추적 가능                       |
|            | 결과는 `.result()`로 조회                 |
| `map()`    | 여러 작업을 병렬로 실행                   |
|            | 결과를 순서대로 반환                      |
|            | 리스트처럼 다룰 수 있음                   |

# submit 예시
```python
futures = [executor.submit(sum_generator, n) for n in WORK_LIST]
results = [f.result() for f in futures]
```

# map 예시
```rust
results = executor.map(sum_generator, WORK_LIST)
```


## ⚙️ 작동 원리 요약
- Executor가 작업을 워커(worker)에게 분배
- 각 워커는 작업을 병렬로 실행
- Future 객체는 작업의 상태(진행 중, 완료, 실패 등)를 추적
- 결과를 .result() 또는 map()으로 수집

## 🧠 GIL과의 관계
- Python의 GIL(Global Interpreter Lock) 때문에 멀티스레딩은 CPU 병렬 처리에 한계가 있어.
- 그래서 CPU 바운드 작업은 ProcessPoolExecutor로 우회하는 게 좋아.
- GIL은 스레드 간 자원 충돌을 막기 위한 CPython의 안전장치야.

## 🧩 비동기 흐름 예시
```python
from concurrent.futures import ThreadPoolExecutor

def task(n):
    print(f"작업 {n} 시작")
    return n * 2

with ThreadPoolExecutor(max_workers=3) as executor:
    future = executor.submit(task, 10)
    print(f"결과: {future.result()}")

```

---

# ❓ 왜 ProcessPoolExecutor가 더 느릴까?
## 🔍 실험 결과 요약
- ThreadPoolExecutor: 약 0.20초
- ProcessPoolExecutor: 약 0.52초
    - 멀티프로세싱이 더 느리게 나옴

### 📌 이유 설명

| 항목                     | 설명                                                                 |
|--------------------------|----------------------------------------------------------------------|
| `ProcessPoolExecutor`    | 프로세스 생성 비용이 크고, 작업 결과를 수집하는 데 IPC 비용이 발생함 |
| `WORK_LIST`              | 작업 크기 편차가 커서 병렬 효율이 떨어질 수 있음                    |
| `sum_generator(1000000)` | 작은 작업은 멀티프로세싱 오버헤드가 더 커서 오히려 느려질 수 있음   |
| `ThreadPoolExecutor`     | GIL의 영향이 있지만, 단순 계산 작업에서는 병목이 크지 않음           |


## ✅ 사용자에게 전달할 메시지 예시
멀티프로세싱이 항상 빠른 건 아닙니다. 작업의 크기, 성격, 병렬화 비용에 따라 오히려 느려질 수 있습니다.
작은 계산 작업이나 I/O 중심 작업이라면 ThreadPoolExecutor가 더 효율적일 수 있습니다.
반면, CPU를 많이 사용하는 대규모 작업에서는 ProcessPoolExecutor가 더 나은 성능을 보입니다.

---



