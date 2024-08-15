module;

#include <cmath>

export module math.vector2;

import math;
import math.vector;

export namespace FunEngine::Math {
template <Numeric TYPE = double>
class Vector2 final : public Vector<TYPE, 2> {
public:
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
} // namespace FunEngine::Math
