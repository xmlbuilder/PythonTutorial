# 🧠 일급 함수 (First-class Function)
- Python에서 함수는 일급 객체로 취급.  
- 즉, 함수도 변수처럼 다룰 수 있음.


## ✅ 일급 함수 특징 요약
| 기능 항목               | 예시 코드 또는 설명                  |
|------------------------|--------------------------------------|
| 변수에 할당 가능       | `var_func = factorial`               |
| 함수 인수로 전달 가능  | `map(f, data)`                       |
| 함수 결과로 반환 가능  | `return lambda x: x + 1`             |
| 고위 함수 지원         | `map`, `filter`, `reduce`, `partial` |
| 런타임 객체로 취급     | `type(factorial) → <class 'function'>` |
| 호출 가능 여부 확인    | `callable(factorial)` → `True`       |


## 실전 예제
```python
def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)

print(factorial(5))
```
```
120
```
```python
print(type(factorial))
```
```
<class 'function'>
```
```python
print(dir(factorial))
```
```
['__annotations__', '__builtins__', '__call__', '__class__', '__closure__', '__code__', '__defaults__',
'__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__get__', '__getattribute__',
'__getstate__', '__globals__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__kwdefaults__', '__le__',
'__lt__', '__module__', '__name__', '__ne__', '__new__', '__qualname__', '__reduce__', '__reduce_ex__', '__repr__',
'__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__type_params__']
```
```python
class A:
    pass

print(set(sorted(dir(factorial))) - set(sorted(dir(A))))
```
```
{'__globals__', '__qualname__', '__builtins__', 
'__name__', '__kwdefaults__', '__code__', '__closure__', 
'__get__', '__type_params__', '__defaults__', '__call__', '__annotations__'}
```
```python
print(factorial.__name__)
```
```
factorial
```

```python
print(factorial.__code__)
```

```
<code object factorial at 0x1014ee6a0, file "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 12>
```

### 변수 할당 가능
```python
var_func = factorial
print(var_func)
```
```
<function factorial at 0x1036b6340>
```
```python
print(var_func(10))
```
```
3628800
```

## 🔍 실전 예제 요약
- factorial 함수는 재귀로 정의되고, 변수에 할당 가능
- map, filter, reduce로 고위 함수 활용

```python
print(map(var_func, range(1, 11)))
```
```
<map object at 0x103f06470>
```
```python
print(list(map(var_func, range(1, 11))))
```
```
[1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800]
```
```python
# 함수 인수 전달 및 함수로 결과 반환 -> 고위 함수(Higher-order function)
# map, filter, reduce
print([var_func(i) for i in range(1, 6) if i % 2 != 0])
```
```
[1, 6, 120]
```
```python
print(list(map(var_func, filter(lambda i: i % 2 != 0, range(1, 6)))))
```
```
[1, 6, 120]
```
```python
from functools import reduce
print(reduce(lambda x, y: x * y, range(1, 6), 10))
```
```
1200
````
- partial로 인수 고정 → 콜백 함수처럼 사용 가능
```python
from operator import mul
from functools import partial

print(mul(10, 10), 10*10)
```
```
100 100
```
```python
# 인수 고정
five_mul = partial(mul, 5)
print(five_mul(10))
```
```
50
```
```python
# 고정 추가
six_mul = partial(five_mul, 6)
print(six_mul())
```
```
30
```
```python
print([five_mul(i) for i in range(1, 11)])
```
```
[5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
```
```python
print(list(map(five_mul, range(1, 11))))
```
```
[5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
```

- callable()로 함수 여부 확인 가능
```python
# Callable -> 메소드 호출로 가능
print(callable(str))
```
```
True
```
```python
print(callable(list), callable(var_func), callable(factorial), callable(3.14))
```
```
True True True False
```

## 🧩 함수형 프로그래밍 vs 객체지향 프로그래밍

| 항목             | 함수형 프로그래밍                            | 객체지향 프로그래밍                          |
|------------------|----------------------------------------------|----------------------------------------------|
| 핵심 개념        | 순수 함수, 불변성, 고차 함수                  | 클래스, 객체, 캡슐화, 상속                   |
| 상태 관리        | 상태 없음 (불변 데이터)                      | 상태 보존 (객체 내부에 저장)                 |
| 코드 흐름        | 선언적 (무엇을 할지 기술)                    | 명령적 (어떻게 할지 기술)                    |
| 테스트 용이성    | 높음 (사이드 이펙트 없음)                    | 중간 (상태 의존성 있음)                      |
| 확장성           | 함수 조합으로 확장                           | 상속과 다형성으로 확장                       |
| 디버깅 난이도     | 낮음 (함수 단위로 분리)                      | 높음 (객체 간 상호작용 추적 필요)           |
| 대표 언어        | Haskell, Elixir, JavaScript                  | Java, C++, Python                            |
| 실전 적용 방식   | 데이터 흐름 중심, map/filter/reduce 활용     | 도메인 모델 중심, 클래스 기반 설계           |


### 💬 극단적 강조에 대한 균형
- 함수형만 강조하면 상태 기반 로직이나 UI 처리에 불리
- 객체지향만 강조하면 재사용성과 조합성이 떨어질 수 있음
- Python은 둘 다 지원하므로 상황에 따라 혼합 설계가 가장 이상적

## 🦀 Rust / C++ / Java에서 함수형 스타일 살리는 기법

| 언어   | 함수형 스타일 적용 기법                                               |
|--------|------------------------------------------------------------------------|
| Rust   | `iter().map().filter()`, `closure`, `Option`, `Result`, `match`, `impl Fn` |
| C++    | `std::function`, `lambda`, `std::bind`, `ranges`, `constexpr`          |
| Java   | `Stream API`, `lambda`, `Function<T,R>`, `Optional`, `Predicate`       |

### 🔧 예시: Rust에서 map/filter/reduce
```python
let result: i32 = (1..=5).filter(|x| x % 2 != 0).map(|x| factorial(x)).sum();
```

### 🔧 예시: C++에서 std::transform
```cpp
std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
```

### 🔧 예시: Java Stream
```java
List<Integer> result = list.stream()
    .filter(x -> x % 2 != 0)
    .map(x -> factorial(x))
    .collect(Collectors.toList());
```


## 📘 결론

- Python은 함수형과 객체지향을 모두 지원하는 멀티 패러다임 언어
- 함수형은 조합성과 테스트 용이성, 객체지향은 구조화와 상태 관리에 강점
- Rust/C++/Java에서도 함수형 스타일을 살릴 수 있지만, 언어 제약과 구조적 한계는 존재함
- 가장 중요한 건 문제에 맞는 패러다임을 선택하는 유연함

---

