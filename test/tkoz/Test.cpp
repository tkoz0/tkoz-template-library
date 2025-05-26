#include <tkoz/Test.hpp>

TEST_RUNNER_MAIN

TEST_CASE_CREATE(unitTest1)
{
    int a = 5;
    int b = 10;
    int c = 15;
    TEST_INFO("set a = " << a << " and b = " << b);
    TEST_WARN("(ignore this) example warning message");
    TEST_FAIL("(ignore this) example failure message");
    TEST_ASSERT(a+b == c);
    TEST_ASSERT_MSG(a-b == -5, "subtract to negative");
    //TEST_ASSERT(a*b == 10); // this assert fails
    //TEST_ASSERT_MSG(a*b == 20, "a times b is not equal to twenty"); // fails
}

TEST_CASE_CREATE(unitTest2)
{
    const char *c = "abc";
    // check characters
    TEST_ASSERT(c[0] == 0x61);
    TEST_ASSERT(c[1] == 0x62);
    TEST_ASSERT(c[2] == 0x63);
    TEST_ASSERT_MSG(c[3] == 0x00, "did not find null where expected");
    //TEST_ASSERT(c[4] == 0x00); // undefined behavior
}

TEST_CASE_CREATE(unitTest3)
{
    static const int n = 10;
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += i;
    }
    TEST_ASSERT(sum == (n-1)*n/2);
}

TEST_CASE_CREATE(unitTest4)
{
    TEST_ASSERT(1);
    TEST_ASSERT_MSG(2, "assert failed");
    TEST_ASSERT_TRUE(3);
    TEST_ASSERT_TRUE_MSG(4, "true assert failed");
    TEST_ASSERT_FALSE(3-3);
    TEST_ASSERT_FALSE_MSG(5-5, "false assert failed");
    TEST_ASSERT_EQ(10+5,15);
    TEST_ASSERT_EQ_MSG(1+1,2, "equal assert failed");
    TEST_ASSERT_NE(10+5,25);
    TEST_ASSERT_NE_MSG(1+1+1,2, "nonequal assert failed");
    TEST_ASSERT_LT(1,2);
    TEST_ASSERT_LT_MSG(1,2, "less than assert failed");
    TEST_ASSERT_GT(2,1);
    TEST_ASSERT_GT_MSG(2,1, "greater than assert failed");
    TEST_ASSERT_LE(2,2);
    TEST_ASSERT_LE_MSG(1,2, "less than or equal to assert failed");
    TEST_ASSERT_GE(2,2);
    TEST_ASSERT_GE_MSG(2,1, "greater than or equal to assert failed");
    TEST_ASSERT_CLOSE_ABS(1.04,1.0,0.05);
    TEST_ASSERT_CLOSE_ABS_MSG(1.0,1.04,0.05, "close absolute error");
    TEST_ASSERT_CLOSE_REL(0.1009,0.1,0.01);
    TEST_ASSERT_CLOSE_REL_MSG(0.1009,0.1,0.01, "close relative error");
}

TEST_CASE_CREATE(unitTest5)
{
    TEST_EXCEPTION(throw 5,int);
    //TEST_EXCEPTION(void(5);,int); // no exception
    TEST_EXCEPTION_MSG(throw'a',char,
        "should throw exception but does not",
        "throws but wrong exception type");
}

TEST_CASE_CREATE(unitTestEmpty)
{
}

TEST_CASE_CREATE(unitTestFail)
{
    TEST_ASSERT(0);
}

TEST_CASE_CREATE(unitTestThrow)
{
    throw 0;
}

TEST_CASE_CREATE(unitTestExtra)
{
}
