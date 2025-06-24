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

template <typename T> struct _IsTemplatedImpl: FalseValue {};
template <template <typename...> typename T, typename ...Us>
struct _IsTemplatedImpl<T<Us...>>: TrueValue {};

// (T, T&, T&&) -> T
template <typename T> struct _RemoveRefImpl: TypeValue<T> {};
template <typename T> struct _RemoveRefImpl<T&>: TypeValue<T> {};
template <typename T> struct _RemoveRefImpl<T&&>: TypeValue<T> {};

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

template <typename T, typename U>
struct _CopyRefImpl: TypeValue<typename _RemoveRefImpl<U>::type> {};
template <typename T, typename U>
struct _CopyRefImpl<T&,U>: TypeValue<typename _RemoveRefImpl<U>::type&> {};
template <typename T, typename U>
struct _CopyRefImpl<T&&,U>: TypeValue<typename _RemoveRefImpl<U>::type&&> {};

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

template <typename T, typename U>
struct _CopyConstImpl: TypeValue<typename _RemoveConstImpl<U>::type> {};
template <typename T, typename U>
struct _CopyConstImpl<const T,U>: TypeValue<const U> {};

template <typename T, typename U>
struct _CopyVolatileImpl: TypeValue<typename _RemoveVolatileImpl<U>::type> {};
template <typename T, typename U>
struct _CopyVolatileImpl<volatile T,U>: TypeValue<volatile U> {};

template <typename T, typename U>
struct _CopyCVImpl: TypeValue<typename _RemoveCVImpl<U>::type> {};
template <typename T, typename U>
struct _CopyCVImpl<const T,U>:
    TypeValue<const typename _RemoveCVImpl<U>::type> {};
template <typename T, typename U>
struct _CopyCVImpl<volatile T,U>:
    TypeValue<volatile typename _RemoveCVImpl<U>::type> {};
template <typename T, typename U>
struct _CopyCVImpl<const volatile T,U>: TypeValue<const volatile U> {};

} // namespace _detail

//
// few basic type checks
//

/// are 2 types the same (including const and references)
template <typename T, typename U>
static constexpr bool isSame = _detail::_IsSameImpl<T,U>::value;

/// is type T the same as any of Us...
template <typename T, typename ...Us>
static constexpr bool isSameAsAny = (isSame<T,Us> || ...);

/// is a type an array
template <typename T>
static constexpr bool isArray = _detail::_IsArrayImpl<T>::value;

/// is T a templated type
template <typename T>
static constexpr bool isTemplated = _detail::_IsTemplatedImpl<T>::value;

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
static constexpr bool isConst =
    _detail::_IsConstImpl<typename _detail::_RemoveRefImpl<T>::type>::value;

/// type T is volatile qualified
template <typename T>
static constexpr bool isVolatile =
    _detail::_IsVolatileImpl<typename _detail::_RemoveRefImpl<T>::type>::value;

//
// reference types
//

/// typename without a (move) reference
template <typename T>
using RemoveRef = _detail::_RemoveRefImpl<T>::type;

/// type T with l-value reference
template <typename T>
using AddLVRef = decltype(_detail::_addLVRefImpl<T>(0));

/// type T with r-value reference
template <typename T>
using AddRVRef = decltype(_detail::_addRVRefImpl<T>(0));

/// copy reference type from T to U
template <typename T, typename U>
using CopyRef = _detail::_CopyRefImpl<T,U>::type;

//
// const/volatile qualifiers
//

/// type T without const or volatile
template <typename T>
using RemoveCV =
    CopyRef<T,typename _detail::_RemoveCVImpl<RemoveRef<T>>::type>;

/// type T without const
template <typename T>
using RemoveConst =
    CopyRef<T,typename _detail::_RemoveConstImpl<RemoveRef<T>>::type>;

/// type T without volatile
template <typename T>
using RemoveVolatile =
    CopyRef<T,typename _detail::_RemoveVolatileImpl<RemoveRef<T>>::type>;

/// copy const qualifier from T to U
template <typename T, typename U>
using CopyConst = CopyRef<U,
    typename _detail::_CopyConstImpl<RemoveRef<T>,RemoveRef<U>>::type>;

/// copy volatile qualifier from T to U
template <typename T, typename U>
using CopyVolatile = CopyRef<U,
    typename _detail::_CopyVolatileImpl<RemoveRef<T>,RemoveRef<U>>::type>;

/// copy cv qualifiers from T to U
template <typename T, typename U>
using CopyCV = CopyRef<U,
    typename _detail::_CopyCVImpl<RemoveRef<T>,RemoveRef<U>>::type>;

//
// both cv qualifiers and reference
//

/// type T without const/volatile or reference
template <typename T>
using RemoveCVRef = RemoveCV<RemoveRef<T>>;

/// copy reference type and cv qualifiers from T to U
template <typename T, typename U>
using CopyCVRef = CopyRef<T,CopyCV<T,U>>;

//
// other types
//

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

/// type T if given true, substitution failure otherwwise (SFINAE)
template <bool B, typename T = void>
using EnableIf = _detail::_EnableIfImpl<B,T>::type;

/// type T if given true, type F if given false
template <bool B, typename T, typename F>
using Conditional = _detail::_ConditionalImpl<B,T,F>::type;

/// type T is a signed number
template <typename T>
static constexpr bool isSigned =
    _detail::_IsSignedImpl<RemoveCVRef<T>>::value;

/// type T is an unsigned number
template <typename T>
static constexpr bool isUnsigned =
    _detail::_IsUnsignedImpl<RemoveCVRef<T>>::value;

//
// instantiate a value for expressions in unevaluated contexts
//

/// instance of type T for unevaluated contexts (like std::declval)
template <typename T>
constexpr T declVal()
{
    static_assert(0, "only allowed in unevaluated contexts");
}

//
// type equality ignoring cv qualifiers/reference
//

/// are 2 types the same ignoring const qualifiers
template <typename T, typename U>
static constexpr bool isSameIgnoreConst =
    isSame<RemoveConst<T>,RemoveConst<U>>;

/// are 2 types the same ignoring volatile qualifiers
template <typename T, typename U>
static constexpr bool isSameIgnoreVolatile =
    isSame<RemoveVolatile<T>,RemoveVolatile<U>>;

/// are 2 types the same ignoring cv qualifiers
template <typename T, typename U>
static constexpr bool isSameIgnoreCV = isSame<RemoveCV<T>,RemoveCV<U>>;

/// are 2 types the same ignoring reference
template <typename T, typename U>
static constexpr bool isSameIgnoreRef = isSame<RemoveRef<T>,RemoveRef<U>>;

/// are 2 types the same ignoring cv qualifiers and reference
template <typename T, typename U>
static constexpr bool isSameIgnoreCVRef = isSame<RemoveCVRef<T>,RemoveCVRef<U>>;

//
// return types of using operators
//

/// result type of adding T and U
template <typename T, typename U = T>
using AddResult = decltype(declVal<T>() + declVal<U>());

/// result type of subtracting T and U
template <typename T, typename U = T>
using SubResult = decltype(declVal<T>() - declVal<U>());

/// result type of positive of T
template <typename T>
using PosResult = decltype(+declVal<T>());

/// result type of negative of T
template <typename T>
using NegResult = decltype(-declVal<T>());

/// result type of multiplying T and U
template <typename T, typename U = T>
using MulResult = decltype(declVal<T>() * declVal<U>());

/// result type of dividing T and U
template <typename T, typename U = T>
using DivResult = decltype(declVal<T>() / declVal<U>());

/// result type of modding T and U
template <typename T, typename U = T>
using ModResult = decltype(declVal<T>() % declVal<U>());

/// result type of pre incrementing T
template <typename T>
using PreIncResult = decltype(++declVal<T>());

/// result type of post incrementing T
template <typename T>
using PostIncResult = decltype(declVal<T>()++);

/// result type of pre decrementing T
template <typename T>
using PreDecResult = decltype(--declVal<T>());

/// result type of post decrementing T
template <typename T>
using PostDecResult = decltype(declVal<T>()--);

/// result type of comparing T and U equal
template <typename T, typename U = T>
using CmpEqResult = decltype(declVal<T>() == declVal<U>());

/// result type of comparing T and U not equal
template <typename T, typename U = T>
using CmpNeResult = decltype(declVal<T>() != declVal<U>());

/// result type of comparing T and U less than
template <typename T, typename U = T>
using CmpLtResult = decltype(declVal<T>() < declVal<U>());

/// result type of comparing T and U less than or equal to
template <typename T, typename U = T>
using CmpLeResult = decltype(declVal<T>() <= declVal<U>());

/// result type of comparing T and U greater than
template <typename T, typename U = T>
using CmpGtResult = decltype(declVal<T>() > declVal<U>());

/// result type of comparing T and U greater than or equal to
template <typename T, typename U = T>
using CmpGeResult = decltype(declVal<T>() >= declVal<U>());

/// result type of 3 way comparing T and U
template <typename T, typename U = T>
using Cmp3wayResult = decltype(declVal<T>() <=> declVal<U>());

/// result type of logical not T
template <typename T>
using LNotResult = decltype(!declVal<T>());

/// result type of logical and T and U
template <typename T, typename U = T>
using LAndResult = decltype(declVal<T>() && declVal<U>());

/// result type of logical or T and U
template <typename T, typename U = T>
using LOrResult = decltype(declVal<T>() || declVal<U>());

/// result type of bit not T
template <typename T>
using BitNotResult = decltype(~declVal<T>());

/// result type of bit and T and U
template <typename T, typename U = T>
using BitAndResult = decltype(declVal<T>() & declVal<U>());

/// result type of bit or T and U
template <typename T, typename U = T>
using BitOrResult = decltype(declVal<T>() | declVal<U>());

/// result type of bit xor T and U
template <typename T, typename U = T>
using BitXorResult = decltype(declVal<T>() ^ declVal<U>());

/// result type of bit shift left T and U
template <typename T, typename U = T>
using ShiftLeftResult = decltype(declVal<T>() << declVal<U>());

/// result type of bit shift right T and U
template <typename T, typename U = T>
using ShiftRightResult = decltype(declVal<T>() >> declVal<U>());

/// result type of assigning U to T
template <typename T, typename U = T>
using AssignResult = decltype(declVal<T>() = declVal<U>());

/// result type of compound adding T and U
template <typename T, typename U = T>
using AddEqResult = decltype(declVal<T>() += declVal<U>());

/// result type of compound subtracting T and U
template <typename T, typename U = T>
using SubEqResult = decltype(declVal<T>() -= declVal<U>());

/// result type of compound multiplying T and U
template <typename T, typename U = T>
using MulEqResult = decltype(declVal<T>() *= declVal<U>());

/// result type of compound dividing T and U
template <typename T, typename U = T>
using DivEqResult = decltype(declVal<T>() /= declVal<U>());

/// result type of compound modding T and U
template <typename T, typename U = T>
using ModEqResult = decltype(declVal<T>() %= declVal<U>());

/// result type of compound anding T and U
template <typename T, typename U = T>
using AndEqResult = decltype(declVal<T>() &= declVal<U>());

/// result type of compound oring T and U
template <typename T, typename U = T>
using OrEqResult = decltype(declVal<T>() |= declVal<U>());

/// result type of compound xoring T and U
template <typename T, typename U = T>
using XorEqResult = decltype(declVal<T>() ^= declVal<U>());

/// result type of compound shifting left T and U
template <typename T, typename U = T>
using ShiftLeftEqResult = decltype(declVal<T>() <<= declVal<U>());

/// result type of compound shifting right T and U
template <typename T, typename U = T>
using ShiftRightEqResult = decltype(declVal<T>() >>= declVal<U>());

/// result type of dereferencing T
template <typename T>
using DerefResult = decltype(*declVal<T>());

/// result type of address of T
template <typename T>
using AddrResult = decltype(&declVal<T>());

/// result type of subscripting T
template <typename T, typename ...Us>
using SubscriptResult = decltype(declVal<T>()[declVal<Us>()...]);

/// result type of calling T
template <typename T, typename ...Us>
using CallResult = decltype(declVal<T>()(declVal<Us>()...));

//
// same as specific types ignoring cvref
//

/// type is void (possibly cv qualified)
template <typename T>
static constexpr bool isVoid = isSame<meta::RemoveCVRef<T>,void>;

/// type is bool (possibly cvref qualified)
template <typename T>
static constexpr bool isBool = isSame<meta::RemoveCVRef<T>,bool>;

} // namespace tkoz::stl::meta
