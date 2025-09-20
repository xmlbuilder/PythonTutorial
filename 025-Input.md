# Input
Python의 input() 함수는 사용자로부터 데이터를 입력받는 가장 기본적인 방법. 
아래에 기본 사용법, 형 변환, 예외 처리, 실무 팁까지 정리.

## 🧠 input() 함수 기본 개념
- input(prompt)는 사용자에게 메시지를 보여주고 **문자열(str)**을 입력받습니다.
- 입력값은 항상 문자열 타입으로 반환되므로, 숫자 계산을 하려면 형 변환이 필요합니다.

## 📌 기본 사용법
```python
name = input("Enter Your name : ")
grade = input("Enter Your Grade : ")
company = input("Enter Your Company Name : ")

print(name, grade, company)
```

- 모든 입력값은 str 타입입니다.
- type()으로 확인 가능:
```python
number = input("Enter number : ")
print(type(number))  # <class 'str'>
```


## 🔢 숫자 입력 처리 (형 변환)
### 정수 입력
```python
first_number = int(input("Enter number : "))
second_number = int(input("Enter number : "))
print(f"{first_number} + {second_number} = {first_number + second_number}")
```

### 실수 입력
```python
float_number = float(input("Enter a float number : "))
print("input float:", float_number)
print("type:", type(float_number))  # <class 'float'>
```


### 🧾 포맷 출력
```
print("FirstName - {0}, LastName - {1}".format(input('Enter first name : '), input('Enter second name : ')))
```


- format()을 사용하면 입력값을 깔끔하게 출력할 수 있어요.

## ⚠️ 예외 처리
### 단일 입력 예외 처리
```python
try:
    n = int(input("Enter a number : "))
    print("Ok. Your number is :", n)
except ValueError:
    print("This is not a number")
```


### 반복 입력 예외 처리
```python
while True:
    try:
        n = int(input("Enter a number : "))
        break
    except ValueError:
        print("This is not a number")

print("Ok. Your number is :", n)
```


- 사용자가 잘못된 값을 입력했을 때 프로그램이 멈추지 않도록 보호합니다.

## 💼 실무 팁
### 1. 리스트 입력 처리
```python
numbers = input("Enter numbers separated by space: ").split()
numbers = [int(n) for n in numbers]
print("Sum:", sum(numbers))
```

### 2. 다중 필드 입력
```python
user_info = input("Enter name, age, company: ").split(',')
name, age, company = user_info
print(f"Name: {name}, Age: {age}, Company: {company}")
```

### 3. 조건 검증
```python
email = input("Enter your email: ")
if "@" not in email or "." not in email:
    print("Invalid email format")
else:
    print("Email accepted")
```


## 🔚 요약

| 항목         | 기능 설명                         |
|--------------|----------------------------------|
| 기본 입력     | `input()`은 문자열(str)로 입력 받음 |
| 형 변환       | `int()`, `float()`으로 숫자 처리 가능 |
| 예외 처리     | `try-except`, `while`로 안전하게 입력 검증 |

---

## 실전 샘플

아래는 input()을 활용한 기본 메뉴 시스템 예제입니다. 
사용자가 메뉴를 선택하고, 각 선택에 따라 다른 동작을 수행하는 구조예요.

## 🧪 Python 콘솔 메뉴 시스템 예제
```python
def show_menu():
    print("\n📋 Main Menu")
    print("1. Say Hello")
    print("2. Add Two Numbers")
    print("3. Show Company Info")
    print("4. Exit")

def say_hello():
    name = input("Enter your name: ")
    print(f"👋 Hello, {name}!")

def add_numbers():
    try:
        a = float(input("Enter first number: "))
        b = float(input("Enter second number: "))
        print(f"➕ Result: {a} + {b} = {a + b}")
    except ValueError:
        print("⚠️ Invalid input. Please enter numeric values.")

def show_company_info():
    company = input("Enter your company name: ")
    print(f"🏢 Company: {company}")

# 메뉴 루프
while True:
    show_menu()
    choice = input("Select an option (1-4): ")

    if choice == "1":
        say_hello()
    elif choice == "2":
        add_numbers()
    elif choice == "3":
        show_company_info()
    elif choice == "4":
        print("👋 Exiting program. Goodbye!")
        break
    else:
        print("❌ Invalid choice. Please select 1-4.")

```

## ✅ 실행 예시
### 📋 Main Menu
```
1. Say Hello
2. Add Two Numbers
3. Show Company Info
4. Exit
Select an option (1-4): 1
```

```

Enter your name: JungHwan
👋 Hello, JungHwan!

```

## 💡 실무 확장 아이디어
- 사용자 인증 (ID/PW 입력)
- 파일 저장/불러오기 기능
- DB 연동 메뉴 (예: 회원 조회, 등록)
- 반복 입력 처리 및 예외 방지

---
