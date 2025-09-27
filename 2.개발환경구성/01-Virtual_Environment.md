# 🧪 1. 가상환경(Virtual Environment) 설정

가상환경은 프로젝트마다 독립적인 Python 실행 환경을 만드는 것.
다른 프로젝트와 패키지 충돌 없이 개발할 수 있음.

## ✅ 생성 방법 (venv 기준)
```
python -m venv myenv
```

- myenv 폴더에 Python 실행 파일과 독립적인 패키지 디렉토리가 생성됨
## ✅ 활성화 방법
### - Windows:
```
myenv\Scripts\activate
```
### - macOS/Linux:
```
source myenv/bin/activate
```

활성화되면 PATH가 변경되어 해당 가상환경의 Python이 우선 사용됨

## ✅ 비활성화 명령어
```
deactivate
```
- venv 환경을 종료하고 시스템 기본 Python으로 돌아가게 돼.
- macOS, Linux, Windows 모두 동일하게 deactivate 입력하면 돼.

### 🧠 실무 팁

| 환경 종류   | 비활성화 명령어       | 설명                                      |
|-------------|------------------------|-------------------------------------------|
| `venv`      | `deactivate`           | 가상환경 종료 후 시스템 기본 Python으로 복귀 |
| `conda`     | `conda deactivate`     | Conda 환경 종료 후 이전 셸 또는 기본 환경으로 복귀 |

비활성화 후에는 which python 또는 where python 명령어로 현재 사용 중인 Python 경로를 확인하면 좋아.

✅ 추가 팁
- 비활성화 후 which python 또는 where python으로 현재 Python 경로를 확인하면 환경이 잘 바뀌었는지 알 수 있음
- 여러 환경을 중첩해서 활성화한 경우, conda deactivate를 여러 번 입력해야 완전히 빠져나올 수 있음


---

## 🧠 2. sys.path vs PYTHONPATH
| 항목             | PYTHONPATH                                | sys.path                                 |
|------------------|--------------------------------------------|-------------------------------------------|
| 설정 방식         | OS 환경 변수로 설정 (`export`, `set`)         | Python 코드 내에서 직접 수정 가능            |
| 적용 시점         | Python 실행 **전**에 설정됨                   | Python 실행 **중**에 동적으로 변경 가능       |
| 사용 목적         | 모듈 검색 경로를 **외부에서 추가**할 때 사용     | 실제 import 시 참조되는 경로 목록             |
| 설정 위치         | `.bashrc`, `.zshrc`, 시스템 환경 변수 등에서 설정 | `sys.path.append()` 등으로 코드 내에서 설정    |

## ✅ 예시
```python
import sys
print(sys.path)
```
- sys.path에는 기본 경로 + 현재 디렉토리 + PYTHONPATH 값이 포함됨

## 🔍 실무 팁

| 상황 또는 목적             | 활용 방법 또는 변수                                               |
|----------------------------|------------------------------------------------------------------|
| 프로젝트별 독립 환경 구성     | `venv`, `conda`로 가상환경 생성 → 패키지 충돌 방지                    |
| 모듈 경로 동적 추가         | 코드 내에서 `sys.path.append()` 사용 → 실행 중 경로 확장 가능           |
| 외부 모듈 경로 고정 설정     | `PYTHONPATH` 환경 변수에 경로 추가 → 시스템 또는 세션 단위로 적용 가능   |

## ✅ 실무 적용 예시
### 1. venv로 가상환경 생성
```
python -m venv myenv
source myenv/bin/activate  # macOS/Linux
myenv\Scripts\activate     # Windows
```

### 2. sys.path로 경로 추가
```python
import sys
sys.path.append("/Users/junghwan/my_modules")
```

## 3. .bashrc 또는 .zshrc에 PYTHONPATH 설정
```
export PYTHONPATH="/Users/junghwan/my_modules:$PYTHONPATH"
```


## 🧠 요약
- 가상환경은 프로젝트 단위로 Python 환경을 분리하는 도구
- **PYTHONPATH**는 환경 변수로 모듈 검색 경로를 추가
- **sys.path**는 실제 import 시 참조되는 경로 리스트로, 코드에서 직접 수정 가능

---

## 🧠 거부감 극복을 위한 실전 팁
### 1. 🧩 “왜 필요한지”부터 이해하기
- 가상환경은 프로젝트마다 독립적인 Python 환경을 만들어줌.
- 다른 프로젝트와 패키지 충돌 없이 개발 가능 → 실무에서 필수 스킬.
- 예: A 프로젝트는 numpy==1.21, B 프로젝트는 numpy==1.24 → 가상환경 없으면 충돌!
- 
### 2. 🐾 아주 작은 실습부터 시작하기
```
python -m venv testenv
source testenv/bin/activate  # macOS/Linux
testenv\Scripts\activate     # Windows
```

- 이걸로 “아, 환경이 분리되는구나”를 직접 체감할 수 있음.
- pip install로 패키지 설치 후 deactivate 해보면 완전히 감이 옴.
- 
### 🔄 기존 방식과 비교해보기
| 항목               | 전통적인 방식                          | 가상환경 방식 (`venv`, `conda`)                     | 환경 공유 방식                          |
|--------------------|----------------------------------------|-----------------------------------------------------|------------------------------------------|
| 패키지 설치 위치     | 시스템 전체에 설치됨                     | 프로젝트별 독립 환경에 설치됨                         | `requirements.txt`, `environment.yml`로 공유 가능 |
| 버전 충돌 위험       | 높음                                   | 낮음 (환경마다 버전 격리 가능)                        | 버전 명시로 재현 가능                     |
| 협업/배포 편의성     | 환경 설정 공유 어려움                    | 환경 파일로 손쉽게 공유 가능                          | `pip freeze`, `conda env export` 활용       |
| 유지보수 및 테스트   | 환경 오염 가능성 있음                    | 테스트 환경 격리 가능                                 | 환경 복원 명령어로 빠르게 재현 가능         |


### 4. 🧘‍♂️ “완벽하게” 하려 하지 말기
- 처음엔 venv만 써도 충분해. conda는 나중에 익숙해지면 확장하면 됨.
- 환경 이름, 경로, 설정 실수해도 괜찮아. rm -rf envname 하면 다시 만들면 됨.
### 5. 🧑‍🤝‍🧑 다른 개발자들의 경험 듣기
- 많은 개발자들이 “처음엔 귀찮았는데, 지금은 없으면 못 써요”라고 말함.
- GitHub, 블로그, 유튜브에서 “Python 가상환경 실무 활용” 같은 키워드로 찾아보면 동기부여 됨.

## 💬 한마디
“가상환경은 마치 개발자의 작업복이야. 처음엔 불편하지만, 입고 나면 자유로워져.”

----
# PyCharm
PyCharm을 중심으로 가상환경을 이해하면 훨씬 쉽게 다가갈 수 있음.  
사실 많은 개발자들이 venv나 conda를 처음 접할 때 거부감이 들지만, PyCharm이 그 과정을 자동화해주기 때문에 훨씬 부드럽게 시작할 수 있어.

## 🧠 PyCharm 관점에서 보는 가상환경
## ✅ 1. 프로젝트 생성 시 자동 가상환경 설정
- PyCharm에서 새 프로젝트를 만들면 아래 옵션이 보여:
[✔] Create a new environment using: [Virtualenv / Conda]
Location: /Users/junghwan/PycharmProjects/MyProject/venv
Base interpreter: /usr/bin/python3.10
- 이걸 체크하면 PyCharm이 알아서 venv나 conda 환경을 생성해줘.
- 별도로 python -m venv나 conda create 명령어를 몰라도 됨!

## ✅ 2. 가상환경 자동 활성화
- PyCharm은 해당 프로젝트를 열 때 자동으로 해당 가상환경을 활성화해.
- 터미널에서도 자동으로 venv나 conda 환경이 적용돼서 바로 pip install 가능.

## ✅ 3. 패키지 관리도 GUI로 가능
- Preferences → Project → Python Interpreter 메뉴에서 패키지를 설치/삭제 가능
- + 버튼으로 원하는 패키지를 검색해서 설치하면 PyCharm이 pip install을 대신 실행해줘
- requirements.txt도 자동으로 생성하거나 관리할 수 있어

## ✅ 4. 환경 공유도 쉬움
- PyCharm은 requirements.txt를 자동으로 감지하고 설치 여부를 물어봐
- Git에 requirements.txt나 environment.yml을 포함시키면 협업자도 PyCharm에서 쉽게 복원 가능

## 🔍 PyCharm이 주는 장점
| 기능 또는 상황           | PyCharm의 지원 또는 자동화 기능                                      |
|--------------------------|---------------------------------------------------------------------|
| `venv`, `conda` 환경 생성 | 새 프로젝트 생성 시 GUI로 가상환경 자동 생성 가능 (`venv` 또는 `conda`)     |
| 환경 자동 활성화         | 프로젝트 열 때 해당 가상환경 자동 적용 → 터미널에서도 바로 활성화됨         |
| 패키지 설치/관리         | GUI에서 패키지 검색 및 설치 가능 → `pip install` 없이도 손쉽게 관리 가능     |
| `requirements.txt` 연동  | 파일 감지 시 자동 설치 안내 → 협업 시 환경 복원이 쉬움                     |

## 한마디
“PyCharm은 가상환경을 마치 ‘숨은 조력자’처럼 다뤄줘. 복잡한 설정은 뒤에서 처리하고, 너는 코드에만 집중하면 됨.”
---






