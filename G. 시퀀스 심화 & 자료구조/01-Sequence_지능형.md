# Sequence
Python에서 시퀀스 자료형 처리와 지능형 리스트(List Comprehension), 그리고 map, filter를 활용한 고급 리스트 변환

## 🧠 시퀀스 자료형 분류 요약
| 분류       | 설명                                      | 예시                                      |
|------------|-------------------------------------------|-------------------------------------------|
| Container  | 서로 다른 자료형을 담을 수 있음            | `list`, `tuple`, `collections.deque`      |
| Flat       | 단일 자료형만 담을 수 있음                | `str`, `bytes`, `bytearray`, `array.array`, `memoryview` |
| 가변       | 값 변경 가능                              | `list`, `dict`, `set`, `bytearray`, `deque` 등 |
| 불변       | 값 변경 불가                              | `tuple`, `str`, `bytes`                   |



## 🔍 지능형 리스트 vs map/filter
### ✅ 기본 for-loop 방식
```python
code_list = []
for s in chars:
    code_list.append(ord(s))
```

### ✅ 지능형 리스트 (List Comprehension)
```python
code_list2 = [ord(s) for s in chars]
```

→ 더 간결하고 Pythonic한 방식

### 🔧 조건 필터링 방식 비교
#### 1. List Comprehension + 조건
```python
code_list3 = [s for s in chars if ord(s) > 40]
```
- 문자 자체를 필터링
- 결과: ['+', '_', ')', '*', '^', '@', 'i', ')']


#### 2. map + filter
```python
code_list4 = list(filter(lambda c: c > 40, map(ord, chars)))
```

- 문자 → ASCII 변환 후 필터링
- 결과: [43, 95, 41, 42, 94, 64, 105, 41]


### 3. 문자 필터링 직접
```python
code_list5 = list(filter(lambda c: ord(c) > 40, chars))
```

- 문자 그대로 필터링
- 결과: ['+', '_', ')', '*', '^', '@', 'i', ')']

## 📘 요약 테이블
| 방식               | 설명                                  | 결과 예시                      |
|--------------------|---------------------------------------|--------------------------------|
| for-loop           | 전통적인 방식                          | `[43, 95, 41, ...]`            |
| list comprehension | 간결하고 빠름                          | `[ord(s) for s in chars]`      |
| map + filter       | 함수형 스타일                          | `[43, 95, 41, ...]`            |
| filter + ord 조건  | 문자 기준 필터링                       | `['+', '_', ')', ...]`         |

---

## 💡 실전 팁
- map(ord, chars) → 문자 → 숫자 변환
- filter(lambda c: ...) → 조건에 맞는 값만 추출
- chr(n) → 숫자 → 문자 변환
- list comprehension은 대부분의 경우 가독성과 성능에서 우위

## 전체 코드
```python

# Case1
chars = '+_)(*&^%$#@i)'
code_list = []
for s in chars:
    code_list.append(ord(s))

print(code_list)
'''[43, 95, 41, 40, 42, 38, 94, 37, 36, 35, 64, 105, 41]'''


# Case2
code_list2 = [ord(s) for s in chars]
print(code_list2)
'''[43, 95, 41, 40, 42, 38, 94, 37, 36, 35, 64, 105, 41]'''


# Case 3 : Comprehending Lists + Map, Filter
code_list3 = [s for s in chars if ord(s) > 40]
print(code_list3)
'''['+', '_', ')', '*', '^', '@', 'i', ')']'''

# Case 4: 
code_list4 = list(filter(lambda c: c > 40, map(ord, chars)))
print(code_list4)
'''[43, 95, 41, 42, 94, 64, 105, 41]'''

# Case 5
print([chr(s) for s in code_list4])
'''['+', '_', ')', '*', '^', '@', 'i', ')']'''


# Case 6
code_list5 = list(filter(lambda c: ord(c) > 40, chars))
print(code_list5)
'''['+', '_', ')', '*', '^', '@', 'i', ')']'''

```

