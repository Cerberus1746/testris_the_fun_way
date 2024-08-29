module;

#include <type_traits>

export module FunEngine.math;

/// Speed of Light in vacuum in meters per second
const int LIGHT_SPEED = 299792458;

#define ParentMatrix Matrix<TYPE, SIZE_X, SIZE_Y>


export namespace FunEngine::Math {
template <class TYPE>
concept Numeric = std::is_arithmetic_v<TYPE>;
} // namespace FunEngine::Math
