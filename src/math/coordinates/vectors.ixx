/**
 * @brief Vector classes
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

export module clockwork_reverie.math.vectors;

import clockwork_reverie.math.cartesian;
import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {

/**
 * @brief Base Cartesian vector
 *
 * @tparam Numeric TYPE float in Python.
 * @tparam SIZE
 */
template <Numeric TYPE, unsigned short int SIZE> struct VectorBase {
  std::array<TYPE, SIZE> values;

  /**
   * @brief get a number by it's index
   *
   * @param idx
   * @return Numeric TYPE& float in Python
   */
  TYPE &operator[](unsigned short int idx) { return values[idx]; }

  bool operator==(CartesianBase<TYPE, SIZE> &other) {
    if (typeid(TYPE) != typeid(int)) {
      throw std::logic_error("You can only compare vectors of type int, for "
                             "other types use approximately");
    }
    for (unsigned short int i = 0; i < SIZE; i++)
      if (values[i] != other[i])
        return false;
    return true;
  }

  std::string to_string() {
    std::string vec_str;
    if (typeid(TYPE) == typeid(int))
      vec_str = std::format("Vector{}Int(", SIZE);
    else
      vec_str = std::format("Vector{}(", SIZE);

    for (size_t i = 0; i < SIZE; i++) {
      vec_str += std::to_string(values[i]);
      if (i < SIZE - 1)
        vec_str += ", ";
    }

    vec_str += ")";
    return vec_str;
  }

  /// multiply elements one by one
  FORCE_INLINE auto pi_notation() {
    auto curr_value = values[0];

    if (SIZE == 1)
      return curr_value;

    for (size_t i = 1; i < SIZE; i++)
      curr_value *= values[i];

    return curr_value;
  }

  FORCE_INLINE auto magnitude() const {
    double curr_sum = 0;

    for (auto curr_value : values)
      curr_sum += pow(curr_value, 2);

    return sqrt(curr_sum);
  }

  /// magnitude, but clamped to speed of light
  FORCE_INLINE auto velocity() {
    auto mag = magnitude();
    return mag < LIGHT_SPEED ? mag : LIGHT_SPEED;
  }

  FORCE_INLINE auto angle_to(VectorBase<TYPE, SIZE> other) {
    auto sums = this->pi_notation() + other.pi_notation();
    auto magnitudes = this->magnitude() * other.magnitude();
    return acos(sums / magnitudes);
  }

  FORCE_INLINE auto
  approximately(VectorBase<TYPE, SIZE> other,
                TYPE tolerance = std::numeric_limits<TYPE>::epsilon()) {
    if (typeid(TYPE) == int_id)
      return this == other;

    for (unsigned short int i = 0; i < SIZE; i++)
      if (!ClockworkReverie::Math::approximately<TYPE>(values[i], other[i],
                                                       tolerance))
        return false;

    return true;
  }
};

template <Numeric TYPE = double, unsigned short int SIZE = 1>
struct Vector : VectorBase<TYPE, SIZE>, Cartesian<TYPE, SIZE> {};

NUMERIC_TEMPLATE struct Vector<TYPE, 2> : VectorBase<TYPE, 2>,
                                          Cartesian<TYPE, 2> {
  Vector(TYPE x_axis, TYPE y_axis) {
    set_x(x_axis);
    set_y(y_axis);
  }

  TYPE get_x() const { return this->values[0]; }
  TYPE get_y() const { return this->values[1]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }

  double angle() { return atan2(this->values[1], this->values[0]); }
};

NUMERIC_TEMPLATE
struct Vector<TYPE, 3> : VectorBase<TYPE, 3>, Cartesian<TYPE, 3> {
  Vector(TYPE x_axis, TYPE y_axis, TYPE z_axis) {
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
struct Vector<TYPE, 4> : VectorBase<TYPE, 4>, Cartesian<TYPE, 4> {
  Vector(TYPE x_axis, TYPE y_axis, TYPE z_axis, TYPE w_axis) {
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
