## 📘 Boost.Python → Python `.pyd` 개발 참고

> Windows x64 · MSVC · CMake · Boost 1.92 · Python 3.12 · Release  
> 목적: C++ CAD 라이브러리 바인딩부터 빌드, 테스트, 배포까지 다시 따라 하기.

### 📌 1. 개념

- `.pyd`는 Windows용 CPython 확장 DLL이며 `import python_lib`로 불러온다.
- `BOOST_PYTHON_MODULE(python_lib)`의 이름과 `.pyd` 파일의 모듈 이름이 같아야 한다.
- C++ 계산 코드는 그대로 두고 `PythonBinding.cpp`에 공개 인터페이스를 정의한다.
- 일반적인 Boost.Python은 Python 버전·아키텍처·런타임에 종속된다. 버전 변경 시 재빌드한다.
- 배포용은 C++ 라이브러리, Boost.Python, `.pyd`를 모두 Release로 빌드한다.

#### 🔹 DLL - PYD로 바꾸기
```cmake
set_target_properties(python_lib PROPERTIES
        PREFIX ""
        SUFFIX ".pyd"
)
```
#### 🔹 PYD 복사하기
```cmake
# Python 모듈을 복사할 디렉터리
set(PYTHON_MODULE_DIR
        "${CMAKE_SOURCE_DIR}/Python312/DLLs"
)

add_custom_command(TARGET python_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "${PYTHON_MODULE_DIR}"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:python_lib>"
        "${PYTHON_MODULE_DIR}"

        COMMENT "Copying python_lib.pyd to Python312"
)
```

### 📌 2. 최소 C++ 예제

**Vector3.h**
```cpp
#pragma once
struct Vector3 {
    double x = 0, y = 0, z = 0;
    Vector3() = default;
    Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
    Vector3 operator+(const Vector3& v) const {
        return {x+v.x, y+v.y, z+v.z};
    }
};
```

**PythonBinding.cpp**
```cpp
#include <boost/python.hpp>
#include "Vector3.h"
namespace py = boost::python;

BOOST_PYTHON_MODULE(python_lib) {
    py::class_<Vector3>("Vector3", py::init<>())
        .def(py::init<double,double,double>())
        .def_readwrite("x", &Vector3::x)
        .def_readwrite("y", &Vector3::y)
        .def_readwrite("z", &Vector3::z)
        .def(py::self + py::self);
}
```

- 공개 필드는 `.def_readwrite`;
- getter/setter는 `.add_property("X", &Vector3::getX, &Vector3::setX)`.
- `.def(py::self + py::self)`는 C++ `operator+`를 Python `+`에 연결한다.
- 같은 이름의 C++ 오버로드는 `static_cast`로 함수 포인터 타입을 지정하여 각각 `.def`한다.

### 📌 3. CMake로 `.pyd` 생성

- 아래는 Boost가 CMake 패키지로 발견되는 환경의 예다. `Boost::python312`는 설치 방식에 따라 달라질 수 있다.

```cmake
cmake_minimum_required(VERSION 3.20)
project(CADPython LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 3.12 REQUIRED COMPONENTS Interpreter Development)
find_package(Boost 1.92 REQUIRED COMPONENTS python312)

add_library(python_lib MODULE PythonBinding.cpp)
set_target_properties(python_lib PROPERTIES PREFIX "" SUFFIX ".pyd")
target_link_libraries(python_lib PRIVATE Boost::python312 Python3::Python)

set(PYTHON_MODULE_DIR "${CMAKE_SOURCE_DIR}/Python312")
add_custom_command(TARGET python_lib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PYTHON_MODULE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CONFIG=$<CONFIG>"
    COMMAND ${CMAKE_COMMAND} -E echo "SOURCE=$<TARGET_FILE:python_lib>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:python_lib>" "${PYTHON_MODULE_DIR}"
    VERBATIM)
```

**확인 사항**
1. CLion → Settings → Build, Execution, Deployment → CMake → Release 프로필.
2. 단일 구성 생성기는 `CMAKE_BUILD_TYPE=Release`; 다중 구성 생성기는 빌드 구성 `Release`.
3. `target_link_directories()`는 *링커 검색 경로*이지 `.pyd` 출력 경로가 아니다.
4. `$<TARGET_FILE:python_lib>`는 현재 빌드 구성의 실제 출력 파일을 가리킨다.
5. `POST_BUILD`는 타깃이 다시 빌드될 때 실행된다. Debug/Release를 같은 복사 폴더에 섞지 않는 것이 좋다.
6. Boost.Python과 Python 헤더/라이브러리의 버전·x64 여부를 맞춘다.

### 📌 4. Python 테스트

```python
import python_lib
a = python_lib.Vector3(1, 2, 3)
b = python_lib.Vector3(4, 5, 6)
c = a + b
assert (c.x, c.y, c.z) == (5, 7, 9)
print("PASS")
```

- `.pyd` 폴더가 `sys.path`에 있어야 한다.
- `ModuleNotFoundError`와 의존 DLL을 못 찾는 `DLL load failed`는 다른 문제다.
- DLL 경로는 설치 폴더 구성이나 `os.add_dll_directory(...)`로 관리한다.

### 📌 5. Model–Geometry: 실무용 소유권

- **권장**: `Model`이 `Geometry`를 `unique_ptr`로 소유하고 Python은 기존 객체를 참조한다.

```cpp
#include <memory>
#include <vector>
#include <stdexcept>

struct Geometry {
    virtual ~Geometry() = default;
};
struct PointGeometry : Geometry {
    Vector3 position;
    Vector3 getPosition() const { return position; }
    void setPosition(const Vector3& p) { position = p; }
    void setPosition(const PointGeometry& p) { position = p.position; }
};
class Model {
    std::vector<std::unique_ptr<Geometry>> items_;
public:
    PointGeometry& addPoint(const Vector3& p) {
        auto obj = std::make_unique<PointGeometry>();
        obj->position = p;
        PointGeometry& ref = *obj;
        items_.push_back(std::move(obj));
        return ref;
    }
    Geometry& getGeometry(std::size_t i) { return *items_.at(i); }
    std::size_t geometryCount() const { return items_.size(); }
};
```

- 바인딩(기존 `BOOST_PYTHON_MODULE` 안에 추가):
```cpp
py::class_<Geometry, boost::noncopyable>("Geometry", py::no_init);

py::class_<PointGeometry, py::bases<Geometry>, boost::noncopyable>(
    "PointGeometry", py::no_init)
    .def("getPosition", &PointGeometry::getPosition)
    .def("setPosition",
         static_cast<void (PointGeometry::*)(const Vector3&)>(
             &PointGeometry::setPosition))
    .def("setPosition",
         static_cast<void (PointGeometry::*)(const PointGeometry&)>(
             &PointGeometry::setPosition));

py::class_<Model, boost::noncopyable>("Model")
    .def("addPoint", &Model::addPoint, py::return_internal_reference<>())
    .def("getGeometry", &Model::getGeometry,
         py::return_internal_reference<>())
    .def("geometryCount", &Model::geometryCount);
```

```python
model = python_lib.Model()
p1 = model.addPoint(python_lib.Vector3(1, 2, 3))
p2 = model.addPoint(python_lib.Vector3(4, 5, 6))
p1.setPosition(p2)                # PointGeometry 오버로드
p1.setPosition(p2.getPosition())  # Vector3 오버로드
```

- `std::vector<std::unique_ptr<Geometry>>`가 재할당되어도 개별 Geometry의 주소는 유지된다.
- **그러나 Geometry 자체를 삭제하면 참조가 무효화된다.** `return_internal_reference<>`는 Python 측에서 부모 Model의 수명을 연결하지만 C++에서 임의 삭제한 객체까지 보호하지는 않는다.
- 이 예제에서는 개별 삭제를 제공하지 않는다.

### 📌 6. 포인터 반환 정책

| C++ 반환 | Boost.Python 정책 | 소유권 |
|---|---|---|
| `Vector3` 값 | 기본 | Python에 독립 값 |
| `new Foo`로 만든 `Foo*` | `return_value_policy<manage_new_object>()` | Python으로 이전 |
| Model 내부의 `Geometry&` | `return_internal_reference<>()` | Model 소유 유지, Python 부모 수명 연결 |
| 기존 외부 객체 `Foo*` | `reference_existing_object` | Python은 소유하지 않음; 수명 보장 별도 필요 |
| `boost::shared_ptr<Foo>` | `class_<Foo, boost::shared_ptr<Foo>>` | 공유 소유 |

```cpp
py::class_<Bar>("Bar")
    .def("makeFoo", &Bar::makeFoo,
         py::return_value_policy<py::manage_new_object>());
```

- **주의:** Model 내부 객체에 `manage_new_object`를 적용하면 이중 삭제 위험이 있다.

### 📌 7. Geometry 목록을 Python list로 반환

- C++ 멤버 `boost::python::list Model::getGeometries()`가 있다면 등록 자체는 다음 한 줄이다.

```cpp
.def("getGeometries", &Model::getGeometries)
```

- 하지만 리스트 내부의 `Geometry*` 수명은 별도 고려해야 한다.
- **C++ 코어에 Boost 의존성을 넣지 않으려면** 바인딩 계층에서 이미 등록한 `getGeometry`를 호출한다.

```cpp
static py::list GetGeometries(py::object modelObj) {
    Model& model = py::extract<Model&>(modelObj);
    py::list result;
    for (std::size_t i = 0; i < model.geometryCount(); ++i)
        result.append(modelObj.attr("getGeometry")(i));
    return result;
}
```

```cpp
.def("getGeometries", &GetGeometries)
```

- 이렇게 하면 각 요소에 `getGeometry`의 `return_internal_reference<>`가 적용된다.
- 반환 리스트는 목록의 **스냅샷**이다. 리스트의 `append/pop`은 Model에 반영되지 않는다.
- 대규모 CAD 모델은 전체 리스트 대신 인덱스/지연 반복자 사용을 검토한다.

### 📌 8. NumPy 배열 연동

```cpp
#include <boost/python/numpy.hpp>
namespace np = boost::python::numpy;
BOOST_PYTHON_MODULE(python_lib) {
    np::initialize();
    // ... bindings ...
}
```

- Boost.NumPy 라이브러리도 별도로 링크해야 한다(환경에 따라 `boost_numpy312`).

- `setNodes(ndarray)`는 다음 순서로 작성한다.

1. `array.get_nd() == 2` 검사 **후** `shape(1) == 3` 검사.
2. dtype이 네이티브 엔디언 `float64`인지 검사.
3. `strides(0)`, `strides(1)`으로 비연속 배열/슬라이스/역순 지원.
4. 임시 `std::vector<Vector3>`에 `reserve()` 후 값을 채우고 `swap()`으로 교체.
5. `getNodes()`는 `np::empty((N,3), float64)`에 데이터를 복사해 반환.

- **Zero-copy는 별도 과제**: NumPy가 C++ 메모리를 직접 참조하면 수명, 재할당, 수정 권한을 함께 설계해야 한다.

### 📌 9. 배포

```text
CADLibrary/
├── bin/       # CAD 실행 파일, C++ DLL
├── python/    # 고정 버전 Python 3.12 런타임
├── modules/   # python_lib.pyd, Boost.Python/Boost.NumPy DLL
├── packages/  # NumPy/pandas 등 검증된 패키지
└── scripts/   # 테스트 및 예제
```

- Python 3.12 런타임과 필요한 패키지를 함께 배포한다.
- Python embeddable 배포판은 최소 구성이다. NumPy/pandas는 별도 구성하고 `._pth` 설정을 확인한다.
- `.pyd`의 직접·간접 DLL, MSVC 런타임 의존성을 확인한다.
- Python/Visual Studio가 없는 깨끗한 Windows VM에서 `import`, 계산, 종료 테스트를 진행한다.
- 배포 폴더 검증 후 Inno Setup 또는 WiX로 `Setup.exe`를 제작한다.

### 📌 10. 문제 해결표

| 증상 | 점검 |
|---|---|
| `ModuleNotFoundError` | `.pyd` 이름, Python `sys.path` |
| `DLL load failed` | 의존 DLL, DLL 검색 경로, x64, MSVC 런타임 |
| `dynamic module does not define module export function` | `BOOST_PYTHON_MODULE` 이름과 모듈명 |
| `Boost.Python.ArgumentError` | 인수 타입, 오버로드 등록 |
| `No to_python converter` | 반환 타입 바인딩, 반환 정책 |
| Release인데 Debug 파일 복사 | CMake 프로필, `$<CONFIG>`, `$<TARGET_FILE:...>`, 기존 복사 파일 |
| 종료 시 크래시 | 이중 삭제, 소유권, 수명보다 오래 살아 있는 참조 |
| NumPy 슬라이스에서 오작동 | ndim, dtype, strides, endian |

### 📌 11. 작업 재개 체크리스트

- [ ] Python 버전과 Boost.Python 버전/x64 확인
- [ ] CMake Release 구성에서 `.pyd` 빌드
- [ ] `BOOST_PYTHON_MODULE`과 `.pyd` 이름 확인
- [ ] Python `import python_lib` 테스트
- [ ] `Vector3` 생성·연산 테스트
- [ ] `Model` 생성·Geometry 참조·소유권 테스트
- [ ] NumPy 연속/비연속/빈 배열 테스트
- [ ] 의존 DLL 수집 및 깨끗한 Windows에서 실행 검증

---

- **핵심 원칙:** C++ `Model`이 CAD 객체를 소유하고 Boost.Python은 인터페이스·반환 정책·수명 연결을 담당한다.
- 작은 값은 복사, Model 내부 객체는 안전한 참조, 대량 데이터는 검증된 NumPy 변환으로 처리한다.
