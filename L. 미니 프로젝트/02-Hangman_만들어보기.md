## 📘 Hangman 게임 코드
- Hangman 게임 코드는 단순한 단어 맞추기 게임을 구현하면서 Python의 핵심 문법과 프로그래밍 사고력을   
    자연스럽게 익힐 수 있도록 구성.  


### 📌 코드
```python
import time

name = input("What is your name? ")
print("Hello, " + name, " Time to play hangman game!")
print()

time.sleep(1)
print("Start Loading...")
print()
time.sleep(0.5)

word = "secret"
# guess
guesses = ''
#
turns = 10
while turns > 0:
    failed = 0
    for char in word:
        if char in guesses:
            print(char, end=' ')
        else:
            print('_', end=' ')
            failed += 1
    if failed == 0:
        print()
        print()
        print('Congrats, you guessed the word!')
        break
    print()
    guess = input("Guess a letter: ")
    guesses += guess
    if guess not in word:
        turns -= 1
        print("oops! Wrong guess!")
        print("You have", turns, 'more guesses!')
        if turns == 0:
            print("You hangman game failed. Bye!")
```

#### 🔹 전체 코드의 취지
- 텍스트 기반 게임을 통해 Python의 기초 문법을 실습
- 사용자 입력, 반복문, 조건문, 문자열 처리 등 기초 프로그래밍 능력 강화
- time.sleep()을 활용한 간단한 UX 개선
- 게임 로직을 직접 구현하며 문제 해결 능력 향상

#### 🔹 Hangman 코드에서 학습 가능한 요소

| 문법/개념             | 설명                                                                 |
|------------------------|----------------------------------------------------------------------|
| `input()`              | 사용자로부터 이름과 문자 입력 받기                                   |
| `print()` + `end=' '` | 줄바꿈 없이 출력하여 단어의 진행 상태를 한 줄로 표현                  |
| `time.sleep()`         | 출력 지연을 통해 UX 개선 (게임 시작 전 로딩 효과 등)                  |
| `in`, `+=`, `char in guesses` | 문자열 포함 여부 확인 및 문자 누적 처리                            |
| `while`, `for`         | 반복문을 통해 게임 루프 및 단어 문자 순회                             |
| `if`, `else`           | 조건문으로 정답 여부, 실패 처리, 게임 종료 조건 구현                  |
| `guesses`, `turns`, `failed` | 게임 상태 추적을 위한 변수 관리 (입력 문자, 남은 기회, 실패 횟수 등) |


#### 🔹 확장 아이디어
- 단어를 무작위로 선택 (random.choice)
- 이미 입력한 문자 중복 방지
- 알파벳 외 입력 처리 (isalpha() 활용)
- GUI 버전으로 확장 (tkinter 등)
- 점수 시스템, 난이도 설정, 힌트 기능 추가

---

