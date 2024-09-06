module;

#include <string>
#include "constants.hpp"

export module engine.math.coordinate;

import engine.math;

export namespace ClockworkReverie::Math {
template <Numeric TYPE, unsigned short int SIZE = 1> struct Coordinate {
  virtual ~Coordinate() {}

  virtual TYPE &operator[](unsigned short int idx) = 0;
  virtual const bool operator==(Coordinate<TYPE, SIZE> &other) = 0;
  virtual std::string to_string() = 0;
};

template <Numeric TYPE> struct Coordinate2 {
  virtual ~Coordinate2() {}

  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
};

template <Numeric TYPE> struct Coordinate3 {
  virtual ~Coordinate3() {}

  virtual TYPE get_x() const = 0;
  virtual TYPE get_y() const = 0;
  virtual TYPE get_z() const = 0;

  virtual void set_x(TYPE value) = 0;
  virtual void set_y(TYPE value) = 0;
  virtual void set_z(TYPE value) = 0;
};

template <Numeric TYPE> struct Coordinate4 {
  virtual ~Coordinate4() {}

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
