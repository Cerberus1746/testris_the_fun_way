#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

import clockwork_reverie;
import clockwork_reverie.utils;

import clockwork_reverie.math;
import clockwork_reverie.math.utils;
import clockwork_reverie.math.vectors;

import vectors;

namespace nb = nanobind;
using namespace nb::literals;

namespace reverie = ClockworkReverie;
namespace math = reverie::Math;
namespace python = reverie::Python;
namespace utils = reverie::Utils;

NB_MODULE(clockwork_reverie_py, m) {
  /*nb::class_<reverie::EngineObject>(m, "EngineObject")
      .def(nb::init<const std::string &>());*/
  nb::class_<reverie::Main>(m, "Main").def(
      nb::init<std::string &, utils::Version &>(), "name"_a, "version"_a);

  {
    auto py_utils = m.def_submodule("utils");

    nb::class_<utils::Version>(py_utils, "Version")
        .def(nb::init<int &, int &, int &>(), "major"_a, "minor"_a, "patch"_a);
  }

  {
    auto py_math = m.def_submodule("math");

    {
      auto py_math_utils = py_math.def_submodule("utils");

      py_math_utils.def(
          "approximately", &math::approximately<double>,
          "Compare two floating points together", "left"_a, "right"_a,
          "tolerance"_a = std::numeric_limits<double>::epsilon());
    }

    // Vectors Declaration
    {
      auto py_math_vectors = py_math.def_submodule("vectors");

      python::declare_vector2<double>(py_math_vectors, "");
      python::declare_vector2<int>(py_math_vectors, "Int");

      python::declare_vector3<double>(py_math_vectors, "");
      python::declare_vector3<int>(py_math_vectors, "Int");

      python::declare_vector4<double>(py_math_vectors, "");
      python::declare_vector4<int>(py_math_vectors, "Int");
    }
  }
}
