#  Thread Lock
Python의 Thread Lock에 대해 실무 중심으로 아주 자세히 설명. 
특히 동시성 문제, Race Condition, Lock의 종류와 사용법까지 정리\.

## 🔒 Thread Lock이란?
여러 스레드가 공유 자원에 동시에 접근할 때 발생할 수 있는 충돌(Race Condition)을 방지하기 위한 동기화 도구.

Python에서는 threading.Lock()을 사용해서 한 번에 하나의 스레드만 자원에 접근하도록 제한할 수 있음.

### ⚠️ 왜 필요한가?
예시: Race Condition 발생
```python
import threading

counter = 0

def increment():
    global counter
    for _ in range(100000):
        counter += 1

t1 = threading.Thread(target=increment)
t2 = threading.Thread(target=increment)
t1.start(); t2.start()
t1.join(); t2.join()
print(counter)  # 예상: 200000 → 실제: 불안정
```

### ✅ 두 스레드가 동시에 counter를 수정하면서 값이 꼬일 수 있음

## ✅ 해결: Lock 사용

```python
import threading

counter = 0
lock = threading.Lock()

def increment():
    global counter
    for _ in range(100000):
        with lock:
            counter += 1

t1 = threading.Thread(target=increment)
t2 = threading.Thread(target=increment)
t1.start(); t2.start()
t1.join(); t2.join()
print(counter)  # 정확히 200000
```

### 🔐 with lock: 블록 안에서는 다른 스레드가 접근할 수 없음 → 안전한 동기화

## 🔄 Lock의 주요 메서드

| 메서드 / 구문       | 설명                                                                 |
|---------------------|----------------------------------------------------------------------|
| `lock.acquire()`     | Lock을 수동으로 획득함. 다른 스레드는 대기 상태로 들어감                     |
| `lock.release()`     | Lock을 수동으로 해제함. 다음 대기 중인 스레드가 접근 가능                     |
| `with lock:`         | `acquire()`와 `release()`를 자동으로 처리하는 안전한 구문 → 예외 발생 시에도 안정적 |


## 🧠 Lock의 종류

| 종류         | 설명                                                                 |
|--------------|----------------------------------------------------------------------|
| `Lock`       | 가장 기본적인 락. 한 번에 하나의 스레드만 자원에 접근 가능. 공유 자원 보호에 사용됨     |
| `RLock`      | 재진입 가능한 락. 동일한 스레드가 여러 번 `acquire()` 가능 → 재귀 함수나 중첩 락에 유용 |
| `Semaphore`  | 제한된 수의 스레드만 접근 가능. 예: 최대 3개 동시 다운로드 → 동시성 제어에 적합         |
| `Condition`  | 특정 조건이 만족될 때까지 스레드 대기. `wait()`와 `notify()`로 제어 → 생산자-소비자 패턴에 사용 |
| `Event`      | 스레드 간 신호 전달에 사용. `set()`, `clear()`, `wait()`로 상태 제어 → 작업 시작/중단 제어에 유용 |

## 📌 실무 Lock 선택 팁

| 상황 / 용도               | 추천 방식           | 설명                                                                 |
|---------------------------|---------------------|----------------------------------------------------------------------|
| 단순한 공유 자원 보호        | `Lock`              | 가장 기본적인 락. 한 번에 하나의 스레드만 접근 가능 → 충돌 방지에 적합         |
| 재귀 함수 / 중첩 락 구조     | `RLock`             | 동일한 스레드가 여러 번 락을 획득 가능 → 재진입이 필요한 구조에 유용           |
| 동시 접근 수 제한 (예: API 호출) | `Semaphore`         | 최대 접근 수를 제한 → 과도한 동시 실행 방지, 자원 보호에 효과적               |
| 조건 기반 대기 / 알림        | `Condition`, `Event` | 특정 조건 만족 시 작업 진행 → 생산자-소비자 패턴, 작업 시작/중단 제어에 적합     |

## 🧪 실무 예시: 파일 접근 동기화

```python
import threading

lock = threading.Lock()

def write_to_file(filename, text):
    with lock:
        with open(filename, 'a') as f:
            f.write(text + '\n')

threads = [threading.Thread(target=write_to_file, args=('log.txt', f'Line {i}')) for i in range(10)]
for t in threads: t.start()
for t in threads: t.join()
```

### ✅ 여러 스레드가 동시에 파일에 쓰더라도 충돌 없이 안전하게 처리됨

---

# GIL / Thread

GIL 때문에 Python의 threading이 진짜 병렬 처리에 불리한 건 맞지만, “Thread가 안 된다”는 건 절대 아님.  
오히려 특정 상황에서는 매우 유용.

### 🔍 GIL이 있어도 Thread가 필요한 이유
### 1. I/O-bound 작업에서는 여전히 효과적
- GIL은 CPU를 사용할 때만 병목을 만들고,
- 파일 읽기, 네트워크 요청, DB 접근처럼 대기 시간이 많은 작업에서는
스레드가 GIL을 잠깐 놓고 다른 스레드가 실행됨.
- 결과적으로 동시성 효과가 충분히 있음.
#### ✅ 예: 웹 크롤링, API 호출, 로그 수집, 파일 다운로드

### 2. GUI 응답 유지에 필수
- GUI 앱에서 백그라운드 작업을 threading으로 처리하면
메인 UI가 멈추지 않고 사용자 입력에 반응할 수 있어.
#### ✅ 예: PyQt, Tkinter, Kivy 기반 앱

### 3. 경량 작업 병렬 처리
- GIL이 있다고 해도, 작업이 가볍고 빠르면 스레드가 더 효율적일 수 있어.
- multiprocessing은 프로세스 생성 비용이 크기 때문에
작은 작업에는 오히려 느릴 수 있음.
#### ✅ 예: 로그 파싱, 간단한 텍스트 처리, 이벤트 감시

### 4. 스레드 간 메모리 공유가 쉬움
- threading은 공유 메모리 공간을 사용하므로
Lock, Queue, Condition 등으로 쉽게 협업 가능.
- 반면 multiprocessing은 메모리 분리되어 통신이 더 복잡함.
#### ✅ 예: 실시간 상태 공유, 캐시 처리, 세션 관리

## 📌 요약: GIL이 있어도 Thread는 실무에서 충분히 가치 있음
| 작업 유형               | 추천 방식       | 이유                                                                 |
|------------------------|----------------|----------------------------------------------------------------------|
| 웹 크롤링, 파일 다운로드 | `threading`    | I/O-bound 작업은 GIL 영향 적음 → 병렬 처리 효과 충분                     |
| 이미지 처리, 수치 계산   | `multiprocessing` | CPU-bound 작업은 GIL 우회 필요 → 진짜 병렬 처리 가능                     |
| GUI 응답 유지            | `threading`    | 백그라운드 작업을 분리해 UI 멈춤 방지 → 사용자 경험 향상                  |
| 실시간 로그 감시         | `threading`    | 경량 작업을 빠르게 처리 가능 → 메모리 공유도 쉬움                         |

즉, GIL은 제약이지만 무조건적인 단점은 아니고, 상황에 따라 threading은 여전히 가볍고 강력한 도구
---
