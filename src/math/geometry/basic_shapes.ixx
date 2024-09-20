module;

#include <array>

#include "constants.hpp"

export module clockwork_reverie.math.geometry.basic_shapes;

import clockwork_reverie.math.points;
import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math::Geometry {
NUMERIC_TEMPLATE struct Size2d {
  std::array<TYPE, 2> sizes;

  Size2d(TYPE width, TYPE height) {
    sizes[0] = width;
    sizes[1] = height;
  }

  FORCE_INLINE TYPE get_height() { return get_length(); }

  FORCE_INLINE TYPE get_width() { return sizes[0]; }
  FORCE_INLINE TYPE get_length() { return sizes[1]; }
};

NUMERIC_TEMPLATE struct Size3d {
  std::array<TYPE, 3> sizes;

  FORCE_INLINE TYPE get_width() { return sizes[0]; }
  FORCE_INLINE TYPE get_length() { return sizes[1]; }
  FORCE_INLINE TYPE get_height() { return sizes[2]; }
};

NUMERIC_TEMPLATE struct Rectangle {};
} // namespace ClockworkReverie::Math::Geometry
