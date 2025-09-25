🧠 클래스 데코레이터란?
클래스 데코레이터는 클래스를 인자로 받아서 수정하거나 확장한 후 반환하는 함수입니다.  
함수 데코레이터처럼 @decorator 문법을 사용하지만, 대상이 함수가 아니라 클래스라는 점이 다릅니다.
```python
@decorator
class MyClass:
    ...
```

이렇게 하면 MyClass = decorator(MyClass)가 실행되는 것과 동일한 효과를 가집니다.

## 🔍 예제 분석
### 1. 데코레이터 정의
```python
def decorator(cls):
    def wrapper(self, name):
        self.name = name
    cls.__init__ = wrapper
    return cls
```

- decorator(cls)는 클래스를 인자로 받습니다.
- 내부에서 wrapper(self, name)라는 새로운 __init__ 메서드를 정의하고,
- 원래 클래스의 __init__을 이 wrapper로 덮어씌웁니다.
- 즉, 클래스가 인스턴스화될 때 self.name = name만 수행하게 됩니다.

### 2. DecoratedClass 사용
```python
@decorator
class DecoratedClass:
    def method(self):
        return self.name

dec = DecoratedClass("jhjeong")
print(dec.method())  # 출력: jhjeong
```

- DecoratedClass는 데코레이터에 의해 __init__이 self.name = name으로 바뀌었습니다.
- method()는 self.name을 반환하므로 "jhjeong"이 출력됩니다.

### 3. Klass 사용
```python
@decorator
class Klass:
    pass

k = Klass("jhjeong")
print(k.__dict__)  # 출력: {'name': 'jhjeong'}
```

- Klass는 아무 메서드도 없지만, 데코레이터 덕분에 __init__이 생겼습니다.
- self.name = name이 실행되어 인스턴스에 name 속성이 생깁니다.

## ✅ 요약
| 항목           | 설명                             |
|----------------|----------------------------------|
| 데코레이터 대상 | `cls`                            |
| 주요 기능      | `__init__`에서 `self.name = name` |
| 효과           | 인스턴스에 `name` 속성이 추가됨   |


## 💡 주의할 점
- 원래 클래스의 __init__이 사라지므로, 기존 초기화 로직이 있다면 덮어쓰기 위험이 있습니다.


