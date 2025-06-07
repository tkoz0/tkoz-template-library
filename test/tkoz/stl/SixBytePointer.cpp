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
}
