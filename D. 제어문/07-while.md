## 📘 기본 구조
```
while <조건식>:
    <실행할 코드>
```

- 조건식이 True인 동안 반복
- 조건이 False가 되면 반복 종료

### 📌 기본 예제
```python
n = 5
while n > 0:
    print(n)
    n -= 1
```
```
# 출력: 5 4 3 2 1
```
### 📌 리스트 요소 제거 반복
#### 🔹 뒤에서 제거
```python
a = ['1', '2', '3', '4', '5']
while a:
    print(a.pop())     # 뒤에서 제거
```
```
# 출력: 5 4 3 2 1
```

#### 🔹 앞에서 제거
```python
a = ['1', '2', '3', '4', '5']
while a:
    print(a.pop(0))    # 앞에서 제거
```
```
# 출력: 1 2 3 4 5
```

### 📌 break, continue 제어문
#### 🔹 break: 반복 즉시 종료
```python
n = 5
while n > 0:
    n -= 1
    if n == 2:
        break
    print('n --', n)
```
```
# 출력: n -- 4, n -- 3
```

#### 🔹 continue: 현재 반복 건너뛰기
```python
n = 5
while n > 0:
    n -= 1
    if n == 2:
        continue
    print('n --', n)
```

```
# 출력: n -- 4, n -- 3, n -- 1, n -- 0
```

### 📌 while-else 문법
```python
n = 10
while n > 0:
    n -= 1
    print(n)
else:
    print('else out')
```
```
# 출력: 9 ~ 0, 그리고 'else out'
```
- while이 정상 종료되면 else 실행
- break로 종료되면 else는 실행되지 않음

#### 🔹 검색 실패 처리
```python
a = ['1', '2', '3', '4']
s = '5'
i = 0
while i < len(a):
    if a[i] == s:
        break
    i += 1
else:
    print(s, 'not found in list.')
```
```
# 출력: 5 not found in list.
```

#### 🔹 무한 반복
```python
while True:
    print('1')  # Ctrl+C로 중단
```
- 조건이 항상 True → 무한 루프
- break로 탈출 조건 설정 필요

#### 🔹 실전 예시
```python
a = ['1', '2', '3']
while True:
    if not a:
        break
    print(a.pop())
```
```
# 출력: 3 2 1
```

### 📌 요약 표
| 문법/키워드     | 설명                                 | 예시                          |
|------------------|--------------------------------------|-------------------------------|
| `while`          | 조건이 참일 때 반복                  | `while x > 0:`                |
| `break`          | 반복 즉시 종료                       | `if x == target: break`       |
| `continue`       | 현재 반복 건너뛰고 다음으로 진행     | `if 조건: continue`           |
| `while-else`     | 반복이 정상 종료되면 else 실행       | `while ... else:`             |
| `while True`     | 무한 반복                            | `while True:`                 |

---




