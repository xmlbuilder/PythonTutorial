# Immutable dict
Python에서의 Immutable dict와 set, 그리고 해시테이블 구조에 대한 핵심 정리입니다. 
MappingProxyType을 활용한 불변 딕셔너리와 관련된 동작까지 깔끔하게 요약.

## 🧠 해시테이블 구조 이해
- 해시테이블: 키를 해싱하여 메모리 주소에 직접 접근하는 자료구조
- dict: Python의 대표적인 해시테이블 구현체
- 키 중복 ❌
- 순서 보존 ✅ (Python 3.7+)

- set: 중복 없는 키 집합
- 값 자체가 키 역할
- 순서 없음, 중복 ❌

## 🔐 Immutable dict: MappingProxyType
```python
from types import MappingProxyType

d = {'key1': 'value1', 'key2': 'value2'}
d_frozen = MappingProxyType(d)
```

## 🔐 MappingProxyType 요약
| 항목               | 설명                                                  |
|--------------------|-------------------------------------------------------|
| `MappingProxyType` | dict를 읽기 전용으로 감싸는 proxy 객체                 |
| `id(d)` vs `id(d_frozen)` | 서로 다른 객체 → 원본과 proxy는 별도 메모리 주소       |
| `hash(d_frozen)`   | ❌ TypeError 발생 → dict는 가변 객체라 해시 불가         |



## 🔍 동작 예시
```python
d['key3'] = 'value3'      # ✅ 원본 dict 수정 가능
d_frozen['key3'] = 'value3'  # ❌ TypeError: 수정 불가
```

→ MappingProxyType은 불변 dict처럼 동작하지만, 내부적으로는 원본 dict를 참조하므로 원본이 바뀌면 proxy도 바뀝니다.

## 📘 요약 테이블
| 구조/기능         | dict                 | set                  | MappingProxyType         |
|------------------|----------------------|----------------------|---------------------------|
| 중복 허용         | ❌ key 중복 불가       | ❌ 값 중복 불가        | ❌ key 중복 불가           |
| 수정 가능         | ✅ 가능               | ✅ 가능               | ❌ 불가능 (읽기 전용)       |
| 해시 가능 여부     | ❌ dict 자체는 불가능   | ✅ set은 가능          | ❌ proxy도 불가능           |
| 용도              | 키-값 저장            | 유일한 값 저장         | 안전한 읽기 전용 dict 제공 |

---

## 전체 코드
```python
# immutable dic
from types import MappingProxyType
d = {'key1' : 'value1', 'key2' : 'value2'}

# Read only
d_frozen = MappingProxyType(d)

print(d_frozen)
print(d, id(d))
'''
{'key1': 'value1', 'key2': 'value2'} 4308867712
'''
print(d_frozen, id(d_frozen))
'''
{'key1': 'value1', 'key2': 'value2'} 4326409840
'''

#print(hash(d_frozen))
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 21, in <module>
    print(hash(d_frozen))
          ^^^^^^^^^^^^^^
TypeError: unhashable type: 'dict'
'''

# 수정 가능
d['key3'] = 'value3'
print(d)
'''{'key1': 'value1', 'key2': 'value2', 'key3': 'value3'}'''

#d_frozen['key3'] = 'value3'
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 34, in <module>
    d_frozen['key3'] = 'value3'
    ~~~~~~~~^^^^^^^^
TypeError: 'mappingproxy' object does not support item assignment
'''

```