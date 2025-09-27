# StrinGIO
 아래는 StringIO와 함께 사용하는 np.genfromtxt()의 다양한 기능을 정리 

## 🔍 핵심 요약.  
 특히 실무에서 자주 쓰이는 delimiter, autostrip, comments, skip_header, usecols 등 옵션들을 예제와 함께 설명

## 📘 StringIO + np.genfromtxt 핵심 정리
### ✅ 1. 기본 사용 — CSV 형식 문자열 읽기
```python
data = u'1, 2, 3\n4,5,6'
np.genfromtxt(StringIO(data), delimiter=',')
```
#### 출력
```
   [[1. 2. 3.]
   [4. 5. 6.]]
```

- StringIO는 문자열을 파일처럼 다룰 수 있게 해줌
- delimiter=','로 CSV 형식 파싱

### ✅ 2. 고정 너비 필드 — delimiter=int 또는 tuple
```python
data1 = u'  1  2  3\n  4  5 67\n890123  4'
np.genfromtxt(StringIO(data1), delimiter=3, dtype=np.int64)
```
#### 출력
```
   [[  1   2   3]
   [  4   5  67]
   [890 123   4]]
```
```python
data2 = u'123456789\n   4  7  9\n   4567 9'
np.genfromtxt(StringIO(data2), delimiter=(4, 3, 2))
```
#### 출력

```
   [[1234.  567.   89.]
   [   4.    7.    9.]
   [   4.  567.    9.]]
```

- delimiter=3 → 고정 너비 3칸씩 분할
- delimiter=(4,3,2) → 각 필드 너비 지정

### ✅ 3. 문자열 처리 — dtype="|U5" + autostrip
```python
data = u"1, abc , 2\n 3, xxx, 4"
np.genfromtxt(StringIO(data), delimiter=",", dtype="|U5")
```
#### 출력
```
   [['1' ' abc ' ' 2']
   ['3' ' xxx' ' 4']]
```
```
np.genfromtxt(StringIO(data), delimiter=",", dtype="|U5", autostrip=True)
```
#### 출력
```
   [['1' 'abc' '2']
   ['3' 'xxx' '4']]
```

- dtype="|U5" → 유니코드 문자열 최대 길이 5
- autostrip=True → 공백 자동 제거

### ✅ 4. 주석 제거 — comments='#'
```
data = u"""#
# Skip me !
# Skip me too !
1, 2
3, 4
5, 6 #This is the third line of the data
7, 8
# And here comes the last line
9, 0
"""
````
```python
np.genfromtxt(StringIO(data), delimiter=',', comments='#')
```
#### 출력
```
   [[1. 2.]
   [3. 4.]
   [5. 6.]
   [7. 8.]
   [9. 0.]]
```

- comments='#' → #로 시작하는 줄 무시
- 줄 끝의 주석도 자동 제거됨

### ✅ 5. 행 건너뛰기 — skip_header, skip_footer
```python
data = "\n".join(str(i) for i in range(10))
np.genfromtxt(StringIO(data))
```
#### 출력
```
[0. 1. 2. 3. 4. 5. 6. 7. 8. 9.]
```
```python
np.genfromtxt(StringIO(data), skip_header=3, skip_footer=5)
```
#### 출력
```
    [3. 4.]
```

- skip_header=n → 앞에서 n줄 건너뜀
- skip_footer=n → 뒤에서 n줄 건너뜀

### ✅ 6. 열 선택 — usecols
```python
data = u"1,2,3\n4,5,6\n7,8,9"
np.genfromtxt(StringIO(data), delimiter=",", usecols=(0, 2))
```
#### 출력
```
→ [[1. 3.]
   [4. 6.]
   [7. 9.]]
```

- usecols=(0, 2) → 0번째와 2번째 열만 추출

## 💡 실무 팁 요약 — np.genfromtxt 주요 옵션

| 옵션         | 기능 설명                          | 실무 활용 예시                     |
|--------------|-------------------------------------|------------------------------------|
| delimiter    | 구분자 또는 고정 너비 필드 지정     | CSV, 고정폭 텍스트 파싱            |
| dtype        | 데이터 타입 지정                    | 문자열, 정수, 실수 처리            |
| autostrip    | 문자열 공백 자동 제거               | 텍스트 정제, 깔끔한 문자열 추출    |
| comments     | 주석 제거                           | 로그, 설정 파일 파싱               |
| skip_header  | 앞부분 줄 건너뛰기                  | 메타데이터 제거, 헤더 무시         |
| skip_footer  | 뒷부분 줄 건너뛰기                  | 요약/통계 제거, 꼬리말 무시        |
| usecols      | 특정 열만 선택                      | 피처 선택, 열 필터링               |



## 한마디
StringIO와 np.genfromtxt() 조합은  
파일 없이도 문자열 데이터를 빠르게 파싱할 수 있어서  
테스트, 로그 분석, 텍스트 기반 데이터 처리에 정말 유용해.  
특히 delimiter=(...)와 usecols은 실무에서 자주 쓰이는 꿀 옵션.  

---

## 실전 예제
```python

import numpy as np
from io import StringIO
data = u'1, 2, 3\n4,5,6'
x = np.genfromtxt(StringIO(data), delimiter=',')
print(x)
'''
[[1. 2. 3.]
 [4. 5. 6.]]
 '''


data1 = u'  1  2  3\n  4  5 67\n890123  4'
x1 = np.genfromtxt(StringIO(data1), delimiter=3, dtype=np.int64)
print(x1)
'''
[[  1   2   3]
 [  4   5  67]
 [890 123   4]]
 '''



data2 = u'123456789\n  4  7  9\n   4567 9'
x2 = np.genfromtxt(StringIO(data2), delimiter=(4, 3, 2))
print(x2)
'''
[[1234.  567.   89.]
 [   4.    7.    9.]
 [   4.  567.    9.]]
'''



data2 = u'123456789\n   4  7 9\n  4567 9'
x2 = np.genfromtxt(StringIO(data2), delimiter=(4, 3, 2))
print(x2)
'''
[[1234.  567.   89.]
 [   4.    7.    9.]
 [  45.   67.    9.]]
'''


data = u"1, abc , 2\n 3, xxx, 4"
# Without autostrip
x1 = np.genfromtxt(StringIO(data), delimiter=",", dtype="|U5")
print(x1, x1.dtype)
'''
[['1' ' abc ' ' 2']
 ['3' ' xxx' ' 4']] <U5
 '''


# With autostrip
x2 = np.genfromtxt(StringIO(data), delimiter=",", dtype="|U5", autostrip=True)
print(x2, x2.dtype)
'''
[['1' 'abc' '2']
 ['3' 'xxx' '4']] <U5
'''




import numpy as np
from io import StringIO
data = u"""#
# Skip me !
# Skip me too !
1, 2
3, 4
5, 6 #This is the third line of the data
7, 8
# And here comes the last line
9, 0
"""



x1 = np.genfromtxt(StringIO(data), delimiter=',', comments='#')
print(x1)
'''
[[1. 2.]
 [3. 4.]
 [5. 6.]
 [7. 8.]
 [9. 0.]]
 '''



data = u"\n".join(str(i) for i in range(10))
print(data)
'''
0
1
2
3
4
5
6
7
8
9
'''



x2 = np.genfromtxt(StringIO(data), )
print(x2)
'''[0. 1. 2. 3. 4. 5. 6. 7. 8. 9.]'''


x3 = np.genfromtxt(StringIO(data), skip_header=3, skip_footer=5)
print(x3)
'''[3. 4.]'''

# usecols argument


```
