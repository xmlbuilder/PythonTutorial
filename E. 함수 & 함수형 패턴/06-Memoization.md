## 📘 Memoization

### 📌 메모이제이션(Memoization)이란?
- 메모이제이션은 함수의 결과를 저장해두고, 같은 입력이 들어오면 계산하지 않고 저장된 값을 반환하는 최적화 기법입니다.

### 📌 핵심 원리
- 함수 호출 시 입력값을 키로 사용
- 결과를 캐시에 저장
- 동일한 입력이 들어오면 캐시에서 즉시 반환

### 📌 기본 예제 분석
#### 1. 🔹 일반 재귀 함수
```python
def fact(n):
    if n == 0 or n == 1:
        return 1
    return n * fact(n - 1)

print(fact(10))  # 3628800
```

- 매번 fact(n-1)을 재귀적으로 계산 → 중복 계산 많음

#### 2. 🔹 함수 객체 속성 활용한 메모이제이션
```cpp
def factorial(k):
    if not hasattr(factorial, '_memo'):
        factorial._memo = {1: 1}
    if k not in factorial._memo:
        factorial._memo[k] = k * factorial(k - 1)
    return factorial._memo[k]
```

- factorial._memo는 함수 객체의 속성으로 캐시 역할
- 결과 저장 후 재사용 → 성능 향상

#### 3. 🔹 데코레이터 스타일 메모이제이션
```python
def memoize(func):
    memoize.cache = {}

    def inner(x):
        if x not in memoize.cache:
            print("Calculate {}".format(x))
            for i in range(0, x + 1):
                if i not in memoize.cache:
                    memoize.cache[i] = func(i)
        return memoize.cache[x]

    return inner

a = memoize(fact)
a(6)  # Calculate 6
print(a(5))  # 120
```

- memoize.cache는 데코레이터 외부에 저장된 캐시
- inner 함수가 func을 감싸고 결과를 저장
- a는 fact의 메모이제이션 버전

#### 🔹 실무 확장 예제: Fibonacci with Memoization
```python
def memoize(func):
    cache = {}

    def wrapper(n):
        if n not in cache:
            cache[n] = func(n)
        return cache[n]

    return wrapper

@memoize
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)

print(fib(30))  # 빠르게 계산됨
```


#### 🔹 안전한 메모이제이션: functools.lru_cache
- Python 내장 라이브러리 functools에는 더 안전하고 강력한 메모이제이션 기능이 있음.
```python
from functools import lru_cache

@lru_cache(maxsize=None)
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)

print(fib(30))  # 매우 빠름
```

- maxsize로 캐시 크기 제한 가능
- 자동으로 메모리 관리
- 실무에서 가장 많이 사용됨

### 📌 마무리 요약

| 방식                  | 장점                              | 단점                              | 추천 용도                         | 비고                         |
|-----------------------|-----------------------------------|-----------------------------------|-----------------------------------|------------------------------|
| 함수 객체 속성        | 간단하고 빠르게 구현 가능          | 유지보수 어려움, 부작용 가능       | 실험적 코드, 단일 함수 캐시       | `func.attr`로 캐시 저장      |
| 데코레이터 직접 구현  | 재사용 가능, 구조적                | 캐시 공유 시 주의 필요            | 커스텀 캐시 로직 필요할 때        | `memoize(func)` 형태         |
| functools.lru_cache   | 안정적, 자동 메모리 관리           | 커스텀 로직 어려움                 | 실무 최적화, 재귀 함수            | 내장 라이브러리, 가장 추천됨 |

---


### 📌 DB에 적용

- SQLite를 사용하는 예제로, 메모이제이션을 통해 동일한 쿼리 결과를 캐시하는 구조.

#### 🔹 예제: 사용자 정보 조회에 메모이제이션 적용
```python
import sqlite3

# DB 연결 및 샘플 테이블 생성
conn = sqlite3.connect(":memory:")
cursor = conn.cursor()
cursor.execute("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT)")
cursor.executemany("INSERT INTO users (name) VALUES (?)", [("Alice",), ("Bob",), ("Charlie",)])
conn.commit()

# 메모이제이션 데코레이터
def memoize_query(func):
    cache = {}

    def wrapper(user_id):
        if user_id not in cache:
            print(f"🔍 DB 조회: user_id={user_id}")
            cache[user_id] = func(user_id)
        else:
            print(f"⚡ 캐시 사용: user_id={user_id}")
        return cache[user_id]

    return wrapper

# 사용자 정보 조회 함수
@memoize_query
def get_user_by_id(user_id):
    cursor.execute("SELECT * FROM users WHERE id = ?", (user_id,))
    return cursor.fetchone()

# 테스트
print(get_user_by_id(2))  # DB 조회
print(get_user_by_id(2))  # 캐시 사용
print(get_user_by_id(3))  # DB 조회
print(get_user_by_id(3))  # 캐시 사용

```


#### 🔹 출력 예시
```
🔍 DB 조회: user_id=2
(2, 'Bob')
⚡ 캐시 사용: user_id=2
(2, 'Bob')
🔍 DB 조회: user_id=3
(3, 'Charlie')
⚡ 캐시 사용: user_id=3
(3, 'Charlie')
```


### 📌 실무 적용 포인트
- 읽기 중심 쿼리에 적합 (예: 사용자 프로필, 설정값, 카테고리 목록 등)
- 캐시 무효화 전략 필요 시 TTL(Time-To-Live) 또는 수동 초기화 추가 가능

---

