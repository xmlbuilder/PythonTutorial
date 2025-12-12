# 🧨 Python try-except 예외 처리 구조
Python에서 예외(Exception)는 프로그램 실행 중 발생할 수 있는 오류를 우아하게 처리하기 위한 구조입니다.  
try-except 블록을 사용하면 예외 발생 시 프로그램이 중단되지 않고 원하는 방식으로 대응할 수 있습니다.

## 🔧 기본 구조
```
try:
    # 에러가 발생할 가능성이 있는 코드
except 에러타입1:
    # 에러타입1 발생 시 실행
except 에러타입2:
    # 에러타입2 발생 시 실행
else:
    # 예외가 발생하지 않았을 때 실행
finally:
    # 예외 발생 여부와 관계없이 항상 실행
```


## 🧪 예제 1: ValueError 처리
```python
name = ['1', '2', '3', '4']

try:
    z = '1'
    x = name.index(z)
    print('{} Founded it! {} in name'.format(z, x + 1))
except ValueError:
    print("Not found it! - Occurred ValueError!")
else:
    print('Ok! else')
```

## 🧾 출력 결과
```python
1 Founded it! 1 in name
Ok! else
```
```
리스트에서 '1'을 찾는 데 성공했기 때문에 except는 실행되지 않고 else 블록이 실행됩니다.
```

## 🧪 예제 2: raise로 예외 직접 발생시키기
```python
try:
    a = 'park'
    if a == "jhjeong":
        print('OK Pass')
    else:
        raise ValueError("User Not Defined")
except ValueError as e:
    print('Occurred Exception:', e)
else:
    print('Ok!')
```

## 🧾 출력 결과
```
Occurred Exception: User Not Defined
```

- 조건을 만족하지 않으면 raise를 통해 직접 ValueError를 발생시켜 예외 처리 흐름을 제어합니다.


## 📘 각 블록의 역할 요약
| 블록     | 역할 설명                                                                 |
|----------|---------------------------------------------------------------------------|
| `try`      | 예외가 발생할 가능성이 있는 코드를 실행                                   |
| `except`   | 특정 예외가 발생했을 때 실행할 코드 블록                                   |
| `else`     | `try` 블록에서 예외가 발생하지 않았을 경우 실행                            |
| `finally`  | 예외 발생 여부와 관계없이 항상 마지막에 실행 (자원 정리, 로그 기록 등)     |
| `raise`    | 조건에 따라 예외를 직접 발생시켜 흐름을 제어                               |


## ✅ 실전 팁
- `except` 는 여러 개 작성 가능하며, except Exception as e:로 모든 예외를 포괄할 수도 있음
- `finally` 는 파일 닫기, DB 연결 종료 등 자원 정리에 매우 유용
- `raise는` 사용자 정의 예외나 조건 기반 예외 발생에 사용

---



