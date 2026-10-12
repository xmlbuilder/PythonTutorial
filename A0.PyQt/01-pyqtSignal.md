## 📘 pyqtSignal 사용법과 동작 원리

- `pyqtSignal`은 PyQt의 **Signal/Slot 이벤트 전달 시스템** 으로, 객체 간 결합도를 낮추면서 데이터를 전달합니다.
- `connect()`로 수신 함수를 연결하고 `emit()`으로 신호를 발생시킵니다.
- `QThread`와 함께 사용하면 Worker Thread의 진행률·완료 결과를 **GUI Thread에서 안전하게 처리** 할 수 있습니다.
- `pyqtSignal` 자체는 Thread를 만들지 않으며, 비동기 실행을 보장하지도 않습니다.

### 📌 설치

```bash
python -m pip install PyQt5
python -m pip show PyQt5
```

```python
from PyQt5.QtCore import QObject, pyqtSignal
print("PyQt5 OK")
```

- PyQt6에서도 `pyqtSignal`을 제공하지만 아래 예제는 **PyQt5** 기준입니다.
- Signal/Slot만 테스트한다면 Qt Designer는 필요하지 않습니다.

### 📌 정의 및 기본 구문

```python
from PyQt5.QtCore import QObject, pyqtSignal

class Worker(QObject):
    progressChanged = pyqtSignal(int)  # 정수 전달 Signal

    def run(self):
        self.progressChanged.emit(50)  # Signal 발생

worker = Worker()
worker.progressChanged.connect(lambda value: print(value))
worker.run()  # 50 출력
```

| 구문 | 의미 |
|------|------|
| `pyqtSignal(int)` | 정수 인자를 전달하는 Signal 선언 (클래스 속성) |
| `connect(slot)` | Signal과 수신 함수 연결 |
| `emit(value)` | 연결된 Slot으로 신호 전달 |
| `disconnect(slot)` | 기존 연결 해제 |
| `@pyqtSlot(int)` | Qt Meta-Object에 Slot 시그니처 등록 |

### 📌 핵심 개념: Direct / Queued Connection

- 기본 연결 방식은 `Qt.AutoConnection`이며, **Signal을 emit하는 현재 Thread** 와 **Receiver 객체가 속한 Thread** 를 기준으로 결정됩니다.

| 방식 | 동작 | 특징 |
|------|------|------|
| `Qt.DirectConnection` | Slot 즉시 호출 | Slot이 emit 호출 Thread에서 실행 |
| `Qt.QueuedConnection` | 수신 Thread의 Event Queue에 등록 | 수신 Thread의 Event Loop가 Slot 실행 |
| `Qt.AutoConnection` | 실행 시 Direct/Queued 선택 | 기본값 |


### 📌 connect()의 Connection Type 옵션
- connect() 함수는 Signal과 Slot을 연결하며, type 인자를 통해 Slot의 실행 방식을 지정할 수 있습니다.

```python
from PyQt5.QtCore import Qt

# 기본 연결 (Qt.AutoConnection)
worker.progress.connect(receiver.onProgress)

# Connection Type 명시
worker.progress.connect(
    receiver.onProgress,
    type=Qt.QueuedConnection
)
```
| 옵션	| 동작	| 특징|
|------|------|------|
|Qt.AutoConnection	| Direct/Queued 자동 선택|	기본값|
|Qt.DirectConnection	|Slot 즉시 호출	emit 호출 |Thread에서 실행|
|Qt.QueuedConnection	|수신 Thread의 Event Queue에 등록	수신 |Thread의 Event Loop에서 실행|

- AutoConnection: Signal을 emit하는 현재 Thread와 Receiver 객체가 속한 Thread가 같으면 Direct, 다르면 Queued 방식으로 실행됩니다.
- DirectConnection: Slot을 즉시 호출하므로 호출이 완료될 때까지 emit()이 반환되지 않습니다.
- QueuedConnection: 수신 Thread의 Event Loop를 통해 Slot을 실행하므로 emit()은 Slot 실행을 기다리지 않습니다.
- 참고: Qt.QueuedConnection은 같은 Thread 사이에서도 사용할 수 있으며, 수신 Thread에서 Event Loop가 실행되고 있어야 합니다.

```text
같은 Thread (Direct)
  emit() → slot() → emit() 반환

다른 Thread (Queued)
  Worker Thread                  GUI Thread
  emit() ── 이벤트 등록 ────────→ Event Queue
       └─ 반환                     │
                                  ▼
                              Event Loop
                                  │
                                  ▼
                                slot()
```

- QueuedConnection에서 `emit()`은 일반적으로 Slot 완료를 기다리지 않습니다.
- 수신 Thread의 **Event Loop가 동작해야** Queued Slot이 처리됩니다.
- 일반 Python 함수나 람다를 Receiver로 사용할 때는 QObject에 정의된 Slot과 Thread 처리 방식이 다를 수 있으므로, GUI 갱신은 GUI 객체의 `@pyqtSlot` 메서드에 연결하는 편이 명확합니다.

### 📌 GUI 없는 기본 테스트

```python
from PyQt5.QtCore import QObject, pyqtSignal

class Worker(QObject):
    progress = pyqtSignal(int)

    def run(self):
        for i in range(5):
            self.progress.emit(i * 10)

def on_progress(value):
    print(f"Progress: {value}")

worker = Worker()
worker.progress.connect(on_progress)
worker.run()
```

```text
Progress: 0
Progress: 10
Progress: 20
Progress: 30
Progress: 40
```

- 같은 Thread에서 직접 연결된 Slot을 호출하므로 `QApplication`이나 Event Loop가 없어도 실행됩니다.

### 📌 QThread와 GUI 진행률 업데이트

```python
import sys
import time
import threading
from PyQt5.QtCore import QObject, QThread, pyqtSignal, pyqtSlot
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QProgressBar

class Worker(QObject):
    progressChanged = pyqtSignal(int)
    completed = pyqtSignal()

    @pyqtSlot()
    def run(self):
        print("Worker Thread:", threading.get_ident())
        for i in range(101):
            time.sleep(0.02)
            self.progressChanged.emit(i)
        self.completed.emit()

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.progressBar = QProgressBar(self)
        layout = QVBoxLayout(self)
        layout.addWidget(self.progressBar)

        self.thread = QThread(self)
        self.worker = Worker()
        self.worker.moveToThread(self.thread)

        self.thread.started.connect(self.worker.run)
        self.worker.progressChanged.connect(self.onProgressChanged)
        self.worker.completed.connect(self.thread.quit)
        self.worker.completed.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        self.thread.start()

    @pyqtSlot(int)
    def onProgressChanged(self, value):
        print("GUI Thread:", threading.get_ident())
        self.progressBar.setValue(value)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec_())
```

- `moveToThread()`는 Worker의 Thread Affinity를 변경합니다.
- `thread.started`에 연결된 `Worker.run()`은 Worker Thread에서 실행됩니다.
- `progressChanged`를 받는 `MainWindow.onProgressChanged()`는 GUI Thread에서 실행됩니다.
- `completed`로 Thread 종료를 요청하고 `deleteLater()`로 객체 정리를 예약합니다.
- 실무에서는 창이 작업 중 닫힐 때 `thread.quit()` / `thread.wait()` 등으로 **Thread 종료와 객체 수명** 을 별도로 관리해야 합니다.

### 📌 C++ Qt와 비교

Python:

```python
class Worker(QObject):
    progressChanged = pyqtSignal(int)

    def run(self):
        self.progressChanged.emit(50)

worker.progressChanged.connect(receiver.onProgressChanged)
```

C++:

```cpp
class Worker : public QObject {
    Q_OBJECT
signals:
    void progressChanged(int value);
public:
    void run() { emit progressChanged(50); }
};

QObject::connect(worker, &Worker::progressChanged,
                 receiver, &Receiver::onProgressChanged);
```

- C++의 `emit`은 매크로이며 실제 Signal 전달은 Qt의 Meta-Object System이 담당합니다.
- Python의 `pyqtSignal`도 Qt Meta-Object System을 사용합니다.

### 📌 Callback과 차이

```python
# 일반 Callback: 호출한 Thread에서 바로 실행
callback(50)

# Qt Signal: 연결 방식에 따라 직접 호출하거나 수신 Thread에 전달
worker.progressChanged.emit(50)
```

| 항목 | 일반 Callback | pyqtSignal |
|------|---------------|------------|
| 함수 호출 | 직접 호출 | Qt Connection 경유 |
| Thread 간 전달 | 별도 구현 필요 | QueuedConnection 지원 |
| 다중 수신자 | 직접 관리 | 여러 Slot 연결 가능 |
| Event Loop | 필수 아님 | Queued 전달 시 수신 Thread에 필요 |
| GUI 업데이트 | 직접 Thread 확인 필요 | GUI QObject Slot으로 안전하게 전달 가능 |

### 📌 요약

- **선언:** `progressChanged = pyqtSignal(int)`
- **연결:** `worker.progressChanged.connect(receiver.onProgressChanged)`
- **발생:** `worker.progressChanged.emit(50)`
- **같은 Thread:** 기본적으로 즉시 호출(DirectConnection).
- **다른 Thread:** 기본적으로 수신 Thread의 Event Loop를 통해 실행(QueuedConnection).
- `pyqtSignal`은 이벤트 전달, `QThread`는 별도 실행, `Event Loop`는 Queued 이벤트 처리를 담당합니다.
- C++ Qt의 `signals` / `slots` / `emit`과 같은 개념입니다.

---

