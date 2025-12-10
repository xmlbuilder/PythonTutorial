## 🧠 클래스 접근 연산자 요약

### ✅ `__dict__`
- 인스턴스 또는 클래스의 속성 저장소를 딕셔너리 형태로 보여줍니다.
- 인스턴스: `a.__dict__` → 인스턴스에 직접 설정된 속성들
- 클래스: `Attribute.__dict__` → 클래스 정의에 포함된 속성들

### ✅ setattr(obj, name, value)
- 객체에 속성을 동적으로 추가합니다.
    - 예: setattr(a, "name", "jhjeong") → a.name = "jhjeong"과 동일

### ✅ getattr(obj, name)
- 객체에서 속성 값을 동적으로 조회합니다.
    - 예: getattr(a, "name") → a.name과 동일

### ✅ hasattr(obj, name)
- 객체에 해당 속성이 존재하는지 여부를 확인합니다.
    - 예: hasattr(a, "name") → True 또는 False

### ✅ delattr(obj, name)
- 객체에서 해당 속성을 삭제합니다.
    - 예: delattr(a, "name") → del a.name과 동일

### 🔧 클래스에 메서드 동적 추가
``` python
def __init__(self, name):
    self.name = name

setattr(Attribute, "__init__", __init__)
```

- 클래스 정의 이후에도 setattr로 메서드를 추가할 수 있습니다.
- 이후 Attribute("Init Name")처럼 생성자 호출이 가능해집니다.

## 📘 요약 테이블
| 연산자/함수     | 역할                                | 예시                                |
|----------------|-------------------------------------|-------------------------------------|
| `__dict__`     | 속성 저장소 딕셔너리                 | `a.__dict__`, `Attribute.__dict__` |
| `setattr`      | 속성 동적 추가                       | `setattr(a, "name", "jhjeong")`     |
| `getattr`      | 속성 동적 조회                       | `getattr(a, "name")`                |
| `hasattr`      | 속성 존재 여부 확인                  | `hasattr(a, "name")`                |
| `delattr`      | 속성 동적 삭제                       | `delattr(a, "name")`                |

### 참고 소스
```python
class Attribute:
    pass

a = Attribute()
print(a.__dict__)
```
```
{}
```
```python
setattr(a, "name", "jhjeong")

print(a.__dict__)
```
```
{'name': 'jhjeong'}
```
```python
print(getattr(a, 'name'))
```
```
jhjeong
```
```python
if hasattr(a, 'name'):
    delattr(a, 'name')
print(a.__dict__)
```
```
{}
```
```python
def __init__(self, name):
    self.name = name

setattr(Attribute, "__init__", __init__)

print(Attribute.__init__)
```
```
<function __init__ at 0x00000140CFF8A0C0>
```
```python
print(Attribute.__dict__)
```
```
{'__module__': '__main__', 
'__dict__': <attribute '__dict__' of 'Attribute' objects>, 
'__weakref__': <attribute '__weakref__' of 'Attribute' objects>, 
'__doc__': None, 
'__init__': <function __init__ at 0x000001F9D827A0C0>}
```
```python
aa = Attribute("Init Name")
print(aa.__dict__)
```
```
{'name': 'Init Name'}
```

---
