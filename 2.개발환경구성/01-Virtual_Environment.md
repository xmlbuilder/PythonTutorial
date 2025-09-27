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


