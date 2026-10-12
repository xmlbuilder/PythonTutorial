## 📘 Dictionary 자료형 요약

### 📌 딕셔너리 특징
- 범용적으로 가장 많이 사용되는 자료형
- 순서가 없음 → `Python 3.7+부터 삽입 순서 유지`
- 키 중복 불가
- 수정 가능
- 삭제 가능
- 키는 불변(immutable) 타입만 가능


### 📌 딕셔너리 선언 방법
#### 🔹 중괄호 사용
```python
a = {
    'name': 'Jeong',
    'name': 'JungHwan',  # 중복 키 → 마지막 값으로 덮어씀
    'phone': '010-7339-9286',
    'birth': '690712'
}
```

#### 🔹 숫자 키
```python
b = {0: "Hello World"}
```
#### 🔹 리스트를 값으로
```python
c = {'array': [1, 2, 3, 4]}
```

#### 🔹 dict() 생성자 사용
```python
d = dict([('Name', 'jhjeong'), ('City', 'Seoul')])
f = dict(Name='jhjeong', City='Seoul', Age=33, Grade='A', Status=True)
```

### 📌 딕셔너리 출력 및 접근
#### 🔹 키가 존재하면 값 반환
```python
print(a['name'])
```
#### 🔹 출력 결과
```        
JungHwan
```
#### 🔹 안전한 접근 방식
```python
print(a.get('name'))
```
#### 🔹 출력 결과
```     
JungHwan
```
#### 🔹 존재하지 않으면 None 반환
```python
print(a.get('name1'))    
```
#### 🔹 출력 결과
```
None
```

- `[]` 접근: 키가 없으면 `KeyError`
- `.get()`: 키가 없으면 `None` 반환

### 📌 딕셔너리 타입 확인
```python
print(type(f))  # <class 'dict'>
```
### 📌 딕셔너리 특징 요약표
| 항목           | 설명                                | 예제 코드                  |
|----------------|-------------------------------------|----------------------------|
| 순서           | Python 3.7+부터 삽입 순서 유지       | —                          |
| 키 중복 불가   | 동일 키 사용 시 마지막 값으로 덮어씀 | —                          |
| 수정 가능      | 값 변경 가능                         | `dict[key] = new_value`   |
| 삭제 가능      | 키-값 쌍 제거 가능                   | `del dict[key]`           |
| 키 타입 제한   | 불변 타입만 사용 가능                | `str`, `int`, `tuple` 등  |
| 값 타입 자유   | 어떤 타입도 가능                     | `list`, `dict`, `bool` 등 |


#### 🔹 예제 출력
```python
print(b[0])         # Hello World
print(b.get(0))     # Hello World
print(c['array'])   # [1, 2, 3, 4]
```
---


### 📌 Dictionary 핵심 기능 요약
```python
a = {
    'name': 'Jeong',
    'phone': '010-7339-9286',
    'birth': '690712'
}
```

#### 🔹 기본 기능 코드
```python
### 키 추가
a['address'] = 'seoul'
```
#### 🔹 출력 결과
```
{'name': 'Jeong', 'phone': '010-7339-9286', 'birth': '690712', 'address': 'seoul'}
```

#### 🔹 값 수정
```python
a['name'] = 'jhjeong'
```
#### 🔹 출력 결과
```
{'name': 'jhjeong', 'phone': '010-7339-9286', 'birth': '690712', 'address': 'seoul'}
```
#### 🔹 len
```python
len(a)
```
#### 🔹 출력 결과
```
4
```


### 📌 기본 기능
| 기능 구분     | 설명               | 예제 코드                  | 결과     |
|---------------|--------------------|-----------------------------|----------|
| 키 추가       | 새로운 키 삽입      | `a['address'] = 'seoul'`    | —        |
| 값 수정       | 기존 키 값 변경     | `a['name'] = 'jhjeong'`     | —        |
| 길이 확인     | 전체 항목 개수 확인 | `len(a)`                    | `5`      |
| 키 존재 확인  | 특정 키 존재 여부   | `'birth' in a`              | `True`   |


### 📌 조회 관련 코드
#### 🔹 keys
```python
a.keys()
```
#### 🔹 출력 결과
```
dict_keys(['name', 'phone', 'birth', 'address'])
```
#### 🔹 values
```python
a.values()
```
#### 🔹 출력 결과
```
dict_values(['jhjeong', '010-7339-9286', '690712', 'seoul')
```
#### 🔹 items
```python
list(a.items())
```
#### 🔹 출력 결과
```
[('name', 'jhjeong'), ('phone', '010-7339-9286'), ('birth', '690712'), ('address', 'seoul')]
```

### 📌 조회 관련 메서드
| 메서드       | 설명             | 예제 코드           | 결과 예시                                 |
|--------------|------------------|----------------------|--------------------------------------------|
| `a.keys()`   | 모든 키 반환      | `list(a.keys())`     | `['name', 'phone', ...]`                   |
| `a.values()` | 모든 값 반환      | `list(a.values())`   | `['jhjeong', '010-...', ...]`              |
| `a.items()`  | 키-값 쌍 반환     | `list(a.items())`    | `[('name', 'jhjeong'), ('phone', '010-...')]` |


### 📌 삭제 관련 코드
```python
a.pop('name')
print(a)
```
#### 🔹 출력 결과
```
jhjeong
{'phone': '010-7339-9286', 'birth': '690712', 'address': 'seoul'}
```
### 📌 삭제 관련 메서드
| 메서드         | 설명                  | 예제 코드           | 결과 예시           |
|----------------|-----------------------|----------------------|----------------------|
| `pop(key)`     | 지정한 키 제거 및 값 반환 | `a.pop('name')`      | `'jhjeong'`          |
| `popitem()`    | 마지막 키-값 쌍 제거 및 반환 | `f.popitem()`        | `('Status', True)`   |
| `del dict[key]`| 지정한 키 삭제         | `del a['test']`      | —                    |

### 📌 수정 관련 코드
```python
a['address'] = 'kyeongki'
```
#### 🔹 출력 결과
```
{'phone': '010-7339-9286', 'birth': '690712', 'address': 'kyeongki'}
```

```python
temp2 = {'data': 'Sample'}
a.update(temp2)
```
#### 🔹 출력 결과
```
{'phone': '010-7339-9286', 'birth': '123456', 'address': 'kyeongki', 'data': 'Sample'}
```

### 📌 수정 관련 메서드
| 기능 구분     | 설명               | 예제 코드                        | 결과 예시 |
|---------------|--------------------|----------------------------------|------------|
| 직접 수정     | 기존 키의 값 변경 또는 새 키 추가 | `a['address'] = 'Busan'`         | 값 변경 또는 키 추가 |
| `update()`    | 여러 키-값 쌍을 한 번에 병합     | `a.update({'data': 'Sample'})`   | 병합됨     |


### 📌 추가 유용한 메서드
| 메서드         | 설명                         | 예제 코드                          | 결과 예시               |
|----------------|------------------------------|-------------------------------------|--------------------------|
| `get(key)`     | 키가 없을 경우 `None` 반환     | `a.get('model')`                   | `None`                   |
| `setdefault()` | 키가 없으면 기본값 설정 후 반환 | `a.setdefault('level', 1)`         | `'level': 1` 추가됨      |
| `clear()`      | 모든 항목 제거                 | `a.clear()`                         | `{}`                     |
| `copy()`       | 얕은 복사본 생성               | `a.copy()`                          | 원본과 동일한 새 딕셔너리 |
| `fromkeys()`   | 키 리스트로 새 딕셔너리 생성    | `dict.fromkeys(['a', 'b'], 0)`      | `{'a': 0, 'b': 0}`        |


### 📌 반복문 활용 예시
```python
for key in a:
    print(key, a[key])
```

또는
```python
for k, v in a.items():
    print(f"{k}: {v}")
```
---

