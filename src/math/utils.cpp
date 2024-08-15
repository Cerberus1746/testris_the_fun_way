module;

#include <limits>

export module math.utils;

import math;

export namespace FunEngine::Math {
template <Numeric TYPE>
bool approximately(TYPE left, TYPE right,
                   TYPE tolerance = std::numeric_limits<TYPE>::epsilon()) {
  return ((left - right) < tolerance) && ((right - left) < tolerance);
}
} // namespace FunEngine::Math
