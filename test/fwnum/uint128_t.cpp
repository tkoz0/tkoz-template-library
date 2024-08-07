
#include <cassert>
#include <sstream>
#include <vector>

#include "../../src/fwnum/uint128_t.hpp"
#include "../test_common.hpp"
using tkoz::uint128_t;
using std::cout;
using std::endl;

void check_u128(uint128_t n, uint64_t w0, uint64_t w1)
{
    assert(n.array()[0] == w0);
    assert(n.array()[1] == w1);
}

void check_u128(uint128_t n, const char *s)
{
    std::stringstream ss;
    ss << n;
    assert(ss.str() == s);
}

uint128_t factorial(uint32_t n)
{
    if (n < 2) return n;
    uint128_t ret = 1;
    for (uint32_t i = 2; i <= n; ++i)
        ret *= i;
    return ret;
}

std::vector<const char*> u128strings =
{
    "0",
    "1",
    "9",
    "10",
    "19",
    "20",
    "21",
    "1000",
    "9876",
    "4294967295",
    "4294967296", // 2**32
    "4294967297",
    "18446744073709551615",
    "18446744073709551616", // 2**64
    "18446744073709551617",
    "1111111111111111111111111111111111111",
    "2305843009213693951", // 2**61-1
    "618970019642690137449562111", // 2**89-1
    "162259276829213363391578010288127", // 2**107-1
    "170141183460469231731687303715884105727", // 2**127-1
    "-1"
};

// construct/convert
void test1()
{
    bool b = false;
    int8_t i8 = -1;
    int16_t i16 = -16;
    int32_t i32 = 96;
    int64_t i64 = 10000000000;
    uint8_t u8 = 63;
    uint16_t u16 = 12000;
    uint32_t u32 = 2147483648;
    uint64_t u64 = 1000000000039;
    float fp32 = 89.1;
    double fp64 = -2.1;
    uint128_t n1;
    assert(n1 == 0);
    n1 = b;
    assert(n1 == 0);
    assert(bool(n1) == b);
    b = true;
    n1 = b;
    assert(n1 == 1);
    assert(bool(n1) == b);
    n1 = i8;
    check_u128(n1,-1,-1);
    assert(int8_t(n1) == i8);
    n1 = i16;
    check_u128(n1,-16,-1);
    assert(int16_t(n1) == i16);
    n1 = i32;
    check_u128(n1,96,0);
    assert(int32_t(n1) == i32);
    n1 = i64;
    check_u128(n1,10000000000,0);
    assert(int64_t(n1) == i64);
    n1 = u8;
    check_u128(n1,63,0);
    assert(uint8_t(n1) == u8);
    n1 = u16;
    check_u128(n1,12000,0);
    assert(uint16_t(n1) == u16);
    n1 = u32;
    check_u128(n1,2147483648,0);
    assert(uint32_t(n1) == u32);
    n1 = u64;
    check_u128(n1,1000000000039,0);
    assert(uint64_t(n1) == u64);
    n1 = uint128_t(fp32);
    check_u128(n1,89,0);
    assert(float(n1) == 89.0f);
    n1 = uint128_t(fp64);
    check_u128(n1,-2,-1);
    assert(double(n1) == 3.402823669209385e+38);
    // from uint64_t
    check_u128(uint128_t(),0,0);
    check_u128(uint128_t(89,107),89,107);
    check_u128(uint128_t(1000000007u,1000000009u),1000000007u,1000000009u);
    check_u128(uint128_t(1000000000061ull,1000000000063ull),1000000000061ull,1000000000063ull);
    // from uint32_t
    assert(uint128_t(5014321u,212761408u,2999999999u,6112u)
        == uint128_t(913803289215927089ull,26253840113151ull));
        // 484297869519387227085804130829105
    assert(uint128_t(15u,240u,65535u,4294901760u)
        == uint128_t(1030792151055ull,18446462598732906495ull));
        // 340277174624081137543118948521696296975
    // from uint16_t
    assert(uint128_t(16,32,64,128,256,512,1024,2048)
        == uint128_t(36029071898968080ull,576465150383489280ull));
        // 10633905096536716331957354350241644560
    assert(uint128_t(7017,62144,412,1507,1103,79,12777,6969)
        == uint128_t(424184563502160745ull,1961653989498881103ull));
        // 36186129105457183985602915199327673193
    // from uint8_t
    assert(uint128_t(204,215,130,173,135,234,238,200,3,238,165,112,87,83,250,72)
        == uint128_t(14478767720495241164ull,5258607149925658115ull));
        // 97004180278857809439118275110857005004
    assert(uint128_t(201,245,0,62,2,235,26,218,238,244,149,118,135,69,21,219)
        == uint128_t(15716132244525479369ull,15786600516929582318ull));
        // 291211379529690916706582053950467405257
    // from bool (for memes)
    assert(uint128_t(0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,
                     0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,
                     1,0,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,
                     0,1,0,1,1,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0)
        == uint128_t(14346338644655984136ull,4675209317535610437ull));
        // 86242389771601699135908678068775800328
    assert(uint128_t(0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,
                     1,1,1,1,0,1,0,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,
                     1,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,
                     1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1)
        == uint128_t(7617186964671749594ull,12220001005671563757ull));
        // 225419231132096679587794432454698130906
    // implicit conversion from primitive types
    n1 = (char) 0;
    n1 = (tkoz::schar_t) 0;
    n1 = (tkoz::uchar_t) 0;
    n1 = (tkoz::sshort_t) 0;
    n1 = (tkoz::ushort_t) 0;
    n1 = (tkoz::sint_t) 0;
    n1 = (tkoz::uint_t) 0;
    n1 = (tkoz::sll_t) 0;
    n1 = (tkoz::ull_t) 0;
}

void test2()
{
    // TODO float/double conversions
    uint128_t n1;
    n1 = 0.0f;
    assert(n1 == 0);
    n1 = 0.0;
    assert(n1 == 0);
}

#if 1

int main()
{
    test1();
    test2();
    assert(factorial(64).array()[0] == (1ul << 63));
    assert(factorial(64).array()[0] == (1ull << 63));
    assert(factorial(128) == uint128_t(1) << 127);
    assert(factorial(130) == 0);
    return 0;
}

#else

int main()
{
    uint128_t n;
    while (std::cin >> n)
    {
        cout << n.get_array()[0] << " " << n.get_array()[1] << endl;
        cout << n << endl;
    }
}

#endif
