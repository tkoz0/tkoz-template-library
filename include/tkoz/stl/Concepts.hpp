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
concept isSameAsAny = (isSame<T,Us> || ...);

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

/// Can all SrcTypes be used to construct a DstType object
template <typename DstType, typename ...SrcTypes>
concept canConvertAll = (canConvert<DstType,SrcTypes> && ...);

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
/// \note this may be useful for checking implicit convertibility
template <typename DstType, typename SrcType>
concept canAssign = requires (DstType dst, SrcType src)
{ { dst = src } -> isSame<meta::AddLVRef<DstType>>; };

/// Can all SrcTypes be assigned to a DstType object (a = b)
template <typename DstType, typename ...SrcTypes>
concept canAssignAll = (canAssign<DstType,SrcTypes> && ...);

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

/// Can a Type object be pre incremented (with usual Type& result)
template <typename Type>
concept canPreInc = requires (Type t)
{ { ++t } -> isSame<meta::AddLVRef<Type>>; };

/// Can a Type object be post incremented (with usual Type result)
template <typename Type>
concept canPostInc = requires (Type t)
{ { t++ } -> isSame<meta::RemoveRef<Type>>; };

/// Can a Type object be pre decremented (with usual Type& result)
template <typename Type>
concept canPreDec = requires (Type t)
{ { --t } -> isSame<meta::AddLVRef<Type>>; };

/// Can a Type object be post decremented (with usual Type result)
template <typename Type>
concept canPostDec = requires (Type t)
{ { t-- } -> isSame<meta::RemoveRef<Type>>; };

/// Can 2 types be compared equal (bool)
template <typename LeftType, typename RightType>
concept canCmpEq = requires (LeftType l, RightType r)
{ { l == r } -> isSame<bool>; };

/// Can a type be compared equal to itself (bool)
template <typename Type> concept canCmpEqSame = canCmpEq<Type,Type>;

/// Can 2 types be compared not equal (bool)
template <typename LeftType, typename RightType>
concept canCmpNe = requires (LeftType l, RightType r)
{ { l != r } -> isSame<bool>; };

/// Can a type be compared not equal to itself (bool)
template <typename Type> concept canCmpNeSame = canCmpNe<Type,Type>;

/// Can 2 types be compared less than (bool)
template <typename LeftType, typename RightType>
concept canCmpLt = requires (LeftType l, RightType r)
{ { l < r } -> isSame<bool>; };

/// Can a type be compared less than itself (bool)
template <typename Type> concept canCmpLtSame = canCmpLt<Type,Type>;

/// Can 2 types be compared less than or equal to (bool)
template <typename LeftType, typename RightType>
concept canCmpLe = requires (LeftType l, RightType r)
{ { l <= r } -> isSame<bool>; };

/// Can a type be compared less than or equal to itself (bool)
template <typename Type> concept canCmpLeSame = canCmpLe<Type,Type>;

/// Can 2 types be compared greater than (bool)
template <typename LeftType, typename RightType>
concept canCmpGt = requires (LeftType l, RightType r)
{ { l > r } -> isSame<bool>; };

/// Can a type be compared greater than itself (bool)
template <typename Type> concept canCmpGtSame = canCmpGt<Type,Type>;

/// Can 2 types be compared greater than or equal to (bool)
template <typename LeftType, typename RightType>
concept canCmpGe = requires (LeftType l, RightType r)
{ { l >= r } -> isSame<bool>; };

/// Can a type be compared greater than or equal to itself (bool)
template <typename Type> concept canCmpGeSame = canCmpGe<Type,Type>;

/// Can 2 types be compared 3 way (std::strong_ordering)
template <typename LeftType, typename RightType>
concept canCmp3wayStrong = requires (LeftType l, RightType r)
{ { l <=> r } -> isSame<std::strong_ordering>; };

/// Can 2 types be compared 3 way (std::weak_ordering)
template <typename LeftType, typename RightType>
concept canCmp3wayWeak = requires (LeftType l, RightType r)
{ { l <=> r } -> isSame<std::weak_ordering>; };

/// Can 2 types be compared 3 way (std::partial_ordering)
template <typename LeftType, typename RightType>
concept canCmp3wayPartial = requires (LeftType l, RightType r)
{ { l <=> r } -> isSame<std::partial_ordering>; };

/// Can a type be 3 way compared with itself (std::strong_ordering)
template <typename Type> concept canCmp3waySameStrong =
    canCmp3wayStrong<Type,Type>;

/// Can a type be 3 way compared with itself (std::weak_ordering)
template <typename Type> concept canCmp3waySameWeak =
    canCmp3wayWeak<Type,Type>;

/// Can a type be 3 way compared with itself (std::partial_ordering)
template <typename Type> concept canCmp3waySamePartial =
    canCmp3wayPartial<Type,Type>;

/// Is the address of a type the expected pointer type
template <typename Type>
concept canAddr = requires (Type t)
{ { &t } -> isSame<meta::RemoveRef<Type>*>; };

/// Can 2 types be compound added (usual Type& result)
template <typename LeftType, typename RightType>
concept canAddEq = requires (LeftType l, RightType r)
{ { l += r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be compound added to itself (usual Type& result)
template <typename Type> concept canAddEqSame = canAddEq<Type,Type>;

/// Can 2 types be compound subtracted (usual Type& result)
template <typename LeftType, typename RightType>
concept canSubEq = requires (LeftType l, RightType r)
{ { l -= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be compound subtracted from itself (usual Type& result)
template <typename Type> concept canSubEqSame = canSubEq<Type,Type>;

/// Can 2 types be compound multiplied (usual Type& result)
template <typename LeftType, typename RightType>
concept canMulEq = requires (LeftType l, RightType r)
{ { l *= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be compound multiplied by itself (usual Type& result)
template <typename Type> concept canMulEqSame = canMulEq<Type,Type>;

/// Can 2 types be compound divided (usual Type& result)
template <typename LeftType, typename RightType>
concept canDivEq = requires (LeftType l, RightType r)
{ { l /= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be compound divided by itself (usual Type& result)
template <typename Type> concept canDivEqSame = canDivEq<Type,Type>;

/// Can 2 types support compound modulo (usual Type& result)
template <typename LeftType, typename RightType>
concept canModEq = requires (LeftType l, RightType r)
{ { l %= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type support compound modulo by itself (usual Type& result)
template <typename Type> concept canModEqSame = canModEq<Type,Type>;

/// Can 2 types support compound and (usual Type& result)
template <typename LeftType, typename RightType>
concept canAndEq = requires (LeftType l, RightType r)
{ { l &= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be bit anded with itself (usual Type& result)
template <typename Type> concept canAndEqSame = canAndEq<Type,Type>;

/// Can 2 types support compound or (usual Type& result)
template <typename LeftType, typename RightType>
concept canOrEq = requires (LeftType l, RightType r)
{ { l |= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be bit ored with itself (usual Type& result)
template <typename Type> concept canOrEqSame = canOrEq<Type,Type>;

/// Can 2 types support compound xor (usual Type& result)
template <typename LeftType, typename RightType>
concept canXorEq = requires (LeftType l, RightType r)
{ { l ^= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can a type be bit xored with itself (usual Type& result)
template <typename Type> concept canXorEqSame = canXorEq<Type,Type>;

/// Can 2 types support compound shift left (usual Type& result)
template <typename LeftType, typename RightType>
concept canShiftLeftEq = requires (LeftType l, RightType r)
{ { l <<= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can 2 types support compound shift right (usual Type& result)
template <typename LeftType, typename RightType>
concept canShiftRightEq = requires (LeftType l, RightType r)
{ { l >>= r } -> isSame<meta::AddLVRef<LeftType>>; };

/// Can Type be tested for logical not (bool result)
template <typename Type>
concept canLNot = requires (Type t) { { !t } -> isSame<bool>; };

/// Can 2 types be tested for logical and (bool result)
template <typename LeftType, typename RightType>
concept canLAnd = requires (LeftType l, RightType r)
{ { l && r } -> isSame<bool>; };

/// Can 2 types be tested for logical or (bool result)
template <typename LeftType, typename RightType>
concept canLOr = requires (LeftType l, RightType r)
{ { l || r } -> isSame<bool>; };

/// Can Type be bit not to same type
template <typename Type>
concept canBitNotSame = requires (Type t) { { ~t } -> isSame<Type>; };

/// Can Type be bit and to same type
template <typename Type>
concept canBitAndSame = requires (Type l, Type r)
{ { l & r } -> isSame<Type>; };

/// Can Type be bit or to same type
template <typename Type>
concept canBitOrSame = requires (Type l, Type r)
{ { l | r } -> isSame<Type>; };

/// Can Type be bit xor to same type
template <typename Type>
concept canBitXorSame = requires (Type l, Type r)
{ { l ^ r } -> isSame<Type>; };

//
// Check if an operator is supported with some types
// The result type is ignored
//

/// Do 2 types have addition (a + b)
template <typename LeftType, typename RightType>
concept hasAdd = requires (LeftType l, RightType r) { l + r; };

/// Does Type have addition with itself
template <typename Type> concept hasAddSame = hasAdd<Type,Type>;

/// Do 2 types have subtraction (a - b)
template <typename LeftType, typename RightType>
concept hasSub = requires (LeftType l, RightType r) { l - r; };

/// Does Type have subtraction with itself
template <typename Type> concept hasSubSame = hasSub<Type,Type>;

/// Does a type have unary + (+obj)
template <typename Type>
concept hasPos = requires (Type t) { +t; };

/// Does a type have unary - (-obj)
template <typename Type>
concept hasNeg = requires (Type t) { -t; };

/// Do 2 types have multiplication (a * b)
template <typename LeftType, typename RightType>
concept hasMul = requires (LeftType l, RightType r) { l * r; };

/// Does Type have multiplication with itself
template <typename Type> concept hasMulSame = hasMul<Type,Type>;

/// Do 2 types have division (a / b)
template <typename LeftType, typename RightType>
concept hasDiv = requires (LeftType l, RightType r) { l / r; };

/// Does Type have division with itself
template <typename Type> concept hasDivSame = hasDiv<Type,Type>;

/// Do 2 types have modulo
template <typename LeftType, typename RightType>
concept hasMod = requires (LeftType l, RightType r) { l % r; };

/// Does Type have modulus with itself
template <typename Type> concept hasModSame = hasMod<Type,Type>;

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

/// Does Type have compare equal with itself
template <typename Type> concept hasCmpEqSame = hasCmpEq<Type,Type>;

/// Do 2 types have compare not equal
template <typename LeftType, typename RightType>
concept hasCmpNe = requires (LeftType l, RightType r) { l != r; };

/// Does Type have compare not equal with itself
template <typename Type> concept hasCmpNeSame = hasCmpNe<Type,Type>;

/// Do 2 types have compare less than
template <typename LeftType, typename RightType>
concept hasCmpLt = requires (LeftType l, RightType r) { l < r; };

/// Does Type have compare less that with itself
template <typename Type> concept hasCmpLtSame = hasCmpLt<Type,Type>;

/// Do 2 types have compare less than or equal to
template <typename LeftType, typename RightType>
concept hasCmpLe = requires (LeftType l, RightType r) { l <= r; };

/// Does Type have compare less than or equal to with itself
template <typename Type> concept hasCmpLeSame = hasCmpLe<Type,Type>;

/// Do 2 types have compare greater than
template <typename LeftType, typename RightType>
concept hasCmpGt = requires (LeftType l, RightType r) { l > r; };

/// Does Type have compare grater that with itself
template <typename Type> concept hasCmpGtSame = hasCmpGt<Type,Type>;

/// Do 2 types have compare greater than or equal to
template <typename LeftType, typename RightType>
concept hasCmpGe = requires (LeftType l, RightType r) { l >= r; };

/// Does Type have compare greater than or equal to with itself
template <typename Type> concept hasCmpGeSame = hasCmpGe<Type,Type>;

/// Do 2 types have 3 way compare
template <typename LeftType, typename RightType>
concept hasCmp3way = requires (LeftType l, RightType r) { l <=> r; };

/// Does Type have 3 way compare with itself
template <typename Type> concept hasCmp3waySame = hasCmp3way<Type,Type>;

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

/// Does Type have bit and with itself
template <typename Type> concept hasBitAndSame = hasBitAnd<Type,Type>;

/// Do 2 types have bit or
template <typename LeftType, typename RightType>
concept hasBitOr = requires (LeftType l, RightType r) { l | r; };

/// Does Type have bit or with itself
template <typename Type> concept hasBitOrSame = hasBitOr<Type,Type>;

/// Do 2 types have bit xor
template <typename LeftType, typename RightType>
concept hasBitXor = requires (LeftType l, RightType r) { l ^ r; };

/// Does Type have bit xor with itself
template <typename Type> concept hasBitXorSame = hasBitXor<Type,Type>;

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

/// Does Type have compound add to itself
template <typename Type> concept hasAddEqSame = hasAddEq<Type,Type>;

/// Do 2 types have compound subtract
template <typename LeftType, typename RightType>
concept hasSubEq = requires (LeftType l, RightType r) { l -= r; };

/// Does Type have comound subtract from itself
template <typename Type> concept hasSubEqSame = hasSubEq<Type,Type>;

/// Do 2 types have compound multiply
template <typename LeftType, typename RightType>
concept hasMulEq = requires (LeftType l, RightType r) { l *= r; };

/// Does Type have compound multiply with itself
template <typename Type> concept hasMulEqSame = hasMulEq<Type,Type>;

/// Do 2 types have compound divide
template <typename LeftType, typename RightType>
concept hasDivEq = requires (LeftType l, RightType r) { l /= r; };

/// Does Type have compound divide with itself
template <typename Type> concept hasDivEqSame = hasDivEq<Type,Type>;

/// Do 2 types have compound modulus
template <typename LeftType, typename RightType>
concept hasModEq = requires (LeftType l, RightType r) { l %= r; };

/// Does Type have compound modulus with itself
template <typename Type> concept hasModEqSame = hasModEq<Type,Type>;

/// Do 2 types have compound and
template <typename LeftType, typename RightType>
concept hasAndEq = requires (LeftType l, RightType r) { l &= r; };

/// Does Type have compound bit and with itself
template <typename Type> concept hasAndEqSame = hasAndEq<Type,Type>;

/// Do 2 types have compound or
template <typename LeftType, typename RightType>
concept hasOrEq = requires (LeftType l, RightType r) { l |= r; };

/// Does Type have compound bit or with itself
template <typename Type> concept hasOrEqSame = hasOrEq<Type,Type>;

/// Do 2 types have compound xor
template <typename LeftType, typename RightType>
concept hasXorEq = requires (LeftType l, RightType r) { l ^= r; };

/// Does Type have compound bit xor with itself
template <typename Type> concept hasXorEqSame = hasXorEq<Type,Type>;

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
