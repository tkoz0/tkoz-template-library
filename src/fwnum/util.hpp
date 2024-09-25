#pragma once
#include <cstddef>
#include <cstdint>
#include "../meta/basic.hpp"

namespace tkoz
{

// higher 64 bits of 64 bit multiplication
// (x86_64 computes 128 bit result)
inline constexpr uint64_t _umul64hi(uint64_t a, uint64_t b)
{ return ((__uint128_t)(a) * (__uint128_t)(b)) >> 64; }

// lower 64 bits of 64 bit multiplication
inline constexpr uint64_t _umul64lo(uint64_t a, uint64_t b)
{ return a*b; }

// multiplies a*b and stores the 128 bit result in {r0,r1}
inline constexpr void _umul64full(uint64_t a, uint64_t b, uint64_t &r0, uint64_t &r1)
{
/*
#if __x86_64__ || __amd64__
    __asm__
    (
        "mulq %[n]"
        : "=a"(r0), "=d"(r1)
        : [n]"r"(b), "a"(a)
    );
#else
#error "_umul64full only implemented for x86_64/amd64"
#endif
*/
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
#error "_udiv64_1 only implemented for x86_64/amd64"
#endif
}

// divides {x0,x1} by d (this one allows results that dont fit in 64 bits)
// stores 128 bit quotient in {q0,q1} and remainder in r
// (x86_64 only since it uses divq)
inline void _udiv64_2(uint64_t x0, uint64_t x1, uint64_t d, uint64_t &q0, uint64_t &q1, uint64_t &r)
{
    uint64_t x1q = x1 / d, x1r = x1 % d; // x1/d quotient and remainder
    q1 = x1q; // higher 64 bits
    // no error for 2nd division since (q1r*2^64+x0)/d < (q1r+1)*2^64/d <= 2^64
    _udiv64_1(x0,x1r,d,q0,r); // {x0,q1r}/d
}

// interpret bits as floating point
inline constexpr float _bits_to_fp32(uint32_t a) { return *(float*)(&a); }

// interpret bits as floating point
inline constexpr double _bits_to_fp64(uint64_t a) { return *(double*)(&a); }

// bit representation of a floating point
inline constexpr uint32_t _fp32_to_bits(float f) { return *(uint32_t*)(&f); }

// bit representation of a floating point
inline constexpr uint64_t _fp64_to_bits(double f) { return *(uint64_t*)(&f); }

// power of 2 single precision floating point
// numeric value when -126 <= p <= 127
// p = -127 gives a signed zero, p = 128 gives an infinity
// result undefined when p is outside this range
inline constexpr float _2pow_fp32(int p, bool neg = false)
{ return _bits_to_fp32((uint32_t(neg) << 31) | (uint32_t(p+127) << 23)); }

// power of 2 double precision floating point
// numeric value when -1022 <= p <= 1023
// p = -1023 gives a signed zero, p = 1024 gives an infinity
// result undefined when p is outside this range
inline constexpr double _2pow_fp64(int p, bool neg = false)
{ return _bits_to_fp64((uint64_t(neg) << 63) | (uint64_t(p+1023) << 52)); }


static constexpr char _digit_min = '0';
static constexpr char _digit_max = '9';

template <bool uppercase> static constexpr char *_letter_min = uppercase ? 'A' : 'a';
template <bool uppercase> static constexpr char *_letter_max = uppercase ? 'Z' : 'z';

template <bool uppercase> static constexpr char *_base_digits =
    uppercase ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
              : "0123456789abcdefghijklmnopqrstuvwxyz";

static constexpr bool _is_digit(char c)
{
    return _digit_min <= c && c <= _digit_max;
}

template <bool uppercase> static constexpr bool _is_letter(char c)
{
    return _letter_min<uppercase> <= c && c <= _letter_max<uppercase>;
}

}
