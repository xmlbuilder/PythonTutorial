# 🧠 Python 정규표현식 핵심 개념
Python에서는 re 모듈을 사용해 문자열에서 특정 패턴을 찾거나 추출할 수  있음.

## 📦 기본 구조
```python
import re
pattern = re.compile(r'정규표현식')
result = pattern.search('대상 문자열')
```

## 🔤 주요 정규표현식 패턴
| 패턴            | 설명                                      | 예시 매칭 값             |
|-----------------|-------------------------------------------|---------------------------|
| \d              | 숫자 하나                                 | 0, 9                      |
| \d{3}           | 숫자 3자리                                | 123                       |
| \w              | 문자 또는 숫자 또는 밑줄                  | a, 9, _                   |
| \s              | 공백 문자 (space, tab, newline 등)        | ' '                       |
| .               | 아무 문자 하나                            | a, 1                      |
| ^               | 문자열의 시작                             | ^Hello → Hello world      |
| $               | 문자열의 끝                               | world$ → Hello world      |
| ()              | 그룹 지정                                 | (\d{3})-(\d{4})           |
| (?P<name>...)   | 그룹에 이름 지정                          | (?P<area>\d{3})           |
| \|              | OR 조건                                   | cat\|dog → cat 또는 dog   |
| []              | 문자 집합                                 | [aeiou] → 모음 중 하나    |
| {n,m}           | 반복 횟수 지정                            | \d{2,4} → 2~4자리 숫자     |


## 🧪 실전 예제 분석
### 1️⃣ 전화번호 추출
```python
text = "문의사항이 있으면 032-232-3245 으로 연락주시기 바랍니다."
regex = re.compile(r'\d{2,3}-\d{3,4}-\d{4}')
matchobj = regex.search(text)
if matchobj:
    print(matchobj.group())  # 032-232-3245
```      

- \d{2,3}: 지역번호 (2~3자리)
- \d{3,4}: 중간번호 (3~4자리)
- \d{4}: 마지막 번호 (4자리)

###  2️⃣ 에러 코드 추출
```python
text = "에러 1122 : 레퍼런스 오류\n 에러 1033: 아규먼트 오류"
regex = re.compile(r"에러\s(\d+)")
mc = regex.findall(text)
print(mc)  # ['1122', '1033']
```

- \s: 공백 문자
- (\d+): 숫자 그룹 추출

### 3️⃣ 그룹 이름으로 전화번호 분리
```python
regex = re.compile(r'(?P<area>\d{3})-(?P<num>\d{3}-\d{4})')
matchobj = regex.search(text)
if matchobj:
    areaCode = matchobj.group("area")
    num = matchobj.group("num")
    print(areaCode, num)  # 032 232-3245
````

- (?P<area>...): 그룹 이름 area
- (?P<num>...): 그룹 이름 num
이렇게 하면 matchobj.group("area")처럼 이름으로 접근할 수 있어요.

## 🛠 자주 쓰는 함수
| 함수             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| re.search()      | 문자열 전체에서 **첫 번째 매칭** 을 찾아 Match 객체 반환               |
| re.findall()     | 문자열 전체에서 **모든 매칭 결과** 를 리스트로 반환                    |
| re.match()       | 문자열의 **시작 부분** 에서만 매칭 시도 (전체가 아닌 시작만)           |
| re.sub()         | 매칭된 부분을 **다른 문자열로 치환**                                  |
| re.compile()     | 정규표현식을 **패턴 객체로 컴파일** 하여 재사용 가능                   |

## 💡 팁
- 정규표현식 앞에는 항상 r'' (raw string) 사용 → 백슬래시를 이스케이프하지 않도록
- matchobj.group() → 전체 매칭 결과
- matchobj.group(n) 또는 group("name") → 특정 그룹 추출


## 전체 소스

```python
import re
text = "문의사항이 있으면 032-232-3245 으로 연락주시기 바랍니다."
#regex = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')
regex = re.compile(r'\d{2,3}-\d{3,4}-\d{4}')
matchobj = regex.search(text)
if matchobj != None  :
    phonenumber = matchobj.group()
    print(phonenumber)

#출력  
'''032-232-3245'''
```
```python
text = "에러 1122 : 레퍼런스 오류\n 에러 1033: 아규먼트 오류"
regex = re.compile(r"에러\s(\d+)")
mc = regex.findall(text)
print(mc)

#출력
'''['1122', '1033']'''
```
```python
text = "문의사항이 있으면 032-232-3245 으로 연락주시기 바랍니다."
regex = re.compile(r'(?P<area>\d{3})-(?P<num>\d{3}-\d{4})')
matchobj = regex.search(text)
print(matchobj)

#출력
'''<re.Match object; span=(10, 22), match='032-232-3245'>'''
```
```python
if matchobj != None:
    areaCode = matchobj.group("area")
    num = matchobj.group("num")
    print(areaCode, num)

#출력
'''032 232-3245'''
```
