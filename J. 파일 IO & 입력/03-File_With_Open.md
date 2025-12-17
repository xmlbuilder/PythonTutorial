# 📘 Python with open() 파일 읽기 정리

## ✅ 왜 with open()을 사용할까?
- 파일을 열고 자동으로 닫아주는 컨텍스트 매니저 방식
- f.close()를 직접 호출하지 않아도 안전하게 자원 해제
- 예외 발생 시에도 파일이 정상적으로 닫힘

```python
with open('파일경로', '모드', encoding='인코딩') as f:
    # 파일 작업 수행
```



## 🔧 주요 읽기 함수 요약

| 함수           | 설명                                 | 예시 출력 또는 동작 예시               |
|----------------|--------------------------------------|----------------------------------------|
| `read()`       | 파일 전체 내용을 문자열로 읽음        | `'Right now gamers can...'`           |
| `read(n)`      | n 바이트만큼 읽음                     | `'Right now gamers can'`              |
| `readline()`   | 한 줄씩 읽음                          | `'Right now gamers can pay...'`       |
| `readlines()`  | 모든 줄을 리스트로 반환               | `['Right now...', 'and Xbox...']`     |
| `seek(pos)`    | 파일 포인터 위치 이동                 | `f.seek(0)` → 처음으로 이동            |

## 📂 다양한 읽기 방식 예시
### 1. 전체 읽기 + 반복자 변환
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    content = f.read()
    print(content)           # 전체 텍스트 출력
    print(iter(content))     # 반복자 객체
    print(list(content))     # 문자 하나씩 리스트로 변환
```

### 2. 바이트 단위 읽기 + 포인터 이동
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    print(f.read(20))        # 처음 20바이트
    print(f.read(20))        # 다음 20바이트
    print(f.read(20))        # 또 다음 20바이트
    f.seek(0)                # 처음으로 이동
    print(f.read(20))        # 다시 처음 20바이트
```

### 3. 줄 단위 읽기 (readline())
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    line1 = f.readline()
    print(line1)
    line2 = f.readline()
    print(line2)
```

### 4. 전체 줄 리스트로 읽기 (readlines())
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    lines = f.readlines()
    print(lines)             # 리스트 형태로 출력
```

### 5. 줄 단위 반복 출력
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    for line in f:
        print(line, end='')  # 줄바꿈 제거하고 출력
```


## 📌 팁: 파일 모드 조합

| 모드   | 설명                                 |
|--------|--------------------------------------|
| `'rt'` | 텍스트 모드로 읽기 (기본값)           |
| `'rb'` | 바이너리 모드로 읽기                  |
| `'wt'` | 텍스트 모드로 쓰기 (기존 내용 삭제)   |
| `'at'` | 텍스트 모드로 추가 (파일 끝에 덧붙임) |
| `'r+'` | 읽기 + 쓰기 (파일이 있어야 함, 기존 내용 유지)                        |
| `'w+'` | 쓰기 + 읽기 (파일이 없으면 생성, 있으면 덮어씀)                       |
| `'a+'` | 추가 + 읽기 (파일이 없으면 생성, 있으면 끝에 덧붙임)                  |
| `'x'`  | 배타적 생성 (파일이 있으면 오류 발생, 없으면 새로 생성)               |

### 📘 추가 팁
- 'r', 'w', 'a'는 모두 텍스트 모드가 기본 ('t' 생략 가능)
- 바이너리 작업 시에는 이미지, 오디오, PDF 등 비텍스트 파일에 사용
- encoding='utf-8'은 텍스트 파일을 다룰 때 권장


### 📘 예시 코드

#### r+ : 기존 파일을 읽고 수정
```python
with open('sample.txt', 'r+') as f:
    content = f.read()
    f.seek(0)
    f.write('Updated!\n' + content)
```
#### w+ : 새로 쓰고 읽기 (기존 내용 삭제됨)
```python
with open('sample.txt', 'w+') as f:
    f.write('Hello World')
    f.seek(0)
    print(f.read())
```

#### a+ : 기존 내용 유지하며 추가
```python
with open('sample.txt', 'a+') as f:
    f.write('\nAppended line')
    f.seek(0)
    print(f.read())
```
#### x : 파일이 존재하면 오류 발생
```python
with open('newfile.txt', 'x') as f:
    f.write('Created exclusively')
```


### ⚠️ 주의사항
- 'r+'는 파일이 없으면 FileNotFoundError 발생
- 'x'는 파일이 이미 존재하면 FileExistsError 발생
- 'w+', 'a+'는 파일이 없으면 자동 생성됨

### 실전 예제
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as  f:
    content = f.read()
    print(content)
    print(iter(content))
    print(list(content))
```
#### read() : 전체 읽기, read(10) : 10Byte
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as  f:
    content = f.read(20)
    print(content)
```
```
Right now gamers can
```
```python
    c = f.read(20)
    print(c)
```
```
pay just $1 for acc
```

```python
    d = f.read(20)
    print(d)
```
```
ess to hundreds of t
```
```python
    f.seek(0,0)
    e = f.read(20)
    print(e)
```
```
Right now gamers can
```
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as  f:
    # for line in f:
    #     print(line)
    #
    line  = f.readline()
    print(line)
    line = f.readline()
    print(line)
```
```
Right now gamers can pay just $1 for access to hundreds of titles across PC 
and Xbox via Microsoft Xbox Game Pass Ultimate service?but dont 
```
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as  f:
    content = f.readlines()
    print(content)
```
```
['Right now gamers can pay just $1 for access to hundreds of titles across PC \n', 
'and Xbox via Microsoft Xbox Game Pass Ultimate service?but dont \n', 
... 
'\n']
```    
```python   
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as  f:
    content = f.readlines()
    for c in content:
        print(c, end='')
```

---

