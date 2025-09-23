# Decorator

데코레이터는 파이썬에서 정말 강력한 기능

## 🧠 데코레이터란?
함수를 감싸서 기능을 확장하거나 수정하는 함수
즉, 기존 함수를 변경하지 않고도 실행 전후에 원하는 동작을 추가할 수 있음.


## 🔧 기본 구조
```python
def decorator(func):         # 1. 원래 함수를 받아서
    def wrapper(*args, **kwargs):  # 2. 감싸는 함수 정의
        # 추가 기능
        result = func(*args, **kwargs)  # 3. 원래 함수 호출
        # 추가 기능
        return result
    return wrapper           # 4. 감싼 함수 반환
```

## ✅ 사용 방식
```python
@decorator
def my_func():
    pass
```

→ my_func = decorator(my_func) 와 동일


## 예제

```python
import time
def perf_clock(func):
    def perf_clocked(*args):
        st = time.perf_counter()
        result = func(*args)
        et = time.perf_counter()
        name = func.__name__
        arg_str = ', '.join(repr(arg) for arg in args)
        print('[%0.5fs] %s(%s) -> %r' % (et - st, name, arg_str, result))
        return result
    return perf_clocked

def time_func(seconds):
    time.sleep(seconds)

def sum_func(*numbers):
    return sum(numbers)


# 데코레이터 미사용

func1 = perf_clock(time_func)
func2 = perf_clock(sum_func)
print(func1, func1.__code__.co_freevars)
print(func2, func2.__code__.co_freevars)
'''
<function perf_clock.<locals>.perf_clocked at 0x103312980> ('func',)
<function perf_clock.<locals>.perf_clocked at 0x10338fe20> ('func',)
'''

func1(3)
func2(1,2, 3, 4, 5, 6, 7)
[10.00507s] time_func(10) -> None
[0.00001s] sum_func(1, 2, 3, 4, 5, 6, 7) -> 28

print(func1, func1.__code__.co_freevars)
print(func2, func2.__code__.co_freevars)

'''
<function perf_clock.<locals>.perf_clocked at 0x100a8e8e0> ('func',)
<function perf_clock.<locals>.perf_clocked at 0x100a8e980> ('func',)
'''

#데코레이터 사용 - Clousure 처럼 바로 사용하게 해 준다.
@perf_clock
def time_func_def(seconds):
    time.sleep(seconds)

@perf_clock
def sum_func_def(*numbers):
    return sum(numbers)

time_func_def(3)
sum_func_def(1, 2, 3, 4, 5, 6, 7)
'''
[3.00237s] time_func_def(3) -> None
[0.00001s] sum_func_def(1, 2, 3, 4, 5, 6, 7) -> 28
'''

def decorator_func(func):
    def inner(*args, **kwargs):
        return func(*args, **kwargs)
    return inner

@decorator_func
def func2(data_type, n):
    data = {'int' : int, 'str' : str, 'float' : float, 'bool' : bool}
    return data[data_type](n)

print(func2('int', 3))
'''3'''

print(func2('str', 3))
'''3'''

print(func2('float', 3))
'''3.0'''

print(func2('bool', 3))
'''True'''

```

## 🔍 예제 분석: perf_clock
```python
def perf_clock(func):
    def perf_clocked(*args):
        st = time.perf_counter()
        result = func(*args)
        et = time.perf_counter()
        print(f"[{et - st:.5f}s] {func.__name__}({args}) -> {result}")
        return result
    return perf_clocked
```

- perf_clock는 함수 실행 시간 측정 기능을 추가
- func은 원래 함수 (time_func, sum_func)
- perf_clocked는 감싼 함수 → 실행 시간 출력 후 결과 반환

✅ 데코레이터 사용 전 vs 후
| 구분             | 코드 표현                         | 설명                                  |
|------------------|----------------------------------|---------------------------------------|
| 데코레이터 미사용 | `func1 = perf_clock(time_func)`   | 직접 감싸서 새로운 함수 변수에 할당     |
| 데코레이터 사용   | `@perf_clock`                     | 함수 정의 위에 붙여 자동으로 감싸줌     |
| 내부 동작        | `func = perf_clock(func)`         | 데코레이터가 실제로 수행하는 치환 동작 |


## 📘 데코레이터의 장점

| 항목             | 설명 |
|------------------|------|
| 중복 제거         | 공통 기능을 한 곳에서 관리 → 코드 간결화 |
| 관심사 분리       | 핵심 로직과 부가 기능(로깅, 인증 등)을 분리 가능 |
| 재사용성 향상     | 여러 함수에 동일한 기능을 쉽게 적용 가능 |
| 조합 가능         | 여러 데코레이터를 겹쳐서 사용 가능 → `@auth @log`처럼 체이닝 |
| 유지보수 용이     | 기능 변경 시 데코레이터만 수정하면 전체 반영됨 |

## ⚠️ 데코레이터의 단점

| 항목             | 설명 |
|------------------|------|
| 가독성 저하       | `@`가 여러 개 겹치면 흐름 파악이 어려워짐 |
| 디버깅 어려움     | 감싸진 함수가 실행되므로 실제 호출 위치 추적이 복잡함 |
| 추상화 과다       | 단순한 함수에 데코레이터를 쓰면 오히려 구조가 과해짐 |
| 실행 순서 혼란    | 여러 데코레이터가 겹치면 실행 순서를 직관적으로 알기 어려움 |


## 🧪 기억에 남는 비유
데코레이터는 함수에 옷을 입히는 것이야.
원래 함수는 그대로인데, 겉에 로깅 옷, 타이머 옷, 인증 옷을 입혀서
실행할 때마다 추가 기능이 자동으로 따라붙는 구조야.


## 🔁 기억 유지 팁
- 데코레이터는 결국 func = decorator(func)이라는 함수 치환
- @는 단축 문법일 뿐, 함수를 감싸는 구조가 핵심
- 감싸는 함수는 항상 def wrapper(*args, **kwargs)처럼 인자 그대로 전달하고 결과 반환

---

# C++ / Rust Decorator

## ✅ C++에서 데코레이터처럼 동작하는 구조
C++은 메타 언어가 없지만, 함수 포인터, 람다, 템플릿, Functor를 활용해서
함수를 감싸는 구조를 만들 수 있음.

## 🔧 예시: 실행 시간 측정 데코레이터
```cpp
#include <iostream>
#include <chrono>
#include <functional>

template<typename Func, typename... Args>
auto perf_clock(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "[Time] " << elapsed.count() << "s\n";
    return result;
}

// 원래 함수
int sum_func(int a, int b) {
    return a + b;
}

int main() {
    int result = perf_clock(sum_func, 10, 20);
    std::cout << "Result: " << result << std::endl;
}
```

- perf_clock()은 데코레이터처럼 함수를 감싸서 실행 시간 측정
- std::function이나 람다로 더 일반화 가능

## ✅ Rust에서 데코레이터처럼 동작하는 구조
Rust는 메타 언어는 없지만 고차 함수와 클로저를 통해
함수 감싸기, 실행 전후 로직 삽입이 가능해.
🔧 예시: 실행 시간 측정 데코레이터

```rust
use std::time::Instant;

fn perf_clock<F, R>(func: F) -> R
where
    F: FnOnce() -> R,
{
    let start = Instant::now();
    let result = func();
    let duration = start.elapsed();
    println!("[Time] {:.5}s", duration.as_secs_f64());
    result
}

fn sum_func() -> i32 {
    (1..=7).sum()
}

fn main() {
    let result = perf_clock(|| sum_func());
    println!("Result: {}", result);
}
```

- perf_clock은 데코레이터처럼 클로저를 받아서 감싸는 함수
- || sum_func()는 람다 표현식으로 전달

## 📘 결론
C++과 Rust는 메타 언어는 없지만,
고차 함수, 람다, 템플릿, 클로저를 활용하면
데코레이터처럼 함수를 감싸고 기능을 확장하는 구조를 충분히 만들 수 있음.


---

# FnOnce

FnOnce()는 Rust에서 함수형 프로그래밍을 다룰 때 자주 등장하는 트레잇(trait) 중 하나.

## 🧠 FnOnce란?
한 번만 호출 가능한 함수형 트레잇
즉, 클로저가 **자기 내부의 값을 소비(move)**하기 때문에 다시 호출할 수 없는 함수를 의미.


## 🔍 Fn, FnMut, FnOnce 비교

| 트레잇     | 호출 가능 횟수     | 내부 상태 변경 | 캡처 방식 |
|------------|--------------------|----------------|-----------|
| `Fn`       | 여러 번 가능        | ❌ 불변         | `&T`      |
| `FnMut`    | 여러 번 가능        | ✅ 가변         | `&mut T`  |
| `FnOnce`   | **한 번만 가능**    | ✅ 소비(move)   | `T`       |

### ✅ 예시로 기억해보자
```rust
fn call_once<F>(f: F)
where
    F: FnOnce(),
{
    f(); // 한 번만 호출
}

fn main() {
    let name = String::from("JungHwan");

    let say_hi = move || {
        println!("Hi, {}", name); // name을 move해서 가져감
    };

    call_once(say_hi); // OK
    // call_once(say_hi); // ❌ 다시 호출 불가
}
```

- move 클로저는 name을 소유권 이동해서 가져감
- 그래서 say_hi는 한 번만 호출 가능 → FnOnce

##  📘 결론
FnOnce는 소유권을 move해서 내부 값을 소비하는 클로저를 위한 트레잇.
그래서 한 번만 호출 가능하고,
Rust의 소유권 시스템과 함수형 스타일이 결합된 대표적인 개념.

----



