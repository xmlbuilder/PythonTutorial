# set / frozenset을
Python의 set과 frozenset을 아주 잘 보여주는 실전 예제.
아래에 전체 내용을 개념 + 코드 + 설명으로 정리.

## 🧮 Python의 집합 자료형: set과 frozenset
### ✅ 기본 개념

| 자료형     | 특징                     |
|------------|--------------------------|
| `set`      | 변경 가능, 중복 제거     |
| `frozenset`| `set` 기반, 변경 불가능  |


### 🔹 set 생성과 중복 제거
```python
s1 = {'Apple', 'Orange', 'Mango', 'Pineapple', 'Kiwi', 'Apple'}
print(s1)
# 출력: {'Orange', 'Pineapple', 'Kiwi', 'Mango', 'Apple'}
```
- 중복된 'Apple'은 자동 제거됨
- 순서는 보장되지 않음 (해시 기반)

```python
s2 = set(['Apple', 'Orange', 'Mango', 'Pineapple', 'Kiwi', 'Apple'])
print(s2)
# 출력: {'Pineapple', 'Kiwi', 'Mango', 'Orange', 'Apple'}
```

- 리스트를 set()으로 변환해도 동일하게 중복 제거

### 🔹 단일 요소 집합과 빈 집합
```python
s3 = {3}          # 하나의 요소를 가진 집합
s4 = set()        # 빈 집합
print(type(s4))   # <class 'set'>
```

- {}는 빈 딕셔너리로 인식되므로 빈 집합은 set()으로 생성해야 함

### 🔹 frozenset: 불변 집합
```python
s5 = frozenset(s1)
print(type(s5))   # <class 'frozenset'>
```

- frozenset은 요소 추가/삭제 불가
- 아래 코드는 오류 발생:
```python
# s5.add('Melon')  # AttributeError
```

### 🔹 set은 변경 가능
```python
s1.add("Melon")
print(s1, type(s1))
# 출력: {'Kiwi', 'Melon', 'Mango', 'Pineapple', 'Orange', 'Apple'} <class 'set'>
```

---


### 🔍 선언 최적화: 바이트코드 비교
```python
from dis import dis

print(dis('{10}'))
```

# 더 간단한 바이트코드 (BUILD_SET)
```python
print(dis('set([10])'))
```

## 🔍 바이트코드 비교: 집합 선언 방식

| 표현식        | 바이트코드 요약                  | 연산 단계 수 | 성능 |
|---------------|----------------------------------|--------------|-------|
| `{10}`        | `LOAD_CONST → BUILD_SET → RETURN`| 3단계        | ✅ 빠름 |
| `set([10])`   | `PUSH_NULL → LOAD_NAME → BUILD_LIST → CALL → RETURN` | 5단계 이상 | ❌ 느림 |


## 🧠 지능형 집합 (Set Comprehension)
```python
from unicodedata import name

print({ name(chr(i), '') for i in range(0, 256) })
```

- name(chr(i), '')는 유니코드 문자 이름을 반환
- 집합으로 중복 없이 정리됨

## 📌 요약
| 특징             | `set`                     | `frozenset`               |
|------------------|---------------------------|----------------------------|
| 중복 제거        | ✅                         | ✅                          |
| 순서 없음        | ✅                         | ✅                          |
| 변경 가능        | ✅ (`add`, `remove` 가능) | ❌ (불변, 수정 불가)         |
| 해시 가능        | ❌                         | ✅ (딕셔너리 키로 사용 가능) |
| 선언 방식        | `{}` 또는 `set([...])`     | `frozenset([...])`         |



---
