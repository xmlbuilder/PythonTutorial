# 클래스 메소드 / 바운드 메소드
이 코드는 Python에서 클래스 메서드와 인스턴스 메서드의 차이를 보여주는 예제.  
아래에 핵심 개념과 학습 포인트를 정리.

## 🧠 핵심 개념: 클래스 메서드 vs 바운드 메서드
| 표현       | 객체 타입       | 설명                                               |
|------------|------------------|----------------------------------------------------|
| `A.func`   | `function`       | 클래스에서 직접 접근한 함수. 아직 `self`가 바인딩되지 않음 |
| `a.func`   | `bound method`   | 인스턴스에서 접근한 메서드. `self`가 `a`로 자동 바인딩됨     |
| 호출 방식  | `self` 필요      | `A.func(a)`처럼 명시적으로 `self`를 넘겨야 호출 가능         |
| 호출 방식  | `self` 자동 전달 | `a.func()`처럼 `self`가 자동으로 바인딩되어 호출됨           |

## ✅ 코드 흐름 설명
```python
class A(object):
    def func(self):
        print('function')
```

- func는 인스턴스 메서드로 정의됨 (self를 첫 번째 인자로 받음)
```python
print(A.func)
# <function A.func at 0x...>
```

- 클래스에서 직접 접근하면 func는 함수 객체로 출력됨
```python
a = A()
print(a.func)
# <bound method A.func of <__main__.A object at 0x...>>
```

- 인스턴스에서 접근하면 func는 바운드 메서드로 출력됨
- self가 a로 자동 바인딩됨


## ✅ A.func() 직접 호출 예시
```python
class A:
    def func(self):
        print("Hello from", self)

a = A()
A.func(a)  # 직접 self 인자를 넘겨 호출
```
- A.func()는 클래스에서 직접 접근한 언바운드 함수
- self 인자를 명시적으로 넘겨야 정상 호출됨


## 📘 실전 팁

| 항목             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `a.func()`       | 내부적으로 `A.func(a)`와 동일하게 동작 (`self`가 자동 전달됨)         |
| `A.func()`       | `TypeError`: `self` 인자가 없기 때문에 호출 불가능                     |
| 바운드 vs 언바운드 | 인스턴스에서 접근 시 `bound method`, 클래스에서 접근 시 `function` 객체 |
| 디버깅 시 구분     | `print(a.func)` → 바운드 메서드 / `print(A.func)` → 함수 객체 출력     |


## 🔍 확장 학습
- @classmethod, @staticmethod의 차이
- 메서드 바인딩 해제 (A.func.__get__(None, A) 등)
- 메타클래스에서 메서드 동적 생성


---

# @classmethod, @staticmethod, __get__, __call__
@classmethod, @staticmethod, __get__, __call__을 활용한 고급 메서드 개념까지 정리.

## 🧠 고급 메서드 개념 정리
### 1. @classmethod
```python
class B:
    @classmethod
    def greet(cls):
        print("Hello from class", cls)

B.greet()  # Hello from class <class '__main__.B'>
```

- 첫 번째 인자가 cls (클래스 자체)
- 클래스에서 직접 호출 가능
- 팩토리 메서드, 클래스 설정 초기화 등에 자주 사용

### 2. @staticmethod
class C:
    @staticmethod
    def greet():
        print("Hello without self or cls")

C.greet()  # Hello without self or cls


- self, cls 없이 독립적으로 동작
- 유틸리티 함수처럼 클래스 내부에 정의하고 싶을 때 사용

### 3. __get__ (디스크립터 프로토콜)
```python
class Descriptor:
    def __get__(self, instance, owner):
        print(f"Accessed from {instance} of {owner}")

class D:
    attr = Descriptor()

d = D()
d.attr  # Accessed from <__main__.D object at ...> of <class '__main__.D'>
```            

- __get__은 속성 접근 시 자동 호출됨
- 메서드 바인딩, 속성 제어 등에 사용됨

### 4. __call__ (객체를 함수처럼 호출)
```python
class E:
    def __call__(self, x):
        print(f"Called with {x}")

e = E()
e(42)  # Called with 42
```

- 객체를 함수처럼 사용할 수 있게 해줌
- 커스텀 함수 객체, 래퍼 클래스 등에 활용됨

## 📘 요약 테이블

| 정의 방식           | 첫 인자 | 호출 방식     | 특징 및 용도                                      |
|---------------------|---------|---------------|--------------------------------------------------|
| `def func(self)`    | `self`  | `obj.func()`  | 인스턴스 메서드. 객체 상태를 다루는 일반적인 메서드 |
| `@classmethod`      | `cls`   | `Class.func()`| 클래스 자체를 인자로 받음. 팩토리 메서드 등에 사용 |
| `@staticmethod`     | 없음    | `Class.func()`| 독립 함수처럼 동작. `self`, `cls` 없이 호출 가능     |
| `__get__`           | `self`  | `obj.attr`    | 디스크립터 프로토콜. 속성 접근 시 자동 호출됨       |
| `__call__`          | `self`  | `obj()`       | 객체를 함수처럼 호출 가능. 함수 객체, 래퍼 등에 활용 |


---
# functools.partial / operator.methodcaller / 데코레이터 패턴

아래는 Python에서 자주 쓰이는 고급 함수형 프로그래밍 도구인 functools.partial, operator.methodcaller, 그리고 데코레이터 패턴에 대한 정리.  
실전 예제와 함께 핵심 개념을 깔끔하게 정리.

## 🧩 1. functools.partial: 인자 고정 함수 생성
### ✅ 개념
- 기존 함수의 일부 인자를 미리 고정한 새 함수를 생성
- 반복되는 인자 설정을 줄이고, 콜백이나 람다 대체에 유용
### ✅ 예시
```python
from functools import partial

def power(base, exponent):
    return base ** exponent

square = partial(power, exponent=2)
cube = partial(power, exponent=3)

print(square(5))  # 25
print(cube(2))    # 8
```


### ✅ 실전 활용
- map(), filter()에 고정 인자 함수 전달
- GUI 이벤트 핸들러에서 인자 고정
- requests.get()에 기본 URL 고정 등

## 🧩 2. operator.methodcaller: 메서드 호출 함수 생성
### ✅ 개념
- 문자열로 메서드 이름을 받아 호출 가능한 함수 객체 생성
- 메서드 이름을 동적으로 다뤄야 할 때 유용
### ✅ 예시
```python
from operator import methodcaller

to_upper = methodcaller("upper")
print(to_upper("hello"))  # "HELLO"

strip_and_split = methodcaller("strip")
print(strip_and_split("  hello  "))  # "hello"

```

### ✅ 실전 활용
- map(methodcaller("strip"), lines)처럼 리스트 처리에 유용
- DSL, 템플릿 엔진, 동적 메서드 호출 등에 활용

## 🧩 3. 데코레이터 패턴: 함수 기능 확장
### ✅ 개념
- 기존 함수를 감싸서 전후 처리, 로깅, 검증, 캐싱 등을 추가
- @decorator_name 문법으로 간결하게 적용
### ✅ 기본 예시
```python
def logger(func):
    def wrapper(*args, **kwargs):
        print(f"Calling {func.__name__}")
        return func(*args, **kwargs)
    return wrapper

@logger
def greet(name):
    print(f"Hello, {name}")

greet("JungHwan")
# Calling greet
# Hello, JungHwan
```

## ✅ 실전 활용

| 기능                  | 활용 예시                                                              |
|-----------------------|------------------------------------------------------------------------|
| `functools.partial`   | 콜백 함수에 인자 고정, `map()`이나 `filter()`에 부분 적용 함수 전달         |
| `operator.methodcaller` | 리스트 요소에 메서드 일괄 적용 (`map(methodcaller("strip"), lines)`)     |
| 데코레이터 패턴       | 로깅, 인증, 유효성 검사, 실행 시간 측정 등 함수 기능 확장                   |
| `functools.lru_cache` | 함수 결과를 캐싱하여 반복 계산 방지, 재귀 함수 최적화                       |
| `functools.wraps`     | 데코레이터 내부에서 원래 함수의 이름과 docstring을 유지                     |
| `contextlib.contextmanager` | with 문을 위한 커스텀 컨텍스트 관리 (`@contextmanager`로 자원 관리)     |


## 📘 요약 테이블

| 기능              | 목적                         | 모듈         | 실전 활용 예시                                 |
|-------------------|------------------------------|--------------|------------------------------------------------|
| `partial`         | 인자 고정 함수 생성           | `functools`  | `map(partial(func, x), data)`                  |
| `methodcaller`    | 메서드 호출 함수 생성         | `operator`   | `map(methodcaller("strip"), lines)`            |
| `lru_cache`       | 함수 결과 캐싱                | `functools`  | `@lru_cache`로 재귀 함수 최적화, DB 캐싱 등     |
| `wraps`           | 데코레이터 내부에서 원형 유지 | `functools`  | `@wraps(func)`으로 이름, docstring 보존         |
| `contextmanager`  | 커스텀 with 블록 생성         | `contextlib` | `@contextmanager`로 자원 관리, 파일/DB 연결 등 |


---

