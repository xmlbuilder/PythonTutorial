# None / bool

## 🌀 None과 NoneType
- None은 Python에서 값이 없음을 나타내는 객체.
- type(None)을 출력하면 <class 'NoneType'>이 나오는데, 이는 None이 NoneType 클래스의 유일한 인스턴스라는 뜻.
- None.__bool__()은 False를 반환합니다. 즉, None은 조건문에서 False처럼 작동.

```python
if None:
    print("실행됨")  # 실행되지 않음
```


## ✅ bool 타입과 __bases__
- bool은 Python의 불리언 타입으로, True와 False 두 값만 가질 수 있음.
- bool.__bases__를 출력하면 (<class 'int'>,)가 나오는데, 이는 bool이 int를 상속받은 클래스라는 뜻.  
    - 즉, True와 False는 사실상 숫자 1과 0처럼 동작합니다:
```python
print(True + 1)  # 2
print(False * 10)  # 0
```

- 이런 특성 덕분에 bool 값은 수치 연산에서도 자연스럽게 사용할 수 있음.

## 🔍 정리하면
| 값     | 타입        | 불리언 값 | 수치 값 |
|--------|-------------|------------|----------|
| `None` | `NoneType`  | `False`    | —        |
| `True` | `bool` (`int` 상속) | `True`     | `1`       |
| `False`| `bool` (`int` 상속) | `False`    | `0`       |


---


