## 📬 Message Passing이란?

- 여러 스레드 또는 프로세스가 직접 메모리를 공유하지 않고, 메시지를 주고받으며 데이터를 교환하는 방식.
- 이 방식은 동기화 문제를 줄이고, 안전하게 병렬 작업을 처리할 수 있게 해줌.

## 샘플 소스
```python
import threading
import time
from queue import Queue

channel = Queue(maxsize=3)

def producer():
    for item in ["hello", "from", "the", "other", "side"]:
        print(f"Producing {item}...")
        channel.put(item)

def consumer():
    while not channel.empty():
        item = channel.get()
        print(f"Consuming {item}...")
        channel.task_done()
        time.sleep(0.01)

producer_thread = threading.Thread(target=producer)
consumer_thread = threading.Thread(target=consumer)

producer_thread.start()
consumer_thread.start()

producer_thread.join()
consumer_thread.join()
```

###  출력결과
```
Producing hello...
Producing from...
Consuming hello...
Producing the...
Producing other...
Producing side...
Consuming from...
Consuming the...
Consuming other...
Consuming side...
```

## 🧵 소스 구조: Producer–Consumer + Queue
### 🔧 구성 요소 요약
| 구성 요소     | 연결 대상 | 역할 / 기능                                               |
|---------------|-----------|------------------------------------------------------------|
| `producer()`  | `Queue`   | 데이터를 생성하고 Queue에 넣음 → 메시지를 보내는 역할         |
| `consumer()`  | `Queue`   | Queue에서 데이터를 꺼내 처리함 → 메시지를 받는 역할           |
| `Queue`       | (공통 자원) | 스레드 간 안전한 메시지 전달 통로 → 내부적으로 Lock으로 동기화 처리 |


## 🔄 흐름
- Producer가 "hello", "from" 등 메시지를 생성
- channel.put()으로 메시지를 Queue에 전달
- Consumer가 channel.get()으로 메시지를 수신
- 메시지를 처리하고 task_done()으로 완료 표시

## 📌 Message Passing의 장점

| 항목               | 설명                                                                 |
|--------------------|----------------------------------------------------------------------|
| 안전한 동기화     | 공유 메모리 대신 메시지를 통해 데이터 전달 → Race Condition 방지 가능       |
| 느슨한 결합 구조  | 생산자와 소비자가 직접 연결되지 않음 → 모듈 간 독립성 유지, 유지보수 용이         |
| 확장성           | 생산자/소비자 수를 쉽게 늘릴 수 있음 → 병렬 처리 및 시스템 확장에 유리            |
| 디버깅 용이       | 메시지 흐름이 명확하고 로깅이 쉬움 → 시스템 상태 추적 및 오류 분석에 효과적         |
| 다양한 환경 적용   | 스레드, 프로세스, 네트워크 기반 시스템 등 다양한 환경에서 활용 가능               |

## 🧪 실무 예시
| 분야               | Message Passing 활용 예시                                     |
|--------------------|---------------------------------------------------------------|
| 웹 서버            | 요청 처리 스레드가 작업 스레드에 메시지 전달 → 비동기 응답 처리 가능         |
| IoT 시스템         | 센서 데이터 수집 후 분석 스레드에 전달 → 실시간 모니터링 및 제어             |
| 게임 서버          | 이벤트 발생 시 메시지를 각 클라이언트 처리 스레드로 전달 → 빠른 반응성 유지     |
| 데이터 파이프라인   | 생산자 스레드가 데이터를 생성하고 소비자 스레드가 저장 또는 분석 → 병렬 처리 최적화 |
| 채팅/메신저 시스템  | 사용자 입력을 메시지 큐에 넣고, 처리 스레드가 전송 → 안정적인 실시간 통신       |

## 🔁 요약
- 소스 속 구조는 스레드 간 메시지를 안전하게 전달하는 구조
- Queue는 메모리 공유 대신 메시지 전달을 통해 동기화 문제를 해결
- 실무에서는 비동기 처리, 병렬 작업, 이벤트 기반 시스템에 널리 사용됨

---


