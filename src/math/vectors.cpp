module;

#include <array>
#include <cmath>
#include <format>
#include <stdexcept>
#include <string>
#include <typeinfo>

#include "constants.hpp"

export module FunEngine.math.vectors;

import FunEngine;
import FunEngine.math;
import FunEngine.math.utils;

export namespace FunEngine::Math {
template <Numeric TYPE = double, unsigned short int SIZE = 1> struct Vector {
  std::array<TYPE, SIZE> values{};

  TYPE &operator[](size_t idx) { return values[idx]; }

  bool operator==(Vector<TYPE, SIZE> &other) {
    if (typeid(TYPE) != typeid(int))
      throw std::logic_error("You can only compare vectors of type int, for "
                             "other types use approximately");
    for (size_t i; i < SIZE; i++)
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
  FORCE_INLINE TYPE pi_notation() {
    auto curr_value = values[0];

    if (SIZE == 1)
      return curr_value;

    for (size_t i = 1; i < SIZE; i++)
      curr_value *= values[i];

    return curr_value;
  }

  FORCE_INLINE double magnitude() const {
    double curr_sum = 0;

    for (auto curr_value : values)
      curr_sum += pow(curr_value, 2);

    return sqrt(curr_sum);
  }

  /// magnitude, but clamped to speed of light
  FORCE_INLINE TYPE velocity() {
    auto mag = magnitude();
    return mag < LIGHT_SPEED ? mag : LIGHT_SPEED;
  }

  FORCE_INLINE TYPE angle_to(Vector<TYPE, SIZE> to) {
    auto sums = this->pi_notation() + to.pi_notation();
    auto magnitudes = this->magnitude() * to.magnitude();
    return acos(sums / magnitudes);
  }

  FORCE_INLINE bool
  approximately(Vector<TYPE, SIZE> other,
                TYPE tolerance = std::numeric_limits<TYPE>::epsilon()) {
    if (typeid(TYPE) == int_id)
      return this == other;
    else
      for (size_t i; i < SIZE; i++)
        if (!FunEngine::Math::approximately<TYPE>(values[i], other[i],
                                                  tolerance))
          return false;

    return true;
  }
};

template <Numeric TYPE = double>
struct Vector2 final : Vector<TYPE, 2> {
  TYPE *x_axis = &this->values[0];
  TYPE *y_axis = &this->values[1];

  using Vector<TYPE, 2>::Vector;
  Vector2(TYPE x_axis, TYPE y_axis) : Vector<TYPE, 2>({x_axis, y_axis}) {}

  TYPE get_x() { return this->values[0]; }
  TYPE get_y() { return this->values[1]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }

  double angle() { return atan2(this->values[1], this->values[0]); }
};

template <Numeric TYPE = double>
struct Vector3 final : Vector<TYPE, 3> {
  using Vector<TYPE, 3>::Vector;

  Vector3(TYPE x_axis, TYPE y_axis, TYPE z_axis)
      : Vector<TYPE, 3>({x_axis, y_axis, z_axis}) {}

  TYPE get_x() { return this->values[0]; }
  TYPE get_y() { return this->values[1]; }
  TYPE get_z() { return this->values[2]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }
  void set_z(TYPE value) { this->values[2] = value; }
};

template <typename TYPE = double>
struct Vector4 final : Vector<TYPE, 4> {
  using Vector<TYPE, 4>::Vector;

  Vector4(TYPE x_axis, TYPE y_axis, TYPE z_axis, TYPE w_axis)
      : Vector<TYPE, 4>({x_axis, y_axis, z_axis, w_axis}) {}

  TYPE get_x() { return this->values[0]; }
  TYPE get_y() { return this->values[1]; }
  TYPE get_z() { return this->values[2]; }
  TYPE get_w() { return this->values[3]; }

  void set_x(TYPE value) { this->values[0] = value; }
  void set_y(TYPE value) { this->values[1] = value; }
  void set_z(TYPE value) { this->values[2] = value; }
  void set_w(TYPE value) { this->values[3] = value; }
};
} // namespace FunEngine::Math
