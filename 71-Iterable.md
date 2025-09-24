# Iterable
## 🔁 Python에서 반복 가능한 객체 만들기
### 1. Iterable이란?
- for 루프에서 사용할 수 있는 객체
- iter(obj)를 호출할 수 있어야 함
- 내부적으로 __iter__() 메서드를 구현하고 있어야 함
```python
t = "ABC"
print(hasattr(t, '__iter__'))  # True
```


### 2. Iterator란?
- next()를 호출할 수 있는 객체
- 내부적으로 __next__() 메서드를 구현하고 있어야 함
- iter(obj)를 호출하면 iterator가 반환됨
```python
w = iter(t)
print(hasattr(w, '__next__'))  # True
```


### 3. 반복 가능한 타입들
- list, tuple, dict, set, str, file, range, *args, **kwargs, collections 등

### 4. 직접 반복자 만들기
```python
class WordSplitter:
    def __init__(self, text):
        self.words = text.split()
        self.idx = 0

    def __next__(self):
        if self.idx >= len(self.words):
            raise StopIteration
        word = self.words[self.idx]
        self.idx += 1
        return word

    def __iter__(self):
        return self  # 반복자 자체를 반환

    def __repr__(self):
        return ', '.join(self.words)


ws = WordSplitter("Do today what you could do tomorrow")
for word in ws:
    print(word)

```

## ✅ 핵심 요약 (Markdown 표)
| 개념       | 설명                                                         |
|------------|--------------------------------------------------------------|
| Iterable   | `__iter__()` 메서드를 가진 객체. `for` 루프에서 사용 가능.     |
| Iterator   | `__next__()` 메서드를 가진 객체. `next()`로 값 하나씩 반환.     |
| iter(obj)  | 반복 가능한 객체에서 반복자를 생성하는 함수.                  |
| next(obj)  | 반복자에서 다음 값을 꺼내는 함수. `StopIteration`으로 종료됨. |
| 직접 구현  | 클래스에 `__iter__()`와 `__next__()`를 구현하면 반복자 완성.   |

---



# ⚙️ Generator란?
- Generator는 **반복자(iterator)**를 자동으로 만들어주는 함수입니다.
- yield 키워드를 사용하면 함수가 값을 하나씩 반환하고, 상태를 기억합니다.
- next()를 호출할 때마다 yield 다음 줄부터 다시 실행됩니다.

## 🔁 Generator 함수 예제
```python
def word_generator(text):
    for word in text.split():
        yield word
gen = word_generator("Do today what you could do tomorrow")
print(next(gen))  # Do
print(next(gen))  # today
```


- word_generator는 yield를 사용해 하나씩 단어를 반환합니다.
- next()를 호출하면 다음 단어가 나옵니다.
- 반복이 끝나면 StopIteration 예외가 발생합니다.

## 🔄 for 루프와 함께 사용
```python
for word in word_generator("Do today what you could do tomorrow"):
    print(word)


출력:
Do
today
what
you
could
do
tomorrow
```


## ✅ Generator vs Iterator 비교 요약
| 항목         | Iterator 클래스 방식                    | Generator 함수 방식             |
|--------------|------------------------------------------|----------------------------------|
| 구현 방식    | `__iter__()` + `__next__()` 직접 구현     | `yield` 사용한 함수              |
| 코드 길이    | 길고 복잡할 수 있음                      | 간결하고 직관적임                |
| 상태 저장    | 인덱스 등 수동으로 관리해야 함            | 자동으로 상태 저장됨             |
| 사용 예시    | 복잡한 반복 로직, 사용자 정의 반복자 등   | 간단한 반복, 데이터 스트림 등    |

---

💡 실전 팁
- 파일 읽기, 대용량 데이터 처리, 무한 반복 등에서 Generator가 매우 유용합니다.
- yield from을 사용하면 다른 generator를 위임할 수도 있어요.


---

# 🧩 사용자 정의 Iterator 구현 방법
✅ 필수 조건

클래스에 다음 두 가지 메서드를 구현해야 합니다:
- __iter__(self) → 반복자 객체를 반환
- __next__(self) → 다음 값을 반환, 더 이상 없으면 StopIteration 예외 발생

## 📦 예제: 사용자 정의 숫자 반복기
```python
class MyRange:
    def __init__(self, start, end):
        self.current = start
        self.end = end

    def __iter__(self):
        return self  # 반복자 객체 자신을 반환

    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        value = self.current
        self.current += 1
        return value

```
### 🔍 사용 예
```python
for num in MyRange(1, 5):
    print(num)
```

### 출력:
```python
1
2
3
4
```


### 🧠 작동 원리
- for 루프가 __iter__()를 호출 → 반복자 객체 반환
- next()가 __next__()를 호출 → 값 반환
- 값이 없으면 StopIteration 예외 발생 → 루프 종료

## ✅ 요약 (Markdown 표)
| 메서드        | 역할                                      |
|---------------|-------------------------------------------|
| `__iter__()`  | 반복자 객체 반환 (`self`를 반환하는 경우 많음) |
| `__next__()`  | 다음 값을 반환, 없으면 `StopIteration` 발생     |



## 💡 팁
- 상태를 기억해야 하므로 self.current 같은 속성을 사용합니다.
- __iter__()는 보통 self를 반환하지만, 다른 반복자 객체를 반환해도 됩니다.
- StopIteration을 명시적으로 발생시켜야 반복이 종료됩니다.

----


##  🔁 기본적인 yield와 비교
## 일반적인 yield 사용
```python
def gen1():
    yield 1
    yield 2

def gen2():
    yield 'A'
    yield from gen1()
    yield 'B'
```

실행 결과
```python
for x in gen2():
    print(x)
```

출력:
```
A
1
2
B
```


## 🔍 무슨 일이 일어난 걸까?
- gen2()는 'A'를 먼저 yield
- 그 다음 yield from gen1() → gen1()의 모든 yield를 자동으로 반복
- 마지막으로 'B'를 yield
즉, yield from gen1()은 다음과 같은 코드와 동일한 효과를 냅니다:
```python
for value in gen1():
    yield value
```


## ✅ 요약: yield from의 의미
| 문법            | 의미                                      |
|-----------------|-------------------------------------------|
| `yield`         | 하나의 값을 반환                          |
| `yield from X`  | X의 모든 값을 반복해서 반환 (`for` 대신)  |



## 💡 실전 활용 예
### 리스트에 위임
```python
def gen():
    yield from [10, 20, 30]
```

→ 리스트의 각 요소를 하나씩 yield합니다.

### 중첩된 generator 구조
```python
def subgen():
    yield "sub1"
    yield "sub2"

def main():
    yield "start"
    yield from subgen()
    yield "end"
```

→ main()은 subgen()의 모든 값을 포함한 하나의 흐름을 만듭니다.

## 🧠 장점
- 코드가 간결해지고
- 중첩된 generator를 재사용하기 쉬워지고
- return 값을 받을 수도 있음 (PEP 380)

---

# C++ Generator

## 🔁 Python의 yield from vs C++의 generator 위임
### Python
```python
def subgen():
    yield 1
    yield 2

def main():
    yield 'start'
    yield from subgen()
    yield 'end'

```
### C++20 coroutine 스타일
```cpp
Generator<int> subgen() {
    co_yield 1;
    co_yield 2;
}

Generator<int> main() {
    co_yield -1;
    for (auto val : subgen()) {  // 위임
        co_yield val;
    }
    co_yield -2;
}
```

→ main()은 subgen()의 값을 반복해서 직접 co_yield 합니다.
C++에는 yield from 같은 문법은 없지만, for (auto val : subgen())로 위임 효과를 구현할 수 있어요.

## ✅ 핵심 요약
| 항목               | Python: `yield from`                  | C++20: `co_yield` 위임 방식                     |
|--------------------|----------------------------------------|------------------------------------------------|
| 위임 문법          | `yield from subgen()`                 | `for (auto x : subgen()) co_yield x;`         |
| 자동 반복 처리     | O                                      | X (반복문으로 수동 처리)                       |
| 상태 관리 방식     | 내부적으로 자동                       | `promise_type`로 명시적 상태 관리             |
| 반환값 전달 방식   | `StopIteration.value`로 전달          | `co_return`으로 반환값 전달 가능              |


## 💡 팁
- C++에서는 co_yield를 반복문으로 감싸서 위임합니다.
- co_return을 사용하면 Python처럼 하위 generator의 반환값도 받을 수 있습니다.
- 위임 구조는 중첩된 데이터 흐름, 스트리밍 처리, 상태 머신 등에 유용합니다.

# coroutine 반환값 전달과 비동기 위임
coroutine에서 과 를 활용한 반환값 전달과 비동기 위임 구조를 설명.
Python의 처럼 generator를 위임하거나, 비동기 흐름을 연결하는 방식입니다.

## 🧩 1. 을 활용한 반환값 전달
## 📦 예제: 하위 coroutine의 결과를 상위 coroutine으로 전달
```cpp
#include <coroutine>
#include <iostream>
#include <optional>

struct Task {
    struct promise_type {
        std::optional<int> result;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void return_value(int value) {
            result = value;
        }

        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> handle;

    Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { handle.destroy(); }

    int get() { return *handle.promise().result; }
};

Task subtask() {
    co_return 42;
}

Task main_task() {
    int value = subtask().get();  // 하위 coroutine의 반환값 받기
    std::cout << "Subtask returned: " << value << std::endl;
    co_return value + 1;
}

int main() {
    Task t = main_task();
    std::cout << "Main task result: " << t.get() << std::endl;
}
```
### 출력:
```
Subtask returned: 42
Main task result: 43
```

## ⚡️ 2. 를 활용한 비동기 위임 구조
### 📦 예제: 비동기 작업을 coroutine으로 연결
```cpp
#include <coroutine>
#include <iostream>
#include <thread>
#include <chrono>

struct Awaiter {
    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> h) {
        std::thread([h]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            h.resume();
        }).detach();
    }

    void await_resume() {
        std::cout << "Async operation completed!" << std::endl;
    }
};

struct AsyncTask {
    struct promise_type {
        AsyncTask get_return_object() {
            return AsyncTask{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> handle;
    AsyncTask(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~AsyncTask() { handle.destroy(); }
};

AsyncTask async_main() {
    std::cout << "Starting async task..." << std::endl;
    co_await Awaiter();  // 비동기 위임
    std::cout << "Resumed after await!" << std::endl;
}

int main() {
    async_main();
    std::this_thread::sleep_for(std::chrono::seconds(2));  // main이 먼저 끝나지 않도록
}
```
### 출력:
```
Starting async task...
Async operation completed!
Resumed after await!
```

## ✅ 요약
| 기능             | 설명                                      | 키워드       |
|------------------|-------------------------------------------|--------------|
| 반환값 전달      | 하위 coroutine의 결과를 상위에서 받기     | `co_return`  |
| 비동기 위임      | 다른 작업이 끝날 때까지 기다렸다가 재개   | `co_await`   |
| 병렬 처리        | `await_suspend`에서 스레드나 이벤트 연결  | `std::thread` 등 |


##  coroutine 실무
C++20 coroutine은 강력하지만 문법이 너무 복잡해서 직접 구현하려면 부담이 큽니다.
그래서 실무에서는 직접 coroutine을 짜기보다는, 잘 만들어진 Wrapper나 라이브러리를 활용해서 블랙박스처럼 쓰는 방식이 훨씬 효율적.

## 🧠 언제 coroutine을 쓰면 좋을까?
### ✅ 대표적인 사용처
| 사용처                  | 관련 coroutine 키워드         |
|-------------------------|-------------------------------|
| 비동기 I/O 처리         | `co_await`                    |
| 게임 루프 / 상태 머신   | `co_yield`                    |
| 스트리밍 데이터 처리    | `co_yield`                    |
| 결과 반환 / 흐름 종료   | `co_return`                   |

예를 들어, 네트워크 요청을 기다리는 동안 다른 작업을 진행하거나, 게임 캐릭터의 행동을 단계별로 표현할 때 coroutine이 빛을 발합니다.

## 🧰 어떻게 Wrapper해서 블랙박스처럼 쓸 수 있을까?
### 1. 라이브러리 사용 (예: cppcoro, Folly, Boost)
- cppcoro: C++ coroutine을 위한 경량 라이브러리
- Folly: Facebook에서 만든 고성능 coroutine 지원
- Boost.Asio: coroutine 기반 비동기 네트워크 처리 가능
이런 라이브러리들은 복잡한 promise_type, handle, suspend 등을 내부에서 처리해주기 때문에
사용자는 co_await, co_yield, co_return만 쓰면 됩니다.
```cpp

task<int> fetch_data() {
    co_await network_ready();
    co_return 42;
}
```
→ 내부 구현은 보지 않아도 되고, 마치 Python처럼 간결하게 사용할 수 있어요.

### 2. 자체 Wrapper 클래스 만들기
직접 coroutine을 감싸는 클래스를 만들어서 API처럼 제공할 수도 있어요.
```cpp
class AsyncFetcher {
public:
    task<int> fetch() {
        co_await wait_for_data();
        co_return result;
    }
};
```

→ 사용자는 AsyncFetcher().fetch()만 호출하면 되고, 내부 coroutine 구조는 몰라도 됩니다.

### 3. DSL 스타일로 추상화
게임 엔진이나 UI 프레임워크에서는 coroutine을 **도메인 특화 언어(DSL)**처럼 추상화해서 사용합니다.
```cpp
co_await move_to(target);
co_await play_animation("attack");
co_await wait(2s);
```

→ 이건 마치 "스크립트"처럼 보이지만, 내부는 coroutine으로 동작합니다.

## ✅ 요약:
| 전략              | 설명                                      |
|-------------------|-------------------------------------------|
| 라이브러리 활용    | cppcoro, Boost 등으로 복잡한 문법 감춤     |
| Wrapper 클래스     | coroutine을 감싸서 API처럼 제공            |
| DSL 추상화         | 게임/UI에서 스크립트처럼 coroutine 사용     |



## Wrapper 만들어 보기

복잡한 C++ coroutine을 감추고, 사용자는 간단하게 호출만 하면 되는 형태의 사용자 정의 Wrapper 예제.
예제는 숫자를 하나씩 생성하는 Generator Wrapper입니다.

### 🎁 목표: 사용자 입장에서는 이렇게만 쓰면 됨
```cpp
MyGenerator gen(5);
while (gen.has_next()) {
    std::cout << gen.next() << std::endl;
}
```


### 🧱 내부 구현: coroutine은 Wrapper가 알아서 처리
```cpp
#include <coroutine>
#include <iostream>

class MyGenerator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    MyGenerator(handle_type h) : coro(h) {}
    ~MyGenerator() { if (coro) coro.destroy(); }

    bool has_next() {
        return !coro.done();
    }

    int next() {
        coro.resume();
        return coro.promise().value;
    }

    struct promise_type {
        int value;

        auto get_return_object() {
            return MyGenerator{handle_type::from_promise(*this)};
        }

        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }

        auto yield_value(int val) {
            value = val;
            return std::suspend_always{};
        }

        void return_void() {}
    };

private:
    handle_type coro;
};

// 실제 coroutine 함수
MyGenerator make_generator(int max) {
    for (int i = 0; i < max; ++i)
        co_yield i;
}

```

### ✅ 사용 예
```cpp
int main() {
    auto gen = make_generator(5);
    while (gen.has_next()) {
        std::cout << gen.next() << std::endl;
    }
}
```

### 출력:
```
0
1
2
3
4
```


## 💡 요점
- 사용자는 make_generator()만 호출하면 되고, coroutine 내부는 몰라도 됨
- MyGenerator는 next()와 has_next()만 제공하는 블랙박스 API
- 내부적으로 co_yield와 promise_type을 사용해 coroutine을 처리

## yield_value

C++ coroutine에서 auto yield_value(...)는 사용자가 co_yield를 호출할 때 자동으로 연결되는 메서드입니다.
겉으로 보면 연결 지점이 없는데, 사실은 코루틴 프레임워크가 내부적으로 연결해줍니다.

### 🔗 어떻게 연결되는가?
C++20 coroutine은 컴파일러가 다음과 같은 **코루틴 트랜스폼(coroutine transformation)**을 수행합니다:
- 사용자가 co_yield value;를 호출하면
- 컴파일러는 promise.yield_value(value)를 자동으로 호출합니다
- 그 결과로 suspend_point를 반환해야 코루틴이 멈춥니다
즉, co_yield는 **promise_type::yield_value()를 호출하는 문법적 설탕(syntactic sugar)**입니다.

### 🔍 예제 흐름
```cpp
struct promise_type {
    int value;

    auto yield_value(int v) {
        value = v;
        return std::suspend_always{};
    }
};


co_yield 42;  // 컴파일러가 내부적으로 yield_value(42) 호출

```

→ value에 42가 저장되고, std::suspend_always로 코루틴이 멈춥니다.

### 🧠 왜 연결 지점이 없어 보일까?
- co_yield는 일반 함수 호출처럼 보이지 않기 때문에
- promise_type은 사용자 코드와 직접 연결되지 않기 때문에
- 컴파일러가 자동으로 yield_value()를 호출하므로 보이지 않는 연결처럼 느껴집니다

## ✅ 요약 (Markdown 표)
| 키워드       | 내부적으로 호출되는 메서드           |
|--------------|----------------------------------------|
| `co_yield x` | `promise_type::yield_value(x)`         |
| `co_return x`| `promise_type::return_value(x)`        |
| `co_await x` | `x.await_ready()`, `await_suspend()`, `await_resume()` |

----

## 로또 생성기 만들어 보기

### 🧱 구현 코드
```cpp
#include <coroutine>
#include <iostream>
#include <random>
#include <set>

class LottoMachine {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    LottoMachine(handle_type h) : coro(h) {}
    ~LottoMachine() { if (coro) coro.destroy(); }

    bool has_next() const {
        return !coro.done();
    }

    int next() {
        coro.resume();
        return coro.promise().value;
    }

    struct promise_type {
        int value;

        auto get_return_object() {
            return LottoMachine{handle_type::from_promise(*this)};
        }

        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }

        auto yield_value(int v) {
            value = v;
            return std::suspend_always{};
        }

        void return_void() {}
    };

private:
    handle_type coro;
};

// coroutine 함수: 로또 번호 생성기
LottoMachine generate_lotto(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 45);

    std::set<int> lotto;
    while (lotto.size() < count) {
        int num = dist(gen);
        if (lotto.insert(num).second) {
            co_yield num;
        }
    }
}
```


### ✅ 사용 예
```cpp
int main() {
    int how_many = 6;
    auto machine = generate_lotto(how_many);

    std::cout << "Your Lotto Numbers: ";
    while (machine.has_next()) {
        std::cout << machine.next() << " ";
    }
    std::cout << std::endl;
}
```

출력 예:
```
Your Lotto Numbers: 7 22 35 1 44 18
```

### 💡 특징
- std::set을 사용해 중복 없이 번호 생성
- co_yield로 하나씩 값을 반환
- LottoMachine은 블랙박스처럼 next()만 호출하면 됨


## 🎯 목표: 로또 번호를 하나씩 co_yield로 생성하고, 필요할 때마다 꺼내 쓰기
```cpp
auto lotto = make_lotto_machine(1, 45, 6);
while (lotto.has_next()) {
    std::cout << lotto.next() << std::endl;
}
```

→ 내부적으로 coroutine이 번호를 하나씩 co_yield하고, 외부에서는 next()로 꺼냅니다.

### 🧱 구조 설계: Wrapper + coroutine
```cpp
#include <coroutine>
#include <vector>
#include <random>
#include <algorithm>

class LottoGenerator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    LottoGenerator(handle_type h) : coro(h) {}
    ~LottoGenerator() { if (coro) coro.destroy(); }

    bool has_next() const { return !coro.done(); }

    int next() {
        coro.resume();
        return coro.promise().value;
    }

    struct promise_type {
        int value;

        auto get_return_object() {
            return LottoGenerator{handle_type::from_promise(*this)};
        }

        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }

        auto yield_value(int v) {
            value = v;
            return std::suspend_always{};
        }
    };

private:
    handle_type coro;
};
```


### 🎰 실제 coroutine 함수
```cpp
LottoGenerator make_lotto_machine(int min, int max, int count) {
    std::vector<int> pool;
    for (int i = min; i <= max; ++i)
        pool.push_back(i);

    std::shuffle(pool.begin(), pool.end(), std::mt19937{std::random_device{}()});

    for (int i = 0; i < count; ++i)
        co_yield pool[i];
}
```

### ✅ 사용 예
```cpp
int main() {
    auto lotto = make_lotto_machine(1, 45, 6);
    while (lotto.has_next()) {
        std::cout << lotto.next() << " ";
    }
    std::cout << std::endl;
}
```

### 출력 예:
```
7 22 35 1 44 18
```


## 💡 요점
- make_lotto_machine()은 coroutine 함수로서, 번호를 하나씩 co_yield
- LottoGenerator는 coroutine을 감싸는 Wrapper로서, next()와 has_next()만 제공
- 사용자는 coroutine 내부를 몰라도 되고, 마치 블랙박스처럼 사용 가능


---
## std::shuffle
std::shuffle은 C++11부터 도입된 함수인데, 기존의 random_shuffle보다 더 안전하고 유연한 방식으로 컨테이너의 요소를 무작위로 섞는 함수입니다.

## 🎲 std::shuffle이란?
- 헤더: <algorithm>
- 기능: 컨테이너의 요소들을 무작위로 섞음
- 필요한 것: 반드시 난수 생성기를 함께 전달해야 함 (std::mt19937 등)

## 📦 기본 사용법
```cpp
#include <algorithm>
#include <vector>
#include <random>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister 엔진

    std::shuffle(v.begin(), v.end(), gen);

    for (int n : v)
        std::cout << n << " ";
}
```

## 출력 예:
```
3 1 5 2 4  // 실행할 때마다 달라짐
```


## ✅ std::shuffle vs random_shuffle
| 항목               | `random_shuffle`           | `std::shuffle`                  |
|--------------------|----------------------------|----------------------------------|
| 도입 시기          | C++98                      | C++11                            |
| 난수 생성기 지정   | 불가능                     | 가능 (`std::mt19937` 등)         |
| 안전성             | 낮음 (내부 구현에 의존)    | 높음 (사용자 지정 엔진 사용 가능) |
| 현재 상태          | C++17부터 **제거됨**       | 표준으로 사용됨                  |
| 대표 난수 엔진     | 없음                       | `std::mt19937` (Mersenne Twister) |


## 💡 팁
- std::shuffle은 보안적으로 안전한 난수를 쓰고 싶다면 std::random_device와 함께 쓰면 좋음.
- 게임, 시뮬레이션, 로또, 카드 섞기 등에 자주 쓰입니다.

---
