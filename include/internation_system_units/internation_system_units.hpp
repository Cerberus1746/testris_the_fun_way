namespace FunEngine::SI {
struct Base {
  double value;

  explicit Base(const double &from);
};

struct Meters : Base {};

struct Grams : Base {};

struct Ampere : Base {};

struct Kelvin : Base {};

struct Mole : Base {};

struct Candela : Base {};
} // namespace FunEngine::SI
