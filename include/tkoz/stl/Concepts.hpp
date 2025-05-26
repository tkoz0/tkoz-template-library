///
/// template concepts for template parameter constraints
///

#pragma once

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

namespace tkoz::stl::concepts
{

/// type is void
template <typename T>
concept isVoid = meta::isSame<T,void>;

static_assert(isVoid<void>);
static_assert(!isVoid<void*>);
static_assert(!isVoid<bool>);

/// type is bool
template <typename T>
concept isBool = meta::isSame<T,bool>;

static_assert(isBool<bool>);
static_assert(!isBool<int>);

/// type is float, double, or long double
template <typename T>
concept isPrimitiveFloatingPoint =
    meta::isSameAsAny<T,float,double,long double>;

static_assert(isPrimitiveFloatingPoint<float>);
static_assert(isPrimitiveFloatingPoint<double>);
static_assert(isPrimitiveFloatingPoint<long double>);
static_assert(!isPrimitiveFloatingPoint<long>);

/// type is char, unsigned char, or signed char
template <typename T>
concept isAnyChar = meta::isSameAsAny<T,char,unsigned char,signed char>;

static_assert(isAnyChar<char>);
static_assert(isAnyChar<signed char>);
static_assert(isAnyChar<unsigned char>);
static_assert(!isAnyChar<void>);
static_assert(!isAnyChar<bool>);

/// type is a primitive signed integer
template <typename T>
concept isPrimitiveSignedInteger =
    meta::isSameAsAny<T,signed char,signed short,signed int,
                        signed long,signed long long>;

static_assert(isPrimitiveSignedInteger<signed char>);
static_assert(isPrimitiveSignedInteger<short>);
static_assert(isPrimitiveSignedInteger<int>);
static_assert(isPrimitiveSignedInteger<long>);
static_assert(isPrimitiveSignedInteger<long long>);
static_assert(!isPrimitiveSignedInteger<unsigned int>);
static_assert(!isPrimitiveSignedInteger<bool>);

/// type is a primitive unsigned integer
template <typename T>
concept isPrimitiveUnsignedInteger =
    meta::isSameAsAny<T,unsigned char,unsigned short,unsigned int,
                        unsigned long,unsigned long long>;

static_assert(isPrimitiveUnsignedInteger<unsigned char>);
static_assert(isPrimitiveUnsignedInteger<unsigned short>);
static_assert(isPrimitiveUnsignedInteger<unsigned int>);
static_assert(isPrimitiveUnsignedInteger<unsigned long>);
static_assert(isPrimitiveUnsignedInteger<unsigned long long>);
static_assert(!isPrimitiveUnsignedInteger<int>);
static_assert(!isPrimitiveUnsignedInteger<bool>);

/// type is a primitive integer
template <typename T>
concept isPrimitiveInteger = isPrimitiveSignedInteger<T>
    || isPrimitiveUnsignedInteger<T>;

/// type is primitive integer or bool (integral)
template <typename T>
concept isPrimitiveIntegerOrBool = isPrimitiveInteger<T> || isBool<T>;

} // namespace tkoz::stl::concepts
