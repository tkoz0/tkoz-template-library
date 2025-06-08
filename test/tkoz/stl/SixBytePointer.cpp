//
// Unit tests for 6 byte pointer
//

#include <tkoz/stl/SixBytePointer.hpp>

#include <tkoz/Test.hpp>

#include <string>

TEST_RUNNER_MAIN

using tkoz::stl::SixBytePointer;

static_assert(sizeof(SixBytePointer<void>) == 6);
static_assert(sizeof(SixBytePointer<bool>) == 6);
static_assert(sizeof(SixBytePointer<long>) == 6);
static_assert(sizeof(SixBytePointer<std::string>) == 6);
static_assert(alignof(SixBytePointer<void>) == 2);
static_assert(alignof(SixBytePointer<bool>) == 2);
static_assert(alignof(SixBytePointer<long>) == 2);
static_assert(alignof(SixBytePointer<std::string>) == 2);

TEST_CASE_CREATE(test)
{
    int a = 5;
    SixBytePointer<int> p(&a);
    TEST_ASSERT_EQ(&a,p.ptr());
    *p = 6;
    TEST_ASSERT_EQ(a,6);
    TEST_ASSERT_TRUE(p);
    p = nullptr;
    TEST_ASSERT_FALSE(p);

    std::string s = "string";
    SixBytePointer<std::string> sp(&s);
    TEST_ASSERT_EQ(&s,sp.ptr());
    *sp += "string";
    TEST_ASSERT_EQ(s,"stringstring");
    TEST_ASSERT_TRUE(sp);

    const SixBytePointer<std::string> &csp = sp;
    TEST_ASSERT_EQ(csp->size(),12);
    TEST_ASSERT_EQ(*csp,"stringstring");

    char c[3];
    SixBytePointer p1(c+0), p2(c+1), p3(c+2);
    TEST_ASSERT_EQ(p1,p1);
    TEST_ASSERT_EQ(p2,p2);
    TEST_ASSERT_EQ(p3,p3);
    TEST_ASSERT_LE(p1,p1);
    TEST_ASSERT_GE(p1,p1);
    TEST_ASSERT_NE(p1,p3);
    TEST_ASSERT_LT(p1,p2);
    TEST_ASSERT_GT(p3,p2);
    TEST_ASSERT_LE(p1,p3);
    TEST_ASSERT_GE(p3,p1);

    long d[30];
    SixBytePointer dp(d);
    TEST_ASSERT_EQ(dp+0,d);
    TEST_ASSERT_EQ(dp-0,d);
    TEST_ASSERT_EQ(dp+15,d+15);
    long *d2 = d + 20;
    SixBytePointer dp2(d2);
    TEST_ASSERT_EQ(dp2-10,dp+10);

    TEST_ASSERT_EQ(dp++,d);
    TEST_ASSERT_EQ(dp,d+1);
    TEST_ASSERT_EQ(++dp,d+2);
    TEST_ASSERT_EQ(dp,d+2);
    TEST_ASSERT_EQ(--dp,d+1);
    TEST_ASSERT_EQ(dp,d+1);
    TEST_ASSERT_EQ(dp--,d+1);
    TEST_ASSERT_EQ(dp,d);
}
