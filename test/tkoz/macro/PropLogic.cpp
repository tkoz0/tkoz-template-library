///
/// tests for IFF macro
///

#include <tkoz/Test.hpp>

#include <tkoz/stl/Meta.hpp>

#include <tkoz/macro/PropLogic.hpp>

TEST_RUNNER_MAIN

TEST_CASE_CREATE(testIff)
{
    bool a = true;
    bool b = true;
    static_assert(tkoz::stl::meta::isSame<decltype(a IFF b),bool>);

    TEST_ASSERT_TRUE((a IFF b));
    a = true; b = false;
    TEST_ASSERT_FALSE((a IFF b));
    a = false; b = true;
    TEST_ASSERT_FALSE((a IFF b));
    a = false; b = false;
    TEST_ASSERT_TRUE((a IFF b));

    TEST_ASSERT_TRUE((3 IFF 3.1));
    TEST_ASSERT_FALSE(('a' IFF 0));
    TEST_ASSERT_TRUE((0 IFF '\0'));
    TEST_ASSERT_FALSE((-1 IFF -0.0));
}

TEST_CASE_CREATE(testThen)
{
    bool a = true;
    bool b = true;
    static_assert(tkoz::stl::meta::isSame<decltype(a THEN b),bool>);

    TEST_ASSERT_TRUE((a THEN b));
    a = true; b = false;
    TEST_ASSERT_FALSE((a THEN b));
    a = false; b = true;
    TEST_ASSERT_TRUE((a THEN b));
    a = false; b = false;
    TEST_ASSERT_TRUE((a THEN b));

    TEST_ASSERT_TRUE((3 THEN 1));
    TEST_ASSERT_FALSE((7.5 THEN 0.0));
}

TEST_CASE_CREATE(testIf)
{
    bool a = true;
    bool b = true;
    static_assert(tkoz::stl::meta::isSame<decltype(a IF b),bool>);

    TEST_ASSERT_TRUE((a IF b));
    a = true; b = false;
    TEST_ASSERT_TRUE((a IF b));
    a = false; b = true;
    TEST_ASSERT_FALSE((a IF b));
    a = false; b = false;
    TEST_ASSERT_TRUE((a IF b));

    TEST_ASSERT_TRUE((5 IF '\0'));
    TEST_ASSERT_FALSE(('\0' IF -2));
}
