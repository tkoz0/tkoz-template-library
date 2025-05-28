//
// Compile time tests for some metaprogramming utilities
//

#include <tkoz/metacalc/Utils.hpp>

#include <tkoz/stl/Meta.hpp>

int main()
{
    using namespace tkoz::metacalc;
    namespace meta = tkoz::stl::meta;

    // packAnd
    static_assert(packAnd<>);
    static_assert(!packAnd<false>);
    static_assert(packAnd<true>);
    static_assert(packAnd<true,true>);
    static_assert(!packAnd<false,false>);
    static_assert(!packAnd<false,true>);
    static_assert(!packAnd<true,false>);
    static_assert(packAnd<true,true,true,true,true,true>);
    static_assert(!packAnd<true,true,false,true,true>);

    // packOr
    static_assert(!packOr<>);
    static_assert(!packOr<false>);
    static_assert(packOr<true>);
    static_assert(packOr<true,true>);
    static_assert(!packOr<false,false>);
    static_assert(packOr<true,false>);
    static_assert(packOr<false,true>);
    static_assert(!packOr<false,false,false,false,false>);
    static_assert(packOr<false,false,true,false,false,false>);
}
