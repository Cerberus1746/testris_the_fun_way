#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <string>

import math;
import math.utils;
import math.vectors;

namespace math = FunEngine::Math;
namespace nb = nanobind;

template <math::Numeric TYPE>
void declare_vector2(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector2<TYPE>;
  std::string pyclass_name = (std::string) "Vector2" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &>())
      // Data
      .def("__repr__", &Class::to_string)

      // Getters
      .def("get_x", &Class::get_x)
      .def("get_y", &Class::get_y)

      // Setters
      .def("set_x", &Class::set_x)
      .def("set_y", &Class::set_y)

      // Properties
      .def_prop_rw("x_axis", &Class::get_x, &Class::set_x)
      .def_prop_rw("y_axis", &Class::get_y, &Class::set_y)

      .def("angle", &Class::angle_to)
      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude);

}

template <math::Numeric TYPE>
void declare_vector3(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector3<TYPE>;
  std::string pyclass_name = (std::string) "Vector3" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &, TYPE &>())

      // Data
      .def("__repr__", &Class::to_string)

      // Getters
      .def("get_x", &Class::get_x)
      .def("get_y", &Class::get_y)
      .def("get_z", &Class::get_z)

      // Setters
      .def("set_x", &Class::set_x)
      .def("set_y", &Class::set_y)
      .def("set_z", &Class::set_z)

      // Properties
      .def_prop_rw("x_axis", &Class::get_x, &Class::set_x)
      .def_prop_rw("y_axis", &Class::get_y, &Class::set_y)
      .def_prop_rw("z_axis", &Class::get_z, &Class::set_z)

      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude);
}

template <math::Numeric TYPE>
void declare_vector4(nb::module_ &m, const std::string &type_name) {
  using Class = math::Vector4<TYPE>;
  std::string pyclass_name = (std::string) "Vector4" + type_name;
  nb::class_<Class>(m, pyclass_name.c_str())
      .def(nb::init<TYPE &, TYPE &, TYPE &, TYPE &>())

      // Data
      .def("__repr__", &Class::to_string)

      // Getters
      .def("get_x", &Class::get_x)
      .def("get_y", &Class::get_y)
      .def("get_z", &Class::get_z)
      .def("get_w", &Class::get_w)

      // Setters
      .def("set_x", &Class::set_x)
      .def("set_y", &Class::set_y)
      .def("set_z", &Class::set_z)
      .def("set_w", &Class::set_w)

      // Properties
      .def_prop_rw("x_axis", &Class::get_x, &Class::set_x)
      .def_prop_rw("y_axis", &Class::get_y, &Class::set_y)
      .def_prop_rw("z_axis", &Class::get_z, &Class::set_z)
      .def_prop_rw("w_axis", &Class::get_w, &Class::set_w)

      .def("angle_to", &Class::angle_to)
      .def("magnitude", &Class::magnitude);
}

NB_MODULE(FunEnginePy, m) {
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
