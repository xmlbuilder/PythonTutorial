# 📂 Python 파일 읽기 정리

## 🔧 파일 열기 모드
| 모드 | 설명                                 |
|------|--------------------------------------|
| `r`  | 읽기 전용 (파일이 없으면 오류 발생)   |
| `w`  | 쓰기 전용 (파일이 없으면 생성, 있으면 덮어씀) |
| `a`  | 추가 모드 (파일 끝에 내용 덧붙임)     |
| `t`  | 텍스트 모드 (기본값)                  |
| `b`  | 바이너리 모드                         |

- 예: 'rt' → 텍스트 읽기, 'rb' → 바이너리 읽기

### 📘 예시 조합
- 'rt' : 텍스트 읽기
- 'wb' : 바이너리 쓰기
- 'at' : 텍스트 추가


## 📁 경로 지정 방식
| 경로 유형   | 예시 경로                         | 설명                                 |
|-------------|-----------------------------------|--------------------------------------|
| 상대 경로   | `'./data/file.txt'`               | 현재 작업 디렉토리를 기준으로 접근    |
| 절대 경로   | `'C:\\Users\\User\\file.txt'`     | 전체 경로를 지정하여 정확한 위치 접근 |

### 📘 추가 설명
- ./ : 현재 디렉토리
- ../ : 상위 디렉토리
- 절대 경로는 운영체제에 따라 형식이 다를 수 있음 (Windows는 C:\, macOS/Linux는 /Users/ 등)

## 📖 파일 읽기 기본 구조
```python
f = open('./resource/it_news.txt', 'rt', encoding='utf-8')
print(f.encoding)     # 파일 인코딩 확인
```
```python
print(f.name)         # 파일 이름 확인
```
```python
print(f.mode)         # 파일 모드 확인
```
```python
cts = f.read()        # 전체 내용 읽기
print(cts)
```
```python
f.close()             # 파일 닫기
```

## 🔍 주요 읽기 함수
| 함수           | 설명                                 |
|----------------|--------------------------------------|
| `read()`       | 파일 전체 내용을 문자열로 읽음        |
| `readline()`   | 한 줄씩 읽음 (줄바꿈 포함)            |
| `readlines()`  | 모든 줄을 리스트로 반환               |


### 📘 예시 코드
```python
with open('example.txt', 'rt', encoding='utf-8') as f:
    print(f.read())         # 전체 내용
```
```python
    f.seek(0)
    print(f.readline())     # 첫 번째 줄
```
```python
    f.seek(0)
    print(f.readlines())    # 모든 줄 리스트
```

## ✅ `with` 문을 사용한 안전한 파일 처리
```python
with open('./resource/it_news.txt', 'rt', encoding='utf-8') as f:
    for line in f:
        print(line.strip())
```
- with 문을 사용하면 close()를 자동으로 처리해줘서 안전하고 깔끔합니다.

---


