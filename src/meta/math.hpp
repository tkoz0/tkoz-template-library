#include <cstddef>

namespace tkoz::meta
{

template <size_t N>
struct factorial { static constexpr size_t value = N * factorial<N-1>::value; };

template <>
struct factorial<0> { static constexpr size_t value = 1; };

template <size_t N> constexpr size_t factorial_v = factorial<N>::value;

template <size_t A, size_t B>
struct gcd { static constexpr size_t value = gcd<B,A%B>::value; };

template <>
struct gcd<0,0> {};

template <size_t A>
struct gcd<A,0> { static constexpr size_t value = A; };

template <size_t B>
struct gcd<0,B> { static constexpr size_t value = B; };

template <size_t A, size_t B> constexpr size_t gcd_v = gcd<A,B>::value;

}
