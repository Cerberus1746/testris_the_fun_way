/**
 * @brief Base abstract classes for any object that implement coordinate<br />
 *        system, for example, Vector and Point
 *
 */
module;

#include <string>

#include "constants.hpp"

export module clockwork_reverie.math.cartesian;

import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {
template <Numeric TYPE, unsigned short int SIZE = 1> struct Cartesian {
  virtual ~Cartesian() {}

  virtual TYPE &operator[](unsigned short int idx) = 0;
  virtual bool operator==(Cartesian<TYPE, SIZE> &other) = 0;
  virtual std::string to_string() = 0;
};

NUMERIC_TEMPLATE struct Cartesian2 {
  virtual ~Cartesian2() {}

  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
};

template <Numeric TYPE> struct Cartesian3 {
  virtual ~Cartesian3() {}

  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;
  virtual TYPE get_z() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
  virtual void set_z(TYPE value) = 0;
};

template <Numeric TYPE> struct Cartesian4 {
  virtual ~Cartesian4() {}

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
