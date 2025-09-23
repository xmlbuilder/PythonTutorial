# 🧠 Sequence 개념 요약
Python의 시퀀스(Sequence) 관련 핵심 개념들을 튜플, 가변/불변 객체, 정렬 방식 중심으로 깔끔하게 정리한 요약입니다:


## ✅ 시퀀스란?
- 순서가 있는 자료형
- 대표적으로 list, tuple, str, range, array.array 등이 있음

## 🧩 Tuple: 불변 시퀀스

| 기능           | 설명                                      | 예시                                      |
|----------------|-------------------------------------------|-------------------------------------------|
| 선언 방식       | 괄호 또는 tuple()로 생성                   | `(1, 2, 3)`, `tuple([1, 2, 3])`            |
| 불변성          | 값 변경 불가, 메모리 주소 변경됨           | `id(t)` 변경 확인                         |
| 언패킹          | 변수에 순서대로 할당 가능                  | `a, b = b, a`, `x, y, *rest = range(10)`  |
| 함수 인자 전달  | 튜플을 인자로 분해하여 함수에 전달         | `divmod(*(100, 9))` → `divmod(100, 9)`    |
| 함수 반환값     | 여러 값 반환 시 튜플로 자동 포장           | `quot, rem = divmod(100, 9)`              |


## 🔁 Mutable vs Immutable

| 항목           | 설명                              | list (m)                        | tuple (l)                        |
|----------------|-----------------------------------|----------------------------------|----------------------------------|
| 가변성          | 값 변경 가능 여부                  | ✅ (mutable)                     | ❌ (immutable)                   |
| 연산 후 주소     | `*= 2` 연산 후 메모리 주소 변화     | 유지됨 (같은 객체)               | 변경됨 (새 객체 생성됨)          |
| 연산 결과       | 값이 두 배로 늘어남                | `[15, 20, 25, 15, 20, 25]`       | `(15, 20, 25, 15, 20, 25)`       |
| 추가 연산 후 주소| `*= 2` 다시 실행 시 주소 변화 여부 | 동일 주소 유지                   | 새로운 주소 생성됨               |
| 예시            | `m *= 2`                          | `[15, 20, 25, ...]` (주소 동일)  | `(15, 20, 25, ...)` (주소 변경)  |

```python
m = [15, 20, 25]
l = (15, 20, 25)
print(id(m))  # 가변 → 주소 유지
print(id(l))  # 불변 → 주소 변경
```

## 🔃 sort vs sorted

| 항목         | 설명                            | 반환값       | 원본 변경 | 사용 대상     |
|--------------|----------------------------------|--------------|------------|----------------|
| `sorted()`   | 정렬된 **새 리스트** 반환         | 새 리스트     | ❌ 변경 없음 | 모든 iterable  |
| `sort()`     | 리스트를 **제자리에서 정렬**       | `None`       | ✅ 변경됨   | 리스트만 가능  |


### 🔍 예시 비교
```python
f_list = ['10', '4', '30']
print(sorted(f_list))   # ['10', '30', '4']
print(f_list)           # ['10', '4', '30'] → 원본 유지

f_list.sort()
print(f_list)           # ['10', '30', '4'] → 원본 변경됨
```

### ✅ 정렬 옵션
- reverse=True → 내림차순
- key=len → 길이 기준
- key=lambda x: x[-1] → 마지막 문자 기준

## 🧮 List vs Array 사용법

| 항목           | list                                | array.array                           | 비고                         |
|----------------|-------------------------------------|----------------------------------------|------------------------------|
| 자료형 제한     | 없음 (혼합 가능)                     | 있음 (단일 타입만 저장)                | 숫자 처리에 array가 유리     |
| 메모리 효율     | 일반적                               | 더 효율적 (특히 대량 숫자 처리 시)      | array는 C 기반 구조 사용     |
| 선언 방식       | `[1, 2, 3]`                          | `array('i', [1, 2, 3])`                | `'i'`, `'f'`, `'d'` 등 타입코드 필요 |
| 기능 확장성     | 매우 높음                            | 제한적 (기본 연산 중심)                 | list는 다양한 메서드 지원    |
| 변환 기능       | 기본 제공 없음                       | `.tolist()` → 일반 리스트로 변환 가능   | array → list 변환 가능       |



## 📘 요약 테이블
| 개념           | 핵심 요약                                      |
|----------------|------------------------------------------------|
| Tuple          | 불변 시퀀스, 언패킹 가능, 함수 인자 전달에 유용 |
| Mutable/Immutable | list는 가변, tuple은 불변                     |
| sort/sorted    | sort는 원본 변경, sorted는 새 객체 반환         |
| List vs Array  | list는 범용적, array는 숫자 처리에 최적화       |


## 예제 정리
```python

# Tuple
a = 1
b = 2
b, a = a, b
print(a, b)
'''2 1'''

print(divmod(100, 9))
'''(11, 1)'''

#print(divmod((100, 9)))
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 11, in <module>
    print(divmod((100, 9)))
          ^^^^^^^^^^^^^^^^
TypeError: divmod expected 2 arguments, got 1
'''
# Unpacking
print(divmod(*(100, 9)))
'''(11, 1)'''

print(*(divmod(100, 9)))
'''11 1'''

#x, y, rest = range(10)
'''
Traceback (most recent call last):
  File "/Users/jeongjunghwan/PycharmProjects/Tutorial2/module_test.py", line 25, in <module>
    x, y, rest = range(10)
    ^^^^^^^^^^
ValueError: too many values to unpack (expected 3)
'''

x, y, *rest = range(10)
print(x, y, rest)
'''0 1 [2, 3, 4, 5, 6, 7, 8, 9]'''

x, y, *rest = range(2)
print(x, y, rest)
'''0 1 []'''

x, y, *rest = 1, 2, 3, 4, 5
print(x, y, rest)
'''1 2 [3, 4, 5]'''

# Mutable vs Immutable
l = (15, 20, 25)
m = [15, 20, 25]
print(l, id(l))
print(m, id(m))
'''
(15, 20, 25) 4353672896
[15, 20, 25] 4350972544
'''

l = l * 2
m = m * 2
print(l, id(l))
print(m, id(m))
'''
(15, 20, 25, 15, 20, 25) 4394998016
[15, 20, 25, 15, 20, 25] 4377396032
'''

l *=  2
m *=  2
print(l, id(l))
print(m, id(m))
'''
(15, 20, 25, 15, 20, 25, 15, 20, 25, 15, 20, 25) 4314936464
[15, 20, 25, 15, 20, 25, 15, 20, 25, 15, 20, 25] 4377396032 # id가 같다 (가변 객체이기 때문)
'''

# sort vs sorted
# sorted : 정렬 후 새로운 객체 반환
# sort : 정렬 후 객체 변경

f_list = ['10', '12', '30', '4', '15', '60', '27', '48', '29']
print('sorted - ', sorted(f_list))
'''sorted -  ['10', '12', '15', '27', '29', '30', '4', '48', '60']'''

print(f_list)
'''['10', '12', '30', '4', '15', '60', '27', '48', '29']'''

print('sorted - ', sorted(f_list, reverse=True))
'''sorted -  ['60', '48', '4', '30', '29', '27', '15', '12', '10']'''

print('sorted - ', sorted(f_list, key=len))
'''sorted -  ['4', '10', '12', '30', '15', '60', '27', '48', '29']'''

print('sorted - ', sorted(f_list, key=lambda x:x[-1]))
'''sorted -  ['10', '30', '60', '12', '4', '15', '27', '48', '29']'''

print('sorted - ', sorted(f_list, key=lambda x:x[-1], reverse=True))
'''sorted -  ['29', '48', '27', '15', '4', '12', '10', '30', '60']'''

print('sort - ', f_list.sort())
'''sort -  None'''

print(f_list)
'''['10', '12', '15', '27', '29', '30', '4', '48', '60']'''

print('sort - ', f_list.sort(reverse=True))
print(f_list)
'''['60', '48', '4', '30', '29', '27', '15', '12', '10']'''

# List vs Array 적합한 사용법 설명
# 리스트 기반 : 융통성, 다양한 자료형, 범용적 사용
# 숫자 기반 : 배열 (리스트와 거의 호환)

def element_1(x):
    print('input = ', x, x[-1])
    return x[-1]
f_list = ['10', '12', '30', '4', '15', '60', '27', '48', '29']
print('sorted - ', sorted(f_list, key=element_1))
'''
input =  10 0
input =  12 2
input =  30 0
input =  4 4
input =  15 5
input =  60 0
input =  27 7
input =  48 8
input =  29 9
sorted -  ['10', '30', '60', '12', '4', '15', '27', '48', '29']
'''

```