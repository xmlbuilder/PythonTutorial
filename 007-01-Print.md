# Print

## 🖨️ 기본 출력
```python
print()                      # 빈 줄 출력
print("Hello World!")        # 큰따옴표
print('Hello World!')        # 작은따옴표 (Python에서 가장 일반적)
```

## 📋 여러 줄 문자열 출력
```python
print('''Sample Model1
Sample Model2''')

print("""Sample Model3
Sample Model4
    Sample Model5""")
```

- ''' 또는 """를 사용하면 여러 줄 문자열을 출력할 수 있어요.
- 들여쓰기도 그대로 유지됩니다.

## ⚙️ sep 옵션: 값 사이 구분자 지정
```python
print('P', 'Y', 'T', 'H', 'O', 'N')                 # 기본: 공백
print('P', 'Y', 'T', 'H', 'O', 'N', sep='')         # PYTHON
print('P', 'Y', 'T', 'H', 'O', 'N', sep=',')        # P,Y,T,H,O,N
print('010', '7339', '9286', sep='-')              # 010-7339-9286
print('python', 'google.com', sep='@')             # python@google.com
```

- sep='구분자'를 지정하면 출력값 사이에 원하는 문자열을 삽입할 수 있어요.

## 🔚 end 옵션: 출력 끝에 붙일 문자열 지정
```python
print("Hello", end='')       # 줄바꿈 없이 출력
print("World")               # 이어서 출력 → HelloWorld

print("Line1", end=' | ')
print("Line2")               # → Line1 | Line2
```

- 기본값은 end='\n' (줄바꿈)
- end='' 또는 end=' ' 등으로 변경 가능

## 📦 전체 옵션 요약
```
print(object, ..., sep=' ', end='\n', file=sys.stdout, flush=False)
```

## 📌 print() 함수 옵션 요약

| 옵션 이름 | 설명 또는 기능                                 |
|-----------|--------------------------------------------------|
| `sep`     | 여러 값 사이에 삽입할 구분자 지정 (기본값: 공백 `' '`) |
| `end`     | 출력 후 끝에 붙일 문자열 지정 (기본값: 줄바꿈 `'\n'`) |
| `file`    | 출력 대상 지정 (기본값: `sys.stdout`, 즉 콘솔)       |
| `flush`   | 출력 버퍼를 강제로 비울지 여부 (`True` 또는 `False`) |
---



