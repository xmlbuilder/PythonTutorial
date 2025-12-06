# Switch
Python에는 전통적인 switch-case 문이 없지만, 딕셔너리 기반의 함수 매핑을 활용하면 유사한 기능을 구현할 수 있음. 

## 🔁 Python에서의 Switch 구문 구현
### ✅ 기본 개념
- Python은 switch-case 문을 지원하지 않음
- 대신 dict를 활용해 조건에 따라 함수 또는 값 매핑 가능
- dict.get(key, default)를 사용하면 기본값 처리도 가능

### 🧪 예제 코드
```python
def func10():
    print(10)

def func100():
    print(100)

switch = {
    '10': func10,
    '100': func100
}

switch.get('100', lambda: print('None'))()  # 출력: 100
switch.get('1', lambda: print('None'))()    # 출력: None
```

- '100' 키가 존재하므로 func100() 실행
- '1' 키는 없으므로 lambda: print('None') 실행

### 🧩 구조 설명

| 구성 요소            | 설명                                                   |
|----------------------|--------------------------------------------------------|
| `dict`               | 조건(key)과 실행할 함수(value)를 매핑하는 자료구조       |
| `get(key, default)`  | key가 존재하면 해당 함수 반환, 없으면 기본 함수 반환     |
| `()`                 | 반환된 함수를 즉시 실행하는 호출 연산자                  |

#### 📘 예시 흐름
```python
switch = {
    '10': func10,
    '100': func100
}

switch.get('100', lambda: print('None'))()  # → func100 실행
switch.get('1', lambda: print('None'))()    # → 기본 함수 실행
```
```
get()으로 함수 객체를 받아오고, ()로 실행하는 구조입니다.
```

### 📘 실무 활용
```python
def handle_login(): print("로그인 처리")
def handle_logout(): print("로그아웃 처리")

action = "logout"
actions = {
    "login": handle_login,
    "logout": handle_logout
}
actions.get(action, lambda: print("알 수 없는 요청"))()

```

조건 분기 없이 깔끔하게 함수 실행 가능


### ⚠️ 주의사항

| 항목           | 설명                                                                 |
|----------------|----------------------------------------------------------------------|
| `'10' vs 10`   | 딕셔너리 키는 타입까지 구분하므로 `'10'`(문자열)과 `10`(정수)는 다름     |
| `()`           | `dict.get()`으로 반환된 함수는 `()`를 붙여야 실행됨 (`func()` 형태)       |
| `if-elif`      | 복잡한 조건이나 범위 비교에는 `if-elif` 문이 더 명확하고 가독성 좋음      |


#### 📘 예시
```python
switch = {'10': func10, 10: func100}
switch.get(10)()       # func100 실행
switch.get('10')()     # func10 실행
```

- 키 타입이 다르면 서로 다른 함수가 실행됩니다.

---




