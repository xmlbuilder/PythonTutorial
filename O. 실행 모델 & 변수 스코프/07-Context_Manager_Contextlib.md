# Context Manager Contextlib
- 이 예제는 컨텍스트 매니저를 활용해 코드 실행 시간을 측정하고 예외까지 처리하는 구조를 보여주는 사례.   
- 특히 `__enter__()` 와 `__exit__()` 를 직접 구현한 클래스 기반 컨텍스트 매니저를 통해 리소스 관리 + 로깅 + 타이밍을 동시에 처리.   
- 아래에 개념, 동작 원리, 실무 활용, 그리고 contextlib로 확장하는 방식까지 자세히 정리.

## 전체 소스
```python
import time

class ExecuteTimer(object):
    def __init__(self, msg):
        self._msg = msg
    def __enter__(self):
        self._start = time.monotonic()
        return self._start
    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_type:
            print("Logging execption {}",format((exc_type, exc_val, exc_tb)))
        else:
            print('{} | {} s'.format(self._msg
                                     , time.monotonic() - self._start))
        return True #예외를 무시하고 계속 진행하겠다는 의미

with ExecuteTimer('Timer check') as first:
    print('Received start monotonic : {{{}}}'.format(first))
    for i in range(3100000):
        pass
    raise Exception('Raise Exception!!!')

```


## 🧠 핵심 개념: 컨텍스트 매니저 + 실행 시간 측정

### 🔹 클래스 기반 컨텍스트 매니저
```python
class ExecuteTimer:
    def __enter__(self):
        self._start = time.monotonic()
        return self._start
    def __exit__(self, exc_type, exc_val, exc_tb):
        # 예외가 있으면 로깅, 없으면 실행 시간 출력
```

- `__enter__()` 에서 시작 시간 기록
- `__exit__()` 에서 종료 시간 계산 및 출력
- 예외 발생 시 exc_type, exc_val, exc_tb로 로깅 처리
- return True는 예외를 무시하고 계속 진행하겠다는 의미

## 📌 실무에서 왜 중요한가?

| 상황 또는 목적             | 설명                                                                 |
|----------------------------|----------------------------------------------------------------------|
| 자원 누수 방지              | `with` 구문은 블록 종료 시 자동으로 자원을 해제하여 누수 위험을 제거함         |
| 예외 안전성 확보            | 예외 발생 여부와 관계없이 `__exit__()`가 호출되어 안정적인 종료 보장             |
| 코드 가독성 향상            | `try-finally`보다 간결하고 명확한 구조로 자원 사용 범위를 쉽게 파악 가능         |
| 유지보수 및 협업 효율       | 자원 관리 로직이 캡슐화되어 있어 수정과 협업 시 오류 발생 가능성이 낮음          |
| 커스텀 자원 관리            | `with` 구문을 통해 복잡한 초기화/종료 로직을 컨텍스트 매니저로 깔끔하게 처리 가능 |


## 🔍 특징 요약

| 구성 요소           | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| `__enter__()`        | 블록 시작 시 호출. `time.monotonic()`으로 시작 시간 기록               |
| `__exit__()`         | 블록 종료 시 호출. 예외 정보(`exc_type`, `exc_val`, `exc_tb`) 전달 가능 |
| `return True`        | 예외 발생 시 무시하고 프로그램 계속 진행 (예외 전파 방지)               |
| `with`               | 컨텍스트 매니저를 사용하는 문법. 자원 사용 범위 명확, 자동 종료 처리     |
| 예외 처리 및 로깅     | 예외 발생 시 `__exit__()`에서 로깅하거나 복구 가능                       |

---

## 🔧 contextlib로 함수형 컨텍스트 매니저 구현
```python
from contextlib import contextmanager
import time

@contextmanager
def execute_timer(msg):
    start = time.monotonic()
    try:
        yield start
    except Exception as e:
        print("Logging exception:", e)
    else:
        print(f'{msg} | {time.monotonic() - start:.4f} s')
```
- `@contextmanager` 데코레이터로 함수 기반 컨텍스트 매니저 구현 가능
- yield 앞은 `__enter__()` , 뒤는 `__exit__()` 역할
- 코드가 간결하고 직관적이어서 간단한 컨텍스트 매니저에 적합

## ✅ 요약
- 클래스 기반 컨텍스트 매니저는 복잡한 자원 관리와 진단 로직에 적합
- contextlib.contextmanager는 간단한 타이밍, 로깅, 상태 추적에 유용
- 예외 발생 여부와 관계없이 자원 해제와 로깅을 보장하는 구조는 실무에서 매우 중요

---

#  Context Manager (Annotation)

- 예제는 Python의 컨텍스트 매니저를 함수형 스타일로 구현하는 방식.  
- 특히 contextlib.contextmanager 데코레이터를 활용하면 `__enter__()` 와 `__exit__()` 를 직접 구현하지 않아도 훨씬 간결하고 직관적인 코드를 만들 수 있음.   
- 아래에 개념 설명과 함께 다양한 실무 예제를 추가해서 정리.

## 🧠 핵심 개념: contextlib.contextmanager
- @contextmanager 데코레이터는 함수 기반 컨텍스트 매니저를 만들 수 있게 해줌
- yield 앞은 `__enter__()` 역할, 뒤는 `__exit__()` 역할
- 예외가 발생하면 try-except 블록에서 처리 가능
- 코드가 간결하고 직관적이며, 예외 처리도 용이

### ✅ 대표 예제 1: 파일 쓰기
```python
@contextmanager
def my_file_writer(file_name, method):
    f = open(file_name, method)
    yield f  # __enter__
    f.close()  # __exit__

with my_file_writer('test4.txt', 'w') as f:
    f.write("Sample Model")
```

- open()과 close()를 자동으로 처리
- try-finally 없이도 자원 누수 방지

### ✅ 대표 예제 2: 실행 시간 측정 + 예외 로깅
```python
@contextmanager
def ExecuteTimerDc(msg):
    start = time.monotonic()
    try:
        yield start
    except BaseException as e:
        print(f'Logging exception: {msg}: {e}')
        raise
    else:
        print(f'{msg}: {time.monotonic() - start:.4f} s')

with ExecuteTimerDc("Timer Check") as start:
    print(f'Start Time: {start}')
    for i in range(1, 10000000):
        pass
```

- 코드 실행 시간 측정
- 예외 발생 시 로깅 처리
- raise로 예외를 다시 전파 가능

### ✅ 실무 예제 3: 데이터베이스 연결 관리
```python
@contextmanager
def db_connection():
    conn = connect_to_db()
    try:
        yield conn
    finally:
        conn.close()

with db_connection() as conn:
    conn.execute("SELECT * FROM users")
```

- DB 연결을 자동으로 열고 닫음
- 예외 발생 시에도 안전하게 종료

### ✅ 실무 예제 4: 파일 잠금(lock) 처리
```python
@contextmanager
def file_lock(lock_file):
    lock = acquire_lock(lock_file)
    try:
        yield
    finally:
        release_lock(lock)

with file_lock('resource.lock'):
    process_file()

```

- 파일이나 자원에 대한 동시 접근 제어
- try-finally 없이도 안정적인 락 해제

### ✅ 실무 예제 5: 출력 리디렉션
```python
from contextlib import redirect_stdout

with open('log.txt', 'w') as f:
    with redirect_stdout(f):
        print("This will be written to log.txt")

````

- print() 출력 결과를 파일로 리디렉션
- 테스트, 로깅, 디버깅에 유용

### 📌 실무에서 왜 중요한가?

| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `with`             | 자원 사용 범위를 명확히 지정하고, 블록 종료 시 자동으로 자원 해제. 예외 발생에도 안전하게 종료됨 |
| `contextlib`       | 데코레이터 방식으로 컨텍스트 매니저를 간결하게 구현. 복잡한 `try-finally` 구조를 대체 가능 |
| `try-finally`      | 자원 해제를 보장하지만 코드가 장황하고 예외 처리 로직이 분리되어 가독성이 떨어짐             |
| `try-except-finally` | 예외 처리와 자원 해제를 모두 포함하지만, 구조가 복잡하고 실수로 누락될 가능성 있음             |
| 유지보수 효율       | `with` + `contextlib` 구조는 로직이 캡슐화되어 협업과 테스트에 유리하며, 오류 발생 가능성 낮음   |

---

