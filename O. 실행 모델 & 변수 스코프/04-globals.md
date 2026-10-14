## 📘 globals()
- Python의 **globals()** 는 초보자도 금방 이해할 수 있음
- 깊게 파고들면 꽤 흥미로운 개념.

### 📌 globals()란 무엇인가
- globals()는 현재 전역(global) 네임스페이스에 존재하는 모든 이름(name)과 그 값(value)을 담은 딕셔너리를 반환하는 함수.
- 쉽게 말하면:
    - 현재 파이썬 파일(또는 모듈) 전체에서 접근 가능한 변수, 함수, 클래스 등을 한 번에 보여주는 함수


### 📌 예시로 이해하기
```python
x = 10

def foo():
    return "hello"

print(globals())
```

- 출력되는 딕셔너리에 포함되는 내용:
    - 전역 변수 x
    - 함수 foo
    - 모듈 이름 __name__
    - 내장된 여러 시스템 변수들 (__file__, __package__ 등)

### 📌 왜 딕셔너리일까?
- 전역 네임스페이스는 내부적으로 딕셔너리 형태로 관리되기 때문.
- 그래서 globals()는 그 딕셔너리를 그대로 보여주는 것 임.

### 📌 globals()를 언제 사용할까?
- 1) 동적으로 변수 만들 때
```python
for i in range(3):
    globals()[f"var{i}"] = i

print(var0, var1, var2)
```

- 2) 전역 변수 접근/수정
    - 함수 안에서 전역 변수를 직접 수정하고 싶을 때:
```python
x = 10

def change():
    globals()['x'] = 99

change()
print(x)  # 99
```

- 3) 디버깅할 때
    - 현재 어떤 전역 이름들이 있는지 확인할 때 유용.
---

