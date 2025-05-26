///
/// basic type declarations
///

#pragma once

#include <cstddef>
#include <cstdint>

// try to avoid including Meta.hpp

namespace tkoz::stl
{

//                         //
// builtin primitive types //
//                         //

/// a single bit (boolean)
using bit_t = bool;

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

// these sizes are what GCC/Clang have when compiled for x86_64/amd64
static_assert(sizeof(bit_t) == 1);
static_assert(sizeof(single_t) == 4);
static_assert(sizeof(double_t) == 8);
static_assert(sizeof(ldouble_t) == 16);
static_assert(sizeof(schar_t) == 1);
static_assert(sizeof(uchar_t) == 1);
static_assert(sizeof(sshort_t) == 2);
static_assert(sizeof(ushort_t) == 2);
static_assert(sizeof(sint_t) == 4);
static_assert(sizeof(uint_t) == 4);
static_assert(sizeof(slong_t) == 8);
static_assert(sizeof(ulong_t) == 8);
static_assert(sizeof(sll_t) == 8);
static_assert(sizeof(ull_t) == 8);

// primitives should be aligned to their size
static_assert(alignof(bit_t) == 1);
static_assert(alignof(single_t) == 4);
static_assert(alignof(double_t) == 8);
static_assert(alignof(ldouble_t) == 16);
static_assert(alignof(schar_t) == 1);
static_assert(alignof(uchar_t) == 1);
static_assert(alignof(sshort_t) == 2);
static_assert(alignof(ushort_t) == 2);
static_assert(alignof(sint_t) == 4);
static_assert(alignof(uint_t) == 4);
static_assert(alignof(slong_t) == 8);
static_assert(alignof(ulong_t) == 8);
static_assert(alignof(sll_t) == 8);
static_assert(alignof(ull_t) == 8);

//                          //
// fixed width number types //
//                          //

// size assert on primitives
static_assert(sizeof(bool) == 1);
static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);
static_assert(sizeof(std::uint8_t) == 1);
static_assert(sizeof(std::uint16_t) == 2);
static_assert(sizeof(std::uint32_t) == 4);
static_assert(sizeof(std::uint64_t) == 8);
static_assert(sizeof(std::int8_t) == 1);
static_assert(sizeof(std::int16_t) == 2);
static_assert(sizeof(std::int32_t) == 4);
static_assert(sizeof(std::int64_t) == 8);

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
static_assert(cPtrSize == 4 || cPtrSize == 8); // expect 32 bit or 64 bit
static_assert(sizeof(std::intptr_t) == cPtrSize);
static_assert(sizeof(std::uintptr_t) == cPtrSize);

/// size (in bits) of a pointer
static const constexpr int cPtrSizeBits = 8 * cPtrSize;

// pointer size assert
static_assert(sizeof(void*) == cPtrSize);
static_assert(sizeof(bool*) == cPtrSize);
static_assert(sizeof(float*) == cPtrSize);
static_assert(sizeof(double*) == cPtrSize);
static_assert(sizeof(std::uint8_t*) == cPtrSize);
static_assert(sizeof(std::uint16_t*) == cPtrSize);
static_assert(sizeof(std::uint32_t*) == cPtrSize);
static_assert(sizeof(std::uint64_t*) == cPtrSize);
static_assert(sizeof(std::int8_t*) == cPtrSize);
static_assert(sizeof(std::int16_t*) == cPtrSize);
static_assert(sizeof(std::int32_t*) == cPtrSize);
static_assert(sizeof(std::int64_t*) == cPtrSize);
static_assert(sizeof(std::nullptr_t) == cPtrSize);

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

//                         //
// checks on literal types //
//                         //

namespace _detail
{

// redefining is_same so this file does not depend on Meta.hpp
template <typename T, typename U> struct _is_same_impl
{ static constexpr bool _value = false; };
template <typename T> struct _is_same_impl<T,T>
{ static constexpr bool _value = true; };
template <typename T, typename U>
static constexpr bool _is_same = _is_same_impl<T,U>::_value;

} // namespace _detail

static_assert(_detail::_is_same<decltype(true),bool>);
static_assert(_detail::_is_same<decltype(false),bool>);
static_assert(_detail::_is_same<decltype(nullptr),std::nullptr_t>);
static_assert(_detail::_is_same<decltype(' '),char>);

// string literals are lvalues so the (&) for reference is needed
static_assert(_detail::_is_same<decltype(""),const char(&)[1]>);

// integers (standard)
static_assert(_detail::_is_same<decltype(0),sint_t>);
static_assert(_detail::_is_same<decltype(0u),uint_t>);
static_assert(_detail::_is_same<decltype(0l),slong_t>);
static_assert(_detail::_is_same<decltype(0ul),ulong_t>);
static_assert(_detail::_is_same<decltype(0ll),sll_t>);
static_assert(_detail::_is_same<decltype(0ull),ull_t>);

// integers (hexadecimal)
static_assert(_detail::_is_same<decltype(0x0),sint_t>);
static_assert(_detail::_is_same<decltype(0x0u),uint_t>);
static_assert(_detail::_is_same<decltype(0x0l),slong_t>);
static_assert(_detail::_is_same<decltype(0x0ul),ulong_t>);
static_assert(_detail::_is_same<decltype(0x0ll),sll_t>);
static_assert(_detail::_is_same<decltype(0x0ull),ull_t>);

// integers (octal)
static_assert(_detail::_is_same<decltype(00),sint_t>);
static_assert(_detail::_is_same<decltype(00u),uint_t>);
static_assert(_detail::_is_same<decltype(00l),slong_t>);
static_assert(_detail::_is_same<decltype(00ul),ulong_t>);
static_assert(_detail::_is_same<decltype(00ll),sll_t>);
static_assert(_detail::_is_same<decltype(00ull),ull_t>);

// integers (binary)
static_assert(_detail::_is_same<decltype(0b0),sint_t>);
static_assert(_detail::_is_same<decltype(0b0u),uint_t>);
static_assert(_detail::_is_same<decltype(0b0l),slong_t>);
static_assert(_detail::_is_same<decltype(0b0ul),ulong_t>);
static_assert(_detail::_is_same<decltype(0b0ll),sll_t>);
static_assert(_detail::_is_same<decltype(0b0ull),ull_t>);

// floating point (standard)
static_assert(_detail::_is_same<decltype(0.0),double>);
static_assert(_detail::_is_same<decltype(0.0l),long double>);
static_assert(_detail::_is_same<decltype(0.0f),float>);

// floating point (scientific)
static_assert(_detail::_is_same<decltype(1e0),double>);
static_assert(_detail::_is_same<decltype(1e0l),long double>);
static_assert(_detail::_is_same<decltype(1e0f),float>);

// floating point (hexadecimal)
static_assert(_detail::_is_same<decltype(0x1p1),double>);
static_assert(_detail::_is_same<decltype(0x1p1l),long double>);
static_assert(_detail::_is_same<decltype(0x1p1f),float>);

} // namespace tkoz::stl
