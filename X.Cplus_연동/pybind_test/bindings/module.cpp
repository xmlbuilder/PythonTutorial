//
// Created by THJ on 2025-10-05.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/MyThing.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mything, m) {
    m.doc() = "Minimal pybind11 example exposing a C++ class";

    py::class_<MyThing>(m, "MyThing", R"doc(
A tiny demo class with one member variable, a member method, and a static method.
)doc")
        // 생성자
        .def(py::init<int>(), py::arg("value") = 0, "Create with initial value")

        // value 프로퍼티 (getter/setter)
        .def_property("value", &MyThing::get_value, &MyThing::set_value,
                      "The internal integer value")

        // 멤버 메소드
        .def("increment", &MyThing::increment, py::arg("delta"),
             "Increase value by delta and return the new value")

        // 정적 메소드
        .def_static("version", &MyThing::version, "Return library version");
}
