## 메모리 관리 핵심 개념
- 여기에 실무에서 반드시 알아두면 좋은 Python 메모리 관리 핵심 개념들을 더 보충.
- 아래 내용들은 Python 메모리 구조를 깊이 이해할 때 꼭 필요한 것들이고,
- 성능 최적화나 메모리 누수 방지에도 직접적으로 도움이 됨.

## ✅ Python 메모리에서 꼭 알아야 할 추가 개념
### ✅ 1. Python의 메모리 구조 (CPython 기준)
- Python은 크게 다음 4가지 레이어로 메모리를 관리:
| 레이어 이름                | 설명 |
|---------------------------|------|
| Python Object Layer       | 모든 객체가 PyObject 구조체로 관리되는 최상위 레이어 |
| Python Memory Manager     | 객체 생성/삭제를 관리하는 Python 내부 메모리 관리자 |
| pymalloc (Small Object Allocator) | 512바이트 이하 작은 객체를 위한 전용 메모리 풀 |
| OS Memory Allocator       | 큰 메모리 블록을 OS malloc/free로 직접 관리 |

#### ✅ 핵심 포인트
- Python은 **작은 객체는 자체 메모리 풀(pymalloc)** 에서 관리
- 큰 객체는 OS 메모리 할당을 직접 사용
- 그래서 del을 해도 OS 메모리가 즉시 줄지 않는 이유가 여기 있음
  - Python 내부 풀에서 재사용하기 때문

## ✅ 2. Python의 “작은 정수 캐싱” (Small Integer Cache)
- Python은 -5 ~ 256 범위의 정수를 미리 캐싱해둔다.
```python
a = 10
b = 10
print(a is b)  # True
```
- ✅ 이유: 정수는 매우 자주 사용되므로 재사용하면 성능 향상
- ✅ 실무에서 “is 비교”가 잘못된 결과를 주는 대표적인 케이스

## ✅ 3. 문자열 인터닝 (String Interning)
- Python은 짧은 문자열, 식별자 형태 문자열을 자동으로 캐싱한다.
```python
a = "hello"
b = "hello"
print(a is b)  # True
```

- 하지만:
```python
a = "hello world!"
b = "hello world!"
print(a is b)  # False
```

- ✅ 문자열 비교 최적화를 위해 존재
- ✅ 메모리 절약 + 빠른 비교

## ✅ 4. 리스트(list) 메모리 확장 방식
- Python 리스트는 동적 배열(dynamic array) 구조.
  - append() 시 공간이 부족하면 2배 가까이 확장
  - 그래서 리스트는 실제 길이보다 더 큰 capacity를 가짐
- 확인:
```python
import sys
lst = []
print(sys.getsizeof(lst))  # capacity 0

lst.append(1)
print(sys.getsizeof(lst))  # capacity 증가
```    

- ✅ 실무에서 리스트가 메모리를 많이 잡아먹는 이유
- ✅ 대량 데이터는 list보다 array, deque, numpy array가 더 효율적

## ✅ 5. 딕셔너리(dict)의 해시 테이블 구조
- Python dict는 Open Addressing 기반 해시 테이블.
- 특징:
  - key 삽입 시 해시 충돌을 최소화하도록 내부적으로 재배치
  - capacity는 자동 확장
  - key 삭제해도 메모리가 바로 줄지 않음
- ✅ 실무에서 dict는 매우 빠르지만 메모리 사용량이 큼
- ✅ 대량 데이터는 dict 대신 slots, namedtuple, dataclass(slots=True) 고려

## ✅ 6. __slots__를 사용한 메모리 최적화
- 클래스에 __slots__를 선언하면 인스턴스가 dict를 가지지 않음  
  - 메모리 절약 + 속도 향상

```python
class User:
    __slots__ = ("name", "age")

u = User()
u.name = "A"
u.age = 20
```

- ✅ 메모리 절약 효과가 매우 큼
- ✅ 대량 객체 생성 시 필수

## ✅ 7. 객체가 “바로” 삭제되지 않는 이유
- Python은 참조 수가 0이 되어도 즉시 OS에 메모리를 반환하지 않음.
- 이유:
  - Python 메모리 풀(pymalloc)이 재사용을 위해 보관
  - OS에 메모리를 반환하는 것은 비용이 큼
- ✅ 그래서 “메모리 누수처럼 보이지만 실제로는 Python 내부 풀에 남아 있는 것”

## ✅ 8. GIL(Global Interpreter Lock)
- Python의 가장 중요한 메모리/스레드 관련 개념.
  - 한 번에 하나의 스레드만 Python bytecode 실행 가능
  - CPU-bound 작업은 스레드로 병렬 처리 불가
  - I/O-bound 작업은 스레드 효율적
- ✅ 메모리와 직접 관련은 없지만,
- ✅ 객체 접근의 thread-safety를 보장하는 핵심 요소

## ✅ 9. 메모리 누수가 발생하는 실제 케이스
- ✅ 실무에서 가장 흔한 메모리 누수 원인들
  - ✅ 1) 전역 변수에 객체가 계속 쌓일 때
  - ✅ 2) 리스트/딕셔너리에 참조를 계속 유지할 때
  - ✅ 3) 순환 참조 + __del__ 조합
  - ✅ 4) 이벤트 핸들러/콜백 등록 후 해제 안 할 때
  - ✅ 5) LRU 캐시가 너무 커질 때

## ✅ 10. 메모리 최적화 팁 (실무용)
| 상황 또는 목적            | 최적화 방법                     |
|---------------------------|----------------------------------|
| 대량 객체 생성            | `__slots__` 사용                 |
| 대량 숫자/배열 처리       | `array`, `numpy` 사용            |
| 문자열 중복 제거          | `sys.intern()` 사용              |
| 캐시 자동 정리            | `WeakValueDictionary` 사용       |
| 순환 참조 정리            | `gc.collect()` 호출              |
| CPU-bound 작업 병렬화     | `multiprocessing` 사용           |
| I/O-bound 작업 최적화     | `asyncio` 사용                   |


## ✅ 최종 요약
- Python 메모리에서 꼭 알아야 할 추가 개념:
  - ✅ Python 메모리 구조 (Object → Memory Manager → pymalloc → OS)
  - ✅ 작은 정수 캐싱
  - ✅ 문자열 인터닝
  - ✅ 리스트의 capacity 확장 방식
  - ✅ dict의 해시 테이블 구조
  - ✅ __slots__로 메모리 최적화
  - ✅ Python이 메모리를 즉시 반환하지 않는 이유
  - ✅ GIL
  - ✅ 실무에서 발생하는 메모리 누수 패턴
  - ✅ 메모리 최적화 전략

---

