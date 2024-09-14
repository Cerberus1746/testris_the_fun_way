module;

#include "constants.hpp"

export module clockwork_reverie.math.geometry.basic_shapes;

import clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math::Geometry {
NUMERIC_TEMPLATE struct Size2d {
  TYPE x_axis;
  TYPE y_axis;
};
} // namespace ClockworkReverie::Math
