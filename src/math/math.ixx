module;

#include <type_traits>

export module engine.math;

export namespace FunEngine::Math {
template <class TYPE>
concept Numeric = std::is_arithmetic_v<TYPE>;
} // namespace FunEngine::Math
