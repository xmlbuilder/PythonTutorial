## 📘 Named Tuple이란?

### 📌 정의
- collections.namedtuple은 튜플 기반의 경량 객체를 생성하는 팩토리 함수입니다.
- 일반 튜플처럼 **불변(immutable)** 이며, 인덱스뿐 아니라 이름으로도 접근할 수 있습니다.
- 객체처럼 동작하면서도 메모리 효율이 높고, 코드 가독성이 뛰어납니다.


### 📌 선언 방식
```python
from collections import namedtuple

Point1 = namedtuple('Point1', 'x y')               # 공백으로 필드 나열
Point2 = namedtuple('Point2', ['x', 'y'])           # 리스트로 필드 나열
Point3 = namedtuple('Point3', 'x, y')               # 쉼표로 필드 나열
Point4 = namedtuple('Point4', 'x y z class', rename=True)  # 예약어 자동 리네임
```

- rename=True → 예약어(class)는 자동으로 _3처럼 변경됨

### 📌 생성 및 접근
```python
p = Point1(1.0, 2.0)
print(p.x, p.y)     # 이름으로 접근
print(p[0], p[1])   # 인덱스로 접근
```

- `**dict` 언패킹도 가능: Point1(**{'x': 10, 'y': 20})

### 📌 Named Tuple 주요 메서드

| 메서드        | 설명                                      |
|---------------|-------------------------------------------|
| `_make(iter)` | iterable로부터 새로운 NamedTuple 생성       |
| `_fields`     | 필드 이름들을 튜플 형태로 반환              |
| `_asdict()`   | 필드 값을 `OrderedDict`로 반환              |


### 📌 예시로 확인해보기
```python
Point = namedtuple('Point', ['x', 'y'])

pt = Point(10, 20)

print(Point._make([30, 40]))     # Point(x=30, y=40)
print(pt._fields)                # ('x', 'y')
print(pt._asdict())              # OrderedDict([('x', 10), ('y', 20)])
```


### 📌 일반 튜플 vs Named Tuple

| 항목               | 일반 튜플                         | Named Tuple                          |
|--------------------|-----------------------------------|--------------------------------------|
| 선언 방식           | `(x, y)`                          | `namedtuple('Point', ['x', 'y'])`    |
| 접근 방식           | 인덱스 기반 (`pt[0]`)             | 이름 기반 (`pt.x`) + 인덱스 (`pt[0]`) |
| 가독성              | 낮음                              | 높음                                 |
| 불변성              | 있음                              | 있음                                 |
| 메모리 효율         | 높음                              | 높음                                 |
| 메서드 지원         | 없음                              | `_make()`, `_fields`, `_asdict()`    |


### 📌 실전 활용 예시
```python
Classes = namedtuple('Classes', ('rank', 'number'))
students = [Classes(rank, number) for rank in ['A', 'B', 'C', 'D'] for number in map(str, range(1, 21))]
print(students[0])            # Classes(rank='A', number='1')
print(students[0].rank)       # 'A'
print(len(students))          # 80
```

- 데이터 구조화, CSV 파싱, 좌표 표현, 로그 기록 등에 유용

### 📌 요약
| 특징           | 설명                                      |
|----------------|-------------------------------------------|
| 선언 방식       | `namedtuple('Name', ['field1', 'field2'])` |
| 접근 방식       | `.field` 또는 `[index]`                   |
| 주요 메서드     | `_make()`, `_fields`, `_asdict()`         |
| 장점           | 가독성, 메모리 효율, 불변성               |
| 활용 분야       | 좌표, 학생 정보, 로그, 설정값 등          |


### 📌 전체 소스
```python
# 일반적인 튜플
pt1 = (1.0, 5.0)
pt2 = (2.5, 1.5)

from math import sqrt

l_length1 = sqrt((pt1[0] - pt2[0]) ** 2 + (pt1[1] - pt2[1]) ** 2)

print(l_length1)
```
#### 🔹 출력 결과
```
3.8078865529319543
```
### 📌 네임드 튜플 사용 (Named tuple)
```python
from collections import namedtuple

#Point = namedtuple('Point', 'x y')
Point = namedtuple('Point', ('x', 'y'))

pt3 = Point(1.0, 2.0)
pt4 = Point(3.0, 4.0)

print(pt3)
```
#### 🔹 출력 결과
```
Point(x=1.0, y=2.0)
```
```python
print(pt4)
```
#### 🔹 출력 결과
```
Point(x=3.0, y=4.0)
```
```python
l_length2 = sqrt((pt3[0] - pt4[0]) ** 2 + (pt3[1] - pt4[1]) ** 2)
print(l_length2)
```
#### 🔹 출력 결과
```
2.8284271247461903
```
```python
l_length3 = sqrt((pt3.x - pt4.x) ** 2 + (pt3.y - pt4.y) ** 2)
print(l_length3)
```
#### 🔹 출력 결과
```
2.8284271247461903
```

#### 🔹 네임드 튜플 선언 방법
```python
Point1 = namedtuple('Point1', 'x y')
Point2 = namedtuple('Point2', ['x','y'])
Point3 = namedtuple('Point3', 'x, y')
Point4 = namedtuple('Point4', 'x y z class', rename=True)

print(Point1, Point2,Point3, Point4)
'''<class '__main__.Point1'> <class '__main__.Point2'> <class '__main__.Point3'> <class '__main__.Point4'>'''

p1 = Point1(x = 1.0, y = 2.0)
p2 = Point2(3.0, 4.0)
p3 = Point3(3.0, y=4.0)
p4 = Point4(10, 20, 30, 40)

print(p4)
```
#### 🔹 출력 결과
```
Point4(x=10, y=20, z=30, _3=40)
```

#### 🔹 Dict to Unpacking
```python
temp_dict = {'x' : 75, 'y' : 55}
p5 = Point2(**temp_dict)

print(p5)
```
#### 🔹 출력 결과
```
Point2(x=75, y=55)
```

```python
# 사용
print(p1[0] + p2[0])
```
#### 🔹 출력 결과
```
4.0
```
```python
print(p1.x + p2.x)
```
#### 🔹 출력 결과
```
4.0
```
```python
x, y = p1.x, p1.y
x1, y1 = p1
print(x, y, x1, y1)
```
#### 🔹 출력 결과
```
1.0 2.0 1.0 2.0
```

### 📌 네임드 튜플 메소드
#### 🔹 새로운 객체 생성
```python
temp = [52, 38]
pt4 = Point2._make(temp)
print(pt4)
```
#### 🔹 출력 결과
```
Point2(x=52, y=38)
```

#### 🔹 _fields : 필드 네임 확인
```python
print(p1._fields, p2._fields, p3._fields, p4._fields)
```
#### 🔹 출력 결과
```
('x', 'y') ('x', 'y') ('x', 'y') ('x', 'y', 'z', '_3')
```

#### 🔹 _asdict() : OrderedDict 반환
```python
print(p1._asdict())
```
#### 🔹 출력 결과
```
{'x': 1.0, 'y': 2.0}
```
```python
print(p4._asdict())
```
#### 🔹 출력 결과
```
{'x': 10, 'y': 20, 'z': 30, '_3': 40}
```

### 📌 실 사용 실습

#### 🔹 반 20명 4개의 반(A, B, C, D)
```python
Classes = namedtuple('Classes', ('rank', 'number'))
numbers = [str(n) for n in range(1, 21)]
print(numbers)
```
#### 🔹 출력 결과
```
['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20']
```
```python
ranks = 'A B C D '.split()
print(ranks)
```
#### 🔹 출력 결과
```
['A', 'B', 'C', 'D']
```

#### 🔹 List Comprehension
```python
students = [Classes(rank, number) for rank in ranks for number in numbers]

print(students)
```
#### 🔹 출력 결과
```
[Classes(rank='A', number='1'), ..., Classes(rank='D', number='19'), Classes(rank='D', number='20')]
```
```python
print(len(students))
```
#### 🔹 출력 결과
```
80
```
```python
print(students[0].number, students[0].rank)
```
#### 🔹 출력 결과
```
1 A
```
```python
for s in students:
    print(s)
```
#### 출력 결과
```
Classes(rank='A', number='1')
Classes(rank='A', number='2')
...
Classes(rank='D', number='19')
Classes(rank='D', number='20')
'''
```

----






