#  명령어 정리

## source
```python

from collections import OrderedDict
friend_ordered_dict = OrderedDict([ ('name', ['John', 'Jenny', 'Nate']),
          ('age', [20, 30, 30]),
          ('job', ['student', 'developer', 'teacher']) ] )
df = pd.DataFrame.from_dict(friend_ordered_dict)
df.head()
```

##  1️⃣ import pandas as pd
- 무엇을 하는가?
Python의 외부 라이브러리인 Pandas를 불러옵니다.

- 왜 필요한가?
Pandas는 데이터 분석과 조작에 특화된 라이브러리예요. 테이블 형태의 데이터를 다루기 쉽게 해줍니다.

- as pd는 뭐지?
Pandas를 pd라는 짧은 이름으로 사용하겠다는 뜻이에요. 이후 코드에서 pd.read_csv()처럼 간결하게 쓸 수 있어요.

## Source
```python
df.to_csv('friend_list_from_df.csv')
```


## 2️⃣ data_frame = pd.read_csv('data/friend_list.csv')
- 무엇을 하는가?
'data/friend_list.csv'라는 CSV 파일을 읽어서 data_frame이라는 변수에 저장합니다.

- read_csv()는 뭐지?
Pandas의 함수로, CSV 파일을 읽어서 DataFrame이라는 구조로 변환해 줍니다.

- DataFrame이란?
엑셀처럼 **행(row)과 열(column)**로 구성된 2차원 테이블입니다. Pandas의 핵심 데이터 구조예요.

- 파일 경로 'data/friend_list.csv'는?
현재 작업 디렉토리 기준으로 data 폴더 안에 있는 friend_list.csv 파일을 가리킵니다.

## 3️⃣ data_frame.head()
- 무엇을 하는가?
data_frame의 **상위 5개 행(row)**을 출력합니다.

- 왜 쓰는가?
데이터를 처음 확인할 때, 전체를 보기엔 너무 많으니까 샘플만 미리 확인하는 용도로 사용합니다.

- 변형도 가능해요!
data_frame.head(10)  # 처음 10개 행 보기
data_frame.head(3)   # 처음 3개 행 보기

## 💡 전체 흐름 요약
| 단계 | 명령어                              | 역할               | 설명                                                                 |
|------|-------------------------------------|--------------------|----------------------------------------------------------------------|
| 1️⃣   | import pandas as pd                | 라이브러리 불러오기 | Pandas를 pd라는 이름으로 불러와서 데이터 분석 기능을 사용할 준비를 함 |
| 2️⃣   | pd.read_csv('data/friend_list.csv')| 데이터 불러오기     | CSV 파일을 읽어와서 Pandas의 DataFrame 형태로 저장함                 |
| 3️⃣   | data_frame.head()                  | 데이터 미리보기     | 불러온 데이터의 상위 5개 행을 출력해서 구조와 내용을 빠르게 확인함   |

---

# type(data_frame.job)

이 명령어 type(data_frame.job)은 data_frame이라는 DataFrame에서 "job" 열의 데이터 타입을 확인하는 코드입니다.

## 🔍 결과는 무엇인가요?
<class 'pandas.core.series.Series'>


### 즉, data_frame.job은 Pandas의 Series 객체입니다.

## ✅ 요약 설명
| 객체             | 설명                          |
|------------------|-------------------------------|
| data_frame       | 전체 테이블 (DataFrame 객체)   |
| data_frame.job   | "job" 열만 추출한 Series 객체 |
| type(...)        | 객체의 타입 확인               |
| 결과             | pandas.Series                 |


## 💡 추가 팁
- 열 전체를 다룰 때는 Series로 처리되고,
- 여러 열을 동시에 다루면 DataFrame이 됩니다:
type(data_frame[['name', 'job']])  # 결과: <class 'pandas.core.frame.DataFrame'>

---

# 소스
```python
data_frame.job = data_frame.job.str.upper()
```
## data_frame.job = data_frame.job.str.upper()
이 명령어는 data_frame의 "job" 열에 있는 모든 문자열을 **대문자(UPPERCASE)**로 변환하는 작업입니다. 하나씩 분석해볼게요:

## ✅ 요약 설명
| 구성 요소         | 설명                                      |
|------------------|-------------------------------------------|
| data_frame.job   | "job" 열을 선택한 Series 객체              |
| .str             | 문자열 전용 메서드 접근자                  |
| .upper()         | 각 문자열을 대문자로 변환 ("teacher" → "TEACHER") |
| =                | 변환된 결과를 다시 "job" 열에 저장          |

이 표는 data_frame.job = data_frame.job.str.upper() 명령어의 구조를 한눈에 보여줍니다. 
.lower(), .title(), .replace() 같은 다른 문자열 처리 함수도 같은 방식 정리


## ✅ 예시 전후 비교
### 원래 데이터:  
```
0    student
1  developer
2    teacher
```

### 변환 후:
```
0    STUDENT
1  DEVELOPER
2    TEACHER
```

## 💡 왜 이렇게 하는가?
- 데이터 정규화: "Teacher", "teacher", "TEACHER"처럼 표기 방식이 다르면 분석 시 혼란이 생깁니다.  
대문자로 통일하면 그룹화나 필터링이 쉬워져요.
- 비교 용이성: 특정 값을 찾거나 조건을 걸 때 대소문자 구분 없이 처리할 수 있어요.
- 시각적 일관성: 보고서나 시각화 시 깔끔하게 보이도록 정리하는 목적도 있습니다.

---

# 소스
```python
s1 = pd.core.series.Series(['one', 'two', 'three'])
s2 = pd.core.series.Series([1, 2, 3])
pd.DataFrame(data=dict(word=s1, num=s2))
```


## ✅ 1. pd.core.series.Series(...)는 왜 쓰는가?
- 이건 Pandas 내부 경로를 통해 Series 객체를 생성하는 방식인데, 권장되지 않는 방식입니다.
- 보통은 이렇게 간단하게 씁니다:
```python
s1 = pd.Series(['one', 'two', 'three'])
s2 = pd.Series([1, 2, 3])
```


## ✅ 2. dict(word=s1, num=s2)
- 두 개의 Series를 딕셔너리 형태로 묶습니다.
- 키 'word'와 'num'이 각각 열 이름이 되고, 값은 Series 객체입니다.

## ✅ 3. pd.DataFrame(...)
- 딕셔너리를 기반으로 DataFrame을 생성합니다.
- 결과는 다음과 같은 테이블이 됩니다:

```
   word  num
0   one    1
1   two    2
2 three    3
```
## 💡 전체 흐름 요약 (ASCII 표)
| 단계            | 설명                                       |
|-----------------|--------------------------------------------|
| pd.Series(...)   | 1차원 데이터(열)를 생성                    |
| dict(...)        | 열 이름과 데이터를 딕셔너리로 묶음         |
| pd.DataFrame(...)| 딕셔너리를 기반으로 테이블(DataFrame) 생성 |

## 🎯 결론
- pd.core.series.Series(...)는 동작은 하지만 비표준 방식이므로   
pd.Series(...)를 사용하는 것이 더 안전하고 가독성이 좋습니다.
- 이 코드는 두 개의 열을 가진 DataFrame을 만드는 아주 기본적인 예제예요.

---

# 소스
```python
df = pd.read_csv('data/friend_list.csv')
```

## 🔍 코드 분석: df = pd.read_csv('data/friend_list.csv')
| 구성 요소              | 설명                                               |
|------------------------|----------------------------------------------------|
| pd                     | `import pandas as pd`로 불러온 Pandas 라이브러리  |
| read_csv()             | CSV 파일을 읽어와서 DataFrame으로 변환하는 함수   |
| 'data/friend_list.csv' | 불러올 CSV 파일의 경로                            |
| df = ...               | 읽어온 데이터를 df라는 변수에 저장                |


## ✅ 결론
- df는 이제 friend_list.csv의 내용을 담고 있는 Pandas DataFrame입니다.
- 이후에는 df.head(), df.info(), df.describe() 같은 명령어로 데이터를 탐색하거나 분석할 수 있음.


## 💡 예시 흐름
| 단계             | 설명                                               |
|------------------|----------------------------------------------------|
| pd.read_csv(...) | CSV 파일을 읽어와서 DataFrame으로 변환             |
| '파일 경로'       | 불러올 파일의 위치 지정 ('data/friend_list.csv')   |
| df = ...         | 읽어온 데이터를 df라는 변수에 저장                 |

----


# 소스
```python
df
```

명령어 df는 단순히 DataFrame 객체를 출력하라는 뜻.  
이걸 실행하면 df에 저장된 테이블 형태의 데이터가 화면에 표시됩니다.

## 🔍 코드 분석: df
| 구성 요소 | 설명                                               |
|------------|----------------------------------------------------|
| df         | pd.read_csv('data/friend_list.csv')로 불러온 데이터 |
| 출력       | CSV 파일의 내용을 담은 DataFrame 객체               |


## ✅ 예시 출력 (가상의 friend_list.csv 내용)
```
     name     age       job
0    John    25.0   student
1   Jenny    30.0  developer
2    Nate     NaN   teacher
3      Ed     NaN   dentist
4    Jack    40.0    farmer
5     Ted    35.0  designer
```

- NaN은 결측값(missing value)을 의미합니다.
- 각 열은 "name", "age", "job"로 구성되어 있고,  
각 행은 친구 한 명의 정보입니다.

---

## 소스
```python
df = pd.read_csv('data/friend_list_no_head.csv', header = None)
```

## 🔍 코드 분석: df = pd.read_csv('data/friend_list_no_head.csv', header = None)
| 구성 요소                  | 설명                                                       |
|----------------------------|------------------------------------------------------------|
| pd.read_csv(...)           | Pandas 함수로 CSV 또는 텍스트 파일을 읽어옴               |
| 'data/friend_list_no_head.csv' | 읽어올 파일 경로 (헤더가 없는 CSV 파일)                   |
| header=None                | 첫 줄을 열 이름으로 사용하지 않고, 모든 줄을 데이터로 처리 |
| df = ...                   | 읽어온 데이터를 df라는 변수에 저장                        |


## ✅ 결과
파일 내용이 다음과 같다고 가정하면:
```
John,25,student
Jenny,30,developer
Nate,,teacher
```

header=None을 지정했기 때문에 Pandas는 열 이름을 자동으로 0, 1, 2로 설정합니다:
```
       0     1          2
0   John  25.0     student
1  Jenny  30.0   developer
2   Nate   NaN     teacher
```


## 💡 왜 header=None을 쓰는가?
- CSV 파일에 열 이름이 포함되어 있지 않을 때 사용합니다.
- 그렇지 않으면 첫 번째 행이 열 이름으로 잘못 처리될 수 있음.

## 📌 다음 단계
- 열 이름을 직접 지정하고 싶다면 names 옵션을 함께 사용:
```python
df = pd.read_csv('data/friend_list_no_head.csv', header=None, names=['name', 'age', 'job'])
```
이렇게 하면 더 보기 좋은 구조로 데이터를 다룰 수 있음.


---

# 소스
```python
df.columns = ['name', 'age', 'job']

```

## 🔍 코드 분석: df.columns = ['name', 'age', 'job']
| 구성 요소         | 설명                                           |
|------------------|------------------------------------------------|
| df.columns        | df의 열 이름을 나타내는 속성                   |
| =                 | 새로운 값을 할당함                             |
| ['name', 'age', 'job'] | 열 이름을 직접 지정함 ("name", "age", "job") |


## ✅ 언제 사용하는가?
- CSV 파일에 헤더가 없거나, 열 이름이 자동으로 숫자(0, 1, 2)로 지정된 경우
- 열 이름을 더 의미 있게 바꾸고 싶을 때
- 데이터 정제 과정에서 열 이름을 통일하거나 수정할 때

## 💡 예시 전후 비교
### 전:
```
   0     1         2
0  John  25   student
1 Jenny  30 developer
```

###  후:
```
   name  age       job
0  John   25   student
1 Jenny   30 developer
```

## 📌 주의할 점
- 열 개수와 리스트 길이가 정확히 일치해야 합니다. 예를 들어 열이 3개인데 이름을 2개만 주면 오류가 발생.
- 열 이름은 문자열 리스트로 지정해야 합니다.

## 🔁 열 순서 바꾸기
예를 들어 df에 "name", "age", "job"이라는 열이 있을 때, "job"을 맨 앞으로 옮기고 싶다면:

```python
df = df[['job', 'name', 'age']]
```

### 💡 설명
- df[...]는 원하는 열 순서를 리스트로 지정하는 방식입니다.
- 이 코드는 기존 df를 덮어씌우므로, df 자체가 바뀝니다.

## 🎯 특정 열만 선택하기
예를 들어 "name"과 "job" 열만 보고 싶다면:
```python
df_subset = df[['name', 'job']]
```

## 💡 설명
- df_subset은 df에서 "name"과 "job" 열만 추출한 새로운 DataFrame입니다.
- 원본 df는 그대로 유지됩니다.

## ✅ ASCII 표 요약
| 작업 유형         | 코드 예시                        | 설명                                 |
|------------------|----------------------------------|--------------------------------------|
| 열 순서 바꾸기    | df = df[['job', 'name', 'age']]  | 원하는 순서대로 열을 재배치          |
| 특정 열만 선택하기 | df_subset = df[['name', 'job']]  | 일부 열만 추출해서 새 DataFrame 생성 |

---

# 소스 
```python
friend_dict_list = [{'name': 'Jone', 'age': 20, 'job': 'student'},
         {'name': 'Jenny', 'age': 30, 'job': 'developer'},
         {'name': 'Nate', 'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list)

```

## 🔍 코드 분석
friend_dict_list = [
    {'name': 'Jone', 'age': 20, 'job': 'student'},
    {'name': 'Jenny', 'age': 30, 'job': 'developer'},
    {'name': 'Nate', 'age': 30, 'job': 'teacher'}
]

df = pd.DataFrame(friend_dict_list)

## ✅ 설명 요약
| 구성 요소           | 설명                                           |
|--------------------|------------------------------------------------|
| friend_dict_list    | 친구 정보를 담은 딕셔너리들의 리스트           |
| 각 딕셔너리         | 한 사람의 name, age, job 정보를 포함            |
| pd.DataFrame(...)   | 리스트를 테이블 형태의 DataFrame으로 변환       |
| df                  | 최종적으로 생성된 DataFrame 객체                |


## 📋 결과 예시 (df 출력)
```
    name  age        job
0   Jone   20    student
1  Jenny   30  developer
2   Nate   30    teacher
```


## 💡 활용 팁
- df["job"] → 직업 열만 추출
- df[df["age"] > 25] → 25세 이상 친구만 필터링
- df.to_csv("friends.csv", index=False) → CSV로 저장

---

## 소스 
```
df = df[['name', 'age', 'job']]
```

## 🔍 코드 분석: df = df[['name', 'age', 'job']]
| 구성 요소               | 설명                                               |
|------------------------|----------------------------------------------------|
| df[['name', 'age', 'job']] | 원하는 열 순서를 리스트로 지정해서 추출               |
| df = ...               | 추출한 결과를 다시 df에 저장 (덮어쓰기)             |


## ✅ 왜 이렇게 쓰는가?
- 열 순서를 명확하게 지정하고 싶을 때
- 특정 열만 선택적으로 유지하고 나머지는 제거하고 싶을 때
- 시각화나 출력 시 보기 좋은 순서로 정리하고 싶을 때

## 📋 예시 전후 비교
### 원래 순서:
```
   job     name  age
0  student  Jone   20
```

### 바꾼 후:
```
   name  age     job
0  Jone   20  student
```

---

## 소스
```python
from collections import OrderedDict
```

## 🔍 코드 분석: from collections import OrderedDict
| 구성 요소             | 설명                                                       |
|----------------------|------------------------------------------------------------|
| collections           | Python의 표준 라이브러리로, 다양한 컨테이너 자료형을 제공 |
| OrderedDict           | 입력 순서를 기억하는 딕셔너리 자료형                      |
| from ... import ...   | 특정 모듈에서 원하는 클래스나 함수를 불러오는 구문         |


## ✅ OrderedDict의 특징
- 입력한 순서대로 항목을 기억합니다.
- 일반 dict와 거의 동일하게 작동하지만, 순서가 중요한 경우에 유용합니다.
- 예시:

```python
from collections import OrderedDict
data = OrderedDict()
data['banana'] = 3
data['apple'] = 5
data['orange'] = 2

print(data)

# 출력: OrderedDict([('banana', 3), ('apple', 5), ('orange', 2)])
```



## 📌 언제 쓰면 좋을까?
- CSV나 JSON을 만들 때 열 순서가 중요할 때
- 반복문에서 입력 순서대로 처리하고 싶을 때
- 딕셔너리의 순서를 보존하면서 정렬하거나 필터링할 때

---


# 소스
```python
friend_ordered_dict = OrderedDict([ ('name', ['John', 'Jenny', 'Nate']), ('age', [20, 30, 30]), ('job', ['student', 'developer', 'teacher']) ] ) 
df = pd.DataFrame.from_dict(friend_ordered_dict)

```

## 🔍 코드 분석
```python
from collections import OrderedDict
friend_ordered_dict = OrderedDict([
    ('name', ['John', 'Jenny', 'Nate']),
    ('age', [20, 30, 30]),
    ('job', ['student', 'developer', 'teacher'])
])

df = pd.DataFrame.from_dict(friend_ordered_dict)
```

## ✅ 설명 요약
| 구성 요소                 | 설명                                               |
|--------------------------|----------------------------------------------------|
| OrderedDict([...])       | 열 순서를 유지하며 name, age, job 데이터를 정의     |
| pd.DataFrame.from_dict() | 딕셔너리를 기반으로 DataFrame을 생성               |
| df                       | 최종적으로 생성된 테이블 형태의 데이터             |


## 📋 결과 예시 (df 출력)
```
    name  age        job
0   John   20    student
1  Jenny   30  developer
2   Nate   30    teacher
```

열 순서가 OrderedDict에 지정한 그대로 유지된다는 점이 핵심!

## 💡 언제 유용한가?
- 열 순서가 중요한 보고서나 시각화를 만들 때
- 딕셔너리 기반으로 데이터를 만들면서 구조를 명확히 제어하고 싶을 때
- JSON → DataFrame 변환 시 정렬된 구조를 유지하고 싶을 때


---

# 소스
```python
friend_list = [ ['John', 20, 'student'],['Jenny', 30, 'developer'],['Nate', 30, 'teacher'] ]
column_name = ['name', 'age', 'job']
df = pd.DataFrame.from_records(friend_list, columns=column_name)

```

## 🔍 코드 분석
```python
friend_list = [
    ['John', 20, 'student'],
    ['Jenny', 30, 'developer'],
    ['Nate', 30, 'teacher']
]

column_name = ['name', 'age', 'job']

df = pd.DataFrame.from_records(friend_list, columns=column_name)
```

## ✅ 설명 요약
| 구성 요소                    | 설명                                                  |
|-----------------------------|-------------------------------------------------------|
| friend_list                 | 각 친구 정보를 담은 리스트 (행 단위로 구성됨)         |
| column_name                 | 열 이름을 정의한 리스트: name, age, job               |
| pd.DataFrame.from_records(...) | 행 리스트를 기반으로 열 이름을 지정해 DataFrame 생성  |
| df                          | 최종적으로 생성된 테이블 형태의 데이터                |


## 📋 결과 예시 (df 출력)
```
    name  age        job
0   John   20    student
1  Jenny   30  developer
2   Nate   30    teacher
```

## 💡 언제 유용한가?
- 데이터가 행 중심으로 정리되어 있을 때
- 열 이름을 따로 지정해서 구조를 명확히 하고 싶을 때
- 외부 데이터(예: JSON, 리스트)에서 빠르게 테이블화할 때

--- 

# 소스

```python
friend_dict = {
    'name': ['John', 'Jenny', 'Nate'],
    'age': [20, 30, 30],
    'job': ['student', 'developer', 'teacher']
}

df = pd.DataFrame(friend_dict)
print(df)
```

## 🔍 코드 분석
```python
friend_dict = {
    'name': ['John', 'Jenny', 'Nate'],
    'age': [20, 30, 30],
    'job': ['student', 'developer', 'teacher']
}

df = pd.DataFrame(friend_dict)
print(df)
```


## ✅ 설명 요약
| 구성 요소            | 설명                                                  |
|---------------------|-------------------------------------------------------|
| friend_dict         | 각 열 이름을 키로 하고, 값은 리스트로 구성된 딕셔너리 |
| pd.DataFrame(...)   | 딕셔너리를 기반으로 테이블 형태의 데이터 생성         |
| print(df)           | 생성된 DataFrame을 콘솔에 출력                        |


## 📋 출력 결과
```
    name  age        job
0   John   20    student
1  Jenny   30  developer
2   Nate   30    teacher
```


## 💡 활용 팁
- df["age"].mean() → 평균 나이 계산
- df[df["job"] == "developer"] → 개발자만 필터링
- df.to_csv("friends.csv", index=False) → CSV 파일로 저장

---
# 소스

```python
df.to_csv('friend_list_from_df.csv')
```

## 🔍 코드 분석: df.to_csv('friend_list_from_df.csv')
| 구성 요소               | 설명                                                  |
|------------------------|-------------------------------------------------------|
| df                     | 저장할 데이터가 담긴 Pandas DataFrame                 |
| .to_csv(...)           | DataFrame을 CSV 파일로 저장하는 메서드                |
| 'friend_list_from_df.csv' | 저장될 파일 이름 (현재 작업 디렉토리에 생성됨)       |

## ✅ 기본 동작
- CSV 파일이 생성되며, 첫 번째 행은 열 이름, 이후는 각 행의 데이터가 들어갑니다.
- 기본적으로 **행 번호(index)**도 함께 저장됩니다.

### 예시 결과 (friend_list_from_df.csv):
```
,index,name,age,job
0,John,20,student
1,Jenny,30,developer
2,Nate,30,teacher
```

## 💡 옵션 팁
- 행 번호 제외하고 저장하려면:
```python
df.to_csv('friend_list_from_df.csv', index=False)
```

- 다른 인코딩으로 저장 (예: 한글 포함 시):
```python
df.to_csv('friend_list_from_df.csv', index=False, encoding='utf-8-sig')
```

---

# 소소
```python
friend_list = [ ['John', 20, 'student'],['Jenny', 30, 'developer'],['Nate', 30, 'teacher'] ]
df = pd.DataFrame.from_records(friend_list)
```

## ✅ 설명 요약
| 구성 요소                    | 설명                                                  |
|-----------------------------|-------------------------------------------------------|
| friend_list                 | 각 친구 정보를 담은 리스트 (행 단위로 구성됨)         |
| pd.DataFrame.from_records(...) | 행 리스트를 기반으로 DataFrame 생성                   |
| df                          | 최종적으로 생성된 테이블 형태의 데이터                |


## 📋 출력 결과 (df)
```
       0   1          2
0   John  20    student
1  Jenny  30  developer
2   Nate  30    teacher
```

열 이름이 지정되지 않았기 때문에 기본적으로 0, 1, 2라는 숫자 인덱스가 열 이름으로 사용돼요.

## 💡 열 이름 지정하고 싶다면?
```python
df = pd.DataFrame.from_records(friend_list, columns=['name', 'age', 'job'])
```

이렇게 하면 더 보기 좋은 구조로 바뀝니다:
```
    name  age        job
0   John   20    student
1  Jenny   30  developer
2   Nate   30    teacher
```

---

# 소스 분석
```python
df.to_csv('friend_list_from_df.csv', header = False, index = False)
```

## 🔍 코드 분석: df.to_csv('friend_list_from_df.csv', header=False, index=False)
| 구성 요소               | 설명                                                       |
|------------------------|------------------------------------------------------------|
| df                     | 저장할 데이터가 담긴 Pandas DataFrame                      |
| .to_csv(...)           | DataFrame을 CSV 파일로 저장하는 메서드                     |
| 'friend_list_from_df.csv' | 저장할 파일 이름 (현재 작업 디렉토리에 생성됨)             |
| header=False           | 열 이름을 저장하지 않음                                    |
| index=False            | 행 번호(index)를 저장하지 않음                             |


## 📋 저장 결과 예시 (CSV 파일 내용)
```
John,20,student
Jenny,30,developer
Nate,30,teacher
```


## 💡 언제 유용한가?
- CSV 파일을 다른 시스템에 전달할 때, 열 이름이 필요 없는 경우
- 간단한 데이터 저장이나 테스트용 파일 생성 시
- 데이터가 이미 구조화되어 있고, 메타 정보 없이 순수 데이터만 저장하고 싶을 때

---
## 소스 코드
```python
import pandas as pd

friend_dict = {
    'name': ['John', 'Jenny', None],
    'age': [20, None, 30],
    'job': ['student', 'developer', None]
}

df = pd.DataFrame(friend_dict)
print(df)

```

## 📋 출력 결과
```
    name   age        job
0   John  20.0    student
1  Jenny   NaN  developer
2   None  30.0       None
```

## 💡 활용 팁
- df.isnull() → 결측값 위치 확인
- df.dropna() → 결측값이 있는 행 제거
- df.fillna('unknown') → 결측값을 특정 값으로 대체

---


## 소스 코드

```python
df.to_csv('friend_list_from_df.csv', na_rep = '-')
```


## 🔍 코드 분석: df.to_csv('friend_list_from_df.csv', na_rep='-')
| 구성 요소               | 설명                                                  |
|------------------------|-------------------------------------------------------|
| df                     | 저장할 데이터가 담긴 Pandas DataFrame                 |
| .to_csv(...)           | DataFrame을 CSV 파일로 저장하는 메서드                |
| 'friend_list_from_df.csv' | 저장할 파일 이름 (현재 작업 디렉토리에 생성됨)       |
| na_rep='-'             | 결측값(NaN)을 '-'로 대체해서 저장                     |


## 📋 예시 결과 (CSV 내용)
만약 df에 아래와 같은 결측값이 있다면:
```
    name   age        job
0   John  20.0    student
1  Jenny   NaN  developer
2   None  30.0       None
```

저장된 CSV는 이렇게 됩니다:
```
,name,age,job
0,John,20.0,student
1,Jenny,-,developer
2,-,30.0,-
```


## 💡 활용 팁
- na_rep='N/A', na_rep='missing' 등 원하는 문자열로 자유롭게 지정 가능
- 결측값을 시각적으로 구분하기 쉽게 만들 수 있음
- 다른 시스템에서 CSV를 읽을 때 오류를 줄일 수 있음


---
# 소스
```python
friend_dict = {
    'name': ['John', 'Jenny', 'Nate'],
    'age': [20, 30, 30],
    'job': ['student', 'developer', 'teacher']
}
df = pd.DataFrame(friend_dict)
df[1:3]
```

## 🔍 코드 분석: df[1:3]
| 구성 요소 | 설명                                      |
|-----------|-------------------------------------------|
| df        | 전체 Pandas DataFrame 객체                |
| [1:3]     | 두 번째(index=1)부터 세 번째(index=2) 행까지 슬라이싱 |

## ✅ 예시 출력
```
    name  age        job
1  Jenny   30  developer
2   Nate   30    teacher
```


## 💡 슬라이싱 팁
- df[0:2] → 첫 번째부터 두 번째 행
- df[:2] → 처음부터 두 번째 행까지
- df[::2] → 한 행씩 건너뛰며 선택

--- 

#   소스 코드
```python
df.loc[[0,2]]
```

## 🔍 코드 분석: df.loc[[0, 2]]
| 구성 요소     | 설명                                                  |
|--------------|-------------------------------------------------------|
| df           | 전체 Pandas DataFrame 객체                            |
| .loc[[0,2]]  | 0번과 2번 행을 명시적으로 선택                        |


## ✅ 예시 출력
```
    name  age      job
0   John   20  student
2   Nate   30  teacher
```

## 💡 차이점 vs 슬라이싱
| 코드             | 설명                                                             |
|------------------|------------------------------------------------------------------|
| df[1:3]          | 1번부터 2번까지 연속된 행을 슬라이싱 (마지막 index=3은 제외됨)   |
| df.loc[[0,2]]    | 0번과 2번 행을 명시적으로 선택 (비연속 행도 선택 가능)           |

.loc은 정확한 행 번호나 조건을 지정할 때 아주 유용. 
다음으로 df.loc[df["age"] == 30] 같은 조건 필터링도 함께 해볼 수 있음.

-- 

# 소스

```python
df.loc[df["age"] == 30] 
```


## 🔍 코드 분석: df.loc[df["age"] == 30]
| 구성 요소         | 설명                                                  |
|------------------|-------------------------------------------------------|
| df               | 전체 Pandas DataFrame 객체                            |
| df["age"] == 30  | age 열에서 값이 30인 행을 Boolean 조건으로 생성       |
| df.loc[...]      | 조건을 만족하는 행만 선택                             |


## ✅ 예시 출력
```
    name  age        job
1  Jenny   30  developer
2   Nate   30    teacher
```


## 💡 확장 팁
- df.loc[df["job"] == "teacher"] → 직업이 teacher인 행 선택
- df.loc[(df["age"] == 30) & (df["job"] == "teacher")] → 나이 30이고 직업이 teacher인 행 선택
- df.loc[df["age"] >= 25] → 나이가 25 이상인 행 선택

---

# 소스

```python
df_filtered = df[df.age > 25]
df_filtered
```

 코드 분석: df_filtered = df[df.age > 25]
| 구성 요소       | 설명                                                  |
|----------------|-------------------------------------------------------|
| df             | 전체 Pandas DataFrame 객체                            |
| df.age > 25    | age 열에서 값이 25보다 큰 행을 조건으로 생성          |
| df[...]        | 조건을 만족하는 행만 추출                             |
| df_filtered     | 필터링된 결과를 담은 새로운 DataFrame                |


## ✅ 예시 출력
```
    name  age        job
1  Jenny   30  developer
2   Nate   30    teacher
```

## 💡 확장 팁
- df[df.age >= 30] → 나이가 30 이상인 행
- df[df["job"] == "teacher"] → 직업이 teacher인 행
- df[(df.age > 25) & (df.job == "developer")] → 조건 조합도 가능

---
# 소스

```python
df_filtered = df.query('age>25')
df_filtered
```

## 🔍 코드 분석: df_filtered = df.query('age > 25')
| 구성 요소           | 설명                                                  |
|--------------------|-------------------------------------------------------|
| df                 | 전체 Pandas DataFrame 객체                            |
| .query('age > 25') | age 열에서 값이 25보다 큰 행만 조건으로 필터링        |
| df_filtered        | 필터링된 결과를 담은 새로운 DataFrame                 |


## ✅ 예시 출력
```
    name  age        job
1  Jenny   30  developer
2   Nate   30    teacher
```


## 💡 .query() vs Boolean 인덱싱
| 코드                  | 설명                                                             |
|-----------------------|------------------------------------------------------------------|
| df[df.age > 25]       | 일반적인 Boolean 조건 필터링 방식                                |
| df.query('age > 25')  | 문자열 기반 조건식으로 필터링 (가독성 높고 복잡한 조건에 유리함) |

## 두 방식 모두 결과는 동일하지만 .query()는 특히 다음 상황에서 유리해요:
- 열 이름에 공백이나 특수문자가 있을 때
- 조건이 길거나 여러 개일 때
- 외부 변수와 함께 사용할 때 (df.query('age > @min_age'))

---

#  소스

```python
df_filtered = df[(df.age >25) & (df.name == 'Nate')]
df_filtered
```

## 🔍 코드 분석: df_filtered = df[(df.age > 25) & (df.name == 'Nate')]
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| df.age > 25        | age 열에서 값이 25보다 큰 행을 조건으로 생성                     |
| df.name == 'Nate'  | name 열에서 값이 'Nate'인 행을 조건으로 생성                     |
| &                  | 두 조건을 AND로 결합                                              |
| df[...]            | 결합된 조건을 만족하는 행만 추출                                  |
| df_filtered        | 필터링된 결과를 담은 새로운 DataFrame                            |

## ✅ 예시 출력
```
   name  age     job
2  Nate   30  teacher
```

## 💡 확장 팁
- | → OR 조건: df[(df.age > 25) | (df.name == 'Nate')]
- ~ → NOT 조건: df[~(df.name == 'Nate')]
- 괄호는 꼭 써야 해요! 조건마다 괄호로 감싸지 않으면 오류가 날 수 있음.


---

## 소스

```python
df.iloc[:, 0:2]
```

이 코드는 Pandas DataFrame에서 모든 행과 0번부터 1번까지의 열을 선택하는 방식. 
아래처럼 간단하게 분석:

## 🔍 코드 분석: df.iloc[:, 0:2]
| 구성 요소 | 설명                                                             |
|-----------|------------------------------------------------------------------|
| df        | 전체 Pandas DataFrame 객체                                       |
| .iloc     | 정수 기반 인덱싱을 위한 접근자                                   |
| :         | 모든 행 선택                                                     |
| 0:2       | 0번 열부터 1번 열까지 선택 (2번은 포함되지 않음)                 |


## ✅ 예시 출력 (기존 friend_list 기반)
```
       0   1
0   John  20
1  Jenny  30
2   Nate  30
```


## 💡 확장 팁
- df.iloc[1:3, :] → 1번부터 2번 행까지 전체 열 선택
- df.iloc[:, [0, 2]] → 0번과 2번 열만 선택 (비연속 열)
- df.iloc[:, -1] → 마지막 열 선택


---

# 소스
```python
df.iloc[:,[0,2]]
```

## 🔍 코드 분석: df.iloc[:, [0, 2]]
| 구성 요소   | 설명                                                             |
|------------|------------------------------------------------------------------|
| df         | 전체 Pandas DataFrame 객체                                       |
| .iloc      | 정수 기반 인덱싱을 위한 접근자                                   |
| :          | 모든 행 선택                                                     |
| [0, 2]     | 0번 열과 2번 열만 선택 (비연속 열 선택 가능)                      |


## ✅ 예시 출력 (기존 friend_list 기반)]
```
       0          2
0   John    student
1  Jenny  developer
2   Nate    teacher
```

## 💡 확장 팁
- df.iloc[:, [1]] → 두 번째 열만 선택
- df.iloc[:, [0, 2]] → 첫 번째와 세 번째 열만 선택
- 열 이름이 지정되어 있다면 ['name', 'job'] 열만 선택되는 셈


---


### 소스 데이터
```python
df.filter(items=['age', 'job'])
df
```

## 🔍 코드 분석: df.filter(items=['age', 'job'])
| 구성 요소             | 설명                                                  |
|----------------------|-------------------------------------------------------|
| df                   | 전체 Pandas DataFrame 객체                            |
| .filter(items=...)   | 지정한 열 이름만 선택하는 메서드                      |
| ['age', 'job']       | 선택할 열 이름 리스트                                  |



## ✅ 예시 출력
```
   age        job
0   20    student
1   30  developer
2   30    teacher
```


## 📌 주의사항
- .filter()는 기본적으로 열 기준으로 작동하지만, axis=0을 지정하면 행 필터링도 가능.
- 열 이름이 정확히 일치해야 선택됩니다.

## 🔁 df 자체는 변하지 않아요
df.filter(...)는 새로운 DataFrame을 반환하지만, 원래의 df는 그대로 유지. 즉, df를 출력하면 여전히 모든 열이 포함된 원본이 나옵니다:

```
       0   1          2
0   John  20    student
1  Jenny  30  developer
2   Nate  30    teacher
```

열 이름이 지정되지 않았다면 ['age', 'job'] 같은 이름으로 필터링할 수 없음. 이럴 땐 먼저 열 이름을 지정해줘야 함:
```python
df = pd.DataFrame.from_records(friend_list, columns=['name', 'age', 'job'])
```



---

# 소스 데이터
```python
# select columns containing 'a'
df.filter(like='a',axis=1)
```

## 🔍 코드 분석: df.filter(like='a', axis=1)
| 구성 요소     | 설명                                                             |
|--------------|------------------------------------------------------------------|
| df           | 전체 Pandas DataFrame 객체                                       |
| .filter()    | 조건에 맞는 행 또는 열을 선택하는 메서드                         |
| like='a'     | 열 이름 또는 행 인덱스에 'a'가 포함된 항목을 선택                |
| axis=1       | 열 기준으로 필터링                                               |
| axis=0       | 행 기준으로 필터링                                               |

예를 들어 열 이름이 ['name', 'age', 'job']일 경우 like='a', axis=1은 'name'과 'age' 열을 선택하게 됨. 
반대로 axis=0을 쓰면 행 인덱스에 'a'가 포함된 행을 선택.


## ✅ 예시 (열 이름이 있는 경우)
```python
df = pd.DataFrame(friend_list, columns=['name', 'age', 'job'])
df.filter(like='a', axis=1)
```

📋 출력 결과:
```
    name  age
0   John   20
1  Jenny   30
2   Nate   30
```

## 💡 활용 팁
- like='e' → 열 이름에 'e'가 포함된 열 선택
- df.filter(regex='^j', axis=1) → 열 이름이 'j'로 시작하는 열 선택
- df.filter(items=['name', 'job']) → 특정 열 이름 직접 지정


--- 

# 소스
```python
# select columns using regex
df.filter(regex='b$',axis=1)
```

## 🔍 코드 분석: df.filter(regex='b$', axis=1)
| 구성 요소     | 설명                                                                 |
|--------------|----------------------------------------------------------------------|
| df           | 전체 Pandas DataFrame 객체                                           |
| .filter()    | 조건에 맞는 열 또는 행을 선택하는 메서드                            |
| regex='b$'   | 열 이름이 문자 'b'로 끝나는 경우만 선택 (`$`는 끝을 의미하는 정규표현식) |
| axis=1       | 열 기준으로 필터링                                                   |
| axis=0       | 행 기준으로 필터링                                                   |

 방식은 열 이름이 'job', 'club' 처럼 'b'로 끝나는 경우에만 선택. 
 반대로 axis=0을 쓰면 행 인덱스 이름이 'b'로 끝나는 경우를 선택하.


## ✅ 예시
df = pd.DataFrame(friend_list, columns=['name', 'age', 'job'])
df.filter(regex='b$', axis=1)


## 📋 출력 결과:
```
         job
0    student
1  developer
2    teacher
```

## 💡 정규표현식 팁
| 정규표현식     | 의미                                      |
|----------------|-------------------------------------------|
| 'a'            | 열 이름에 'a'가 포함된 경우               |
| 'a$'           | 열 이름이 'a'로 끝나는 경우               |
| '^j'           | 열 이름이 'j'로 시작하는 경우             |
| '[aeiou]'      | 열 이름에 모음(a, e, i, o, u) 중 하나 포함 |


---

# 소스

```python
friend_dict_list = [{'age': 20, 'job': 'student'},
         {'age': 30, 'job': 'developer'},
         {'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list, index = ['John', 'Jenny', 'Nate'])
```

이 코드는 딕셔너리 리스트를 기반으로 인덱스를 지정하여 DataFrame을 생성하는 방식. 
아래에 구조와 설명을 깔끔하게 정리:

## ✅ 코드 설명
```python
import pandas as pd

friend_dict_list = [
    {'age': 20, 'job': 'student'},
    {'age': 30, 'job': 'developer'},
    {'age': 30, 'job': 'teacher'}
]

df = pd.DataFrame(friend_dict_list, index=['John', 'Jenny', 'Nate'])
print(df)
```


## 📋 출력 결과
```
       age       job
John    20    student
Jenny   30  developer
Nate    30    teacher
```


## 🔍 구성 요소 분석
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| friend_dict_list   | 친구 정보를 담은 딕셔너리 리스트 (각 항목은 한 사람의 정보)       |
| pd.DataFrame(...)  | 리스트를 테이블 형태로 변환하는 Pandas 함수                       |
| index=[...]        | 각 행에 이름(인덱스) 지정 → 'John', 'Jenny', 'Nate'               |
| df                 | 최종적으로 생성된 DataFrame 객체                                 |


## 💡 활용 팁
- df.loc['Jenny'] → Jenny의 정보 추출
- df['age'] → 전체 친구들의 나이만 추출
- df[df['age'] > 25] → 25세 이상 친구 필터링


---

# 소스
```
df.drop(['John', 'Nate'])
```

## 🔍 코드 분석: df.drop(['John', 'Nate'])
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| df               | 인덱스가 'John', 'Jenny', 'Nate'인 DataFrame 객체                 |
| .drop([...])     | 지정한 인덱스(행)를 제거하는 메서드                              |
| ['John', 'Nate'] | 삭제할 행 인덱스 리스트                                          |



## ✅ 예시 출력
```python
       age       job
Jenny   30  developer
```

### ※ drop()은 기본적으로 행(row) 기준으로 작동합니다 (axis=0이 기본값)

## 💡 확장 팁
- df.drop(['job'], axis=1) → 'job' 열 삭제
- df.drop(index=['John', 'Nate']) → 인덱스 명시적으로 삭제
- df.drop(['John', 'Nate'], inplace=True) → 원본 df에서 바로 삭제

## .drop 설명 
.drop() 메서드를 활용한 열 삭제, 조건 기반 삭제, 그리고 inplace 옵션의 차이를 깔끔하게 정리한 내용:

## 🧹 .drop()을 활용한 삭제 방식 정리
### 1️⃣ 열 삭제 (Column Drop)
```python
df.drop(['job'], axis=1)
```
| 구성 요소   | 설명                                                             |
|------------|------------------------------------------------------------------|
| ['job']    | 삭제할 열 이름 리스트                                            |
| axis=1     | 열 기준으로 삭제 (행 기준은 axis=0)                              |
|            | 결과는 'job' 열이 제거된 새로운 DataFrame 반환                   |
이 코드는 'job' 열을 제거하고 나머지 열만 남긴 새로운 DataFrame을 반환.  
원본 df는 그대로 유지되며, inplace=True를 추가하면 원본에서도 삭제됩니다.


### 2️⃣ 행 삭제 (Row Drop)]
```python
df.drop(['John', 'Nate'])
df.drop(['job'], axis=1)
```
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| ['John', 'Nate'] | 삭제할 행 인덱스 리스트                                          |
| axis=0           | 행 기준으로 삭제 (기본값이므로 생략 가능)                        |
|                  | 결과는 'John'과 'Nate' 행이 제거된 새로운 DataFrame 반환         |
이 코드는 'John'과 'Nate'에 해당하는 행을 제거하고 'Jenny'만 남긴 새로운 DataFrame을 반환.  
원본 df는 그대로 유지되며, inplace=True를 추가하면 원본에서도 삭제됩니다.

### 3️⃣ 조건 기반 삭제
```python
df[df['age'] != 30]
```
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| df['age'] != 30  | age 열의 값이 30이 아닌 행에 대해 Boolean 조건 생성              |
|                  | 결과는 True/False로 구성된 시리즈 (Boolean Series) 반환           |
이 조건은 30세가 아닌 친구들만 선택할 때 사용되며, 전체 DataFrame에서 조건을 만족하는 행만 필터링할 수 있음:

### ※ .drop()은 직접 조건을 지정할 수 없기 때문에, 조건 기반 삭제는 Boolean indexing을 활용합니다.

### 4️⃣ inplace=True 옵션의 차이
df.drop(['job'], axis=1, inplace=True)
| 옵션           | 설명                                                             |
|----------------|------------------------------------------------------------------|
| inplace=False  | 원본 df는 유지되고, 삭제된 결과를 **새로운 DataFrame**으로 반환     |
| inplace=True   | 원본 df 자체가 **즉시 변경**되며, 반환값은 `None`     


## ✅ 예시 비교
# inplace=False (기본값)

```python
new_df = df.drop(['job'], axis=1)
print(df)       # 원본 유지
print(new_df)   # 'job' 열이 제거된 결과

# inplace=True
df.drop(['job'], axis=1, inplace=True)
print(df)       # 'job' 열이 제거된 상태
```

## 💡 팁
- inplace=True는 되돌릴 수 없기 때문에 주의해서 사용함.
- 원본을 유지하면서 결과만 보고 싶다면 inplace=False가 안전.


## 🧠 정리 요약표
| 목적         | 코드 예시                          | 결과             |
|--------------|-------------------------------------|------------------|
| 열 삭제      | df.drop(['job'], axis=1)            | 열 제거된 새 df  |
| 행 삭제      | df.drop(['John'], axis=0)           | 행 제거된 새 df  |
| 조건 삭제    | df[df['age'] != 30]                 | 조건 만족 행만   |
| 원본 변경    | df.drop(['job'], axis=1, inplace=True) | df 자체 변경됨 |


---

# 소스

```python
friend_dict_list = [{'name': 'Jone', 'age': 20, 'job': 'student'},
         {'name': 'Jenny', 'age': 30, 'job': 'developer'},
         {'name': 'Nate', 'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list)
df = df.drop(df.index[[0,2]])
```

## ✅ 코드 설명
```python
import pandas as pd

friend_dict_list = [
    {'name': 'Jone', 'age': 20, 'job': 'student'},
    {'name': 'Jenny', 'age': 30, 'job': 'developer'},
    {'name': 'Nate', 'age': 30, 'job': 'teacher'}
]

df = pd.DataFrame(friend_dict_list)
df = df.drop(df.index[[0, 2]])
```


## 📋 출력 결과
```python
    name  age        job
1  Jenny   30  developer
```

## 🔍 구성 요소 분석
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| friend_dict_list | 친구 정보를 담은 딕셔너리 리스트                                 |
| pd.DataFrame(...)| 리스트를 테이블 형태로 변환하는 Pandas 함수                       |
| df.index[[0, 2]] | 삭제할 행의 인덱스 선택 (0번째와 2번째 행)                        |
| df.drop(...)     | 해당 인덱스의 행을 제거한 새로운 DataFrame 반환                   |

이 코드는 'Jone'과 'Nate'에 해당하는 행을 제거하고 'Jenny'만 남긴 DataFrame을 생성.   
인덱스를 직접 지정해서 삭제하는 방식은 특히 위치 기반으로 행을 제거할 때 유용.


## 💡 팁
- df.drop([0, 2])도 가능하지만, df.index[[...]]는 더 명시적인 방식.
- inplace=True를 쓰면 원본 df가 직접 수정됩니다.
- 삭제 후 인덱스를 리셋하려면 df.reset_index(drop=True)를 사용하세요.


----

# 조건 기반 필터링을 통해 특정 행을 제거하는 방식

## 소스
```python
friend_dict_list = [{'name': 'Jone', 'age': 20, 'job': 'student'},
         {'name': 'Jenny', 'age': 30, 'job': 'developer'},
         {'name': 'Nate', 'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list)
df
df = df[df.age != 30]
df
```

 이 코드는 조건 기반 필터링을 통해 특정 행을 제거하는 방식. 
 아래에 전체 흐름을 깔끔하게 정리해:


## ✅ 코드 설명
```python
import pandas as pd

friend_dict_list = [
    {'name': 'Jone', 'age': 20, 'job': 'student'},
    {'name': 'Jenny', 'age': 30, 'job': 'developer'},
    {'name': 'Nate', 'age': 30, 'job': 'teacher'}
]

df = pd.DataFrame(friend_dict_list)
print(df)

df = df[df.age != 30]
print(df)
```


## 📋 출력 결과
```
원본 df
    name  age        job
0   Jone   20     student
1  Jenny   30   developer
2   Nate   30     teacher
```

### 필터링 후 df
```
   name  age      job
0  Jone   20  student

```

## 🔍 핵심 구성 요소
| 구성 요소       | 설명                                                             |
|----------------|------------------------------------------------------------------|
| df.age != 30   | age 값이 30이 아닌 행에 대해 Boolean 조건 생성                   |
| df[...]        | 조건을 만족하는 행만 필터링하여 새로운 DataFrame 생성             |
| df = ...       | 필터링된 결과를 다시 df에 저장하여 기존 df를 덮어씀              |


## 💡 팁
- df[df['job'] != 'teacher'] → 특정 직업 제외
- df[df['name'].str.startswith('J')] → 이름이 'J'로 시작하는 친구만 선택
- df.reset_index(drop=True) → 인덱스 재정렬


---

# DataFrame에서 특정 열을 삭제하는 방식
## 소스
```python
friend_dict_list = [{'name': 'Jone', 'age': 20, 'job': 'student'},
         {'name': 'Jenny', 'age': 30, 'job': 'developer'},
         {'name': 'Nate', 'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list)
df 
df = df.drop('age', axis=1)
df
```

## ✅ 코드 설명
```python
import pandas as pd

friend_dict_list = [
    {'name': 'Jone', 'age': 20, 'job': 'student'},
    {'name': 'Jenny', 'age': 30, 'job': 'developer'},
    {'name': 'Nate', 'age': 30, 'job': 'teacher'}
]
df = pd.DataFrame(friend_dict_list)
print(df)
df = df.drop('age', axis=1)
print(df)
```


## 📋 출력 결과
```
원본 df
    name  age        job
0   Jone   20     student
1  Jenny   30   developer
2   Nate   30     teacher
```

### 열 삭제 후 df
```
    name        job
0   Jone     student
1  Jenny   developer
2   Nate     teacher
```


## 🔍 핵심 구성 요소
| 구성 요소   | 설명                                                             |
|------------|------------------------------------------------------------------|
| 'age'      | 삭제할 열 이름                                                   |
| axis=1     | 열 기준으로 삭제 (행 기준은 axis=0)                              |
| df = ...   | 삭제된 결과를 다시 df에 저장하여 기존 df를 덮어씀               |
| df         | 'age' 열이 제거된 새로운 DataFrame                              |
열 삭제의 핵심 흐름을 간결하게 보여줘요. axis=0은 행 삭제를 의미하니, 열을 삭제할 때는 꼭 axis=1을 지정해야 합니다.

## 💡 팁
- 여러 열 삭제: df.drop(['age', 'job'], axis=1)
- 원본 수정: df.drop('age', axis=1, inplace=True)
- 열 이름 확인: df.columns

---

# 기존 DataFrame에 새로운 열을 추가하는 방식
## 소스

```python

friend_dict_list = [{'name': 'Jone', 'age': 15, 'job': 'student'},
         {'name': 'Jenny', 'age': 30, 'job': 'developer'},
         {'name': 'Nate', 'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(friend_dict_list, columns = ['name', 'age', 'job'])
df
df['salary'] = 0
df
```

## 📋 출력 결과
### 원본 df
```
    name  age        job
0   Jone   15     student
1  Jenny   30   developer
2   Nate   30     teacher
```

### salary 열 추가 후 df
```
    name  age        job  salary
0   Jone   15     student       0
1  Jenny   30   developer       0
2   Nate   30     teacher       0
```

## 🔍 핵심 구성 요소
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| df['salary'] = 0 | 'salary'라는 새 열을 추가하고 모든 값에 0을 할당                  |
| columns=[...]    | DataFrame 생성 시 열 순서를 명시적으로 지정                      |
| df               | 'salary' 열이 포함된 최종 DataFrame                              |

이 방식은 모든 친구에게 기본 급여를 설정하는 예시로, 
이후 조건에 따라 값을 바꾸거나 계산할 수 있음:

```python
df.loc[df['job'] == 'developer', 'salary'] = 5000
```

## 💡 팁
- 특정 값으로 초기화: df['salary'] = 3000
- 조건에 따라 값 설정: df.loc[df['job'] == 'developer', 'salary'] = 5000
- 리스트로 설정: df['salary'] = [1000, 5000, 4000]


---
# 조건에 따라 새로운 열을 생성하는 방식
##  소스
```python
import numpy as np 
df['salary'] = np.where(df['job'] != 'student' , 'yes', 'no') 
df
```

## ✅ 코드 설명
```python
import numpy as np
df['salary'] = np.where(df['job'] != 'student', 'yes', 'no')
```


## 📋 출력 결과
```
    name  age        job salary
0   Jone   15     student    no
1  Jenny   30   developer   yes
2   Nate   30     teacher   yes
```


## 🔍 핵심 구성 요소
| 구성 요소                    | 설명                                                             |
|-----------------------------|------------------------------------------------------------------|
| df['job'] != 'student'      | 'student'이 아닌 직업에 대해 조건 생성 (Boolean Series 반환)     |
| np.where(condition, 'yes', 'no') | 조건이 참이면 'yes', 거짓이면 'no'를 반환하는 NumPy 함수     |
| df['salary'] = ...          | 결과를 'salary' 열에 저장하여 새로운 열 생성                    |
| 'salary'                    | 조건 결과가 담긴 새 열 이름                                     |


## 💡 팁
- 숫자 조건도 가능: np.where(df['age'] >= 30, 5000, 0)
- 여러 조건 조합: np.where((df['age'] > 20) & (df['job'] == 'teacher'), 'yes', 'no')
- 문자열 조건은 .str.contains()와 함께 쓰면 유용

--- 

# 중간고사와 기말고사 점수를 합산해서 총점(total)을 계산

## 소스
```python
friend_dict_list = [{'name': 'John', 'midterm': 95, 'final': 85},
         {'name': 'Jenny', 'midterm': 85, 'final': 80},
         {'name': 'Nate', 'midterm': 10, 'final': 30}]
df = pd.DataFrame(friend_dict_list, columns = ['name', 'midterm', 'final'])
df
df['total'] = df['midterm'] + df['final']
df
```

## ✅ 코드 설명
```python
import pandas as pd

friend_dict_list = [
    {'name': 'John', 'midterm': 95, 'final': 85},
    {'name': 'Jenny', 'midterm': 85, 'final': 80},
    {'name': 'Nate', 'midterm': 10, 'final': 30}
]

df = pd.DataFrame(friend_dict_list, columns=['name', 'midterm', 'final'])
df['total'] = df['midterm'] + df['final']
print(df)
```


## 📋 출력 결과
```
    name  midterm  final  total
0   John       95     85    180
1  Jenny       85     80    165
2   Nate       10     30     40
```


## 🔍 핵심 구성 요소
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| df['midterm'] + df['final'] | 각 행의 중간고사와 기말고사 점수를 합산                         |
| df['total'] = ...      | 합산 결과를 'total' 열에 저장하여 새로운 열 생성                  |
| columns=[...]          | DataFrame 생성 시 열 순서를 명시적으로 지정                      |

df['average'] = (df['midterm'] + df['final']) / 2

## 💡 팁
- 평균 점수: df['average'] = (df['midterm'] + df['final']) / 2
- 조건 필터링: df[df['total'] >= 100]
- 정렬: df.sort_values(by='total', ascending=False)


---

# 학생들의 평균 점수를 기반으로 등급을 부여하고, 그 등급을 바탕으로 합격 여부(Pass/Fail)를 판단하는 로직


## 소스
```python
grades = []

for row in df['average']:
    if row >= 90:
        grades.append('A')
    elif row >= 80:
        grades.append('B')
    elif row >= 70:
        grades.append('C')
    else:
        grades.append('F')
        
df['grade'] = grades
df

def pass_or_fail(row):
    print(row)
    if row != "F":
        return 'Pass'
    else:
        return 'Fail'

df.grade = df.grade.apply(pass_or_fail)
df
```

## ✅ 코드 흐름 설명
### 1️⃣ 등급 계산 (grade 열 생성)
```python
grades = []

for row in df['average']:
    if row >= 90:
        grades.append('A')
    elif row >= 80:
        grades.append('B')
    elif row >= 70:
        grades.append('C')
    else:
        grades.append('F')

df['grade'] = grades
```
| 조건 | 결과 | 
| 평균 >= 90 | A | 
| 평균 >= 80 | B | 
| 평균 >= 70 | C | 
| 그 외 | F | 

## 2️⃣ 합격 여부 판단 (grade 기준)
```python
def pass_or_fail(row):
    print(row)
    if row != "F":
        return 'Pass'
    else:
        return 'Fail'

df.grade = df.grade.apply(pass_or_fail)
```
# 참고
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| df.grade               | 'grade' 열의 각 값을 대상으로 처리                               |
| .apply(pass_or_fail)   | 각 값에 대해 pass_or_fail 함수를 적용하여 결과 반환              |
| df.grade = ...         | 처리된 결과를 다시 'grade' 열에 저장                             |


### ※ print(row)는 각 등급을 출력하며 디버깅용으로 사용됩니다.

## 📋 최종 결과 예시
| name  | average | grade | result |
|-------|---------|-------|--------|
| John  | 90.0    | A     | Pass   |
| Jenny | 82.5    | B     | Pass   |
| Nate  | 20.0    | F     | Fail   |

---
# DataFrame을 생성하는 방식

## 소스 코드
```python
date_list = [{'yyyy-mm-dd': '2000-06-27'},
         {'yyyy-mm-dd': '2002-09-24'},
         {'yyyy-mm-dd': '2005-12-20'}]
df = pd.DataFrame(date_list, columns = ['yyyy-mm-dd'])
df
```

## ✅ 코드 설명
```python
import pandas as pd

date_list = [
    {'yyyy-mm-dd': '2000-06-27'},
    {'yyyy-mm-dd': '2002-09-24'},
    {'yyyy-mm-dd': '2005-12-20'}
]

df = pd.DataFrame(date_list, columns=['yyyy-mm-dd'])
print(df)
```


## 📋 출력 결과
```
  yyyy-mm-dd
0  2000-06-27
1  2002-09-24
2  2005-12-20
```

## 핵심 구성 요소
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| date_list              | 날짜 정보를 담은 딕셔너리 리스트                                 |
| columns=['yyyy-mm-dd']| DataFrame 생성 시 열 이름을 명시적으로 지정                      |
| pd.DataFrame(...)      | 리스트를 테이블 형태로 변환하는 Pandas 함수                       |

## 💡 확장 팁
- 날짜 형식 변환: df['yyyy-mm-dd'] = pd.to_datetime(df['yyyy-mm-dd'])
- 연도 추출: df['year'] = df['yyyy-mm-dd'].dt.year
- 월 추출: df['month'] = df['yyyy-mm-dd'].dt.month
- 요일 추출: df['weekday'] = df['yyyy-mm-dd'].dt.day_name()


---

# 문자열로 된 날짜에서 연도만 추출해서 새로운 열 'year'에 저장하는 방식


## 소스 
```python
def extract_year(row):
    return row.split('-')[0]
df['year'] = df['yyyy-mm-dd'].apply(extract_year)

df

```
## ✅ 코드 설명
```python
def extract_year(row):
    return row.split('-')[0]

df['year'] = df['yyyy-mm-dd'].apply(extract_year)
```

## 📋 출력 결과 예시
```
  yyyy-mm-dd  year
0  2000-06-27  2000
1  2002-09-24  2002
2  2005-12-20  2005
```


## 🔍 핵심 구성 요소
| 구성 요소             | 설명                                                             |
|----------------------|------------------------------------------------------------------|
| row.split('-')[0]    | 문자열을 '-' 기준으로 나눈 뒤 첫 번째 요소(연도) 추출             |
| extract_year(row)    | 한 행의 날짜 문자열에서 연도만 반환하는 사용자 정의 함수          |
| .apply(extract_year) | 각 행에 대해 함수를 적용하여 결과 반환                           |
| df['year'] = ...     | 추출된 연도를 'year' 열에 저장하여 새로운 열 생성                |
| 'year'               | 연도 정보가 담긴 새 열 이름                                      |


## 💡 팁
- 날짜 형식으로 변환 후 연도 추출:
df['yyyy-mm-dd'] = pd.to_datetime(df['yyyy-mm-dd'])
df['year'] = df['yyyy-mm-dd'].dt.year
- 월, 일, 요일도 추출 가능:
df['month'] = df['yyyy-mm-dd'].dt.month
df['weekday'] = df['yyyy-mm-dd'].dt.day_name()

---

# 연도 정보를 활용해 나이(age)를 계산하는 방식

## 소스 코드
```python
def extract_year(year, current_year):
    return current_year - int(year)

df['age'] = df['year'].apply(extract_year, current_year=2018)
df
```

## ✅ 코드 설명
```python
def extract_year(year, current_year):
    return current_year - int(year)

df['age'] = df['year'].apply(extract_year, current_year=2018)
```

## 📋 출력 결과 예시
```
  yyyy-mm-dd  year  age
0  2000-06-27  2000   18
1  2002-09-24  2002   16
2  2005-12-20  2005   13
```


## 🔍 핵심 구성 요소
| 구성 요소                      | 설명                                                             |
|-------------------------------|------------------------------------------------------------------|
| extract_year(year, current_year) | 현재 연도에서 출생 연도를 빼서 나이를 계산하는 사용자 정의 함수 |
| int(year)                     | 문자열 형태의 연도를 정수형으로 변환                            |
| .apply(..., current_year=2018)| 각 행에 대해 함수 적용, 현재 연도는 2018로 고정                 |
| df['age'] = ...               | 계산된 나이를 'age' 열에 저장하여 새로운 열 생성                |
| 'age'                         | 나이 정보가 담긴 새 열 이름                                     |


## 💡 팁
- 현재 연도를 자동으로 계산하려면:
from datetime import datetime
current_year = datetime.now().year
df['age'] = df['year'].apply(lambda y: current_year - int(y))
- 생일 기준으로 정확한 나이 계산도 가능해요:
df['yyyy-mm-dd'] = pd.to_datetime(df['yyyy-mm-dd'])
df['age'] = datetime.now().year - df['yyyy-mm-dd'].dt.year



---

# 여러개의 인자 전달
## 소스

```python
def get_introduce(age, prefix, suffix):
    return prefix + str(age) + suffix

df['introduce'] = df['age'].apply(get_introduce, prefix="I am ", suffix=" years old")
df
```

## ✅ 코드 설명
```python
def get_introduce(age, prefix, suffix):
    return prefix + str(age) + suffix

df['introduce'] = df['age'].apply(get_introduce, prefix="I am ", suffix=" years old")
```

## 📋 출력 결과 예시
```
  yyyy-mm-dd  year  age           introduce
0  2000-06-27  2000   18  I am 18 years old
1  2002-09-24  2002   16  I am 16 years old
2  2005-12-20  2005   13  I am 13 years old
```


## 🔍 핵심 구성 요소
| 구성 요소                          | 설명                                                             |
|-----------------------------------|------------------------------------------------------------------|
| get_introduce(age, prefix, suffix)| 나이를 받아 소개 문장을 생성하는 사용자 정의 함수               |
| str(age)                          | 숫자형 나이를 문자열로 변환                                      |
| .apply(..., prefix=..., suffix=...)| 각 행에 대해 함수 적용하며 접두사와 접미사를 함께 전달         |
| df['introduce'] = ...             | 생성된 소개 문장을 'introduce' 열에 저장                         |
| 'introduce'                       | 소개 문장이 담긴 새 열 이름                                      |


## 💡 확장 팁
- 이름 포함:
def full_intro(row):
    return f"My name is {row['name']} and I am {row['age']} years old"
df['introduce'] = df.apply(full_intro, axis=1)
- 다국어 지원도 가능: "저는 XX살입니다" 또는 "Ich bin XX Jahre alt" 등

---
# 각 행(row)을 받아서 'year'와 'age' 정보를 활용해 자기소개 문장을 생성하는 방식


## 소스
```python
def get_introduce2(row):
    return "I was born in "+str(row.year)+" my age is "+str(row.age)
df.introduce = df.apply(get_introduce2, axis=1)
df
```

## ✅ 코드 설명

```python
def get_introduce2(row):
    return "I was born in " + str(row.year) + " my age is " + str(row.age)

df.introduce = df.apply(get_introduce2, axis=1)
```


## 📋 출력 결과 예시
```
  yyyy-mm-dd  year  age           introduce
0  2000-06-27  2000   18  I was born in 2000 my age is 18
1  2002-09-24  2002   16  I was born in 2002 my age is 16
2  2005-12-20  2005   13  I was born in 2005 my age is 13
```

## 🔍 핵심 구성 요소
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| get_introduce2(row)    | 한 행(row)의 정보를 받아 소개 문장을 생성하는 사용자 정의 함수     |
| row.year, row.age      | 해당 행에서 연도와 나이 정보를 추출                              |
| df.apply(..., axis=1)  | 각 행 전체를 함수에 전달하여 처리 (axis=1은 행 단위 적용 의미)    |
| df.introduce = ...     | 생성된 소개 문장을 'introduce' 열에 저장                          |
| 'introduce'            | 소개 문장이 담긴 새 열 이름                                      |


## 💡 확장 팁
- 이름 포함:
def get_intro(row):
    return f"My name is {row['name']}, born in {row['year']}, and I am {row['age']} years old."

---

## 소스

``` python
def extract_year(row):
    return row.split('-')[0]

date_list = [{'yyyy-mm-dd': '2000-06-27'},
         {'yyyy-mm-dd': '2002-09-24'},
         {'yyyy-mm-dd': '2005-12-20'}]
df = pd.DataFrame(date_list, columns = ['yyyy-mm-dd'])
df
df['year'] = df['yyyy-mm-dd'].map(extract_year)
df
```


## ✅ 코드 설명
```python
def extract_year(row):
    return row.split('-')[0]

df['year'] = df['yyyy-mm-dd'].map(extract_year)
```


## 📋 출력 결과 예시
```
  yyyy-mm-dd  year
0  2000-06-27  2000
1  2002-09-24  2002
2  2005-12-20  2005
```


## 🔍 핵심 구성 요소
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| row.split('-')[0]      | 문자열을 '-' 기준으로 나눈 뒤 첫 번째 요소(연도) 추출             |
| extract_year(row)      | 한 셀의 날짜 문자열에서 연도만 반환하는 사용자 정의 함수          |
| .map(extract_year)     | Series의 각 값에 대해 함수를 적용하여 결과 반환                   |
| df['year'] = ...       | 추출된 연도를 'year' 열에 저장하여 새로운 열 생성                |
| 'year'                 | 연도 정보가 담긴 새 열 이름                                      |



## 💡 .map() vs .apply() 차이
| 메서드     | 대상     | 사용 예시                  |
|------------|----------|----------------------------|
| .map()     | Series   | df['col'].map(func)        |
| .apply()   | Series/행/열 | df.apply(func, axis=1)     |


## 🔍 차이점 요약
- .map()은 Series 전용으로, 한 열의 각 값에 함수를 적용할 때 사용해요.
- .apply()는 DataFrame 전체 또는 행/열 단위로 처리할 수 있어서 더 유연해요.
예를 들어:
```python
# .map() → 단일 열 처리
df['year'] = df['yyyy-mm-dd'].map(lambda x: x.split('-')[0])

# .apply() → 여러 열 조합 처리
df['intro'] = df.apply(lambda row: f"I was born in {row['year']} and I am {row['age']} years old", axis=1)
```
---

# 이 코드는 'job' 열의 문자열 값을 숫자로 매핑(mapping) 하는 방식

##  소스
```python
job_list = [{'age': 20, 'job': 'student'},
         {'age': 30, 'job': 'developer'},
         {'age': 30, 'job': 'teacher'}]
df = pd.DataFrame(job_list)
df

df.job = df.job.map({"student":1,"developer":2,"teacher":3})
df
```
## ✅ 코드 설명
```python
job_list = [
    {'age': 20, 'job': 'student'},
    {'age': 30, 'job': 'developer'},
    {'age': 30, 'job': 'teacher'}
]

df = pd.DataFrame(job_list)
df.job = df.job.map({"student": 1, "developer": 2, "teacher": 3})
print(df)
```


## 📋 출력 결과 예시
```
   age  job
0   20     1
1   30     2
2   30     3
```


## 🔍 핵심 구성 요소
| 구성 요소         | 설명                                                             |
|------------------|------------------------------------------------------------------|
| df.job           | 'job' 열의 Series 객체                                           |
| .map({...})      | 각 값에 대해 지정된 딕셔너리로 매핑                              |
| "student": 1     | 문자열 'student'을 숫자 1로 변환하는 매핑 규칙                   |
| df.job = ...     | 매핑된 결과를 다시 'job' 열에 저장                                |
| 'job'            | 직업 정보를 담고 있는 열 이름                                     |


## 💡 확장 팁
- 매핑 딕셔너리는 외부에서 불러올 수도 있어요 (예: JSON, DB)
- .replace()도 유사하게 작동하지만, 일부 값만 바꿀 때 더 유용해요
- 역매핑도 가능: {1: "student", 2: "developer", 3: "teacher"}
----

## 소스
```python
x_y = [{'x': 5.5, 'y': -5.6},
         {'x': -5.2, 'y': 5.5},
         {'x': -1.6, 'y': -4.5}]
df = pd.DataFrame(x_y)
df

df = df.apply(np.around)
df

```


이 코드는 x와 y 값들을 반올림해서 새로운 DataFrame으로 만드는 방식.   
아래에 전체 흐름을 깔끔하게 정리:

## ✅ 코드 설명
```python
import pandas as pd
import numpy as np

x_y = [
    {'x': 5.5, 'y': -5.6},
    {'x': -5.2, 'y': 5.5},
    {'x': -1.6, 'y': -4.5}
]

df = pd.DataFrame(x_y)
df = df.apply(np.around)
print(df)
```


## 📋 출력 결과 예시
```
     x    y
0  6.0 -6.0
1 -5.0  6.0
2 -2.0 -4.0
```
## 🔍 핵심 구성 요소
| 구성 요소        | 설명                                                             |
|-----------------|------------------------------------------------------------------|
| np.around       | NumPy의 반올림 함수 (소수점 첫째 자리 기준으로 반올림)            |
| df.apply(...)   | DataFrame의 각 열에 대해 함수 적용 (기본적으로 axis=0)           |
| axis=0          | 열 단위로 함수 적용 (행마다 각 열에 대해 처리)                   |
| df = ...        | 반올림된 결과를 다시 df에 저장                                   |
| df              | 반올림된 값을 담고 있는 최종 DataFrame 객체                      |


## 💡 확장 팁
- 소수점 자릿수 지정: np.around(df, decimals=1)
- 절댓값 처리: df.apply(np.abs)
- 사용자 정의 반올림: df.applymap(lambda x: round(x, 1))

----

# 두 개의 DataFrame을 하나로 합치는 방식이에요. 

## 소스

```python
friend_dict_list = [{'name': 'John', 'midterm': 95, 'final': 85},
         {'name': 'Jenny', 'midterm': 85, 'final': 80},
         {'name': 'Nate', 'midterm': 10, 'final': 30}]
df = pd.DataFrame(friend_dict_list, columns = ['name', 'midterm', 'final'])
df
df2 = pd.DataFrame([['Ben', 50,50]], columns = ['name', 'midterm', 'final'])


df2.head()


df_combined = pd.concat([df, df2], ignore_index=True)
print(df_combined)

```


이 코드는 두 개의 DataFrame을 하나로 합치는 방식. 
아래에 전체 흐름을 깔끔하게 정리:

## ✅ 코드 설명
```python
import pandas as pd

# 첫 번째 친구 목록
friend_dict_list = [
    {'name': 'John', 'midterm': 95, 'final': 85},
    {'name': 'Jenny', 'midterm': 85, 'final': 80},
    {'name': 'Nate', 'midterm': 10, 'final': 30}
]
df = pd.DataFrame(friend_dict_list, columns=['name', 'midterm', 'final'])

# 두 번째 친구 Ben 추가
df2 = pd.DataFrame([['Ben', 50, 50]], columns=['name', 'midterm', 'final'])

# 두 DataFrame 병합
df_combined = pd.concat([df, df2], ignore_index=True)
print(df_combined)
```


## 📋 출력 결과 예시
```
    name  midterm  final
0   John       95     85
1  Jenny       85     80
2   Nate       10     30
3    Ben       50     50
```


## 🔍 핵심 구성 요소
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| pd.DataFrame(...)  | 리스트 또는 딕셔너리를 기반으로 DataFrame 생성                    |
| df2.head()         | df2의 상위 5개 행을 출력하여 데이터 확인                         |
| pd.concat([...])   | 여러 DataFrame을 하나로 병합                                     |
| ignore_index=True  | 기존 인덱스를 무시하고 새 인덱스를 자동 생성                     |
| df_combined        | 병합된 결과를 담은 최종 DataFrame                                |
이 구조는 여러 데이터셋을 하나로 합칠 때 아주 유용해요. 이후 정렬, 그룹화, 또는 통계 분석까지 확장하기도 좋아요!

## 💡 확장 팁
- 열 순서 맞추기: df2 = df2[df.columns]
- 새로운 열 추가: df_combined['average'] = (df_combined['midterm'] + df_combined['final']) / 2


-----

이 코드는 학생 데이터를 전공()과 성별() 기준으로 그룹화하고, 각 그룹의 인원 수를 계산하는 방식. 
아래에 전체 흐름을 깔끔하게 정리

## 소스
```python
student_list = [{'name': 'John', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Nate', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Abraham', 'major': "Physics", 'sex': "male"},
                {'name': 'Brian', 'major': "Psychology", 'sex': "male"},
                {'name': 'Janny', 'major': "Economics", 'sex': "female"},
                {'name': 'Yuna', 'major': "Economics", 'sex': "female"},
                {'name': 'Jeniffer', 'major': "Computer Science", 'sex': "female"},
                {'name': 'Edward', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Zara', 'major': "Psychology", 'sex': "female"},
                {'name': 'Wendy', 'major': "Economics", 'sex': "female"},
                {'name': 'Sera', 'major': "Psychology", 'sex': "female"}
         ]
df = pd.DataFrame(student_list, columns = ['name', 'major', 'sex'])
df

groupby_major = df.groupby('major')


groupby_major.groups


for name, group in groupby_major:
    print(name + ": " + str(len(group)))
    print(group)
    print()


df_major_cnt = pd.DataFrame({'count' : groupby_major.size()}).reset_index()
df_major_cnt

groupby_sex = df.groupby('sex')

for name, group in groupby_sex:
    print(name + ": " + str(len(group)))
    print(group)
    print()


df_sex_cnt = pd.DataFrame({'count' : groupby_sex.size()}).reset_index()
df_sex_cnt
```

## ✅ 전체 코드 흐름 요약

### 1. 📋 데이터프레임 생성
```python
df = pd.DataFrame(student_list, columns=['name', 'major', 'sex'])
```

- 학생 이름, 전공, 성별 정보를 담은 테이블 생성

### 2. 🎓 전공별 그룹화 및 출력
```python
groupby_major = df.groupby('major')
groupby_major.groups
```

- groupby('major')로 전공 기준 그룹화
- .groups는 각 전공에 속한 인덱스를 보여줌

```python
for name, group in groupby_major:
    print(name + ": " + str(len(group)))
    print(group)
```

- 각 전공별 인원 수와 해당 학생 목록 출력

### 3. 📊 전공별 인원 수 집계
```python
df_major_cnt = pd.DataFrame({'count': groupby_major.size()}).reset_index()
```

- groupby.size()로 각 전공별 인원 수 계산
- reset_index()로 깔끔한 테이블 형태로 변환

#### 📌 출력 예시:
```
           major  count
0  Computer Science      4
1        Economics      3
2          Physics      1
3       Psychology      3
```


### 4. 🚻 성별 그룹화 및 출력
```python
groupby_sex = df.groupby('sex')


- groupby('sex')로 성별 기준 그룹화
for name, group in groupby_sex:
    print(name + ": " + str(len(group)))
    print(group)
```

- 남성과 여성 그룹별 인원 수 및 목록 출력

### 5. 📊 성별 인원 수 집계
```python
df_sex_cnt = pd.DataFrame({'count': groupby_sex.size()}).reset_index()
```

#### 📌 출력 예시:
```
     sex  count
0  female      5
1    male      6
```


## 🔍 핵심 구성 요소 요약
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| groupby('major')       | 'major' 열 기준으로 그룹화                                       |
| groupby('sex')         | 'sex' 열 기준으로 그룹화                                         |
| .size()                | 각 그룹의 원소 수(행 개수)를 계산                                |
| .reset_index()         | 그룹화 결과를 일반 DataFrame 형태로 변환                         |
| for name, group in ... | 각 그룹의 이름과 해당 데이터 그룹을 순회하며 출력               |
이 구조는 데이터 분석에서 그룹별 통계나 분포를 파악할 때 아주 유용해요. 이후 mean(), sum(), count() 같은 집계 함수와 함께 쓰면 더 강력한 분석도 가능하죠!



--- 

학생 데이터를 전공과 성별 기준으로 그룹화하고 집계하는 과정을 단계별로 체계적으로 정리. 
아래는 각 단계의 설명과 핵심 코드 흐름:

### 🧩 1단계: 데이터프레임 생성
```python
student_list = [
    {'name': 'John', 'major': "Computer Science", 'sex': "male"},
    {'name': 'Nate', 'major': "Computer Science", 'sex': "male"},
    ...
]
df = pd.DataFrame(student_list, columns=['name', 'major', 'sex'])
```

- 학생 이름, 전공, 성별 정보를 담은 테이블 생성

### 🧩 2단계: 전공 기준 그룹화
```python
groupby_major = df.groupby('major')
```

- 'major' 열을 기준으로 그룹화
- groupby_major.groups로 각 전공에 속한 인덱스 확인 가능

### 🧩 3단계: 전공별 그룹 출력
```python
for name, group in groupby_major:
    print(name + ": " + str(len(group)))
    print(group)
    print()
```

- 각 전공별 인원 수와 해당 학생 목록 출력

### 🧩 4단계: 전공별 인원 수 집계
```python
df_major_cnt = pd.DataFrame({'count': groupby_major.size()}).reset_index()
```

- .size()로 각 그룹의 행 개수 계산
- .reset_index()로 결과를 일반 테이블 형태로 변환
#### 📌 예시 출력:
```
           major  count
0  Computer Science      4
1        Economics      3
2          Physics      1
3       Psychology      3
```


### 🧩 5단계: 성별 기준 그룹화
```python
groupby_sex = df.groupby('sex')
```

- 'sex' 열을 기준으로 그룹화

### 🧩 6단계: 성별 그룹 출력
```python
for name, group in groupby_sex:
    print(name + ": " + str(len(group)))
    print(group)
    print()
```

- 남성과 여성 그룹별 인원 수 및 목록 출력

### 🧩 7단계: 성별 인원 수 집계
```python
df_sex_cnt = pd.DataFrame({'count': groupby_sex.size()}).reset_index()
```

####📌 예시 출력:
```
     sex  count
0  female      5
1    male      6

```

## 🧠 요약: 핵심 메서드 정리
| 메서드/구문               | 역할 및 설명                                                  |
|--------------------------|---------------------------------------------------------------|
| groupby('major')         | 'major' 열 기준으로 학생들을 전공별로 그룹화                  |
| groupby('sex')           | 'sex' 열 기준으로 학생들을 성별로 그룹화                      |
| .size()                  | 각 그룹의 행 개수(학생 수)를 계산                             |
| .reset_index()           | 그룹화 결과를 일반 DataFrame 형태로 변환                      |
| for name, group in ...   | 각 그룹의 이름(name)과 해당 데이터(group)를 순회하며 출력     |


이 표는 그룹화 → 집계 → 출력까지의 흐름을 한눈에 보여줌.   
이후 .mean(), .sum(), .count() 같은 집계 함수나 pivot_table로 교차 분석도 쉽게 확장

----

# 중복 데이터 삭제하기

## 소스
```python
student_list = [{'name': 'John', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Nate', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Abraham', 'major': "Physics", 'sex': "male"},
                {'name': 'Brian', 'major': "Psychology", 'sex': "male"},
                {'name': 'Janny', 'major': "Economics", 'sex': "female"},
                {'name': 'Yuna', 'major': "Economics", 'sex': "female"},
                {'name': 'Jeniffer', 'major': "Computer Science", 'sex': "female"},
                {'name': 'Edward', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Zara', 'major': "Psychology", 'sex': "female"},
                {'name': 'Wendy', 'major': "Economics", 'sex': "female"},
                {'name': 'Sera', 'major': "Psychology", 'sex': "female"},
                {'name': 'John', 'major': "Computer Science", 'sex': "male"},
         ]
df = pd.DataFrame(student_list, columns = ['name', 'major', 'sex'])
df
df.duplicated()
df = df.drop_duplicates()
df 

```

## 🧩 2단계: 중복 여부 확인
```python
df.duplicated()
```

- 각 행이 이전 행과 완전히 동일한지를 Boolean 값으로 반환
### - 예시 결과:
```
0    False
1    False
...

11    True   ← 마지막 John은 중복
```


## 🧩 3단계: 중복 제거

```python
df = df.drop_duplicates()
```

- 중복된 행을 제거하고 고유한 학생 정보만 유지
- 기본적으로 전체 열 기준으로 중복 판단

### 📋 최종 결과 예시
```
       name             major     sex
0      John  Computer Science    male
1      Nate  Computer Science    male
2   Abraham           Physics    male
3     Brian        Psychology    male
4     Janny         Economics  female
5      Yuna         Economics  female
6  Jeniffer  Computer Science  female
7    Edward  Computer Science    male
8      Zara        Psychology  female
9     Wendy         Economics  female
10     Sera        Psychology  female
```


## 🔍 핵심 메서드 요약
| 메서드                  | 설명                                                             |
|-------------------------|------------------------------------------------------------------|
| df.duplicated()         | 각 행이 이전 행과 완전히 동일한지 여부를 Boolean 값으로 반환     |
| df.drop_duplicates()    | 중복된 행을 제거하고 고유한 데이터만 유지                        |


---

이 코드는 'name' 기준으로 중복된 학생 데이터를 식별하고, 마지막 항목을 남기고 나머지를 제거하는 흐름

#  소스 
```python
student_list = [{'name': 'John', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Nate', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Abraham', 'major': "Physics", 'sex': "male"},
                {'name': 'Brian', 'major': "Psychology", 'sex': "male"},
                {'name': 'Janny', 'major': "Economics", 'sex': "female"},
                {'name': 'Yuna', 'major': "Economics", 'sex': "female"},
                {'name': 'Jeniffer', 'major': "Computer Science", 'sex': "female"},
                {'name': 'Edward', 'major': "Computer Science", 'sex': "male"},
                {'name': 'Zara', 'major': "Psychology", 'sex': "female"},
                {'name': 'Wendy', 'major': "Economics", 'sex': "female"},
                {'name': 'Nate', 'major': None, 'sex': "male"},
                {'name': 'John', 'major': "Computer Science", 'sex': None},
         ]
df = pd.DataFrame(student_list, columns = ['name', 'major', 'sex'])
df

df.duplicated(['name'])


df.drop_duplicates(['name'], keep='last')
```

## 🧩 1단계: 데이터프레임 생성
```python
df = pd.DataFrame(student_list, columns=['name', 'major', 'sex'])
```

- 학생 이름, 전공, 성별 정보를 담은 테이블 생성
- 'John', 'Nate' 이름이 중복으로 등장함

##🧩 2단계: 특정 열 기준 중복 여부 확인
```python
df.duplicated(['name'])
```

- 'name' 열 기준으로 중복 여부를 Boolean 값으로 반환
### - 예시 결과:
```
0    False
1    False
...


10    True   ← Nate 중복 11    True   ← John 중복
```


## 🧩 3단계: 중복 제거 (`keep='last'`)

```python
df.drop_duplicates(['name'], keep='last')
```

- 'name' 기준으로 중복된 행 제거
- 마지막 등장한 항목만 유지, 앞선 중복은 제거됨

### 📌 결과 예시:
```
       name             major     sex
2   Abraham           Physics    male
3     Brian        Psychology    male
4     Janny         Economics  female
5      Yuna         Economics  female
6  Jeniffer  Computer Science  female
7    Edward  Computer Science    male
9     Wendy         Economics  female
10     Nate              None    male
11     John  Computer Science    None
```


## 🔍 핵심 메서드 요약
| 구성 요소                      | 설명                                                             |
|-------------------------------|------------------------------------------------------------------|
| df.duplicated(['name'])       | 'name' 열 기준으로 중복 여부를 Boolean 값으로 반환               |
| df.drop_duplicates(['name'])  | 'name' 열 기준으로 중복된 행 제거                                |
| keep='last'                   | 중복 중 마지막 항목을 유지하고 앞선 항목은 제거                  |

---


## 소스
```python
school_id_list = [{'name': 'John', 'job': "teacher", 'age': 40},
                {'name': 'Nate', 'job': "teacher", 'age': 35},
                {'name': 'Yuna', 'job': "teacher", 'age': 37},
                {'name': 'Abraham', 'job': "student", 'age': 10},
                {'name': 'Brian', 'job': "student", 'age': 12},
                {'name': 'Janny', 'job': "student", 'age': 11},
                {'name': 'Nate', 'job': "teacher", 'age': None},
                {'name': 'John', 'job': "student", 'age': None}
         ]
df = pd.DataFrame(school_id_list, columns = ['name', 'job', 'age'])
df

df.info()
df.isna()

df.isnull()

tmp = df
tmp["age"] = tmp["age"].fillna(0)
tmp

# fill missing age with median age for each group (teacher, student)
df["age"] = df["age"].fillna(df.groupby("job")["age"].transform("median"))

print(df.columns)

df

```

결측값 처리와 그룹별 통계 기반 보정까지 구성. 
아래에 전체 흐름을 단계별로 체계적으로 정리해:

## 🧩 1단계: 데이터프레임 생성
```python
df = pd.DataFrame(school_id_list, columns=['name', 'job', 'age'])
```

- 이름, 직업(teacher/student), 나이 정보를 담은 테이블 생성
- 일부 age 값이 None으로 결측됨

## 🧩 2단계: 결측값 확인
```python
df.info()
df.isna()
df.isnull()
```

- info()로 전체 열의 타입과 결측 개수 확인
- isna() / isnull()은 결측값 위치를 Boolean으로 반환

## 🧩 3단계: 임시 대체 (0으로 채우기)
```python
tmp = df
tmp["age"] = tmp["age"].fillna(0)
```

- fillna(0)으로 결측값을 0으로 채움
- 단순 대체이므로 분석용으로는 부적절할 수 있음

## 🧩 4단계: 그룹별 중앙값으로 결측값 보정
```python
df["age"] = df["age"].fillna(df.groupby("job")["age"].transform("median"))
```

- groupby("job")으로 직업별 그룹화
- 각 그룹의 age 중앙값(median)을 계산
- transform("median")은 원래 인덱스에 맞춰 반환
- 결측값을 해당 그룹의 중앙값으로 채움
### 📌 예시:
- teacher 그룹: [40, 35, 37] → median = 37
- student 그룹: [10, 12, 11] → median = 11

##🧩 5단계: 결과 확인
```python
print(df.columns)
df
```

- age 열의 결측값이 모두 채워진 상태로 출력됨

## 🔍 핵심 메서드 요약
| 구성 요소                                 | 설명                                                             |
|------------------------------------------|------------------------------------------------------------------|
| df.isna() / df.isnull()                  | 결측값 여부를 Boolean 값으로 반환 (True: 결측, False: 정상)     |
| fillna(0)                                 | 결측값을 0으로 채움 (단순 대체 방식)                             |
| groupby("job")["age"].transform("median")| 직업별로 age의 중앙값을 계산하고 각 행에 맞춰 반환               |
| fillna(...)                               | 결측값을 지정된 값 또는 계산된 값으로 채움                       |
이 흐름은 데이터 정제에서 아주 중요. 특히 groupby + transform 조합은 그룹별 통계 기반 보정에 매우 강력!


---- 

# 'job' 열의 고유 직업 목록과 직업별 빈도수를 확인하는 흐름


## 소스
```python

job_list = [{'name': 'John', 'job': "teacher"},
                {'name': 'Nate', 'job': "teacher"},
                {'name': 'Fred', 'job': "teacher"},
                {'name': 'Abraham', 'job': "student"},
                {'name': 'Brian', 'job': "student"},
                {'name': 'Janny', 'job': "developer"},
                {'name': 'Nate', 'job': "teacher"},
                {'name': 'Obrian', 'job': "dentist"},
                {'name': 'Yuna', 'job': "teacher"},
                {'name': 'Rob', 'job': "lawyer"},
                {'name': 'Brian', 'job': "student"},
                {'name': 'Matt', 'job': "student"},
                {'name': 'Wendy', 'job': "banker"},
                {'name': 'Edward', 'job': "teacher"},
                {'name': 'Ian', 'job': "teacher"},
                {'name': 'Chris', 'job': "banker"},
                {'name': 'Philip', 'job': "lawyer"},
                {'name': 'Janny', 'job': "basketball player"},
                {'name': 'Gwen', 'job': "teacher"},
                {'name': 'Jessy', 'job': "student"}
         ]
df = pd.DataFrame(job_list, columns = ['name', 'job'])


print( df.job.unique() )


df.job.value_counts()

```

## 🧩 1단계: 데이터프레임 생성
```python
df = pd.DataFrame(job_list, columns=['name', 'job'])
```

- 이름과 직업 정보를 담은 테이블 생성

## 🧩 2단계: 고유 직업 목록 확인
```python
df.job.unique()
```

- 'job' 열에 등장한 중복 없는 직업 리스트를 반환

### - 예시 결과:
```python
array(['teacher', 'student', 'developer', 'dentist', 'lawyer',
       'banker', 'basketball player'], dtype=object)

```

### 🧩 3단계: 직업별 빈도수 계산
```python
df.job.value_counts()
```

- 각 직업이 몇 번 등장했는지 세어줌
### - 예시 결과:
```
teacher              7
student              5
banker               2
lawyer               2
developer            1
dentist              1
basketball player    1
Name: job, dtype: int64
```


## 🔍 핵심 메서드 요약
| 구성 요소                 | 설명                                                             |
|--------------------------|------------------------------------------------------------------|
| df.job.unique()          | 'job' 열에서 중복 없이 고유한 직업 목록을 배열 형태로 반환        |
| df.job.value_counts()    | 'job' 열에서 각 직업이 몇 번 등장했는지 빈도수로 계산             |

이 두 메서드는 범주형 데이터의 분포를 파악할 때 아주 유용.  
이후 상위 직업 필터링, 비율 계산, 또는 시각화(barplot, pie chart)로 확장

---


normalize=True 옵션은 value_counts() 메서드에서 빈도수를 비율(%)로 변환할 때 사용. \
아래에 단계별로 체계적으로 정리:

## 🧩 1단계: 기본 빈도수 계산
```python
df['job'].value_counts()

```

- 각 직업이 몇 번 등장했는지 정수형 빈도수로 반환
### - 예시:
```
teacher              7
student              5
banker               2
...

```

## 🧩 2단계: 비율 분석 (normalize=True)
```python
df['job'].value_counts(normalize=True)
```

- 각 직업의 전체 대비 비율을 계산
- 반환값은 소수점 형태의 비율 (합계는 1.0)
### - 예시:
```
teacher              0.35
student              0.25
banker               0.10
...
```


### 🧩 3단계: 퍼센트로 보기 (선택적 변환)
```
df['job'].value_counts(normalize=True) * 100

```
- 비율을 **퍼센트(%)**로 변환
### - 예시:
```
teacher              35.0
student              25.0
banker               10.0
...
```


## 🔍 핵심 옵션 요약
| 구성 요소                             | 설명                                                             |
|--------------------------------------|------------------------------------------------------------------|
| value_counts()                       | 각 값의 빈도수(정수)를 반환                                      |
| value_counts(normalize=True)         | 각 값의 비율(소수점)을 반환 (전체 합계는 1.0)                    |
| value_counts(normalize=True) * 100   | 비율을 퍼센트(%)로 변환하여 가독성 향상                         |


## 📊 활용 팁
- 시각화 전에 비율로 정리하면 pie chart, barplot에 바로 적용 가능
- 특정 범주가 전체에서 얼마나 차지하는지 빠르게 파악 가능
- groupby와 함께 쓰면 다중 조건 비율 분석도 가능

---

# 프레임 합치기


## 소스

```python
l1 = [{'name': 'John', 'job': "teacher"},
      {'name': 'Nate', 'job': "student"},
      {'name': 'Fred', 'job': "developer"}]

l2 = [{'name': 'Ed', 'job': "dentist"},
      {'name': 'Jack', 'job': "farmer"},
      {'name': 'Ted', 'job': "designer"}]
         
df1 = pd.DataFrame(l1, columns = ['name', 'job'])
df2 = pd.DataFrame(l2, columns = ['name', 'job'])

frames = [df1, df2]
result = pd.concat(frames, ignore_index=True)
result
```


이 코드는 두 개의 리스트를 각각 DataFrame으로 만든 뒤, 하나로 병합하는 흐름.  
아래에 단계별로 정리:

## 🧩 1단계: 리스트 → DataFrame 변환
```python
df1 = pd.DataFrame(l1, columns=['name', 'job'])
df2 = pd.DataFrame(l2, columns=['name', 'job'])
```

- l1, l2 리스트를 각각 테이블 형태로 변환
- 열 이름은 'name', 'job'

## 🧩 2단계: 병합 준비
```python
frames = [df1, df2]
```

- 두 DataFrame을 리스트로 묶어 병합 준비

## 🧩 3단계: concat으로 병합
```python
result = pd.concat(frames, ignore_index=True)
```

- pd.concat()으로 수직 병합 (행 추가 방식)
- ignore_index=True로 인덱스를 새로 부여

### 📋 최종 결과 예시
```
    name       job
0   John    teacher
1   Nate    student
2   Fred  developer
3     Ed    dentist
4   Jack     farmer
5    Ted   designer
```


## 🔍 핵심 메서드 요약
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| pd.DataFrame(...)  | 리스트 또는 딕셔너리를 기반으로 테이블(DataFrame) 생성            |
| pd.concat([...])   | 여러 DataFrame을 수직 방향으로 병합 (행 추가 방식)               |
| ignore_index=True  | 기존 인덱스를 무시하고 병합 후 새로운 인덱스를 자동 생성         |


열 기준 병합(merge), 중복 제거, 그리고 병합 후 정렬까지의 흐름을 단계별로 체계적으로 정리한:

## 🧩 1단계: 열 기준 병합 (merge)
```python
pd.merge(df1, df2, on='name', how='inner')
```
## 🔍 핵심 메서드 요약
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| pd.merge()         | 공통 열을 기준으로 두 DataFrame을 병합하는 함수                   |
| on='name'          | 'name' 열을 기준으로 병합                                         |
| how='inner'        | 양쪽 모두에 존재하는 값만 병합 (교집합)                          |
| how='outer'        | 양쪽 전체 값을 병합, 없는 값은 NaN으로 채움 (합집합)             |
| how='left' / 'right'| 왼쪽 또는 오른쪽 기준으로 병합 (부분집합 + NaN 보완)            |

## 📌 예시:
```python
pd.merge(df1, df2, on='name', how='outer')
```


## 🧩 2단계: 중복 제거
```python
df.drop_duplicates(subset=['name'], keep='first')
```
## 🔍 핵심 메서드 요약
| 구성 요소                  | 설명                                                             |
|---------------------------|------------------------------------------------------------------|
| drop_duplicates()         | 중복된 행을 제거하는 함수                                        |
| subset=['name']           | 'name' 열 기준으로 중복 여부 판단                                |
| keep='first'              | 중복 중 첫 번째 항목을 유지하고 나머지는 제거                    |
| keep='last'               | 중복 중 마지막 항목을 유지하고 앞선 항목은 제거                  |

## 📌 중복 행만 추출하고 싶다면:
```python
df[df.duplicated('name', keep=False)]
```


## 🧩 3단계: 병합 후 정렬
```python
df.sort_values(by='name', ascending=True)
```
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| sort_values()      | 특정 열 기준으로 행을 정렬하는 함수                               |
| by='name'          | 'name' 열을 기준으로 정렬                                         |
| ascending=True     | 오름차순 정렬 (False로 설정하면 내림차순 정렬)                    |

## 📌 여러 열 기준 정렬도 가능:
```python
df.sort_values(by=['job', 'name'], ascending=[True, False])
```


## 🧠 전체 흐름 요약
| 단계       | 메서드               | 설명                                                             |
|------------|----------------------|------------------------------------------------------------------|
| 병합       | pd.merge()           | 공통 열 기준으로 두 DataFrame을 열 방향으로 병합                 |
| 중복 제거  | drop_duplicates()    | 중복된 행을 제거하여 고유한 데이터만 유지                        |
| 정렬       | sort_values()        | 특정 열 기준으로 행을 오름차순 또는 내림차순 정렬                |


---

# 이 코드는 두 개의 리스트 l1, l2를 각각 DataFrame으로 만든 뒤, 하나로 병합하는 흐름:

# Source
```python
l1 = [{'name': 'John', 'job': "teacher"},
      {'name': 'Nate', 'job': "student"},
      {'name': 'Fred', 'job': "developer"}]

l2 = [{'name': 'Ed', 'job': "dentist"},
      {'name': 'Jack', 'job': "farmer"},
      {'name': 'Ted', 'job': "designer"}]
         
df1 = pd.DataFrame(l1, columns = ['name', 'job'])
df2 = pd.DataFrame(l2, columns = ['name', 'job'])
result = pd.concat([df1, df2], ignore_index=True)

result

```

## 🧩 단계별 설명
### 1️⃣ 리스트 → DataFrame 변환
```python
df1 = pd.DataFrame(l1, columns=['name', 'job'])
df2 = pd.DataFrame(l2, columns=['name', 'job'])
```

- l1, l2 리스트를 각각 테이블 형태로 변환
- 열 이름은 'name', 'job'

###  2️⃣ 병합 준비 및 실행
```python
result = pd.concat([df1, df2], ignore_index=True)
```


- pd.concat()으로 수직 병합 (행 추가 방식)
- ignore_index=True로 인덱스를 새로 부여하여 깔끔하게 정렬

### 📋 병합 결과 예시
```
    name       job
0   John    teacher
1   Nate    student
2   Fred  developer
3     Ed    dentist
4   Jack     farmer
5    Ted   designer
```


## 🔍 핵심 메서드 요약
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| pd.DataFrame(...)  | 리스트 또는 딕셔너리를 기반으로 테이블(DataFrame) 생성            |
| pd.concat([...])   | 여러 DataFrame을 수직 방향으로 병합 (행 추가 방식)               |
| ignore_index=True  | 기존 인덱스를 무시하고 병합 후 새로운 인덱스를 자동 생성         |



# 이 코드는 두 개의 DataFrame을 열 방향(axis=1) 으로 병합하면서 인덱스를 무시하고 새로운 열 인덱스를 부여하는 흐름

# 소스
```python
l1 = [{'name': 'John', 'job': "teacher"},
      {'name': 'Nate', 'job': "student"},
      {'name': 'Jack', 'job': "developer"}]

l2 = [{'age': 25, 'country': "U.S"},
      {'age': 30, 'country': "U.K"},
      {'age': 45, 'country': "Korea"}]
         
df1 = pd.DataFrame(l1, columns = ['name', 'job'])
df2 = pd.DataFrame(l2, columns = ['age', 'country'])
result = pd.concat([df1, df2], axis=1, ignore_index=True)
result
```
## 🧩 1단계: 리스트 → DataFrame 변환
```python
df1 = pd.DataFrame(l1, columns=['name', 'job'])
df2 = pd.DataFrame(l2, columns=['age', 'country'])
```

- df1: 이름과 직업 정보
- df2: 나이와 국가 정보

## 🧩 2단계: 열 방향 병합
```python
result = pd.concat([df1, df2], axis=1, ignore_index=True)
```

| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| axis=1             | 열 방향으로 병합 (가로로 붙이기)                                 |
| ignore_index=True  | 기존 열 이름을 무시하고 숫자 인덱스로 새로 부여                  |


## 📌 결과 예시:
```
       0          1     2        3
0   John    teacher    25      U.S
1   Nate    student    30      U.K
2   Jack  developer    45    Korea
```

열 이름이 사라지고 숫자 인덱스(0, 1, 2, 3)로 바뀌는 이유는 ignore_index=True 때문.


## ✅ 열 이름 유지하려면?
```python
result = pd.concat([df1, df2], axis=1)
```

- ignore_index=False가 기본값이므로 열 이름이 유지됨
### 📌 결과 예시:
```
   name       job  age country
0  John   teacher   25     U.S
1  Nate   student   30     U.K
2  Jack developer   45   Korea
```


## 🔍 핵심 메서드 요약
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| pd.concat([...])   | 여러 DataFrame을 병합하는 함수                                    |
| axis=1             | 열 방향으로 병합 (가로로 붙이기)                                 |
| ignore_index=True  | 기존 열 이름을 무시하고 숫자 인덱스로 새로 부여                  |

----
## 샘플
```python
label = [1,2,3,4,5]
prediction = [1,2,2,5,5]

comparison = pd.DataFrame(
    {'label': label,
     'prediction': prediction
    })

comparison
```



## 🧩 1단계: 리스트 정의
```python
label = [1, 2, 3, 4, 5]
prediction = [1, 2, 2, 5, 5]
```

- label: 실제 정답
- prediction: 모델 또는 알고리즘의 예측 결과

## 🧩 2단계: 비교용 DataFrame 생성
```python
comparison = pd.DataFrame({
    'label': label,
    'prediction': prediction
})
```

- 두 리스트를 열로 구성한 테이블 생성

## 📋 결과 예시
```
   label  prediction
0      1           1
1      2           2
2      3           2
3      4           5
4      5           5
```


## ✅ 확장 아이디어
정확도 계산, 오차 분석, 또는 시각화로 이어질 수 있음:
```python
comparison['correct'] = comparison['label'] == comparison['prediction']
accuracy = comparison['correct'].mean()
```

### 📌 정확도 출력:
```python
accuracy = 3 / 5 = 0.6 (60%)
```




모델 예측 결과를 분석할 때 사용하는 confusion matrix, precision/recall 계산, 그리고 시각화(heatmap, barplot) 흐름을 단계별로 정리

## 🧩 1단계: Confusion Matrix 생성
```python
from sklearn.metrics import confusion_matrix

cm = confusion_matrix(label, prediction)
print(cm)
```

- label: 실제 값
- prediction: 예측 값
- 결과는 클래스별로 얼마나 맞췄는지 보여주는 행렬
### 📌 예시 출력:
```
[[1 0 0 0 0]
 [0 1 1 0 0]
 [0 0 0 0 0]
 [0 0 0 0 1]
 [0 0 0 0 2]]
```


## 🧩 2단계: Precision, Recall 계산
```python
from sklearn.metrics import precision_score, recall_score

precision = precision_score(label, prediction, average='macro')
recall = recall_score(label, prediction, average='macro')

print("Precision:", precision)
print("Recall:", recall)
```

| average 옵션       | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| average='macro'    | 클래스별로 개별 계산 후 단순 평균 (클래스 균형이 중요할 때 사용) |
| average='weighted' | 클래스별 개별 계산 후 샘플 수 기준 가중 평균                     |
| average='micro'    | 전체 TP, FP, FN을 합산하여 계산 (전체 정확도 중심)              |


## 🧩 3단계: Confusion Matrix 시각화 (Heatmap)
```python
import seaborn as sns
import matplotlib.pyplot as plt

sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()
```

- annot=True: 숫자 표시
- fmt='d': 정수 형식
- cmap='Blues': 색상 스타일

## 🧩 4단계: Barplot으로 클래스별 정확도 시각화
```python
import pandas as pd

comparison['correct'] = comparison['label'] == comparison['prediction']
class_accuracy = comparison.groupby('label')['correct'].mean().reset_index()

sns.barplot(x='label', y='correct', data=class_accuracy)
plt.title('Accuracy per Class')
plt.ylabel('Accuracy')
plt.show()
```

- 각 클래스별로 얼마나 정확하게 예측했는지 시각화

## 🧠 핵심 요약
| 단계       | 메서드                          | 설명                                                             |
|------------|----------------------------------|------------------------------------------------------------------|
| 평가       | confusion_matrix()               | 실제 값과 예측 값의 혼동 행렬 생성                              |
| 평가       | precision_score(), recall_score()| 정밀도(Precision)와 재현율(Recall) 계산                          |
| 시각화     | sns.heatmap()                    | 혼동 행렬을 색상으로 시각화 (정확도 시각적 분석에 유용)         |
| 시각화     | sns.barplot()                    | 클래스별 정확도 또는 비율을 막대그래프로 시각화                 |


pandas와 matplotlib를 함께 사용해서 데이터프레임을 시각화하는 기본 샘플 코드.  
막대그래프(bar chart)를 그리는 예제.

## 📊 샘플: 직업별 인원 수 시각화 (Bar Chart)
```python
import pandas as pd
import matplotlib.pyplot as plt

# 데이터 생성
data = [
    {'name': 'John', 'job': 'teacher'},
    {'name': 'Nate', 'job': 'student'},
    {'name': 'Fred', 'job': 'developer'},
    {'name': 'Yuna', 'job': 'teacher'},
    {'name': 'Brian', 'job': 'student'},
    {'name': 'Jack', 'job': 'teacher'}
]

df = pd.DataFrame(data)

# 직업별 인원 수 집계
job_counts = df['job'].value_counts()

# 시각화
job_counts.plot(kind='bar', color='skyblue', edgecolor='black')
plt.title('직업별 인원 수')
plt.xlabel('직업')
plt.ylabel('인원 수')
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
```


## 🔍 설명
| 구성 요소           | 설명                                                             |
|--------------------|------------------------------------------------------------------|
| value_counts()     | 범주형 데이터의 빈도수를 계산                                     |
| plot(kind='bar')   | 막대그래프 형태로 시각화                                         |
| plt.title()        | 그래프 제목 설정                                                  |
| plt.xticks()       | x축 라벨 회전 또는 위치 조정                                      |
| plt.tight_layout() | 그래프 요소 간 간격 자동 조정                                     |
| plt.show()         | 그래프를 화면에 출력                                              |



# NumPy는 수치 계산을 위한 라이브러리이고, matplotlib는 시각화를 위한 라이브러리

## ✅ 기본 호출 방식
```python
import numpy as np
import matplotlib.pyplot as plt
```

- np: NumPy의 약어
- plt: matplotlib의 시각화 모듈인 pyplot의 약어

## 📊 예시: NumPy 배열을 시각화
```python
import numpy as np
import matplotlib.pyplot as plt

# NumPy로 데이터 생성
x = np.linspace(0, 10, 100)
y = np.sin(x)

# matplotlib로 시각화
plt.plot(x, y)
plt.title('Sine Wave')
plt.xlabel('x')
plt.ylabel('sin(x)')
plt.grid(True)
plt.show()
```
## 🔍 설명
| 구성 요소               | 설명                                                             |
|------------------------|------------------------------------------------------------------|
| NumPy np               | 수치 계산 및 배열 생성을 위한 라이브러리                         |
| matplotlib.pyplot plt  | 그래프 시각화를 위한 라이브러리의 서브모듈                      |
| plt.plot()             | 선 그래프 생성 (x, y 값 기반 시각화)                            |
| plt.show()             | 생성된 그래프를 화면에 출력                                     |

---

