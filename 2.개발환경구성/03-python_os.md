# 🧪 환경 변수 확인 코드 설명
```python
import os

python_path = os.environ.get('PYTHONPATH').split(os.pathsep)
print("python_path", python_path)

path = os.environ.get('PATH').split(os.pathsep)
print("path", path)
```


## 🔍 주요 개념

| 키워드 / 함수        | 설명                                                                 |
|----------------------|----------------------------------------------------------------------|
| `os.environ`         | 현재 시스템의 환경 변수들을 딕셔너리 형태로 반환함 (`os.environ['PATH']` 등) |
| `get()`              | 환경 변수 값을 안전하게 가져옴. 없으면 `None` 반환 (`os.environ.get('KEY')`) |
| `os.pathsep`         | 경로 구분자 → Unix는 `:` / Windows는 `;`                            |
| `split()`            | 문자열을 구분자로 나눠 리스트로 변환 (`str.split(os.pathsep)`)         |


## 📦 PYTHONPATH란?
- Python이 모듈을 찾을 때 참조하는 사용자 정의 경로 목록.
- 예를 들어, import mymodule을 할 때 PYTHONPATH에 지정된 경로에서 mymodule.py를 찾게 됨.
- 출력 예시:
```
['/Users/jeongjunghwan/PycharmProjects/Tutorial2',
'/Applications/PyCharm.app/...']
```


## 🛣️ PATH란?
- OS가 명령어 실행 시 참조하는 실행 파일 경로 목록.
- 예를 들어, 터미널에서 python을 입력하면 PATH에 있는 디렉토리들에서 python 실행 파일을 찾게 됨.
- 출력 예시:
```
['/opt/anaconda3/envs/ComputerVision/bin',
'/usr/bin',
'/bin',
'/usr/local/bin', ...]
```


## ✅ 실무 팁

| 상황 또는 목적             | 환경 변수 활용 예시                                               |
|----------------------------|------------------------------------------------------------------|
| 사용자 모듈 import 오류 해결 | `PYTHONPATH`에 프로젝트 경로를 추가하여 모듈 인식 문제 해결             |
| 가상환경 활성화 확인        | `PATH`에 가상환경의 `bin` 경로가 포함되어 있으면 해당 환경이 활성화됨     |
| 명령어 실행 불가 문제 해결   | `PATH`에 실행 파일 경로가 누락된 경우 추가하여 정상 실행 가능하게 함       |

## 🔍 예시 코드로 확인하기
```python
import os
```
# 사용자 모듈 경로 확인
```python
print("PYTHONPATH:", os.environ.get("PYTHONPATH"))
```
# 명령어 실행 경로 확인
```python
print("PATH:", os.environ.get("PATH"))
```

## 🧠 요약
- PYTHONPATH: Python 모듈 검색 경로
- PATH: OS 명령어 실행 경로
- 둘 다 시스템 설정과 개발 환경에 매우 중요한 변수

---
# 환경 변수 설정

## 🧾 1. .bashrc 또는 .zshrc란?
| 파일명       | 설명                                                                 |
|--------------|----------------------------------------------------------------------|
| `.bashrc`    | Bash 셸에서 사용하는 초기화 스크립트. 환경 변수, alias, 경로 설정 등에 사용됨 |
| `.zshrc`     | Zsh 셸에서 사용하는 초기화 스크립트. macOS에서 기본 셸로 많이 사용됨         |

이 파일들은 로그인 시 자동 실행되는 셸 초기화 스크립트야. 여기에 환경 변수를 설정하면 매번 수동으로 입력할 필요 없이 자동 적용됨.


## 🔧 2. 환경 변수 설정 방법
### ✅ PYTHONPATH 설정
# .bashrc 또는 .zshrc에 추가
```
export PYTHONPATH="/Users/jeongjunghwan/PycharmProjects/Tutorial2:$PYTHONPATH"
```

- 기존 PYTHONPATH에 경로를 추가하는 방식.
- 여러 경로를 추가할 땐 :로 구분.
### ✅ PATH 설정
# .bashrc 또는 .zshrc에 추가
```
export PATH="/opt/anaconda3/envs/ComputerVision/bin:$PATH"
```

- 새로운 실행 경로를 PATH 앞에 추가하면 우선순위가 높아짐.
- 기존 PATH를 유지하면서 덧붙이는 게 안전.

## 🧪 3. 적용 방법

### 설정 파일 변경 후 터미널에 입력
```
source ~/.bashrc   # 또는 source ~/.zshrc
```

source 명령어는 설정 파일을 다시 읽어서 변경 사항을 즉시 반영.


## 🧠 실무 팁
| 항목 또는 명령어           | 설명                                                                 |
|----------------------------|----------------------------------------------------------------------|
| `/` 경로 구분자            | 유닉스 기반 시스템에서 디렉토리 경로를 구분할 때 사용 (`/home/user/...`)     |
| `echo $PYTHONPATH`         | 현재 설정된 `PYTHONPATH` 값을 확인하는 명령어                          |
| `.bashrc`, `.zshrc` 백업   | 설정 변경 전 백업 권장 → `cp ~/.zshrc ~/.zshrc.bak` 등으로 원본 보존 가능     |



## 🪟 Windows 주요 환경 변수
| 변수 이름       | 설명                                                                 |
|----------------|----------------------------------------------------------------------|
| `PATH`         | 실행 파일(.exe 등)을 찾는 경로 목록. 명령어 실행 시 참조됨               |
| `PYTHONPATH`   | Python이 모듈을 찾을 때 추가로 참조하는 경로 목록                         |
| `TEMP`, `TMP`  | 임시 파일 저장 경로. 프로그램이나 시스템이 임시 데이터를 저장할 때 사용됨   |
| `USERPROFILE`  | 현재 사용자 홈 디렉토리 경로 → 예: `C:\Users\JungHwan`                   |
| `SystemRoot`   | Windows 설치 경로 → 일반적으로 `C:\Windows`                             |

## ✅ 실무 팁
- PATH에 Python, Git, Java 등의 실행 경로가 포함되어 있어야 명령어가 정상 작동
- PYTHONPATH는 사용자 정의 모듈을 import할 때 유용하게 쓰임
- TEMP, TMP는 디스크 정리나 캐시 관리 시 확인하면 좋음
- USERPROFILE은 사용자 설정 파일, 로그, 다운로드 경로 등과 연결됨
- SystemRoot는 시스템 파일 경로로, 직접 수정하면 위험할 수 있음


## 🔧 환경 변수 확인 방법
### 1. 명령 프롬프트(CMD)에서 확인
```
echo %PATH%
echo %PYTHONPATH%
```

### 2. PowerShell에서 확인
```
$env:PATH
$env:PYTHONPATH
```

### 3. GUI로 확인
- 내 컴퓨터 → 속성 → 고급 시스템 설정 → 환경 변수
- 사용자 변수 / 시스템 변수로 나뉘어 있음

## 🛠️ 환경 변수 설정 방법
### ✅ CMD에서 설정 (일시적)
```
set PYTHONPATH=C:\MyPythonModules
```

이 설정은 현재 세션에서만 유효해. CMD 창을 닫으면 사라짐.

### ✅ PowerShell에서 설정 (일시적)
```
$env:PYTHONPATH = "C:\MyPythonModules"
```

## ✅ 영구 설정 (GUI)
- 시작 → 시스템 환경 변수 편집 검색
- 환경 변수 버튼 클릭
- 사용자 변수 또는 시스템 변수에서 PATH, PYTHONPATH 수정 또는 추가

## 📌 실무 팁

| 상황 또는 목적             | 환경 변수 활용 예시                                               |
|----------------------------|------------------------------------------------------------------|
| 사용자 모듈 import 오류 해결 | `PYTHONPATH`에 프로젝트 경로를 추가하여 모듈 인식 문제 해결             |
| Python 실행 오류 해결       | `PATH`에 Python 설치 경로가 누락되었는지 확인 후 추가                    |
| 가상환경 활성화 확인        | `PATH`에 가상환경의 `Scripts` 경로가 포함되어 있으면 해당 환경이 활성화됨 |
| 명령어 실행 불가 문제 해결   | `PATH`에 실행 파일 경로가 빠져 있는 경우 추가하여 정상 실행 가능하게 함     |

## ✅ 확인 및 설정 팁
- 확인: echo %PYTHONPATH%, echo %PATH% (CMD) 또는 $env:PATH (PowerShell)
- 설정: GUI에서 "시스템 환경 변수 편집" → 사용자 변수 또는 시스템 변수에 추가
- 주의: 경로 추가 시 기존 값 유지하며 덧붙이기 → C:\MyPath;%PATH%


## 🧠 요약
- Windows에서도 PATH, PYTHONPATH는 개발 환경 설정에 핵심적인 역할을 함.
- GUI와 CLI 모두 설정 가능하며, 실무에서는 영구 설정과 일시 설정을 구분해서 사용하는 게 중요함.



