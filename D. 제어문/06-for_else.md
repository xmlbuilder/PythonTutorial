## 📘 for (for, else), reversed, range

### 📌 for-else 문법 설명
```
for 요소 in 반복가능한객체:
    if 조건:
        break
else:
    실행할 코드
```

- for 루프가 `정상적으로 끝났을 때만` `else 블록` 이 실행됨
- break로 루프가 중단되면 else는 실행되지 않음
- 주로 `검색 실패 처리` 에 유용

#### 🔹 예시
```python
numbers = [14, 3, 4, 7, 10, 25, 17, 2, 33, 15, 34, 36, 38]
for num in numbers:
    if num == 24:
        print("Founded : 24")
        break
else:
    print("Not Found : 24")
```
```
# 출력: Not Found : 24
```

#### 🔹 구구단 출력 (중첩 for)
```python
for i in range(2, 10):
    for j in range(1, 10):
        print(f"{i} * {j} = {i*j:4d}", end='    ')
    print()
```

- range(2, 10) → 2단부터 9단까지
- range(1, 10) → 각 단의 곱셈
- {:4d} → 정렬된 숫자 출력

#### 🔹 reversed() 함수 활용
```python
names2 = 'Aceman'
print(reversed(names2))                  # reversed 객체
print(list(reversed(names2)))           # ['n', 'a', 'm', 'e', 'c', 'A']
print(tuple(reversed(names2)))          # ('n', 'a', 'm', 'e', 'c', 'A')
print(set(reversed(names2)))            # {'e', 'a', 'A', 'c', 'n', 'm'}
```
- reversed()는 역순 반복 객체를 반환
- list(), tuple(), set()으로 변환 가능
- set()은 중복 제거 + 순서 없음

### 📌 핵심 요약표
| 문법/함수        | 설명                                       | 특징                         |
|------------------|--------------------------------------------|------------------------------|
| `for-else`       | 루프가 break 없이 끝나면 else 실행          | 검색 실패 처리에 유용        |
| 중첩 `for`       | 반복문 안에 반복문                         | 다차원 반복 처리 가능         |
| `reversed()`     | 역순 반복 객체 반환                        | `list`, `tuple`, `set` 변환 가능 |
| `range()`        | 숫자 반복 생성                            | 시작, 끝, 간격 지정 가능      |

---




