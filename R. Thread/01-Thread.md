# 🧠 Thread란?
- 하나의 프로세스 내에서 동시에 여러 작업을 수행할 수 있게 해주는 실행 단위.

## ✅ 특징
- 경량 프로세스: 메모리 공간을 공유함
- 병렬 처리: I/O 작업, 대기 시간이 많은 작업에 적합
- GIL(Global Interpreter Lock): Python에서는 한 번에 하나의 스레드만 실행됨 (CPU-bound 작업엔 제약)

## 📸 Thrread에서 발생하는  문제 요약
### 💥 문제: Race Condition (경쟁 상태)
```python
balance = 100
def withdraw(amount):
    global balance
    if balance >= amount:
        time.sleep(0.01)  # 의도적 지연
        balance -= amount

```

- 두 스레드가 동시에 balance를 읽고 수정함
- balance >= amount 조건을 통과했지만, 동시에 감소되어 잔고가 -25가 되는 오류 발생

## 🛠 개선 방법: Lock 사용
```python
import threading
import time

balance = 100
lock = threading.Lock()

def withdraw(amount):
    global balance
    with lock:  # 🔒 임계 영역 보호
        if balance >= amount:
            time.sleep(0.01)
            balance -= amount
            print(f"Withdrawal successful. Balance: {balance}")
        else:
            print("Insufficient balance.")
```

## ✅ 개선 효과
- with lock:을 통해 한 번에 하나의 스레드만 balance에 접근
- Race Condition 방지 → 잔고가 음수가 되는 문제 해결

## 🔍 Thread 주요 메서드 요약

| 메서드 / 속성       | 설명                                                                 |
|---------------------|----------------------------------------------------------------------|
| `start()`           | 스레드 실행 시작. 내부적으로 `run()` 메서드를 호출함                     |
| `join()`            | 해당 스레드가 종료될 때까지 메인 스레드가 기다림 → 동기화에 사용됨         |
| `daemon=True`       | 데몬 스레드로 설정. 메인 스레드가 종료되면 함께 종료됨 → 백그라운드 작업에 적합 |
| `is_alive()`        | 스레드가 아직 실행 중인지 확인 → 상태 모니터링에 유용                      |



## 🧪 실무에서 Thread가 유용한 경우

| 활용 분야             | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| 웹 크롤링 / 파일 다운로드 | 여러 URL 또는 파일을 동시에 처리 → 대기 시간 줄이고 속도 향상                     |
| GUI 응답 유지          | 백그라운드 작업을 스레드로 처리 → 사용자 인터페이스가 멈추지 않음                  |
| 실시간 데이터 처리      | 센서, 로그, 네트워크 패킷 등 지속적으로 들어오는 데이터를 병렬로 처리 가능           |
| 서버 요청 처리         | 다수의 클라이언트 요청을 동시에 처리 → 웹 서버, API 서버에서 응답 지연 최소화         |
| 테스트 자동화 / 병렬 실행 | 여러 테스트 케이스를 동시에 실행 → 테스트 시간 단축 및 효율 향상                   |



## 🧠 추가 팁: ThreadPoolExecutor (고급 스레딩)
```python
from concurrent.futures import ThreadPoolExecutor

def task(n):
    print(f"Task {n} running")

with ThreadPoolExecutor(max_workers=3) as executor:
    for i in range(5):
        executor.submit(task, i)
```

- 스레드 풀을 사용하면 스레드 관리가 자동화되고, 성능 최적화에 유리함


# Thread 정리

실무에서 많이 사용하는 Python의 Thread 기법들을 아래에 정리, 
각각에 맞는 샘플 코드를 함께 제공. 
특히 병렬 처리, 백그라운드 작업, 스레드 풀, 동기화 등 실무에서 자주 쓰이는 패턴 중심으로 구성.

## 🧵 1. 기본 Thread 실행
```python
from threading import Thread

def task():
    print("작업 시작")
    
t = Thread(target=task)
t.start()
t.join()
print("작업 완료")
```

### ✅ 기본 구조: start()로 실행, join()으로 대기

## 🔄 2. Daemon Thread (백그라운드 작업)
```python
from threading import Thread
import time

def background_task():
    while True:
        print("백그라운드 작업 중...")
        time.sleep(1)

t = Thread(target=background_task, daemon=True)
t.start()

time.sleep(3)
print("메인 종료 → 데몬 스레드도 종료됨")
```

### ✅ 특징: 메인 스레드가 종료되면 데몬 스레드도 함께 종료됨

## 🧠 3. ThreadPoolExecutor (스레드 풀)
```python
from concurrent.futures import ThreadPoolExecutor

def download(url):
    print(f"{url} 다운로드 중...")

urls = ['url1', 'url2', 'url3']
with ThreadPoolExecutor(max_workers=3) as executor:
    executor.map(download, urls)
```

### ✅ 실무 활용: 웹 크롤링, 파일 다운로드 등 병렬 작업에 최적

## 🔒 4. Lock을 활용한 동기화
```python
import threading
import time

balance = 100
lock = threading.Lock()

def withdraw(amount):
    global balance
    with lock:
        if balance >= amount:
            time.sleep(0.01)
            balance -= amount
            print(f"출금 성공! 잔고: {balance}")
        else:
            print("잔고 부족")

t1 = threading.Thread(target=withdraw, args=(50,))
t2 = threading.Thread(target=withdraw, args=(75,))
t1.start(); t2.start()
t1.join(); t2.join()
```

### ✅ 문제 해결: Race Condition 방지 → 잔고가 음수가 되는 오류 해결

## 🕒 5. Timer Thread (지연 실행)
```python
from threading import Timer

def delayed_task():
    print("3초 후 실행됨")

t = Timer(3.0, delayed_task)
t.start()
```

### ✅ 활용 예시: 예약 작업, 알림, 자동 저장 기능 등

## 🧪 6. 실시간 모니터링 스레드
```python
import threading
import time

def monitor():
    while True:
        print("시스템 상태 확인 중...")
        time.sleep(2)

monitor_thread = threading.Thread(target=monitor, daemon=True)
monitor_thread.start()

for i in range(5):
    print(f"메인 작업 {i}")
    time.sleep(1)
```

### ✅ 활용 예시: 서버 상태 체크, 센서 데이터 수집, 로그 모니터링

## 📌 실무 Thread 활용 팁 요약

| 기법 / 패턴              | 실무 활용 예시 및 장점                                                |
|--------------------------|-----------------------------------------------------------------------|
| 기본 Thread 사용          | 병렬 작업 처리, UI 응답 유지, 단순한 백그라운드 작업에 적합                   |
| Daemon Thread            | 로그 감시, 자동 백업, 센서 모니터링 등 → 메인 종료 시 자동 종료됨             |
| ThreadPoolExecutor       | 대량의 작업을 효율적으로 병렬 처리 → 웹 크롤링, 이미지 처리, 다운로드 등       |
| Lock / RLock 동기화      | 공유 자원 보호 → 금융 시스템, 재고 관리, 동시성 문제 해결에 필수               |
| Timer Thread             | 예약 작업, 자동 저장, 알림 시스템 등 → 일정 시간 후 실행되는 작업에 적합        |
| 실시간 모니터링 스레드     | 서버 상태 체크, 실시간 로그 분석, 센서 데이터 수집 등 → 지속적 감시 작업에 유용     |
| is_alive() / join() 활용 | 스레드 상태 확인 및 동기화 → 작업 완료 여부 확인, 안전한 종료 처리 가능         |

---



