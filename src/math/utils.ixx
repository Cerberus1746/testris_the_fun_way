/**
 * @brief util functions related to math
 *
 */
module;

#include <limits>
#include <type_traits>

export module clockwork_reverie.math.utils;

export namespace ClockworkReverie::Math {
/**
 * @brief Concept to be used by templates that filter by a type that is a
 *        number.
 *
 * @tparam TYPE
 */
template <class TYPE>
concept Numeric = std::is_arithmetic_v<TYPE>;

/**
 * @brief Compare two floating points together with a tolerance ammount.<br />
 *        In python the type for the arguments are float.
 *
 * @tparam TYPE Numeric concept in C++, float in Python
 * @param left the first number to compare
 * @param right the second number to compare
 * @param tolerance the range where the comparison should return true
 *                  by default the value is the epsilon of TYPE
 * @return true if the difference is outside of tolerance
 * @return false otherwise
 */
template <Numeric TYPE>
const bool
approximately(const TYPE &left, const TYPE &right,
              const TYPE &tolerance = std::numeric_limits<TYPE>::epsilon()) {
  return ((left - right) < tolerance) && ((right - left) < tolerance);
}
} // namespace ClockworkReverie::Math
