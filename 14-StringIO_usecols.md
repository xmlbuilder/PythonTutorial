# 📘 np.genfromtxt + StringIO 핵심 정리
## ✅ 1. 특정 열 선택 — usecols
```python
data = u'1 2 3\n4 5 6'
np.genfromtxt(StringIO(data), usecols=(0, -1))
```
### 결론
```
   [[1. 3.]
   [4. 6.]]

```

- usecols=(0, -1) → 첫 번째와 마지막 열 선택
- 음수 인덱스도 사용 가능

## ✅ 2. 열 이름 기반 선택 — names + usecols
```
np.genfromtxt(StringIO(data), names="a, b, c", usecols=('a', 'c'))
```
### 결론
```
    [(1., 3.) (4., 6.)]
```

- names="a, b, c" → 열 이름 지정
- usecols=('a', 'c') → 이름으로 열 선택

## ✅ 3. 구조화된 dtype 생성 — 리스트 컴프리헨션
```
[(_, int) for _ in "abc"]]
```
### 결론
```
    [('a', int), ('b', int), ('c', int)]
```

- 열 이름과 타입을 튜플로 묶어 구조화된 dtype 생성

## ✅ 4. 구조화 배열 생성 — dtype=[...]
```python
np.genfromtxt(StringIO(data), dtype=[(_, int) for _ in "abc"])
```

### 결론
```
[(1, 2, 3) (4, 5, 6)]
```





```python
print(c.dtype)
```

### 결론
```
    [('a', '<i8'), ('b', '<i8'), ('c', '<i8')]
```

- 각 열에 이름과 타입 부여
- 결과는 구조화된 배열

## ✅ 5. 헤더 자동 인식 — names=True
```python
data = StringIO("So it goes\n#a b c\n1 2 3\n4 5 6")
np.genfromtxt(data, skip_header=1, names=True)
```
### 결론
```
    [1., 2., 3.) (4., 5., 6.)]
```

```python
print(d.dtype)
```
### 결론
```
    [('a', '<f8'), ('b', '<f8'), ('c', '<f8')]
```

- skip_header=1 → 첫 줄 건너뜀
- names=True → 두 번째 줄에서 열 이름 자동 추출

## ✅ 6. dtype과 names 직접 지정
```python
ndtype = [('a', int), ('b', int), ('c', int)]
names = ["a", "b", "c"]
np.genfromtxt(StringIO("1 2 3\n4 5 6"), dtype=ndtype, names=names)
```
### 결론
```
    [(1, 2, 3) (4, 5, 6)]
```

- dtype와 names를 명시적으로 지정 가능

## ✅ 7. 튜플 기반 dtype — 자동 필드명
```python
np.genfromtxt(StringIO("1 2 3\n4 5 6"), dtype=(int, float, int))
```
### 결론
```
    [(1, 2., 3) (4, 5., 6)]
```

```python
print(f.dtype)
```

### 결론
```
[('f0', '<i8'), ('f1', '<f8'), ('f2', '<i8')]

```

- 필드명이 자동으로 f0, f1, f2로 생성됨

### ✅ 8. 튜플 기반 dtype + custom 필드명 — defaultfmt
```python
np.genfromtxt(StringIO("1 2 3\n4 5 6"), dtype=(int, float, int), defaultfmt="var_%02i")
```

### 결론
```
[(1, 2., 3) (4, 5., 6)]
```

```python
print(g.dtype)
```

### 결론
```
[('var_00', '<i8'), ('var_01', '<f8'), ('var_02', '<i8')]
```

```python
- defaultfmt="var_%02i" → 필드명 형식 지정
```


## 💡 실무 팁 요약 — np.genfromtxt 주요 옵션

| 옵션         | 기능 설명                              | 실무 활용 예시                       |
|--------------|-----------------------------------------|--------------------------------------|
| usecols      | 열 인덱스 또는 이름으로 선택             | 피처 선택, 열 필터링                 |
| names        | 열 이름 지정 또는 자동 추출              | 구조화 배열 생성, 열 이름 기반 처리  |
| dtype        | 열별 데이터 타입 지정                   | 정수/실수/문자열 혼합 처리           |
| defaultfmt   | 자동 생성되는 필드명 형식 지정           | 튜플 기반 dtype에 커스텀 이름 부여    |
| skip_header  | 헤더 또는 설명 줄 건너뛰기               | 메타데이터 제거, 주석/타이틀 무시     |



## 💬 한마디
np.genfromtxt()는 단순한 텍스트 파싱을 넘어서  
구조화된 데이터셋을 빠르게 만들 수 있는 강력한 도구야.  
특히 usecols, names, dtype 조합은  
실무에서 CSV 전처리, 로그 분석, 피처 선택에 자주 쓰임.

---


# ✅ 목표
```python
np.genfromtxt(StringIO(data), dtype=[(_, int) for _ in "abc"])
```

- 입력 문자열: '1 2 3\n4 5 6'
- 목표: 각 열에 이름과 타입을 부여한 구조화 배열 생성

## 🔍 절차 설명
### ① 입력 문자열 준비
```python
data = u'1 2 3\n4 5 6'
```

- 2행 3열의 숫자 데이터
- 공백으로 구분된 텍스트

### ② dtype 생성
```python
dtype = [(_, int) for _ in "abc"]
```
### 결론
```
[('a', int), ('b', int), ('c', int)]
```
- 열 이름: "a", "b", "c"
- 각 열의 타입: int
- 결과적으로 구조화된 dtype을 생성

### ③ genfromtxt 실행
```python
np.genfromtxt(StringIO(data), dtype=[('a', int), ('b', int), ('c', int)])
```

- StringIO(data) → 문자열을 파일처럼 읽음
- dtype에 따라 각 열에 이름과 타입이 지정됨
- 자동으로 공백을 delimiter로 인식

### ④ 결과: 구조화 배열
```python
array([(1, 2, 3), (4, 5, 6)],
      dtype=[('a', '<i8'), ('b', '<i8'), ('c', '<i8')])
```

- 각 행은 튜플처럼 보이지만 실제로는 구조화된 NumPy 레코드
- 열 이름으로 접근 가능:
x['a'] → array([1, 4])
x['b'] → array([2, 5])
x['c'] → array([3, 6])



### 📘 구조화 배열이란?
- NumPy에서 각 열에 이름과 타입을 지정한 배열  
- 마치 pandas의 DataFrame처럼 열 이름으로 접근 가능  
- 실무에서 이기종 데이터 처리, CSV 파싱, 열별 연산에 유용  

💬 한마디
구조화 배열은 단순한 숫자 배열을 넘어서  
열 이름 기반의 데이터 처리를 가능하게 해줘.  
특히 dtype=[(_, int) for _ in "abc"]는  
반복문 없이 깔끔하게 열 이름과 타입을 지정하는 똑똑한 방식.  


