#include <cstddef>
#include <type_traits>

// TODO include "typename T" so it is not always size_t

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
struct gcd_s
{
    static constexpr size_t value = gcd_s<B,A%B>::value;
};

template <>
struct gcd_s<0,0> {};

template <size_t A>
struct gcd_s<A,0>
{
    static constexpr size_t value = A;
};

template <size_t A, size_t B>
constexpr size_t gcd_v = gcd_s<A,B>::value;

namespace _internal
{

template <size_t i, size_t j>
struct _perm_mulseq
{
    static constexpr size_t value = i * _perm_mulseq<i-1,j>::value;
};

template <size_t i>
struct _perm_mulseq<i,i>
{
    static constexpr size_t value = 1;
};

template <size_t n, size_t k>
struct _comb_mulseq
{
    static constexpr size_t value = _comb_mulseq<n,k-1>::value * (n-k+1) / k;
};

template <size_t n>
struct _comb_mulseq<n,0>
{
    static constexpr size_t value = 1;
};

}

// permutations

template <size_t N, size_t K>
struct permutations_s
{
    static constexpr size_t value = K > N ? 0 : _internal::_perm_mulseq<N,N-K>::value;
};

template <size_t N, size_t K>
constexpr size_t permutations_v = permutations_s<N,K>::value;

// combinations

template <size_t N, size_t K>
struct combinations_s
{
    static constexpr size_t value = std::conditional_t<(K>N),std::integral_constant<size_t,0>,
        std::conditional_t<(K<=N/2),_internal::_comb_mulseq<N,K>,_internal::_comb_mulseq<N,N-K>>>::value;
};

template <size_t N, size_t K>
constexpr size_t combinations_v = combinations_s<N,K>::value;

// pow

// TODO with squaring

template <size_t B, size_t P>
struct pow_s
{
    static constexpr size_t value = B * pow_s<B,P-1>::value;
};

template <>
struct pow_s<1,0>
{
    static constexpr size_t value = 1;
};

template <size_t P>
struct pow_s<1,P>
{
    static constexpr size_t value = 1;
};

template <size_t B>
struct pow_s<B,0>
{
    static constexpr size_t value = 1;
};

template <size_t B, size_t P>
constexpr size_t pow_v = pow_s<B,P>::value;

// modpow

// TODO binary right to left

}
