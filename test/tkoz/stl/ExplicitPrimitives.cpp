//
// Unit tests for explicit primitive types
//

#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/ExplicitPrimitives.hpp>
#include <tkoz/stl/Meta.hpp>

#include <tkoz/Test.hpp>

#include <limits>

TEST_RUNNER_MAIN

// EP = explicit primitive
template <typename T>
using EP = tkoz::stl::wrapper::ExplicitPrimitive<T>;

// abbreviated names

using EPB   = tkoz::stl::wrapper::ExplicitBool;
using EPC   = tkoz::stl::wrapper::ExplicitChar;
using EPSC  = tkoz::stl::wrapper::ExplicitSChar;
using EPUC  = tkoz::stl::wrapper::ExplicitUChar;
using EPSS  = tkoz::stl::wrapper::ExplicitSShort;
using EPUS  = tkoz::stl::wrapper::ExplicitUShort;
using EPSI  = tkoz::stl::wrapper::ExplicitSInt;
using EPUI  = tkoz::stl::wrapper::ExplicitUInt;
using EPSL  = tkoz::stl::wrapper::ExplicitSLong;
using EPUL  = tkoz::stl::wrapper::ExplicitULong;
using EPSLL = tkoz::stl::wrapper::ExplicitSLL;
using EPULL = tkoz::stl::wrapper::ExplicitULL;
using EPF   = tkoz::stl::wrapper::ExplicitFloat;
using EPD   = tkoz::stl::wrapper::ExplicitDouble;
using EPLD  = tkoz::stl::wrapper::ExplicitLDouble;

namespace meta = tkoz::stl::meta;
namespace tsc = tkoz::stl::concepts;

// can convert all ExplicitPrimitives to given type
template <typename T>
concept canConvertAllEPTo = tkoz::stl::concepts::canConvertAll<T,
    EPB,EPC,EPSC,EPUC,EPSS,EPUS,EPSI,EPUI,EPSL,EPUL,EPSLL,EPULL,EPF,EPD,EPLD>;

// can convert all primitives to given type
template <typename T>
concept canConvertAllPrimTo = tkoz::stl::concepts::canConvertAll<T,
    bool, char, signed char, unsigned char, signed short, unsigned short,
    signed int, unsigned int, signed long, unsigned long,
    signed long long, unsigned long long, float, double, long double>;

TEST_CASE_CREATE(testSizes)
{
    // all static_assert so a runtime test case is not really needed
    // but this allows wrapping the using namespace inside a scope block
    using namespace tkoz::stl::wrapper;
    static_assert(sizeof(ExplicitBool)    == sizeof(bool));
    static_assert(sizeof(ExplicitChar)    == sizeof(char));
    static_assert(sizeof(ExplicitSChar)   == sizeof(signed char));
    static_assert(sizeof(ExplicitUChar)   == sizeof(unsigned char));
    static_assert(sizeof(ExplicitSShort)  == sizeof(signed short));
    static_assert(sizeof(ExplicitUShort)  == sizeof(unsigned short));
    static_assert(sizeof(ExplicitSInt)    == sizeof(signed int));
    static_assert(sizeof(ExplicitUInt)    == sizeof(unsigned int));
    static_assert(sizeof(ExplicitSLong)   == sizeof(signed long));
    static_assert(sizeof(ExplicitULong)   == sizeof(unsigned long));
    static_assert(sizeof(ExplicitSLL)     == sizeof(signed long long));
    static_assert(sizeof(ExplicitULL)     == sizeof(unsigned long long));
    static_assert(sizeof(ExplicitFloat)   == sizeof(float));
    static_assert(sizeof(ExplicitDouble)  == sizeof(double));
    static_assert(sizeof(ExplicitLDouble) == sizeof(long double));

    static_assert(tsc::isSame<ExplicitBool   ::ValueType,bool>);
    static_assert(tsc::isSame<ExplicitChar   ::ValueType,char>);
    static_assert(tsc::isSame<ExplicitSChar  ::ValueType,signed char>);
    static_assert(tsc::isSame<ExplicitUChar  ::ValueType,unsigned char>);
    static_assert(tsc::isSame<ExplicitSShort ::ValueType,signed short>);
    static_assert(tsc::isSame<ExplicitUShort ::ValueType,unsigned short>);
    static_assert(tsc::isSame<ExplicitSInt   ::ValueType,signed int>);
    static_assert(tsc::isSame<ExplicitUInt   ::ValueType,unsigned int>);
    static_assert(tsc::isSame<ExplicitSLong  ::ValueType,signed long>);
    static_assert(tsc::isSame<ExplicitULong  ::ValueType,unsigned long>);
    static_assert(tsc::isSame<ExplicitSLL    ::ValueType,signed long long>);
    static_assert(tsc::isSame<ExplicitULL    ::ValueType,unsigned long long>);
    static_assert(tsc::isSame<ExplicitFloat  ::ValueType,float>);
    static_assert(tsc::isSame<ExplicitDouble ::ValueType,double>);
    static_assert(tsc::isSame<ExplicitLDouble::ValueType,long double>);

    static_assert(ExplicitBool   ::cValueSize == sizeof(bool));
    static_assert(ExplicitChar   ::cValueSize == sizeof(char));
    static_assert(ExplicitSChar  ::cValueSize == sizeof(signed char));
    static_assert(ExplicitUChar  ::cValueSize == sizeof(unsigned char));
    static_assert(ExplicitSShort ::cValueSize == sizeof(signed short));
    static_assert(ExplicitUShort ::cValueSize == sizeof(unsigned short));
    static_assert(ExplicitSInt   ::cValueSize == sizeof(signed int));
    static_assert(ExplicitUInt   ::cValueSize == sizeof(unsigned int));
    static_assert(ExplicitSLong  ::cValueSize == sizeof(signed long));
    static_assert(ExplicitULong  ::cValueSize == sizeof(unsigned long));
    static_assert(ExplicitSLL    ::cValueSize == sizeof(signed long long));
    static_assert(ExplicitULL    ::cValueSize == sizeof(unsigned long long));
    static_assert(ExplicitFloat  ::cValueSize == sizeof(float));
    static_assert(ExplicitDouble ::cValueSize == sizeof(double));
    static_assert(ExplicitLDouble::cValueSize == sizeof(long double));
}

TEST_CASE_CREATE(testBool)
{
    // false,cmp
    EPB f1(false);
    EPB f2 = false;
    bool f3 = (bool) f2;
    bool f4 = static_cast<bool>(f1);
    TEST_ASSERT_FALSE(f1);
    TEST_ASSERT_FALSE(f2);
    TEST_ASSERT_FALSE(f3);
    TEST_ASSERT_FALSE(f4);
    TEST_ASSERT_EQ(f1,f2);
    TEST_ASSERT_EQ(f1,false);
    TEST_ASSERT_EQ(false,f1);
    TEST_ASSERT_NE(f1,true);
    TEST_ASSERT_NE(true,f1);
    int f5 = static_cast<int>(f1);
    TEST_ASSERT_EQ(f5,0);

    // true,cmp
    EPB t1(true);
    EPB t2 = true;
    bool t3 = (bool) t2;
    bool t4 = static_cast<bool>(t1);
    TEST_ASSERT_TRUE(t1);
    TEST_ASSERT_TRUE(t2);
    TEST_ASSERT_TRUE(t3);
    TEST_ASSERT_TRUE(t4);
    TEST_ASSERT_EQ(t1,t2);
    TEST_ASSERT_EQ(t1,true);
    TEST_ASSERT_EQ(true,t1);
    TEST_ASSERT_NE(t1,false);
    TEST_ASSERT_NE(false,t1);
    int t5 = static_cast<int>(t1);
    TEST_ASSERT_EQ(t5,1);

    // construct
    TEST_ASSERT_FALSE(EPB());
    TEST_ASSERT_FALSE(EPB(false));
    TEST_ASSERT_TRUE(EPB(true));
    TEST_ASSERT_FALSE(EPB(0));
    TEST_ASSERT_TRUE(EPB(1));
    TEST_ASSERT_FALSE(EPB(-0.0));
    TEST_ASSERT_TRUE(EPB(-0.1));
    TEST_ASSERT_TRUE(EPB(EPC(42)));
    TEST_ASSERT_FALSE(EPB(EPC('\0')));
    TEST_ASSERT_TRUE(EPB(EPSLL(5)));
    TEST_ASSERT_FALSE(EPB(EPSLL(0)));

    // not
    TEST_ASSERT_TRUE(!f1);
    TEST_ASSERT_FALSE(!t1);

    // and
    TEST_ASSERT_FALSE(f1 && f2);
    TEST_ASSERT_FALSE(f1 && t1);
    TEST_ASSERT_FALSE(t1 && f1);
    TEST_ASSERT_TRUE(t1 && t2);
    TEST_ASSERT_FALSE(f1 & f2);
    TEST_ASSERT_FALSE(f1 & t1);
    TEST_ASSERT_FALSE(t1 & f1);
    TEST_ASSERT_TRUE(t1 & t2);
    f1 &= false;
    t1 &= false;
    TEST_ASSERT_FALSE(f1);
    TEST_ASSERT_FALSE(t1);
    f1 = false;
    t1 = true;
    f1 &= true;
    t1 &= true;
    TEST_ASSERT_FALSE(f1);
    TEST_ASSERT_TRUE(t1);
    f1 = false;
    t1 = true;

    // or
    TEST_ASSERT_FALSE(f1 || f2);
    TEST_ASSERT_TRUE(f1 || t1);
    TEST_ASSERT_TRUE(t1 || f1);
    TEST_ASSERT_TRUE(t1 || t2);
    TEST_ASSERT_FALSE(f1 | f2);
    TEST_ASSERT_TRUE(f1 | t1);
    TEST_ASSERT_TRUE(t1 | f1);
    TEST_ASSERT_TRUE(t1 | t2);
    f1 |= false;
    t1 |= false;
    TEST_ASSERT_FALSE(f1);
    TEST_ASSERT_TRUE(t1);
    f1 = false;
    t1 = true;
    f1 |= true;
    t1 |= true;
    TEST_ASSERT_TRUE(f1);
    TEST_ASSERT_TRUE(t1);
    f1 = false;
    t1 = true;

    // xor
    TEST_ASSERT_FALSE(f1 ^ f2);
    TEST_ASSERT_TRUE(f1 ^ t1);
    TEST_ASSERT_TRUE(t1 ^ f1);
    TEST_ASSERT_FALSE(t1 ^ t2);
    f1 ^= false;
    t1 ^= false;
    TEST_ASSERT_FALSE(f1);
    TEST_ASSERT_TRUE(t1);
    f1 = false;
    t1 = true;
    f1 ^= true;
    t1 ^= true;
    TEST_ASSERT_TRUE(f1);
    TEST_ASSERT_FALSE(t1);
    f1 = false;
    t1 = true;

    // compile validity of copy ctor and explicit conversion
    static_assert(canConvertAllPrimTo<EPB>);
    static_assert(canConvertAllEPTo<EPB>);

    // compile validity of operator= (includes implicit conversion test)
    static_assert(tsc::canAssign<EPB,EPB>);
    static_assert(tsc::canAssign<EPB,bool>);
    static_assert(!tsc::canAssign<EPB,int>);
    static_assert(!tsc::canAssign<EPB,double>);
    static_assert(!tsc::canAssign<EPB,EPC>);
    static_assert(!tsc::canAssign<EPB,EPSC>);
    static_assert(!tsc::canAssign<EPB,EPSS>);
    static_assert(!tsc::canAssign<EPB,EPSI>);
    static_assert(!tsc::canAssign<EPB,EPSL>);
    static_assert(!tsc::canAssign<EPB,EPSLL>);
    static_assert(!tsc::canAssign<EPB,EPUC>);
    static_assert(!tsc::canAssign<EPB,EPUS>);
    static_assert(!tsc::canAssign<EPB,EPUI>);
    static_assert(!tsc::canAssign<EPB,EPUL>);
    static_assert(!tsc::canAssign<EPB,EPULL>);
    static_assert(!tsc::canAssign<EPB,EPF>);
    static_assert(!tsc::canAssign<EPB,EPD>);
    static_assert(!tsc::canAssign<EPB,EPLD>);
    static_assert(!tsc::canAssign<char,EPB>);
    static_assert(!tsc::canAssign<signed char,EPB>);
    static_assert(!tsc::canAssign<signed short,EPB>);
    static_assert(!tsc::canAssign<signed int,EPB>);
    static_assert(!tsc::canAssign<signed long,EPB>);
    static_assert(!tsc::canAssign<signed long long,EPB>);
    static_assert(!tsc::canAssign<unsigned char,EPB>);
    static_assert(!tsc::canAssign<unsigned short,EPB>);
    static_assert(!tsc::canAssign<unsigned int,EPB>);
    static_assert(!tsc::canAssign<unsigned long,EPB>);
    static_assert(!tsc::canAssign<unsigned long long,EPB>);
    static_assert(!tsc::canAssign<float,EPB>);
    static_assert(!tsc::canAssign<double,EPB>);
    static_assert(!tsc::canAssign<long double,EPB>);
    // this should be allowed if a good solution can be found
    //static_assert(tsc::canAssign<bool,EPB>);

    // self arithmetic
    static_assert(!tsc::hasAdd<EPB>);
    static_assert(!tsc::hasSub<EPB>);
    static_assert(!tsc::hasPos<EPB>);
    static_assert(!tsc::hasNeg<EPB>);
    static_assert(!tsc::hasMul<EPB>);
    static_assert(!tsc::hasDiv<EPB>);
    static_assert(!tsc::hasMod<EPB>);

    // inc/dec
    static_assert(!tsc::hasPreInc<EPB>);
    static_assert(!tsc::hasPostInc<EPB>);
    static_assert(!tsc::hasPreDec<EPB>);
    static_assert(!tsc::hasPostDec<EPB>);

    // cmp
    static_assert(tsc::canCmpEq<EPB>);
    static_assert(tsc::canCmpNe<EPB>);
    static_assert(!tsc::hasCmpLt<EPB>);
    static_assert(!tsc::hasCmpLe<EPB>);
    static_assert(!tsc::hasCmpGt<EPB>);
    static_assert(!tsc::hasCmpGe<EPB>);
    static_assert(!tsc::hasCmp3way<EPB>);

    // logic/bit
    static_assert(tsc::canLNot<EPB>);
    static_assert(tsc::canLAnd<EPB,EPB>);
    static_assert(tsc::canLOr<EPB,EPB>);
    static_assert(tsc::canBitNotSame<EPB>);
    static_assert(tsc::canBitAndSame<EPB>);
    static_assert(tsc::canBitOrSame<EPB>);
    static_assert(tsc::canBitXorSame<EPB>);

    // compound assign
    static_assert(!tsc::hasAddEq<EPB,EPB>);
    static_assert(!tsc::hasSubEq<EPB,EPB>);
    static_assert(!tsc::hasMulEq<EPB,EPB>);
    static_assert(!tsc::hasDivEq<EPB,EPB>);
    static_assert(!tsc::hasModEq<EPB,EPB>);
    static_assert(tsc::canAndEq<EPB,EPB>);
    static_assert(tsc::canOrEq<EPB,EPB>);
    static_assert(tsc::canXorEq<EPB,EPB>);
    static_assert(!tsc::hasShiftLeftEq<EPB,EPB>);
    static_assert(!tsc::hasShiftRightEq<EPB,EPB>);

    // pointer
    static_assert(tsc::canAddr<EPB>);
    static_assert(!tsc::hasDeref<EPB>);
}

// static cast abbreviation
template <typename T, typename U>
T sc(U value)
{
    return static_cast<T>(value);
}

// if and only if
constexpr bool iff(bool a, bool b)
{
    return (a && b) || (!a && !b);
}

// number tests and static_assert
template <typename T>
    requires tkoz::stl::concepts::isPrimitiveNumber<T>
void testNumber()
{
    using EPT = EP<T>;

    // copy ctor and explicit conversion
    static_assert(canConvertAllPrimTo<EPT>);
    static_assert(canConvertAllEPTo<EPT>);

    // operator= and implicit conversion
    static_assert(!tsc::canAssign<EPT,EPB>);
    // EPT = EPSC if and only if EPSC can be assigned to EPT ...
    static_assert(iff(tsc::isSame<EPT,EPC>,tsc::canAssign<EPT,EPC>));
    static_assert(iff(tsc::isSame<EPT,EPSC>,tsc::canAssign<EPT,EPSC>));
    static_assert(iff(tsc::isSame<EPT,EPSS>,tsc::canAssign<EPT,EPSS>));
    static_assert(iff(tsc::isSame<EPT,EPSI>,tsc::canAssign<EPT,EPSI>));
    static_assert(iff(tsc::isSame<EPT,EPSL>,tsc::canAssign<EPT,EPSL>));
    static_assert(iff(tsc::isSame<EPT,EPSLL>,tsc::canAssign<EPT,EPSLL>));
    static_assert(iff(tsc::isSame<EPT,EPUC>,tsc::canAssign<EPT,EPUC>));
    static_assert(iff(tsc::isSame<EPT,EPUS>,tsc::canAssign<EPT,EPUS>));
    static_assert(iff(tsc::isSame<EPT,EPUI>,tsc::canAssign<EPT,EPUI>));
    static_assert(iff(tsc::isSame<EPT,EPUL>,tsc::canAssign<EPT,EPUL>));
    static_assert(iff(tsc::isSame<EPT,EPULL>,tsc::canAssign<EPT,EPULL>));
    static_assert(iff(tsc::isSame<EPT,EPF>,tsc::canAssign<EPT,EPF>));
    static_assert(iff(tsc::isSame<EPT,EPD>,tsc::canAssign<EPT,EPD>));
    static_assert(iff(tsc::isSame<EPT,EPLD>,tsc::canAssign<EPT,EPLD>));
    // this is disallowed, but if there is a good solution, allow it
    //static_assert(tsc::canAssign<T,EPT>);

    // self arithmetic
    static_assert(tsc::canAddSame<EPT>);
    static_assert(tsc::canSubSame<EPT>);
    static_assert(tsc::canPosSame<EPT>);
    static_assert(tsc::canNegSame<EPT>);
    static_assert(tsc::canMulSame<EPT>);
    static_assert(tsc::canDivSame<EPT>);
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canModSame<EPT>));

    // inc/dec
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canPreInc<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canPostInc<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canPreDec<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canPostDec<EPT>));

    // cmp
    static_assert(tsc::canCmpEq<EPT>);
    static_assert(tsc::canCmpNe<EPT>);
    static_assert(tsc::canCmpLt<EPT>);
    static_assert(tsc::canCmpLe<EPT>);
    static_assert(tsc::canCmpGt<EPT>);
    static_assert(tsc::canCmpGe<EPT>);
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canCmp3wayStrong<EPT>));
    static_assert(iff(tsc::isPrimitiveFloatingPoint<T>,tsc::canCmp3wayPartial<EPT>));

    // logic/bit
    static_assert(tsc::canLNot<EPT>);
    static_assert(tsc::canLAnd<EPT,EPT>);
    static_assert(tsc::canLOr<EPT,EPT>);
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canBitNotSame<EPT>));
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canBitAndSame<EPT>));
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canBitOrSame<EPT>));
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canBitXorSame<EPT>));

    // compound assign
    static_assert(tsc::canAddEq<EPT>);
    static_assert(tsc::canSubEq<EPT>);
    static_assert(tsc::canMulEq<EPT>);
    static_assert(tsc::canDivEq<EPT>);
    static_assert(iff(!tsc::isPrimitiveFloatingPoint<T>,tsc::canModEq<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canAndEq<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canOrEq<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::canXorEq<EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::hasShiftLeftEq<EPT,EPT>));
    static_assert(iff(tsc::isPrimitiveInteger<T>,tsc::hasShiftRightEq<EPT,EPT>));

    // pointer
    static_assert(tsc::canAddr<EPT>);
    static_assert(!tsc::hasDeref<EPT>);
}

// signed integer tests and static_assert
template <typename T>
    requires tkoz::stl::concepts::isPrimitiveSignedInteger<T>
void testSigned()
{
    using EPT = EP<T>;

    EPT a = sc<T>(31);
    T b = sc<T>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPT(31));
    TEST_ASSERT_TRUE(a);
    TEST_ASSERT_FALSE(EPT(0));
    TEST_ASSERT_EQ(a,EPT(EPC(31)));
    TEST_ASSERT_TRUE(EPT(1));

    // some 8 bit operations which should work with all signed types

    // arithmetic
    TEST_ASSERT_EQ(EPT(40) + EPT(13), EPT(53));
    TEST_ASSERT_EQ(EPT(40) - EPT(13), EPT(27));
    TEST_ASSERT_EQ(+EPT(-12), EPT(-12));
    TEST_ASSERT_EQ(-EPT(-12), EPT(12));
    TEST_ASSERT_EQ(EPT(9) * EPT(15), EPT(135));
    TEST_ASSERT_EQ(EPT(60) / EPT(7), EPT(8));
    TEST_ASSERT_EQ(EPT(90) % EPT(21), EPT(6));

    // inc/dec
    EPT e1(6);
    TEST_ASSERT_EQ(++e1, EPT(7));
    TEST_ASSERT_EQ(e1,EPT(7));
    TEST_ASSERT_EQ(e1++, EPT(7));
    TEST_ASSERT_EQ(e1,EPT(8));
    TEST_ASSERT_EQ(--e1, EPT(7));
    TEST_ASSERT_EQ(e1,EPT(7));
    TEST_ASSERT_EQ(e1--, EPT(7));
    TEST_ASSERT_EQ(e1,EPT(6));

    // cmp
    e1 = EPT(10);
    EPT e2(11);
    TEST_ASSERT_LT(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_NE(e1,e2);
    ++e1;
    TEST_ASSERT_EQ(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    ++e1;
    TEST_ASSERT_GT(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    TEST_ASSERT_NE(e1,e2);

    // logic/bit
    // inversion (~) flips high bits too so test it for each type
    TEST_ASSERT_EQ(EPT(0xCC) & EPT(0xF0), EPT(0xC0));
    TEST_ASSERT_EQ(EPT(0xCC) | EPT(0xF0), EPT(0xFC));
    TEST_ASSERT_EQ(EPT(0xCC) ^ EPT(0xF0), EPT(0x3C));

    // compound assign
    e1 = EPT(30);
    TEST_ASSERT_EQ(&(e1 += EPT(6)), &e1);
    TEST_ASSERT_EQ(e1,EPT(36));
    TEST_ASSERT_EQ(&(e1 -= EPT(14)), &e1);
    TEST_ASSERT_EQ(e1,EPT(22));
    TEST_ASSERT_EQ(&(e1 *= EPT(3)), &e1);
    TEST_ASSERT_EQ(e1,EPT(66));
    TEST_ASSERT_EQ(&(e1 /= EPT(9)), &e1);
    TEST_ASSERT_EQ(e1,EPT(7));
    TEST_ASSERT_EQ(&(e1 %= EPT(3)), &e1);
    TEST_ASSERT_EQ(e1,EPT(1));
    e1 = EPT(0x78);
    TEST_ASSERT_EQ(&(e1 &= EPT(0x32)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x30));
    TEST_ASSERT_EQ(&(e1 |= EPT(0x83)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0xB3));
    TEST_ASSERT_EQ(&(e1 ^= EPT(0x84)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x37));
    TEST_ASSERT_EQ(&(e1 <<= 1), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x6E));
    TEST_ASSERT_EQ(&(e1 >>= 4), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x06));
}

TEST_CASE_CREATE(testChar)
{
    testSigned<char>();
    testNumber<char>();
    TEST_ASSERT_EQ(~EPC(0xF0),EPC(0x0F));
}

TEST_CASE_CREATE(testSChar)
{
    testSigned<signed char>();
    testNumber<signed char>();

    EPSC a = static_cast<signed char>(10);
    signed char b = static_cast<signed char>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPSC(10));
    TEST_ASSERT_EQ(a,EPSC(EPC(10)));
    TEST_ASSERT_EQ(~EPSC(0xF0),EPSC(0x0F));
}

TEST_CASE_CREATE(testSShort)
{
    testSigned<signed short>();
    testNumber<signed short>();

    EPSS a = static_cast<short>(11);
    signed short b = static_cast<short>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPSS(11));
    TEST_ASSERT_EQ(a,EPSS(EPC(11)));
    TEST_ASSERT_EQ(~EPSS(0xF0),EPSS(0xFF0F));
}

TEST_CASE_CREATE(testSInt)
{
    testSigned<signed int>();
    testNumber<signed int>();

    EPSI a = 12;
    signed int b = static_cast<int>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPSI(12));
    TEST_ASSERT_EQ(a,EPSI(EPC(12)));
    TEST_ASSERT_EQ(~EPSI(0x0FF00000),EPSI(0xF00FFFFF));
}

TEST_CASE_CREATE(testSLong)
{
    testSigned<signed long>();
    testNumber<signed long>();

    EPSL a = 13l;
    signed long b = static_cast<long>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPSL(13));
    TEST_ASSERT_EQ(a,EPSL(EPC(13)));
    TEST_ASSERT_EQ(~EPSL(0x1020304050607080),EPSL(0xEFDFCFBFAF9F8F7F));
}

TEST_CASE_CREATE(testSLL)
{
    testSigned<signed long long>();
    testNumber<signed long long>();

    EPSLL a = 14ll;
    signed long long b = static_cast<long long>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPSLL(14));
    TEST_ASSERT_EQ(a,EPSLL(EPC(14)));
    TEST_ASSERT_EQ(~EPSLL(0x0F0E0D0C0B0A0908),EPSLL(0xF0F1F2F3F4F5F6F7));
}

// unsigned integer tests and static_assert
template <typename T>
    requires tkoz::stl::concepts::isPrimitiveUnsignedInteger<T>
void testUnsigned()
{
    using EPT = EP<T>;

    EPT a = sc<T>(21);
    T b = sc<T>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPT(21));
    TEST_ASSERT_TRUE(a);
    TEST_ASSERT_FALSE(EPT(0));
    TEST_ASSERT_EQ(a,EPT(EPC(21)));
    TEST_ASSERT_TRUE(EPT(1));

    // some 8 bit operations which should work with all unsigned types

    // arithmetic
    TEST_ASSERT_EQ(EPT(105) + EPT(61), EPT(166));
    TEST_ASSERT_EQ(EPT(105) - EPT(61), EPT(44));
    TEST_ASSERT_EQ(+EPT(57), EPT(57));
    TEST_ASSERT_EQ(-EPT(57), EPT(-57));
    TEST_ASSERT_EQ(EPT(18) * EPT(6), EPT(108));
    TEST_ASSERT_EQ(EPT(180) / EPT(17), EPT(10));
    TEST_ASSERT_EQ(EPT(114) % EPT(10), EPT(4));

    // inc/dec
    EPT e1(66);
    TEST_ASSERT_EQ(++e1,EPT(67));
    TEST_ASSERT_EQ(e1,EPT(67));
    TEST_ASSERT_EQ(e1++,EPT(67));
    TEST_ASSERT_EQ(e1,EPT(68));
    TEST_ASSERT_EQ(--e1,EPT(67));
    TEST_ASSERT_EQ(e1,EPT(67));
    TEST_ASSERT_EQ(e1--,EPT(67));
    TEST_ASSERT_EQ(e1,EPT(66));

    // cmp
    e1 = EPT(98);
    EPT e2(97);
    TEST_ASSERT_GT(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    TEST_ASSERT_NE(e1,e2);
    --e1;
    TEST_ASSERT_EQ(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    --e1;
    TEST_ASSERT_LT(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_NE(e1,e2);

    // logic/bit
    // inversion (~) flips high bits too so test it for each type
    TEST_ASSERT_EQ(EPT(0xCC) & EPT(0xF0), EPT(0xC0));
    TEST_ASSERT_EQ(EPT(0xCC) | EPT(0xF0), EPT(0xFC));
    TEST_ASSERT_EQ(EPT(0xCC) ^ EPT(0xF0), EPT(0x3C));

    // compound assign
    e1 = EPT(75);
    TEST_ASSERT_EQ(&(e1 += EPT(18)), &e1);
    TEST_ASSERT_EQ(e1,EPT(93));
    TEST_ASSERT_EQ(&(e1 -= EPT(23)), &e1);
    TEST_ASSERT_EQ(e1,EPT(70));
    TEST_ASSERT_EQ(&(e1 *= EPT(3)), &e1);
    TEST_ASSERT_EQ(e1,EPT(210));
    TEST_ASSERT_EQ(&(e1 /= EPT(16)), &e1);
    TEST_ASSERT_EQ(e1,EPT(13));
    TEST_ASSERT_EQ(&(e1 %= EPT(5)), &e1);
    TEST_ASSERT_EQ(e1,EPT(3));
    e1 = EPT(0x78);
    TEST_ASSERT_EQ(&(e1 &= EPT(0x32)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x30));
    TEST_ASSERT_EQ(&(e1 |= EPT(0x83)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0xB3));
    TEST_ASSERT_EQ(&(e1 ^= EPT(0x84)), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x37));
    TEST_ASSERT_EQ(&(e1 <<= 1), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x6E));
    TEST_ASSERT_EQ(&(e1 >>= 4), &e1);
    TEST_ASSERT_EQ(e1,EPT(0x06));
}

TEST_CASE_CREATE(testUChar)
{
    testUnsigned<unsigned char>();
    testNumber<unsigned char>();

    TEST_ASSERT_EQ(~EPUC(0xF0),EPUC(0x0F));
}

TEST_CASE_CREATE(testUShort)
{
    testUnsigned<unsigned short>();
    testNumber<unsigned short>();

    TEST_ASSERT_EQ(~EPUS(0xF0),EPUS(0xFF0F));
}

TEST_CASE_CREATE(testUInt)
{
    testUnsigned<unsigned int>();
    testNumber<unsigned int>();

    TEST_ASSERT_EQ(~EPUI(0x0FF00000),EPUI(0xF00FFFFF));
}

TEST_CASE_CREATE(testULong)
{
    testUnsigned<unsigned long>();
    testNumber<unsigned long>();

    TEST_ASSERT_EQ(~EPUL(0x1020304050607080),EPUL(0xEFDFCFBFAF9F8F7F));
}

TEST_CASE_CREATE(testULL)
{
    testUnsigned<unsigned long long>();
    testNumber<unsigned long long>();

    TEST_ASSERT_EQ(~EPULL(0x0F0E0D0C0B0A0908),EPULL(0xF0F1F2F3F4F5F6F7));
}

template <typename T>
static constexpr T inf = std::numeric_limits<T>::infinity();

template <typename T>
static constexpr T nan = std::numeric_limits<T>::quiet_NaN();

// floating point tests and static_assert
template <typename T>
    requires tkoz::stl::concepts::isPrimitiveFloatingPoint<T>
void testFloating()
{
    using EPT = EP<T>;

    EPT a = sc<T>(-0.1);
    T b = sc<T>(a);
    TEST_ASSERT_EQ(a,b);
    TEST_ASSERT_EQ(b,a);
    TEST_ASSERT_EQ(a,EPT(-0.1));
    TEST_ASSERT_TRUE(a);
    TEST_ASSERT_FALSE(EPT(0.0));
    a = sc<T>(0.25);
    TEST_ASSERT_EQ(a,EPT(EPF(0.25)));
    TEST_ASSERT_EQ(a,EPT(EPD(0.25)));
    TEST_ASSERT_EQ(a,EPT(EPLD(0.25)));
    TEST_ASSERT_TRUE(EPT(1.0));

    // arithmetic
    TEST_ASSERT_EQ(EPT(0.5) + EPT(1.75), EPT(2.25));
    TEST_ASSERT_EQ(EPT(0.5) - EPT(1.75), EPT(-1.25));
    TEST_ASSERT_EQ(+EPT(-0.9), EPT(-0.9));
    TEST_ASSERT_EQ(-EPT(-0.9), EPT(0.9));
    TEST_ASSERT_EQ(EPT(0.125) * EPT(7.0), EPT(0.875));
    TEST_ASSERT_EQ(EPT(5.0) / EPT(4.0), EPT(1.25));

    // cmp
    EPT e1(-1.1);
    EPT e2(-1.0);
    TEST_ASSERT_LT(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_NE(e1,e2);
    e1 = EPT(-1.0);
    TEST_ASSERT_EQ(e1,e2);
    TEST_ASSERT_LE(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    e1 = EPT(-0.9);
    TEST_ASSERT_GT(e1,e2);
    TEST_ASSERT_GE(e1,e2);
    TEST_ASSERT_NE(e1,e2);

    // compound assign
    e1 = EPT(12.0);
    TEST_ASSERT_EQ(&(e1 += EPT(3.0)), &e1);
    TEST_ASSERT_EQ(e1,EPT(15.0));
    TEST_ASSERT_EQ(&(e1 -= EPT(9.0)), &e1);
    TEST_ASSERT_EQ(e1,EPT(6.0));
    TEST_ASSERT_EQ(&(e1 *= EPT(1.25)), &e1);
    TEST_ASSERT_EQ(e1,EPT(7.5));
    TEST_ASSERT_EQ(&(e1 /= EPT(4.0)), &e1);
    TEST_ASSERT_EQ(e1,EPT(1.875));

    // inf and nan
    TEST_ASSERT_LT(EPT(-inf<T>),EPT());
    TEST_ASSERT_GT(EPT(inf<T>),EPT());
    TEST_ASSERT_EQ(EPT() <=> EPT(nan<T>), std::partial_ordering::unordered);
    TEST_ASSERT_EQ(EPT(nan<T>) <=> EPT(nan<T>), std::partial_ordering::unordered);
}

TEST_CASE_CREATE(testFloat)
{
    testFloating<float>();
    testNumber<float>();
}

TEST_CASE_CREATE(testDouble)
{
    testFloating<double>();
    testNumber<double>();
}

TEST_CASE_CREATE(testLDouble)
{
    testFloating<long double>();
    testNumber<long double>();
}
