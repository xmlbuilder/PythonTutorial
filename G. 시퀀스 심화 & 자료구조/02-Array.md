## 📘 array 모듈이란?
- array.array(typecode, iterable) 형태로 사용
- C 스타일 배열을 Python에서 사용할 수 있게 해주는 모듈
- 동일한 자료형만 저장 가능 (list와 달리 혼합 불가)
- 메모리 효율성이 뛰어나며, 숫자 데이터 처리에 적합

### 📌 주요 특징 비교

| 항목             | list                            | array.array                         |
|------------------|----------------------------------|-------------------------------------|
| 자료형 제한       | 없음 (혼합 가능)                 | 있음 (단일 타입만 저장)             |
| 메모리 효율       | 일반적                           | 더 효율적 (특히 숫자 처리에 유리)    |
| 타입코드 필요     | 없음                             | 필요 (`'i'`, `'f'`, `'d'` 등)        |
| 변환 기능         | 기본 제공 없음                   | `.tolist()` → 일반 리스트로 변환 가능 |


### 📌 array.array 타입코드 예시

| 타입코드 | 데이터 타입         | 설명                         | 크기 (바이트) |
|----------|----------------------|------------------------------|----------------|
| `'i'`    | signed int           | 일반 정수형 (음수 포함)       | 4              |
| `'f'`    | float                | 단정도 부동소수점             | 4              |
| `'d'`    | double               | 배정도 부동소수점             | 8              |
| `'b'`    | signed char          | 1바이트 정수 (-128 ~ 127)     | 1              |


### 📌 사용법
```python
import array

arr_i = array.array('i', [1, 2, 3])
arr_f = array.array('f', [1.0, 2.0, 3.0])
arr_d = array.array('d', [1.0, 2.0, 3.0])
arr_b = array.array('b', [10, -5, 127])

print(arr_i)   # array('i', [1, 2, 3])
print(arr_f)   # array('f', [1.0, 2.0, 3.0])
print(arr_d)   # array('d', [1.0, 2.0, 3.0])
print(arr_b)   # array('b', [10, -5, 127])
```

### 📌 Generator vs List vs Array
#### 🔹 Generator
```python
gen = (ord(s) for s in chars)
print(next(gen))  # 43
```
- 한 번에 하나씩 생성
- 메모리 유지 안 함
- 반복자(iterator)로 동작


#### 🔹 List Comprehension
```python
list1 = [ord(s) for s in chars]
```
- 전체 데이터를 한 번에 메모리에 로드
- 다양한 자료형 가능

#### 🔹 Array
```python
array1 = array.array('i', (ord(s) for s in chars))
```

- 동일 타입만 저장
- 메모리 효율적
- .tolist()으로 일반 리스트로 변환 가능

#### 🔹 실전 예시
```python
from array import array

chars = '+_)(*&^%$#@i)'
arr = array('i', (ord(c) for c in chars))

print(arr)             # array('i', [...])
print(arr.tolist())    # [43, 95, 41, ...]

```

### 📌 요약
| 구조       | 특징                                  | 장점                         |
|------------|---------------------------------------|------------------------------|
| Generator  | 지연 평가, 메모리 효율                | 대용량 처리에 적합            |
| List       | 다양한 타입, 직관적                   | 범용성 높음                   |
| Array      | 단일 타입, 메모리 효율                | 숫자 처리에 최적화            |


### 📌 전체 코드

#### 🔹 1. List

```python
import array

chars = '+_)(*&^%$#@i)'
list1 = [ord(s) for s in chars]
print(list1)
```
#### 🔹출력 내용
```
[43, 95, 41, 40, 42, 38, 94, 37, 36, 35, 64, 105, 41]
```

#### 🔹 2. Tuple
```python
tuple1 = (ord(s) for s in chars)
print(tuple1)
#### 🔹출력 내용
'''<generator object <genexpr> at 0x100b3a0c0>'''

print(next(tuple1))
print(next(tuple1))
print(next(tuple1))
```
#### 🔹출력 내용
```
43
95
41
```

#### 🔹 3. Array
```python
array1 = array.array('i', (ord(s) for s in chars))
print(array1)
```
#### 🔹출력 내용
```
array('i', [43, 95, 41, 40, 42, 38, 94, 37, 36, 35, 64, 105, 41])
```
```python
print(type(array1))
```
#### 🔹출력 내용
```
<class 'array.array'>
```
```python
print(array1.tolist())
```
#### 🔹출력 내용
```
[43, 95, 41, 40, 42, 38, 94, 37, 36, 35, 64, 105, 41]
```
```python
print(('%s' % c + str(n) for c in ['A', 'B', 'C', 'D'] for n in range(1, 21) ))
```
#### 🔹출력 내용
```
<generator object <genexpr> at 0x103220e50>
```

```python
for s in ('%s' % c + str(n) for c in ['A', 'B', 'C'] for n in range(1, 4) ):
    print(s)
```
#### 🔹출력 내용
```
A1
A2
A3
B1
B2
B3
C1
C2
C3
```
---


