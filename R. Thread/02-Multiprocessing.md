# 🧠 multiprocessing이란?
Python에서 여러 개의 프로세스를 생성하여 병렬로 작업을 수행할 수 있게 해주는 모듈.
각 프로세스는 독립된 메모리 공간과 CPU 코어를 사용함.

## ✅ 특징
- 진짜 병렬 처리 가능 (멀티코어 활용)
- 각 프로세스는 독립적 → GIL의 영향을 받지 않음
- CPU-bound 작업에 적합 (예: 수학 계산, 이미지 처리, 머신러닝)

## 🔄 threading vs multiprocessing 비교

| 항목               | threading                                      | multiprocessing                                  |
|--------------------|------------------------------------------------|--------------------------------------------------|
| 병렬 처리 방식       | 가짜 병렬 (GIL 영향으로 한 번에 하나만 실행됨)       | 진짜 병렬 (여러 CPU 코어 활용 가능)                   |
| GIL(Global Interpreter Lock) | 영향을 받음 → CPU-bound 작업에 비효율적         | 영향을 받지 않음 → CPU-bound 작업에 적합               |
| 메모리 구조          | 하나의 메모리 공간 공유 → 공유 자원 충돌 가능         | 프로세스마다 독립된 메모리 공간 → 안전하지만 통신 필요     |
| 속도 및 효율         | I/O-bound 작업에 빠름 (예: 파일, 네트워크)            | CPU-bound 작업에 빠름 (예: 이미지 처리, 수치 계산)       |
| 생성 비용            | 가볍고 빠름 → 수백 개 스레드도 부담 없음              | 무겁고 느림 → 프로세스 생성 비용 있음                   |
| 예외 처리            | 스레드 내 예외는 메인에서 감지 어려움                  | 프로세스 예외는 메인에서 감지 가능                      |
| 실무 활용 예시        | 웹 크롤링, 파일 다운로드, GUI 응답 유지 등              | 머신러닝 병렬 학습, 이미지 처리, 대규모 계산 작업 등       |


## 🧪 multiprocessing 샘플 코드
```python
from multiprocessing import Process
import os

def task(name):
    print(f"Hello {name} from PID {os.getpid()}")

if __name__ == '__main__':
    p1 = Process(target=task, args=('JungHwan',))
    p2 = Process(target=task, args=('Copilot',))
    p1.start(); p2.start()
    p1.join(); p2.join()
```


### ✅ 결과: 두 프로세스가 동시에 실행되며, 서로 다른 PID를 가짐

## 📌 실무 선택 기준

| 작업 유형               | 추천 방식           |
|------------------------|---------------------|
| 웹 크롤링, 파일 다운로드 | `threading`         |
| 이미지 처리, 수치 계산   | `multiprocessing`   |
| GUI 응답 유지            | `threading`         |
| 머신러닝 병렬 학습       | `multiprocessing`   |
| 실시간 로그 감시         | `threading`         |
| 대규모 데이터 분석       | `multiprocessing`   |


## 🔐 추가 팁
- multiprocessing.Queue, Pipe, Manager로 프로세스 간 통신 가능
- Pool 객체로 작업 분산 및 결과 수집 가능
- Windows에서는 if __name__ == '__main__' 필수

---

