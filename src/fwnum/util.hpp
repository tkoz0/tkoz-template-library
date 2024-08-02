#pragma once
#include <cstdint>
#include "../util/cpp.hpp"

static_assert(sizeof(bool) == 1);
static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);
static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);

namespace tkoz
{

template <typename T> struct fp_exp_size {};
template <> struct fp_exp_size<float> { static constexpr size_t value = 8; };
template <> struct fp_exp_size<double> { static constexpr size_t value = 11; };
#if TKOZ_CPP14_OR_NEWER
template <typename T> constexpr size_t fp_exp_size_v = fp_exp_size<T>::value;
#endif

#if TKOZ_CPP14_OR_NEWER
template <typename T> struct fp_exp_bias { static constexpr size_t value = (1ull << (fp_exp_size_v<T> - 1)) - 1; };
template <typename T> constexpr size_t fp_exp_bias_v = fp_exp_bias<T>::value;
#else
template <typename T> struct fp_exp_bias { static constexpr size_t value = (1ull << (fp_exp_size<T>::value - 1)) - 1; };
#endif

template <typename T> struct fp_mant_size {};
template <> struct fp_mant_size<float> { static constexpr size_t value = 23; };
template <> struct fp_mant_size<double> { static constexpr size_t value = 52; };
#if TKOZ_CPP14_OR_NEWER
template <typename T> constexpr size_t fp_mant_size_v = fp_mant_size<T>::value;
#endif

#if TKOZ_CPP14_OR_NEWER
static_assert(1 + fp_exp_size_v<float> + fp_mant_size_v<float> == 32);
static_assert(1 + fp_exp_size_v<double> + fp_mant_size_v<double> == 64);
static_assert(fp_exp_bias_v<float> == 127);
static_assert(fp_exp_bias_v<double> == 1023);
#endif

static_assert(1 + fp_exp_size<float>::value + fp_mant_size<float>::value == 32);
static_assert(1 + fp_exp_size<double>::value + fp_mant_size<double>::value == 64);
static_assert(fp_exp_bias<float>::value == 127);
static_assert(fp_exp_bias<double>::value == 1023);

// higher 64 bits of 64 bit multiplication
// (x86_64 computes 128 bit result)
inline uint64_t _umul64hi(uint64_t a, uint64_t b)
{ return ((__uint128_t)(a) * (__uint128_t)(b)) >> 64; }

// lower 64 bits of 64 bit multiplication
inline uint64_t _umul64lo(uint64_t a, uint64_t b)
{ return a*b; }

// multiplies a*b and stores the 128 bit result in {r0,r1}
inline void _umul64full(uint64_t a, uint64_t b, uint64_t &r0, uint64_t &r1)
{
    __uint128_t t = (__uint128_t)a * (__uint128_t)b;
    r0 = t;
    r1 = t >> 64;
}

// divides {x0,x1} by d, sigfpe occurs if quotient does not fit in 64 bits
// stores the quotient in q and remainder in r
// (x86_64 only, divq instruction is usually avoided by compilers)
inline void _udiv64_1(uint64_t x0, uint64_t x1, uint64_t d, uint64_t &q, uint64_t &r)
{
#if __x86_64__ || __amd64__
    __asm__
    (
        "divq %[d]"
        : "=a"(q), "=d"(r) // rax(quotient) and rdx(remainder)
        : [d]"r"(d), "a"(x0), "d"(x1) // rdx:rax is 128 bit input
    );
#else
#error "only implemented for x86_64"
#endif
}

// divides {x0,x1} by d (this one allows results that dont fit in 64 bits)
// stores 128 bit quotient in {q0,q1} and remainder in r
// (x86_64 only since it uses divq)
inline void _udiv64_2(uint64_t x0, uint64_t x1, uint64_t d, uint64_t &q0, uint64_t &q1, uint64_t &r)
{
    uint64_t x1q = x1 / d, x1r = x1 % d; // x1/d quotient and remainder
    q1 = x1q; // higher 64 bits
    // no error for 2nd division since  (q1r*2^64+x0)/d < (q1r+1)*2^64/d <= 2^64
    _udiv64_1(x0,x1r,d,q0,r); // {x0,q1r}/d
}

// interpret bits as floating point
inline constexpr float _bits_as_fp32(uint32_t a) { return *(float*)(&a); }

// interpret bits as floating point
inline constexpr double _bits_as_fp64(uint64_t a) { return *(double*)(&a); }

// power of 2 single precision floating point
// numeric value when -126 <= p <= 127
// p = -127 gives a signed zero, p = 128 gives an infinity
// result undefined when p is outside this range
inline constexpr float _2pow_fp32(int p, bool neg = false)
{ return _bits_as_fp32((uint32_t(neg) << 31) | (uint32_t(p+127) << 23)); }

// power of 2 double precision floating point
// numeric value when -1022 <= p <= 1023
// p = -1023 gives a signed zero, p = 1024 gives an infinity
// result undefined when p is outside this range
inline constexpr double _2pow_fp64(int p, bool neg = false)
{ return _bits_as_fp64((uint64_t(neg) << 63) | (uint64_t(p+1023) << 52)); }

}
