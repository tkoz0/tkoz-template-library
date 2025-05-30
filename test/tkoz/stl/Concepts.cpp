//
// Compile time tests for concepts
//

#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/Meta.hpp>

#include <string>

// the following template/macro stuff is for checking a concept applies
// (or does not apply) to a variable list of types
// these check some concepts in tkoz::stl::concepts
// concepts cannot be passed as template parameters in C++ for now

// check parameter pack is all true
template <bool ...values>
static constexpr bool packAllTrue = (true && ... && values);
static_assert(packAllTrue<true,true,true,true>);
static_assert(!packAllTrue<true,true,false,true>);

// check parameter pack is all false
template <bool ...values>
static constexpr bool packAllFalse = !(false || ... || values);
static_assert(packAllFalse<false,false,false,false>);
static_assert(!packAllFalse<false,true,false,false>);

// check for a concept in tkoz::stl::concepts
// requires it is true for all types in __VA_ARGS__
#define CHECK_ALL_TRUE(cppConcept,...) \
template <typename ...Ts> \
concept _check_all_true_##cppConcept = requires (Ts ...ts) \
{ typename tkoz::stl::meta::EnableIf< \
    packAllTrue<tkoz::stl::concepts::cppConcept<decltype(ts)>...>,void>; }; \
static_assert(_check_all_true_##cppConcept<__VA_ARGS__>)

// check for a concept in tkoz::stl::concepts
// requires it is false for all types in __VA_ARGS__
#define CHECK_ALL_FALSE(cppConcept,...) \
template <typename ...Ts> \
concept _check_all_false_##cppConcept = requires (Ts ...ts) \
{ typename tkoz::stl::meta::EnableIf< \
    packAllFalse<tkoz::stl::concepts::cppConcept<decltype(ts)>...>,void>; }; \
static_assert(_check_all_false_##cppConcept<__VA_ARGS__>)

// all numbers at least 4 bytes should support arithmetic with itself
// such that the result is the same type, no implicit conversion occurs
// operations involving char/short are implicitly converted up to int
// if the types sizes differ, result is promoted to the larger type
// if unsigned is involved with same size types
//   then result is implicitly "promoted" to unsigned
#define INTS(sign) sign int, sign long, sign long long
#define SINTS INTS(signed)
#define UINTS INTS(unsigned)
#define ALL_INTS SINTS, UINTS
#define FLOATS float, double, long double
#define ALL_NUMS ALL_INTS, FLOATS
#define ALL_PRIMS bool, char, ALL_NUMS

CHECK_ALL_TRUE(canAddSame,ALL_NUMS);
CHECK_ALL_TRUE(canSubSame,ALL_NUMS);
CHECK_ALL_TRUE(canPosSame,ALL_NUMS);
CHECK_ALL_TRUE(canNegSame,ALL_NUMS);
CHECK_ALL_TRUE(canMulSame,ALL_NUMS);
CHECK_ALL_TRUE(canDivSame,ALL_NUMS);
CHECK_ALL_TRUE(canModSame,ALL_INTS); // mod not supported for floats
CHECK_ALL_FALSE(canModSame,FLOATS);
CHECK_ALL_TRUE(canPreInc,ALL_NUMS); // inc/dec does work on floats
CHECK_ALL_TRUE(canPostInc,ALL_NUMS);
CHECK_ALL_TRUE(canPreDec,ALL_NUMS);
CHECK_ALL_TRUE(canPostDec,ALL_NUMS);

// only compile time tests needed, not running anything
int main()
{
    using namespace tkoz::stl::concepts;
    namespace meta = tkoz::stl::meta;

    // isVoid
    static_assert(isVoid<void>);
    static_assert(!isVoid<void*>);
    static_assert(!isVoid<bool>);

    // isBool
    static_assert(isBool<bool>);
    static_assert(!isBool<int>);

    // isPrimitiveFloatingPoint
    static_assert(isPrimitiveFloatingPoint<float>);
    static_assert(isPrimitiveFloatingPoint<double>);
    static_assert(isPrimitiveFloatingPoint<long double>);
    static_assert(!isPrimitiveFloatingPoint<long>);

    // isAnyChar
    static_assert(isAnyChar<char>);
    static_assert(isAnyChar<signed char>);
    static_assert(isAnyChar<unsigned char>);
    static_assert(!isAnyChar<void>);
    static_assert(!isAnyChar<bool>);

    // isPrimitiveSignedInteger
    static_assert(isPrimitiveSignedInteger<signed char>);
    static_assert(isPrimitiveSignedInteger<short>);
    static_assert(isPrimitiveSignedInteger<int>);
    static_assert(isPrimitiveSignedInteger<long>);
    static_assert(isPrimitiveSignedInteger<long long>);
    static_assert(!isPrimitiveSignedInteger<unsigned int>);
    static_assert(!isPrimitiveSignedInteger<bool>);

    // isPrimitiveUnsignedInteger
    static_assert(isPrimitiveUnsignedInteger<unsigned char>);
    static_assert(isPrimitiveUnsignedInteger<unsigned short>);
    static_assert(isPrimitiveUnsignedInteger<unsigned int>);
    static_assert(isPrimitiveUnsignedInteger<unsigned long>);
    static_assert(isPrimitiveUnsignedInteger<unsigned long long>);
    static_assert(!isPrimitiveUnsignedInteger<int>);
    static_assert(!isPrimitiveUnsignedInteger<bool>);

    // canConvert
    static_assert(canConvert<long,long>);
    static_assert(canConvert<int,bool>);
    static_assert(canConvert<int&&,float&&>);
    static_assert(canConvert<double&,float>);
    static_assert(canConvert<double,float>);
    static_assert(canConvert<float,bool>);
    static_assert(!canConvert<bool,std::string>);
    static_assert(!canConvert<std::string,float>);

    // canStaticCast
    static_assert(canStaticCast<bool,float>);
    static_assert(canStaticCast<double,float>);
    static_assert(canStaticCast<float,double>);
    static_assert(!canStaticCast<std::string,bool>);
    static_assert(!canStaticCast<long,std::string>);

    // canDynamicCast
    class CA { public: virtual ~CA(); };
    class CB: public CA {};
    static_assert(canDynamicCast<CA*,CA*>);
    static_assert(canDynamicCast<CB*,CB*>);
    static_assert(canDynamicCast<CA*,CB*>);
    static_assert(canDynamicCast<CB*,CA*>);
    static_assert(!canDynamicCast<bool*,void*>);

    // canConstCast
    static_assert(canConstCast<const long*,long*>);
    static_assert(canConstCast<float*,const float*>);
    static_assert(!canConstCast<float*,double*>);
    static_assert(!canConstCast<float*,const double*>);
    static_assert(!canConstCast<bool,int>);
    static_assert(canConstCast<float&,const float&>);

    // canReinterpretCast
    static_assert(canReinterpretCast<unsigned long,void*>);
    static_assert(canReinterpretCast<void**,signed long>);
    static_assert(canReinterpretCast<void*,char**>);
    static_assert(!canReinterpretCast<bool,int>);
    static_assert(canReinterpretCast<float***,bool*>);
    static_assert(canReinterpretCast<signed long,char[4]>);
    static_assert(canReinterpretCast<double*,float[8]>);

    // canAssign
    static_assert(canAssign<int,int>);
    static_assert(canAssign<int,bool>);
    static_assert(canAssign<bool,int>);
    static_assert(canAssign<float&,double&&>);
    static_assert(canAssign<double&,float&&>);
    static_assert(canAssign<short&&,char>);
    static_assert(canAssign<std::string,char*>);
    static_assert(!canAssign<float,std::string>);
    static_assert(!canAssign<char,std::string>);
}
