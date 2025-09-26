# id & is

## 🧠 변수와 객체 ID (id() 함수)
Python에서 변수는 **객체를 참조하는 이름(label)**일 뿐입니다. 실제 값은 메모리에 객체로 존재하고, 변수는 그 객체의 **참조(reference)**를 가리킵니다.

### 🔍 예시 분석
```python
n = 777
m = n
print(id(n), id(m))  # 같은 객체를 참조
```

- m = n은 n이 참조하는 객체를 m도 참조하게 함
- id(n) == id(m) → True (같은 객체)

```python
n = 700
m = 700
print(id(n), id(m))  # 여전히 같은 객체
```

- Python은 작은 정수 객체를 내부적으로 캐싱합니다 (보통 -5 ~ 256)
- 700도 일부 구현에서는 같은 객체로 처리될 수 있음
```python
m = 123.45
n = 123.45
print(id(m), id(n))  # 부동소수점도 같은 객체일 수 있음
```

- 부동소수점은 캐싱되지 않지만, 같은 리터럴을 사용하면 컴파일러 최적화로 인해 같은 객체가 될 수 있음

### 🧾 변수 선언 스타일

| 스타일 이름 | 용도 | 예시 |
|-------------|------|------|
| Camel Case  | 메서드, 일반 변수 | `numberOfCollegeGraduates` |
| Pascal Case | 클래스 이름 | `NumberOfCollegeGraduates` |
| Snake Case  | 함수, 변수 | `number_of_college_graduates` |



### 🚫 예약어 (Reserved Keywords)
Python에는 문법적으로 특별한 의미를 가진 단어들이 있으며, 변수명으로 사용할 수 없습니다.
❗ 사용 불가 예시
```python
for = 1      # ❌ SyntaxError
class = 3    # ❌ SyntaxError
```


### ✅ 예약어 목록
```python
False, def, if, raise,
None, del, import, return,
True, elif, in, try,
and, else, is, while,
as, except, lambda, with,
assert, finally, nonlocal, yield,
break, for, not,
class, from, or, continue, global, pass
```

### 👉 이 목록은 keyword 모듈을 통해 확인할 수 있어요:
```python
import keyword
print(keyword.kwlist)
```


## 📌 요약
- id()는 객체의 고유 메모리 주소를 반환
- 변수는 객체를 참조하는 이름일 뿐
- Python은 일부 객체(작은 정수 등)를 캐싱하여 메모리 효율을 높임
- 변수명은 스타일에 따라 목적이 다름 (클래스, 함수, 일반 변수 등)
- 예약어는 절대 변수명으로 사용 불가
---

