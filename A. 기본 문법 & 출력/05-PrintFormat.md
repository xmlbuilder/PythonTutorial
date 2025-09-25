# Print Format
Python의 print() 함수에서 자주 사용하는 end 옵션, file 옵션, 그리고 문자열 포맷팅 방식.

## 🔚 end 옵션: 출력 끝 문자 지정
기본적으로 print()는 출력 후 줄바꿈(\n)을 합니다. end 옵션을 사용하면 이를 원하는 문자로 바꿀 수 있어요.
```python
print('Welcome to', end='')      # 줄바꿈 없음
print('IT News', end='')         # → Welcome toIT News

print('Welcome to', end='    ')  # 공백 4칸
print('IT News', end='    ')     # → Welcome to    IT News    

print('Welcome to', end='')      
print('IT News', end='')         
print('Web Site')                # → Welcome toIT NewsWeb Site
```

## 📌 print() 함수의 `end` 옵션 예시
| 표현         | 설명 또는 출력 결과 예시                  |
|--------------|--------------------------------------------|
| `end=''`     | 줄바꿈 없이 바로 이어서 출력됨             |
| `end=' '`    | 출력 사이에 공백 한 칸 삽입됨              |
| `end='---'`  | 출력 사이에 `'---'` 문자열이 삽입됨         |

## 📁 file 옵션: 출력 대상 지정
```python
import sys
print('Learn Python', file=sys.stdout)  # 콘솔 출력
```

- 기본 출력은 sys.stdout (콘솔)
- file=open('output.txt', 'w')로 파일에 출력 가능

## 🧾 문자열 포맷팅 방식
### 1️⃣ % 포맷 방식 (C 스타일)
```python
print('%s %s' % ("123", "456"))  # 문자열
print('%d %d' % (123, 456))      # 정수
print('%.2f' % (3.14159))        # 소수점 2자리
```

### 2️⃣ str.format() 방식
```python
print('{} {}'.format("123", "456"))       # 기본 순서
print('{1} {0}'.format("123", "456"))     # 인덱스 지정 → 456 123
print('{:.2f}'.format(3.14159))           # 소수점 2자리 → 3.14
```


## 📌 문자열 포맷팅 방식 요약
| 표현           | 설명 또는 사용 예시                                |
|----------------|-----------------------------------------------------|
| `%s%d%f`       | C 스타일 포맷. 문자열, 정수, 실수 포맷 지정 (`%s`, `%d`, `%.2f`) |
| `{}`           | 기본 `str.format()` 방식. 순서대로 값 삽입               |
| `{1} {0}`      | 인덱스를 지정하여 순서 변경 가능 (`format("A", "B") → B A`) |
| `{:.2f}`       | 소수점 2자리까지 포맷팅 (`format(3.14159) → 3.14`)     |


## ✨ 추천: f-string 방식 (Python 3.6+)
name = "JungHwan"
score = 95.5
print(f"{name}님의 점수는 {score:.1f}점입니다.")  # → JungHwan님의 점수는 95.5점입니다.

- 가독성 최고, 성능도 우수
- 변수 직접 삽입 가능
---

