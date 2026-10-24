## 📘 Singleton 패턴이란?
- 클래스의 인스턴스를 하나만 생성하도록 보장하는 디자인 패턴.
- 여러 번 객체를 생성해도 항상 같은 인스턴스를 반환함.

### 📌 소스 코드
```python
class Singleton(object):
   @staticmethod
   def __new__(cls, name, age):
        print('Create Object')
        if hasattr(cls, '_instance'):
            instance = cls._instance
        else:
            instance = object.__new__(cls)
            cls._instance = instance
        return instance

   def __init__(self, name, age):
       print('Init Object')
       if hasattr(type(self), '_init'):
           pass
       else:
           self.name = name
           self.age = age
           type(self)._init = True
           
   @classmethod
   def getInstance(cls):
       return cls._instance

a = Singleton('A', 20)
b = Singleton('B', 20)
c = Singleton.getInstance()

print(a.name, a.age, b.name, b.age)
'''A 20 A 20'''

print(a is b)
'''True'''

print(c is b)
'''True'''

```

### 📌 코드 동작 요약
#### 🔹 1. __new__ 메소드
```python
def __new__(cls, name, age):
    if hasattr(cls, '_instance'):
        return cls._instance
    else:
        instance = object.__new__(cls)
        cls._instance = instance
        return instance

```
- 클래스 수준에서 _instance 속성을 확인해 이미 생성된 객체가 있으면 재사용
- 없으면 새로 생성하고 _instance에 저장
  
#### 🔹 2. __init__ 메소드
```python
def __init__(self, name, age):
    if hasattr(type(self), '_init'):
        pass
    else:
        self.name = name
        self.age = age
        type(self)._init = True
```

- __init__은 여러 번 호출될 수 있으므로 _init 플래그로 초기화는 한 번만 수행
#### 🔹 3. getInstance() 클래스 메소드
```python
@classmethod
def getInstance(cls):
    return cls._instance
```
- 클래스 외부에서 인스턴스를 직접 접근할 수 있도록 제공

#### 🔹 실행 결과
```python
a = Singleton('A', 20)
b = Singleton('B', 20)
c = Singleton.getInstance()

print(a.name, a.age, b.name, b.age)  # A 20 A 20
print(a is b)                        # True
print(c is b)                        # True
```

- a, b, c는 모두 같은 객체
- __init__은 최초 한 번만 실행됨

### 📌 Singleton 패턴 실무 활용 포인트

| 활용 요소         | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| 객체 공유         | 설정, DB 연결, 로그 핸들러 등 하나만 존재해야 하는 객체를 전역으로 공유 가능         |
| 메모리 절약       | 객체를 반복 생성하지 않음 → 리소스 절약 및 성능 향상                              |
| 상태 일관성 유지   | 여러 모듈에서 동일 객체를 참조 → 전역 상태 관리에 유리                              |
| `__init__` 제어   | 초기화는 한 번만 수행 → 불필요한 재초기화 방지, 안전한 상태 유지                    |
| 테스트 용이성      | 인스턴스가 하나이므로 테스트 환경에서 상태 추적 및 검증이 쉬움                       |
| 확장 가능 구조     | `getInstance()` 등으로 외부 접근 제어 → 추후 로깅, 캐싱 등 기능 추가에 유리            |

---

## 📘 Single 확장

### 📌 1. Thread-Safe Singleton (멀티스레드 안전)
```python
import threading

class ThreadSafeSingleton:
    _instance = None
    _lock = threading.Lock()

    def __new__(cls, *args, **kwargs):
        with cls._lock:
            if cls._instance is None:
                print("Create Thread-Safe Singleton")
                cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self, name='Default'):
        if not hasattr(self, '_initialized'):
            self.name = name
            self._initialized = True
```

#### 🔹 실무 장점:
- 멀티스레드 환경에서도 안전하게 하나의 인스턴스만 생성됨
- threading.Lock()으로 race condition 방지

### 📌 2. Metaclass 기반 Singleton (구조적으로 깔끔)
```python
class SingletonMeta(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            print("Create Metaclass Singleton")
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]

class MetaSingleton(metaclass=SingletonMeta):
    def __init__(self, name='Default'):
        self.name = name
```

#### 🔹 실무 장점:
- 여러 클래스에 재사용 가능
- 구조적으로 깔끔하고 Pythonic
- __call__ 오버라이딩으로 객체 생성 제어

### 📌 3. Lazy Initialization Singleton (필요할 때만 생성)

```python
class LazySingleton:
    _instance = None

    def __init__(self, name='Lazy'):
        self.name = name

    @classmethod
    def getInstance(cls, name='Lazy'):
        if cls._instance is None:
            print("Create Lazy Singleton")
            cls._instance = cls(name)
        return cls._instance
```

#### 🔹 실무 장점:
- 실제로 필요할 때만 객체 생성됨
- 초기 비용이 큰 객체에 적합 (예: DB 연결, 설정 로딩)

#### 🔹 사용 예시
```python
a = ThreadSafeSingleton('A')
b = ThreadSafeSingleton('B')
print(a is b)  # True

x = MetaSingleton('X')
y = MetaSingleton('Y')
print(x is y)  # True

lazy1 = LazySingleton.getInstance('First')
lazy2 = LazySingleton.getInstance('Second')
print(lazy1.name)  # First
print(lazy2.name)  # First
print(lazy1 is lazy2)  # True
```

---





