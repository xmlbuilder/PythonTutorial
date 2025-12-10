# Iterable
## 🔁 Python에서 반복 가능한 객체 만들기
### 1. Iterable이란?
- for 루프에서 사용할 수 있는 객체
- iter(obj)를 호출할 수 있어야 함
- 내부적으로 `__iter__()` 메서드를 구현하고 있어야 함
```python
t = "ABC"
print(hasattr(t, '__iter__'))  # True
```


### 2. Iterator란?
- next()를 호출할 수 있는 객체
- 내부적으로 `__next__()` 메서드를 구현하고 있어야 함
- iter(obj)를 호출하면 iterator가 반환됨
```python
w = iter(t)
print(hasattr(w, '__next__'))  # True
```

### 3. 반복 가능한 타입들
- list, tuple, dict, set, str, file, range, *args, **kwargs, collections 등

### 4. 직접 반복자 만들기
```python
class WordSplitter:
    def __init__(self, text):
        self.words = text.split()
        self.idx = 0

    def __next__(self):
        if self.idx >= len(self.words):
            raise StopIteration
        word = self.words[self.idx]
        self.idx += 1
        return word

    def __iter__(self):
        return self  # 반복자 자체를 반환

    def __repr__(self):
        return ', '.join(self.words)

ws = WordSplitter("Do today what you could do tomorrow")
for word in ws:
    print(word)

```

## ✅ 핵심 요약 (Markdown 표)
| 개념       | 설명                                                         |
|------------|--------------------------------------------------------------|
| Iterable   | `__iter__()` 메서드를 가진 객체. `for` 루프에서 사용 가능.     |
| Iterator   | `__next__()` 메서드를 가진 객체. `next()`로 값 하나씩 반환.     |
| iter(obj)  | 반복 가능한 객체에서 반복자를 생성하는 함수.                  |
| next(obj)  | 반복자에서 다음 값을 꺼내는 함수. `StopIteration`으로 종료됨. |
| 직접 구현  | 클래스에 `__iter__()`와 `__next__()`를 구현하면 반복자 완성.   |

---


## ⚙️ Generator란?
- Generator는 **반복자(iterator)** 를 자동으로 만들어주는 함수입니다.
- yield 키워드를 사용하면 함수가 값을 하나씩 반환하고, 상태를 기억합니다.
- next()를 호출할 때마다 yield 다음 줄부터 다시 실행됩니다.

## 🔁 Generator 함수 예제
```python
def word_generator(text):
    for word in text.split():
        yield word
gen = word_generator("Do today what you could do tomorrow")
print(next(gen))  # Do
print(next(gen))  # today
```

- word_generator는 yield를 사용해 하나씩 단어를 반환합니다.
- next()를 호출하면 다음 단어가 나옵니다.
- 반복이 끝나면 StopIteration 예외가 발생합니다.

## 🔄 for 루프와 함께 사용
```python
for word in word_generator("Do today what you could do tomorrow"):
    print(word)
```

### 출력:
```
Do
today
what
you
could
do
tomorrow
```

## ✅ Generator vs Iterator 비교 요약
| 항목         | Iterator 클래스 방식                    | Generator 함수 방식             |
|--------------|------------------------------------------|----------------------------------|
| 구현 방식    | `__iter__()` + `__next__()` 직접 구현     | `yield` 사용한 함수              |
| 코드 길이    | 길고 복잡할 수 있음                      | 간결하고 직관적임                |
| 상태 저장    | 인덱스 등 수동으로 관리해야 함            | 자동으로 상태 저장됨             |
| 사용 예시    | 복잡한 반복 로직, 사용자 정의 반복자 등   | 간단한 반복, 데이터 스트림 등    |

## 💡 실전 팁
- 파일 읽기, 대용량 데이터 처리, 무한 반복 등에서 Generator가 매우 유용합니다.
- yield from을 사용하면 다른 generator를 위임할 수도 있음.


---

## 🧩 사용자 정의 Iterator 구현 방법
### ✅ 필수 조건
- 클래스에 다음 두 가지 메서드를 구현해야 합니다:
    - `__iter__(self)` → 반복자 객체를 반환
    - `__next__(self)` → 다음 값을 반환, 더 이상 없으면 StopIteration 예외 발생

## 📦 예제: 사용자 정의 숫자 반복기
```python
class MyRange:
    def __init__(self, start, end):
        self.current = start
        self.end = end

    def __iter__(self):
        return self  # 반복자 객체 자신을 반환

    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        value = self.current
        self.current += 1
        return value
```

### 🔍 사용 예
```python
for num in MyRange(1, 5):
    print(num)
```

### 출력:
```
1
2
3
4
```


### 🧠 작동 원리
- for 루프가 `__iter__()` 를 호출 → 반복자 객체 반환
- next()가 `__next__()` 를 호출 → 값 반환
- 값이 없으면 StopIteration 예외 발생 → 루프 종료

## ✅ 요약 (Markdown 표)
| 메서드        | 역할                                      |
|---------------|-------------------------------------------|
| `__iter__()`  | 반복자 객체 반환 (`self`를 반환하는 경우 많음) |
| `__next__()`  | 다음 값을 반환, 없으면 `StopIteration` 발생     |



## 💡 팁
- 상태를 기억해야 하므로 self.current 같은 속성을 사용합니다.
- `__iter__()` 는 보통 self를 반환하지만, 다른 반복자 객체를 반환해도 됩니다.
- StopIteration을 명시적으로 발생시켜야 반복이 종료됩니다.

----


##  🔁 기본적인 yield와 비교
## 일반적인 yield 사용
```python
def gen1():
    yield 1
    yield 2

def gen2():
    yield 'A'
    yield from gen1()
    yield 'B'
```

### 실행 결과
```python
for x in gen2():
    print(x)
```

### 출력:
```
A
1
2
B
```


## 🔍 무슨 일이 일어난 걸까?
- gen2()는 'A'를 먼저 yield
    - 그 다음 yield from gen1() → gen1()의 모든 yield를 자동으로 반복
    - 마지막으로 'B'를 yield
- 즉, yield from gen1()은 다음과 같은 코드와 동일한 효과를 냅니다:
```python
for value in gen1():
    yield value
```

## ✅ 요약: yield from의 의미
| 문법            | 의미                                      |
|-----------------|-------------------------------------------|
| `yield`         | 하나의 값을 반환                          |
| `yield from X`  | X의 모든 값을 반복해서 반환 (`for` 대신)  |



## 💡 실전 활용 예
### 리스트에 위임
```python
def gen():
    yield from [10, 20, 30]
```
- 리스트의 각 요소를 하나씩 yield합니다.

### 중첩된 generator 구조
```python
def subgen():
    yield "sub1"
    yield "sub2"

def main():
    yield "start"
    yield from subgen()
    yield "end"
```

- main()은 subgen()의 모든 값을 포함한 하나의 흐름을 만듭니다.

## 🧠 장점
- 코드가 간결해지고
- 중첩된 generator를 재사용하기 쉬워지고
- return 값을 받을 수도 있음 (PEP 380)

---


