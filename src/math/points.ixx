/**
 * @brief Point classes
 *
 */
module;

#include <array>
#include <cmath>
#include <format>
#include <stdexcept>
#include <string>
#include <typeinfo>

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
struct Point : Cartesian<TYPE, SIZE> {
  std::array<TYPE, SIZE> values;

  /**
   * @brief get a number by it's index
   *
   * @param idx
   * @return Numeric TYPE& float in Python
   */
  TYPE &operator[](unsigned short int idx) { return values[idx]; }

  const bool operator==(Cartesian<TYPE, SIZE> &other) {
    if (typeid(TYPE) != typeid(int))
      throw std::logic_error("You can only compare vectors of type int, for "
                             "other types use approximately");
    for (unsigned short int i = 0; i < SIZE; i++)
      if (values[i] != other[i])
        return false;

    return true;
  }

  std::string to_string() {
    std::string name;

    if (typeid(TYPE) == typeid(int))
      name = std::format("Point{}Int(", SIZE);
    else
      name = std::format("Point{}(", SIZE);

    for (size_t i = 0; i < SIZE; i++) {
      name += std::to_string(values[i]);
      if (i < SIZE - 1)
        name += ", ";
    }

    name += ")";
    return name;
  }

  FORCE_INLINE bool
  approximately(Point<TYPE, SIZE> other,
                TYPE tolerance = std::numeric_limits<TYPE>::epsilon()) {
    if (typeid(TYPE) == int_id)
      return this == other;
    else
      for (size_t i; i < SIZE; i++)
        if (!ClockworkReverie::Math::approximately<TYPE>(values[i], other[i],
                                                         tolerance))
          return false;

    return true;
  }
};

NUMERIC_TEMPLATE
struct Point2 final : Point<TYPE, 2>, Cartesian2<TYPE> {
  Point2(TYPE x_axis, TYPE y_axis) {
    set_x(x_axis);
    set_y(y_axis);
  }

  TYPE get_x() const { return this->values[0]; }
  TYPE get_y() const { return this->values[1]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }

};

NUMERIC_TEMPLATE
struct Point3 final : Point<TYPE, 3>, Cartesian3<TYPE> {
  Point3(TYPE x_axis, TYPE y_axis, TYPE z_axis) {
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
struct Point4 final : Point<TYPE, 4>, Cartesian4<TYPE> {
  Point4(TYPE x_axis, TYPE y_axis, TYPE z_axis, TYPE w_axis) {
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
