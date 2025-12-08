## 🐍 Python의 repr 기능
- repr() 함수는 객체의 **공식적인 문자열 표현** 을 반환합니다.
- 이 표현은 개발자용으로, 디버깅이나 로깅에 적합하게 설계되어 있습니다.
- 보통 repr(obj)의 결과는 그 객체를 다시 생성할 수 있는 코드 형태에 가깝습니다.

## 📌 특징
- repr()은 객체의 __repr__ 메서드를 호출합니다.
- str()과 달리 **사람이 읽기 좋은 문자열(str)** 이 아니라, **개발자가 객체를 식별하기 좋은 문자열(repr)** 을 제공합니다.
- 예를 들어, 문자열은 따옴표까지 포함해서 보여줍니다.

## 🔎 예시
```python
x = "hello"
print(str(x))   # hello
print(repr(x))  # 'hello'
```
```python
y = [1, 2, 3]
print(str(y))   # [1, 2, 3]
print(repr(y))  # [1, 2, 3]   (리스트는 str과 repr이 같음)
```
```python
import datetime
d = datetime.datetime(2025, 12, 8, 14, 50)
print(str(d))   # 2025-12-08 14:50:00
print(repr(d))  # datetime.datetime(2025, 12, 8, 14, 50)
```


## ✅ 요약
- `str()` → 사용자 친화적, 사람이 읽기 좋은 문자열
- `repr()` → 개발자 친화적, 디버깅/재생성 가능한 표현

---

