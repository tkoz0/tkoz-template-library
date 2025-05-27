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

/// type is bool
template <typename T>
concept isBool = meta::isSame<T,bool>;

/// type is float, double, or long double
template <typename T>
concept isPrimitiveFloatingPoint =
    meta::isSameAsAny<T,float,double,long double>;

/// type is char, unsigned char, or signed char
template <typename T>
concept isAnyChar = meta::isSameAsAny<T,char,unsigned char,signed char>;

/// type is a primitive signed integer
template <typename T>
concept isPrimitiveSignedInteger =
    meta::isSameAsAny<T,signed char,signed short,signed int,
                        signed long,signed long long>;

/// type is a primitive unsigned integer
template <typename T>
concept isPrimitiveUnsignedInteger =
    meta::isSameAsAny<T,unsigned char,unsigned short,unsigned int,
                        unsigned long,unsigned long long>;

/// type is a primitive integer
template <typename T>
concept isPrimitiveInteger = isPrimitiveSignedInteger<T>
    || isPrimitiveUnsignedInteger<T>;

/// type is primitive integer or bool (integral)
template <typename T>
concept isPrimitiveIntegerOrBool = isPrimitiveInteger<T> || isBool<T>;

} // namespace tkoz::stl::concepts
