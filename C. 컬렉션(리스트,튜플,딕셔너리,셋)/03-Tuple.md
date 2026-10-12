## 📘 Tuple
- Python의 튜플(tuple) 자료형을 구조적으로 정리

### 📌 튜플 자료형 요약
#### 🔹 튜플의 특징
- 순서가 있음 (Ordered)
- 중복 가능 (Duplicates allowed)
- 수정 불가 (Immutable)
- 삭제 불가 (Immutable)
- 불변 객체 (Immutable Object)



#### 🔹 튜플 선언 및 타입 확인
```python
a = ()
b = (1, 2)
print(type(a), type(b))  # <class 'tuple'> <class 'tuple'>
```

- 빈 튜플: ()
- 단일 요소 튜플: (4,) ← `쉼표 필수`
    - 마지막 쉼표가 필수인 경우는 단일 요소 튜플뿐입니다.
    - (4)는 int로 인식됩니다.
- 여러 요소: (1, 2, 3)
  

#### 🔹 값 비교 vs 참조 비교
```python
d = (100, 100, '1', '2', '3')
e = (100, 100, '1', '2', '3')
```
print(d == e)      # True (값 비교)
print(id(d), id(e))# 동일 객체일 경우 같은 ID
- ==: 값 비교
- is: 참조 비교
- id(): 객체의 메모리 주소 확인
- 불변 객체라서 is 값이 True 일수도 False일 수도 있음. 값 비교에서 쓰면 안됨.

#### ❌ 수정 불가
```python
b = (1, 2)
b[0] = 1
# TypeError: 'tuple' object does not support item assignment
```

- 튜플은 불변 객체이므로 요소 변경 불가

### 📌 슬라이싱 & 연산
```python
b = (1, 2)
c = (11, 12, 13, 14)
d = (100, 100, '1', '2', '3')
print(b[:])        # (1, 2)
print(b * 2)       # (1, 2, 1, 2)
print(c + d)       # 튜플 연결
```
```
(11, 12, 13, 14, 100, 100, '1', '2', '3')
```

- 슬라이싱은 리스트처럼 가능
- +, * 연산도 지원

### 📌 튜플 메서드
```python
a = (5, 2, 3, 1, 4, 4)
print(a.index(3))  # 2
print(a.count(4))  # 2
```

- index(x): `x의 첫 번째 위치 반환`
- count(x): `x의 개수 반환`
```python
try:
    print(a.index(10))
except ValueError:
    print("Test")
finally:
    print("default value")
```

- 없는 값에 index() 사용 시 ValueError 발생

### 📌 Packing & Unpacking
```python
t = ('1', '2', '3', 4)
x1, x2, x3, x4 = t
print(x1, x2, x3, x4)  # 1 2 3 4
```

- 튜플의 각 요소를 변수에 한 번에 할당 가능
```python
t2 = 1, 2, 3       # 괄호 없이도 튜플 생성 가능
t3 = 4,            # 단일 요소 튜플은 쉼표 필수
```


### 📌  튜플 생성 방식 비교
```python
t = 1, 2, 3, 4
t1 = tuple((1, 2, 3, 4))
print(t is t1)     # True (같은 객체일 경우)
```


### 📌 내부 메서드 제한
```python
print(tuple.__setitem__)
# AttributeError: 'tuple' object has no attribute '__setitem__'
```

- 튜플은 `__setitem__` 이 없고, `__getitem__` 만 존재

### 📌 튜플 vs 리스트 비교 요약
| 항목           | `list` (리스트)           | `tuple` (튜플)           |
|----------------|---------------------------|---------------------------|
| 순서           | 있음                        | 있음                        |
| 중복           | 가능                        | 가능                        |
| 수정 가능 여부 | ✅ 가능                     | ❌ 불가능                   |
| 삭제 가능 여부 | ✅ 가능                     | ❌ 불가능                   |
| 불변성         | 변경 가능 (mutable)        | 변경 불가 (immutable)      |
| 메서드 지원    | 다양함 (`append`, `pop`, `sort` 등) | 제한적 (`count`, `index`) |

---







