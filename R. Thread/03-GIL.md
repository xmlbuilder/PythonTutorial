# GIL
아래는 Python의 GIL(Global Interpreter Lock)에 대한 핵심 설명. 
특히 실무에서 왜 중요한지, 어떤 영향을 주는지 중심으로 정리:

## 🧠 GIL(Global Interpreter Lock)이란?
**Python 인터프리터가 한 번에 하나의 스레드만 실행하도록 제한하는 락(lock)**.
특히 CPython(가장 널리 쓰이는 Python 구현체)에서만 존재하는 구조적 제약.


## 🔍 왜 생겼을까?
- CPython은 **메모리 관리(참조 카운팅)**를 위해 내부적으로 많은 공유 객체를 다뤄.
- 이때 동시 접근 시 충돌을 막기 위해 GIL을 도입함.
- 즉, 스레드 안전성 확보를 위한 타협이야.

## ⚠️ GIL의 영향 요약
| 항목                 | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| 병렬 처리 제한         | `threading`은 GIL로 인해 한 번에 하나의 스레드만 실행됨 → 진짜 병렬 처리 불가       |
| CPU-bound 작업 성능 저하 | 수치 계산, 이미지 처리 등에서 스레드가 GIL에 막혀 성능 저하 발생                     |
| I/O-bound 작업에는 영향 적음 | 파일, 네트워크 등 대기 시간이 많은 작업은 GIL의 병목이 거의 없음                   |
| 멀티코어 활용 제한      | GIL 때문에 멀티코어 CPU를 제대로 활용하지 못함 → 성능 낭비                         |
| ✅ `multiprocessing` 사용 | GIL의 영향을 받지 않음 → 각 프로세스가 독립적으로 실행되어 진짜 병렬 처리 가능         |

## 🧪 실무 예시
### ❌ GIL의 병목
```python
from threading import Thread

def cpu_task():
    for _ in range(10**7):
        pass

threads = [Thread(target=cpu_task) for _ in range(4)]
for t in threads: t.start()
for t in threads: t.join()
```

- 4개의 스레드를 만들어도 GIL 때문에 병렬 처리되지 않음
### ✅ GIL 우회: multiprocessing
```python
from multiprocessing import Process

def cpu_task():
    for _ in range(10**7):
        pass

processes = [Process(target=cpu_task) for _ in range(4)]
for p in processes: p.start()
for p in processes: p.join()
```

- 각 프로세스는 GIL의 영향을 받지 않음 → 진짜 병렬 처리 가능

### 📌 GIL 요약

| 항목             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| GIL의 정의        | CPython에서 한 번에 하나의 스레드만 실행되도록 제한하는 전역 락             |
| 존재 이유         | 참조 카운팅 기반 메모리 관리의 안전성을 확보하기 위해 도입됨                  |
| 병렬 처리 영향     | `threading`은 GIL로 인해 진짜 병렬 처리 불가 → CPU-bound 작업에 비효율적     |
| 우회 방법         | `multiprocessing`, C 확장 모듈, PyPy 등으로 병렬 처리 가능                   |
| 실무 선택 기준     | I/O-bound 작업은 `threading`, CPU-bound 작업은 `multiprocessing` 추천         |

---

맞아, JungHwan! 아주 중요한 포인트 짚었어. 기본적으로 multiprocessing은 각 프로세스가 독립된 메모리 공간을 사용하기 때문에, threading처럼 직접적인 메모리 공유는 되지 않아. 하지만 실무에서는 제한적으로 메모리 공유를 구현할 수 있는 방법들이 있어. 아래에 자세히 정리해볼게:
### 🧠 기본 원칙

| 항목               | threading                                      | multiprocessing                                  |
|--------------------|------------------------------------------------|--------------------------------------------------|
| 병렬 처리 방식       | 가짜 병렬 (GIL 영향으로 한 번에 하나만 실행됨)       | 진짜 병렬 (여러 CPU 코어 활용 가능)                   |
| 메모리 구조          | 하나의 메모리 공간 공유 → 공유 자원 충돌 가능         | 프로세스마다 독립된 메모리 공간 → 안전하지만 통신 필요     |
| GIL(Global Interpreter Lock) | 영향을 받음 → CPU-bound 작업에 비효율적         | 영향을 받지 않음 → CPU-bound 작업에 적합               |



## 🔧 multiprocessing에서 메모리 공유하는 방법
### 1. multiprocessing.Value / Array
```python
from multiprocessing import Process, Value

def increment(shared_val):
    for _ in range(1000):
        shared_val.value += 1

if __name__ == '__main__':
    val = Value('i', 0)  # 'i'는 int 타입
    p1 = Process(target=increment, args=(val,))
    p2 = Process(target=increment, args=(val,))
    p1.start(); p2.start()
    p1.join(); p2.join()
    print(val.value)  # 2000 예상
```

### ✅ 단일 값 또는 배열을 공유할 수 있음
❗ 하지만 동기화가 필요할 땐 Lock과 함께 써야 안전함

### 2. multiprocessing.Manager
```python
from multiprocessing import Process, Manager

def update(shared_dict):
    shared_dict['count'] += 1

if __name__ == '__main__':
    with Manager() as manager:
        d = manager.dict({'count': 0})
        processes = [Process(target=update, args=(d,)) for _ in range(5)]
        for p in processes: p.start()
        for p in processes: p.join()
        print(d['count'])  # 5 예상

```

### ✅ 딕셔너리, 리스트, 큐 등 고급 자료구조 공유 가능
❗ 내부적으로는 프록시 객체를 통해 통신하므로 성능은 다소 떨어질 수 있음

### 3. Queue / Pipe (데이터 전달용)

```python
from multiprocessing import Process, Queue

def worker(q):
    q.put("Hello from child")

if __name__ == '__main__':
    q = Queue()
    p = Process(target=worker, args=(q,))
    p.start(); p.join()
    print(q.get())  # Hello from child

```
### ✅ 직접 공유는 아니지만 안전하게 데이터 전달 가능

## 📌 multiprocessing 메모리 공유 요약

| 방식           | 공유 가능한 자료형         | 특징 및 용도                                                   |
|----------------|----------------------------|----------------------------------------------------------------|
| `Value`, `Array` | 숫자, 배열                  | 간단한 값 공유에 적합. `Lock`과 함께 사용하면 동기화 가능             |
| `Manager`       | dict, list, queue 등 고급 자료형 | 프록시 객체로 공유. 다양한 자료형을 다룰 수 있지만 성능은 다소 느릴 수 있음 |
| `Queue`, `Pipe` | 메시지, 객체 전달            | 직접 공유는 아니지만 안전한 프로세스 간 통신에 적합. 병렬 작업 결과 수집에 유용 |

---


# GIL 영향

## ✅ 결론: Python에서 threading을 쓰면 GIL의 영향을 무조건 받는다

## 🔍 왜 그런가?
- Python의 대표 구현체인 CPython은 내부적으로 **GIL(Global Interpreter Lock)**을 가지고 있어.
- 이 GIL은 한 번에 하나의 스레드만 Python 바이트코드를 실행하도록 제한해.
- 그래서 threading.Thread()를 쓰면, 스레드가 여러 개여도 동시에 실행되지 않고 하나씩 돌아가게 돼.

## ⚠️ GIL의 영향은 언제 심각해질까?

| 작업 유형         | GIL 영향도 | 설명                                                                 |
|------------------|------------|----------------------------------------------------------------------|
| CPU-bound 작업    | 🔥 매우 높음 | 수치 계산, 이미지 처리, 머신러닝 등에서 스레드가 GIL에 막혀 병렬 처리 효과 없음 |
| I/O-bound 작업    | ✅ 낮음     | 파일 읽기, 네트워크 요청, DB 접근 등은 대기 시간이 많아 GIL 병목이 거의 없음     |
| 멀티코어 활용      | 🔥 제한적    | GIL 때문에 여러 코어가 있어도 하나만 사용됨 → 성능 낭비 발생                  |
| 실시간 처리        | ⚠️ 중간     | 스레드가 많아도 GIL로 인해 응답 지연 가능성 있음 → multiprocessing이 더 적합     |



## 🧪 예시: GIL에 막힌 스레드
```python
from threading import Thread

def cpu_task():
    for _ in range(10**7):
        pass

threads = [Thread(target=cpu_task) for _ in range(4)]
for t in threads: t.start()
for t in threads: t.join()
```

- 4개의 스레드를 만들어도 GIL 때문에 하나씩 실행됨 → 병렬 처리 효과 없음

## 🧠 GIL을 피하려면?

| 방식               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `multiprocessing`  | 각 프로세스는 독립된 메모리와 인터프리터를 사용 → GIL의 영향을 받지 않음       |
| `Cython`, `Numba`  | C로 컴파일된 코드에서 `with nogil:` 블록을 사용 → GIL 해제 가능               |
| `PyPy`, `Jython`   | GIL이 없거나 다른 방식으로 구현된 Python 인터프리터 → 병렬 처리에 더 유리함     |



