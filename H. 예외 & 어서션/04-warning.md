# waring
- Python의 warnings 모듈에 대한 설명과 실전 예제 중심의 정리입니다.
- assert와는 다르게 프로그램을 중단하지 않고 경고만 출력하는 방식.

## ⚠️ Python warnings 모듈 정리
### ✅ 1. 기본 개념
- warnings.warn("메시지")는 경고 메시지를 출력하지만 프로그램은 계속 실행됨
- 디버깅, API 변경 안내, 사용 중단(deprecated) 경고 등에 활용됨
- 예외(Exception)처럼 프로그램을 멈추지 않음

### 🧪 2. 예제 코드
```rust
import warnings

print("before warning")
warnings.warn("this message is deprecated")
print("after warning")
```

#### 출력 결과:
```
D:\...\main.py:4: UserWarning: this message is deprecated
  warnings.warn("this message is deprecated")
before warning
after warning
```

- UserWarning은 기본 경고 타입
- 경고는 콘솔에 출력되며, 코드 흐름은 중단되지 않음

### 🧩 3. 주요 경고 타입

| 경고 타입            | 설명                                                   |
|----------------------|--------------------------------------------------------|
| `UserWarning`        | 일반적인 사용자 경고. 직접 정의하거나 테스트용으로 사용 |
| `DeprecationWarning` | 앞으로 제거될 예정인 기능에 대한 경고                   |
| `SyntaxWarning`      | 문법적으로 애매하거나 위험한 코드에 대한 경고           |
| `RuntimeWarning`     | 실행 중 발생할 수 있는 잠재적 문제에 대한 경고          |
| `FutureWarning`      | 향후 동작이 변경될 가능성이 있는 기능에 대한 경고       |

### 🛠️ 4. 커스터마이징
```python
warnings.warn("사용 중단 예정입니다", DeprecationWarning)
```
- 특정 경고 타입을 지정해 더 명확한 의미 전달 가능

### 🚫 5. 경고 무시하기
```python
import warnings
warnings.filterwarnings("ignore", category=UserWarning)
```
- 특정 경고를 무시하고 출력되지 않도록 설정할 수 있음


## 📘 실무 활용 예시
```python
def old_function():
    warnings.warn("이 함수는 더 이상 사용되지 않습니다", DeprecationWarning)
```

- 라이브러리나 API에서 사용 중단 예정 함수에 자주 사용됨
- 사용자에게 변경을 유도하면서도 기존 코드는 유지 가능

---
