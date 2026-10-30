## 📘 np.genfromtxt — converters 옵션

### 📌 1. 기본 동작 — 변환 없이 읽기
```python
data = u'1, 2.3%, 45.\n6, 78.9%, 0'
names = ("i", "p", "n")
a = np.genfromtxt(StringIO(data), delimiter=",", names=names)
```

#### 🔹 출력:
```
[(1., nan, 45.) (6., nan,  0.)]
```

- `%` 가 포함된 문자열은 변환 실패 → nan 처리됨
- converters를 지정하지 않으면 자동 파싱만 수행됨

---

#### 🔹 출력 검증

- 결과가 `[(1., nan, 45.), (6., nan, 0.)]` 가 나오는지 절차적으로 설명.

#### 🔹 코드 분석: 변환 없이 읽기
```python
from io import StringIO
import numpy as np

data = u'1, 2.3%, 45.\n6, 78.9%, 0'
names = ("i", "p", "n")
a = np.genfromtxt(StringIO(data), delimiter=",", names=names)
```

#### 🔹 동작 절차 — 변환 없이 읽기
| 단계              | 설명                                       |
|-------------------|--------------------------------------------|
| StringIO(data)    | 문자열을 파일처럼 읽을 수 있도록 래핑함     |
| delimiter=","     | 쉼표 기준으로 열을 나눔                    |
| names=("i", "p", "n") | 각 열에 이름 부여: i, p, n               |
| 변환 시도          | "2.3%" → float 변환 실패 → nan 처리됨      |


#### 🔹 내부 처리 흐름 — 변환 없이 읽기
| 원본 행             | 열 분할 결과             | 변환 결과 (float 시도)     |
|---------------------|--------------------------|-----------------------------|
| '1, 2.3%, 45.'      | '1' '2.3%' '45.'         | 1.0   nan   45.0            |
| '6, 78.9%, 0'       | '6' '78.9%' '0'          | 6.0   nan    0.0            |

- 2.3%와 78.9%는 `%` 때문에 float 변환 실패 → nan 발생
- 나머지 숫자는 정상적으로 float으로 변환됨

#### 🔹 최종 결과
```
array([(1., nan, 45.), (6., nan, 0.)],
      dtype=[('i', '<f8'), ('p', '<f8'), ('n', '<f8')])
```

- 구조화 배열 형태
- 각 열은 이름으로 접근 가능:
```
a['i'] → array([1., 6.])
a['p'] → array([nan, nan])
a['n'] → array([45., 0.])
```


#### 🔹 설명
- delimiter="," → 쉼표 기준으로 열 분할
- 각 필드는 float()으로 자동 변환 시도
- "2.3%", "78.9%"는 float() 변환 실패 → nan 처리됨
- 나머지 "1", "45.", "6", "0"은 정상적으로 변환됨

#### 🔹 float로 변환을 시도하는 이유
- np.genfromtxt()가 데이터를 기본적으로 float으로 변환하려고 시도하는 이유는 다음과 같은 내부 동작 원칙 때문.

#### 🔹 변환 기준의 근거
#### 1. 기본 dtype은 float
- np.genfromtxt()는 명시적으로 dtype을 지정하지 않으면 기본적으로 float으로 데이터를 읽으려고 함.
- 이는 대부분의 수치 데이터가 실수형이기 때문에 범용성을 고려한 기본 설정.
```python
np.genfromtxt(StringIO("1 2 3\n4 5 6"))
→ array([[1., 2., 3.],
         [4., 5., 6.]])
```
- 위처럼 아무 옵션 없이 읽으면 자동으로 float64로 처리됨

#### 2. 결측값(nan) 처리를 위해 float이 필요함
- np.genfromtxt()는 결측값을 nan으로 처리하는데, nan은 float 타입에서만 표현 가능
- 그래서 기본적으로 float을 사용해야 결측값을 안전하게 표현할 수 있어
```python
np.genfromtxt(StringIO("1, , 3\n4, 5, 6"), delimiter=",")
→ array([[ 1., nan,  3.],
         [ 4.,  5.,  6.]])
```


#### 3. 자동 타입 추론이 없음
- np.genfromtxt()는 pandas.read_csv()처럼 자동으로 타입을 추론하지 않음 
- 대신 모든 필드를 동일한 타입으로 처리하려고 시도함 → 기본은 float

| 원본                     | 변환 결과              |
|-------------------------|-------------------------|
| 기본 dtype             | 명시하지 않으면 float64로 처리됨           |
| 결측값 처리            | nan 표현을 위해 float 타입이 필요함        |
| 자동 타입 추론 없음    | 모든 열을 동일한 타입으로 처리하려고 함     |


### 📌 2. 열 인덱스 기반 변환 — converters={1: func}
```python
convert_func = lambda x: float(x.strip("%")) / 100.0
b = np.genfromtxt(StringIO(data), delimiter=",", names=names, converters={1: convert_func})
```

#### 🔹 결과:
```
[(1., 0.023, 45.) (6., 0.789,  0.)]
```
- converters={1: func} → 두 번째 열(인덱스 1)에만 변환 함수 적용
- % 제거 후 백분율 → 실수로 변환

### 📌 3. 열 이름 기반 변환 — converters={"p": func}
```python
c = np.genfromtxt(StringIO(data), delimiter=",", names=names, converters={"p": convert_func})
```

#### 🔹 결과:
```
[(1., 0.023, 45.) (6., 0.789,  0.)]
```

- converters={"p": func} → 열 이름 "p"에 직접 적용
- 이름 기반 접근은 구조화 배열에서 더 직관적

### 📌 4. 결측값 처리 — 공백을 기본값으로 대체
```python
data = u'1,  , 3\n 4, 5, 6'
convert_func = lambda x: float(x.strip() or -999)
e = np.genfromtxt(StringIO(data), delimiter=",", converters={1: convert_func})
```

#### 🔹 결과:
```
[[   1. -999.    3.]
 [   4.    5.    6.]]
```

- 공백 문자열 → x.strip()은 빈 문자열
- or -999 → 빈 문자열일 경우 -999로 대체
- 실무에서 결측값을 특정 숫자로 채울 때 유용

### 📌 실무 팁 요약 — np.genfromtxt converters 활용
| 기법                    | 기능 설명                          | 실무 활용 예시                        |
|-------------------------|-------------------------------------|---------------------------------------|
| `converters={i: f}`       | 열 인덱스 기반 변환 함수 지정       | 1번째 열의 퍼센트 문자열 처리         |
| `converters={"name": f}`  | 열 이름 기반 변환 함수 지정         | "p" 열의 문자열 → 실수 변환           |
| `lambda x: x or default`  | 결측값 처리용 람다 함수             | 공백 → -999 같은 기본값으로 대체      |
| `strip()`                 | 문자열 전처리 (공백/기호 제거)      | `" 78.9% "` → `"78.9"` → `0.789`      |

### 📌 한마디
- converters는 np.genfromtxt()를 텍스트 전처리 도구로 확장시켜주는 핵심 옵션.  
- 특히 %, 공백, 단위 같은 비정형 데이터를 깔끔하게 숫자로 바꿔주는 데 유용. 
---
