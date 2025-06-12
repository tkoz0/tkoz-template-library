///
/// common utilities
///

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Utils.hpp>

#include <tkoz/Test.hpp>

#include <string>

TEST_RUNNER_MAIN

template <typename T>
T&& testForward(T &&v)
{
    //using tkoz::stl::forward;
    // T&& can be accepted as lvalue or rvalue reference
    // tkoz::stl::forward (should be equivalent to std::forward) deduces it
    return tkoz::stl::fwdRef<T>(v);
}

TEST_CASE_CREATE(test)
{
    namespace meta = tkoz::stl::meta;
    using meta::declVal;
    using tkoz::stl::move;
    using tkoz::stl::swap;
    using tkoz::stl::fwdRef;

    static_assert(meta::isSame<int&&,decltype(move(declVal<int>()))>);
    static_assert(meta::isSame<int&&,decltype(move(declVal<int&>()))>);
    static_assert(meta::isSame<int&&,decltype(move(declVal<int&&>()))>);

    int ia = 1;
    int ib = 2;
    swap(ia,ib);
    TEST_ASSERT_EQ(ia,2);
    TEST_ASSERT_EQ(ib,1);

    using std::string;

    // rvalue reference is forwarded to rvalue reference
    static_assert(meta::isSame<int&&,decltype(testForward(declVal<int&&>()))>);
    static_assert(meta::isSame<const int&&,decltype(testForward(declVal<const int&&>()))>);
    static_assert(meta::isSame<string&&,decltype(testForward(declVal<string&&>()))>);
    static_assert(meta::isSame<const string&&,decltype(testForward(declVal<const string&&>()))>);

    // lvalue reference is forwarded to lvalue reference
    static_assert(meta::isSame<int&,decltype(testForward(declVal<int&>()))>);
    static_assert(meta::isSame<const int&,decltype(testForward(declVal<const int&>()))>);
    static_assert(meta::isSame<string&,decltype(testForward(declVal<string&>()))>);
    static_assert(meta::isSame<const string&,decltype(testForward(declVal<const string&>()))>);

    // pass by value creates a copy and is treated as rvalue to rvalue
    // looks like primitive always becomes non const rvalue reference
    static_assert(meta::isSame<int&&,decltype(testForward(declVal<int>()))>);
    static_assert(meta::isSame<int&&,decltype(testForward(declVal<const int>()))>);
    static_assert(meta::isSame<string&&,decltype(testForward(declVal<string>()))>);
    static_assert(meta::isSame<const string&&,decltype(testForward(declVal<const string>()))>);

    static_assert(meta::isSame<int&&,decltype(fwdRef<int&&>(declVal<int&&>()))>);
    static_assert(meta::isSame<const int&&,decltype(fwdRef<const int&&>(declVal<const int&&>()))>);
    static_assert(meta::isSame<int&,decltype(fwdRef<int&>(declVal<int&>()))>);
    static_assert(meta::isSame<const int&,decltype(fwdRef<const int&>(declVal<const int&>()))>);
    static_assert(meta::isSame<int&&,decltype(fwdRef<int&&>(declVal<int&&>()))>);
    static_assert(meta::isSame<const int&&,decltype(fwdRef<const int&&>(declVal<const int&&>()))>);

    // somehow these conflict with std::forward
    static_assert(meta::isSame<string&&,decltype(tkoz::stl::fwdRef<string&&>(declVal<string&&>()))>);
    static_assert(meta::isSame<const string&&,decltype(tkoz::stl::fwdRef<const string&&>(declVal<const string&&>()))>);
    static_assert(meta::isSame<string&,decltype(tkoz::stl::fwdRef<string&>(declVal<string&>()))>);
    static_assert(meta::isSame<const string&,decltype(tkoz::stl::fwdRef<const string&>(declVal<const string&>()))>);
    static_assert(meta::isSame<string&&,decltype(tkoz::stl::fwdRef<string&&>(declVal<string>()))>);
    static_assert(meta::isSame<const string&&,decltype(tkoz::stl::fwdRef<const string&&>(declVal<const string>()))>);
    //static_assert(meta::isSame<string&&,decltype(fwdRef<string&&>(declVal<string&&>()))>);
    //static_assert(meta::isSame<const string&&,decltype(fwdRef<const string&&>(declVal<const string&&>()))>);
    //static_assert(meta::isSame<string&,decltype(fwdRef<string&>(declVal<string&>()))>);
    //static_assert(meta::isSame<const string&,decltype(fwdRef<const string&>(declVal<const string&>()))>);
    //static_assert(meta::isSame<string&&,decltype(fwdRef<string&&>(declVal<string>()))>);
    //static_assert(meta::isSame<const string&&,decltype(fwdRef<const string&&>(declVal<const string>()))>);
}
