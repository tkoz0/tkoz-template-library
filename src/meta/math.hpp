#include <cstddef>
#include <type_traits>

namespace tkoz::meta
{

// min

template <size_t A, size_t B>
struct min_s
{
    static constexpr size_t value = A < B ? A : B;
};

template <size_t A, size_t B>
constexpr size_t min_v = min_s<A,B>::value;

// max

template <size_t A, size_t B>
struct max_s
{
    static constexpr size_t value = A > B ? A : B;
};

template <size_t A, size_t B>
constexpr size_t max_v = max_s<A,B>::value;

// all

template <bool ...vs>
struct all_s
{
    static constexpr bool value = true;
};

template <bool v, bool ...vs>
struct all_s<v,vs...>
{
    static constexpr bool value = v && all_s<vs...>::value;
};

template <bool ...vs>
constexpr bool all_v = all_s<vs...>::value;

// any

template <bool ...vs>
struct any_s
{
    static constexpr bool value = false;
};

template <bool v, bool ...vs>
struct any_s<v,vs...>
{
    static constexpr bool value = v || any_s<vs...>::value;
};

template <bool ...vs>
constexpr bool any_v = any_s<vs...>::value;

// factorial

template <size_t N>
struct factorial_s
{
    static constexpr size_t value = N * factorial_s<N-1>::value;
};

template <>
struct factorial_s<0>
{
    static constexpr size_t value = 1;
};

template <size_t N>
constexpr size_t factorial_v = factorial_s<N>::value;

// fibonacci

template <size_t N>
struct fibonacci_s
{
    static constexpr size_t value = fibonacci_s<N-1>::value + fibonacci_s<N-1>::_prev;
    static constexpr size_t _prev = fibonacci_s<N-1>::value;
};

template <>
struct fibonacci_s<0>
{
    static constexpr size_t value = 0;
};

template <>
struct fibonacci_s<1>
{
    static constexpr size_t value = 1;
    static constexpr size_t _prev = 0;
};

template <size_t N>
constexpr size_t fibonacci_v = fibonacci_s<N>::value;

// gcd

template <size_t A, size_t B>
struct gcd
{
    static constexpr size_t value = gcd<B,A%B>::value;
};

template <>
struct gcd<0,0> {};

template <size_t A>
struct gcd<A,0>
{
    static constexpr size_t value = A;
};

template <size_t A, size_t B>
constexpr size_t gcd_v = gcd<A,B>::value;

namespace _internal
{

template <size_t i, size_t j>
struct _permutations_mulseq
{
    static_assert(i > j);
    static constexpr size_t _value = i * _permutations_mulseq<i-1,j>::_value;
};

template <size_t i>
struct _permutations_mulseq<i,i>
{
    static constexpr size_t _value = 1;
};

template <size_t n, size_t k, size_t i = k>
struct _combinations_mulseq
{
    static constexpr size_t _value = _combinations_mulseq<n,k,k-1>::_value * (n-k+1) / k;
};

template <size_t n, size_t k>
struct _combinations_mulseq<n,k,0>
{
    static constexpr size_t _value = 1;
};

}

// permutations

template <size_t N, size_t K>
struct permutations_s
{
    static constexpr size_t value = K > N ? 0 : _internal::_permutations_mulseq<N,N-K>::_value;
};

template <size_t N, size_t K>
constexpr size_t permutations_v = permutations_s<N,K>::value;

// combinations

template <size_t N, size_t K>
struct combinations_s
{
    static constexpr size_t value = K <= N/2 ? _internal::_combinations_mulseq<N,K>::_value : combinations_s<N,N-K>::value;
};

template <size_t N, size_t K>
constexpr size_t combinations_v = combinations_s<N,K>::value;

}
