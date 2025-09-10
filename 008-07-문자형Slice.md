# 문자열 슬라이싱
Python의 문자열 슬라이싱과 ASCII 코드 관련 기능

## 샘플 소스
```python

# 슬라이스
str_s1 = "Hi Python"
print(str_s1[:3], str_s1[0:3])
'''Hi  Hi '''

print(str_s1[3:9], str_s1[3:])
'''Python Python'''

print(str_s1[:], str_s1[:len(str_s1)])
'''Hi Python Hi Python'''

print(str_s1[1:4:2])
'''iP'''

print(str_s1[-6:])
'''Python'''

print(str_s1[1:-2])
'''i Pyth'''

print(str_s1[::2])
'''H yhn'''

print(str_s1[::-1])
'''nohtyP iH'''

# Ascii Code (또는 유니코드)
a = 'z'
print(ord(a))  # 아스키 코드로
'''122'''

print(chr(122))  # 문로
'''z'''
```

## 🔪 문자열 슬라이싱 요약
| 표현               | 설명                          | 결과             |
|--------------------|-------------------------------|------------------|
| `str_s1[:3]`       | 처음부터 인덱스 3 전까지       | `'Hi '`          |
| `str_s1[3:9]`      | 인덱스 3부터 9 전까지          | `'Python'`       |
| `str_s1[3:]`       | 인덱스 3부터 끝까지            | `'Python'`       |
| `str_s1[:]`        | 전체 문자열                    | `'Hi Python'`    |
| `str_s1[1:4:2]`    | 인덱스 1부터 4 전까지, 2칸씩   | `'iP'`           |
| `str_s1[-6:]`      | 뒤에서 6번째부터 끝까지        | `'Python'`       |
| `str_s1[1:-2]`     | 인덱스 1부터 뒤에서 두 번째 전까지 | `'i Pyth'`   |
| `str_s1[::2]`      | 처음부터 끝까지, 2칸씩 건너뛰며 | `'H yhn'`        |
| `str_s1[::-1]`     | 문자열 뒤집기                  | `'nohtyP iH'`    |



### 🔤 ASCII 코드 변환
```python
a = 'z'
print(ord(a))   # 122
print(chr(122)) # 'z'
```


### 🔤 ASCII/유니코드 변환 함수 요약

| 함수     | 설명                     | 예시 결과           |
|----------|--------------------------|----------------------|
| `ord()`  | 문자 → 유니코드(정수) 값 | `ord('z')` → `122`   |
| `chr()`  | 유니코드(정수) 값 → 문자 | `chr(122)` → `'z'`   |


### 📌 슬라이싱 팁:
- str[start:end]는 start부터 end-1까지를 포함합니다.
- str[start:end:step]에서 step은 건너뛰는 간격을 의미합니다.
- 음수 인덱스(-1, -2 등)는 뒤에서부터 접근할 때 사용합니다.
