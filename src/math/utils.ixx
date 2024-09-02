module;

#include <limits>

export module engine.math.utils;

import engine.math;

export namespace FunEngine::Math {
template <Numeric TYPE>
bool approximately(const TYPE &left, const TYPE &right,
                   const TYPE &tolerance = std::numeric_limits<TYPE>::epsilon()) {
  return ((left - right) < tolerance) && ((right - left) < tolerance);
}
} // namespace FunEngine::Math
