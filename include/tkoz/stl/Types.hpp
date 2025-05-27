///
/// basic type declarations
///

#pragma once

#include <cstddef>
#include <cstdint>

namespace tkoz::stl
{

//                         //
// builtin primitive types //
//                         //

/// boolean true/false
using bool_t = bool;

/// single precision IEEE754 floating point
using single_t = float;

/// double precision IEEE754 floating point
using double_t = double;

/// nonstandard long double
using ldouble_t = long double;

/// 8 bit unsigned integer
using uchar_t = unsigned char;

/// 8 bit signed integer
using schar_t = signed char;

/// 16 bit unsigned integer
using ushort_t = unsigned short;

/// 16 bit signed integer
using sshort_t = signed short;

/// 32 bit unsigned integer
using uint_t = unsigned int;

/// 32 bit signed integer
using sint_t = signed int;

/// 64 bit unsigned integer
using ulong_t = unsigned long;

/// 64 bit signed integer
using slong_t = signed long;

/// 64 bit unsigned integer
using ull_t = unsigned long long;

/// 64 bit signed integer
using sll_t = signed long long;

//                          //
// fixed width number types //
//                          //

/// unsigned 8 bit integer
using uint8_t = std::uint8_t;

/// unsigned 16 bit integer
using uint16_t = std::uint16_t;

/// unsigned 32 bit integer
using uint32_t = std::uint32_t;

/// unsigned 64 bit integer
using uint64_t = std::uint64_t;

/// signed 8 bit integer
using sint8_t = std::int8_t;

/// signed 16 bit integer
using sint16_t = std::int16_t;

/// signed 32 bit integer
using sint32_t = std::int32_t;

/// signed 64 bit integer
using sint64_t = std::int64_t;

//             //
// short names //
//             //

/// short alias for uint8_t
using u8 = uint8_t;

/// short alias for uint16_t
using u16 = uint16_t;

/// short alias for uint32_t
using u32 = uint32_t;

/// short alias for uint64_t
using u64 = uint64_t;

/// short alias for sint8_t
using s8 = sint8_t;

/// short alias for sint16_t
using s16 = sint16_t;

/// short alias for sint32_t
using s32 = sint32_t;

/// short alias for sint64_t
using s64 = sint64_t;

/// short alias for float
using fp32 = float;

/// short alias for double
using fp64 = double;

//                                      //
// pointer size and select size_t types //
//                                      //

/// size (in bytes) of a pointer
static const constexpr int cPtrSize = sizeof(void*);

/// size (in bits) of a pointer
static const constexpr int cPtrSizeBits = 8 * cPtrSize;

namespace _detail
{

template <int ptr_size> struct _usize_t_impl {};
template <> struct _usize_t_impl<1> { using type = uint8_t; };
template <> struct _usize_t_impl<2> { using type = uint16_t; };
template <> struct _usize_t_impl<4> { using type = uint32_t; };
template <> struct _usize_t_impl<8> { using type = uint64_t; };

template <int ptr_size> struct _ssize_t_impl {};
template <> struct _ssize_t_impl<1> { using type = sint8_t; };
template <> struct _ssize_t_impl<2> { using type = sint16_t; };
template <> struct _ssize_t_impl<4> { using type = sint32_t; };
template <> struct _ssize_t_impl<8> { using type = sint64_t; };

} // namespace _detail

/// unsigned type for size/length of containers
using usize_t = _detail::_usize_t_impl<cPtrSize>::type;

/// signed type for size/length of containers
using ssize_t = _detail::_ssize_t_impl<cPtrSize>::type;

/// unsigned integer type with the same size as a pointer
using uintptr_t = _detail::_usize_t_impl<cPtrSize>::type;

/// signed integer type with the same size as a pointer
using sintptr_t = _detail::_usize_t_impl<cPtrSize>::type;

} // namespace tkoz::stl
