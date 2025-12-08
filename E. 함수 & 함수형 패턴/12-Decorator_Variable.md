# 메타 정보 / 매개변수 활용
데코레이터를 공부하면서 **메타 정보와 매개변수 활용** 을 어떻게 결합하는지 실험.  
데코레이터의 핵심 개념 두 가지를 동시에 다루고 있음:

## 🧠 핵심 개념 1: 메타 정보 보존 (functools.wraps)
```python
import functools as fs

def decorator_3(func):
    @fs.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper
```

### ✅ 왜 functools.wraps를 쓰는가?
- 데코레이터는 원래 함수를 감싸기 때문에 __name__, __doc__, __module__ 같은 메타 정보가 사라짐
- @wraps(func)을 쓰면 원래 함수의 메타 정보를 wrapper에 복사해줌
- 그래서 print(add.__name__) → 'add'가 나옴

## 🧠 핵심 개념 2: 매개변수 기반 데코레이터
```python
def typecheck(para1, para2):
    def typeproc(x, y):
        if not (type(x) == para1 and type(y) == para2):
            raise TypeError("Type check failed")
    def decorator_(func):
        def wrapper(*args, **kwargs):
            typeproc(*args)  # 여기서 실제 인자 검사
            return func(*args, **kwargs)
        return wrapper
    print(para1, para2)
    return decorator_
```
### 📌 샘플 코드
-  위에서 정의한 typecheck를 사용한다고 가정
-  para1=int, para2=str 로 지정하면
-  첫 번째 인자는 int, 두 번째 인자는 str 이어야 합니다.
```python
@typecheck(int, str)
def repeat_number(num, text):
    return text * num
```
```python
print(repeat_number(3, "Hi"))   # 정상 동작 → "HiHiHi"
```
#### 잘못된 타입 전달 시 에러 발생
```python
try:
    print(repeat_number("3", "Hi"))  # 첫 번째 인자가 str → TypeError
except TypeError as e:
    print("에러 발생:", e)
```
```python
try:
    print(repeat_number(3, 100))     # 두 번째 인자가 int → TypeError
except TypeError as e:
    print("에러 발생:", e)
```

#### 📝 실행 흐름
- @typecheck(int, str) → 데코레이터가 적용되어 repeat_number 함수의 첫 두 인자를 검사합니다.
- repeat_number(3, "Hi") → 첫 번째 인자 3은 int, 두 번째 인자 "Hi"는 str → 조건 만족 → 정상 실행.
- repeat_number("3", "Hi") → 첫 번째 인자가 str → TypeError("Type check failed") 발생.
- repeat_number(3, 100) → 두 번째 인자가 int → 역시 TypeError 발생.


## ✅ 이건 뭐 하는 구조인가?
- typecheck(int, int)처럼 데코레이터에 인자를 넘기는 구조
- 이건 데코레이터 팩토리라고 부름 → 데코레이터를 생성하는 함수
- typeproc()은 실제 인자 타입을 검사하는 로직
- decorator_()는 원래 함수를 감싸는 데코레이터
- wrapper()는 감싸진 함수 → 실행 전에 타입 체크

## 🔍 정리 목적

| 목적 구분         | 핵심 기능 설명                          |
|------------------|----------------------------------------|
| `@wraps`          | 원래 함수의 `__name__`, `__module__`, `__doc__` 보존 |
| `@typecheck(int, int)` | 데코레이터에 인자를 전달해서 실행 전 타입 검사 수행 |
| 데코레이터 팩토리 | 데코레이터를 생성하는 함수 구조 학습 (`return decorator`) |
| 실행 전 유효성 검사 | 함수 실행 전에 조건 검사 로직 삽입 가능 (`wrapper`) |

---
# 타 언어와 비교

## ✅ C++에서 데코레이터 구조 응용
- C++은 함수 포인터, 람다, 템플릿, Functor를 활용해서 함수 실행 전후에 로직을 삽입하는 구조를 만들 수 있음.

### 🔧 예시: 타입 체크 + 실행 시간 측정
```cpp
#include <iostream>
#include <chrono>
#include <type_traits>

template<typename Func, typename... Args>
auto decorate(Func func, Args&&... args) {
    static_assert(std::is_same_v<decltype(func(std::forward<Args>(args)...)), int>,
                  "Return type must be int");

    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "[Time] " << elapsed.count() << "s\n";
    return result;
}

int add(int x, int y) {
    return x + y;
}

int main() {
    int result = decorate(add, 10, 20);
    std::cout << "Result: " << result << std::endl;
}
```

- decorate()는 데코레이터처럼 동작
- static_assert로 타입 체크
- 실행 시간 측정까지 포함

## ✅ Rust에서 데코레이터 구조 응용
- Rust는 고차 함수 + 클로저 + 트레잇을 활용해서 함수 감싸기, 타입 검사, 실행 전후 로직 삽입이 가능.
### 🔧 예시: 타입 체크 + 실행 시간 측정
```rust
use std::time::Instant;

fn decorate<F, R>(func: F) -> R
where
    F: FnOnce() -> R,
{
    let start = Instant::now();
    let result = func();
    let duration = start.elapsed();
    println!("[Time] {:.5}s", duration.as_secs_f64());
    result
}

fn add(x: i32, y: i32) -> i32 {
    x + y
}

fn main() {
    let result = decorate(|| add(10, 20));
    println!("Result: {}", result);
}
```

- decorate()는 FnOnce() 클로저를 받아서 감싸는 구조
- || add(10, 20)는 람다로 전달
- 실행 시간 측정 포함

## 📘 결론
- C++과 Rust는 @decorator 문법은 없지만, 함수형 스타일과 고차 함수, 템플릿, 클로저를 활용하면
    데코레이터처럼 함수를 감싸고 기능을 확장하는 구조를 충분히 만들 수 있음.
---

# 🧠 왜 클로저와 결합하면 강력해질까?
- 클로저는 외부 스코프의 변수(상태)를 기억하는 함수
- 데코레이터는 함수를 감싸서 실행 전후 로직을 삽입하는 구조
- 이 둘을 결합하면 → **상태를 가진 데코레이터** 를 만들 수 있어


## 🔧 예시: 호출 횟수 추적 데코레이터
```python
def call_counter():
    count = 0
    def decorator(func):
        def wrapper(*args, **kwargs):
            nonlocal count
            count += 1
            print(f"[Call #{count}] {func.__name__}")
            return func(*args, **kwargs)
        return wrapper
    return decorator

@call_counter()
def greet(name):
    print(f"Hello, {name}!")

greet("JungHwan")
greet("Copilot")
greet("Pythonista")
```

### ✅ 결과
```
[Call #1] greet
Hello, JungHwan!
[Call #2] greet
Hello, Copilot!
[Call #3] greet
Hello, Pythonista!
```
- count는 클로저로 유지되는 상태
- 데코레이터가 함수 호출 횟수를 기억하고 출력

## 🔧 예시: 매개변수 기반 유효성 검사
```python
def typecheck(typ1, typ2):
    def decorator(func):
        def wrapper(x, y):
            if not isinstance(x, typ1) or not isinstance(y, typ2):
                raise TypeError("Type mismatch")
            return func(x, y)
        return wrapper
    return decorator

@typecheck(int, int)
def add(x, y):
    return x + y
```

- typ1, typ2는 클로저로 기억됨
- 데코레이터가 동적으로 타입 검사 로직을 삽입

## 📘 결론
- 데코레이터 + 클로저는 단순한 감싸기를 넘어서 상태 기억, 동적 로직 삽입, 매개변수 기반 제어까지 가능하게 함.
- 이건 파이썬에서 프레임워크 수준의 기능 확장을 설계할 때 핵심 도구.

---

