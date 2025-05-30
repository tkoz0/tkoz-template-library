///
/// template concepts for template parameter constraints
///

#pragma once

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

#include <compare>

namespace tkoz::stl::concepts
{

/// 2 types are the same
template <typename T, typename U>
concept isSame = meta::isSame<T,U> && meta::isSame<U,T>;

/// type T is the same as any of Us...
template <typename T, typename ...Us>
concept isSameAsAny = (false || ... || isSame<T,Us>);

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

// char is signed even though char is different type from signed char
static_assert(static_cast<char>(-1) < static_cast<char>(0));

// checks for signed/unsigned integers
static_assert(static_cast<signed char>(-1) < static_cast<signed char>(0));
static_assert(static_cast<unsigned char>(-1) > static_cast<unsigned char>(0));
static_assert(static_cast<signed short>(-1) < static_cast<signed short>(0));
static_assert(static_cast<unsigned short>(-1) > static_cast<unsigned short>(0));
static_assert(static_cast<signed int>(-1) < static_cast<signed int>(0));
static_assert(static_cast<unsigned int>(-1) > static_cast<unsigned int>(0));
static_assert(static_cast<signed long>(-1) < static_cast<signed long>(0));
static_assert(static_cast<unsigned long>(-1) > static_cast<unsigned long>(0));
static_assert(static_cast<signed long long>(-1)
    < static_cast<signed long long>(0));
static_assert(static_cast<unsigned long long>(-1)
    > static_cast<unsigned long long>(0));

/// type is a primitive signed integer
template <typename T>
concept isPrimitiveSignedInteger =
    meta::isSameAsAny<T,char,signed char,signed short,signed int,
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

/// type is primitive number (integer or floating point)
template <typename T>
concept isPrimitiveNumber = isPrimitiveInteger<T>
    || isPrimitiveFloatingPoint<T>;

/// type is primitive
template <typename T>
concept isPrimitive = isPrimitiveIntegerOrBool<T>
    || isPrimitiveFloatingPoint<T>;

//
// Checks on validity of calling operators and copy constructor
// These have expected result types that are applicable to common types
//

/// Can a SrcType object be used to construct a DstType object
/// \note If DstType and SrcType are the same, this checks the copy constructor
template <typename DstType, typename SrcType>
concept canConvert = requires (SrcType value)
{ { meta::RemoveRef<DstType>(value) } -> isSame<meta::RemoveRef<DstType>>; };

/// Can a SrcType object be statically casted to a DstType object
template <typename DstType, typename SrcType>
concept canStaticCast = requires (SrcType value)
{ { static_cast<DstType>(value) } -> isSame<DstType>; };

/// Can a SrcType object be dynamically casted to a DstType object
template <typename DstType, typename SrcType>
concept canDynamicCast = requires (SrcType value)
{ { dynamic_cast<DstType>(value) } -> isSame<DstType>; };

/// Can a SrcType object be const casted to a DstType object
template <typename DstType, typename SrcType>
concept canConstCast = requires (SrcType value)
{ { const_cast<DstType>(value) } -> isSame<DstType>; };

/// Can a SrcType object be reinterpret casted to a DstType object
template <typename DstType, typename SrcType>
concept canReinterpretCast = requires (SrcType value)
{ { reinterpret_cast<DstType>(value) } -> isSame<DstType>; };

/// Can a SrcType object be assigned to a DstType object (a = b)
/// And is the result a DstType reference as usual
template <typename DstType, typename SrcType>
concept canAssign = requires (DstType dst, SrcType src)
{ { dst = src } -> isSame<meta::AddLVRef<DstType>>; };

/// Can Type be added to same type
template <typename Type>
concept canAddSame = requires (Type a, Type b)
{ { a + b } -> isSame<meta::RemoveRef<Type>>; };

/// Can Type be subtracted to same type
template <typename Type>
concept canSubSame = requires (Type a, Type b)
{ { a - b } -> isSame<meta::RemoveRef<Type>>; };

/// Does Type support unary plus to same type
template <typename Type>
concept canPosSame = requires (Type t)
{ { +t } -> isSame<meta::RemoveRef<Type>>; };

/// Does Type support unary minus to same type
template <typename Type>
concept canNegSame = requires (Type t)
{ { -t } -> isSame<meta::RemoveRef<Type>>; };

/// Can Type be multiplied to same type
template <typename Type>
concept canMulSame = requires (Type a, Type b)
{ { a * b } -> isSame<meta::RemoveRef<Type>>; };

/// Can Type be divided to same type
template <typename Type>
concept canDivSame = requires (Type a, Type b)
{ { a / b } -> isSame<meta::RemoveRef<Type>>; };

/// Does Type support modulus to same type
template <typename Type>
concept canModSame = requires (Type a, Type b)
{ { a % b } -> isSame<meta::RemoveRef<Type>>; };

/// Can a Type object be pre incremented (with a Type& result)
template <typename Type>
concept canPreInc = requires (Type t)
{ { ++t } -> isSame<meta::AddLVRef<Type>>; };

/// Can a Type object be post incremented (with a Type result)
template <typename Type>
concept canPostInc = requires (Type t)
{ { t++ } -> isSame<meta::RemoveRef<Type>>; };

/// Can a Type object be pre decremented (with a Type& result)
template <typename Type>
concept canPreDec = requires (Type t)
{ { --t } -> isSame<meta::AddLVRef<Type>>; };

/// Can a Type object be post decremented (with a Type result)
template <typename Type>
concept canPostDec = requires (Type t)
{ { t-- } -> isSame<meta::RemoveRef<Type>>; };

/// Can 2 types be compared equal (bool)
template <typename LeftType, typename RightType>
concept canCmpEq = requires (LeftType l, RightType r)
{ { l == r } -> isSame<bool>; };

/// Can 2 types be compared not equal (bool)
template <typename LeftType, typename RightType>
concept canCmpNe = requires (LeftType l, RightType r)
{ { l != r } -> isSame<bool>; };

/// Can 2 types be compared less than (bool)
template <typename LeftType, typename RightType>
concept canCmpLt = requires (LeftType l, RightType r)
{ { l < r } -> isSame<bool>; };

/// Can 2 types be compared less than or equal to (bool)
template <typename LeftType, typename RightType>
concept canCmpLe = requires (LeftType l, RightType r)
{ { l <= r } -> isSame<bool>; };

/// Can 2 types be compared greater than (bool)
template <typename LeftType, typename RightType>
concept canCmpGt = requires (LeftType l, RightType r)
{ { l > r } -> isSame<bool>; };

/// Can 2 types be compared greater than or equal to (bool)
template <typename LeftType, typename RightType>
concept canCmpGe = requires (LeftType l, RightType r)
{ { l >= r } -> isSame<bool>; };

/// Can 2 types be compared 3 way (std::strong_ordering)
template <typename LeftType, typename RightType>
concept canCmp3way = requires (LeftType l, RightType r)
{ { l <=> r } -> isSame<std::strong_ordering>; };

/// Is the address of a type the expected pointer type
template <typename Type>
concept canAddr = requires (Type t)
{ { &t } -> isSame<meta::RemoveRef<Type>*>; };

/// Can 2 types be compound added
template <typename LeftType, typename RightType>
concept canAddEq = requires (LeftType l, RightType r)
{ { l += r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types be compound subtracted
template <typename LeftType, typename RightType>
concept canSubEq = requires (LeftType l, RightType r)
{ { l -= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types be compound multiplied
template <typename LeftType, typename RightType>
concept canMulEq = requires (LeftType l, RightType r)
{ { l *= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types be compound divided
template <typename LeftType, typename RightType>
concept canDivEq = requires (LeftType l, RightType r)
{ { l /= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound modulo
template <typename LeftType, typename RightType>
concept canModEq = requires (LeftType l, RightType r)
{ { l %= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound and
template <typename LeftType, typename RightType>
concept canAndEq = requires (LeftType l, RightType r)
{ { l &= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound or
template <typename LeftType, typename RightType>
concept canOrEq = requires (LeftType l, RightType r)
{ { l |= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound xor
template <typename LeftType, typename RightType>
concept canXorEq = requires (LeftType l, RightType r)
{ { l ^= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound shift left
template <typename LeftType, typename RightType>
concept canShiftLeftEq = requires (LeftType l, RightType r)
{ { l <<= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound shift right
template <typename LeftType, typename RightType>
concept canShiftRightEq = requires (LeftType l, RightType r)
{ { l >>= r } -> isSame<meta::AddLVRef<LeftType>>; };

//
// Check if an operator is supported with some types
// The result type is ignored
//

/// Do 2 types have addition (a + b)
template <typename LeftType, typename RightType>
concept hasAdd = requires (LeftType l, RightType r) { l + r; };

/// Do 2 types have subtraction (a - b)
template <typename LeftType, typename RightType>
concept hasSub = requires (LeftType l, RightType r) { l - r; };

/// Does a type have unary + (+obj)
template <typename Type>
concept hasPos = requires (Type t) { +t; };

/// Does a type have unary - (-obj)
template <typename Type>
concept hasNeg = requires (Type t) { -t; };

/// Do 2 types have multiplication (a * b)
template <typename LeftType, typename RightType>
concept hasMul = requires (LeftType l, RightType r) { l * r; };

/// Do 2 types have division (a / b)
template <typename LeftType, typename RightType>
concept hasDiv = requires (LeftType l, RightType r) { l / r; };

/// Do 2 types have modulo
template <typename LeftType, typename RightType>
concept hasMod = requires (LeftType l, RightType r) { l % r; };

/// Does a type have prefix increment (++obj)
template <typename Type>
concept hasPreInc = requires (Type t) { ++t; };

/// Does a type have postfix increment (obj++)
template <typename Type>
concept hasPostInc = requires (Type t) { t++; };

/// Does a type have prefix decrement (--obj)
template <typename Type>
concept hasPreDec = requires (Type t) { --t; };

/// Does a type have postfix decrement (obj--)
template <typename Type>
concept hasPostDec = requires (Type t) { t--; };

/// Do 2 types have compare equal
template <typename LeftType, typename RightType>
concept hasCmpEq = requires (LeftType l, RightType r) { l == r; };

/// Do 2 types have compare not equal
template <typename LeftType, typename RightType>
concept hasCmpNe = requires (LeftType l, RightType r) { l != r; };

/// Do 2 types have compare less than
template <typename LeftType, typename RightType>
concept hasCmpLt = requires (LeftType l, RightType r) { l < r; };

/// Do 2 types have compare less than or equal to
template <typename LeftType, typename RightType>
concept hasCmpLe = requires (LeftType l, RightType r) { l <= r; };

/// Do 2 types have compare greater than
template <typename LeftType, typename RightType>
concept hasCmpGt = requires (LeftType l, RightType r) { l > r; };

/// Do 2 types have compare greater than or equal to
template <typename LeftType, typename RightType>
concept hasCmpGe = requires (LeftType l, RightType r) { l >= r; };

/// Does a type have logical not
template <typename Type>
concept hasLNot = requires (Type t) { !t; };

/// Do 2 types have logical and
template <typename LeftType, typename RightType>
concept hasLAnd = requires (LeftType l, RightType r) { l && r; };

/// Do 2 types have logical or
template <typename LeftType, typename RightType>
concept hasLOr = requires (LeftType l, RightType r) { l || r; };

/// Does a type have bit not
template <typename Type>
concept hasBitNot = requires (Type t) { ~t; };

/// Do 2 types have bit and
template <typename LeftType, typename RightType>
concept hasBitAnd = requires (LeftType l, RightType r) { l & r; };

/// Do 2 types have bit or
template <typename LeftType, typename RightType>
concept hasBitOr = requires (LeftType l, RightType r) { l | r; };

/// Do 2 types have bit xor
template <typename LeftType, typename RightType>
concept hasBitXor = requires (LeftType l, RightType r) { l ^ r; };

/// Do 2 types have shift left
template <typename LeftType, typename RightType>
concept hasShiftLeft = requires (LeftType l, RightType r) { l << r; };

/// Do 2 types have shift right
template <typename LeftType, typename RightType>
concept hasShiftRight = requires (LeftType l, RightType r) { l >> r; };

/// Do 2 types have assignment
template <typename LeftType, typename RightType>
concept hasAssign = requires (LeftType l, RightType r) { l = r; };

/// Do 2 types have compound add
template <typename LeftType, typename RightType>
concept hasAddEq = requires (LeftType l, RightType r) { l += r; };

/// Do 2 types have compound subtract
template <typename LeftType, typename RightType>
concept hasSubEq = requires (LeftType l, RightType r) { l -= r; };

/// Do 2 types have compound multiply
template <typename LeftType, typename RightType>
concept hasMulEq = requires (LeftType l, RightType r) { l *= r; };

/// Do 2 types have compound divide
template <typename LeftType, typename RightType>
concept hasDivEq = requires (LeftType l, RightType r) { l /= r; };

/// Do 2 types have compound modulus
template <typename LeftType, typename RightType>
concept hasModEq = requires (LeftType l, RightType r) { l %= r; };

/// Do 2 types have compound and
template <typename LeftType, typename RightType>
concept hasAndEq = requires (LeftType l, RightType r) { l &= r; };

/// Do 2 types have compound or
template <typename LeftType, typename RightType>
concept hasOrEq = requires (LeftType l, RightType r) { l |= r; };

/// Do 2 types have compound xor
template <typename LeftType, typename RightType>
concept hasXorEq = requires (LeftType l, RightType r) { l ^= r; };

/// Do 2 types have compound shift left
template <typename LeftType, typename RightType>
concept hasShiftLeftEq = requires (LeftType l, RightType r) { l <<= r; };

/// Do 2 types have compound shift right
template <typename LeftType, typename RightType>
concept hasShiftRightEq = requires (LeftType l, RightType r) { l >>= r; };

/// Do a type have subscript with given args
template <typename LeftType, typename ...ArgTypes>
concept hasSubscript = requires (LeftType l, ArgTypes ...a) { l[a...]; };
// TODO visual studio code error with expanding parameter pack in subscript

/// Does a type have dereference
template <typename Type>
concept hasDeref = requires (Type t) { *t; };

/// Does a type have address of
template <typename Type>
concept hasAddr = requires (Type t) { &t; };

/// Does a type have calling with given args
template <typename LeftType, typename ...ArgTypes>
concept hasCall = requires (LeftType l, ArgTypes ...a) { l(a...); };

} // namespace tkoz::stl::concepts
