## 📘 Boost.Python & Boost.NumPy 빌드 및 C++ 연동 정리


### 📌  1. 문서 범위와 확인 상태

- Windows x64, MSVC, Python 3.12 환경에서 Boost.Python·Boost.NumPy를 `b2`로 빌드하고 C++ 실행 파일에 연결하는 과정을 정리한다.
- `b2`는 Boost의 빌드 도구이며, CMake의 Ninja와는 별개다.
- Apple M2를 의미한 경우를 위해 macOS ARM64 절차도 마지막에 포함한다.

- 현재 프로젝트에서 확인한 파일은 다음과 같다.

```text
D:/Development/cplus/THJ/nurbslib_cpp/Nurbslib/
  include/boost/                  Boost 1.92 헤더
  Python312/
    python.exe
    python312.dll
    include/Python.h
    libs/python312.lib
    Lib/encodings/
    Lib/site-packages/
  lib/Release/
    libboost_python312-vc142-mt-x64-1_92.lib
    libboost_numpy312-vc142-mt-x64-1_92.lib
  lib/Debug/
    libboost_python312-vc142-mt-gd-x64-1_92.lib
    libboost_numpy312-vc142-mt-gd-x64-1_92.lib
```


### 📌 2. 구성 요소의 역할

| 구성 요소 | 역할 |
|---|---|
| Boost.Python | C++와 Python 객체·함수 연결 |
| Boost.NumPy | C++에서 NumPy 배열 생성 및 메모리 연결 |
| Python 헤더·LIB | C++ 컴파일·링크 시 필요 |
| python312.dll | 실행 시 Python 인터프리터 제공 |
| Python Lib | encodings 등 표준 라이브러리 |
| site-packages | numpy, pandas, matplotlib, pyvista 등 |

- Boost.NumPy를 빌드하려면 선택한 Python에 NumPy가 먼저 설치되어 있어야 한다.
- C++에서 PyVista를 호출하는 용도라면 PyVista 자체를 C++ 라이브러리로 빌드할 필요는 없다.

### 📌  3. Windows 준비

- Visual Studio의 C++ 빌드 도구와 Windows SDK를 설치한다.
- 현재 라이브러리 이름의 `vc142`에 맞추려면 MSVC 2019 도구 집합을 사용한다. 
- MSVC 2022로 재빌드할 때는 `msvc-14.3`과 그 결과물에 맞춰 프로젝트 설정도 조정한다.

```bat
"D:\Development\cplus\THJ\nurbslib_cpp\Nurbslib\Python312\python.exe" -I -c "import sys, struct; print(sys.executable); print(sys.version); print(struct.calcsize('P') * 8)"
```
- Python이 64비트인지 확인한다.
- C++ 실행 파일·Boost·Python·NumPy 확장 모듈의 아키텍처를 맞춘다.


- 환경 변수 혼선이 있다면 이 CMD 창에서만 기존 Python 환경 변수를 비운다.
- 시스템 설정을 영구 변경하는 명령은 아니다.

```bat
set PYTHONHOME=
set PYTHONPATH=
```

### 📌 4. 선택한 Python의 패키지 확인

```bat
"%NURBS_PYTHON_ROOT%\python.exe" -m pip show numpy
"%NURBS_PYTHON_ROOT%\python.exe" -I -c "import numpy; print(numpy.__version__); print(numpy.get_include())"
```

- 미설치일 때만 설치한다. 기존에 정상 동작하는 환경을 재현하려면 패키지 버전을 기록하고 유지한다.

```bat
"%NURBS_PYTHON_ROOT%\python.exe" -m pip install numpy
"%NURBS_PYTHON_ROOT%\python.exe" -m pip freeze > python-packages.txt
```

- NumPy 1.x와 2.x 같은 주요 버전 변경 시에는 기존 Boost.NumPy 바이너리의 호환성을 가정하지 말고, 선택한 NumPy 헤더로 다시 빌드하고 배열 생성·읽기·쓰기까지 검사한다.

### 📌 5. Boost 소스와 b2 준비

- Boost 전체 소스 배포본을 별도 폴더에 압축 해제한다.
- 아래의 `D:\Libraries\boost_1_92_0`은 예시 경로다.
- 프로젝트에 복사한 `include/boost` 헤더만으로는 이 빌드 절차를 수행할 수 없다.

```bat
cd /d D:\Libraries\boost_1_92_0
bootstrap.bat
```

- 성공하면 소스 루트에 `b2.exe`가 생성된다.

### 📌 6. user-config.jam 작성

- Boost 소스 루트에 이 빌드 전용 `user-config.jam`을 만든다.
- 기존 파일이 있다면 먼저 내용을 확인하고 필요한 설정만 반영한다.
- 전역 사용자 설정을 덮어쓸 필요는 없다.

```jam
using msvc : 14.2 ;

using python
    : 3.12
    : "D:/Development/cplus/THJ/nurbslib_cpp/Nurbslib/Python312/python.exe"
    : "D:/Development/cplus/THJ/nurbslib_cpp/Nurbslib/Python312/include"
    : "D:/Development/cplus/THJ/nurbslib_cpp/Nurbslib/Python312/libs"
    ;
```
- 경로에는 위와 같이 `/`를 사용하면 편리하다. Python 버전은 major.minor 형식인 `3.12`로 지정하며 `3.12.6`으로 쓰지 않는다.



### 📌 7. Release 빌드

```bat
b2.exe --user-config=user-config.jam --with-python ^
    toolset=msvc-14.2 python=3.12 python-debugging=off ^
    architecture=x86 address-model=64 threading=multi ^
    variant=release link=static runtime-link=shared ^
    --layout=versioned --build-dir=build-python312 ^
    --stagedir=stage-python312-release stage -j4
```

| 옵션 | 의미 |
|---|---|
| `--with-python` | Boost.Python 관련 빌드. NumPy 검출 시 Boost.NumPy도 대상 |
| `python=3.12` | 설정한 Python 3.12 선택 |
| `python-debugging=off` | 일반 Release Python 사용 |
| `architecture=x86 address-model=64` | Windows x64 |
| `variant=release` | Release Boost |
| `link=static` | Boost 라이브러리를 정적 LIB로 생성 |
| `runtime-link=shared` | MSVC CRT는 DLL 버전. Release에서는 `/MD` |
| `--layout=versioned` | 컴파일러·구성·Boost 버전이 포함된 파일명 |
| `-j4` | 최대 4개 병렬 작업. 메모리 용량에 맞게 조정 |

- `link=static`은 Python 본체까지 정적 링크한다는 뜻이 아니다.
- 일반 Windows Python에서는 실행 시 `python312.dll`이 필요하다.

### 📌 8. Debug 빌드

```bat
b2.exe --user-config=user-config.jam --with-python ^
    toolset=msvc-14.2 python=3.12 python-debugging=off ^
    architecture=x86 address-model=64 threading=multi ^
    variant=debug link=static runtime-link=shared ^
    --layout=versioned --build-dir=build-python312 ^
    --stagedir=stage-python312-debug stage -j4
```

- Debug에서도 `python-debugging=off`를 유지한다.
- C++와 Boost는 Debug, Python은 일반 Release인 구성이다.
- Debug 측 CRT는 `/MDd`이다.

- 생성된 파일을 확인한다.

```bat
dir stage-python312-release\lib\*python*.lib
dir stage-python312-release\lib\*numpy*.lib
dir stage-python312-debug\lib\*python*.lib
dir stage-python312-debug\lib\*numpy*.lib
```

- Boost.NumPy가 생성되지 않으면 로그에서 NumPy 검출 결과를 확인한다.
- b2 인자에 `--debug-configuration`을 추가하면 설정 로딩을 확인할 수 있다.
- 설정 수정 후에도 이전 검출 결과가 남으면 `--reconfigure`를 붙여 다시 실행한다.

### 📌 9. 라이브러리 이름 읽기

```text
libboost_numpy312-vc142-mt-gd-x64-1_92.lib
```

| 부분 | 의미 |
|---|---|
| `libboost_numpy` | 정적 Boost.NumPy |
| `312` | Python 3.12 |
| `vc142` | MSVC v142 |
| `mt` | 멀티스레드 |
| `gd` | Debug CRT·Debug 구성을 나타내는 태그 |
| `x64` | 64비트 |
| `1_92` | Boost 1.92 |

- 헤더와 LIB의 Boost 버전, 애플리케이션과 Boost의 CRT 설정을 맞춘다.
- Debug 애플리케이션에 Release Boost를 연결하여 불일치를 우회하지 않는다.

### 📌 10. C++ 프로젝트 연결

- 인클루드 디렉터리:

```text
<Boost 소스 루트>              boost/python.hpp를 찾을 수 있는 상위 경로
<Python312>/include
```

- 현재 프로젝트에 복사된 헤더를 사용하면 `<프로젝트>/include`를 지정한다.

| 구성 | Boost LIB | Python LIB | CRT |
|---|---|---|---|
| Release | Release python·numpy LIB | python312.lib | /MD |
| Debug | `-gd-` python·numpy LIB | python312.lib | /MDd |

- MSVC의 Boost 자동 링크를 사용한다면 LIB 검색 경로와 구성을 정확히 지정한다.
- 명시적으로 링크할 때는 아래처럼 자동 링크를 끄고 사용할 파일을 지정할 수 있다.

```cmake
# 기존 타깃 NurbsLibTest3에 추가하는 설정 예시.
# BOOST_ROOT는 Boost 소스 루트, PYTHON_ROOT는 Python312 루트.
target_include_directories(NurbsLibTest3 BEFORE PRIVATE
    "${BOOST_ROOT}"
    "${PYTHON_ROOT}/include"
)

target_compile_definitions(NurbsLibTest3 PRIVATE
    BOOST_ALL_NO_LIB
)

set_property(TARGET NurbsLibTest3 PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

target_link_libraries(NurbsLibTest3 PRIVATE
    debug "${BOOST_ROOT}/stage-python312-debug/lib/libboost_python312-vc142-mt-gd-x64-1_92.lib"
    debug "${BOOST_ROOT}/stage-python312-debug/lib/libboost_numpy312-vc142-mt-gd-x64-1_92.lib"
    optimized "${BOOST_ROOT}/stage-python312-release/lib/libboost_python312-vc142-mt-x64-1_92.lib"
    optimized "${BOOST_ROOT}/stage-python312-release/lib/libboost_numpy312-vc142-mt-x64-1_92.lib"
    "${PYTHON_ROOT}/libs/python312.lib"
)

add_custom_command(TARGET NurbsLibTest3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PYTHON_ROOT}/python312.dll"
        "$<TARGET_FILE_DIR:NurbsLibTest3>"
    VERBATIM
)
```

- MSVC_RUNTIME_LIBRARY는 CMake 3.15 이상과 CMP0091의 NEW 동작을 전제로 한다.
- 최상위에서 `cmake_minimum_required(VERSION 3.15)` 이상을 `project()`보다 앞에 지정하는 등 기존 구성과 맞춘다.
- 위 예시는 일반 Debug/Release용이며, 사용자 정의 구성 이름을 사용하면 별도 대응을 추가한다.

### 📌 11. python312_d.lib를 찾지 못하는 경우

- `Python.h`를 직접 포함하면 MSVC Debug의 `_DEBUG` 때문에 `python312_d.lib`가 자동 링크 대상이 될 수 있다.
- Boost.Python 구성에서는 Python C API만 직접 사용하는 파일도 아래 래퍼를 사용한다.

```cpp
#include <boost/python/detail/wrap_python.hpp>
```

- Boost.Python·NumPy를 사용하는 파일은 다음 헤더를 포함하면 된다.

```cpp
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
```

- `BOOST_DEBUG_PYTHON`을 정의하지 않는 일반 구성에서는 Boost 래퍼가 Python 헤더를 읽는 동안만 `_DEBUG`를 조정하고 원래대로 복원한다.
- 프로젝트 전체의 `_DEBUG`를 해제하거나 `Py_DEBUG`를 직접 정의하지 않는다.

- 미리 컴파일된 헤더 등에서 먼저 `Python.h`를 직접 포함하는지 확인하고, 수정 후 클린 빌드한다.
- LIB 파일의 이름만 바꿔 해결하지 않는다.

### 📌 12. 실행 시 Python 초기화

- 링크에 사용한 Python과 실행 시 로딩하는 DLL·표준 라이브러리·site-packages를 맞춘다.

- 이미 제공한 `InitializeProjectPython()`은 `PyConfig_InitIsolatedConfig`와 `Py_InitializeFromConfig`로 Python 루트를 지정한다.
- 일반적인 `Lib` 폴더가 있는 배포 구성을 대상으로 한다.

```cpp
InitializeProjectPython(
    LR"(D:\Development\cplus\THJ\nurbslib_cpp\Nurbslib\Python312)"
);
```

- 초기화는 Boost.Python 객체 생성 전에 수행한다.
- 외부에서 먼저 `Py_Initialize()`를 호출하면 나중에 다른 Python 루트로 전환할 수 없다.
- Python 객체가 살아 있는 동안 `Py_FinalizeEx()`를 호출하지 않는다.

### 📌 13. 연결 확인 코드

- Python 초기화 후 초기화한 스레드에서 호출한다.
- 다른 C++ 스레드에서 호출하려면 GIL 관리를 별도로 설계한다.

```cpp
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

namespace py = boost::python;
namespace np = boost::python::numpy;

bool CheckPythonConnection()
{
    if (!Py_IsInitialized())
    {
        std::cerr << "Python is not initialized.\n";
        return false;
    }

    try
    {
        np::initialize();

        py::object sys = py::import("sys");
        py::object numpy = py::import("numpy");

        std::cout << py::extract<std::string>(
            py::str(sys.attr("version")))() << '\n';

        std::cout << py::extract<std::string>(
            py::str(numpy.attr("__file__")))() << '\n';

        np::ndarray values = np::zeros(
            py::make_tuple(3),
            np::dtype::get_builtin<double>()
        );

        values[0] = 1.0;
        values[1] = 2.0;
        values[2] = 3.0;

        const double sum = py::extract<double>(
            numpy.attr("sum")(values)
        )();

        std::cout << "Sum: " << sum << '\n';
        return sum == 6.0;
    }
    catch (const py::error_already_set&)
    {
        PyErr_Print();
        return false;
    }
}
```

- 이는 연결 확인이며 수치 알고리즘 전체의 정확성을 보장하는 테스트는 아니다.

### 📌 14. 패키지 확인과 이미지 출력

```bat
"%NURBS_PYTHON_ROOT%\python.exe" -m pip show numpy pandas matplotlib pyvista
"%NURBS_PYTHON_ROOT%\python.exe" -I -c "import numpy, pandas, matplotlib, pyvista; print('imports OK')"
```

- `pip show`는 설치 정보를 확인하고, `import`는 실제로 읽어올 수 있는지 확인한다. 서로 다른 검사다.

- Matplotlib은 `Agg` 백엔드로 이미지를 저장할 수 있다.
- PyVista는 `Plotter(off_screen=True)`로 창을 표시하지 않고 이미지를 저장하지만, VTK 렌더링 환경은 필요하다.


```cpp
py::object savefig = figure.attr("savefig");
py::tuple arguments = py::make_tuple(outputFile);
py::dict options;
options["dpi"] = 150;

PyObject* result = PyObject_Call(
    savefig.ptr(), arguments.ptr(), options.ptr()
);

if (result == nullptr)
{
    py::throw_error_already_set();
}

Py_DECREF(result);
```

### 📌 15. 데이터 전달 방침

- CAE 모델의 좌표 `(N,3)`, 요소 연결, 요소 타입, 절점 값·요소 값을 시각화용 연속 배열로 변환한다. 절점 ID를 0부터 시작하는 인덱스로 매핑하고, VTK 요소의 절점 순서에 맞춘다.

- 이후 `np::from_data()`로 C++ 배열을 NumPy에 연결할 수 있다. 소유자를 지정하지 않는 뷰는 C++에서 메모리 수명을 보장해야 한다. Python이나 VTK가 참조하는 동안 `std::vector`를 재할당하거나 파괴하지 않는다.

- PyVista/VTK 내부에서 추가 복사가 발생할 수 있으므로 전체 파이프라인의 무복사는 보장하지 않는다. 올바른 데이터 변환과 수명 관리를 확립한 다음 복사 감소를 검토한다.

### 📌 16. 자주 발생하는 오류

| 증상 | 확인할 부분 |
|---|---|
| python312_d.lib 없음 | Python.h 직접 포함, Debug 매크로, PCH |
| encodings 없음 | Python 루트, Lib, PyConfig, 이전 환경 변수 |
| Boost LIB 없음 | LIB 검색 경로, Debug/Release, 도구 집합, 버전 |
| LNK2038 | CRT 또는 _ITERATOR_DEBUG_LEVEL 불일치 |
| DLL load failed | DLL 의존성, 아키텍처, 실제 로딩된 Python |
| pip에서는 확인되지만 import 실패 | 다른 Python에 설치됨, 의존 모듈 로딩 실패 |
| keywords<1> 변환 오류 | py::arg를 Python 호출에 직접 전달했는지 확인 |
| NumPy 배열에서 비정상 종료 | Boost.NumPy와 NumPy 호환성, 수명, dtype, stride |

- Python 예외를 잡으면 원래 예외 정보부터 가져와 출력한다. 먼저 `close()` 등 다른 Python 처리를 호출하면 원인 추적이 어려워진다. 접근 위반은 Python 예외와 구분하여 호출 스택을 확인한다.

### 📌 17. Apple M2 / macOS ARM64의 경우

- Windows LIB·DLL은 재사용할 수 없다.
- Python·NumPy·Boost·C++ 실행 파일을 모두 ARM64로 맞추고 Rosetta x86_64 환경과 혼용하지 않는다.

```sh
xcode-select --install
uname -m
python3.12 -c 'import platform, sys; print(platform.machine()); print(sys.executable)'
python3.12 -m pip show numpy
```

- 사용할 Python 3.12에 NumPy를 설치한다. 관리되는 Python에서 pip 직접 설치가 제한되면 전용 venv를 만든다. 
- venv를 사용해도 임베딩에 필요한 기본 Python의 헤더·라이브러리 위치는 확인한다.

```sh
python3.12 -m venv ~/venvs/boost-python312
source ~/venvs/boost-python312/bin/activate
python -m pip install numpy
python -c 'import sysconfig; print(sysconfig.get_path("include")); print(sysconfig.get_config_var("LIBDIR"))'
```

- Boost 소스 루트에서 실행한다.

```sh
./bootstrap.sh
```

- 빌드 전용 `user-config.jam`을 작성한다.
- 아래 Python 경로는 실제 `sys.executable` 값으로 바꾼다.

```jam
using clang ;
using python : 3.12 : /Users/yourname/venvs/boost-python312/bin/python ;
```

```sh
./b2 --user-config=user-config.jam --with-python \
  toolset=clang architecture=arm address-model=64 \
  python=3.12 python-debugging=off \
  variant=release link=shared threading=multi \
  --build-dir=build-arm64-release \
  --stagedir=stage-arm64-release stage -j4

./b2 --user-config=user-config.jam --with-python \
  toolset=clang architecture=arm address-model=64 \
  python=3.12 python-debugging=off \
  variant=debug link=shared threading=multi \
  --build-dir=build-arm64-debug \
  --stagedir=stage-arm64-debug stage -j4
```

- 이 Mac 예시는 공유 라이브러리로 빌드한다. 생성된 `.dylib`의 이름과 ARM64 여부는 `file`, 의존성은 `otool -L`로 확인한다.
- 실행 시 검색 경로와 rpath도 설정한다. Debug/Release 결과는 별도 디렉터리에 유지한다.
- C++ 임베딩에는 기본 Python의 링크 조건도 필요하다.
- 사용하는 배포본에 `python3.12-config`가 있다면 `python3.12-config --embed --ldflags`를 참고한다.
- Framework Python과 일반 Python의 조건이 다르므로 Windows CMake 설정을 그대로 사용하지 않는다.

### 📌 18. Linux 빌드 및 연결

- 이 절은 Ubuntu/Debian 계열의 배포판 기본 Python과 GCC를 기준으로 한 절차 예시다.
- 현재 Windows 환경에서 Linux 빌드를 실행 검증하지는 않았다.
- Windows에서 만든 `.lib`·`.dll`은 Linux에서 사용할 수 없으므로 Linux에서 다시 빌드한다.

#### 🔹 18.1 개발 도구와 Python 준비

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build python3-dev python3-venv

g++ --version
python3 --version
uname -m
```

- 배포판에 따라 기본 Python 버전이 다르다.
- Linux까지 Python 3.12로 고정해야 한다면 먼저 해당 배포판에서 제공하는 Python 3.12 인터프리터·개발 헤더·venv 패키지를 준비하고 아래 명령의 `python3`를 해당 인터프리터로 바꾼다.
- 서로 다른 버전의 개발 헤더를 섞지 않는다.

- 시스템 Python에 pip로 직접 설치하는 대신 전용 가상환경을 만든다.

```bash
python3 -m venv "$HOME/venvs/nurbs-python"
source "$HOME/venvs/nurbs-python/bin/activate"

python -m pip install numpy
python -m pip freeze > python-packages-linux.txt

python -c 'import sys, sysconfig, numpy; print(sys.executable); print(sys.version); print(sys.prefix); print(sys.base_prefix); print(sysconfig.get_path("include")); print(sysconfig.get_config_var("LIBDIR")); print(numpy.get_include())'
```

- `sys.prefix`는 가상환경, `sys.base_prefix`는 기본 Python 설치 위치다.
- venv는 별도의 Python 전체 배포본이 아니므로, 개발 헤더·표준 라이브러리·libpython의 기본 설치도 유지해야 한다.

#### 🔹 18.2 Boost 및 Python 구성

- Boost 전체 소스를 예를 들어 `$HOME/libraries/boost_1_92_0`에 압축 해제한다.

```bash
cd "$HOME/libraries/boost_1_92_0"
./bootstrap.sh --with-toolset=gcc
```

- venv를 활성화한 상태에서 빌드 전용 설정 파일을 생성한다. 기존 같은 이름의 파일이 있으면 먼저 확인한다.

```bash
python - <<'PY'
from pathlib import Path
import sys
import sysconfig

version = f"{sys.version_info.major}.{sys.version_info.minor}"
interpreter = sys.executable
include_dir = sysconfig.get_path("include")
library_dir = sysconfig.get_config_var("LIBDIR")

if not library_dir:
    raise RuntimeError("Python library directory could not be determined.")

configuration = (
    "using gcc ;\n\n"
    "using python\n"
    f"    : {version}\n"
    f'    : "{interpreter}"\n'
    f'    : "{include_dir}"\n'
    f'    : "{library_dir}"\n'
    "    ;\n"
)

target = Path("user-config-linux.jam")
if target.exists():
    raise FileExistsError(f"Review the existing configuration first: {target}")

target.write_text(configuration, encoding="utf-8")
print(configuration)
PY
```

- Python 실행 파일 경로는 venv 내부 경로를 그대로 사용한다.
- 이를 실제 파일 경로로 정규화하여 기본 Python 실행 파일로 바꾸면 venv의 NumPy 검출에 영향을 줄 수 있다.

#### 🔹 18.3 Release 및 Debug 빌드

- 이 예시는 공유 라이브러리 `.so`를 생성하고, 같은 이름의 Debug/Release 파일을 별도 디렉터리로 구분한다. `--layout=system`을 명시하여 CMake 예시에서 사용할 파일명을 단순하게 유지한다.

```bash
NURBS_PYTHON_VERSION=$(python -c 'import sys; print(f"{sys.version_info.major}.{sys.version_info.minor}")')

./b2 --user-config=user-config-linux.jam --with-python \
  toolset=gcc python="$NURBS_PYTHON_VERSION" python-debugging=off \
  variant=release link=shared runtime-link=shared threading=multi \
  --layout=system --build-dir=build-linux-release \
  --stagedir=stage-linux-release stage -j4

./b2 --user-config=user-config-linux.jam --with-python \
  toolset=gcc python="$NURBS_PYTHON_VERSION" python-debugging=off \
  variant=debug link=shared runtime-link=shared threading=multi \
  --layout=system --build-dir=build-linux-debug \
  --stagedir=stage-linux-debug stage -j4

ls -l stage-linux-release/lib/libboost_python* stage-linux-release/lib/libboost_numpy*
ls -l stage-linux-debug/lib/libboost_python* stage-linux-debug/lib/libboost_numpy*
```

- 기본적으로 현재 Linux의 아키텍처로 빌드한다. x86_64와 ARM64 결과물을 혼용하지 않는다.
- 크로스 컴파일은 이 예제의 범위 밖이다.
- `variant=debug`는 Boost의 Debug 빌드다.
- `python-debugging=off`이므로 Python 본체는 일반 버전을 사용한다.
- Linux에는 Windows의 `/MD`, `/MDd`, `python312_d.lib` 설정이 없다.
- 일부 객체에만 `_GLIBCXX_DEBUG`를 정의하면 STL ABI가 달라질 수 있으므로 일반 Debug 빌드와 구분한다.

#### 🔹 18.4 CMake 설정 예시

- 아래는 독립적인 연결 확인 프로젝트 예시다. `main.cpp`에 Python 초기화, 앞서 설명한 연결 검사, 객체 파괴 후 종료 처리를 구현한다.
- 기존 프로젝트에는 필요한 부분을 기존 타깃에 반영한다.

```cmake
cmake_minimum_required(VERSION 3.18)
project(PythonEmbedCheck LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NURBS_BOOST_ROOT "" CACHE PATH "Boost source directory")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Embed)

# Python 3.12이면 312. 선택한 인터프리터에서 결정한다.
set(NURBS_PYTHON_TAG "${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")

foreach(NURBS_COMPONENT IN ITEMS python numpy)
    find_library(NURBS_BOOST_${NURBS_COMPONENT}_RELEASE
        NAMES boost_${NURBS_COMPONENT}${NURBS_PYTHON_TAG}
        PATHS "${NURBS_BOOST_ROOT}/stage-linux-release/lib"
        NO_DEFAULT_PATH REQUIRED
    )
    find_library(NURBS_BOOST_${NURBS_COMPONENT}_DEBUG
        NAMES boost_${NURBS_COMPONENT}${NURBS_PYTHON_TAG}
        PATHS "${NURBS_BOOST_ROOT}/stage-linux-debug/lib"
        NO_DEFAULT_PATH REQUIRED
    )
endforeach()

add_executable(PythonEmbedCheck main.cpp)
target_include_directories(PythonEmbedCheck BEFORE PRIVATE
    "${NURBS_BOOST_ROOT}"
)
target_link_libraries(PythonEmbedCheck PRIVATE
    Python3::Python
    debug "${NURBS_BOOST_python_DEBUG}"
    debug "${NURBS_BOOST_numpy_DEBUG}"
    optimized "${NURBS_BOOST_python_RELEASE}"
    optimized "${NURBS_BOOST_numpy_RELEASE}"
)
```

- 생성된 파일명이 다르면 실제 파일을 확인하고 `NAMES`를 맞춘다.
- CMake가 선택하는 Python은 b2와 동일한 인터프리터로 고정한다.

```bash
cmake -S . -B build-release -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DPython3_EXECUTABLE="$VIRTUAL_ENV/bin/python" \
  -DNURBS_BOOST_ROOT="$HOME/libraries/boost_1_92_0"
cmake --build build-release

cmake -S . -B build-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DPython3_EXECUTABLE="$VIRTUAL_ENV/bin/python" \
  -DNURBS_BOOST_ROOT="$HOME/libraries/boost_1_92_0"
cmake --build build-debug
```

- CMake는 일반적으로 빌드용 RPATH를 설정하지만 배포 위치에서의 실행 시 검색 경로는 별도로 확인한다.
- 먼저 `ldd`로 누락된 라이브러리를 확인한다.

```bash
ldd build-release/PythonEmbedCheck
ldd build-debug/PythonEmbedCheck
```

- 테스트 중 Boost 경로를 보충하려면 대상 프로세스에 한정하여 지정할 수 있다.

```bash
LD_LIBRARY_PATH="$HOME/libraries/boost_1_92_0/stage-linux-release/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}" \
  ./build-release/PythonEmbedCheck
```

- Debug 실행 시에는 Debug 디렉터리를 지정한다. 같은 이름의 `.so`가 있는 두 디렉터리를 무조건 함께 추가하지 않는다. 
- 배포 시에는 설치 위치에 맞는 `INSTALL_RPATH`를 설정한다.

#### 🔹 18.5 임베딩 Python과 venv

- venv를 활성화한 셸에서 시작해도 C++ 임베딩 Python이 자동으로 같은 패키지를 사용하는 것은 아니다. - 초기화 설정에서도 사용할 인터프리터를 명시한다.

- 일반적으로 `PyConfig`의 `program_name`에 venv Python 실행 파일의 절대 경로를 지정하고, 초기화 후 `sys.prefix`, `sys.base_prefix`, `sys.path`, `numpy.__file__`을 확인한다.
- Python 3.12에서 venv를 사용한다면 `site_import`를 비활성화하지 않는다.
- Windows용 `InitializeProjectPython()`의 `Lib`, `DLLs`, `Lib/site-packages` 고정 경로를 Linux에 그대로 사용하지 않는다.
- Linux 표준 라이브러리는 보통 `lib/pythonX.Y` 등에 있으며 배포본에 따라 다르다.
- venv 디렉터리를 Python 본체의 `home`으로 취급하지 않는다.

- 초기화 설정 작성 전에 사용할 Python 정보를 확인한다.

```bash
python -c 'import sys, sysconfig; print(sys.executable); print(sys.prefix); print(sys.base_prefix); print(sysconfig.get_paths())'
```

- 명령줄에서 직접 링크한다면 C++에 Python을 임베딩하는 용도로 해당 Python의 `python3-config --embed --ldflags`를 참고한다. Python 확장 모듈의 링크 조건과 구분한다.

#### 🔹 18.6 GUI 없이 이미지를 저장할 때

```bash
python -m pip install matplotlib pyvista
python -c 'import matplotlib, pyvista; print(matplotlib.__version__); print(pyvista.__version__)'
```

- Matplotlib은 `Agg` 백엔드를 선택한다. PyVista는 `off_screen=True`와 함께 VTK가 사용할 수 있는 렌더링 환경을 준비한다.
- 현재 PyVista 자료에는 VTK 9.5 이상 표준 PyPI wheel에서 Linux EGL 헤드리스 렌더링을 사용하는 방법이 설명되어 있다.
- Ubuntu/Debian에서는 `libegl1` 등의 런타임 라이브러리와 GPU 사용 시 해당 드라이버를 확인한다.
- 이전 VTK 구성에서는 Xvfb 등이 필요할 수 있으므로 VTK 버전과 렌더링 백엔드를 먼저 확인한다.

```bash
python -c 'import vtk; print(vtk.vtkVersion.GetVTKVersion())'
```

- 이 Linux 절차는 빌드와 연결 방법을 정리한 것이며, 대상 서버의 GPU나 컨테이너에서 이미지 생성을 실행 검증한 결과는 아니다.

### 📌 19. 공식 자료

- [Boost.Python의 Python 구성](https://boostorg.github.io/python/doc/html/building/configuring_boost_build.html): using python의 인자와 설정.
- [B2 User Manual](https://www.boost.org/latest/tools/build/doc/html/index.html): toolset, variant, link, 설정 파일.
- [Python debugging builds](https://www.boost.org/doc/libs/latest/libs/python/doc/html/building/python_debugging_builds.html): 일반 Python과 C++ Debug 조합, BOOST_DEBUG_PYTHON.
- [Boost Windows 도입 자료](https://www.boost.org/doc/libs/1_79_0/more/getting_started/windows.html): 빌드와 라이브러리 이름. 문서 버전이 다르므로 사용 버전과의 차이를 확인한다.
- [Python 3.12 초기화 설정](https://docs.python.org/3.12/c-api/init_config.html): PyConfig와 분리 설정.
- [CMake MSVC_RUNTIME_LIBRARY](https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html): MSVC CRT 지정.
- [PyVista 설치](https://docs.pyvista.org/getting-started/installation): VTK와 렌더링 환경.
- [Python 임베딩 및 Unix 링크 설정](https://docs.python.org/3.12/extending/embedding.html#compiling-and-linking-under-unix-like-systems): python-config의 --embed 사용.
- [CMake FindPython3](https://cmake.org/cmake/help/latest/module/FindPython3.html): Interpreter, Development.Embed, Python3::Python.
