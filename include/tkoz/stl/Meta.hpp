///
/// template metaprogramming
///
/// \note these were implemented for understanding and it is better practice
/// to use the equivalents provided in the STL
///

#pragma once

// try to avoid including Types.hpp

#include <cstddef>

namespace tkoz::stl::meta
{

/// Contains a bool member named value which is false
struct FalseValue { static constexpr bool value = false; };

/// Contains a bool member named value which is true
struct TrueValue { static constexpr bool value = true; };

/// Contains a type member which is the template type
template <typename T>
struct TypeValue { using type = T; };

namespace _detail
{

// T = U (including const, references, pointers)
template <typename T, typename U> struct _IsSameImpl: FalseValue {};
template <typename T> struct _IsSameImpl<T,T>: TrueValue {};

template <typename T> struct _IsArrayImpl: FalseValue {};
template <typename T> struct _IsArrayImpl<T[]>: TrueValue {};
template <typename T, std::size_t N> struct _IsArrayImpl<T[N]>: TrueValue {};

// (T, T&, T&&) -> T
template <typename T> struct _RemoveRefImpl: TypeValue<T> {};
template <typename T> struct _RemoveRefImpl<T&>: TypeValue<T> {};
template <typename T> struct _RemoveRefImpl<T&&>: TypeValue<T> {};

// (T, const T, volatile T, const volatile T) -> T
template <typename T> struct _RemoveCVImpl: TypeValue<T> {};
template <typename T> struct _RemoveCVImpl<const T>: TypeValue<T> {};
template <typename T> struct _RemoveCVImpl<volatile T>: TypeValue<T> {};
template <typename T> struct _RemoveCVImpl<const volatile T>: TypeValue<T> {};

// (T, const T) -> T
template <typename T> struct _RemoveConstImpl: TypeValue<T> {};
template <typename T> struct _RemoveConstImpl<const T>: TypeValue<T> {};

// (T, volatile T) -> T
template <typename T> struct _RemoveVolatileImpl: TypeValue<T> {};
template <typename T> struct _RemoveVolatileImpl<volatile T>: TypeValue<T> {};

template <typename T> struct _IsPointerImpl: FalseValue {};
template <typename T> struct _IsPointerImpl<T*>: TrueValue {};
template <typename T> struct _IsPointerImpl<T * const>: TrueValue {};
template <typename T> struct _IsPointerImpl<T * volatile>: TrueValue {};
template <typename T> struct _IsPointerImpl<T * const volatile>: TrueValue {};

template <typename T> struct _IsLVRefImpl: FalseValue {};
template <typename T> struct _IsLVRefImpl<T&>: TrueValue {};

template <typename T> struct _IsRVRefImpl: FalseValue {};
template <typename T> struct _IsRVRefImpl<T&&>: TrueValue {};

template <typename T> struct _IsRefImpl: FalseValue {};
template <typename T> struct _IsRefImpl<T&>: TrueValue {};
template <typename T> struct _IsRefImpl<T&&>: TrueValue {};

template <typename T> struct _IsConstImpl: FalseValue {};
template <typename T> struct _IsConstImpl<const T>: TrueValue {};

template <typename T> struct _IsVolatileImpl: FalseValue {};
template <typename T> struct _IsVolatileImpl<volatile T>: TrueValue {};

template <typename T> struct _IsSignedImpl
{
    static constexpr bool value = static_cast<T>(-1) < static_cast<T>(0);
};

template <typename T> struct _IsUnsignedImpl
{
    static constexpr bool value = static_cast<T>(0) < static_cast<T>(-1);
};

template <typename T> struct _RemoveExtentImpl: TypeValue<T> {};
template <typename T> struct _RemoveExtentImpl<T[]>: TypeValue<T> {};
template <typename T, std::size_t N>
struct _RemoveExtentImpl<T[N]>: TypeValue<T> {};

template <typename T> struct _RemoveAllExtentsImpl: TypeValue<T> {};
template <typename T>
struct _RemoveAllExtentsImpl<T[]>
    : TypeValue<typename _RemoveAllExtentsImpl<T>::type>
{};
template <typename T, std::size_t N>
struct _RemoveAllExtentsImpl<T[N]>
    : TypeValue<typename _RemoveAllExtentsImpl<T>::type>
{};

template <typename T> struct _RemovePointerImpl: TypeValue<T> {};
template <typename T> struct _RemovePointerImpl<T*>: TypeValue<T> {};
template <typename T> struct _RemovePointerImpl<T * const>: TypeValue<T> {};
template <typename T> struct _RemovePointerImpl<T * volatile>: TypeValue<T> {};
template <typename T>
struct _RemovePointerImpl<T * const volatile>: TypeValue<T> {};

template <typename T> struct _RemoveAllPointersImpl: TypeValue<T> {};
template <typename T>
struct _RemoveAllPointersImpl<T*>
    : TypeValue<typename _RemoveAllPointersImpl<T>::type>
{};
template <typename T>
struct _RemoveAllPointersImpl<T * const>
    : TypeValue<typename _RemoveAllPointersImpl<T>::type>
{};
template <typename T>
struct _RemoveAllPointersImpl<T * volatile>
    : TypeValue<typename _RemoveAllPointersImpl<T>::type>
{};
template <typename T>
struct _RemoveAllPointersImpl<T * const volatile>
    : TypeValue<typename _RemoveAllPointersImpl<T>::type>
{};

template <bool B, typename T> struct _EnableIfImpl {};
template <typename T> struct _EnableIfImpl<true,T>: TypeValue<T> {};

template <bool B, typename T, typename F>
struct _ConditionalImpl: TypeValue<T> {};
template <typename T, typename F>
struct _ConditionalImpl<false,T,F>: TypeValue<F> {};

// cv void& substitution failure
template <typename T>
_RemoveRefImpl<T>::type& _addLVRefImpl(int) { static_assert(0); }
// T = cv void
template <typename T> T _addLVRefImpl(...) { static_assert(0); }

template <typename T>
_RemoveRefImpl<T>::type&& _addRVRefImpl(int) { static_assert(0); }
template <typename T> T _addRVRefImpl(...) { static_assert(0); }

} // namespace _detail

/// are 2 types the same (including const and references)
template <typename T, typename U>
static constexpr bool isSame = _detail::_IsSameImpl<T,U>::value;

/// is a type void (possibly cv qualified)
template <typename T>
static constexpr bool isVoid = isSame<T,void> || isSame<T,const void>
    || isSame<T,volatile void> || isSame<T,const volatile void>;

/// is type T the same as any of Us...
template <typename T, typename ...Us>
static constexpr bool isSameAsAny = (isSame<T,Us> || ...);

/// is a type an array
template <typename T>
static constexpr bool isArray = _detail::_IsArrayImpl<T>::value;

/// typename without a (move) reference
template <typename T>
using RemoveRef = _detail::_RemoveRefImpl<T>::type;

/// type T without const or volatile
template <typename T>
using RemoveCV = _detail::_RemoveCVImpl<T>::type;

/// type T without const
template <typename T>
using RemoveConst = _detail::_RemoveConstImpl<T>::type;

/// type T without volatile
template <typename T>
using RemoveVolatile = _detail::_RemoveVolatileImpl<T>::type;

/// type T is a pointer
template <typename T>
static constexpr bool isPointer = _detail::_IsPointerImpl<T>::value;

/// type T is a l-value reference
template <typename T>
static constexpr bool isLVRef = _detail::_IsLVRefImpl<T>::value;

/// type T is a r-value reference
template <typename T>
static constexpr bool isRVRef = _detail::_IsRVRefImpl<T>::value;

/// type T is a reference (l-value or r-value)
template <typename T>
static constexpr bool isRef = _detail::_IsRefImpl<T>::value;

/// type T is const qualified
template <typename T>
static constexpr bool isConst = _detail::_IsConstImpl<T>::value;

/// type T is volatile qualified
template <typename T>
static constexpr bool isVolatile = _detail::_IsVolatileImpl<T>::value;

/// type T is a signed number
template <typename T>
static constexpr bool isSigned = _detail::_IsSignedImpl<T>::value;

/// type T is an unsigned number
template <typename T>
static constexpr bool isUnsigned = _detail::_IsUnsignedImpl<T>::value;

/// type T with a single extent removed if it has one
template <typename T>
using RemoveExtent = _detail::_RemoveExtentImpl<T>::type;

/// type T with all extents removed
template <typename T>
using RemoveAllExtents = _detail::_RemoveAllExtentsImpl<T>::type;

/// type T with a single pointer removed if it has one
template <typename T>
using RemovePointer = _detail::_RemovePointerImpl<T>::type;

/// type T with all pointers removed
template <typename T>
using RemoveAllPointers = _detail::_RemoveAllPointersImpl<T>::type;

/// type T without const/volatile or reference
template <typename T>
using RemoveCVRef = RemoveCV<typename RemoveRef<T>::type>::type;

/// type T if given true, substitution failure otherwwise (SFINAE)
template <bool B, typename T = void>
using EnableIf = _detail::_EnableIfImpl<B,T>::type;

/// type T if given true, type F if given false
template <bool B, typename T, typename F>
using Conditional = _detail::_ConditionalImpl<B,T,F>::type;

/// type T with l-value reference
template <typename T>
using AddLVRef = decltype(_detail::_addLVRefImpl<T>(0));

/// type T with r-value reference
template <typename T>
using AddRVRef = decltype(_detail::_addRVRefImpl<T>(0));

/// instance of type T for unevaluated contexts (like std::declval)
template <typename T>
constexpr T declVal()
{ static_assert(0,"only allowed in unevaluated contexts"); }

} // namespace tkoz::stl::meta
