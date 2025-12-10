# iterator와 genertor 결합

- iterator와 generator 패턴을 결합한 구조로, Python의 메모리 효율성과 반복 제어를 잘 보여주는 예제입니다.
- 아래에 핵심 개념과 동작 원리를 정리.

## 🔁 Iterator + Generator 결합 구조
### ✅ 핵심 구성
```python
class WordSplitterGenerator:
    def __init__(self, words):
        self.words = words.split(' ')  # 내부 데이터 준비

    def __iter__(self):
        for word in self.words:
            yield word  # generator로 반복자 구현

```
- `__iter__()` 가 generator 함수로 동작
- `yield` 를 사용해 하나씩 값을 반환
- `iter(wg)` 를 호출하면 generator 객체가 생성됨

## 🧠 동작 흐름
- wg = WordSplitterGenerator(...) → 객체 생성
- wt = iter(wg) → `__iter__()` 호출 → generator 객체 반환
- next(wt) → generator 내부의 yield 실행 → 단어 하나 반환
- 반복 끝나면 StopIteration 예외 발생

## ✅ 이 구조의 장점
| 장점                     | 설명                                      |
|--------------------------|-------------------------------------------|
| 메모리 효율              | 전체 데이터를 리스트로 만들지 않고 하나씩 처리 |
| `__iter__()` + `for` 루프 | 반복자 프로토콜을 만족해 `for`에서 바로 사용 가능 |
| `yield` 사용              | 상태를 유지하며 중단/재개 가능, 코드 간결화     |
| 지연 실행 (Lazy Evaluation) | 필요한 순간에만 값을 생성, 성능 최적화         |
| 확장성                   | 다른 iterable과 쉽게 결합 (`zip`, `map` 등)   |


## 💡 확장 아이디어
- `__next__()` 를 직접 구현하면 더 정교한 iterator 제어 가능
- yield from을 사용하면 다른 generator에 위임 가능
- enumerate, zip, map 등과 함께 사용하면 강력한 데이터 흐름 구성 가능

🔍 예외 처리 팁
```python
try:
    print(next(wt))
except StopIteration:
    print("모든 단어를 다 꺼냈습니다.")
```
- StopIteration은 반복이 끝났다는 신호이므로, 정상적인 종료입니다.

---



