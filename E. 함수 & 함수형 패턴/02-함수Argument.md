## 📘 Function Argument
- Python 함수의 고급 기능 중에서도 실무에서 자주 등장하는 핵심.  
- 아래에 `*args`, `**kwargs`, 그리고 `중첩 함수(클로저 포함)` 에 대해 개념 + 예제 + 활용 포인트를 체계적으로 문서화

### 📌 *args: 가변 위치 인자
```python
def args_func(*args):
    for i, v in enumerate(args):
        print(f"Result : {i}", v)
```

- *args는 **여러 개의 위치 인자(positional arguments)** 를 하나의 튜플로 받아옴
- 함수 호출 시 인자의 개수가 정해져 있지 않을 때 사용
- args는 관례적인 이름일 뿐, 다른 이름도 가능

#### 🔹 예시
```python
args_func("jhjeong", "hyangseon", "1")
```
#### 🔹 출력:
```
Result : 0 jhjeong
Result : 1 hyangseon
Result : 2 1
```

### 📌 **kwargs: 가변 키워드 인자
```python
def kwargs_func(**kwargs):
    for key in kwargs:
        print(f"{key} {kwargs[key]}")
```

- `**kwargs`는 **여러 개의 키워드 인자(keyword arguments)** 를 하나의 딕셔너리로 받아옴
- 인자의 이름과 값을 함께 전달할 수 있음
- kwargs 역시 관례적인 이름

#### 🔹 예시
```python
kwargs_func(name1='1', name2='2', name3='3')
```

#### 🔹 출력:
```
name1 1
name2 2
name3 3
```


### 📌 *args + **kwargs 함께 사용
```python
def args_kwargs_func(*args, **kwargs):
    for i, v in enumerate(args):
        print(f"Result : {i}", v)
    for key in kwargs:
        print(f"{key} {kwargs[key]}")
```
- 위치 인자와 키워드 인자를 동시에 처리
- 순서 중요: *args → **kwargs

#### 🔹  예제
```python
def args_kwargs_func(*args, **kwargs):  # 매개변수 명 자유
    for i, v in enumerate(args):
        print("Result : {}".format(i), v)

    for v in kwargs.keys():
        print("{}".format(v), kwargs[v])
    print('-----')

args_kwargs_func("1", "2", "3", name1="1", name2='2', name3='3')
```
```
Result : 0 1
Result : 1 2
Result : 2 3
name1 1
name2 2
name3 3
-----
```

#### 🔹 혼합 인자 함수
```python
def arg_args_kwargs_func(arg_1, arg_2, *args, **kwargs):
    print("arg_1", arg_1)
    print("arg_2", arg_2)
    for i, v in enumerate(args):
        print(f"Result : {i}", v)
    for key in kwargs:
        print(f"{key} {kwargs[key]}")
```

#### 🔹  예제
```python
def arg_args_kwargs_func(arg_1, arg_2, *args, **kwargs):  # 매개변수 명 자유
    print("arg_1 {}".format(arg_1))
    print("arg_2 {}".format(arg_2))
    for i, v in enumerate(args):
        print("Result : {}".format(i), v)
    for v in kwargs.keys():
        print("{}".format(v), kwargs[v])
    print('-----')

arg_args_kwargs_func(10, 20, "1", "2", "3", name1="1", name2='2', name3='3')
```
```
arg_1 10
arg_2 20
Result : 0 1
Result : 1 2
Result : 2 3
name1 1
name2 2
name3 3
-----
```
- 고정 인자 + 가변 인자를 함께 사용
- 실무에서 API 설계, 유연한 함수 호출에 자주 활용됨

### 📌 중첩 함수 (Nested Function)
```python
def nested_func(num):
    def func_in_func(inner_num):  # 내부 함수
        print(inner_num)
    print("In func")
    func_in_func(num + 10)
```

#### 🔹 예제
```python
def nested_func(num):
    def func_in_fuc(num):  # Closure
        print(num)
    print('In func')
    func_in_fuc(num + 10)

nested_func(100)
```
```
In func 
110
```
- 함수 안에 또 다른 함수를 정의
- 내부 함수는 외부 함수의 지역 변수에 접근 가능
- 이 구조는 **클로저(Closure)** 의 기반이 됨

### 📌 클로저란?
- 내부 함수가 외부 함수의 변수 상태를 기억하고 사용할 수 있는 구조
- 상태 유지, 캡슐화, 데코레이터 구현 등에 활용됨

### 📌 요약 표
| 기능           | 설명                                   | 자료형         |
|----------------|----------------------------------------|----------------|
| `*args`        | 가변 위치 인자                         | 튜플           |
| `**kwargs`     | 가변 키워드 인자                       | 딕셔너리       |
| 중첩 함수      | 함수 내부에 또 다른 함수 정의           | 클로저 가능     |
| 혼합 인자      | 고정 인자 + 가변 인자 조합             | 실무에서 자주 사용 |


### 📌 활용 팁
- `*args` 는 리스트처럼 반복 가능하지만 수정 불가 (튜플)
- `**kwargs` 는 딕셔너리처럼 키-값 접근 가능
- `중첩 함수` 는 데코레이터, 상태 유지 함수, 캡슐화에 매우 유용

---



