## 📘 for break / continue

### 📌 기본 구조: for in <iterable>
```
for 변수 in 반복가능한객체:
    실행할 코드
```

- 반복가능한객체: 문자열, 리스트, 튜플, 집합, 딕셔너리 등
- 반복 함수: range(), reversed(), enumerate(), filter(), map(), zip()

### 📌 다양한 반복 예시
#### 🔹 리스트 반복
```python
names = ['1', '2', '3', '4', '5']
for name in names:
    print("You are :", name)
```

#### 🔹 문자열 반복
```python
word = "Jhjeong"
for s in word:
    print("word :", s)
```

#### 🔹 딕셔너리 반복
```python
my_info = {"name": "jhjeong", "age": 55, "city": "Seoul"}
for key in my_info:
    print("key:", key, "value:", my_info[key])
```


### 📌 break 문: 반복 중단
```python
numbers = [14, 3, 4, 7, 10, 25, 17, 2, 33, 15, 34, 36, 38]
for n in numbers:
    if n == 34:
        print("Found : 34!")
        break
```
- break는 조건이 만족되면 반복을 즉시 종료
- 검색, 조건 만족 시 빠른 탈출에 유용

### 📌 continue 문: 현재 반복 건너뛰기
```python
lt = ["1", 2, 5, True, 4.3, complex(4, 3)]
for v in lt:
    if type(v) is not bool:
        continue
    print("current type:", v, type(v))

```
- continue는 조건이 만족되면 현재 반복을 건너뛰고 다음으로 이동
- 필터링, 조건 제외 등에 유용

#### 🔹 대문자 변환 예시
```python
name = 'FineAppLE'
for n in name:
    if n.isupper():
        print(n, end='')
    else:
        print(n.upper(), end='')
```
```
# 출력: FINEAPPLE
```

- 조건에 따라 출력 형식을 다르게 처리

### 📌 요약 표: for, break, continue
| 키워드      | 설명                          | 사용 예시                        |
|-------------|-------------------------------|----------------------------------|
| `for`       | 반복 가능한 객체 순회         | `for x in list:`                 |
| `break`     | 반복 중단                     | `if x == target: break`         |
| `continue`  | 현재 반복 건너뛰기            | `if 조건: continue`             |
| `in`        | 멤버십 테스트                 | `'a' in 'apple'` → `True`       |
| `get()`     | 딕셔너리 값 안전하게 접근     | `dict.get(key)`                 |

---
