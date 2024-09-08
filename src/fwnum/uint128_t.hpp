/*

TODO specialize std::numeric_limits
TODO specialize std::hash
TODO specialize std::to_string
TODO https://en.cppreference.com/w/cpp/language/user_literal

*/

#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

#include "util.hpp"
#include "../util/cpp.hpp"

namespace tkoz
{

class uint128_t
{
private:
    std::array<uint64_t,2> _v;
    static_assert(sizeof(_v) == 16);
    static constexpr char _digit_min = '0';
    static constexpr char _digit_max = '9';
    template <bool uppercase> static constexpr char _letter_min = uppercase ? 'A' : 'a';
    template <bool uppercase> static constexpr char _letter_max = uppercase ? 'Z' : 'z';
public:
    inline constexpr uint128_t() noexcept: _v{0,0} {}
    inline constexpr uint128_t(uint64_t w0, uint64_t w1) noexcept: _v{w0,w1} {}
    inline constexpr uint128_t(const std::array<uint64_t,2> &v) noexcept: _v(v) {}

    // access the internal std::array representation
    inline constexpr const std::array<uint64_t,2> &array() const noexcept { return _v; }

    // access the internal std::array representation
    inline std::array<uint64_t,2> &array() noexcept { return _v; }

    // access one of the 2 words (index must be 0 or 1)
    template <size_t i>
    inline constexpr uint64_t get() const noexcept { static_assert(i < 2); return _v[i]; }

    // set one of the 2 words (index must be 0 or 1)
    template <size_t i>
    inline void set(uint64_t v) noexcept { static_assert(i < 2); _v[i] = v; }

    // conversion constructors
    // all primitives can be implicitly constructed by having constructors for all of them

    inline constexpr uint128_t(uint64_t n) noexcept: _v{n,0} {}
    inline constexpr uint128_t(int64_t n) noexcept: _v{(uint64_t)n,(uint64_t)(n>>63)} {}
    inline constexpr uint128_t(uint32_t n) noexcept: uint128_t((uint64_t)n) {}
    inline constexpr uint128_t(int32_t n) noexcept: uint128_t((int64_t)n) {}
    inline constexpr uint128_t(uint16_t n) noexcept: uint128_t((uint64_t)n) {}
    inline constexpr uint128_t(int16_t n) noexcept: uint128_t((int64_t)n) {}
    inline constexpr uint128_t(uint8_t n) noexcept: uint128_t((uint64_t)n) {}
    inline constexpr uint128_t(int8_t n) noexcept: uint128_t((int64_t)n) {}
    inline constexpr uint128_t(bool b) noexcept: _v{b,0} {}
    inline constexpr uint128_t(ull_t n) noexcept: uint128_t((uint64_t)n) {}
    inline constexpr uint128_t(sll_t n) noexcept: uint128_t((int64_t)n) {}

    // result is undefined for nan and inf
    inline uint128_t(float f) noexcept
    {
        uint32_t bits = *(uint32_t*)(&f);
        bool neg = bits >> 31;
        bits &= 0x7FFFFFFFu;
        int exp = (bits >> 23) - 127; // -127 <= exp <= 128
        if (exp == 128) // inf
            _v[0] = _v[1] = 0;
        else
        {
            _v[0] = (1u << 23) | (bits & 0x7FFFFFu);
            _v[1] = 0;
            int shl = exp - 23;
            if (shl >= 0)
                *this <<= shl;
            else if (shl > -24)
                *this >>= -shl;
            else
                _v[0] = 0;
            if (neg)
                *this = -*this;
        }
    }

    // result is undefined for nan and inf
    inline uint128_t(double f) noexcept
    {
        uint64_t bits = *(uint64_t*)(&f);
        bool neg = bits >> 63;
        bits &= 0x7FFFFFFFFFFFFFFFull;
        int exp = (bits >> 52) - 1023; // -1023 <= exp <= 1024
        if (exp == 1024) // inf
            _v[0] = _v[1] = 0;
        else
        {
            _v[0] = (1ull << 52) | (bits & 0xFFFFFFFFFFFFFull);
            _v[1] = 0;
            int shl = exp - 52;
            if (shl >= 128)
                _v[0] = 0;
            else if (shl >= 0)
                *this <<= shl;
            else if (shl > -53)
                *this >>= -shl;
            else
                _v[0] = 0;
            if (neg)
                *this = -*this;
        }
    }

    // conversion operators (conversion to primitives must be explicit)

    inline explicit operator bool() const noexcept { return _v[0] || _v[1]; }
    inline explicit operator uint64_t() const noexcept { return _v[0]; }
    inline explicit operator uint32_t() const noexcept { return _v[0]; }
    inline explicit operator uint16_t() const noexcept { return _v[0]; }
    inline explicit operator uint8_t() const noexcept { return _v[0]; }
    inline explicit operator int64_t() const noexcept { return _v[0]; }
    inline explicit operator int32_t() const noexcept { return _v[0]; }
    inline explicit operator int16_t() const noexcept { return _v[0]; }
    inline explicit operator int8_t() const noexcept { return _v[0]; }
    inline explicit operator ull_t() const noexcept { return _v[0]; }
    inline explicit operator sll_t() const noexcept { return _v[0]; }

    static_assert(1.8446744e19f == float(1ull<<32)*float(1ll<<32));
    static_assert(1.8446744e19f == float(1.8446744073709552e+19));
    static_assert(1.8446744073709552e19 == double(1ull<<32)*double(1ull<<32));
    // reinterpret_cast is not compatible with constexpr
    //static_assert(1.8446744e19f == _2pow_fp32(64));
    //static_assert(1.8446744073709552e19 == _2pow_fp64(64));

    inline explicit operator float() const noexcept { return float(_v[1])*1.8446744e19f + float(_v[0]); }
    inline explicit operator double() const noexcept { return double(_v[1])*1.8446744073709552e19 + double(_v[0]); }

#define _W(x,s) (uint64_t(x) << s)

    inline constexpr uint128_t(uint32_t w0, uint32_t w1, uint32_t w2, uint32_t w3) noexcept:
        _v{w0|_W(w1,32), w2|_W(w3,32)} {}

    inline constexpr uint128_t(uint16_t w0, uint16_t w1, uint16_t w2, uint16_t w3,
                               uint16_t w4, uint16_t w5, uint16_t w6, uint16_t w7) noexcept:
        _v{w0|_W(w1,16)|_W(w2,32)|_W(w3,48), w4|_W(w5,16)|_W(w6,32)|_W(w7,48)} {}

    inline constexpr uint128_t(uint8_t w0 , uint8_t w1 , uint8_t w2 , uint8_t w3 ,
                               uint8_t w4 , uint8_t w5 , uint8_t w6 , uint8_t w7 ,
                               uint8_t w8 , uint8_t w9 , uint8_t w10, uint8_t w11,
                               uint8_t w12, uint8_t w13, uint8_t w14, uint8_t w15) noexcept:
        _v{w0|_W(w1,8)|_W(w2 ,16)|_W(w3 ,24)|_W(w4 ,32)|_W(w5 ,40)|_W(w6 ,48)|_W(w7 ,56),
           w8|_W(w9,8)|_W(w10,16)|_W(w11,24)|_W(w12,32)|_W(w13,40)|_W(w14,48)|_W(w15,56)} {}

    inline constexpr uint128_t(
        bool b0  , bool b1  , bool b2  , bool b3  , bool b4  , bool b5  , bool b6  , bool b7  ,
        bool b8  , bool b9  , bool b10 , bool b11 , bool b12 , bool b13 , bool b14 , bool b15 ,
        bool b16 , bool b17 , bool b18 , bool b19 , bool b20 , bool b21 , bool b22 , bool b23 ,
        bool b24 , bool b25 , bool b26 , bool b27 , bool b28 , bool b29 , bool b30 , bool b31 ,
        bool b32 , bool b33 , bool b34 , bool b35 , bool b36 , bool b37 , bool b38 , bool b39 ,
        bool b40 , bool b41 , bool b42 , bool b43 , bool b44 , bool b45 , bool b46 , bool b47 ,
        bool b48 , bool b49 , bool b50 , bool b51 , bool b52 , bool b53 , bool b54 , bool b55 ,
        bool b56 , bool b57 , bool b58 , bool b59 , bool b60 , bool b61 , bool b62 , bool b63 ,
        bool b64 , bool b65 , bool b66 , bool b67 , bool b68 , bool b69 , bool b70 , bool b71 ,
        bool b72 , bool b73 , bool b74 , bool b75 , bool b76 , bool b77 , bool b78 , bool b79 ,
        bool b80 , bool b81 , bool b82 , bool b83 , bool b84 , bool b85 , bool b86 , bool b87 ,
        bool b88 , bool b89 , bool b90 , bool b91 , bool b92 , bool b93 , bool b94 , bool b95 ,
        bool b96 , bool b97 , bool b98 , bool b99 , bool b100, bool b101, bool b102, bool b103,
        bool b104, bool b105, bool b106, bool b107, bool b108, bool b109, bool b110, bool b111,
        bool b112, bool b113, bool b114, bool b115, bool b116, bool b117, bool b118, bool b119,
        bool b120, bool b121, bool b122, bool b123, bool b124, bool b125, bool b126, bool b127) noexcept:
        _v{_W(b0  ,0 )|_W(b1  ,1 )|_W(b2  ,2 )|_W(b3  ,3 )|_W(b4  ,4 )|_W(b5  ,5 )|_W(b6  ,6 )|_W(b7  ,7 )
          |_W(b8  ,8 )|_W(b9  ,9 )|_W(b10 ,10)|_W(b11 ,11)|_W(b12 ,12)|_W(b13 ,13)|_W(b14 ,14)|_W(b15 ,15)
          |_W(b16 ,16)|_W(b17 ,17)|_W(b18 ,18)|_W(b19 ,19)|_W(b20 ,20)|_W(b21 ,21)|_W(b22 ,22)|_W(b23 ,23)
          |_W(b24 ,24)|_W(b25 ,25)|_W(b26 ,26)|_W(b27 ,27)|_W(b28 ,28)|_W(b29 ,29)|_W(b30 ,30)|_W(b31 ,31)
          |_W(b32 ,32)|_W(b33 ,33)|_W(b34 ,34)|_W(b35 ,35)|_W(b36 ,36)|_W(b37 ,37)|_W(b38 ,38)|_W(b39 ,39)
          |_W(b40 ,40)|_W(b41 ,41)|_W(b42 ,42)|_W(b43 ,43)|_W(b44 ,44)|_W(b45 ,45)|_W(b46 ,46)|_W(b47 ,47)
          |_W(b48 ,48)|_W(b49 ,49)|_W(b50 ,50)|_W(b51 ,51)|_W(b52 ,52)|_W(b53 ,53)|_W(b54 ,54)|_W(b55 ,55)
          |_W(b56 ,56)|_W(b57 ,57)|_W(b58 ,58)|_W(b59 ,59)|_W(b60 ,60)|_W(b61 ,61)|_W(b62 ,62)|_W(b63 ,63),
           _W(b64 ,0 )|_W(b65 ,1 )|_W(b66 ,2 )|_W(b67 ,3 )|_W(b68 ,4 )|_W(b69 ,5 )|_W(b70 ,6 )|_W(b71 ,7 )
          |_W(b72 ,8 )|_W(b73 ,9 )|_W(b74 ,10)|_W(b75 ,11)|_W(b76 ,12)|_W(b77 ,13)|_W(b78 ,14)|_W(b79 ,15)
          |_W(b80 ,16)|_W(b81 ,17)|_W(b82 ,18)|_W(b83 ,19)|_W(b84 ,20)|_W(b85 ,21)|_W(b86 ,22)|_W(b87 ,23)
          |_W(b88 ,24)|_W(b89 ,25)|_W(b90 ,26)|_W(b91 ,27)|_W(b92 ,28)|_W(b93 ,29)|_W(b94 ,30)|_W(b95 ,31)
          |_W(b96 ,32)|_W(b97 ,33)|_W(b98 ,34)|_W(b99 ,35)|_W(b100,36)|_W(b101,37)|_W(b102,38)|_W(b103,39)
          |_W(b104,40)|_W(b105,41)|_W(b106,42)|_W(b107,43)|_W(b108,44)|_W(b109,45)|_W(b110,46)|_W(b111,47)
          |_W(b112,48)|_W(b113,49)|_W(b114,50)|_W(b115,51)|_W(b116,52)|_W(b117,53)|_W(b118,54)|_W(b119,55)
          |_W(b120,56)|_W(b121,57)|_W(b122,58)|_W(b123,59)|_W(b124,60)|_W(b125,61)|_W(b126,62)|_W(b127,63)} {}

#undef _W

    // increment/decrement

    inline uint128_t &operator++() noexcept { _v[1] += (++_v[0] == 0); return *this; }
    inline uint128_t operator++(int) noexcept { uint128_t ret = *this; ++(*this); return ret; }
    inline uint128_t &operator--() noexcept { _v[1] -= (_v[0]-- == 0); return *this; }
    inline uint128_t operator--(int) noexcept { uint128_t ret = *this; --(*this); return ret; }

    // unary operators

    inline uint128_t operator~() const noexcept { return uint128_t(~_v[0],~_v[1]); }
    inline bool operator!() const noexcept { return _v[0] == 0 && _v[1] == 0; }
    inline uint128_t operator+() const noexcept { return *this; }
    inline uint128_t operator-() const noexcept { return ++(~(*this)); }

    // arithmetic

    inline friend uint128_t operator+(uint128_t a, const uint128_t &b) noexcept { a += b; return a; }
    inline friend uint128_t operator+(uint128_t a, uint64_t b) noexcept { a += b; return a; }
    inline friend uint128_t operator+(uint64_t a, uint128_t b) noexcept { b += a; return b; }
    inline friend uint128_t operator-(uint128_t a, const uint128_t &b) noexcept { a -= b; return a; }
    inline friend uint128_t operator-(uint128_t a, uint64_t b) noexcept { a -= b; return a; }
    inline friend uint128_t operator-(uint64_t a, uint128_t b) noexcept { b -= a; return -b; }
    inline friend uint128_t operator*(uint128_t a, const uint128_t &b) noexcept { a *= b; return a; }
    inline friend uint128_t operator*(uint128_t a, uint64_t b) noexcept { a *= b; return a; }
    inline friend uint128_t operator*(uint64_t a, uint128_t b) noexcept { b *= a; return b; }
    inline friend uint128_t operator/(uint128_t a, const uint128_t &b) noexcept { a /= b; return a; }
    inline friend uint128_t operator/(uint128_t a, uint64_t b) noexcept { a /= b; return a; }
    inline friend uint64_t operator/(uint64_t a, const uint128_t &b) noexcept { return b._v[1] ? 0 : a / b._v[0]; }
    inline friend uint128_t operator%(uint128_t a, const uint128_t &b) noexcept { a %= b; return a; }
    inline friend uint64_t operator%(uint128_t a, uint64_t b) noexcept { a %= b; return a._v[0]; }
    inline friend uint64_t operator%(uint64_t a, const uint128_t &b) { return b._v[1] ? a : a % b._v[0]; }
    inline friend uint128_t operator<<(uint128_t a, uint32_t s) noexcept { a <<= s; return a; }
    inline friend uint128_t operator>>(uint128_t a, uint32_t s) noexcept { a >>= s; return a; }

    // compare

    inline friend bool operator<(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[1] == b._v[1] ? a._v[0] < b._v[0] : a._v[1] < b._v[1]; }
    inline friend bool operator>(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[1] == b._v[1] ? a._v[0] > b._v[0] : a._v[1] > b._v[1]; }
    inline friend bool operator<=(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[1] == b._v[1] ? a._v[0] <= b._v[0] : a._v[1] < b._v[1]; }
    inline friend bool operator>=(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[1] == b._v[1] ? a._v[0] >= b._v[0] : a._v[1] > b._v[1]; }
    inline friend bool operator==(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[0] == b._v[0] && a._v[1] == b._v[1]; }
    inline friend bool operator!=(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[0] != b._v[0] || a._v[1] != b._v[1]; }
    inline friend auto operator<=>(const uint128_t &a, const uint128_t &b) noexcept
    { return a._v[1] == b._v[1] ? a._v[0] <=> b._v[0] : a._v[1] <=> b._v[1]; }

    // bitwise

    inline friend uint128_t operator&(uint128_t a, const uint128_t &b) { a &= b; return a; }
    inline friend uint128_t operator|(uint128_t a, const uint128_t &b) { a |= b; return a; }
    inline friend uint128_t operator^(uint128_t a, const uint128_t &b) { a ^= b; return a; }

    // compound assignment

    inline uint128_t &operator+=(uint64_t a) noexcept
    {
        uint64_t t = _v[0];
        _v[0] += a;
        _v[1] += _v[0] < t;
        return *this;
    }
    inline uint128_t &operator+=(const uint128_t &a) noexcept
    {
        uint64_t t = _v[0];
        _v[0] += a._v[0];
        _v[1] += a._v[1];
        _v[1] += _v[0] < t;
        return *this;
    }
    inline uint128_t &operator-=(uint64_t a) noexcept
    {
        uint64_t t = _v[0];
        _v[0] -= a;
        _v[1] -= _v[0] > t;
        return *this;
    }
    inline uint128_t &operator-=(const uint128_t &a) noexcept
    {
        uint64_t t = _v[0];
        _v[0] -= a._v[0];
        _v[1] -= a._v[1];
        _v[1] -= _v[0] > t;
        return *this;
    }
    inline uint128_t &operator*=(uint64_t a) noexcept
    {
        uint64_t c;
        _umul64full(_v[0],a,_v[0],c);
        _v[1] *= a;
        _v[1] += c;
        return *this;

    }
    inline uint128_t &operator*=(const uint128_t &a) noexcept
    {
        uint64_t hi1,hi2;
        hi1 = _v[0]*a._v[1];
        hi2 = _v[1]*a._v[0];
        _umul64full(_v[0],a._v[0],_v[0],_v[1]);
        _v[1] += hi1;
        _v[1] += hi2;
        return *this;
    }
    inline uint128_t &operator/=(uint64_t a) noexcept
    {
        uint64_t r; // unused
        _udiv64_2(_v[0],_v[1],a,_v[0],_v[1],r);
        return *this;
    }
    inline uint128_t &operator/=(const uint128_t &a) noexcept
    {
        if (a._v[1])
        {
            if (*this < a)
                _v[0] = _v[1] = 0;
            else // *this >= a -> quotient is nonzero
            {
                uint128_t d = a;
                // amount to shift divisor to match msb with *this
                int s1 = __builtin_clzll(d._v[1]) - __builtin_clzll(_v[1]);
                d <<= s1;
                uint64_t q = 0;
                while (s1 >= 0) // long division
                {
                    q <<= 1;
                    if (*this >= d)
                        *this -= d, q |= 1;
                    d >>= 1;
                    --s1;
                }
                _v[0] = q;
                _v[1] = 0;
            }
        }
        else // small divisor
            *this /= a._v[0];
        return *this;
    }
    inline uint128_t &operator%=(uint64_t a) noexcept
    {
        uint64_t q0,q1; // unused
        _udiv64_2(_v[0],_v[1],a,q0,q1,_v[0]);
        _v[1] = 0;
        return *this;
    }
    inline uint128_t &operator%=(const uint128_t &a) noexcept
    {
        if (a._v[1])
        {
            if (*this >= a) // value unchanged if *this < a
            {
                uint128_t d = a;
                // amount to shift divisor to match msb with *this
                int s1 = __builtin_clzll(d._v[1]) - __builtin_clzll(_v[1]);
                d <<= s1;
                while (s1 >= 0) // long division
                {
                    if (*this >= d)
                        *this -= d;
                    d >>= 1;
                    --s1;
                }
            }
        }
        else // small divisor
            *this %= a._v[0];
        return *this;
    }
    // assumes 0 <= s < 128, undefined for s >= 128
    inline uint128_t &operator<<=(uint32_t s) noexcept
    {
        if (s >= 64)
            _v[1] = _v[0], _v[0] = 0, _v[1] <<= s - 64;
        // shift by 64 bits does nothing on x86, which is desired here (s=0)
        else if (s > 0)
            _v[1] <<= s, _v[1] |= _v[0] >> (64 - s), _v[0] <<= s;
        return *this;
    }
    // assumes 0 <= s < 128, undefined for s >= 128
    inline uint128_t &operator>>=(uint32_t s) noexcept
    {
        if (s >= 64)
            _v[0] = _v[1], _v[1] = 0, _v[0] >>= s - 64;
        // shift by 64 bits does nothing on x86, which is desired here (s=0)
        else if (s > 0)
            _v[0] >>= s, _v[0] |= _v[1] << (64 - s), _v[1] >>= s;
        return *this;
    }
    inline uint128_t &operator&=(const uint128_t &a) noexcept
    { return _v[0] &= a._v[0], _v[1] &= a._v[1], *this; }
    inline uint128_t &operator|=(const uint128_t &a) noexcept
    { return _v[0] |= a._v[0], _v[1] |= a._v[1], *this; }
    inline uint128_t &operator^=(const uint128_t &a) noexcept
    { return _v[0] ^= a._v[0], _v[1] ^= a._v[1], *this; }

    // streams

    inline friend std::ostream &operator<<(std::ostream &os, uint128_t a)
    {
        char buf[40];
        buf[39] = '\0';
        size_t i = 39;
        while (a) // last digit and divide by 10
        {
            buf[--i] = '0' + (a % 10);
            a /= 10;
        }
        if (i == 39) // for 0
            buf[--i] = '0';
        return os << buf+i;
    }

    inline friend std::istream &operator>>(std::istream &is, uint128_t &a)
    {
        while (std::isspace(is.peek()))
            is.get();
        bool neg = false;
        if (is.peek() == '-')
        {
            neg = true;
            is.get();
        }
        else if (is.peek() == '+')
            is.get();
        uint128_t result = 0;
        bool success = false;
        while (std::isdigit(is.peek()))
        {
            result *= 10;
            result += (is.get() - '0');
            success = true;
        }
        if (neg)
            result = -result;
        if (success)
            a = result;
        else
            is.setstate(std::ios::failbit);
        return is;
    }

    // conversion to/from string

    // convert value to a string
    // base can be 2-36, using digits 0-9 then letters a-z or A-Z
    std::string to_string(int base = 10, bool uppercase = false) const
    {
        (void)base;
        (void)uppercase;
        return "";
    }

    // convert value to a string (compile time optimized)
    template <int base = 10, bool uppercase = false>
    std::string to_string_c() const
    {
        static_assert(base >= 2 && base <= 36);
        return "";
    }

    // parse value from a string
    // base can be 2-36, using digits 0-9 then letters a-z or A-Z
    static constexpr uint128_t parse(const std::string &s, int base = 10, bool uppercase = false)
    {
        (void)s;
        (void)base;
        (void)uppercase;
        return 0;
    }

    // parse value from a string (compile time optimized)
    template <int base = 10, bool uppercase = false>
    static constexpr uint128_t parse_c(const std::string &s)
    {
        static_assert(base >= 2 && base <= 36);
        (void)s;
        return 0;
    }
};

static_assert(sizeof(uint128_t) == 16);

}

namespace std
{

template <>
struct numeric_limits<tkoz::uint128_t>
{
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr std::float_round_style round_style = std::round_toward_zero;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = true;
    static constexpr int digits = 8 * sizeof(tkoz::uint128_t);
    static constexpr int digits10 = 38; // digits * std::log10(2)
    static constexpr int max_digits10 = 0;
    static constexpr int radix = 2;
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr bool traps = true; // div by 0
    static constexpr bool tinyness_before = false;
    static constexpr tkoz::uint128_t min() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t lowest() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t max() noexcept { return tkoz::uint128_t(-1ull,-1ull); }
    static constexpr tkoz::uint128_t epsilon() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t round_error() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t infinity() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t quiet_NaN() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t signaling_NaN() noexcept { return tkoz::uint128_t(); }
    static constexpr tkoz::uint128_t denorm_min() noexcept { return tkoz::uint128_t(); }
};

string to_string(const tkoz::uint128_t &n)
{
    return n.to_string_c();
}

}
