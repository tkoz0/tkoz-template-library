//
// Unit tests for 6 byte pointer
//

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/SixBytePointer.hpp>

#include <tkoz/Test.hpp>

#include <string>
#include <vector>

TEST_RUNNER_MAIN

using tkoz::stl::SixBytePointer;
template <typename T>
using SBP = tkoz::stl::SixBytePointer<T>;
namespace meta = tkoz::stl::meta;
namespace concepts = tkoz::stl::concepts;

static_assert(sizeof(SixBytePointer<void>) == 6);
static_assert(sizeof(SixBytePointer<bool>) == 6);
static_assert(sizeof(SixBytePointer<long>) == 6);
static_assert(sizeof(SixBytePointer<std::string>) == 6);

// must align to 2 bytes to get the memory saving benefit
// we would just use regular 8 byte pointers if they were padded to 8

static_assert(alignof(SixBytePointer<void>) == 2);
static_assert(alignof(SixBytePointer<bool>) == 2);
static_assert(alignof(SixBytePointer<long>) == 2);
static_assert(alignof(SixBytePointer<std::string>) == 2);

// check if a value of type T can be converted to type P
template <typename P, typename T>
consteval bool canConstruct()
{
    return requires { P(meta::declVal<T>()); };
}

// check if a value of type T can be dereferenced
template <typename T>
consteval bool canDeref()
{
    return requires { *meta::declVal<T>(); };
}

TEST_CASE_CREATE(testCtor)
{
    SBP<char> p1;
    TEST_ASSERT_EQ(p1.ptr(),nullptr);
    bool b1;
    SBP<bool> p0(&b1);
    char c1;

    // cannot convert other types to SBP<bool>
    static_assert(!canConstruct<SBP<bool>,int*>());
    static_assert(!canConstruct<SBP<bool>,unsigned int*>());
    static_assert(!canConstruct<SBP<bool>,long long*>());
    static_assert(!canConstruct<SBP<bool>,unsigned long long*>());
    static_assert(!canConstruct<SBP<bool>,long long>());
    static_assert(!canConstruct<SBP<bool>,unsigned long long>());
    static_assert(!canConstruct<SBP<bool>,bool>());
    // only same type* and nullptr_t
    static_assert(canConstruct<SBP<bool>,bool*>());
    static_assert(canConstruct<SBP<bool>,std::nullptr_t>());
    static_assert(canConstruct<SBP<char>,std::nullptr_t>());
    // from pointer to local variable of matching type
    static_assert(!canConstruct<SBP<bool>,decltype(&c1)>());
    static_assert(canConstruct<SBP<bool>,decltype(&b1)>());
    static_assert(canConstruct<SBP<char>,decltype(&c1)>());

    // string pointer
    std::string s = "abcde";
    SBP<std::string> p2(&s);
    TEST_ASSERT_EQ(p2.ptr(),&s);
    static_assert(meta::isSame<decltype(p2.ptr()),std::string*>);
    static_assert(canDeref<SBP<std::string>>());

    SBP<std::string> p3(p2);
    TEST_ASSERT_EQ(p2.ptr(),p3.ptr());
    p3 = p2;
    TEST_ASSERT_EQ(p2.ptr(),p3.ptr());

    SBP<void> n1;
    static_assert(canConstruct<SBP<void>,std::nullptr_t>());
    static_assert(canConstruct<SBP<void>,decltype(&b1)>());
    static_assert(canConstruct<SBP<void>,decltype(&c1)>());
    TEST_ASSERT_EQ(n1.ptr(),nullptr);
    SBP<void> n2(&c1);
    TEST_ASSERT_EQ(n2.ptr(),&c1);
    static_assert(meta::isSame<decltype(n2.ptr()),void*>);
    // cannot dereference
    //*n2;
}

TEST_CASE_CREATE(testPtr)
{
    SBP<double> p1;
    SBP<double>& r1 = p1;
    const SBP<double>& r2 = r1;
    static_assert(tkoz::stl::meta::isSame<decltype(r1.ptr()),double*>);
    static_assert(tkoz::stl::meta::isSame<decltype(r2.ptr()),double*>);
    double d;
    p1 = &d;
    TEST_ASSERT_EQ(p1.ptr(),&d);
    p1 = nullptr;
    TEST_ASSERT_EQ(p1.ptr(),nullptr);
}

TEST_CASE_CREATE(testDeref)
{
    static_assert(canDeref<SBP<char>>()
        && meta::isSame<decltype(*meta::declVal<SBP<char>>()),char&>);
    static_assert(canDeref<SBP<bool>>()
        && meta::isSame<decltype(*meta::declVal<SBP<bool>>()),bool&>);
    // void is not dereferenceable
    static_assert(!canDeref<SBP<void>>());
    SBP<double> p1;
    double d1 = -7.3;
    p1 = &d1;
    TEST_ASSERT_EQ(*p1,d1);
    TEST_ASSERT_EQ(-7.3,*p1);
}

TEST_CASE_CREATE(testMember)
{
    SBP<std::string> p1;
    TEST_ASSERT_EQ(p1,nullptr);
    std::string s1;
    p1 = &s1;
    std::string s2 = "abcdef";
    SBP<std::string> p2 = &s2;
    TEST_ASSERT_EQ(p2.ptr(),&s2);
    TEST_ASSERT_EQ(&s2,p2.ptr());
    TEST_ASSERT_EQ(p1->size(),0);
    TEST_ASSERT_EQ(p2->size(),6);
    TEST_ASSERT_TRUE(p2->contains("abc"));
    TEST_ASSERT_EQ(p2->substr(3),"def");
    p2->operator[](0) = 'z';
    TEST_ASSERT_EQ(*p2,"zbcdef");
    TEST_ASSERT_TRUE(p1->c_str());
}

TEST_CASE_CREATE(testBool)
{
    SBP<unsigned int> p1;
    TEST_ASSERT_FALSE(static_cast<bool>(p1));
    SBP<SBP<unsigned int>> p2(&p1);
    TEST_ASSERT_TRUE(static_cast<bool>(p2));
    TEST_ASSERT_FALSE(p1);
    TEST_ASSERT_TRUE(p2);
}

TEST_CASE_CREATE(testCastPtr) // to T*
{
    float f1 = 1.9f;
    SBP<float> pf = &f1;
    const float *f2 = pf.ptr();
    TEST_ASSERT_EQ(*f2,1.9f);
    TEST_ASSERT_EQ(&f1,const_cast<float*>(f2));

    double d1 = 0.0;
    SBP<double> pd = &d1;
    const double *d2 = pd.ptr();
    TEST_ASSERT_EQ(*d2,0.0);
    TEST_ASSERT_EQ(&d1,const_cast<double*>(d2));

    static_assert(!concepts::canAssign<SBP<float>,SBP<double>>);
    static_assert(!concepts::canAssign<SBP<float>,SBP<const float>>);
    static_assert(concepts::canAssign<SBP<double>,SBP<double>>);
    static_assert(concepts::canAssign<float*,SBP<float>>);
    static_assert(!concepts::canAssign<float*,SBP<const float>>);
    static_assert(!concepts::canAssign<float*,SBP<double>>);
}

TEST_CASE_CREATE(testCast6bp) // to SBP<T>
{
    // convert/assign with same type is allowed
    static_assert(concepts::canConvert<SBP<long>,SBP<long>>);
    static_assert(concepts::canAssign<SBP<long>,SBP<long>>);
    static_assert(concepts::canConvert<SBP<int>,SBP<int>>);
    static_assert(concepts::canAssign<SBP<int>,SBP<int>>);
    // types are different but conversion is explicit
    static_assert(canConstruct<SBP<int>,SBP<long>>());
    static_assert(canConstruct<SBP<long>,SBP<int>>());
    static_assert(concepts::canConvert<SBP<int>,SBP<long>>);
    static_assert(concepts::canConvert<SBP<long>,SBP<int>>);
    // implicit conversion with different types not allowed
    static_assert(!concepts::canAssign<SBP<long>,SBP<int>>);
    static_assert(!concepts::canAssign<SBP<int>,SBP<long>>);
    static_assert(!concepts::canAssign<SBP<const int>,SBP<int>>);
    static_assert(!concepts::canAssign<SBP<int>,SBP<const int>>);

    int i1 = 65537;
    SBP<int> p0(&i1);
    SBP<long> pa(p0);
    SBP<long> pb = static_cast<SBP<long>>(SBP<int>());
    static_cast<void>(pa);
    static_cast<void>(pb);

    long l1 = 65537;
    SBP<long> p1(&l1);
    SBP<long> p2 = p1;
    //SBP<int> p3(p1);
    TEST_ASSERT_EQ(p1.ptr(),p2.ptr());
    SBP<const long> p3 = static_cast<SBP<const long>>(p2);
    TEST_ASSERT_EQ(p1.ptr(),const_cast<long*>(p3.ptr()));
}

TEST_CASE_CREATE(testCmp)
{
    bool b[3] = {false,true,false};
    SBP<bool> p0(b+0), p1(b+1), p2(b+2);
    TEST_ASSERT_LT(p0,p1);
    TEST_ASSERT_LT(p0,p2);
    TEST_ASSERT_LT(p1,p2);
    TEST_ASSERT_LE(p0,p0);
    TEST_ASSERT_LE(p0,p1);
    TEST_ASSERT_LE(p0,p2);
    TEST_ASSERT_LE(p1,p1);
    TEST_ASSERT_LE(p1,p2);
    TEST_ASSERT_LE(p2,p2);
    TEST_ASSERT_EQ(p0,p0);
    TEST_ASSERT_EQ(p1,p1);
    TEST_ASSERT_EQ(p2,p2);
    TEST_ASSERT_GT(p1,p0);
    TEST_ASSERT_GT(p2,p0);
    TEST_ASSERT_GT(p2,p1);
    TEST_ASSERT_GE(p0,p0);
    TEST_ASSERT_GE(p1,p0);
    TEST_ASSERT_GE(p2,p0);
    TEST_ASSERT_GE(p1,p1);
    TEST_ASSERT_GE(p2,p1);
    TEST_ASSERT_GE(p2,p2);
    TEST_ASSERT_NE(p0,p1);
    TEST_ASSERT_NE(p0,p2);
    TEST_ASSERT_NE(p1,p0);
    TEST_ASSERT_NE(p1,p2);
    TEST_ASSERT_NE(p2,p0);
    TEST_ASSERT_NE(p2,p1);

    double d[6] = {-3.14,-2.72,-0.58,1.41,1.73,2.24};
    SBP<double> q0(d+1), q1(d+3), q2(d+5);
    TEST_ASSERT_LT(q0,q1);
    TEST_ASSERT_LT(q0,q2);
    TEST_ASSERT_LT(q1,q2);
    TEST_ASSERT_LE(q0,q0);
    TEST_ASSERT_LE(q0,q1);
    TEST_ASSERT_LE(q0,q2);
    TEST_ASSERT_LE(q1,q1);
    TEST_ASSERT_LE(q1,q2);
    TEST_ASSERT_LE(q2,q2);
    TEST_ASSERT_EQ(q0,q0);
    TEST_ASSERT_EQ(q1,q1);
    TEST_ASSERT_EQ(q2,q2);
    TEST_ASSERT_GT(q1,q0);
    TEST_ASSERT_GT(q2,q0);
    TEST_ASSERT_GT(q2,q1);
    TEST_ASSERT_GE(q0,q0);
    TEST_ASSERT_GE(q1,q0);
    TEST_ASSERT_GE(q2,q0);
    TEST_ASSERT_GE(q1,q1);
    TEST_ASSERT_GE(q2,q1);
    TEST_ASSERT_GE(q2,q2);
    TEST_ASSERT_NE(q0,q1);
    TEST_ASSERT_NE(q0,q2);
    TEST_ASSERT_NE(q1,q0);
    TEST_ASSERT_NE(q1,q2);
    TEST_ASSERT_NE(q2,q0);
    TEST_ASSERT_NE(q2,q1);

    static_assert(concepts::canCmp3wayStrong<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpEq<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpNe<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpLt<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpLe<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpGt<SBP<int>,SBP<int>>);
    static_assert(concepts::canCmpGe<SBP<int>,SBP<int>>);
}

TEST_CASE_CREATE(testAddSub)
{
    int ints[50];
    TEST_ASSERT_EQ(SBP<int>(ints+5) + 10, SBP<int>(ints+15));
    TEST_ASSERT_EQ(SBP<int>(ints+12) - 6, SBP<int>(ints+6));
    TEST_ASSERT_EQ(SBP<int>(ints+40) + (-13), SBP<int>(ints+27));
    TEST_ASSERT_EQ(SBP<int>(ints+10) - (-12), SBP<int>(ints+22));
    SBP<int> a = ints;
    TEST_ASSERT_EQ(a,ints);
    a += 10;
    TEST_ASSERT_EQ(a,ints+10);
    a += 14;
    TEST_ASSERT_EQ(a,ints+24);
    a += 25;
    TEST_ASSERT_EQ(a,ints+49);

    std::vector<std::string> vecs[20];
    using SBPV = SBP<std::vector<std::string>>;
    TEST_ASSERT_EQ(SBPV(vecs+15) - 1, SBPV(vecs+14));
    TEST_ASSERT_EQ(SBPV(vecs+12) - 4, SBPV(vecs+8));
    TEST_ASSERT_EQ(SBPV(vecs+18) + 1, SBPV(vecs+19));
    TEST_ASSERT_EQ(SBPV(vecs+3) + 6, SBPV(vecs+9));
    SBP<std::vector<std::string>> b = vecs;
    TEST_ASSERT_EQ(b,vecs);
    b += 3;
    TEST_ASSERT_EQ(b,vecs+3);
    b += 7;
    TEST_ASSERT_EQ(b,vecs+10);
}

TEST_CASE_CREATE(testSubscript)
{
    float fs[11] = {1.1,2.2,3,3,-2,-4,-6,10,-10,3.14,-3.14};
    SBP<float> fp = fs;
    TEST_ASSERT_EQ(fp[0],1.1f);
    TEST_ASSERT_EQ(fp[1],2.2f);
    TEST_ASSERT_EQ(fp[10],-3.14f);
    fp[0] = -2.1;
    fp[1] = -4.1;
    TEST_ASSERT_EQ(fp[0],-2.1f);
    TEST_ASSERT_EQ(fp[1],-4.1f);
    fp += 10;
    TEST_ASSERT_EQ(fp[0],-3.14f);

    bool bs[3] = {false,true,false};
    SBP<bool> bp = bs;
    TEST_ASSERT_FALSE(bp[0]);
    TEST_ASSERT_TRUE(bp[1]);
    TEST_ASSERT_FALSE(bp[2]);
}

TEST_CASE_CREATE(testIncDec)
{
    long arr[100];
    SBP<long> p1 = arr;
    TEST_ASSERT_EQ(p1++,arr);
    TEST_ASSERT_EQ(p1,arr+1);
    TEST_ASSERT_EQ(++p1,arr+2);
    TEST_ASSERT_EQ(p1,arr+2);

    unsigned int arr2[100];
    SBP<unsigned int> p2 = arr2+80;
    TEST_ASSERT_EQ(p2--,arr2+80);
    TEST_ASSERT_EQ(p2,arr2+79);
    TEST_ASSERT_EQ(--p2,arr2+78);
    TEST_ASSERT_EQ(p2,arr2+78);
}

TEST_CASE_CREATE(testToIntFromInt)
{
    using tkoz::stl::uintptr_t;
    using tkoz::stl::sintptr_t;
    bool arr[200];
    SBP<bool> p1 = arr;
    uintptr_t u1 = p1.toUInt();
    sintptr_t s1 = p1.toSInt();
    TEST_ASSERT_EQ(u1,reinterpret_cast<uintptr_t>(arr));
    TEST_ASSERT_EQ(s1,reinterpret_cast<sintptr_t>(arr));
    u1 += 50u;
    s1 += 100;
    TEST_ASSERT_EQ(SBP<bool>::fromInt(u1),arr+50u);
    TEST_ASSERT_EQ(SBP<bool>::fromInt(s1),arr+100u);

    double arr2[100];
    SBP<double> p2 = arr2;
    uintptr_t u2 = p2.toUInt();
    sintptr_t s2 = p2.toSInt();
    TEST_ASSERT_EQ(SBP<double>::fromInt(u2),arr2);
    TEST_ASSERT_EQ(SBP<double>::fromInt(s2),arr2);
    TEST_ASSERT_EQ(SBP<double>::fromInt(u2+80),arr2+10);
    TEST_ASSERT_EQ(SBP<double>::fromInt(s2+160),arr2+20);
    u2 += 27;
    s2 += 42;
    // intptr values are no longer 8 byte aligned
    TEST_ASSERT_GT(SBP<double>::fromInt(u2),arr2+3);
    TEST_ASSERT_LT(SBP<double>::fromInt(u2),arr2+4);
    TEST_ASSERT_GT(SBP<double>::fromInt(s2),arr2+5);
    TEST_ASSERT_LT(SBP<double>::fromInt(s2),arr2+6);
}
