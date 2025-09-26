
# Context Manager
Python의 컨텍스트 매니저(Context Manager) 개념  설명.  
특히 with 구문과 __enter__, __exit__ 메서드의 동작을 직접 구현한 부분이 핵심.  
아래에 개념, 동작 원리, 특징, 실무 중요성까지 자세히 정리.

## 🧠 컨텍스트 매니저란?
리소스의 할당과 해제를 정확한 시점에 자동으로 처리해주는 구조

- 파일, 네트워크 연결, 데이터베이스 커넥션, 락(lock) 등 한정된 자원을 다룰 때 사용
- with 구문을 통해 명시적인 시작과 종료 시점을 정의
- 예외가 발생해도 자원 누수 없이 안전하게 종료됨

## 🔧 기본 구조
```python
with open('file.txt', 'w') as f:
    f.write("Hello")
```

- open()은 컨텍스트 매니저 객체를 반환
- __enter__() → f에 반환됨
- __exit__() → 블록 종료 시 자동 호출 (예외 발생 여부와 관계없이)

## 🧪 직접 구현 예제 분석
```python
class MyFileWriter():
    def __init__(self, file_name, method):
        self.file_obj = open(file_name, method)
    def __enter__(self):
        return self.file_obj
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file_obj.close()
```

- __enter__()는 자원 할당 (파일 열기)
- __exit__()는 자원 해제 (파일 닫기)
- 예외가 발생하면 exc_type, exc_val, exc_tb로 전달되어 로깅이나 복구 가능

## 📌 실무에서 왜 중요한가?
| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| `__exit__()` 자동 호출 | 블록이 끝나는 순간 자동으로 호출되어 **자원 해제 누락 방지** 가능             |
| `try-finally` 대체     | `with` 구문은 `try-finally`보다 **간결하고 예외 안전성이 높음**               |
| 예외 발생 시 안전 종료 | 예외가 발생해도 `__exit__()`가 호출되어 **파일, DB, 네트워크 등 자원 누수 방지** |
| 코드 가독성 향상       | `with` 구문은 **자원 사용 범위가 명확**하여 유지보수와 협업에 유리              |
| 커스텀 자원 관리       | 직접 구현한 컨텍스트 매니저로 **복잡한 초기화/종료 로직을 캡슐화** 가능         |


## 🔍 특징 요약
| 구성 요소               | 설명                                                                 |
|--------------------------|----------------------------------------------------------------------|
| `__enter__()`            | `with` 블록 시작 시 호출됨. 자원 할당, 초기화, 연결 등 수행              |
| `__exit__()`             | `with` 블록 종료 시 호출됨. 자원 해제, 종료 처리, 예외 핸들링 포함         |
| `exc_type`, `exc_val`, `exc_tb` | `__exit__()`에 전달되는 예외 정보. 예외 발생 시 로깅, 복구, 무시 여부 결정 가능 |
| `with` 구문              | 컨텍스트 매니저를 사용하는 문법. 자원 사용 범위 명확, 예외 안전성 확보       |
| `contextlib.contextmanager` | 데코레이터 방식으로 간단한 컨텍스트 매니저 구현 가능. 함수 기반 구조 지원     |


## ✅ 실무 팁
- 파일, DB, 락(lock), 소켓 등 자원은 반드시 컨텍스트 매니저로 다루는 습관이 중요
- contextlib 모듈을 활용하면 함수 기반 컨텍스트 매니저도 쉽게 구현 가능
- 예외 발생 시 __exit__()에서 로깅, 복구, 트랜잭션 롤백 등 처리 가능

## C# uing / java try

Python의 with 구문을 사용하는 컨텍스트 매니저는 C#의 using, Java의 try-with-resources와 본질적으로 같은 개념  
— 자원(Resource)을 안전하게 관리하는 구조적 방법이라는 점에서 공통돼.


## 🔍 비교 요약: 언어별 자원 관리 구조
| 언어       | 자원 관리 키워드         | 종료 처리 메서드         | 설명                                                                 |
|------------|---------------------------|----------------------------|----------------------------------------------------------------------|
| Python     | `with` + `__enter__/__exit__` | `__exit__()`               | 컨텍스트 매니저를 통해 자원 할당/해제. 예외 발생 여부와 관계없이 `__exit__()` 호출 |
| C#         | `using`                   | `Dispose()`                | IDisposable 구현 객체에 대해 `Dispose()` 자동 호출. 메모리/파일/DB 자원 해제     |
| Java       | `try-with-resources`      | `close()`                  | AutoCloseable 구현 객체에 대해 `close()` 자동 호출. 예외 발생 시에도 안전하게 종료 |

## 🧠 공통 개념
- 자원 할당과 해제를 명확하게 관리
- 예외 발생 여부와 관계없이 자원 누수 방지
- 코드 가독성과 안정성 향상
- 파일, DB, 네트워크, 락(lock) 등 한정된 자원에 필수

## ✅ Python만의 특징
- __enter__()와 __exit__()를 직접 구현하거나 contextlib로 간단하게 구성 가능
- 예외 정보 (exc_type, exc_val, exc_tb)를 __exit__()에서 직접 처리 가능
- 함수형 방식으로도 컨텍스트 매니저 구현 가능 → @contextmanager 데코레이터

## ✍️ 예시 비교
### 🔸 Python
```python
with open('file.txt', 'w') as f:
    f.write("Hello")
```

### 🔸 C#
```csharp
using (var file = new StreamWriter("file.txt"))
{
    file.Write("Hello");
}
```

### 🔸 Java
```java
try (BufferedWriter file = new BufferedWriter(new FileWriter("file.txt"))) {
    file.write("Hello");
}
```

결론적으로, 세 언어 모두 자원 해제를 자동화하여 안정성을 높이는 구조를 갖고 있고,  
Python의 with 구문은 그 중에서도 가장 유연하고 확장성 있는 방식.

---

