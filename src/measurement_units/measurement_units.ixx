module;

#include "constants.hpp"

import clockwork_reverie.math;

export module clockwork_reverie.si;

// Pow is always calculated at compile time here. Yes, I tested
#define BASE_SI_STRUCT(BASE, NAME, M_PREFIX_SYMBOL, EXPONENT)                 \
  template <Numeric TYPE = double> struct NAME : BASE<TYPE> {                 \
    constexpr static const char PREFIX_SYMBOL = M_PREFIX_SYMBOL;              \
                                                                              \
    NAME(const TYPE &value) { this->value = value; }                          \
    NAME(const BASE<TYPE> &value) { from_base(value); }                       \
                                                                              \
    void from_base(TYPE from) {                                               \
      this->value = from / std::pow(10, EXPONENT);                            \
    };                                                                        \
                                                                              \
    void from_base(BASE<TYPE> from) { from_base(from.value); };               \
                                                                              \
    auto to_base() {                                                          \
      return BASE<TYPE>(this->value * std::pow(10, EXPONENT));                \
    }                                                                         \
    inline friend std::ostream &operator<<(std::ostream &os,                  \
                                           const NAME<TYPE> &other) {         \
      return os << other.value << " " << other.PREFIX_SYMBOL << other.SYMBOL; \
    }                                                                         \
  };

#define AUTOMATIC_PREFIX(NAME)                                                \
  BASE_SI_STRUCT(NAME, Kilo##NAME, 'k', 3)                                    \
  BASE_SI_STRUCT(NAME, Mega##NAME, 'M', 6)                                    \
  BASE_SI_STRUCT(NAME, Giga##NAME, 'G', 9)

export namespace ClockworkReverie::SI {
template <Numeric TYPE> struct Meter {
  constexpr static const char SYMBOL = 'm';
  TYPE value;

  inline friend std::ostream &operator<<(std::ostream &os,
                                         const Meter<TYPE> &other) {
    return os << other.value << other.SYMBOL;
  }
};
AUTOMATIC_PREFIX(Meter)

template <Numeric TYPE = double> struct Grams {};

template <Numeric TYPE = double> struct Ampere {};

template <Numeric TYPE = double> struct Kelvin {};

template <Numeric TYPE = double> struct Mole {};

template <Numeric TYPE = double> struct Candela {};
} // namespace ClockworkReverie::SI
