/**
 * @brief Point classes
 *
 */
module;

#include <cmath>
#include <format>

#include "constants.hpp"

export module clockwork_reverie.math.points;

import clockwork_reverie.math.cartesian;
import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {

/**
 * @brief Base Cartesian location, similar to vectors but more basic
 *
 * @tparam Numeric TYPE float in Python.
 * @tparam SIZE
 */
template <Numeric TYPE = double, unsigned short int SIZE = 1>
struct PointBase : CartesianBase<TYPE, SIZE> {
  std::string to_string() {
    std::string name;

    if constexpr (std::is_same<TYPE, int>::value)
      name = std::format("Point{}Int(", SIZE);
    else
      name = std::format("Point{}(", SIZE);

    for (size_t i = 0; i < SIZE; i++) {
      name += std::to_string(this->values[i]);
      if (i < SIZE - 1)
        name += ", ";
    }

    name += ")";
    return name;
  }
};

template <Numeric TYPE = double, unsigned short int SIZE = 1>
struct Point : PointBase<TYPE, SIZE> {};

NUMERIC_TEMPLATE
struct Point<TYPE, 2> : PointBase<TYPE, 2>, Cartesian<TYPE, 2> {
  Point(TYPE x_axis, TYPE y_axis) {
    set_x(x_axis);
    set_y(y_axis);
  }

  TYPE get_x() const { return this->values[0]; }
  TYPE get_y() const { return this->values[1]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }
};

NUMERIC_TEMPLATE
struct Point<TYPE, 3> : PointBase<TYPE, 3>, Cartesian<TYPE, 3> {
  Point(TYPE x_axis, TYPE y_axis, TYPE z_axis) {
    set_x(x_axis);
    set_y(y_axis);
    set_z(z_axis);
  }

  TYPE get_x() const { return this->values[0]; }
  TYPE get_y() const { return this->values[1]; }
  TYPE get_z() const { return this->values[2]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }
  void set_z(TYPE value) { this->values[2] = value; }
};

NUMERIC_TEMPLATE
struct Point<TYPE, 4> : PointBase<TYPE, 4>, Cartesian<TYPE, 4> {
  Point(TYPE x_axis, TYPE y_axis, TYPE z_axis, TYPE w_axis) {
    set_x(x_axis);
    set_y(y_axis);
    set_z(z_axis);
    set_w(w_axis);
  }

  TYPE get_x() const { return this->values[0]; }
  TYPE get_y() const { return this->values[1]; }
  TYPE get_z() const { return this->values[2]; }
  TYPE get_w() const { return this->values[3]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }
  void set_z(TYPE value) { this->values[2] = value; }
  void set_w(TYPE value) { this->values[3] = value; }
};
} // namespace ClockworkReverie::Math
