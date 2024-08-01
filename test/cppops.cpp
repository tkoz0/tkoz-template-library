#include <cassert>
#include <cstdint>

#include "../src/cppops.hpp"

int main()
{
    uint32_t a, b;
    a = 5;
    b = tkoz::op_preinc(a);
    assert(a == 6 && b == 6);
    a = 5;
    b = tkoz::op_postinc(a);
    assert(a == 6 && b == 5);
    a = 5;
    b = tkoz::op_predec(a);
    assert(a == 4 && b == 4);
    a = 5;
    b = tkoz::op_postdec(a);
    assert(a == 4 && b == 5);
    return 0;
}
