# Score / Closure / Global / nonlocal
Python의 변수 범위(Scope), 클로저(Closure), 전역(Global) 처리 방식은 JavaScript와 비교했을 때 덜 자유롭고  
더 엄격한 구조를 가지고 있어서 과거 C/C++ 스타일에 익숙한 사람에게는 헷갈림을 유발하는 지점이 많음.

## 🧠 Python vs JavaScript: Scope & Closure 비교
| 개념 항목         | Python 키워드/구조        | JavaScript 키워드/구조       |
|------------------|----------------------------|-------------------------------|
| 함수 정의         | `def`                      | `function`, `=>`              |
| 변수 스코프       | `nonlocal`, `global`       | `let`, `const`, `var`         |
| 블록 스코프       | 없음 (함수 단위 스코프)    | `let`, `const` (블록 스코프) |
| 전역 접근         | `global`                   | `window`, `globalThis`        |
| 불변 데이터 표현  | `tuple`                    | `const`                       |
| 클로저 지원       | `__closure__`, `nonlocal`  | 자유로운 캡처 (자동 클로저)  |


## 🔍 Python의 변수 범위 예외: 왜 헷갈릴까?
```python
c = 30
def func_v3(a):
    print(a)
    print(c)  # 여기서 c는 전역처럼 보이지만
    c = 40    # 이 줄 때문에 Python은 c를 지역 변수로 간주
```

- Python은 함수 내부에서 변수에 할당이 있으면 무조건 지역 변수로 간주
- 그래서 print(c)는 아직 지역 변수 c가 초기화되지 않았다고 판단해서 `UnboundLocalError` 발생

### 해결 방법
- global c → 전역 변수로 명시
- nonlocal c → 클로저 내부에서 상위 함수의 지역 변수로 명시

## 🔍 JavaScript는 더 자유롭지만 더 위험함
```javascript
let c = 30;
function func_v3(a) {
    console.log(a);
    console.log(c); // 외부 변수 참조 가능
    c = 40;         // 외부 변수 덮어쓰기 가능
}
func_v3(10);
console.log(c); // 40
```
- JavaScript는 외부 변수 참조와 수정이 자유로움
- 하지만 이 자유로움이 예측 불가능한 사이드 이펙트를 유발할 수 있어

## 🧩 클로저의 본질: 상태를 은닉하고 공유하되 변경하지 않기
- Python에서는 클래스나 nonlocal을 활용해서 클로저를 구현하고
- JavaScript에서는 함수 자체가 클로저로 동작해서 더 직관적이야.

### Python 예시
```python
def make_averager():
    series = []
    def averager(v):
        series.append(v)
        return sum(series) / len(series)
    return averager

avg = make_averager()
print(avg(10))  # 10.0
print(avg(20))  # 15.0
```
- series는 make_averager의 지역 변수지만 averager가 참조함
- nonlocal 없이도 리스트는 참조 가능하지만, 숫자라면 `nonlocal` 이 필요

## 📘 결론
- Python은 명시적 제어를 강조해서 안전하지만, 처음엔 헷갈릴 수 있음
- JavaScript는 자유로운 참조와 수정이 가능하지만, 사이드 이펙트에 취약함
- 클로저는 두 언어 모두에서 상태 은닉과 함수형 설계에 핵심적인 역할을 함
- Python에서는 nonlocal, global, callable, __closure__ 같은 내부 구조를 이해하면  
    더 정교한 클로저 설계를 할 수 있어
---

JavaScript는 {} 블록 스코프에 갇히지 않는 var와, 블록 스코프에 갇히는 let, const가 공존하는 언어.
그리고 함수 스코프는 언제나 강력하게 작동해서, 함수 안에서 선언된 변수는 함수 밖에서는 절대 접근할 수 없음.

## 🧠 JavaScript의 스코프 핵심 요약
| 키워드   | 스코프 종류     | 블록 `{}` 영향 | 특징 요약                          |
|----------|------------------|----------------|------------------------------------|
| `var`    | 함수 스코프      | 무시됨         | 선언 끌어올림(hoisting), 재선언 가능 |
| `let`    | 블록 스코프      | 적용됨         | TDZ 존재, 재선언 불가               |
| `const`  | 블록 스코프      | 적용됨         | TDZ 존재, 재할당/재선언 불가        |

### 🔍 예시로 이해하기
```javascript
function test() {
    console.log(c); // undefined
    var c = 40;
    console.log(c); // 40
}
test();
```
- var c = 40은 호이스팅돼서 var c가 함수 시작 부분으로 끌어올려짐
- 그래서 첫 번째 console.log(c)는 undefined가 출력됨
- 두 번째 console.log(c)는 40이 출력됨

### 반면 let이나 const는 다르게 동작해
```javascript
function test() {
    console.log(c); // ReferenceError: Cannot access 'c' before initialization
    let c = 40;
}
```
- let은 호이스팅은 되지만 초기화는 안 됨
- 그래서 **Temporal Dead Zone(TDZ)** 에 걸려서 ReferenceError가 발생함

### 🔒 함수 스코프는 항상 강력하게 작동
```javascript
function test() {
    let c = 40;
}
console.log(c); // ReferenceError: c is not defined
```
- 함수 안에서 선언된 변수는 함수 밖에서는 절대 접근 불가
- 이건 Python과 동일한 규칙

## 📘 결론
- JavaScript는 {} 블록 스코프에 자유로운 것처럼 보이지만 함수 스코프는 철저하게 지켜진다
- var는 호이스팅 때문에 헷갈릴 수 있고, let과 const는 TDZ 때문에 더 엄격하게 동작한다
- Python은 블록 스코프가 없고, 함수 스코프만 존재하므로 오히려 스코프 규칙은 더 단순하지만, 명시적 제어(global, nonlocal)가 필요

## 🧠 클로저로 변수 c를 살아남게 만드는 방식
```javascript
function makeClosure() {
    let c = 40;
    return function() {
        return c;
    };
}
const getC = makeClosure();
console.log(getC()); // 40
```

- makeClosure()는 c를 지역 변수로 선언하고
- 내부 함수가 c를 참조한 채로 반환됨 → 이게 클로저
- getC()는 c를 직접 접근하지 않지만, 함수 내부의 환경을 기억하고 있음

## 🔍 클로저의 핵심: **함수가 선언될 당시의 환경을 기억한다**
- JavaScript는 함수가 생성될 때 자신이 선언된 스코프를 캡처함
- 그래서 c는 makeClosure()가 종료된 뒤에도 메모리에서 살아남아 있음
- 이건 Python의 __closure__와 유사한 구조
  
## 💡 실전 활용 예시: 상태 은닉
```javascript
function counter() {
    let count = 0;
    return function() {
        count += 1;
        return count;
    };
}

const next = counter();
console.log(next()); // 1
console.log(next()); // 2
console.log(next()); // 3
```
- count는 외부에서 접근 불가능하지만
- 내부 함수가 count를 계속 참조하고 수정함 → 상태 은닉 + 지속성 유지

## 📘 결론
- JavaScript는 변수 c를 직접 꺼낼 수는 없지만 함수에 담아서 내보내면 클로저로 살아남는다.
- 이건 JavaScript의 가장 강력한 기능 중 하나고, 함수형 프로그래밍, 비동기 처리, UI 상태 관리에 핵심적으로 쓰임.

- JavaScript의 `클로저` 와 Python의 `nonlocal` 을 활용한 클로저를 나란히 비교.
- 두 언어 모두 클로저를 지원하지만, Python은 명시적 제어가 필요하고, JavaScript는 자동 캡처 방식.

## 🧠 JavaScript 클로저 예시
```javascript
function makeCounter() {
    let count = 0;
    return function() {
        count += 1;
        return count;
    };
}

const counter = makeCounter();
console.log(counter()); // 1
console.log(counter()); // 2
```
- count는 makeCounter의 지역 변수지만
- 내부 함수가 count를 참조하고 수정 → 클로저로 상태 유지

## 🧠 Python 클로저 + `nonlocal` 예시
```python
def make_counter():
    count = 0
    def counter():
        nonlocal count
        count += 1
        return count
    return counter

counter = make_counter()
print(counter())  # 1
print(counter())  # 2
```
- count는 make_counter의 지역 변수
- 내부 함수에서 count += 1을 하려면 `nonlocal` 로 상위 스코프 변수임을 명시해야 함
- 그렇지 않으면 Python은 count를 새로운 지역 변수로 간주해서 UnboundLocalError 발생


## 🔍 클로저 및 스코프 처리: JavaScript vs Python 핵심 차이 요약

| 항목               | JavaScript                          | Python                              | 비고 |
|--------------------|--------------------------------------|--------------------------------------|------|
| 클로저 생성 방식   | 자동 캡처                            | 명시적 캡처 (`nonlocal`)             | Python은 수정 시 `nonlocal` 필요 |
| 변수 수정 가능 여부| 자유롭게 수정 가능                   | `nonlocal` 없으면 수정 불가          | 리스트 등 참조형은 예외적 수정 가능 |
| 스코프 규칙        | 블록/함수 스코프 혼합               | 함수 스코프만 존재                   | Python은 블록 스코프 없음 |
| 상태 은닉 방식     | 함수 내부 변수 자동 유지             | `nonlocal`로 상위 함수 변수 유지     | 클로저로 은닉된 상태 유지 |



## 📘 결론
- JavaScript는 클로저를 자연스럽게 생성하고 수정할 수 있는 자유로운 구조
- Python은 클로저를 안전하게 제어할 수 있도록 명시적 키워드(nonlocal)를 요구
- 두 언어 모두 클로저는 상태 은닉, 함수형 설계, 비동기 처리에 핵심적인 도구


## 🧠 C++ 클로저의 위험: 스택 변수 캡처
### ❌ 위험한 예시
```cpp
std::function<void()> make_lambda() {
    int x = 42;
    return [&]() { std::cout << x << std::endl; };
}
```
auto f = make_lambda(); // x는 이미 소멸됨
f(); // UB (Undefined Behavior)
- x는 make_lambda()의 지역 변수 → 스택에 존재
- f()는 x를 참조하려고 하지만, 이미 스택에서 사라짐
- 결과: 런타임 오류 또는 이상한 값 출력

### 🔧 안전하게 쓰는 방법
#### ✅ 값으로 캡처
```cpp
std::function<void()> make_lambda() {
    int x = 42;
    return [x]() { std::cout << x << std::endl; };
}
```
- x를 복사해서 람다 내부에 저장 → 안전
#### ✅ 동적 메모리로 캡처
```cpp
std::function<void()> make_lambda() {
    auto x = std::make_shared<int>(42);
    return [x]() { std::cout << *x << std::endl; };
}
```
- shared_ptr로 캡처하면 스택 소멸과 무관하게 생존 가능

### 🦀 Rust는 왜 안전한가?
```rust
fn make_closure() -> impl Fn() {
    let x = 42;
    move || println!("{}", x)
}
```
- move 클로저는 x의 소유권을 가져감
- Rust는 스택에서 사라질 변수는 캡처 불가 → 컴파일 에러로 막아줌
- 그래서 런타임 오류가 아니라 컴파일 타임에 안전성 확보

---
