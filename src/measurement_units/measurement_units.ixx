export module engine.si;

export namespace ClockworkReverie::SI {
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
} // namespace ClockworkReverie::SI
