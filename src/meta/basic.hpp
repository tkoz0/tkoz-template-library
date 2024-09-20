#pragma once

#include <cstddef>
#include "../types/primitive.hpp"

namespace tkoz::meta
{

// has member value of true or false, indicating if T and U are the same type
template <typename T, typename U> struct same_type_s { static constexpr bool value = false; };
template <typename T> struct same_type_s<T,T> { static constexpr bool value = true; };
template <typename T, typename U> static constexpr bool same_type_v = same_type_s<T,U>::value;

// has member type=T when B is true, otherwise no member (for SFINAE)
template <bool B, typename T> struct enable_if_s {};
template <typename T> struct enable_if_s<true,T> { using type = T; };
template <bool B, typename T> using enable_if_t = enable_if_s<B,T>::type;

// has member type T or F depending on boolean value B
template <bool B, typename T, typename F> struct cond_s { using type = T; };
template <typename T, typename F> struct cond_s<false,T,F> { using type = F; };
template <bool B, typename T, typename F> using cond_t = cond_s<B,T,F>::type;

// give the signed integer primitive type of same size
template <typename T> struct same_size_signed_s {};
template <> struct same_size_signed_s<schar_t> { using type = schar_t; };
template <> struct same_size_signed_s<uchar_t> { using type = schar_t; };
template <> struct same_size_signed_s<sshort_t> { using type = sshort_t; };
template <> struct same_size_signed_s<ushort_t> { using type = sshort_t; };
template <> struct same_size_signed_s<sint_t> { using type = sint_t; };
template <> struct same_size_signed_s<uint_t> { using type = sint_t; };
template <> struct same_size_signed_s<slong_t> { using type = slong_t; };
template <> struct same_size_signed_s<ulong_t> { using type = slong_t; };
template <> struct same_size_signed_s<sll_t> { using type = sll_t; };
template <> struct same_size_signed_s<ull_t> { using type = sll_t; };
template <typename T> using same_size_signed_t = same_size_signed_s<T>::type;

// give the unsigned integer primitive type of same size
template <typename T> struct same_size_unsigned_s {};
template <> struct same_size_unsigned_s<schar_t> { using type = uchar_t; };
template <> struct same_size_unsigned_s<uchar_t> { using type = uchar_t; };
template <> struct same_size_unsigned_s<sshort_t> { using type = ushort_t; };
template <> struct same_size_unsigned_s<ushort_t> { using type = ushort_t; };
template <> struct same_size_unsigned_s<sint_t> { using type = uint_t; };
template <> struct same_size_unsigned_s<uint_t> { using type = uint_t; };
template <> struct same_size_unsigned_s<slong_t> { using type = ulong_t; };
template <> struct same_size_unsigned_s<ulong_t> { using type = ulong_t; };
template <> struct same_size_unsigned_s<sll_t> { using type = ull_t; };
template <> struct same_size_unsigned_s<ull_t> { using type = ull_t; };
template <typename T> using same_size_unsigned_t = same_size_unsigned_s<T>::type;

// give the same size integer primitive, specify if it should be signed
template <typename T, bool is_signed> struct same_size_integer_s {};
template <typename T> struct same_size_integer_s<T,true> { using type = same_size_signed_t<T>; };
template <typename T> struct same_size_integer_s<T,false> { using type = same_size_unsigned_t<T>; };
template <typename T, bool is_signed> using same_size_integer_t = same_size_integer_s<T,is_signed>::type;

// asserts for gcc defaults
static_assert(same_type_v<uint8_t, unsigned char>);
static_assert(same_type_v<uint16_t, unsigned short>);
static_assert(same_type_v<uint32_t, unsigned int>);
static_assert(same_type_v<uint64_t, unsigned long>);
static_assert(same_type_v<int8_t, signed char>);
static_assert(same_type_v<int16_t, signed short>);
static_assert(same_type_v<int32_t, signed int>);
static_assert(same_type_v<int64_t, signed long>);

// asserts for tkoz defined types
static_assert(same_type_v<bit_t, bool>);
static_assert(same_type_v<fp32_t, float>);
static_assert(same_type_v<fp64_t, double>);
static_assert(same_type_v<uchar_t, unsigned char>);
static_assert(same_type_v<schar_t, signed char>);
static_assert(same_type_v<ushort_t, unsigned short>);
static_assert(same_type_v<sshort_t, signed short>);
static_assert(same_type_v<uint_t, unsigned int>);
static_assert(same_type_v<sint_t, signed int>);
static_assert(same_type_v<ulong_t, unsigned long>);
static_assert(same_type_v<slong_t, signed long>);
static_assert(same_type_v<ull_t, unsigned long long>);
static_assert(same_type_v<sll_t, signed long long>);

// floating point exponent size (in bits)
template <typename T> struct fp_exp_size_s {};
template <> struct fp_exp_size_s<float> { static constexpr size_t value = 8; };
template <> struct fp_exp_size_s<double> { static constexpr size_t value = 11; };
template <typename T> constexpr size_t fp_exp_size_v = fp_exp_size_s<T>::value;

// floating point exponent bias value
template <typename T> struct fp_exp_bias_s { static constexpr size_t value = (1ull << (fp_exp_size_v<T> - 1)) - 1; };
template <typename T> constexpr size_t fp_exp_bias_v = fp_exp_bias_s<T>::value;

// floating point mantissa size (in bits)
template <typename T> struct fp_mant_size_s {};
template <> struct fp_mant_size_s<float> { static constexpr size_t value = 23; };
template <> struct fp_mant_size_s<double> { static constexpr size_t value = 52; };
template <typename T> constexpr size_t fp_mant_size_v = fp_mant_size_s<T>::value;

static_assert(1 + fp_exp_size_v<float> + fp_mant_size_v<float> == 32);
static_assert(1 + fp_exp_size_v<double> + fp_mant_size_v<double> == 64);
static_assert(fp_exp_bias_v<float> == 127);
static_assert(fp_exp_bias_v<double> == 1023);

static_assert(1 + fp_exp_size_v<float> + fp_mant_size_v<float> == 32);
static_assert(1 + fp_exp_size_v<double> + fp_mant_size_v<double> == 64);
static_assert(fp_exp_bias_v<float> == 127);
static_assert(fp_exp_bias_v<double> == 1023);

}
