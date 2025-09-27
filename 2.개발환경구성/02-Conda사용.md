# 🧪 1. Conda 환경 설정
## ✅ 환경 생성
```python
conda create -n myenv python=3.10
```

- myenv: 환경 이름
- python=3.10: 원하는 Python 버전 지정
## ✅ 환경 활성화

```
conda activate myenv
```

##✅ 비활성화 명령어
```
conda deactivate
```

- 현재 활성화된 Conda 환경을 종료하고 이전 환경 또는 기본 셸로 돌아가.
- 여러 단계로 활성화된 경우, 한 번 더 conda deactivate를 입력해야 완전히 빠져나올 수 있어.

## 🧠 실무 팁
| 환경 종류   | 비활성화 명령어       | 설명                                      |
|-------------|------------------------|-------------------------------------------|
| `venv`      | `deactivate`           | 가상환경 종료 후 시스템 기본 Python으로 복귀 |
| `conda`     | `conda deactivate`     | Conda 환경 종료 후 이전 셸 또는 기본 환경으로 복귀 |

비활성화 후에는 which python 또는 where python 명령어로 현재 사용 중인 Python 경로를 확인하면 좋아.

### ✅ 추가 팁
- 비활성화 후 which python 또는 where python으로 현재 Python 경로를 확인하면 환경이 잘 바뀌었는지 알 수 있음
- 여러 환경을 중첩해서 활성화한 경우, conda deactivate를 여러 번 입력해야 완전히 빠져나올 수 있음


##📦 2. requirements.txt란?
requirements.txt는 프로젝트에서 사용하는 패키지 목록과 버전 정보를 기록한 파일이야.
다른 개발자가 동일한 환경을 재현할 수 있도록 도와줘.

예시 내용:
```
numpy==1.24.0
pandas>=1.5.0
scikit-learn
```


## 🔄 3. requirements.txt로 패키지 설치
### ✅ pip 기반 설치
```
pip install -r requirements.txt
```
Conda 환경 안에서 pip로 설치하면 해당 환경에만 적용돼.


## 🧾 4. requirements.txt 생성 방법
### ✅ 현재 환경에서 설치된 패키지 목록 저장
```
pip freeze > requirements.txt
```

pip freeze는 현재 환경의 모든 패키지와 버전을 출력해줘.


## 🧠 실무 팁
| 상황 또는 목적             | 활용 방법 또는 명령어                                               |
|----------------------------|--------------------------------------------------------------------|
| Conda 환경 전체 공유        | `conda env export > environment.yml` → 패키지 + Python 버전까지 포함됨     |
| pip 기반 패키지 공유        | `requirements.txt` → `pip freeze > requirements.txt`로 생성 가능           |
| venv 또는 conda 환경에서 사용 | `requirements.txt`를 `pip install -r requirements.txt`로 설치 가능         |

## ✅ 실무 적용 흐름
### Conda 환경 공유
```
conda env export > environment.yml
conda env create -f environment.yml
```

### venv 또는 Conda 환경에서 pip 패키지 관리
```
ㅔip freeze > requirements.txt
pip install -r requirements.txt
```


## 🧠 요약
- environment.yml은 Conda 환경 전체를 공유할 때 사용
- requirements.txt는 pip 기반 패키지 목록을 공유할 때 사용
- 둘 다 협업, 배포, 환경 재현에 필수적인 도구야
혹시 이걸 기반으로 Docker와 연동하거나, .gitignore에 환경 파일을 어떻게 관리하는지도 보고 싶어? 다음 단계로 넘어가도 좋아!


## 🔁 Conda + pip 혼합 관리 팁
- Conda로 주요 패키지 설치 (예: numpy, pandas)
- pip로 특수 패키지 설치 (예: 웹 프레임워크, 최신 라이브러리)
- requirements.txt는 pip 기반이므로 Conda 환경 안에서 사용해야 정확함

## 🧠 요약
- Conda는 환경 격리와 Python 버전 관리에 강력함
- requirements.txt는 패키지 버전 고정과 재현에 필수
- 둘을 함께 쓰면 유지보수와 협업에 최적화된 개발 환경을 만들 수 있음

---
# environment.yml
environment.yml 파일은 Conda 환경을 전체적으로 공유하거나 재현할 때 사용하는 설정 파일. 
이 파일에는 Python 버전, 설치된 패키지, 채널 정보 등이 포함돼서 다른 사람이 동일한 환경을 쉽게 복원 가능.

## 🧾 environment.yml 기본 구조 예시
```
name: myenv
channels:
  - defaults
  - conda-forge
dependencies:
  - python=3.10
  - numpy=1.24.0
  - pandas>=1.5.0
  - scikit-learn
  - pip
  - pip:
      - fastapi
      - uvicorn
```


## 🔍 구성 요소 설명

| 항목           | 설명                                                                 |
|----------------|----------------------------------------------------------------------|
| `name`         | 환경 이름 설정 → `conda create -n myenv`에서의 `myenv`와 동일하게 지정됨 |
| `channels`     | 패키지를 다운로드할 Conda 채널 목록 → 예: `conda-forge`, `defaults`       |
| `dependencies` | Conda로 설치할 패키지 목록 → 예: `numpy=1.24.0`, `python=3.10` 등         |
| `pip:`         | Conda에 없는 패키지를 pip로 설치할 때 사용 → 예: `fastapi`, `uvicorn` 등   |




## ✅ 생성 및 사용 방법
### 환경 내보내기
```
conda env export > environment.yml
```

### 환경 복원하기
```
conda env create -f environment.yml
```

이 명령어로 동일한 환경을 새로 만들 수 있음. 협업이나 배포 시 아주 유용!


## 🧠 실무 팁
- pip 패키지가 포함된 경우 pip: 섹션을 꼭 분리해서 명시해야 해
- environment.yml은 Git에 포함시켜서 프로젝트 환경을 공유하는 데 최적이야
- name:은 복원 시 변경 가능 → conda env create -n newname -f environment.yml


