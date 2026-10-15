## 📘 Python 파일 쓰기 + CSV 연동 정리

### 📌 일반 텍스트 파일 쓰기

| 함수/모드             | 설명                         | 예시 코드                          |
|------------------------|------------------------------|-------------------------------------|
| `write()`              | 문자열 한 줄 쓰기             | `f.write('I love python\n')`        |
| `writelines()`         | 문자열 리스트를 한꺼번에 쓰기 | `f.writelines(['Apple\n', 'Banana\n'])` |
| `print(..., file=f)`   | `print()` 결과를 파일에 출력  | `print('Hello', file=f)`            |
| `'wt'`                 | 텍스트 쓰기 모드              | `open('file.txt', 'wt')`            |
| `'at'`                 | 텍스트 추가 모드              | `open('file.txt', 'at')`            |

#### 🔹 추가 팁
- `'wt'` 는 기존 내용을 덮어쓰기하며, 파일이 없으면 새로 생성
- `'at'` 는 기존 내용 뒤에 덧붙이기하며, 파일이 없으면 새로 생성
- `print(..., file=f)` 는 write()보다 줄바꿈 처리에 편리함


### 📌 1. 텍스트 쓰기 vs 바이너리 쓰기

| 모드   | 설명                                   | 예시 코드                                 |
|--------|----------------------------------------|--------------------------------------------|
| `'wt'` | 텍스트 쓰기 모드 (문자 기반, 인코딩 필요) | `open('file.txt', 'wt', encoding='utf-8')` |
| `'wb'` | 바이너리 쓰기 모드 (바이트 기반)         | `open('file.bin', 'wb')`                   |

---

### 📌 CSV 파일 읽기
#### 🔹 1. 기본 읽기 (csv.reader)
```python
import csv

with open('test.csv', 'r', encoding='utf-8') as f:
    reader = csv.reader(f)
    next(reader)  # 헤더 스킵
    for row in reader:
        print(row)  # ['Afghanistan', 'AF']

```
#### 🔹 2. 구분자 변경 (delimiter='|')
```python
reader = csv.reader(f, delimiter='|')
```

#### 🔹 3. 딕셔너리 방식 (csv.DictReader)
```python
reader = csv.DictReader(f)
for row in reader:
    print(row['Name'], row['Code'])
```

### 📌 CSV 파일 쓰기
#### 🔹 1. 리스트 기반 쓰기 (csv.writer)
```python
import csv

data = [[1,2,3], [4,5,6], [7,8,9]]
with open('write.csv', 'w', encoding='utf-8') as f:
    writer = csv.writer(f)
    for row in data:
        writer.writerow(row)
```

#### 🔹 결과:
```
1,2,3
4,5,6
7,8,9
```

#### 🔹 2. 딕셔너리 기반 쓰기 (csv.DictWriter)
```python
fields = ['One', 'Two', 'Three']
data = [[1,2,3], [4,5,6]]

with open('write.csv', 'w', encoding='utf-8') as f:
    writer = csv.DictWriter(f, fieldnames=fields)
    writer.writeheader()
    for row in data:
        writer.writerow({'One': row[0], 'Two': row[1], 'Three': row[2]})
```

#### 🔹 결과:
```
One,Two,Three
1,2,3
4,5,6
```

### 📌 MIME 타입 참고
- CSV 파일의 MIME 타입은 text/csv
- 웹에서 다운로드 시 파일 형식 지정에 사용됨

---

## 📘 CSV / JSON 비교

### 📌 CSV vs JSON 파일 쓰기 읽기  비교  
#### 🔹 1. 구조 차이

| 항목         | `.csv` 파일                        | `.json` 파일                          |
|--------------|------------------------------------|----------------------------------------|
| 구조 형태    | 행/열 기반 (테이블 구조)           | 키-값 기반 (딕셔너리/리스트 구조)     |
| 확장성       | 단순한 데이터에 적합                | 중첩 구조, 복잡한 데이터에 적합       |
| 표현 방식    | 텍스트로 행 구분, 쉼표로 열 구분    | 중괄호 `{}`와 대괄호 `[]`로 구조 표현 |
| MIME 타입    | `text/csv`                         | `application/json`                    |


#### 🔹 CSV 쓰기 예시
```python
import csv

data = [['Name', 'Age'], ['Alice', 30], ['Bob', 25]]
with open('data.csv', 'w', encoding='utf-8') as f:
    writer = csv.writer(f)
    writer.writerows(data)
```

#### 🔹 JSON 쓰기 예시
```python
import json
data = {'Name': 'Alice', 'Age': 30}
with open('data.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=4)
```

#### 🔹 CSV 딕셔너리 방식
```python
with open('data.csv', 'r', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    for row in reader:
        print(row['Name'], row['Age'])  # Alice 30
```

#### 🔹 JSON 파일 읽기
```python
import json

with open('data.json', 'r', encoding='utf-8') as f:
    data = json.load(f)
    print(data['Name'])  # Alice
```

#### 🔹 CSV (data.csv)
```
Name,Age
Alice,30
Bob,25
```

#### 🔹 JSON (data.json)
```
{
  "users": [
    {"Name": "Alice", "Age": 30},
    {"Name": "Bob", "Age": 25}
  ]
}
```
---






