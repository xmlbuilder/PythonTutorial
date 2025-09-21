
# 🧨 Python 예외 처리 원리와 사용법
Python에서 예외(Exception)는 프로그램 실행 중 발생하는 오류 상황을 제어하기 위한 핵심 기능입니다.  
예외를 적절히 처리하면 프로그램이 예상치 못한 종료 없이 안정적으로 동작할 수 있습니다.

## 🔍 예외 처리의 기본 원칙
- 예외는 반드시 처리한다
→ try-except 구문을 통해 예외 발생 시 대처
- 로그는 반드시 남긴다
→ logging 모듈을 활용하여 예외 발생 시 기록
- 예외는 던져진다
→ raise 키워드로 사용자 정의 예외를 발생시킬 수 있음
- 예외는 무시할 수도 있다
→ except: pass 형태로 처리하지만, 남용은 위험

## 🧪 주요 예외 종류와 예시
### 1. SyntaxError – 문법 오류
```python
print('error)
```

SyntaxError: unterminated string literal

코드가 실행되기 전에 파싱 단계에서 발생


### 2. NameError – 정의되지 않은 변수
```python
a = 10
b = 15
print(c)
```

NameError: name 'c' is not defined


### 3. ZeroDivisionError – 0으로 나누기
```python
print(100 / 0)
```

ZeroDivisionError: division by zero



### 4. IndexError – 리스트 인덱스 초과
```python
x = [50, 70, 90]
print(x[4])
```

IndexError: list index out of range



### 5. KeyError – 딕셔너리 키 없음
```python
dic = {'name': "jhjeong", 'age': 56, 'city': 'Seoul'}
print(dic['phone'])
```

KeyError: 'phone'


### 6. AttributeError – 존재하지 않는 속성 호출
```python
import time
print(time.time2())
```

AttributeError: module 'time' has no attribute 'time2'



### 7. ValueError – 잘못된 값
```python
x = [50, 10, 90]
x.remove(200)
```

ValueError: list.remove(x): x not in list



### 8. FileNotFoundError – 파일 없음
```rust
f = open('test.xlsx', 'r')
```

FileNotFoundError: No such file or directory: 'test.xlsx'



### 9. TypeError – 자료형 불일치
```python
x = [1, 2]
y = (1, 2)
print(x + y)
```

TypeError: can only concatenate list (not "tuple") to list

## ✅ 예외 처리 기본 구조
```python
try:
    # 예외 발생 가능 코드
    result = 10 / 0
except ZeroDivisionError as e:
    print("예외 발생:", e)
finally:
    print("항상 실행되는 블록")
```


## 📘 예외 처리 팁
- try-except-finally 구조를 적극 활용
- logging 모듈로 예외 기록 남기기
- 사용자 정의 예외는 class MyError(Exception): 형태로 작성 가능
- 예외 무시는 except: pass로 가능하지만, 디버깅이 어려워질 수 있음

---


