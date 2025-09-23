# Function Chaining
함수형 프로그래밍의 핵심 장점인 **함수 체이닝(Function Chaining)**을 Python으로 구현.
아래에 그 개념과 동작 원리를 정리.

## 🧠 함수형 프로그래밍의 큰 장점: 체이닝
### ✅ 정의
함수 체이닝은 여러 함수를 순차적으로 연결해서
데이터 흐름을 함수 중심으로 구성하는 방식.

- 각 함수는 입력을 받아 다음 함수를 반환
- 최종 결과는 연결된 함수들을 순차적으로 실행한 결과

### 🔧 Python으로 구현한 체이닝 구조
```python
import functools as ft

def add(x, y):
    return ft.partial(mul, x + y)

def mul(x, y):
    return ft.partial(sub, x * y)

def sub(x, y):
    return ft.partial(div, x - y)

def div(x, y):
    return x / y
```
### 예제 코드
```python


import functools as ft

def add(x, y):
    return ft.partial(mul, x+y)

def mul(x, y):
    return ft.partial(sub, x*y)

def sub(x, y):
    return ft.partial(div, x-y)

def div(x, y):
    return x/y

print(add(5, 6)(4)(5)(5))
'''7.8'''

a = add(5, 6)
b = a(4)
c = b(5)
d = c(5)
print(d)
'''7.8'''

```


### 🔄 실행 흐름
```
add(5, 6) → mul(11)
mul(11)(4) → sub(44)
sub(44)(5) → div(39)
div(39)(5) → 7.8
```
- 각 함수는 ft.partial()을 통해 다음 함수를 반환
- 인자를 하나씩 받아가며 연결된 계산 흐름을 구성

## 💡 핵심 개념 요약: 함수 체이닝과 functools.partial

| 개념            | 키워드 또는 구조         | 설명 |
|-----------------|--------------------------|------|
| 함수 체이닝      | `ft.partial()`           | 인자를 고정한 함수 반환 → 다음 함수로 연결 가능 |
| 커링(Currying)  | `partial`, `lambda`      | 여러 인자를 나눠서 단계적으로 적용 |
| 순수 함수        | `def` + 반환만 존재      | 상태 없이 입력 → 출력만 처리 |
| 상태 없음        | 함수형 설계의 기본       | 부작용 없이 흐름 제어 가능 |
| 가독성 향상      | 체이닝 구조              | 복잡한 로직을 단계별로 분리 가능 |


## 📘 결론
함수형 프로그래밍의 체이닝은
복잡한 로직을 단순한 함수 조합으로 표현할 수 있게 해줌.
Python에서도 커링 + 체이닝을 구현할 수 있다는 걸 보여주는 사례.

---

# 🧠 1. Python 확장: map, reduce, pipe 스타일
## ✅ map과 reduce 활용
```python
from functools import reduce

data = [1, 2, 3, 4]

# map: 각 요소에 함수 적용
mapped = map(lambda x: x * 2, data)  # [2, 4, 6, 8]

# reduce: 누적 계산
total = reduce(lambda acc, x: acc + x, data)  # 10
```

- map: 각 요소에 함수 적용
- reduce: 누적 계산 흐름 구성
- 체이닝은 pipe 스타일로 표현 가능
## ✅ pipe 스타일 (직접 구현)
```python
def pipe(value, *funcs):

    for f in funcs:
        value = f(value)
    return value

result = pipe(5,
              lambda x: x + 2,
              lambda x: x * 3,
              lambda x: x - 4)
print(result)  # 17
```

- pipe()는 함수형 체이닝을 명시적으로 표현
- 너의 ft.partial() 구조와 유사하게 단계별 흐름을 구성

## 🧠 2. JavaScript: compose와 체이닝
### ✅ compose 구현
```javascript
const compose = (...funcs) => x =>
    funcs.reduceRight((acc, f) => f(acc), x);

const add2 = x => x + 2;
const mul3 = x => x * 3;
const sub4 = x => x - 4;

const result = compose(sub4, mul3, add2)(5); // ((5 + 2) * 3) - 4 = 17
console.log(result);
```

- compose(f, g, h)(x)는 f(g(h(x)))처럼 우측부터 적용
- Python의 pipe()는 좌측부터 적용 → compose()와 반대 방향

### ✅ 체이닝 스타일
```javascript
const result = [1, 2, 3, 4]
    .map(x => x + 1)
    .filter(x => x % 2 === 0)
    .reduce((acc, x) => acc + x, 0);
console.log(result); // 6
```

- JavaScript는 배열 메서드 체이닝이 매우 강력함
- map → filter → reduce는 함수형 흐름의 대표 구조

##  🧠 3. Rust: Iterator.chain()과 함수형 흐름
### ✅ 기본 체이닝
```rust
let result: i32 = [1, 2, 3]
    .iter()
    .map(|x| x + 1)
    .filter(|x| x % 2 == 0)
    .fold(0, |acc, x| acc + x);
println!("{}", result); // 6
```


- Rust는 map, filter, fold를 Iterator trait로 제공
- 체이닝은 lazy evaluation 기반으로 최적화됨
### ✅ chain()으로 연결
```python
let a = [1, 2];
let b = [3, 4];

let chained: Vec<_> = a.iter().chain(b.iter()).collect();
println!("{:?}", chained); // [1, 2, 3, 4]
```

- chain()은 두 이터레이터를 하나로 연결
- Python의 itertools.chain()과 유사

## 📘 결론 요약: 함수형 체이닝 비교

| 언어        | 체이닝 방식                         | 특징 요약                         |
|-------------|-------------------------------------|-----------------------------------|
| Python      | `map`, `reduce`, `pipe`, `partial` | 명시적 흐름, 커링 가능, 가독성 우수 |
| JavaScript  | `compose`, `map/filter/reduce`     | 자유로운 함수 조합, 배열 중심 체이닝 |
| Rust        | `Iterator.chain()`, `map`, `fold`  | 타입 안전, lazy 평가, 고성능 처리 |


---

# C++ 구현

## 🔧 Function Chaining 구현 방식
### 1. 함수 객체(Functor) + operator() 오버로드
```cpp
struct Add {
    int x;
    Add(int v) : x(v) {}
    int operator()(int y) const { return x + y; }
};

struct Mul {
    int x;
    Mul(int v) : x(v) {}
    int operator()(int y) const { return x * y; }
};

// 체이닝
int result = Mul(4)(Add(5)(100)); // (100 + 5) * 4 = 420
```

- 함수 객체를 중첩 호출 → 체이닝처럼 동작
### 2. 커링 스타일 람다
```cpp
auto add = [](int x) {
    return [x](int y) { return x + y; };
};

auto mul = [](int x) {
    return [x](int y) { return x * y; };
};

int result = mul(4)(add(5)(100)); // 420
```

- 람다로 커링 구조 구현 → 체이닝 가능
### 3. 파이프 스타일 with operator overloading
```cpp
template<typename F, typename G>
auto compose(F f, G g) {
    return [=](auto x) { return g(f(x)); };
}

auto f = compose([](int x){ return x + 5; },
                 [](int x){ return x * 4; });

int result = f(100); // (100 + 5) * 4 = 420
```

- compose()로 함수 체이닝 구성

## 📘 결론
C에서는 Method Chaining은 자연스럽게 되지만,
Function Chaining은 람다, 함수 객체, 커링, compose 구조를 활용해서
충분히 구현 가능해.
너처럼 직접 템플릿과 메모리 구조를 설계하는 사람이라면
**함수형 스타일의 체이닝도 C에서 자유롭게 구현할 수 있어.**

---





