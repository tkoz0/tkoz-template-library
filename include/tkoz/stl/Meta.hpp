///
/// template metaprogramming
///

#pragma once

// try to avoid including Types.hpp

namespace tkoz::stl::meta
{

// implementation details to keep within this file only
namespace _detail
{
// T = U (including const, references, pointers)
template <typename T, typename U> struct _isSameImpl
{ static constexpr bool value = false; };
template <typename T> struct _isSameImpl<T,T>
{ static constexpr bool value = true; };
} // namespace _detail

/// are 2 types the same (including const and references)
template <typename T, typename U>
static constexpr bool isSame = _detail::_isSameImpl<T,U>::value;

namespace _detail
{
// T -> T, T& -> T, T&& -> T
template <typename T> struct _removeRefImpl { using type = T; };
template <typename T> struct _removeRefImpl<T&> { using type = T; };
template <typename T> struct _removeRefImpl<T&&> { using type = T; };
} // namespace _detail

/// typename without a (move) reference
template <typename T>
using removeRef = _detail::_removeRefImpl<T>::type;

namespace _detail
{
template <typename T, typename ...Us>
struct _isSameAsAnyImpl
{
    static constexpr bool value = false;
};
template <typename T, typename U, typename ...Us>
struct _isSameAsAnyImpl<T,U,Us...>
{
    static constexpr bool value = isSame<T,U>
        || _isSameAsAnyImpl<T,Us...>::value;
};
} // namespace _detail

/// is type T the same as any of Us...
template <typename T, typename ...Us>
static constexpr bool isSameAsAny = _detail::_isSameAsAnyImpl<T,Us...>::value;

} // namespace tkoz::stl::meta
