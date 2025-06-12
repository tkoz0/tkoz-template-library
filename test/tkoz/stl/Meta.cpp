//
// Compile time tests related to metaprogramming utils
//

#include <tkoz/stl/Meta.hpp>

#include <map>
#include <string>
#include <tuple>
#include <vector>

// only checking compile time stuff, does not need to run anything
int main()
{
    using namespace tkoz::stl::meta;
    static_assert(!FalseValue::value);
    static_assert(TrueValue::value);

    // tests for isSame
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
    static_assert(!isSame<const int,int>);
    static_assert(!isSame<volatile int,int>);
    static_assert(!isSame<const volatile int,int>);

    // tests for isArray
    static_assert(!isArray<int>);
    static_assert(isArray<int[]>);
    static_assert(isArray<int[10]>);
    static_assert(!isArray<int*>);

    // tests for isSameAsAny
    static_assert(!isSameAsAny<char,signed char,unsigned char>);
    static_assert(!isSameAsAny<bool>);
    static_assert(isSameAsAny<bool,bool>);
    static_assert(isSameAsAny<bool,void,bool>);
    static_assert(!isSameAsAny<bool,void,void*>);
    static_assert(!isSameAsAny<char,int,int,int>);

    // tests for isTemplated
    static_assert(!isTemplated<void>);
    static_assert(!isTemplated<double>);
    static_assert(isTemplated<std::string>);
    static_assert(isTemplated<std::vector<int>>);
    static_assert(isTemplated<std::map<std::string,std::string>>);
    static_assert(isTemplated<std::tuple<short,int,long>>);

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

    // tests fore RemoveRef
    static_assert(isSame<RemoveRef<bool>,bool>);
    static_assert(isSame<RemoveRef<bool&>,bool>);
    static_assert(isSame<RemoveRef<bool&&>,bool>);
    static_assert(isSame<RemoveRef<void*>,void*>);
    static_assert(isSame<RemoveRef<void*&>,void*>);
    static_assert(isSame<RemoveRef<void*&&>,void*>);

    // tests for RemoveCV
    static_assert(isSame<RemoveCV<float>,float>);
    static_assert(isSame<RemoveCV<const float>,float>);
    static_assert(isSame<RemoveCV<volatile float>,float>);
    static_assert(isSame<RemoveCV<volatile const float>,float>);
    static_assert(isSame<RemoveCV<bool * const volatile>,bool*>);
    static_assert(isSame<RemoveCV<const volatile int&>,int&>);
    static_assert(isSame<RemoveCV<const volatile int&&>,int&&>);

    // tests for RemoveConst
    static_assert(isSame<RemoveConst<const double>,double>);
    static_assert(isSame<RemoveConst<char>,char>);
    static_assert(isSame<RemoveConst<void * const>,void*>);
    static_assert(isSame<RemoveConst<volatile const bool>,volatile bool>);
    static_assert(isSame<RemoveConst<const int&>,int&>);
    static_assert(isSame<RemoveConst<int&>,int&>);
    static_assert(isSame<RemoveConst<volatile const float&&>,volatile float&&>);

    // tests for RemoveVolatile
    static_assert(isSame<RemoveVolatile<volatile long>,long>);
    static_assert(isSame<RemoveVolatile<long long>,long long>);
    static_assert(isSame<RemoveVolatile<int * volatile>,int*>);
    static_assert(isSame<RemoveVolatile<volatile const float>,const float>);
    static_assert(isSame<RemoveVolatile<volatile int&>,int&>);
    static_assert(isSame<RemoveVolatile<int&>,int&>);
    static_assert(isSame<RemoveVolatile<volatile const double&&>,const double&&>);

    // tests for isPointer
    static_assert(isPointer<void*>);
    static_assert(!isPointer<void>);
    static_assert(isPointer<int * const>);
    static_assert(isPointer<long * volatile>);
    static_assert(isPointer<long long * const volatile>);

    // tests for isLVRef
    static_assert(!isLVRef<long>);
    static_assert(isLVRef<long&>);
    static_assert(!isLVRef<long&&>);
    static_assert(isLVRef<const long&>);

    // tests for isRVRef
    static_assert(!isRVRef<short>);
    static_assert(!isRVRef<short&>);
    static_assert(isRVRef<short&&>);
    static_assert(isRVRef<const short&&>);

    // tests for isRef
    static_assert(!isRef<char>);
    static_assert(isRef<char&>);
    static_assert(isRef<char&&>);
    static_assert(!isRef<const char>);

    // tests for isConst
    static_assert(!isConst<int>);
    static_assert(isConst<const int>);
    static_assert(!isConst<volatile int>);
    static_assert(isConst<const int&>);
    static_assert(isConst<const int&&>);
    static_assert(!isConst<int&>);
    static_assert(!isConst<int&&>);

    // tests for isVolatile
    static_assert(!isVolatile<int>);
    static_assert(isVolatile<volatile int>);
    static_assert(!isVolatile<const int>);
    static_assert(!isVolatile<const double&>);
    static_assert(isVolatile<const volatile double&>);
    static_assert(isVolatile<volatile bool&&>);

    // tests for isSigned
    static_assert(isSigned<char>);
    static_assert(isSigned<signed char>);
    static_assert(!isSigned<unsigned char>);
    static_assert(isSigned<const int>);
    static_assert(isSigned<int&>);
    static_assert(isSigned<int&&>);

    // tests for isUnsigned
    static_assert(!isUnsigned<char>);
    static_assert(!isUnsigned<signed char>);
    static_assert(isUnsigned<unsigned char>);
    static_assert(!isUnsigned<const long long&>);
    static_assert(isUnsigned<const volatile unsigned long long&&>);

    // tests for RemoveExtent
    static_assert(isSame<RemoveExtent<int>,int>);
    static_assert(isSame<RemoveExtent<int[]>,int>);
    static_assert(isSame<RemoveExtent<const int[6]>,const int>);
    static_assert(isSame<RemoveExtent<int[5][5]>,int[5]>);
    static_assert(isSame<RemoveExtent<int[18][36][54]>,int[36][54]>);

    // tests for RemoveAllExtents
    static_assert(isSame<RemoveAllExtents<int>,int>);
    static_assert(isSame<RemoveAllExtents<int[]>,int>);
    static_assert(isSame<RemoveAllExtents<const int[6]>,const int>);
    static_assert(isSame<RemoveAllExtents<int[5][5]>,int>);
    static_assert(isSame<RemoveAllExtents<int[18][36][54]>,int>);

    // tests for RemovePointer
    static_assert(isSame<RemovePointer<int>,int>);
    static_assert(isSame<RemovePointer<int*>,int>);
    static_assert(isSame<RemovePointer<int**>,int*>);
    static_assert(isSame<RemovePointer<int * const>,int>);
    static_assert(isSame<RemovePointer<int * const * volatile>,int * const>);
    static_assert(isSame<RemovePointer<int * volatile * const>,int * volatile>);
    static_assert(isSame<RemovePointer<const int***>,const int**>);

    // tests for RemoveAllPointers
    static_assert(isSame<RemoveAllPointers<int>,int>);
    static_assert(isSame<RemoveAllPointers<int*>,int>);
    static_assert(isSame<RemoveAllPointers<int**>,int>);
    static_assert(isSame<RemoveAllPointers<int * const>,int>);
    static_assert(isSame<RemoveAllPointers<int * const * volatile>,int>);
    static_assert(isSame<RemoveAllPointers<int * volatile * const>,int>);
    static_assert(isSame<RemoveAllPointers<const int***>,const int>);

    // tests for EnableIf
    static_assert(isSame<EnableIf<true,long>,long>);
    // substitution error, does not compile
    //static_assert(isSame<EnableIf<false,long>,void>);

    // tests for Conditional
    static_assert(isSame<Conditional<true,char,bool>,char>);
    static_assert(isSame<Conditional<false,char,bool>,bool>);

    // tests for AddLVRef
    static_assert(isSame<AddLVRef<char>,char&>);
    static_assert(isSame<AddLVRef<const bool*>,const bool *&>);
    static_assert(isSame<AddLVRef<long&>,long&>);
    static_assert(isSame<AddLVRef<float&&>,float&>);
    static_assert(isSame<AddLVRef<void>,void>);

    // tests for AddRVRef
    static_assert(isSame<AddRVRef<char>,char&&>);
    static_assert(isSame<AddRVRef<volatile float*>,volatile float*&&>);
    static_assert(isSame<AddRVRef<double&>,double&&>);
    static_assert(isSame<AddRVRef<bool&&>,bool&&>);
    static_assert(isSame<AddRVRef<void>,void>);

    // tests for declVal
    static_assert(isSame<decltype(declVal<long>()),long>);
    static_assert(isSame<decltype(declVal<const bool&>()),const bool&>);
    static_assert(isSame<decltype(declVal<volatile long&&>()),volatile long&&>);

    // tests for CopyRef
    static_assert(isSame<CopyRef<int,int&&>,int>);
    static_assert(isSame<CopyRef<int&&,const double>,const double&&>);
    // note that vector of reference is not allowed
    static_assert(isSame<CopyRef<std::vector<const float&>&,volatile std::string*>,volatile std::string*&>);
    static_assert(isSame<CopyRef<bool&,char&>,char&>);
    static_assert(isSame<CopyRef<long long&,const volatile double>,const volatile double&>);
    static_assert(isSame<CopyRef<const bool&&,volatile int>,volatile int&&>);

    // tests for CopyConst
    static_assert(isSame<CopyConst<int,volatile float>,volatile float>);
    static_assert(isSame<CopyConst<int,const volatile double>,volatile double>);
    static_assert(isSame<CopyConst<const int,const bool>,const bool>);
    static_assert(isSame<CopyConst<const std::string&,int&>,const int&>);
    static_assert(isSame<CopyConst<std::string&,int&>,int&>);
    static_assert(isSame<CopyConst<const double&&,const double>,const double>);
    static_assert(isSame<CopyConst<double&&,const double>,double>);

    // tests for CopyVolatile
    static_assert(isSame<CopyVolatile<int,float>,float>);
    static_assert(isSame<CopyVolatile<volatile int,float>,volatile float>);
    static_assert(isSame<CopyVolatile<const int,float>,float>);
    static_assert(isSame<CopyVolatile<volatile double&,short&&>,volatile short&&>);
    static_assert(isSame<CopyVolatile<const volatile long,volatile int>,volatile int>);
    static_assert(isSame<CopyVolatile<bool,const volatile int>,const int>);

    // tests for CopyCV
    static_assert(isSame<CopyCV<double,int>,int>);
    static_assert(isSame<CopyCV<volatile double&,int&&>,volatile int&&>);
    static_assert(isSame<CopyCV<double,const int&>,int&>);
    static_assert(isSame<CopyCV<const volatile bool&&,volatile float>,const volatile float>);

    // tests for CopyCVRef
    static_assert(isSame<CopyCVRef<volatile int&&,const bool>,volatile bool&&>);
    static_assert(isSame<CopyCVRef<const double&,const char>,const char&>);
    static_assert(isSame<CopyCVRef<int,const volatile float&&>,float>);
}
