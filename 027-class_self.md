# class self
Python 클래스에서 self의 역할, 클래스 변수와 인스턴스 변수의 차이, 그리고 네임스페이스의 동작. 
아래에 핵심 개념을 정리하고, 예제 분석을 통해 실무적인 이해.

## 🧠 핵심 개념 요약
| 개념             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| self             | 인스턴스 자신을 가리키는 예약어. 메서드 호출 시 자동으로 전달됨         |
| 클래스 변수       | 클래스 전체에서 공유되는 변수. 모든 인스턴스가 접근 가능                 |
| 인스턴스 변수     | 각 객체마다 별도로 존재하는 변수. `self`를 통해 정의됨                   |
| 네임스페이스      | 객체 내부에 변수들이 저장되는 공간. `__dict__`로 확인 가능                |



## 🧪 예제 1: self의 역할과 메서드 호출 방식
```python
class SelfTest:
    def func():  # self 없음 → 클래스 메서드처럼 동작
        print("Func1 called")

    def func2(self):  # self 있음 → 인스턴스 메서드
        print(id(self))
        print("Func2 called")
```

## 🧪 호출 방식 비교
| 호출 방식           | 설명                                                             |
|---------------------|------------------------------------------------------------------|
| `f.func()`          | ❌ 오류 발생: `func()`은 self 인자가 없는데 인스턴스에서 호출됨     |
| `SelfTest.func()`   | ✅ 정상 호출: 클래스에서 직접 호출, self 없이 정의된 메서드         |
| `f.func2()`         | ✅ 정상 호출: 인스턴스에서 호출, self 자동 전달됨                  |
| `SelfTest.func2(f)` | ✅ 정상 호출: 클래스에서 직접 호출, self를 수동으로 전달함          |
| `SelfTest.func2()`  | ❌ 오류 발생: self 인자가 없어서 호출 실패                         |



## 🏭 예제 2: 클래스 변수 vs 인스턴스 변수
```python
class Warehouse:
    stock_num = 0  # 클래스 변수

    def __init__(self, name):
        self.name = name  # 인스턴스 변수
        Warehouse.stock_num += 1

    def __del__(self):
        Warehouse.stock_num -= 1
```

### 동작 분석
- Warehouse.stock_num은 클래스 전체에서 공유됨
- self.name은 각 인스턴스마다 고유
- __del__은 객체가 삭제될 때 자동 호출되어 stock_num 감소

### 출력 예시
```python
user1 = Warehouse('j1')
user2 = Warehouse('j2')

print(Warehouse.stock_num)  # 2
print(user1.name)           # j1
print(user2.name)           # j2
print(user1.__dict__)       # {'name': 'j1'}
print(user2.__dict__)       # {'name': 'j2'}
print(Warehouse.__dict__)   # 클래스 변수 및 메서드 포함
```

- user1.stock_num → 2 (클래스 변수 접근)
- del user1 → __del__ 호출로 stock_num 감소

## 🔚 마무리 요약
| 항목             | 설명                                                   |
|------------------|--------------------------------------------------------|
| self             | 인스턴스 메서드에서 인스턴스를 참조하는 예약어          |
| 클래스 변수       | 클래스 전체에서 공유. 클래스명 또는 인스턴스로 접근 가능 |
| 인스턴스 변수     | 객체마다 고유. `self`를 통해 정의됨                     |
| 네임스페이스      | `__dict__`로 확인 가능. 변수 저장 공간                   |
| 메서드 호출 방식  | 클래스에서 호출 시 self 직접 전달, 인스턴스에서 자동 전달 |

---



