#include <nanobind/nanobind.h>

import math;
import math.utils;
import math.vector2;
import math.vector3;
import math.vector4;

namespace math = FunEngine::Math;
namespace nb = nanobind;

template <math::Numeric TYPE>
void declare_vector2(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector2<TYPE>;
  std::string pyclass_name = "Vector2" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &>())
      .def("angle", &Class::angle)
      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude)
      .def("__repr__", &Class::to_string);
}

template <math::Numeric TYPE>
void declare_vector3(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector3<TYPE>;
  std::string pyclass_name = "Vector3" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &, TYPE &>())
      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude)
      .def("__repr__", &Class::to_string);
}

template <math::Numeric TYPE>
void declare_vector4(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector4<TYPE>;
  std::string pyclass_name = "Vector4" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &, TYPE &, TYPE &>())
      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude)
      .def("__repr__", &Class::to_string);
}

NB_MODULE(funenginepy, m) {
  /*nb::class_<fun::EngineObject>(m, "EngineObject")
      .def(nb::init<const std::string &>());*/

  auto math_module = m.def_submodule("math");

  math_module.def("approximately", &math::approximately<double>,
                  "Compare two floating points together", nb::arg("left"),
                  nb::arg("right"),
                  nb::arg("tolerance") =
                      std::numeric_limits<double>::epsilon());

  declare_vector2<double>(math_module, "");
  declare_vector2<int>(math_module, "Int");

  declare_vector3<double>(math_module, "");
  declare_vector3<int>(math_module, "Int");

  declare_vector4<double>(math_module, "");
  declare_vector4<int>(math_module, "Int");
}
