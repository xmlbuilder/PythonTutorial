🐼 Pandas 실무 종합 요약
1. 📘 기본 개념

| 항목            | 설명                                                         |
|-----------------|--------------------------------------------------------------|
| Pandas          | 파이썬 기반의 데이터 분석 및 가공 라이브러리                 |
| DataFrame       | 2차원 자료구조 (행 + 열), 엑셀과 유사한 구조                 |
| Series          | DataFrame의 각 열을 구성하는 1차원 객체                      |
| Numpy 기반      | 빠른 연산 처리 가능, Pandas 내부에서 Numpy를 활용함          |
| 실무 활용 분야  | 통계 분석, 머신러닝 전처리, 데이터 시각화, 파일 입출력 등     |




2. 📂 파일 불러오기 — 주요 옵션 요약

| 옵션            | 설명                                                         |
|-----------------|--------------------------------------------------------------|
| read_csv()      | CSV, TXT 등 다양한 포맷의 파일을 불러오는 기본 함수          |
| header=None     | 파일에 컬럼 헤더가 없을 경우, 첫 줄을 데이터로 처리함         |
| names=[]        | 컬럼 이름을 직접 지정할 때 사용                               |
| delimiter="\t"  | 탭으로 구분된 파일을 불러올 때 사용 (기본은 쉼표 `,`)         |




3. 🧱 데이터프레임 생성 — 주요 방식 요약

| 생성 방식                  | 설명                                                         |
|---------------------------|--------------------------------------------------------------|
| pd.DataFrame(dict)        | 딕셔너리를 기반으로 생성, 키가 컬럼 이름, 값이 데이터 리스트 |
| pd.DataFrame.from_records() | 리스트 기반 행(row) 중심 생성, 컬럼 이름은 별도 지정 가능     |
| pd.DataFrame.from_dict()  | 딕셔너리 기반 생성, `orient` 옵션으로 행/열 방향 지정 가능     |
| pd.DataFrame.from_items() | 리스트 기반 컬럼 중심 생성 방식 (⚠️ deprecated)              |


# 딕셔너리 기반
pd.DataFrame({'name': ['John', 'Jenny'], 'age': [20, 30]})

# 레코드(행) 기반
pd.DataFrame.from_records([['John', 20], ['Jenny', 30]], columns=['name', 'age'])

# from_items 방식 (사용 지양)
pd.DataFrame.from_items([['name', ['John', 'Jenny']], ['age', [20, 30]]])



4. 🔍 데이터 선택 및 필터링 — 주요 방식 요약

| 선택/필터 방식             | 설명                                                         |
|----------------------------|--------------------------------------------------------------|
| df[1:3], df.loc[[0,2]]     | 행(Row) 선택 — 슬라이싱 또는 특정 인덱스 지정               |
| df[['name', 'age']], iloc[:,[0,2]] | 열(Column) 선택 — 컬럼 이름 또는 인덱스로 선택         |
| df[df.age > 25], df.query('age > 25') | 조건 필터링 — 특정 조건을 만족하는 행만 선택     |
| df.filter(like='a'), df.filter(regex='b$', axis=1) | 컬럼 이름 기반 필터링 — 문자열 포함 또는 정규식 |


df[1:3]                  # 행 1~2 선택
df.loc[[0,2]]            # 행 0, 2 선택
df[['name', 'age']]      # 'name', 'age' 컬럼 선택
df.iloc[:, [0,2]]        # 컬럼 인덱스 0, 2 선택
df[df.age > 25]          # age가 25보다 큰 행 선택
df.query('age > 25')     # 쿼리 방식 조건 필터링
df.filter(like='a')      # 컬럼 이름에 'a' 포함된 컬럼 선택
df.filter(regex='b$', axis=1)  # 'b'로 끝나는 컬럼 선택


5. 🧹 드롭 및 정제 — 주요 기능 요약

| 기능                  | 설명                                                         |
|-----------------------|--------------------------------------------------------------|
| df.drop(['John'])     | 특정 행(인덱스 이름 또는 번호)을 제거                        |
| df.drop(index)        | 인덱스 번호 기반으로 행 제거                                 |
| df.drop('age', axis=1)| 특정 열(Column)을 제거                                       |
| df[df.age != 30]      | 조건 필터링으로 특정 값 제외                                 |
| df.duplicated()       | 중복 여부 확인 (True/False 반환)                             |
| df.drop_duplicates()  | 중복된 행 제거                                               |


df.drop(['John'])                     # 'John' 인덱스 제거
df.drop(df.index[[0, 2]])             # 인덱스 번호 0, 2 제거
df.drop('age', axis=1)                # 'age' 컬럼 제거
df[df.age != 30]                      # age가 30이 아닌 행만 남김
df.duplicated(['name'])               # name 기준 중복 여부 확인
df.drop_duplicates(['name'], keep='last')  # name 기준 중복 제거, 마지막 값 유지




6. ➕ 컬럼 추가 및 변경 — 주요 방식 요약

| 방식                          | 설명                                                         |
|-------------------------------|--------------------------------------------------------------|
| df['salary'] = 0              | 새로운 컬럼을 기본값으로 추가                                |
| np.where(df['job'] != 'student', 'yes', 'no') | 조건에 따라 값 지정 (NumPy 활용)         |
| df['total'] = df['midterm'] + df['final']    | 기존 컬럼을 연산하여 새로운 컬럼 생성     |
| df['grade'] = grades          | 리스트를 기반으로 컬럼 값 지정                              |

df['salary'] = 0  # 모든 행에 0 할당

df['salary'] = np.where(df['job'] != 'student', 'yes', 'no')  # 조건 기반

df['total'] = df['midterm'] + df['final']  # 점수 합산

grades = ['A', 'B', 'F']
df['grade'] = grades  # 리스트 기반 직접 할당




7. 🧠 apply / map / applymap — 함수 적용 방식 요약

| 함수          | 적용 대상               | 설명                                                         |
|---------------|--------------------------|--------------------------------------------------------------|
| apply()       | Series 또는 DataFrame     | 행 또는 열 단위로 함수 적용 (`axis=0` 또는 `axis=1`)         |
| map()         | Series만                 | 각 원소에 함수 또는 딕셔너리 적용 (단일 컬럼 처리에 적합)     |
| applymap()    | DataFrame 전체           | 모든 셀에 함수 적용 (셀 단위 연산, 전체 값 변경에 적합)       |


# apply() — 행 단위 처리
df['grade'] = df['grade'].apply(lambda x: 'Pass' if x != 'F' else 'Fail')

# map() — 딕셔너리 기반 값 변경
df['job'] = df['job'].map({'student': 1, 'developer': 2, 'teacher': 3})

# applymap() — 전체 셀 반올림
df = df.applymap(np.around)


8. 📊 그룹화 및 통계 — 주요 함수 요약

| 함수/기능         | 설명                                                         |
|-------------------|--------------------------------------------------------------|
| groupby()         | 특정 컬럼 기준으로 데이터를 그룹화                           |
| .size()           | 각 그룹의 행 개수 계산                                        |
| .reset_index()    | 그룹 결과를 일반 데이터프레임 형태로 변환                    |
| value_counts()    | Series에서 각 고유값의 개수를 계산                           |
| unique()          | 중복 없이 고유값 리스트 반환                                  |


df.groupby('major').size().reset_index(name='count')  # 전공별 학생 수

df['job'].value_counts()  # 직업별 빈도

df['job'].unique()        # 직업 종류 목록


9. 🧼 결측값 처리 — 주요 함수 요약

| 함수/기능               | 설명                                                         |
|--------------------------|--------------------------------------------------------------|
| isna(), isnull()         | 결측값(NaN 또는 None) 여부 확인 (True/False 반환)            |
| fillna()                 | 결측값을 지정한 값으로 채움                                  |
| groupby().transform()    | 그룹별 통계(평균, 중앙값 등)를 기반으로 결측값 채움          |

df.isna()                     # NaN 여부 확인
df['age'] = df['age'].fillna(0)  # age 컬럼의 NaN을 0으로 채움

# 그룹별 중앙값으로 채우기
df['age'].fillna(df.groupby('job')['age'].transform('median'), inplace=True)


10. 🔗 병합 및 결합 — 주요 방식 요약

| 방식                              | 설명                                                         |
|-----------------------------------|--------------------------------------------------------------|
| pd.concat([df1, df2], ignore_index=True) | 두 데이터프레임을 행(Row) 기준으로 병합 (인덱스 재정렬)     |
| pd.concat([df1, df2], axis=1)    | 두 데이터프레임을 열(Column) 기준으로 병합                   |
| pd.DataFrame({'label': l1, 'prediction': l2}) | 두 리스트를 컬럼으로 묶어 데이터프레임 생성         |


# 행 기준 병합
result = pd.concat([df1, df2], ignore_index=True)

# 열 기준 병합
result = pd.concat([df1, df2], axis=1)

# 리스트 기반 생성
comparison = pd.DataFrame({
    'label': [1, 2, 3],
    'prediction': [1, 2, 2]
})




💬 Copilot 한마디
이 자료는 Pandas의 입문부터 실무까지 모든 핵심 기능을 망라한 완성형 가이드야.
슬라이드, 튜토리얼, PDF, 강의자료로도 확장 가능하고
실무에서 바로 써먹을 수 있는 예제 중심으로 구성되어 있어.
다음으로는 merge, pivot_table, groupby().agg(), 시각화까지 확장해볼 수 있어!


