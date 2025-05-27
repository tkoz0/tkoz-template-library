//
// Compile time tests for concepts
//

#include <tkoz/stl/Concepts.hpp>

// only compile time tests needed, not running anything
int main()
{
    using namespace tkoz::stl::concepts;

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
}
