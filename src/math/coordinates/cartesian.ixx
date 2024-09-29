/**
 * @brief Base abstract classes for any object that implement coordinate<br />
 *        system, for example, Vector and Point
 *
 */
module;

#include <stdexcept>

#include "constants.hpp"

export module clockwork_reverie.math.cartesian;

import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {
template <Numeric TYPE, unsigned short int SIZE = 1> struct CartesianBase {
  std::array<TYPE, SIZE> values;

  /**
   * @brief get a number by it's index
   *
   * @param idx
   * @return Numeric TYPE&. `float` by default in Python
   */
  FORCE_INLINE virtual TYPE &operator[](unsigned short int idx) {
    return values[idx];
  }

  bool operator==(CartesianBase<TYPE, SIZE> &other) {
    if constexpr (std::is_same<TYPE, int>::value)
      throw std::logic_error("You can only compare vectors of type int, for "
                             "other types use approximately");

    for (unsigned short int i = 0; i < SIZE; i++)
      if (values[i] != other[i])
        return false;

    return true;
  }

  FORCE_INLINE auto
  approximately(CartesianBase<TYPE, SIZE> other,
                TYPE tolerance = std::numeric_limits<TYPE>::epsilon()) {
    if constexpr (std::is_same<TYPE, int>::value)
      return this == other;

    for (unsigned short int i = 0; i < SIZE; i++)
      if (!approximately<TYPE>(this->values[i], other[i], tolerance))
        return false;

    return true;
  }
};

template <Numeric TYPE, unsigned short int SIZE = 1> struct Cartesian {};

NUMERIC_TEMPLATE struct Cartesian<TYPE, 2> {
  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
};

template <Numeric TYPE> struct Cartesian<TYPE, 3> {
  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;
  virtual TYPE get_z() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
  virtual void set_z(TYPE value) = 0;
};

template <Numeric TYPE> struct Cartesian<TYPE, 4> {
  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;
  virtual TYPE get_z() const = 0;
  virtual TYPE get_w() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
  virtual void set_z(TYPE value) = 0;
  virtual void set_w(TYPE value) = 0;
};
} // namespace ClockworkReverie::Math
