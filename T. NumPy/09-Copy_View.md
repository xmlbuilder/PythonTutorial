
## 📘 NumPy Copy vs View — 핵심 개념 정리


### 📌 핵심 차이
| 개념   | 메모리 공유 | 원본 영향 | 독립성 | 용도           |
|--------|--------------|------------|--------|----------------|
| View   | 공유함       | 영향 있음 | X      | 슬라이싱, 얕은 복사 |
| Copy   | 공유 안 함   | 영향 없음 | O      | 완전한 복사        |


### 📌 예제 분석

#### 1️⃣ 기본 할당 (참조 공유)
```python
a = np.arange(12)
b = a
print(b is a)  → True

b.shape = (3, 4)
print(a.shape) → (3, 4)  # b와 a는 같은 객체
```

### 2️⃣ 함수 인자로 전달 (주소 동일)
```
def f(x):
    print(id(x))

print(id(a))  → 4390739120
f(a)          → 4390739120  # 동일한 객체 전달

```

### 3️⃣ View 생성 (얕은 복사)
```python
c = a.view()
print(c is a)         → False
print(c.base is a)    → True
print(c.flags.owndata)→ False
```
```
c.shape = (2, 6)       # c의 shape 변경 → a는 영향 없음
c[0, 4] = 1234         # 데이터 변경 → a에도 반영됨
```

### 4️⃣ 슬라이싱도 View
```python
s = a[:, 1:3]  # a -> [[0 1 2 3], [4  5 6 7], [8, 9, 10, 11]]
print(s) → [[1 2], [5 6], [9 10]]

s[:] = 10              # 슬라이스 변경 → a에도 반영됨
```

### 5️⃣ Copy 생성 (깊은 복사)
```python
d = a.copy()
print(d is a)         → False
print(d.base is a)    → False

d[0, 0] = 9999         # d만 변경 → a는 영향 없음
```

### 6️⃣ 대용량 배열 복사
```python
a = np.arange(int(1e8))  # 1억 개 요소
print(a.size) → 100000000

b = a[0:100].copy()      # 일부만 깊은 복사
print(b.size) → 100
```

## 💡 보강 포인트 — Copy vs View 속성 요약
| 속성 또는 함수       | 설명                                                   | 예시 결과 또는 특징             |
|----------------------|--------------------------------------------------------|----------------------------------|
| .view()              | 원본 데이터를 공유하는 새로운 배열 객체 생성           | shape 변경 가능, 데이터 공유     |
| .copy()              | 원본과 독립적인 배열 생성 (깊은 복사)                  | shape/데이터 변경해도 원본 영향 없음 |
| .base                | 원본 배열을 참조하는 객체인지 확인                      | view일 경우 → .base is 원본 배열 |
| .flags.owndata       | 배열이 데이터를 직접 소유하는지 여부                    | view → False, copy → True        |


## 🔧 예시 코드 요약
```python
a = np.arange(12)
b = a.view()
c = a.copy()

print(b.base is a)          # True → view는 원본 참조
print(c.base is a)          # False → copy는 독립적

print(b.flags.owndata)      # False → view는 데이터 소유 X
print(c.flags.owndata)      # True → copy는 데이터 소유 O
```

## 🧠 핵심 차이 요약 — Copy vs View
| 항목           | View                          | Copy                          | 설명 요약                                   |
|----------------|-------------------------------|-------------------------------|---------------------------------------------|
| 메모리 공유    | O                             | X                             | View는 원본과 메모리 공유                   |
| 원본 영향      | O                             | X                             | View 변경 시 원본도 변경됨                  |
| 독립성         | X                             | O                             | Copy는 완전히 독립된 배열                   |
| 속도/메모리    | 빠름, 메모리 절약             | 느림, 메모리 더 사용          | View는 가볍고 빠름, Copy는 안전하지만 무거움 |
| 용도           | 슬라이싱, 얕은 복사           | 안전한 복사, 데이터 보호      | 상황에 따라 선택 필요                       |


## 💬 한마디
- .view()는 빠르고 가볍지만 원본에 영향을 주고  
- .copy()는 안전하지만 메모리 비용이 있음.  
- 특히 대용량 배열을 다룰 때는 이 차이를 정확히 이해해야 성능과 안정성을 모두 챙길 수 있음.  


## 원본 소스

### Case 1.
```python
import numpy as np

a = np.arange(12)
b = a
print(b is a)
```
```
True
```
```python
b.shape = 3, 4
print(a.shape)
```
```
(3, 4)
```
```python
print(a)
```
```
[[ 0  1  2  3]
 [ 4  5  6  7]
 [ 8  9 10 11]]
```

### Case 2.
```python
def f(x):
    print(id(x))
print(id(a))
```
```
4390739120
```
```python
f(a)
```
```
4390739120
```

### Case 3.
```python
c = a.view()
print( c is a)
```
```
False
```
```python
print( c.base is a)
```
```
True
```
```python
print(c.flags.owndata)
```
```
False
```
```python
c.shape = 2, 6
print(c.shape)
```
```
(2, 6)
```
```python
print(a.shape)
```
```
(3, 4)
```
```python
c[0, 4] = 1234
print(c)
```
```
[[   0    1    2    3 1234    5]
 [   6    7    8    9   10   11]]
``` 
```python
print(a)
```
```
[[   0    1    2    3]
 [1234    5    6    7]
 [   8    9   10   11]]
```
```python
s = a[:, 1:3]
print(s)
```
```
[[ 1  2]
 [ 5  6]
 [ 9 10]]
```
```python
s[:] = 10
print(a)
```
```
[[   0   10   10    3]
 [1234   10   10    7]
 [   8   10   10   11]]
```

### Case 4.
```python
d = a.copy()
print(d is a)
```
```
False
```
```python
print(d.base is a)
```
```
False
```
```python
d[0, 0] = 9999
print(d)
```
```
[[9999   10   10    3]
 [1234   10   10    7]
 [   8   10   10   11]]
```
```python
print(a)
```
```
[[   0   10   10    3]
 [1234   10   10    7]
 [   8   10   10   11]]
```
### Case 5.
```python
a = np.arange(int(1e8))
print(a.size)
```
```
100000000
```
```python
b = a[0:100].copy()
print(b.size)
```
```
100
```
---



```
