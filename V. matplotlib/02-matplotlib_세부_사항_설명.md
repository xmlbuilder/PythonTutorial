## 📘 matplotlib

### 📌 1. Sine & Cosine 그래프 (Matplotlib)
```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 100)
y_sin = np.sin(x)
y_cos = np.cos(x)

# 시각화
plt.plot(x, y_sin, label='Sine', color='blue')
plt.plot(x, y_cos, label='Cosine', color='red')
plt.title('Sine & Cosine Functions')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.show()
```

### 📌 핵심 포인트:
- np.linspace()로 연속적인 x값 생성
- plt.plot()으로 선 그래프
- legend()로 라벨 표시

### 📌 2. 시간에 따른 통계량 (Bar Chart & Polar Chart)
#### 🔹 Bar Chart 예제
```python
import pandas as pd
import matplotlib.pyplot as plt

# 시간별 통계량 예시
data = {'hour': ['00', '01', '02', '03', '04', '05'],
        'count': [5, 15, 25, 10, 20, 30]}
df = pd.DataFrame(data)

# 시각화
plt.bar(df['hour'], df['count'], color='skyblue', edgecolor='black')
plt.title('시간대별 이벤트 수')
plt.xlabel('시간')
plt.ylabel('건수')
plt.show()
```

#### 🔹 Polar Chart 예제
```python
import numpy as np
import matplotlib.pyplot as plt

# 시간별 각도 변환
hours = np.arange(0, 24)
counts = np.random.randint(10, 100, size=24)
angles = 2 * np.pi * hours / 24

# 시각화
fig = plt.figure()
ax = fig.add_subplot(111, polar=True)
ax.plot(angles, counts, color='purple', linewidth=2)
ax.fill(angles, counts, alpha=0.3)
ax.set_title('Polar Chart - 시간별 통계량')
plt.show()
```

### 📌 핵심 포인트:
- polar=True로 극좌표 그래프 생성
- angles는 라디안 단위로 변환 필요

### 📌 3. Seaborn 활용 예제
```python
import seaborn as sns
import matplotlib.pyplot as plt

# 한글 폰트 설정
plt.rcParams['font.family'] = 'Malgun Gothic'
plt.rcParams['axes.unicode_minus'] = False

# 데이터 로드
tips = sns.load_dataset('tips')

# 시각화
sns.barplot(x='day', y='tip', data=tips, estimator=np.mean, hue='day', palette='pastel', legend=False)
plt.title('요일별 평균 팁')
plt.show()
```


### 📌 핵심 포인트:
- sns.load_dataset()으로 내장 데이터 불러오기
- day를 기준으로 데이터를 그룹화하고, 각 그룹의 tip 평균을 계산합니다.
- estimator=np.mean으로 평균값 시각화
- palette로 색상 테마 설정

### 📌 요약 정리
| 시각화 유형       | 라이브러리         | 주요 함수 및 옵션                          |
|------------------|--------------------|--------------------------------------------|
| 선 그래프         | matplotlib         | plot(), legend(), grid()                   |
| 막대 그래프       | matplotlib         | bar(), xlabel(), ylabel()                  |
| 극좌표 그래프     | matplotlib         | subplot(polar=True), fill()                |
| 고급 막대 그래프  | seaborn            | barplot(), palette, estimator   

----

### 📌 Legend

```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 100)
y_sin = np.sin(x)
y_cos = np.cos(x)

# 시각화
plt.plot(x, y_sin, label='Sine', color='blue')
plt.plot(x, y_cos, label='Cosine', color='red')
plt.title('Sine & Cosine Functions')
plt.xlabel('x')
plt.ylabel('y')
plt.legend(loc='upper right', fontsize=12, frameon=True)
plt.grid(True)
plt.show()
```

#### 🔹 커스터마이징 옵션
```python
plt.legend(loc='upper right', fontsize=12, frameon=True)
```

| 옵션 이름   | 주요 값 또는 설명                                 |
|-------------|--------------------------------------------------|
| loc         | 'upper right', 'lower left', 'center' 등 위치 지정 |
| fontsize    | 숫자 또는 'small', 'medium', 'large' 등 글자 크기 |
| frameon     | True / False → 범례 테두리 표시 여부               |


#### 🔹 예시 코드
```python
plt.legend(loc='upper right', fontsize='medium', frameon=True)
```
- loc='upper right': 그래프 오른쪽 위에 범례 배치
- fontsize='medium': 중간 크기 글꼴
- frameon=True: 테두리 표시



### 📌 마커 추가 예제
```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 50)
y_sin = np.sin(x)
y_cos = np.cos(x)

# 시각화
plt.plot(x, y_sin, label='Sine', color='blue', marker='o')   # 둥근 점
plt.plot(x, y_cos, label='Cosine', color='red', marker='*')  # 별표

plt.title('Sine & Cosine with Markers')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.show()
```

#### 🔹 대표적인 마커 종류를 정리한 표

| 마커 코드 | 모양 설명       |
|-----------|----------------|
| 'o'       | 둥근 점         |
| '*'       | 별표            |
| 's'       | 사각형          |
| 'D'       | 다이아몬드      |
| 'x'       | X자             |
| '+'       | 십자            |

#### 🔹 예시 사용법
```python
plt.plot(x, y, marker='*')  # 별표 마커로 데이터 포인트 표시
```
- 마커는 plot() 함수 안에서 marker='...' 옵션으로 지정하며, markersize=10 같은 추가 옵션으로 크기도 조절할 수 있음.

---

### 📌 subplot

- subplot() 또는 subplots()를 사용해서 여러 개의 그래프를 한 화면에 나란히 배치할 수 있음. 

### 📌 기본 구조: plt.subplot()
```python
import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)
y1 = np.sin(x)
y2 = np.cos(x)

# 첫 번째 subplot (1행 2열 중 첫 번째)
plt.subplot(1, 2, 1)
plt.plot(x, y1, color='blue')
plt.title('Sine')

# 두 번째 subplot (1행 2열 중 두 번째)
plt.subplot(1, 2, 2)
plt.plot(x, y2, color='red')
plt.title('Cosine')

plt.tight_layout()
plt.show()
```

### 📌 subplot(행, 열, 위치) 형식으로 지정.

#### 🔹 더 유연한 방식: fig, ax = plt.subplots()
```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 100)
y1 = np.sin(x)
y2 = np.cos(x)

# 2행 1열 subplot 생성
fig, ax = plt.subplots(2, 1, figsize=(8, 6))

# 첫 번째 subplot: Sine
ax[0].plot(x, y1, color='blue')
ax[0].set_title('Sine')
ax[0].set_xlabel('x')
ax[0].set_ylabel('sin(x)')
ax[0].grid(True)

# 두 번째 subplot: Cosine
ax[1].plot(x, y2, color='red')
ax[1].set_title('Cosine')
ax[1].set_xlabel('x')
ax[1].set_ylabel('cos(x)')
ax[1].grid(True)

# 레이아웃 정리 및 출력
plt.tight_layout()
plt.show()
```

### 📌 ax는 배열처럼 접근 가능해서 코드가 더 깔끔해져요.

#### 🔹 확장 아이디어
- figsize=(width, height)로 전체 크기 조절, inch를 의미함
  - dpi로 지정하면:
```python
fig, ax = plt.subplots(
    2, 1,
    figsize=(8, 6),
    dpi=100
)
```
- sharex=True, sharey=True로 축 공유
- subplot(2, 2, i)로 4개까지 배치 가능


---

### 📌 수식 적용

#### 🔹 기본 문법: $수식$
```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

plt.plot(x, y)
plt.title(r'$y = \sin(x)$')  # 제목에 수식
plt.xlabel(r'$x$')           # x축 라벨
plt.ylabel(r'$y$')           # y축 라벨

plt.grid(True)
plt.show()
```

- r'...'는 raw string으로 백슬래시 \가 제대로 인식되도록 해줌.

| 수식 코드                  | 표현 설명                         |
|---------------------------|------------------------------------|
| `$x^2$`                   | x의 제곱                           |
| `$x_1$`                     | x의 아래 첨자 1                    |
| `$\frac{a}{b}$`             | a 나누기 b (분수 형태)             |
| `$\sqrt{x}$`                | x의 제곱근                         |
| `$\int_a^b f(x)\,dx$`       | a부터 b까지 f(x)의 정적분          |
| `$\sum_{i=1}^n i$`          | i=1부터 n까지의 합                 |

#### 🔹 사용 예시
```python
plt.title(r'$\int_a^b f(x)\,dx$')  # 그래프 제목에 수식
plt.xlabel(r'$x$')                 # x축 라벨
plt.text(1, 0.5, r'$\sqrt{x}$', fontsize=14)  # 그래프 안에 수식 주석
```
#### 🔹 그래프 안에 수식 주석 넣기
```python
plt.text(np.pi, 0, r'$\sin(\pi) = 0$', fontsize=12, color='red')
```

- plt.text(x좌표, y좌표, '텍스트')로 그래프 위에 수식 표시 가능
- fontsize, color 등으로 스타일 조절

---

### 📌 수식 넣기

#### 🔹 예시: 수식을 y값에 직접 넣기
```pythoin
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 10, 100)
y = np.exp(-x) * np.sin(2 * np.pi * x)  # 수식 직접 입력

plt.plot(x, y)
plt.title(r'$y = e^{-x} \cdot \sin(2\pi x)$')
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.grid(True)
plt.show()
```
- y = np.exp(-x) * np.sin(2 * np.pi * x)는 수식을 그대로 코드로 표현.

---

### 📌 수식 시각화 + 수식 표시
- 계산은 NumPy
- 표시는 matplotlib의 LaTeX 수식
  - 이렇게 조합하면 수학적 모델이나 물리 공식도 아주 깔끔하게 시각화할 수 있음.

#### 🔹 1.시각적 스타일링 보강
```python
- plt.style.use('ggplot'), 'seaborn-darkgrid', 'fivethirtyeight' 등 다양한 스타일 적용
- figsize, linewidth, alpha, color map 등으로 시각적 완성도 향상
plt.style.use('seaborn-darkgrid')
plt.plot(x, y, color='teal', linewidth=2, alpha=0.8)
```

#### 🔹 샘플 코드
```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 100)
y_sin = np.sin(x)
y_cos = np.cos(x)

# 그래프 스타일 설정 (matplotlib 기본 스타일 중 하나 사용)
plt.style.use('ggplot')  # 다른 옵션: 'fivethirtyeight', 'bmh', 'classic'

# 그래프 크기 설정
fig, ax = plt.subplots(figsize=(10, 6))

# Sine 그래프: 둥근 점 마커, 굵은 선
ax.plot(x, y_sin, label='Sine', color='dodgerblue',
        linewidth=2.5, marker='o', markersize=5)

# Cosine 그래프: 별표 마커, 점선 스타일
ax.plot(x, y_cos, label='Cosine', color='crimson',
        linewidth=2, linestyle='--', marker='*', markersize=6)

# 제목 및 축 라벨 (LaTeX 수식 포함)
ax.set_title(r'Styled Plot of $y = \sin(x)$ and $y = \cos(x)$',
             fontsize=16, fontweight='bold')
ax.set_xlabel(r'$x$ (radians)', fontsize=14)
ax.set_ylabel(r'$y$', fontsize=14)

# 범례 설정
ax.legend(loc='upper right', fontsize=12, frameon=True)

# 격자 스타일
ax.grid(True, linestyle=':', linewidth=0.8)

# 축 범위 설정
ax.set_xlim(0, 2 * np.pi)
ax.set_ylim(-1.2, 1.2)

# 레이아웃 정리 및 출력
plt.tight_layout()
plt.show()

```

### 📌 2. 다양한 그래프 유형
| 그래프 유형         | 주요 함수                          |
|--------------------|------------------------------------|
| 선 그래프           | plot()                             |
| 막대 그래프         | bar(), barh()                      |
| 파이 차트           | pie()                              |
| 산점도              | scatter()                          |
| 히스토그램          | hist()                             |
| 극좌표 그래프       | subplot(polar=True)                |
| 3D 표면 그래프      | Axes3D.plot_surface()              |

---

### 📌 파일로 저장

- matplotlib에서 생성한 그래프를 이미지 파일로 저장하려면 plt.savefig() 함수를 사용하면 됩니다.  

#### 🔹 기본 저장 방법
```python
import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

plt.plot(x, y)
plt.title('Sine Function')

# 이미지 파일로 저장
plt.savefig('sine_plot.png')  # 현재 작업 디렉토리에 저장
plt.show()
```



#### 🔹 저장 옵션
```python
plt.savefig('sine_plot.png', dpi=300, bbox_inches='tight')
```
| 저장 옵션           | 설명 또는 사용 예시                     |
|--------------------|------------------------------------------|
| '파일명'           | 저장할 파일 이름과 확장자 (.png, .jpg, .pdf, .svg 등) |
| dpi=300            | 이미지 해상도 설정 (인쇄용은 300 이상 추천) |
| bbox_inches='tight'| 그래프 주변 여백 제거하고 깔끔하게 저장     |


#### 🔹 저장 경로 지정
```python
plt.savefig('C:/Users/JungHwan/Desktop/sine_plot.png')
```
- 절대 경로 또는 상대 경로 모두 사용 가능
- 경로에 한글이 포함되어도 대부분 문제 없지만, 폰트 설정은 따로 해주는 게 좋음.


---

### 📌 PDF로 저장

- matplotlib에서는 그래프를 이미지뿐 아니라 PDF 파일로도 저장.  

#### 🔹 PDF로 저장하는 예제
```python
import numpy as np
import matplotlib.pyplot as plt

# 데이터 생성
x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

# 그래프 그리기
plt.plot(x, y, label='Sine', color='blue')
plt.title(r'$y = \sin(x)$')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)

# PDF로 저장
plt.savefig('sine_plot.pdf', format='pdf', dpi=300, bbox_inches='tight')

# 화면에도 출력
plt.show()

```

#### 🔹 저장 옵션 요약
| 저장 옵션           | 설명 또는 사용 예시                     |
|--------------------|------------------------------------------|
| 'sine_plot.pdf'    | 저장할 PDF 파일 이름                     |
| format='pdf'       | 저장 형식 명시 (확장자와 일치하면 생략 가능) |
| dpi=300            | 해상도 설정 (PDF는 벡터 기반이라 영향 적음) |
| bbox_inches='tight'| 여백 없이 그래프만 깔끔하게 저장           |


#### 🔹 팁
- PDF는 벡터 그래픽이라 확대해도 깨지지 않아서 인쇄나 문서 삽입 좋음.
- plt.savefig()는 .svg, .eps, .ps 같은 다른 벡터 포맷도 지원.

---

