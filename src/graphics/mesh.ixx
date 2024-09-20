module;

#include <string>
#include <vector>

#include "constants.hpp"

export module clockwork_reverie.graphics.mesh;

import clockwork_reverie.math.utils;
import clockwork_reverie.math.points;

namespace math = ClockworkReverie::Math;

export namespace ClockworkReverie::Graphics {
NUMERIC_TEMPLATE struct Vertex {
  math::Point3<TYPE> position;
};

NUMERIC_TEMPLATE struct Edge {
  std::array<Vertex<TYPE> *, 2> vertices;
};

NUMERIC_TEMPLATE struct Face {
  std::array<Edge<TYPE> *, 3> edges;
  std::array<Vertex<TYPE> *, 3> vertices;
};

NUMERIC_TEMPLATE class Mesh {
  std::string name;
  std::vector<Vertex<TYPE>> vertices;
  std::vector<int> index_buffer;
};
} // namespace ClockworkReverie::Graphics
