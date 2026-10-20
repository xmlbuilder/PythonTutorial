## 📘 해시 테이블이란?

- Key → Value 구조로 데이터를 저장
- dict는 Python의 대표적인 해시 테이블 구현체
- 내부적으로는 key를 해싱 함수로 처리 → 해시 주소 → value 참조
- 불변 객체만 key로 사용 가능 (int, str, tuple 등)

### 📌 해시 가능 여부
```python
t1 = (10, 20, 30, 40, 50)
print(hash(t1))  # ✅ 해시 가능

t2 = (10, 20, [30, 40, 50])
print(hash(t2))  # ❌ TypeError: list는 가변 객체
```

- tuple은 불변이지만 내부에 list가 있으면 해시 불가
- 해시 가능한 객체만 dict의 key로 사용 가능

### 📌 dict + setdefault() 활용
#### 🔹 일반 방식
```python
new_dict1 = {}
for k, v in source:
    if k in new_dict1:
        new_dict1[k].append(v)
    else:
        new_dict1[k] = [v]
```

#### 🔹 setdefault() 방식
```python
new_dict2 = {}
for k, v in source:
    new_dict2.setdefault(k, []).append(v)

```
- setdefault(key, default)는 key가 없으면 default를 넣고 반환
- 이후 .append(v)로 리스트에 값 추가

### 📌 주의: dict comprehension
```python
new_dict3 = {k: v for k, v in source}
```

- 같은 key가 여러 번 등장하면 마지막 값으로 덮어씀
- 리스트로 누적하려면 setdefault() 또는 조건문 방식 사용

### 📌 요약 테이블
| 항목             | 설명                                      | 예시/결과                          |
|------------------|-------------------------------------------|------------------------------------|
| 해시 테이블       | key → value 구조, 빠른 접근                | `dict`                             |
| 해시 가능 객체     | 불변 객체만 가능                           | `int`, `str`, `tuple`              |
| setdefault()     | key 없으면 기본값 설정 후 반환             | `dict.setdefault(k, []).append(v)` |
| dict comprehension | key 중복 시 마지막 값으로 덮어씀          | `{'k1': 'val4', ...}`              |

### 📌 예제 소스
#### 🔹 dict 가 해쉬 데이블 일종
```python
print(__builtins__.__dict__)
```

#### 🔹 Hash 값 확인 (불변 객체만 가능)
```python
t1 = (10, 20, 30, 40, 50)
t2 = (10, 20, [30, 40, 50])
print(hash(t1))
```
```
8567762680143973733
```
```python
#print(hash(t2))
```
#### 🔹 출력 결과
```
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 18, in <module>
    print(hash(t2))
          ^^^^^^^^
TypeError: unhashable type: 'list'
```

#### 🔹 Dict setdefault
```python
source = (('k1', 'val1'), ('k2', 'val2'), ('k3', 'val3'), ('k1', 'val4'),)
new_dict1 = {}
new_dict2 = {}

for k, v in source:
    if k in new_dict1:
        new_dict1[k].append(v)
    else:
        new_dict1[k] = [v]

print(new_dict1)
```
#### 🔹출력 결과
```
{'k1': ['val1', 'val4'], 'k2': ['val2'], 'k3': ['val3']}
```
```python
for k, v in source:
    new_dict2.setdefault(k, []).append(v)
print(new_dict2)
```
#### 🔹출력 결과
```
{'k1': ['val1', 'val4'], 'k2': ['val2'], 'k3': ['val3']}
```

#### 🔹 주의 (덮어 써 버린다, 배열로 관리 하지 못한다)
```python
new_dict3 = {k: v for k, v in source}
print(new_dict3)
```

#### 🔹출력 결과

```
{'k1': 'val4', 'k2': 'val2', 'k3': 'val3'}
```
---

### 📌 `__builtins__.__dict__`

- Python 내부에서 기본 제공되는 내장 함수, 예외, 객체들을 담고 있는 딕셔너리 형태의 네임스페이스입니다.  
- 쉽게 말해, Python이 실행될 때 자동으로 사용할 수 있게 해주는 기본 도구 상자라고 생각하시면 됨.

### 📌 `__builtins__` 란?
- Python 인터프리터가 시작될 때 자동으로 로딩되는 내장 모듈
- print, len, range, int, str, Exception 등 기본 함수와 객체들이 포함됨
- `__builtins__.__dict__` 는 이들을 딕셔너리 형태로 보여줌


### 📌 `__builtins__.__dict__` 사용 목적

| 목적 구분           | 설명                                                  |
|---------------------|-------------------------------------------------------|
| 내장 함수 확인       | Python이 기본으로 제공하는 함수, 예외, 객체 목록 확인 가능 |
| 동적 실행 제어       | `eval()` / `exec()` 사용 시 허용할 함수 제한 가능         |
| 샌드박스 환경 구성   | 보안 목적의 제한된 실행 환경에서 필요한 기능만 노출       |
| 디버깅 및 학습용     | 내부 동작 구조를 이해하거나 실험할 때 유용               |
| 사용자 환경 커스터마이징 | 특정 내장 기능을 오버라이드하거나 제거할 때 활용          |


### 📌  예시
```python
print(__builtins__.__dict__.keys())
```
#### 🔹 출력 결과

```
dict_keys([... 'abs', 'all', 'any', 'ascii', 'bin', 'bool', ...])
```
```python
print(__builtins__.__dict__['max']([1, 2, 3]))
```
#### 🔹출력 결과

```
3
```

### 📌 예시: eval()에서 내장 함수 제한
```python
safe_globals = {"__builtins__": {"abs": abs}}
print(eval("abs(-5)", safe_globals))  # ✅ 5
print(eval("max([1, 2, 3])", safe_globals))  # ❌ NameError
```

- `__builtins__`를 제한하면 eval()에서 사용할 수 있는 함수도 제한됩니다.

#### 🔹 1. eval()의 기본 구조
```python
eval(expression, globals=None, locals=None)
```

| 인자	| 역할 | 
|-------|------|
| expression	| 실행할 Python 표현식 |
| globals	| 표현식에서 참조할 전역 이름 공간 |
| locals	| 표현식에서 참조할 지역 이름 공간 |



#### 📌 주의사항
- 일반적인 코드에서는 직접 사용할 일이 거의 없음
- `__builtins__` 는 구현 환경에 따라 module 또는 dict로 보일 수 있음
- 보안이 중요한 환경에서는 eval() 사용 시 `__builtins__` 를 제거하거나 제한하는 방식으로 활용됨

---


---

