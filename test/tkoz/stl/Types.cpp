///
/// Compile time tests related to basic types
///

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

#include <cstdint>
#include <limits>

// do not need to run anything, only compile time stuff
int main()
{
    using namespace tkoz::stl;

    // these sizes are what GCC/Clang have when compiled for x86_64/amd64
    static_assert(sizeof(bool_t) == 1);
    static_assert(sizeof(single_t) == 4);
    static_assert(sizeof(double_t) == 8);
    static_assert(sizeof(ldouble_t) == 16);
    static_assert(sizeof(schar_t) == 1);
    static_assert(sizeof(uchar_t) == 1);
    static_assert(sizeof(sshort_t) == 2);
    static_assert(sizeof(ushort_t) == 2);
    static_assert(sizeof(sint_t) == 4);
    static_assert(sizeof(uint_t) == 4);
    static_assert(sizeof(slong_t) == 8);
    static_assert(sizeof(ulong_t) == 8);
    static_assert(sizeof(sll_t) == 8);
    static_assert(sizeof(ull_t) == 8);

    // primitives should be aligned to their size
    static_assert(alignof(bool_t) == 1);
    static_assert(alignof(single_t) == 4);
    static_assert(alignof(double_t) == 8);
    static_assert(alignof(ldouble_t) == 16);
    static_assert(alignof(schar_t) == 1);
    static_assert(alignof(uchar_t) == 1);
    static_assert(alignof(sshort_t) == 2);
    static_assert(alignof(ushort_t) == 2);
    static_assert(alignof(sint_t) == 4);
    static_assert(alignof(uint_t) == 4);
    static_assert(alignof(slong_t) == 8);
    static_assert(alignof(ulong_t) == 8);
    static_assert(alignof(sll_t) == 8);
    static_assert(alignof(ull_t) == 8);

    // size assert on primitives
    static_assert(sizeof(bool) == 1);
    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);
    static_assert(sizeof(long double) == 16);
    static_assert(sizeof(std::uint8_t) == 1);
    static_assert(sizeof(std::uint16_t) == 2);
    static_assert(sizeof(std::uint32_t) == 4);
    static_assert(sizeof(std::uint64_t) == 8);
    static_assert(sizeof(std::int8_t) == 1);
    static_assert(sizeof(std::int16_t) == 2);
    static_assert(sizeof(std::int32_t) == 4);
    static_assert(sizeof(std::int64_t) == 8);

    static_assert(cPtrSize == 4 || cPtrSize == 8); // expect 32 bit or 64 bit
    static_assert(sizeof(std::intptr_t) == cPtrSize);
    static_assert(sizeof(std::uintptr_t) == cPtrSize);

    // pointer size assert
    static_assert(sizeof(void*) == cPtrSize);
    static_assert(sizeof(bool*) == cPtrSize);
    static_assert(sizeof(float*) == cPtrSize);
    static_assert(sizeof(double*) == cPtrSize);
    static_assert(sizeof(long double*) == cPtrSize);
    static_assert(sizeof(char*) == cPtrSize);
    static_assert(sizeof(schar_t*) == cPtrSize);
    static_assert(sizeof(uchar_t*) == cPtrSize);
    static_assert(sizeof(sshort_t*) == cPtrSize);
    static_assert(sizeof(ushort_t*) == cPtrSize);
    static_assert(sizeof(sint_t*) == cPtrSize);
    static_assert(sizeof(uint_t*) == cPtrSize);
    static_assert(sizeof(slong_t*) == cPtrSize);
    static_assert(sizeof(ulong_t*) == cPtrSize);
    static_assert(sizeof(sll_t*) == cPtrSize);
    static_assert(sizeof(ull_t*) == cPtrSize);
    static_assert(sizeof(std::uint8_t*) == cPtrSize);
    static_assert(sizeof(std::uint16_t*) == cPtrSize);
    static_assert(sizeof(std::uint32_t*) == cPtrSize);
    static_assert(sizeof(std::uint64_t*) == cPtrSize);
    static_assert(sizeof(std::int8_t*) == cPtrSize);
    static_assert(sizeof(std::int16_t*) == cPtrSize);
    static_assert(sizeof(std::int32_t*) == cPtrSize);
    static_assert(sizeof(std::int64_t*) == cPtrSize);
    static_assert(sizeof(std::nullptr_t) == cPtrSize);

    //
    // types of literals
    //
    using tkoz::stl::meta::isSame;

    static_assert(isSame<decltype(true),bool>);
    static_assert(isSame<decltype(false),bool>);
    static_assert(isSame<decltype(nullptr),std::nullptr_t>);
    static_assert(isSame<decltype(' '),char>);

    // string literals are lvalues so the (&) for reference is needed
    static_assert(isSame<decltype(""),const char(&)[1]>);

    // integers (standard)
    static_assert(isSame<decltype(0),sint_t>);
    static_assert(isSame<decltype(0u),uint_t>);
    static_assert(isSame<decltype(0l),slong_t>);
    static_assert(isSame<decltype(0ul),ulong_t>);
    static_assert(isSame<decltype(0ll),sll_t>);
    static_assert(isSame<decltype(0ull),ull_t>);

    // integers (hexadecimal)
    static_assert(isSame<decltype(0x0),sint_t>);
    static_assert(isSame<decltype(0x0u),uint_t>);
    static_assert(isSame<decltype(0x0l),slong_t>);
    static_assert(isSame<decltype(0x0ul),ulong_t>);
    static_assert(isSame<decltype(0x0ll),sll_t>);
    static_assert(isSame<decltype(0x0ull),ull_t>);

    // integers (octal)
    static_assert(isSame<decltype(00),sint_t>);
    static_assert(isSame<decltype(00u),uint_t>);
    static_assert(isSame<decltype(00l),slong_t>);
    static_assert(isSame<decltype(00ul),ulong_t>);
    static_assert(isSame<decltype(00ll),sll_t>);
    static_assert(isSame<decltype(00ull),ull_t>);

    // integers (binary)
    static_assert(isSame<decltype(0b0),sint_t>);
    static_assert(isSame<decltype(0b0u),uint_t>);
    static_assert(isSame<decltype(0b0l),slong_t>);
    static_assert(isSame<decltype(0b0ul),ulong_t>);
    static_assert(isSame<decltype(0b0ll),sll_t>);
    static_assert(isSame<decltype(0b0ull),ull_t>);

    // floating point (standard)
    static_assert(isSame<decltype(0.0),double>);
    static_assert(isSame<decltype(0.0l),long double>);
    static_assert(isSame<decltype(0.0f),float>);

    // floating point (scientific)
    static_assert(isSame<decltype(1e0),double>);
    static_assert(isSame<decltype(1e0l),long double>);
    static_assert(isSame<decltype(1e0f),float>);

    // floating point (hexadecimal)
    static_assert(isSame<decltype(0x1p1),double>);
    static_assert(isSame<decltype(0x1p1l),long double>);
    static_assert(isSame<decltype(0x1p1f),float>);

    // infinity and nan
    static_assert(std::numeric_limits<float>::has_infinity);
    static_assert(std::numeric_limits<double>::has_infinity);
    static_assert(std::numeric_limits<long double>::has_infinity);
    static_assert(std::numeric_limits<float>::has_quiet_NaN);
    static_assert(std::numeric_limits<double>::has_quiet_NaN);
    static_assert(std::numeric_limits<long double>::has_quiet_NaN);
    static_assert(std::numeric_limits<float>::has_signaling_NaN);
    static_assert(std::numeric_limits<double>::has_signaling_NaN);
    static_assert(std::numeric_limits<long double>::has_signaling_NaN);
    static_assert(std::numeric_limits<float>::has_denorm);
    static_assert(std::numeric_limits<double>::has_denorm);
    static_assert(std::numeric_limits<long double>::has_denorm);
}
