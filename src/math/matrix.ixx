module;

#include <array>
#include <cassert>
#include <cstddef>
#include <typeinfo>

#include "constants.hpp"

export module clockwork_reverie.math.matrix;

import clockwork_reverie.math.vectors;
import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {
template <Numeric TYPE = double, unsigned short int SIZE_X = 2,
          unsigned short int SIZE_Y = 2>
class Matrix {
public:
  std ::array<TYPE, SIZE_X * SIZE_Y> values{};

  explicit Matrix(std ::array<TYPE, SIZE_X * SIZE_Y> items) {
    this->values = items;
  }

  ParentMatrix *transpose;

#if __cplusplus >= 202302L
  TYPE &operator[](unsigned short int index_x, unsigned short int index_y) {
    assert(index_x < SIZE_X && index_y < SIZE_Y);
    return values[index_y * SIZE_X + index_x];
  }
#endif

  TYPE get(unsigned short int index_x, unsigned short int index_y) {
    assert(index_x < SIZE_X && index_y < SIZE_Y);
    return values[index_y * SIZE_X + index_x];
  }

  void set(unsigned short int index_x, unsigned short int index_y,
           TYPE value) {
    assert(index_x < SIZE_X && index_y < SIZE_Y);
    values[index_y * SIZE_X + index_x] = value;
  }

  Matrix() {
    for (unsigned short int x = 0; x < SIZE_X; x++)
      for (unsigned short int y = 0; y < SIZE_Y; y++)
        set(x, y, x == y ? 1 : 0);
  }
};

template <typename TYPE = double>
class Matrix2x2 final : public Matrix<TYPE, 2, 2> {
public:
  TYPE *a1 = &this->values[0];
  TYPE *a2 = &this->values[1];
  TYPE *b1 = &this->values[2];
  TYPE *b2 = &this->values[3];

  FORCE_INLINE TYPE get_determinant() {
    if (!this->cache.is_determinant_dirty)
      return this->cache.determinant;

    if (this->cache.is_identity) {
      this->cache.set_determinant(1);
      return 1;
    }

    // if the columns are the same, the determinant will always be 0
    // but we are only doing the check if TYPE is int because floating point
    // comparison might be more expensive than to actually do the math
    if (typeid(TYPE) == int_id && a1 == a2 && b1 == b2) {
      this->cache.determinant = 0;
      return 0;
    }

    TYPE result = a1 * b1 - a2 * b2;
    this->cache.set_determinant(result);
    return result;
  }
};

template <typename TYPE = double>
class Matrix3x3 final : public Matrix<TYPE, 3, 3> {
public:
  TYPE *a1 = *this[0, 0];
  TYPE *a2 = *this[0, 1];
  TYPE *a3 = *this[0, 2];

  TYPE *b1 = *this[1, 0];
  TYPE *b2 = *this[1, 1];
  TYPE *b3 = *this[1, 2];

  TYPE *c1 = *this[2, 0];
  TYPE *c2 = *this[2, 1];
  TYPE *c3 = *this[2, 2];

  Vector2<TYPE> get_position() {
    return Vector2<TYPE>(*this[3, 0], *this[3, 1]);
  }

  TYPE get_determinant() {
    if (!this->cache.is_determinant_dirty)
      return this->cache.determinant;
  }

  void set_position(TYPE x_axis, TYPE y_axis) {
    (*this)[2, 0] = x_axis;
    (*this)[2, 1] = y_axis;

    this->cache.set_all_dirty();
  }

  void set_position(Vector2<TYPE> &vector) {
    (*this)[2, 0] = vector[0];
    (*this)[2, 1] = vector[1];

    this->cache.set_all_dirty();
  }
};

template <typename TYPE = double>
class Matrix4x4 final : public Matrix<TYPE, 4, 4> {
public:
  Vector3<TYPE> get_position() {
    return Vector3<TYPE>(this->values[3][0], this->values[3][1],
                         this->values[3][2]);
  }
  /*
    TYPE get_determinant() {
      if (!this->cache.is_determinant_dirty)
        return this->cache.determinant;
    }*/

  void set_position(TYPE x_axis, TYPE y_axis, TYPE z_axis) {
    this->set(3, 0, x_axis);
    this->set(3, 1, y_axis);
    this->set(3, 2, z_axis);
  }

  void set_position(Vector3<TYPE> &vector) {
    this->set(3, 0, vector[0]);
    this->set(3, 1, vector[1]);
    this->set(3, 2, vector[2]);
  }
};
} // namespace ClockworkReverie::Math
