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

static_assert(isSame<bool,bool>);
static_assert(!isSame<bool*,bool>);
static_assert(!isSame<bool**,bool>);
static_assert(!isSame<bool&,bool>);
static_assert(!isSame<bool&&,bool>);
static_assert(!isSame<bool&,bool&&>);
static_assert(!isSame<const bool,bool>);
static_assert(isSame<void*,void*>);
static_assert(!isSame<void*,void**>);
static_assert(!isSame<void**,void*>);

// check of default sign (note char and signed char are different)
static_assert(!isSame<char,signed char>);
static_assert(!isSame<char,unsigned char>);
static_assert(isSame<short,signed short>);
static_assert(!isSame<short,unsigned short>);
static_assert(isSame<int,signed int>);
static_assert(!isSame<int,unsigned int>);
static_assert(isSame<long,signed long>);
static_assert(!isSame<long,unsigned long>);
static_assert(isSame<long long,signed long long>);
static_assert(!isSame<long long,unsigned long long>);

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

static_assert(isSame<removeRef<bool>,bool>);
static_assert(isSame<removeRef<bool&>,bool>);
static_assert(isSame<removeRef<bool&&>,bool>);
static_assert(isSame<removeRef<void*>,void*>);
static_assert(isSame<removeRef<void*&>,void*>);
static_assert(isSame<removeRef<void*&&>,void*>);

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

static_assert(!isSameAsAny<char,signed char,unsigned char>);
static_assert(!isSameAsAny<bool>);
static_assert(isSameAsAny<bool,bool>);
static_assert(isSameAsAny<bool,void,bool>);
static_assert(!isSameAsAny<bool,void,void*>);
static_assert(!isSameAsAny<char,int,int,int>);

} // namespace tkoz::stl::meta
