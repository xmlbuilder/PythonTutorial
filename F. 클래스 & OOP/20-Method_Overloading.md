## 📘 Method Overloading

- 이 코드는 Python에서 **Method Overloading(메소드 오버로딩)** 을 구현하는 다양한 방식과 그 한계를 아주 잘 보여줌.  
- Python은 기본적으로 오버로딩을 지원하지 않기 때문에, 실무에서는 *args, 타입 분기, 또는 multipledispatch를 활용해 유사한 효과를 구현.  

### 📌 핵심 개념: Method Overloading
- 같은 이름의 메소드를 파라미터 수나 타입에 따라 다르게 동작하도록 정의하는 것
    - Python은 기본적으로 오버로딩을 지원하지 않음
    - 마지막에 정의된 메소드만 유효함
    - 따라서 *args, 조건문, multipledispatch로 우회 구현

### 📌 메소드 오버로딩 효과
| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 기능 통합           | 동일한 메소드 이름으로 다양한 입력을 처리 → 인터페이스 일관성 유지            |
| 코드 절약           | 중복 제거로 간결한 코드 작성 가능 → 유지보수 효율 향상                      |
| 가독성 향상         | 메소드 이름 예측 가능 → 사용자가 기능을 쉽게 이해하고 활용 가능               |
| 파라미터 기반 분기    | 입력 개수나 타입에 따라 동작을 다르게 설정 가능 → 유연한 함수 설계 가능         |
| 확장성 확보          | 새로운 입력 타입이나 구조에 맞춰 쉽게 기능 추가 가능 → 플러그인 구조에 적합     |

### 📌 설치가 필요함
```
pip install multipledispatch
```

### 📌 예제 코드
```python
class SampleA():
    def add(self, x, y):
        return x + y

    def add(self, x, y, z):
        return x + y + z

a = SampleA()

print("x+y = ", a.add(2, 3))
```
```
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/variable_scope.py", line 26, in <module>
    print("x+y = ", a.add(2, 3))
                    ^^^^^^^^^^^
TypeError: SampleA.add() missing 1 required positional argument: 'z'
```
```python
print("x+y+z = ", a.add(2, 3, 4))

print("dir : a", dir(a))
```
#### 🔹 출력 결과
```
dir : a ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__',
'__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__',
'__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__',
'__str__', '__subclasshook__', '__weakref__', 'add']
```
#### 🔹 Packing 처리
```python
class SampleA():
    def add(self, *args):  # packing 으로 처리
        return sum(args)

    def sum(self, args):
        result = 0
        for value in args:
            result += value
        return result

a = SampleA()

print("x+y = ", a.add([1, 2, 3])) #6
```

### 📌 동일 이름 메소드 사용 예제
#### 🔹 자료형에 따른 분기 처리
```python
class SampleB():
    def add(self, datatype, *args):
        if datatype == 'int':
            return sum(args)
        if datatype == 'str':
            return ''.join([x for x in args])

b = SampleB()
print("1, 2, 3, 4 add", b.add('int', 1, 2, 3, 4))  # 1, 2, 3, 4 add 10
print("a, b, c, d add", b.add("str", 'a', 'b', 'c', 'd'))  # a, b, c, d add abcd
```

### 📌 multipledispatch
```python
from multipledispatch import dispatch

class SampleC():
    @dispatch(int, int)
    def product(self, x, y):
        return x * y

    @dispatch(int, int, int)
    def product(self, x, y, z):
        return x * y * z

    @dispatch(float, float, float)
    def product(self, x, y, z):
        return x * y * z

c = SampleC()

print("1 * 2 = ", c.product(1, 1))  # 1 * 2 =  1
print("1 * 2 * 3 = ", c.product(1, 2, 3))  # 1 * 2 * 3 =  6
print("1.1 * 2.2 * 3.3 = ", c.product(1.1, 2.2, 3.2))  # 1.1 * 2.2 * 3.3 =  7.7440000000000015
```

```python
from multipledispatch import dispatch

@dispatch(int, int)
def join(x, y):
    return x + y

@dispatch(float, int)
def join(x, y):
    return x + y

print(join(2, 3))
```
#### 🔹 출력 결과

```
5
```


```python
print(join(2.0, 3))
```
#### 🔹 출력 결과
```
5.0
```


```python
print(join.funcs)
```
#### 🔹 출력 결과

```
{(<class 'int'>, <class 'int'>): <function join at 0x00000198E3D0A020>,
(<class 'float'>, <class 'int'>): <function join at 0x00000198E3D0A0C0>}
```

```python
print(join.funcs[(int, int)])
```
#### 🔹 출력 결과
```
<function join at 0x0000027C0FC9A020>
```


```python
print(join.funcs[(float, int)])
```
#### 🔹 출력 결과
```
<function join at 0x0000027C0FC9A020>
```


```python
def float_add(x, y):
    return x + y

def float_add2(x, y, z):
    return x + y + z

join.add((float, float), float_add)
join.add((float, float, float), float_add2)

print(join(1.0, 2.5))
```
#### 🔹 출력 결과
```
3.5
```


```python
print(join(1.0, 2.0, 3.0))
```

#### 🔹 출력 결과
```
6.0
```

### 📌 예제 분석
#### 🔹 SampleA – 오버로딩 실패 사례
```python
class SampleA:
    def add(self, x, y): ...
    def add(self, x, y, z): ...
```

- Python은 마지막 정의만 유효 → add(self, x, y, z)만 남음
- add(2, 3) 호출 시 TypeError 발생 가능성 있음

#### 🔹 SampleB – 타입 기반 분기 처리
```python
class SampleB:
    def add(self, datatype, *args):
        if datatype == 'int': return sum(args)
        if datatype == 'str': return ''.join(args)
```
- 첫 번째 인자로 타입을 명시하여 분기
- 실무에서 간단한 오버로딩 대체 방식으로 자주 사용됨

#### 🔹 SampleC – multipledispatch 활용
```python
from multipledispatch import dispatch

class SampleC:
    @dispatch(int, int)
    def product(self, x, y): return x * y

    @dispatch(int, int, int)
    def product(self, x, y, z): return x * y * z

    @dispatch(float, float, float)
    def product(self, x, y, z): return x * y * z


- @dispatch 데코레이터로 파라미터 타입에 따라 자동 분기
- product(1, 2) → 정수 버전 호출
- product(1.0, 2.0, 3.0) → 실수 버전 호출
```
#### 🔹 전역 함수 join – 동적 확장
```python
@dispatch(int, int)
def join(x, y): return x + y

@dispatch(float, int)
def join(x, y): return x + y

join.add((float, float), float_add)
join.add((float, float, float), float_add2)
```
- `join.funcs` 로 등록된 함수 목록 확인 가능
- `join.add()` 로 새로운 타입 조합을 동적으로 추가 가능
- 실무에서 플러그인 구조, API 확장에 유용

---

### 📌 특징 요약 – Method Overloading 구현 방식

| 방식               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `*args`            | 파라미터 개수에 따라 동작 분기. 간단하고 유연하지만 타입 제어는 직접 구현해야 함     |
| 타입 분기 처리       | `datatype` 인자 또는 `isinstance()`로 타입에 따라 분기. 명시적이고 직관적이며 제어 가능 |
| `multipledispatch` | 파라미터 타입에 따라 자동으로 적절한 함수 호출. 함수 등록 및 확장 가능. 실무에서 유연한 API 설계에 적합 |

### 📌 실무에서 왜 중요한가?
| 목적               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 인터페이스 통합      | 동일한 메소드 이름으로 다양한 입력을 처리 → API 일관성 유지                   |
| 코드 재사용          | 중복 제거로 간결한 코드 작성 가능 → 유지보수 효율 향상                      |
| 기능 확장           | 새로운 입력 타입이나 구조에 맞춰 쉽게 기능 추가 가능                         |
| 타입 기반 제어        | 입력 타입에 따라 자동 분기 가능 → 실수 방지, 안정성 향상                    |
| 유연한 설계 구조      | `multipledispatch`를 활용하면 런타임에 동적으로 함수 확장 가능 → 플러그인 구조에 적합 |

---

### 📌 join.add
- join.add(...)로 새로운 동작 타입을 추가하는 방식은 multipledispatch 라이브러리의 핵심 기능. 
- Python에서 기본적으로 지원하지 않는 메소드 오버로딩을 타입 기반으로 구현할 수 있게 해줌. 

### 📌 핵심 구조: multipledispatch의 함수 객체
```python
from multipledispatch import dispatch

@dispatch(int, int)
def join(x, y): return x + y
```
- @dispatch는 join을 다중 디스패치 함수 객체로 등록함
- 내부적으로 join은 Dispatcher 클래스의 인스턴스가 됨
- 이 객체는 .add() 메서드를 통해 새로운 타입 조합과 대응 함수를 추가할 수 있음

### 📌 동작 원리
```python
def float_add(x, y): return x + y
def float_add2(x, y, z): return x + y + z

join.add((float, float), float_add)
join.add((float, float, float), float_add2)
```
- join.add((타입 튜플), 함수) 형태로 새로운 타입 조합을 등록
- 내부적으로 `join.funcs[(float, float)] = float_add` 처럼 저장됨
- 호출 시 `join(1.0, 2.5)` → 타입이 `(float, float)` 이므로 float_add 실행

### 📌 multipledispatch 핵심 구성 요약

| 구성 요소           | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| `.add()`             | 새로운 타입 조합과 대응 함수를 등록. 런타임에 동적으로 기능 확장 가능         |
| `.funcs`             | 등록된 모든 타입 조합과 함수 매핑을 저장하는 딕셔너리 (`dict`) 형태             |
| `.dispatch()`        | 특정 타입 조합에 대응하는 함수를 반환. 예: `join.dispatch(float, float)`       |
| `.dispatch_iter()`   | 가능한 모든 타입 조합을 순회하며 대응 함수 반환. 디버깅이나 분석에 유용          |

### 📌 실무 활용 예시
#### 🔹 플러그인 구조
```python
# 기본 기능
@dispatch(str, str)
def process(a, b): return a + b

# 외부에서 기능 확장
def reverse_concat(a, b): return b + a
process.add((str, str), reverse_concat)  # 덮어쓰기 가능
```
- 외부 모듈이나 설정 파일에서 기능을 동적으로 확장 가능
- 플러그인 시스템, 커스텀 처리 로직에 적합

#### 🔹 API 설계
```python
@dispatch(dict)
def handle(data): return "JSON"

@dispatch(list)
def handle(data): return "Array"

@dispatch(str)
def handle(data): return "Text"
```

- 입력 타입에 따라 자동 분기
- RESTful API, 데이터 처리 파이프라인 등에서 유용

---

### 📌 @dispatch add

- @dispatch로 선언된 함수는 내부적으로 Dispatcher 객체로 변환되기 때문에, 그 이후에는 계속해서 새로운 타입 조합과 대응 함수를 추가할 수 있음. 
- 이건 마치 함수가 하나의 타입 기반 라우터처럼 동작.

#### 🔹 어떻게 가능한가?
- @dispatch(...)를 쓰면 함수가 Dispatcher 인스턴스로 바뀜
- 이 객체는 .add() 메서드를 통해 새로운 타입 조합을 등록할 수 있음
- 등록된 타입 조합은 .funcs라는 딕셔너리에 저장됨
- 호출 시, 인자의 타입을 보고 자동으로 해당 함수로 분기함

#### 🔹 예시: 계속 확장되는 함수
```python
@dispatch(int, int)
def calc(x, y): return x + y

@dispatch(str, str)
def calc(x, y): return x + y

# 이후에 동적으로 추가
def multiply(x, y): return x * y
calc.add((float, float), multiply)

def concat_three(x, y, z): return x + y + z
calc.add((str, str, str), concat_three)
```
- calc(1.0, 2.0) → multiply() 호출
- calc("a", "b", "c") → concat_three() 호출

### 📌 Dispatcher 객체의 특징

| 구성 요소             | 설명                                                                 |
|------------------------|----------------------------------------------------------------------|
| 타입 기반 자동 분기      | 인자의 타입에 따라 적절한 함수가 자동으로 호출됨                           |
| `.add()`               | 새로운 타입 조합과 대응 함수를 런타임에 등록 가능 → 유연한 기능 확장 가능       |
| `.funcs`               | 등록된 모든 타입 조합과 함수 매핑을 딕셔너리 형태로 저장 (`dict`)               |
| `.dispatch()`          | 특정 타입 조합에 대응하는 함수를 직접 반환 → 내부 로직 확인이나 테스트에 유용     |
| `NotImplementedError` | 등록되지 않은 타입 조합으로 호출 시 발생 → 안전한 타입 제어와 디버깅에 유리       |

---

### 📌 multipledispatch 가 가능한 이유

- Python의 동적이고 객체 중심적인 구조, 특히 dict 기반의 내부 구현 덕분에 가능.

### 📌 왜 가능한가? – Python의 구조적 특성
#### 🔹 1. 함수도 객체다 (First-class object)
- Python에서는 함수도 객체로 취급됨
    - 즉, 변수에 할당하거나, 다른 함수에 전달하거나, 속성을 추가할 수 있음
#### 🔹 2. Dispatcher는 내부적으로 dict를 사용
- multipledispatch.Dispatcher 객체는 .funcs라는 속성에 타입 튜플을 키로, 대응 함수를 값으로 저장
    - 예시:
```python
join.funcs = {
    (int, int): <function join at 0x...>,
    (float, int): <function join at 0x...>
}
```

#### 🔹 3. 타입 기반 조회가 dict로 빠르게 가능
- 호출 시, 인자의 타입을 튜플로 묶어서 dict에서 조회
- 없으면 NotImplementedError 발생 → 안전한 타입 제어

#### 🔹 Dispatcher 내부 흐름 요약
```python
def dispatch_call(*args):
    types = tuple(type(arg) for arg in args)
    func = dispatcher.funcs.get(types)
    if func:
        return func(*args)
    else:
        raise NotImplementedError
```

- 이처럼 type(arg)로 타입 튜플을 만들고 dict에서 조회하는 구조
- Python의 dict는 해시 기반이라 빠르고 유연함

### 📌 Python 구조 기반 요약 – multipledispatch 동작 원리

| 구성 요소         | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 함수 객체화         | Python에서 함수는 객체로 취급됨 → 속성 추가 및 동적 확장 가능                  |
| `.add()`           | Dispatcher 객체에 새로운 타입 조합과 대응 함수를 등록하는 메서드               |
| `dict` 기반 매핑    | `.funcs` 속성은 타입 튜플을 키로, 대응 함수를 값으로 저장하는 딕셔너리 구조       |
| 타입 튜플 조회      | 호출 시 인자의 타입을 튜플로 묶어 `dict`에서 빠르게 조회하여 적절한 함수 실행       |
| 안전한 분기 처리     | 등록되지 않은 타입 조합은 `NotImplementedError` 발생 → 디버깅과 안정성 확보        |

---





