## 📘 집합(Set) 자료형 요약

### 📌 집합의 특징
- 순서가 없다 (Unordered)
- 중복을 허용하지 않는다 (Unique)
- 수정 및 삭제 가능
- 인덱싱 불가


### 📌 집합 선언 방법
```python
a = set()                      # 빈 집합
b = set([1, 2, 3, 4])          # 리스트 → 집합
c = {1, 2, 'Pen', 'Cap'}       # 중괄호 직접 사용
f = {42, 'foo', (1, 2, 3)}     # 다양한 불변 타입 가능
```

- set()으로 빈 집합 생성 (빈 {}는 딕셔너리!)
- 중복 요소는 자동 제거됨

### 📌 집합 변환
```python
tuple_b = tuple(b)             # 집합 → 튜플
list_c = list(c)               # 집합 → 리스트
```
- 집합은 인덱싱 불가 → 변환 후 인덱싱 가능

### 📌 선언

```python
a = set()
print(a, type(a))
```
- `a = {}`는 dict가 생성됨.
  
#### 🔹 출력 결과
```
set() <class 'set'>
```

```python
b = set([1, 2, 3, 4])
c = set([1, 4, 5, 6])
d = {1, 2, 'Pen', 'Cap', 'Plate'}
print(d, type(d))
```
#### 🔹 출력 결과
```
{'Cap', 2, 1, 'Pen', 'Plate'} <class 'set'>
```

```python
f = {42, 'foo', (1, 2, 3), 3.141592}
print(f, type(f))
```
#### 🔹 출력 결과
```
{'foo', 42, (1, 2, 3), 3.141592} <class 'set'>
```

```python
g = set([1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 7])
print(g, type(g))
```
#### 🔹 출력 결과
```
{1, 2, 3, 4, 5, 6, 7} <class 'set'>
```

```python
print('b -- ', b[0])
```
#### 🔹 출력 결과
```
Traceback (most recent call last):
...
TypeError: 'set' object is not subscriptable

```

#### 🔹 집합 연산 코드 
```python
s1 = {1, 2, 3, 4, 5, 6}
s2 = {4, 5, 6, 7, 8, 9}
print('s1 & s2', s1 & s2)
```
#### 🔹 출력 결과
```
s1 & s2 {4, 5, 6}
```

#### 🔹 intersection

```python
print('s1 & s2', s1.intersection(s2))
```
#### 🔹 출력 결과
```
s1 & s2 {4, 5, 6}
```
#### 🔹 union

```python
print('s1 | s2 : ', s1 | s2)
print('s1 | s2 : ', s1.union(s2))
```
#### 🔹 출력 결과
```
s1 | s2 :  {1, 2, 3, 4, 5, 6, 7, 8, 9}
s1 | s2 :  {1, 2, 3, 4, 5, 6, 7, 8, 9}
```
#### 🔹 difference
```python
print('s1 - s2 : ', s1 - s2)
print('s1 - s2 :', s1.difference(s2))
```
#### 🔹 출력 결과
```
s1 - s2 :  {1, 2, 3}
s1 - s2 : {1, 2, 3}
```

### 📌 집합 연산
| 연산 종류       | 예제 코드                                 | 결과 예시               |
|----------------|--------------------------------------------|--------------------------|
| 교집합          | `s1 & s2` / `s1.intersection(s2)`          | `{4, 5, 6}`              |
| 합집합          | `s1 | s2` / `s1.union(s2)`                 | `{1, 2, ..., 9}`         |
| 차집합          | `s1 - s2` / `s1.difference(s2)`            | `{1, 2, 3}`              |
| 대칭 차집합     | `s1 ^ s2` / `s1.symmetric_difference(s2)`  | `{1, 2, 3, 7, 8, 9}`     |


### 📌 집합 비교 및 포함 코드
#### 🔹 중복 원소 확인
```python
print('s1 & s2 : ' , s1.isdisjoint(s2))
```
#### 🔹 출력 결과
```
s1 & s2 :  False
```

#### 🔹 부분 집합 확인
```python
print('subset : ', s1.issubset(s2))
```
#### 🔹 출력 결과
```
subset :  False
```
#### 🔹 전체 집합 확인
```python
print('superset : ', s1.issuperset(s2))
```
#### 🔹 출력 결과
```
superset :  False
```

#### 🔹 집합 비교 및 포함 관계
```python
s1.isdisjoint(s2)   # 공통 요소 없음 여부
s1.issubset(s2)     # 부분 집합 여부
s1.issuperset(s2)   # 전체 집합 여부
```

### 📌 집합 요소 추가 및 제거 소스
#### 🔹 추가 & 제거
#### 🔹 add
```python
s1 = {1, 2, 3, 4}
s1.add(5)
print('s1 -- ', s1)
```
#### 🔹 출력 결과
```
s1 --  {1, 2, 3, 4, 5}
```
#### 🔹 remove
```python
s1.remove(2)
print('s1 -- ', s1)
```
#### 🔹 출력 결과
```
s1 --  {1, 3, 4, 5}
```
#### 🔹 remove
```python
s1.remove(8)
```
#### 🔹 출력 결과
```
Traceback (most recent call last):
...
KeyError: 8
```
#### 🔹 clear
```python
s1.clear()
print('s1 -- ', s1)
```
#### 🔹 출력 결과
```
s1 --  set()
```


### 📌 집합 요소 추가 및 제거
| 메서드       | 예외 발생 여부     | 예제 코드         | 결과 예시           |
|--------------|--------------------|--------------------|----------------------|
| `add(x)`     | ❌ 없음             | `s1.add(5)`         | `{1, 2, 3, 4, 5}`     |
| `remove(x)`  | ✅ `KeyError` 발생  | `s1.remove(2)`      | `{1, 3, 4, 5}`        |
| `discard(x)` | ❌ 없음             | `s1.discard(8)`     | `{1, 3, 4, 5}`        |
| `clear()`    | ❌ 없음             | `s1.clear()`        | `set()`              |


### 📌 집합의 특징 요약표
| 항목           | 설명                                |
|----------------|-------------------------------------|
| 순서           | 없음 (Unordered)                    |
| 중복           | 허용하지 않음 (Unique)              |
| 인덱싱         | 불가능                              |
| 수정 가능 여부 | ✅ 가능 (`add`, `remove`, `discard`) |
| 삭제 가능 여부 | ✅ 가능 (`clear`, `remove`, `discard`) |
| 요소 타입 제한 | 불변 타입만 가능 (int, str, tuple 등) |

---







