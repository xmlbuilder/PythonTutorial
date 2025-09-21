# Hangman 게임 2
Hangman 게임은 이전 버전보다 훨씬 더 발전된 구조로, 파일 입출력, 랜덤 처리, 사운드 효과, 외부 라이브러리 활용까지 포함.  
아래에 전체 코드의 취지와 학습 가능한 Python 지식을 정리.

## 소스
```python

import time
import csv
import random
import pygame

pygame.init()
pygame.mixer.init()

name = input("What is your name? ")
print("Hello, " + name, " Time to play hangman game!")
print()
time.sleep(1)

print("Start Loading...")
print()
time.sleep(0.5)

words = []
with open("./resource/word_list.csv") as words_file:
    reader = csv.reader(words_file)
    next(reader)
    for row in reader:
        words.append(row)

random.shuffle(words)
q = random.choice(words)

word = q[0]
help = q[1]
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
        sound = pygame.mixer.Sound("./sound/good.wav")
        sound.play()
        print()
        print()
        print('Congrats, you guessed the word!')
        break
    print()
    print("Hint : {}".format(help))
    guess = input("Guess a letter: ")
    guesses += guess
    if guess not in word:
        turns -= 1
        print("oops! Wrong guess!")
        print("You have", turns, 'more guesses!')
        sound = pygame.mixer.Sound("./sound/bad.wav")
        sound.play()
        if turns == 0:
            print("You hangman game failed. Bye!")
    else:
        sound = pygame.mixer.Sound("./sound/good.wav")
        sound.play()

```

## 🎯 전체 코드의 취지
- 텍스트 기반 게임을 실전 수준으로 확장
- 외부 리소스(csv, sound)를 활용한 데이터 및 UX 강화
- pygame을 통한 멀티미디어 효과 추가
- 랜덤성과 힌트 기능으로 게임의 재미와 난이도 조절
- 실전 프로젝트에서 필요한 모듈 분리, 파일 처리, 예외 대응의 기초 다지기

## 🧠 학습 가능한 Python 지식

| 문법/기능                   | 설명                                                                 |
|-----------------------------|----------------------------------------------------------------------|
| `input()`                   | 사용자로부터 이름과 문자 입력 받기                                   |
| `print(end=' ')`            | 줄바꿈 없이 출력하여 단어 진행 상태를 한 줄로 표현                   |
| `time.sleep()`              | UX 개선을 위한 출력 지연 처리                                       |
| `csv.reader()`              | 외부 CSV 파일에서 단어와 힌트 불러오기                              |
| `random.shuffle`, `choice` | 단어 리스트 섞기 및 무작위 선택                                     |
| `pygame.mixer.Sound()`      | 정답/오답에 따라 사운드 효과 재생                                   |
| `while`, `for`              | 게임 루프 및 단어 문자 순회                                         |
| `if`, `else`                | 정답 여부 판단, 남은 기회 처리, 게임 종료 조건                     |
| `in`, `+=`, `char in guesses` | 문자 포함 여부 확인 및 누적 처리                                     |
| `guesses`, `turns`, `failed`, `word`, `help` | 게임 상태 추적을 위한 변수 관리                             |
| 파일 경로 (`./resource/...`) | 외부 리소스 접근을 위한 상대 경로 지정                              |

## 📘 코드 흐름 요약
- 사용자 이름 입력 및 인사
- 게임 로딩 메시지 출력
- CSV 파일에서 단어와 힌트 불러오기
- 무작위 단어 선택
- while 루프를 통해 게임 진행
- 정답 여부에 따라 사운드 재생 및 메시지 출력
- 남은 기회가 0이면 게임 종료

## 🔊 사운드 효과 예시
```python
sound = pygame.mixer.Sound("./sound/good.wav")
sound.play()
```

- pygame.mixer.init()으로 사운드 시스템 초기화
- 정답/오답에 따라 다른 사운드 재생

## 🧩 확장 아이디어

| 기능/아이디어             | 설명                                                                 |
|---------------------------|----------------------------------------------------------------------|
| 중복 문자 입력 방지        | 이미 입력한 문자는 무시하거나 경고 메시지 출력                        |
| 입력 유효성 검사 (`isalpha()`) | 알파벳 외 입력 방지. 숫자, 특수문자 입력 시 안내 메시지 출력             |
| GUI 버전 (`tkinter`, `pygame.display`) | 그래픽 인터페이스로 게임 구현. 버튼, 이미지, 애니메이션 등 추가 가능     |
| 점수 시스템               | 정답 수, 남은 기회, 오답 수 등을 기반으로 점수 계산 및 기록             |
| 난이도 설정               | 단어 길이, 힌트 유무, 기회 수 등을 조절하여 Easy/Normal/Hard 모드 제공   |
| 단어 카테고리 분류        | CSV에 카테고리 추가 후 사용자가 주제 선택 가능 (예: 동물, 음식, 국가 등) |
| 멀티플레이어 모드         | 두 명 이상이 번갈아 가며 플레이하거나 경쟁하는 구조 구현                 |

---


