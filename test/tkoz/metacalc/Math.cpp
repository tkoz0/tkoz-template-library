//
// Compile time tests for math metaprogramming stuff
//

#include <tkoz/metacalc/Math.hpp>

#include <tkoz/stl/Meta.hpp>

int main()
{
    using namespace tkoz::metacalc;
    namespace meta = tkoz::stl::meta;

    // packMax
    static_assert(packMax<float,1.7f> == 1.7f);
    static_assert(packMax<double,-4.1,4.1> == 4.1);
    static_assert(packMax<int,5,11,7> == 11);
    static_assert(packMax<char,'N','T','a','v'> == 'v');
    // does not compile
    //static_assert(packMax<>);
    //static_assert(packMax<int>);

    // packMin
    static_assert(packMin<long,-50> == -50);
    static_assert(packMin<unsigned int,80,90,100,90,80> == 80);
    static_assert(packMin<double,1.1,-1.1,2.2,-2.2> == -2.2);
    static_assert(packMin<char,'u','v','B','A'> == 'A');
    // does not compile
    //static_assert(packMin<>);
    //static_assert(packMin<long>);

    // packSum
    static_assert(packSum<int> == 0);
    static_assert(packSum<int,3> == 3);
    static_assert(packSum<long,5,-12,3,9,4,-5> == 4);
    static_assert(packSum<float,3.14f,-3.14f> == 0.0);
    // does not compile
    //static_assert(packSum<> == 0);

    // packProd
    static_assert(packProd<double> == 1);
    static_assert(packProd<double,2.0,-2.0> == -4.0);
    static_assert(packProd<int,1,0,1> == 0);
    static_assert(packProd<unsigned int,1,2,3,4,5,6> == 720);
    // does not compile
    //static_assert(packProd<> == 1);
}
