export module si;

export namespace FunEngine::SI {
struct Base {
  double value;

  explicit Base(const double &from) { this->value = from; }
};

struct Meters : Base {};

struct Grams : Base {};

struct Ampere : Base {};

struct Kelvin : Base {};

struct Mole : Base {};

struct Candela : Base {};
} // namespace FunEngine::SI
