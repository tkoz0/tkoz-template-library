///
/// unit test macros
///

#pragma once

#include <tkoz/cli/AnsiEscape.hpp>
#include <tkoz/cli/Exit.hpp>
#include <tkoz/stl/Meta.hpp>

// GCC/Clang for __cxa_current_exception_type and __cxa_demangle
#include <cxxabi.h>

// TODO replace with tkoz::stl types of some sort
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

//
// tkoz::test namespace with unit test runner information
//

// data for handling unit test runner
// TODO change data types to tkoz::stl
namespace tkoz::test
{

// exception for assertion failure
struct assert_fail_t {};

/// count tests that have been run
static int num_tests_run = 0;

/// count tests which have passed
static int num_tests_passed = 0;

/// count tests which have failed
static int num_tests_failed = 0;

/// type of time measurement
using time_type = decltype(::std::chrono::high_resolution_clock::now()
                          -::std::chrono::high_resolution_clock::now());
static_assert(tkoz::stl::meta::isSame<time_type,
    ::std::chrono::duration<::std::int64_t,::std::nano>>);

/// total time taken
static time_type total_time;

/// array of pointers to test functions
static ::std::vector<::std::pair<std::string,void(*)()>> test_funcs;

/// add a test pointer
/// use to initialize dummy static variables so this runs before main()
static inline void* add_test_func(const char *name, void (*ptr)())
{
    test_funcs.emplace_back(name,ptr);
    return nullptr;
}

/// possible actions to use when failure occurs
enum fail_action
{
    assert_fail_terminate, // terminate program
    assert_fail_continue // keep running the same test
};

/// what to do when an assertion fails
fail_action assert_fail_action = assert_fail_continue;

/// print a time (milliseconds, microseconds, nanoseconds)
void print_time(time_type t)
{
    using ::std::chrono::duration_cast;
    using ::std::chrono::nanoseconds;
    using ::std::chrono::microseconds;
    using ::std::chrono::milliseconds;
    ::std::cerr << "( " << duration_cast<milliseconds>(t) << " / "
                        << duration_cast<microseconds>(t) << " / "
                        << duration_cast<nanoseconds>(t)  << " )";
}

/// print overall test statistics
void print_stats()
{
    namespace cli = ::tkoz::cli;
    ::std::cerr << cli::cFgBMagenta << "tests run: " << num_tests_run
                << cli::cReset << ::std::endl;
    ::std::cerr << cli::cFgBMagenta << "tests passed: " << num_tests_passed
                << cli::cReset << ::std::endl;
    ::std::cerr << cli::cFgBMagenta << "tests failed: " << num_tests_failed
                << cli::cReset << ::std::endl;
    ::std::cerr << cli::cFgBMagenta << "total time: ";
    print_time(total_time);
    ::std::cerr << cli::cReset << ::std::endl << ::std::endl;
}

/// run the tests sequentially
void run_tests(int argc, char **argv)
{
    using hrclock = ::std::chrono::high_resolution_clock;
    namespace cli = ::tkoz::cli;
    ::std::map<void(*)(),::std::vector<std::string>> test_funcs_map;
    for (auto [name,test] : test_funcs)
        test_funcs_map[test].push_back(name);
    bool test_funcs_error = false;
    for (auto [func,names] : test_funcs_map)
        if (names.size() > 1)
        {
            test_funcs_error = true;
            ::std::cerr << cli::cFgBRed << "error: test func at " << func
                        << "occurred multiple times with names:";
            for (const auto& name : names)
                ::std::cerr << " " << name;
            ::std::cerr << cli::cReset << ::std::endl;
        }
    if (test_funcs_error)
        throw assert_fail_t();
    ::std::set<::std::string> test_args;
    for (int i = 1; i < argc; ++i)
        test_args.insert(::std::string(argv[i]));
    auto t0 = hrclock::now();
    ::std::size_t index = 0;
    for (auto [name,test] : test_funcs)
    {
        if (!test_args.empty() && !test_args.contains(name))
            continue;
        ::std::cerr << cli::cFgBBlue << "running: " << cli::cReset
                    << name << " ( " << (++index) << " / "
                    << test_funcs.size() << " )" << ::std::endl;
        ++num_tests_run;
        auto t1 = hrclock::now();
        bool success = false;
        try
        {
            test();
            success = true;
        }
        catch (...)
        {
            switch (assert_fail_action)
            {
            case assert_fail_terminate:
                ::std::exit(cli::cExitFailure);
            default:
                break;
            }
        }
        auto t2 = hrclock::now();
        if (success)
        {
            ++num_tests_passed;
            ::std::cerr << cli::cFgBGreen << "success " << cli::cReset;
            print_time(t2-t1);
            ::std::cerr << ::std::endl << ::std::endl;
        }
        else
        {
            ++num_tests_failed;
            ::std::cerr << cli::cFgBRed << "failure " << cli::cReset;
            print_time(t2-t1);
            ::std::cerr << ::std::endl << ::std::endl;
            switch (assert_fail_action)
            {
            case assert_fail_terminate:
                ::std::cerr << cli::cFgBRed
                            << "test failure, terminating test runner"
                            << cli::cReset << ::std::endl;
                ::std::exit(cli::cExitFailure);
            default:
                break;
            }
        }
    }
    auto t3 = hrclock::now();
    total_time = duration_cast<time_type>(t3-t0);
}

} // namespace tkoz::test

//
// macros for basic test case definition
// in practice, should use TEST_RUNNER_MAIN in 1 .cpp file
// and for each test case, either use TEST_CASE_CREATE(identifier,code), or
// create a void() function and use TEST_CASE_INSERT(function)
// (identifier is not a quoted string, code should be inside {} braces)
// this should be all that is necessary to setup a program with unit tests
//

/// define a test case
/// (name is an identifier, not quoted string)
#define TEST_CASE_CREATE(name) \
void _test_##name##_function(); \
[[maybe_unused]] static auto test_##name##_dummyvar = \
    ::tkoz::test::add_test_func(#name,_test_##name##_function); \
void _test_##name##_function()

/// add an existing function as a test case
/// function type must be void(*)()
#define TEST_CASE_INSERT(func) \
[[maybe_unused]] static auto _test_##func##_dummyvar = \
    ::tkoz::test::add_test_func(#func,func);

#define _TEST_PRINT_TIME(t) [] { ::tkoz::test::print_time(t); } ()

/// loop that runs the tests
#define _TEST_RUNNER_LOOP [argc,argv] \
{ ::tkoz::test::run_tests(argc,argv); } ()

/// writes overall test run stats
#define _TEST_RUNNER_STAT [] { ::tkoz::test::print_stats(); } ()

/// creates a main function for running tests
/// only use this once if multiple .cpp files are used for a test program
#define TEST_RUNNER_MAIN \
int main(int argc, char **argv) \
{ \
    (void)argc; \
    (void)argv; \
    namespace cli = ::tkoz::cli; \
    ::std::cerr << cli::cFgBYellow << "tkoz unit testing library" \
        << ::std::endl << "test file: " << __FILE__ \
        << ::std::endl << "tests found: " << ::tkoz::test::test_funcs.size() \
        << cli::cReset << ::std::endl << ::std::endl; \
    _TEST_RUNNER_LOOP; \
    _TEST_RUNNER_STAT; \
    bool all_pass = \
        ::tkoz::test::num_tests_passed == ::tkoz::test::num_tests_run; \
    int ret_code = all_pass ? cli::cExitSuccess : cli::cExitFailure; \
    ::std::cerr << (all_pass ? cli::cFgBGreen : cli::cFgBRed) \
        << "return code: " << ret_code \
        << (all_pass ? " (success)" : " (failure)") \
        << cli::cReset << ::std::endl; \
    return ret_code; \
}
// TODO add useful command line arguments

//
// macros for output during test runs
//

#define _TEST_MSG(type,color,msg,file,line,func) \
[&] \
{ \
    ::std::cerr << file << ":" << line << ":" << color << type \
        << ::tkoz::cli::cReset << ": " << msg << ::std::endl; \
} \
()

/// print extra info during a test
/// can use << to separate multiple things
#define TEST_INFO(msg) _TEST_MSG("info",::tkoz::cli::cFgBBlue, \
    msg,__FILE__,__LINE__,__func__)

/// print a warning during a test
/// can use << to separate multiple things
#define TEST_WARN(msg) _TEST_MSG("warn",::tkoz::cli::cFgBYellow, \
    msg,__FILE__,__LINE__,__func__)

/// print a failure during a test
/// can use << to separate multiple things
#define TEST_FAIL(msg) _TEST_MSG("fail",::tkoz::cli::cFgBRed, \
    msg,__FILE__,__LINE__,__func__)

//
// assertion macros intended to be used in test cases
// macros ending with _MSG use a custom message displayed on failure
// macros not ending with _MSG create a message automatically
// the message can include multiple things separated by <<
//

/// assert something is true during a test
/// print a message on failure
#define TEST_ASSERT_MSG(expr,msg) \
[&] \
{ \
    if (!static_cast<bool>(expr)) [[unlikely]] \
    { \
        TEST_FAIL(msg); \
        throw ::tkoz::test::assert_fail_t(); \
    } \
} \
()

/// assert something is true during a test
#define TEST_ASSERT(expr) TEST_ASSERT_MSG(expr, \
    "assert(" #expr ")")

/// assert an expression is true
#define TEST_ASSERT_TRUE(expr) TEST_ASSERT_MSG(expr, \
    "expected (" #expr ") to be true")

/// assert an expression is true (custom failure message)
#define TEST_ASSERT_TRUE_MSG(expr,msg) TEST_ASSERT_MSG(expr,msg)

/// assert an expression is false
#define TEST_ASSERT_FALSE(expr) TEST_ASSERT_MSG(!(expr), \
    "expected (" #expr ") to be false")

/// assert an expression is false (custom failure message)
#define TEST_ASSERT_FALSE_MSG(expr,msg) TEST_ASSERT_MSG(!(expr),msg)

/// assert 2 expressions are equal
#define TEST_ASSERT_EQ(expr1,expr2) TEST_ASSERT_MSG((expr1) == (expr2), \
    "expected (" #expr1 ") to be equal to (" #expr2 ")")

/// assert 2 expressions are equal (custom failure message)
#define TEST_ASSERT_EQ_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) == (expr2),msg)

/// assert 2 expressions are not equal
#define TEST_ASSERT_NE(expr1,expr2) TEST_ASSERT_MSG((expr1) != (expr2), \
    "expected (" #expr1 ") to be NOT equal to (" #expr2 ")")

/// assert 2 expressions are not equal (custom failure message)
#define TEST_ASSERT_NE_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) != (expr2),msg)

/// assert 2 expressions compare <
#define TEST_ASSERT_LT(expr1,expr2) TEST_ASSERT_MSG((expr1) < (expr2), \
    "expected (" #expr1 ") to be less than (" #expr2 ")")

/// assert 2 expressions compare < (custom failure message)
#define TEST_ASSERT_LT_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) < (expr2),msg)

/// assert 2 expressions compare >
#define TEST_ASSERT_GT(expr1,expr2) TEST_ASSERT_MSG((expr1) > (expr2), \
    "expected (" #expr1 ") to be greater than (" #expr2 ")")

/// assert 2 expressions compare > (custom failure message)
#define TEST_ASSERT_GT_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) > (expr2),msg)

/// assert 2 expressions compare <=
#define TEST_ASSERT_LE(expr1,expr2) TEST_ASSERT_MSG((expr1) <= (expr2), \
    "expected (" #expr1 ") to be less than or equal to (" #expr2 ")")

/// assert 2 expressions compare <= (custom failure message)
#define TEST_ASSERT_LE_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) <= (expr2),msg)

/// assert 2 expressions compare >=
#define TEST_ASSERT_GE(expr1,expr2) TEST_ASSERT_MSG((expr1) >= (expr2), \
    "expected (" #expr1 ") to be greater than or equal to (" #expr2 ")")

/// assert 2 expressions compare >= (custom failure message)
#define TEST_ASSERT_GE_MSG(expr1,expr2,msg) \
    TEST_ASSERT_MSG((expr1) >= (expr2),msg)

#define _TEST_ABS(x) ((x) < 0 ? -(x) : (x))
#define _TEST_REL(x,y) (_TEST_ABS((x) - (y)) / (y))

/// assert 2 (floating point) expressions are almost equal
/// (using absolute error)
#define TEST_ASSERT_CLOSE_ABS(expr1,expr2,abs_tol) \
    TEST_ASSERT_MSG(_TEST_ABS((expr1) - (expr2)) < abs_tol, \
    "expected (" #expr1 ") and (" #expr2 ") to be almost equal " \
    "(absolute tolerance " #abs_tol ")")

/// assert 2 (floating point) expressions are almost equal
/// (using absolute error, with custom message)
#define TEST_ASSERT_CLOSE_ABS_MSG(expr1,expr2,abs_tol,msg) \
    TEST_ASSERT_MSG(_TEST_ABS((expr1) - (expr2)) < abs_tol, msg)

/// assert 2 (floating point) expressions are almost equal
/// (using relative error)
#define TEST_ASSERT_CLOSE_REL(expr1,expr2,rel_tol) \
    TEST_ASSERT_MSG(_TEST_REL(expr1,expr2) < rel_tol, \
    "expected (" #expr1 ") and (" #expr2 ") to be almost equal " \
    "(relative tolerance " #rel_tol ")")

/// assert 2 (floating point) expressions are almost equal
/// (using relative error, with custom message)
#define TEST_ASSERT_CLOSE_REL_MSG(expr1,expr2,rel_tol,msg) \
    TEST_ASSERT_MSG(_TEST_REL(expr1,expr2) < rel_tol, msg)

/// assert that an expression raises an exception of expected type
/// (with custom message depending on no exception or unexpected type)
#define TEST_EXCEPTION_MSG(expr,exc,msg_none,msg_other) \
[&] \
{ \
    bool _ok = false; \
    try \
    { \
        static_cast<void>(expr); \
        TEST_FAIL(msg_none); \
    } \
    catch (const exc&) \
    { \
        _ok = true; \
    } \
    catch (...) \
    { \
        TEST_FAIL(msg_other); \
        const std::type_info *_ti = abi::__cxa_current_exception_type(); \
        if (_ti) \
        { \
            int _st; \
            char *_dm = abi::__cxa_demangle( \
                _ti->name(),nullptr,nullptr,&_st); \
            const char *_tt = (_st == 0) ? _dm : _ti->name(); \
            TEST_FAIL("unexpected exception of type: " << _tt); \
            if (_st == 0) \
                ::std::free(_dm); \
        } \
        else \
        { \
            TEST_FAIL("could not determine current exception type"); \
        } \
        throw; \
    } \
    if (!_ok) \
        throw ::tkoz::test::assert_fail_t(); \
} \
()

/// assert that an expression raises an exception of expected type
#define TEST_EXCEPTION(expr,exc) TEST_EXCEPTION_MSG(expr,exc, \
    "expected an exception, no exception thrown", \
    "expected an exception of type: " #exc)

/// assert that an expression raises any exception
/// (with a custom message when no exception is thrown)
#define TEST_EXCEPTION_ANY_MSG(expr,msg) \
[&] \
{ \
    bool _ok = false; \
    try \
    { \
        static_cast<void>(expr); \
        TEST_FAIL(msg); \
    } \
    catch (...) \
    { \
        _ok = true; \
    } \
    if (!_ok) \
        throw ::tkoz::test::assert_fail_t(); \
} \
()

/// assert that an expression raises any exception
#define TEST_EXCEPTION_ANY(expr) TEST_EXCEPTION_ANY_MSG(expr, \
    "expected an exception, no exception thrown")

