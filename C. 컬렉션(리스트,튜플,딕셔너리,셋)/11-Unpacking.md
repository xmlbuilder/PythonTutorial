# Python unpacking with asterisk
파이썬의 `*` 와 `**` 는 **언패킹(unpacking)** 을 위해 쓰입니다.  
`*` 는 반복 가능한 객체(리스트, 튜플 등)의 요소를 펼치고, `**` 는 딕셔너리의 키-값을 펼칩니다.  
함수 호출, 변수 할당, 컨테이너 리터럴에서 모두 활용됩니다.

## Positional unpacking with *
```python
nums = [1, 2, 3]
print(*nums)          # 1 2 3   (공백으로 구분되어 출력)
print([*nums, 4, 5])  # [1, 2, 3, 4, 5]
```
- 함수 호출: f(*iterable)은 iterable의 요소를 개별 인자로 전달합니다.
- 컨테이너 결합: 리스트/튜플 리터럴에서 *로 다른 컨테이너를 펼쳐 결합할 수 있습니다.
```python
a = [1, 2]
b = (3, 4)
merged = [*a, *b, 5]    # [1, 2, 3, 4, 5]
t = (*a, *b)            # (1, 2, 3, 4)
```
## Keyword unpacking with **
```python
def greet(name, lang='ko', polite=False): ...
opts = {'lang': 'en', 'polite': True}
greet('JungHwan', **opts)  # greet(name='JungHwan', lang='en', polite=True)
```
- 함수 호출: f(**mapping)은 딕셔너리의 키를 파라미터 이름으로, 값을 인자로 전달합니다.
- 딕셔너리 병합: 파이썬 3.5+부터 딕셔너리 리터럴에서 **로 병합 가능합니다.
```python
d1 = {'a': 1, 'b': 2}
d2 = {'b': 99, 'c': 3}
merged = {**d1, **d2}   # {'a': 1, 'b': 99, 'c': 3} (뒤가 덮어씀)
```
## Iterable unpacking on the left-hand side
변수 할당의 좌변에서도 *를 사용할 수 있습니다. **남는 요소** 를 하나의 리스트로 받는 문법입니다.
```python
a, b = [10, 20]              # 기본 시퀀스 언패킹
head, *mid, tail = [1, 2, 3, 4, 5]
```
```
# head=1, mid=[2, 3, 4], tail=5
```
```python
*prefix, last = 'abcde'
```
```
# prefix=['a','b','c','d'], last='e'
```
- 좌변 규칙: 좌변은 반드시 **시퀀스 패턴** 이어야 합니다(콤마로 분리된 대상이나 []/() 사용).
- 단일 변수에 `*` 만 쓰기: *s, = 'abcde'처럼 **꼬리 콤마** 로 1-튜플 패턴을 만들면 s가 전체를 리스트로 받습니다.
- `*s, = 'abcde'` → `s == ['a','b','c','d','e']`
- `*s = 'abcde'` 는 `문법 오류` 입니다(좌변이 시퀀스 패턴이 아님).

## Function definitions: *args and **kwargs
```
def f(*args, **kwargs):
    # args: 튼튼한 튜플(모든 위치 인자)
    # kwargs: 딕셔너리(모든 키워드 인자)
    ...
```

- 가변 인자 수용: 인자 개수를 미리 모를 때 유용합니다.
- 호출 시 언패킹과 조합: f(*[1,2], **{'x':3})처럼 호출 측에서 데이터 구조를 바로 펼칠 수 있습니다.

## Common patterns
- 리스트/튜플 슬라이스 대체: first, *rest = seq로 첫 요소와 나머지를 분리.
- 컨테이너 평탄화: [*it1, *it2, *it3]로 여러 시퀀스를 하나로 결합.
- 딕셔너리 오버라이드: {**base, **override}로 기본 설정을 덮어쓰기.
- 인자 전달 래핑: 래퍼 함수가 내부 함수에 인자 전달할 때 *args, **kwargs 그대로 전달.

## Pitfalls and gotchas
- 좌변에 여러 개의 * 사용 불가: 한 할당 패턴에 *는 하나만 허용됩니다.
- 리스트가 아닌 리스트-유사: *iterable은 반복 가능한 객체면 OK. 단, 좌변 언패킹은 길이와 패턴이 맞아야 합니다.
- 딕셔너리 ** 키 충돌: 뒤에 오는 **가 앞의 키를 덮어씁니다. 의도 확인 필요.
- 성능 고려: 대형 시퀀스를 반복해서 언패킹/머지하면 메모리 복사가 발생합니다. 제너레이터나 itertools.chain도 고려.
```
import itertools
combined = itertools.chain([1,2], (3,4), range(5,7))  # 지연 평가로 효율적
```


## Quick reference
- 함수 호출: f(*seq), f(**dict)
- 컨테이너 리터럴: [*a, *b], {**d1, **d2}
- 좌변 할당: a, *b, c = iterable
- 함수 정의: def f(*args, **kwargs): ...

---

# itertools 사용 방법
## 🔑 사용 방법
### 1. 반복문에서 사용

```python
import itertools

combined = itertools.chain([1,2], (3,4), range(5,7))

for x in combined:
    print(x)
```

### 출력:
```
1
2
3
4
5
6
```
- 👉 combined는 이터레이터라서 한 번 순회하면 소진됩니다. 다시 쓰려면 새로 만들어야 합니다.

### 2. 리스트로 변환
```python
list(combined)   # [1, 2, 3, 4, 5, 6]
```
- 👉 한 번에 모든 요소를 메모리에 올려서 사용할 수 있습니다.

### 3. 다른 함수와 함께 사용
이터레이터이므로 sum, max, min, sorted 같은 함수에 바로 전달할 수 있습니다.
```python
sum(combined)       # 합계
max(combined)       # 최댓값
sorted(combined)    # 정렬된 리스트
```
### 4. 체인 연결 응용
여러 데이터 소스를 하나로 합쳐서 처리할 때 유용합니다.
```python
logs1 = ["logA", "logB"]
logs2 = ["logC"]
logs3 = ["logD", "logE"]
for log in itertools.chain(logs1, logs2, logs3):
    print(log)
```

### 출력:
```
logA
logB
logC
logD
logE
```
## ⚠️ 주의할 점
- combined는 이터레이터라서 한 번만 순회 가능합니다.
- 재사용하려면 list(combined)로 변환하거나, itertools.tee로 복제해야 합니다.

---

