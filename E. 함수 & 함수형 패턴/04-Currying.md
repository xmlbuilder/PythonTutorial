# Currying

커링(Currying)은 함수형 프로그래밍에서 매우 중요한 개념이며, Python에서도 pymonad 라이브러리를 통해 쉽게 구현할 수 있습니다.  
아래에 커링의 개념, pymonad.tools.curry 사용법, 그리고 실무에 적용할 수 있는 예제를 정리.

## 🧠 커링(Currying)이란?
커링은 여러 개의 인자를 받는 함수를 하나의 인자만 받는 함수들의 체인으로 변환하는 기법입니다.  
예를 들어, 다음과 같은 함수가 있다고 할 때:
```python
def add(x, y, z):
    return x + y + z
```
- 커링을 적용하면 다음처럼 사용할 수 있습니다:
```
add(1)(2)(3)  # 결과: 6
```

## 🛠 pymonad.tools.curry 사용법
### 설치
```
pip install pymonad
```

### 기본 예제
```python
import pymonad.tools

@pymonad.tools.curry(3)
def f(x, y, z):
    return x + y + z

print(f(1)(2)(3))  # 출력: 6
```

### 단계별 호출
```python
cu = f(1)
print(cu)  # <function ...> (커링된 함수 객체)

cu = cu(2)
print(cu)  # <function ...> (다시 커링된 함수 객체)

cu = cu(3)
print(cu)  # 6 (최종 결과)
```

## ✅ 실무적인 커링 활용 예제
### 1. 💼 세금 계산기
```python
@pymonad.tools.curry(3)
def calculate_tax(price, tax_rate, discount):
    return (price - discount) * (1 + tax_rate)
```
#### 기본 세율 10%, 할인 5 적용
```python
tax_fn = calculate_tax(100)(0.1)(5)
print(tax_fn)  # 출력: 104.5
```

### 2. 📊 로깅 함수
```python
@pymonad.tools.curry(2)
def log(level, message):
    print(f"[{level.upper()}] {message}")

info_log = log("info")
info_log("서비스 시작됨")  # 출력: [INFO] 서비스 시작됨
```

### 3. 🧪 API 응답 처리기
```python
@pymonad.tools.curry(3)
def handle_response(status_code, headers, body):
    return {
        "status": status_code,
        "headers": headers,
        "body": body
    }

partial_handler = handle_response(200)({"Content-Type": "application/json"})
print(partial_handler({"data": "OK"}))
```

## ⚠️ 커링의 주의점
- 가독성: 너무 많은 커링은 오히려 코드를 이해하기 어렵게 만듭니다.
- 디버깅 어려움: 중간 단계에서 오류가 발생하면 추적이 까다로울 수 있습니다.
- 실무에서는: 반복적으로 사용하는 고정 인자 처리, 설정값 주입, 로깅, API 핸들링 등에 유용합니다.

## 🔚 마무리
- 커링은 함수형 프로그래밍의 강력한 도구로, Python에서도 pymonad를 통해 쉽게 구현할 수 있습니다.  
- 실무에서는 고정된 인자를 미리 설정하고 재사용하는 함수 구성에 매우 유용하니, 적절히 활용하면 코드의 유연성과 재사용성이 크게 향상됩니다.

---


