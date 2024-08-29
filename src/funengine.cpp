export module FunEngine;

#if defined(__clang__)
#define FORCE_INLINE [[clang::always_inline]] inline

#elif defined(__GNUC__)
#define FORCE_INLINE [[gnu::always_inline]] inline

#elif defined(_MSC_VER)
#pragma warning(error : 4714)
#define FORCE_INLINE __forceinline

#else
#error Unsupported compiler
#endif
