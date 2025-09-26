# 🧠 Python Coroutine 핵심 요약
✅ 코루틴이란?
- 서브루틴: 메인 루틴이 서브루틴을 호출 → 서브루틴 끝나면 메인으로 복귀
- 코루틴: 실행 중인 루틴을 yield로 중단하고, 다시 재개 가능
   - 동시성 프로그래밍에 적합
   - 싱글 스레드 기반 비동기 처리 가능

✅ Thread
- 쓰레드 : OS 관리, CPU 코어에서 실시간, 시분할 비동기 작업 -> 멀티 쓰레드
    - 쓰레드 : 싱글쓰레드 -> 멀티스레드 -> 복잡 -> 공유 되는 자원 -> 교착 상태 발생, 컨텍스트 스위칭 비용 발생, 자원 소비 가능성 증가


## ✅ Coroutine vs Thread

| 항목             | Coroutine (코루틴)                                  | Thread (쓰레드)                                      |
|------------------|-----------------------------------------------------|------------------------------------------------------|
| 실행 방식        | 싱글 스레드, 스택 기반                              | OS 관리, 멀티 스레드                                 |
| 상태 전환        | `yield`로 직접 제어                                 | 컨텍스트 스위칭                                      |
| 자원 소비        | 낮음                                                | 높음 (락, 스케줄링 등)                               |
| 동시성 처리      | 협력형 (cooperative)                                | 선점형 (preemptive)                                  |
| 복잡도           | 낮음                                                | 높음 (교착 상태, 공유 자원 관리 필요)               |
| 흐름 제어 방식   | 루틴 중단 → 재개 가능 (`yield`, `send`)            | 루틴 간 전환은 OS가 관리                             |
| 오버헤드         | 적음                                                | 많음 (스택, 스레드 생성 비용 등)                    |
| 예시             | `def coroutine(): yield`                            | `std::thread`, `pthread_create()`                   |

## ✅ Coroutine 상태

| 상태          | 설명                         |
|---------------|------------------------------|
| GEN_CREATED   | 생성됨, 아직 시작되지 않음   |
| GEN_RUNNING   | 현재 실행 중                 |
| GEN_SUSPENDED | `yield`에서 대기 중          |
| GEN_CLOSED    | 종료됨 (`StopIteration` 발생) |


## 🔧 코드 흐름 요약
### ▶️ 기본 코루틴 구조
```python
def coroutine1():
    print('coroutine started')
    i = yield
    print(f'coroutine received: {i}')
```

- next()로 시작 → yield에서 멈춤
- send(value)로 값 전달 → 이후 코드 실행
⚠️ send()는 next()로 먼저 시작한 후에만 가능


### ▶️ 양방향 통신 예제
```python
def coroutine2(x):
    print(f'coroutine started: {x}')
    y = yield x
    print(f'received: {y}')
    z = yield x + y
    print(f'received: {z}')
    yield x + y + z

```

- yield는 값을 반환하면서 대기
- send()로 값을 전달하면 다음 yield까지 실행됨

### ▶️ yield from 문
```python
def generator2():
    yield from 'AB'
    yield from range(1, 4)
```

- 하위 이터러블을 자동으로 순회
- C++에서는 for 루프로 직접 구현해야 함

## 🔁 C++ 포팅 전략
### ✅ Python Coroutine 문법 대응표

| Python 문법     | C++ 대응 방식                          |
|------------------|----------------------------------------|
| `yield`          | 상태 기반 반복자, `co_yield` (C++20)   |
| `send()`         | 상태 객체에 값 전달, 커스텀 핸들러     |
| `yield from`     | `for` 루프를 통한 반복자 위임         |
| `async/await`    | `co_await`, `co_yield`, `std::future` |

C에서는 boost::coroutine, cppcoro, 또는 C20 coroutine을 활용 가능


## ✨ 결론
Python의 코루틴은 비동기 흐름을 명확하게 제어할 수 있는 구조이며,
C++에서는 이를 상태 기반 반복자 또는 coroutine 라이브러리로 포팅할 수 있습니다.


## 전체 코드
```python
def coroutine1():
    print('coroutine started')
    i = yield
    print('coroutine received: {}'.format(i))
# 메인 루틴
# 제너레이터 선언
cr1 = coroutine1()
print(cr1, type(cr1))
'''<generator object coroutine1 at 0x1015b20c0> <class 'generator'>'''
next(cr1)
'''
coroutine started
'''
#next(cr1)
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 23, in <module>
    next(cr1)
StopIteration
coroutine received: None
'''
# 기본 전달 값 None
# 값 전송
cr1.send(100)
'''
coroutine received: 100
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 35, in <module>
    cr1.send(100)
StopIteration
'''
cr2 = coroutine1()
cr2.send(100)
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 48, in <module>
    cr2.send(100)
TypeError: can't send non-None value to a just-started generator
<generator object coroutine1 at 0x1017920c0> <class 'generator'>
coroutine started
'''

# GEN_CREATED : 처음 대기 상태
# GEN_RUNNING: 실행 상태
# GEN_SUSPENDED: Yield 대기 상태
# GEN_CLOSED : 실행 완료 상태
def coroutine2(x):
    print('coroutine started : {}'.format(x))
    y = yield x
    print('coroutine received: {}'.format(y))
    z = yield x + y
    print('coroutine received: {}'.format(z))
    yield x + y + z
from inspect import getgeneratorstate
cr2 = coroutine2(10)
print(next(cr2))
'''
coroutine started : 10
10
'''
print(cr2.send(100))
'''
coroutine received: 100
110
'''
print(cr2.send(200))
'''
coroutine received: 200
310
'''
cr3 = coroutine2(10)
print(getgeneratorstate(cr3))
'''GEN_CREATED'''
print(next(cr3))
print(getgeneratorstate(cr3))
'GEN_SUSPENDED'
print(cr3.send(100))
print(getgeneratorstate(cr3))
'GEN_SUSPENDED'
print(cr3.send(200))
print(getgeneratorstate(cr3))
'GEN_SUSPENDED'



# StopIteration 자동 처리 (3.5 -> await)
def generator1():
    for x in 'AB':
        yield x
    for y in range(1, 4):
        yield y
t1 = generator1()
print(next(t1))
print(next(t1))
print(next(t1))
print(next(t1))
print(next(t1))
'''
A
B
1
2
3
'''
t1 = generator1()
print(list(t1))
'''['A', 'B', 1, 2, 3]'''
def generator2():
    yield from 'AB'
    yield from range(1, 4)
t2 = generator2()
print(next(t2))
print(next(t2))
print(next(t2))
print(next(t2))
print(next(t2))
'''
A
B
1
2
3
'''

```


