# itertools

Python의 고성능 반복자 라이브러리인 itertools에 대한 체계적이고 상세한 설명입니다.
각 함수의 역할, 특징, 예제 흐름까지 정리.

## 🧠 itertools란?
- Python 표준 라이브러리 중 하나
- 효율적이고 메모리 절약적인 반복자(iterator) 생성 도구 모음
- 대부분 lazy evaluation 방식 → 필요한 순간에만 값을 생성

## 🔍 주요 함수 설명
### 1. count(start, step)
- 무한 반복자 생성
- start부터 step씩 증가
```python
itertools.count(1, 2.5) → 1, 3.5, 6.0, 8.5, ...
```


### 2. takewhile(predicate, iterable)
- 조건이 참일 동안만 반복
- 조건이 거짓이 되는 순간 반복 종료
```python
itertools.takewhile(lambda x: x < 40, count(1, 2.5))
```
→ 1, 3.5, ..., 38.5 (40 이상은 제외)



### 3. filterfalse(predicate, iterable)
- 조건이 거짓인 값만 반환
- filter()와 반대
```python
itertools.filterfalse(lambda x: x < 3, [1, 2, 3, 4, 5])
```
→ 3, 4, 5



### 4. accumulate(iterable)
- 누적 합 또는 누적 연산
- 기본은 덧셈, func 인자로 다른 연산도 가능
```python
itertools.accumulate([1, 2, 3, 4])
```
→ 1, 3, 6, 10



### 5. chain(*iterables)
- 여러 iterable을 하나로 연결
- 문자열, 리스트, range 등 모두 가능
```python
itertools.chain('ABC', [1, 2])
```
→ 'A', 'B', 'C', 1, 2



### 6. product(*iterables, repeat=n)
- 데카르트 곱 (모든 조합)
- repeat로 반복 횟수 지정
```python
itertools.product('AB', repeat=2)
```
→ ('A', 'A'), ('A', 'B'), ('B', 'A'), ('B', 'B')



### 7. groupby(iterable)
- 연속된 동일 값을 그룹화
- 정렬된 데이터에서 유용
- key 인자로 그룹 기준 지정 가능
```python
itertools.groupby('AAABBBCCDAABBB')
```
→ A: ['A', 'A', 'A'], B: ['B', 'B', 'B'], ...

⚠️ groupby는 연속된 값만 그룹화하므로, 정렬되지 않은 데이터는 기대한 결과가 아닐 수 있어요.

## ✅ 요약 표
| 함수명        | 기능 요약                         | 관련 개념 / 특징        |
|---------------|------------------------------------|--------------------------|
| count         | 무한 반복자 생성                   | 시작값, 증가폭 지정 가능 |
| takewhile     | 조건이 참일 때까지 반복             | 조건이 False면 종료      |
| filterfalse   | 조건이 거짓인 값만 반환             | `filter()`의 반대         |
| accumulate    | 누적 합 또는 누적 연산              | `operator`로 연산 지정 가능 |
| chain         | 여러 iterable 연결                  | 순서대로 이어붙임         |
| product       | 모든 조합 생성                      | `repeat`로 반복 횟수 지정 |
| groupby       | 연속된 동일 값 그룹화               | 정렬된 데이터에 적합      |

## 전체 코드
```python

import itertools

gen1 = itertools.count(1, 2.5)
print(next(gen1))
print(next(gen1))
print(next(gen1))
print(next(gen1))
print(next(gen1))
'''
1
3.5
6.0
8.5
11.0
'''

# 무한 루프에 빠진다
# while True:
#     print(next(gen1))


gen2 = itertools.takewhile(lambda n: n < 40, gen1)
for v in gen2:
    print(v)
'''
1
3.5
6.0
8.5
11.0
13.5
16.0
18.5
21.0
23.5
26.0
28.5
31.0
33.5
36.0
38.5
'''

gen3 = itertools.filterfalse(lambda n: n < 3, [1, 2, 3, 4, 5])
for v in gen3:
    print(v)
'''
3
4
5
'''

#누적 합계
gen4 = itertools.accumulate([x for x in range(1, 10)])
for v in gen4:
    print(v)
'''
1
3
6
10
15
21
28
36
45
'''

gen4 = itertools.accumulate([x for x in range(1, 10) if x % 2 == 0])
for v in gen4:
    print(v)
'''
2
6
12
20
'''

# 연결 1
gen5 = itertools.chain('ABCDE', range(1, 11, 2))
print(list(gen5))
'''['A', 'B', 'C', 'D', 'E', 1, 3, 5, 7, 9]'''

# 연결 2
gen6 = itertools.chain(enumerate('ABCDEFGHIJK'))
print(list(gen6))
'''[(0, 'A'), (1, 'B'), (2, 'C'), (3, 'D'), (4, 'E'), (5, 'F'), (6, 'G'), (7, 'H'), (8, 'I'), (9, 'J'), (10, 'K')]'''

# 개별
gen7 = itertools.product('ABCDE')
print(list(gen7))
'''[('A',), ('B',), ('C',), ('D',), ('E',)]'''

# 연산 (경우의 수)
gen8 = itertools.product('ABCDE', repeat=2)
print(list(gen8))
'''
[('A', 'A'), ('A', 'B'), ('A', 'C'), ('A', 'D'), ('A', 'E'), 
('B', 'A'), ('B', 'B'), ('B', 'C'), ('B', 'D'), ('B', 'E'), 
('C', 'A'), ('C', 'B'), ('C', 'C'), ('C', 'D'), ('C', 'E'), 
('D', 'A'), ('D', 'B'), ('D', 'C'), ('D', 'D'), ('D', 'E'), 
('E', 'A'), ('E', 'B'), ('E', 'C'), ('E', 'D'), ('E', 'E')]
'''


# 그룹화
gen9 = itertools.groupby('AAABBBCCDAABBB')
#print(list(gen9))
'''
[('A', <itertools._grouper object at 0x105113400>), 
('B', <itertools._grouper object at 0x105113550>), 
('C', <itertools._grouper object at 0x105113580>), 
('D', <itertools._grouper object at 0x1051135b0>),
('A', <itertools._grouper object at 0x1051135e0>), 
('B', <itertools._grouper object at 0x105113610>)]
print 하면 iterator 가 소모되고 있다.
'''

for chr, group in gen9:
    print(chr, ' : ', list(group))
'''
A  :  ['A', 'A', 'A']
B  :  ['B', 'B', 'B']
C  :  ['C', 'C']
D  :  ['D']
A  :  ['A', 'A']
B  :  ['B', 'B', 'B']
'''
```
