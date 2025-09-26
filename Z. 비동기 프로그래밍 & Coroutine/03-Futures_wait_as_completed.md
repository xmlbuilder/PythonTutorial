# 🔄 Futures 두 번째 단계
wait() vs as_completed()

## 🎯 목적
submit()으로 스케줄링한 비동기 작업들을 효율적으로 관리하고 결과를 수집하기 위한 고급 API.

## 🧩 핵심 함수 비교
| 함수              | 설명                                                                 |
|-------------------|----------------------------------------------------------------------|
| `wait()`          | 모든 작업이 완료되거나 타임아웃이 발생할 때까지 기다림               |
|                   | 완료된 작업(`done`)과 미완료 작업(`not_done`)을 분리해서 반환         |
| `as_completed()`  | 완료된 작업을 순차적으로 반환함 → 결과를 빠르게 처리 가능             |
|                   | 작업이 완료되는 즉시 결과를 가져올 수 있어 스트리밍 처리에 유리       |


## 🧪 실습 코드 요약

### 공통 코드
```python
import os
import time
from concurrent import futures
WORK_LIST = [10000000, 1000000, 1000000, 1000000, 1000000,]
# 누적 햡계 함수
def sum_generator(n):
    return sum(n for n in range(1, n+1))
```

### 1. wait() 사용 예시

```python
result = futures.wait(futures_list, timeout=1.0)
print("Completed Tasks:", result.done)
print("Pending Tasks:", result.not_done)
print([future.result() for future in result.done])
```
#### 출력 결과
```
Result -> [{<Future at 0x106ab5ca0 state=finished returned int>, 
<Future at 0x106ab5730 state=finished returned int>, 
<Future at 0x106ab5760 state=finished returned int>, 
<Future at 0x106ab5970 state=finished returned int>, 
<Future at 0x106ab4b90 state=finished returned int>}, set()] Time : 0.80s
```

- wait()은 모든 작업을 기다리는 게 아니라, 타임아웃 내에 완료된 작업만 반환
- result.done과 result.not_done으로 작업 상태를 분리해서 확인 가능
- 타임아웃이 작동하지 않는 경우는 OS나 작업 크기, 프로세스 스케줄링에 따라 발생할 수 있음

### 2. as_completed() 사용 예시
```python
for future in futures.as_completed(futures_list, timeout=0.1):
    result = future.result()
    print('Future Result:', result)
```

- as_completed()는 작업이 끝나는 순서대로 결과를 반환
- 빠르게 끝나는 작업부터 처리 가능 → 실시간 처리에 적합
- 타임아웃이 작동하지 않는 경우는 내부적으로 next() 호출 시 예외가 발생하지 않기 때문

⚠️ 타임아웃이 작동하지 않는 이유?
- ProcessPoolExecutor는 작업이 완료되기 전까지 result()를 반환하지 않음
- 타임아웃은 작업 자체가 너무 빨리 끝나거나 너무 오래 걸릴 경우 무시될 수 있음
- 해결 방법:
- future.result(timeout=...)로 개별 Future에 타임아웃 설정
- ThreadPoolExecutor로 바꿔서 테스트해보기

### ✅ 정리

| 기능               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `wait()`           | 모든 작업이 완료되거나 타임아웃이 발생할 때까지 기다림               |
|                    | 완료된 작업(`done`)과 미완료 작업(`not_done`)을 분리해서 반환         |
| `as_completed()`   | 완료된 작업을 순차적으로 반환함 → 빠른 작업부터 처리 가능             |
|                    | 스트리밍 처리나 실시간 응답에 적합                                   |
| `future.result()`  | 개별 작업의 결과를 반환함                                             |
|                    | 타임아웃을 설정하여 작업 실패나 지연을 제어할 수 있음                |



## 전체 코드
```python
import os
import time
from concurrent import futures

WORK_LIST = [10000000, 1000000, 1000000, 1000000, 1000000,]
# 동시성 합계 계산 메인 함수
# 누적 햡계 함수
def sum_generator(n):
    return sum(n for n in range(1, n+1))

# submit
def main():
    cntWorker = min(10, len(WORK_LIST))
    start = time.time()

    futures_list = []
    with futures.ProcessPoolExecutor(max_workers=cntWorker) as executor:

        for work in WORK_LIST:
            # future 반환
            future  = executor.submit(sum_generator, work)

            # 스케쥴링
            futures_list.append(future)

            print('Scheduled for {} : {}'.format(work, future))
    end = time.time() - start
    msg = '\n Result -> {} Time : {:.2f}s'
if __name__ == '__main__':
    main()



# 2. wait  
import os
import time
from concurrent import futures
WORK_LIST = [10000000, 1000000, 1000000000, 1000000000000, 1000000000,]
# 동시성 합계 계산 메인 함수
# 누적 햡계 함수
def sum_generator(n):
    return sum(n for n in range(1, n+1))

def main():
    cntWorker = min(10, len(WORK_LIST))
    start = time.time()
    futures_list = []
    with futures.ProcessPoolExecutor(max_workers=cntWorker) as executor:
        for work in WORK_LIST:
            # future 반환
            future  = executor.submit(sum_generator, work)
            # 스케쥴링
            futures_list.append(future)
    

    result = futures.wait(futures_list, timeout = 1.0)
    print("Completed Tasks : ", str(result.done))
    print("Pending ones for waiting for 7 secs : ", str(result.not_done))
    print([future.result() for future in result.done])
    end = time.time() - start
    msg = '\n Result -> {} Time : {:.2f}s'
    print(msg.format(list(result), end))

if __name__ == '__main__':
    main()



# 3. as_completed
import os
import time
from concurrent import futures
WORK_LIST = [100, 10000, 1000000000, 10000, 10,]
def sum_generator(n):
    return sum(n for n in range(1, n+1))

def main():
    cntWorker = min(10, len(WORK_LIST))
    start = time.time()
    futures_list = []
    with futures.ProcessPoolExecutor(max_workers=cntWorker) as executor:
        for work in WORK_LIST:
            # future 반환
            future  = executor.submit(sum_generator, work)
            # 스케쥴링
            futures_list.append(future)

    for future in futures.as_completed(futures_list, timeout=0.1):
        result = future.result()
        done = future.done()
        cancelled = future.cancelled()
        print('Future Result : {}, Done {}'.format(result, done))
        print('Future Cancelled : {}'.format(cancelled))

    end = time.time() - start
    msg = '\n Result -> {} Time : {:.2f}s'

if __name__ == '__main__':
    main()


```