# PyPI / GitHub 배포
- PyPI 및 GitHub 배포를 위한 샘플 프로젝트 구조와 배포 절차를 깔끔하게 정리. 
- GIFConverter 클래스를 중심으로 패키지화하고, PyPI와 GitHub에 배포하는 흐름을 실무 기준으로 구성.

## 📦 1. PyPI 배포 절차 요약
### ✅ PyPI 배포 순서

#### 1. PyPI 회원 가입 → https://pypi.org
#### 2. 프로젝트 구조 준비
```
   ├── img_converter/
   │   ├── __init__.py
   │   └── converter.py  ← GIFConverter 클래스 정의
   ├── README.md
   ├── setup.py
   ├── LICENSE
   ├── MANIFEST.in
   └── setup.cfg (선택)
```
#### 3. 필수 패키지 설치
```
   pip install setuptools wheel
```

#### 4. 배포용 파일 생성
```
   python setup.py sdist bdist_wheel
```

#### 5. Twine 설치 및 업로드
```
   pip install twine
   python -m twine upload dist/*
```

#### 6. 설치 확인
```
   pip install pygifconv-thj
```


#### 🧪 PyPI 설치 후 사용 예시
```python
from pygifconv_thj.converter import GIFConverter as gfc

c = gfc("./project/images/*.png", "./project/image_out/test.gif", resize=(320, 240))
c.convert()
```

## 🐙 2. GitHub 배포 절차 요약
### ✅ GitHub 배포 순서

####  1. GitHub 회원 가입 → https://github.com
#### 2. 로컬 프로젝트 초기화
```
   git init
   git add .
   git commit -m "first release"
   git remote add origin https://github.com/yourname/pygifconv-thj.git
   git push origin master
```

#### 3. GitHub에 PyPI 구조 그대로 push

#### 4. 설치 확인
```
   pip install git+https://github.com/yourname/pygifconv-thj.git
```


#### 📁 샘플 프로젝트 구조
```
pygifconv-thj/
├── img_converter/
│   ├── __init__.py
│   └── converter.py
├── README.md
├── setup.py
├── LICENSE
├── MANIFEST.in
```


##### 🧠 setup.py 예시
```python
from setuptools import setup, find_packages

setup(
    name='pygifconv-thj',
    version='0.1.0',
    description='GIF image converter using PIL',
    author='JungHwan Jeong',
    packages=find_packages(),
    install_requires=['Pillow'],
    python_requires='>=3.6',
)
```
- 이제 이 프로젝트는 로컬에서만 쓰는 도구가 아니라, 전 세계 개발자들이 pip으로 설치해서 쓸 수 있는 공개 패키지가 된 거임. 

---

# 기능 확장

- 아래는 pygifconv-thj 프로젝트에 다음 기능을 확장한 예제:
   - ✅ setup.cfg를 통한 정적 설정 분리
   - ✅ README.md에 예제 코드 추가
   - ✅ tests/ 디렉토리로 유닛 테스트 연동

## 🧩 1. setup.cfg 정적 설정 분리
- setup.cfg는 setup.py의 일부 설정을 분리해서 관리할 수 있음. 
- 유지보수와 자동화에 유리.
```
# setup.cfg
[metadata]
name = pygifconv-thj
version = 0.1.0
description = GIF image converter using PIL
author = JungHwan Jeong
license = MIT
long_description = file: README.md
long_description_content_type = text/markdown

[options]
packages = find:
install_requires =
    Pillow
python_requires = >=3.6
```

- setup.py는 최소한의 실행 코드만 남겨도 됨:
```
# setup.py
from setuptools import setup
setup()
```


## 📘 2. README.md에 예제 코드 추가
```
# pygifconv-thj

GIF 이미지 변환기입니다. 여러 이미지를 하나의 GIF 애니메이션으로 변환합니다.

## 설치

```bash
pip install pygifconv-thj


사용 예시
from pygifconv_thj.converter import GIFConverter

c = GIFConverter('./images/*.png', './output/result.gif', resize=(320, 240), duration=400)
c.convert()

기능
- 다양한 이미지 포맷 자동 감지
- 리사이즈 및 프레임 간 시간 설정
- GUI 연동 가능
```


## 🧪 3. `tests/` 디렉토리로 유닛 테스트 연동

```python
# tests/test_converter.py
import unittest
import os
from pygifconv_thj.converter import GIFConverter

class TestGIFConverter(unittest.TestCase):
    def test_conversion_creates_file(self):
        output_path = './tests/output/test.gif'
        converter = GIFConverter('./tests/images/*.png', output_path, resize=(100, 100), duration=200)
        converter.convert()
        self.assertTrue(os.path.exists(output_path))

if __name__ == '__main__':
    unittest.main()

```
## ✅ 실행 방법
```
python -m unittest discover tests
```


## 📁 프로젝트 구조 예시
```
pygifconv-thj/
├── img_converter/
│   ├── __init__.py
│   └── converter.py
├── tests/
│   ├── test_converter.py
│   └── images/  ← 테스트용 이미지
├── README.md
├── setup.py
├── setup.cfg
├── LICENSE
├── MANIFEST.in
```


## 📦 MANIFEST.in에 들어가는 것들
```
include README.md
include LICENSE
include setup.cfg
include MANIFEST.in

recursive-include img_converter *.py
recursive-include tests *.py
recursive-include tests/images *.png *.jpg
```


### 🔍 주요 명령어 설명
| 명령어                        | 설명 및 예시                                                              |
|-------------------------------|---------------------------------------------------------------------------|
| `include filename`            | 특정 파일 포함 → `README.md`, `LICENSE` 등 문서 파일 포함                   |
| `exclude filename`            | 특정 파일 제외 → 예: `exclude secret_config.py`                            |
| `recursive-include dir pattern` | 디렉토리 내 특정 패턴의 파일 포함 → `recursive-include img_converter *.py *.png` |
| `recursive-exclude dir pattern` | 디렉토리 내 특정 패턴의 파일 제외 → 예: `recursive-exclude tests *.tmp`         |
| `global-include pattern`      | 전체 프로젝트에서 특정 패턴의 파일 포함 → 예: `global-include *.cfg`           |
| `global-exclude pattern`      | 전체 프로젝트에서 특정 패턴의 파일 제외 → 예: `global-exclude *.log`           |


### ✅ 실무 팁
- README.md, LICENSE, setup.cfg는 꼭 포함시켜야 PyPI에서 문서와 라이선스가 제대로 표시돼.
- 이미지, 테스트 파일, 설정 파일 등도 recursive-include로 명시하면 배포 패키지에 포함돼.
- python setup.py sdist로 생성된 .tar.gz 파일을 열어보면 실제 포함된 파일을 확인할 수 있어.

---



