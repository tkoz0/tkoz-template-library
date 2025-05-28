///
/// template metaprogramming
///

#pragma once

// try to avoid including Types.hpp

namespace tkoz::stl::meta
{

/// Contains a bool member named value which is false
struct FalseValue { static constexpr bool value = false; };

/// Contains a bool member named value which is true
struct TrueValue { static constexpr bool value = true; };

// implementation details to keep within this file only
namespace _detail
{
// T = U (including const, references, pointers)
template <typename T, typename U> struct _IsSameImpl: FalseValue {};
template <typename T> struct _IsSameImpl<T,T>: TrueValue {};
} // namespace _detail

/// are 2 types the same (including const and references)
template <typename T, typename U>
static constexpr bool isSame = _detail::_IsSameImpl<T,U>::value;

namespace _detail
{
// T -> T, T& -> T, T&& -> T
template <typename T> struct _RemoveRefImpl { using type = T; };
template <typename T> struct _RemoveRefImpl<T&> { using type = T; };
template <typename T> struct _RemoveRefImpl<T&&> { using type = T; };
} // namespace _detail

/// typename without a (move) reference
template <typename T>
using RemoveRef = _detail::_RemoveRefImpl<T>::type;

/// is type T the same as any of Us...
template <typename T, typename ...Us>
static constexpr bool isSameAsAny = (false || ... || isSame<T,Us>);

} // namespace tkoz::stl::meta
