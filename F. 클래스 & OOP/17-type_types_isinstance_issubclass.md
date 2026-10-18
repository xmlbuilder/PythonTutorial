## 📘 type / types / isinstance / issubclass

- 이 코드는 Python에서 모듈 객체의 타입 확인과 비교를 통해 type, types, isinstance, issubclass의 개념을 익히는 데 유용.   
- 아래에 전체 코드의 취지와 학습 가능한 내용을 정리.

### 📌 코드의 취지
- math와 같은 모듈 객체의 타입 확인
- types.ModuleType을 활용한 모듈 타입 비교
- type(), isinstance(), issubclass()의 차이점 이해

### 📌 학습 내용

| 문법/기능                  | 설명                                                                 |
|----------------------------|----------------------------------------------------------------------|
| `type(obj)`                | 객체의 실제 타입을 반환 (`<class 'module'>`, `<class 'int'>` 등)       |
| `types.ModuleType`         | 모든 모듈 객체가 속하는 타입. 모듈인지 확인할 때 사용됨                |
| `type(obj) == types.X`     | 객체의 타입이 특정 클래스와 정확히 일치하는지 비교                    |
| `issubclass(type(obj), X)` | 객체의 타입이 특정 클래스의 서브클래스인지 확인                        |
| `isinstance(obj, X)`       | 객체가 특정 클래스 또는 서브클래스의 인스턴스인지 확인                 |


#### 🔹 코드 흐름 설명
```python
import types
import math

print(type(math))  # <class 'module'>
```
- math는 모듈이므로 타입은 <class 'module'>
  
```python
print(type(math) == types.ModuleType)  # True
```
- math의 타입은 `types.ModuleType` 과 정확히 일치

```python
print(issubclass(type(math), types.ModuleType))  # True
```
- type(math)이 ModuleType의 `서브클래스` 인지 확인 → True

```python
print(isinstance(math, types.ModuleType))  # True
```
- math 객체가 ModuleType의 `인스턴스` 인지 확인 → True

#### 🔹 실전 활용 예시
- 동적으로 로딩된 객체가 모듈인지 확인할 때
- 사용자 입력으로 받은 객체가 특정 타입인지 검사
- types 모듈은 FunctionType, LambdaType, GeneratorType 등도 제공

```python
import types

def f(): pass
print(isinstance(f, types.FunctionType))  # True
```

---


### 📌 inspect 모듈을 활용한 객체 분석
- inspect는 Python 객체의 내부 구조를 분석할 수 있는 강력한 도구입니다.

### 📌 주요 기능 요약

| 함수                          | 설명                                                                 |
|-------------------------------|----------------------------------------------------------------------|
| `inspect.getmembers(obj)`     | 객체의 모든 속성과 값을 `(이름, 값)` 형태의 리스트로 반환             |
| `inspect.getmodule(obj)`      | 객체가 정의된 모듈을 반환                                             |
| `inspect.getsource(obj)`      | 함수나 클래스의 소스 코드를 문자열로 반환                             |
| `inspect.signature(func)`     | 함수의 인자 시그니처를 분석하여 반환                                  |
| `inspect.isfunction(obj)`     | `def`로 정의된 일반 함수인지 확인                                     |
| `inspect.isclass(obj)`        | 객체가 클래스인지 확인                                               |
| `inspect.ismodule(obj)`       | 객체가 모듈인지 확인                                                 |
| `inspect.isbuiltin(obj)`      | `len`, `print`처럼 내장 함수인지 확인                                 |


### 📌 예시
```python
import inspect
import math

print(inspect.ismodule(math))  # True
print(inspect.isfunction(math.sin))  # True
print(inspect.getmodule(math.sin))  # <module 'math' ...>
print(inspect.signature(len))  # TypeError: no signature found for built-in function
```

### 📌 사용자 정의 타입과의 비교
- 사용자 정의 클래스와 객체를 비교하거나 검사할 때는 다음을 활용합니다:
#### 🔹 예시: 클래스 정의 및 타입 비교
```python
class MyClass:
    def method(self):
        pass

obj = MyClass()

print(type(obj))  # <class '__main__.MyClass'>
print(isinstance(obj, MyClass))  # True
print(issubclass(MyClass, object))  # True
```

#### 🔹 inspect로 분석
```python
print(inspect.isclass(MyClass))  # True
print(inspect.getmembers(obj))  # 모든 속성과 값 출력
print(inspect.getsource(MyClass))  # 클래스 정의 소스 코드 출력
```

### 📌 실전 팁

| 항목                     | 설명                                                                 |
|--------------------------|----------------------------------------------------------------------|
| 내장 함수 분석 제한       | `inspect.getsource()`는 `len`, `print` 같은 내장 함수에 사용 시 `TypeError` 발생 |
| 사용자 정의 함수 우선     | `inspect.signature()`는 사용자 정의 함수에 더 잘 작동함               |
| 디버깅 및 리플렉션 활용    | `inspect`는 객체 구조 분석, 자동 문서화, 테스트 코드 생성 등에 유용함  |

---


