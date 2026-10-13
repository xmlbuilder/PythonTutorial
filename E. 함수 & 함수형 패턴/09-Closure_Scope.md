## 📘 Closure / Scope
- 클로저와 변수 스코프 핵심 요약
- 외부에서 호출된 함수의 변수값, 상태(레퍼런스) 복사 후 저장 → 후에 접근 가능


### 📌 closure_ex1: 리스트는 참조로 캡처됨
```python
def closure_ex1():
    series = []
    def averager(v):
        series.append(v)
        print("inner >>> {} / {}".format(series, len(series)))
        return sum(series) / len(series)
    return averager

averager = closure_ex1()
print(averager(10))  # 10.0
print(averager(20))  # 15.0
print(averager(30))  # 20.0
print(averager(40))  # 25.0
```

- series는 리스트 → 참조형 객체
- 클로저 내부에서 append()는 가능하지만, series = []처럼 재할당은 불가
- 내부 구조 확인:
```python
print(averager.__code__.co_freevars)         # ('series',)
print(averager.__closure__[0].cell_contents) # [10, 20, 30, 40]
```


#### 🔹 closure_ex2: 숫자는 재할당 시 UnboundLocalError
```python
def closure_ex2():
    cnt = 0
    total = 0
    def averager(v):
        cnt += 1
        total += v
        return total / cnt
    return averager

# averager2 = closure_ex2()
# print(averager2(10))  # Error!
```

- cnt, total은 불변 객체(int)
- 내부에서 += 연산은 재할당으로 간주 → Python은 이를 지역 변수로 판단
- nonlocal 없으면 UnboundLocalError 발생

#### 🔹 closure_ex3: nonlocal로 상위 스코프 변수 수정
```python
def closure_ex3():
    cnt = 0
    total = 0
    def averager(v):
        nonlocal cnt, total
        cnt += 1
        total += v
        return total / cnt
    return averager

averager3 = closure_ex3()
print(averager3(10))  # 10.0
print(averager3(20))  # 15.0

```

- nonlocal 키워드로 상위 함수의 지역 변수임을 명시
- 클로저 내부에서 재할당 가능
- Python의 클로저는 읽기만 할 땐 자유롭지만, 수정하려면 명시적 제어가 필요

### 📌 결론: Python 클로저 핵심 요약

| 항목               | 키워드 또는 구조                     | 설명 |
|--------------------|--------------------------------------|------|
| 상위 변수 수정 필요 | `nonlocal`                          | 상위 함수의 지역 변수에 재할당하려면 필요 |
| 불변 객체 캡처     | `nonlocal`                          | 숫자, 문자열 등은 수정 시 반드시 필요 |
| 클로저 내부 구조   | `__code__.co_freevars`, `__closure__` | 캡처된 변수와 값 확인 가능 |

---



