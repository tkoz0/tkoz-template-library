
#include <cassert>
#include <sstream>
#include <vector>

#include "../../src/fwnum/uint128_t.hpp"
#include "../test_common.hpp"
using tkoz::uint128_t;
using std::cout;
using std::endl;

bool check_u128(uint128_t n, uint64_t w0, uint64_t w1)
{
    if (n.array()[0] != w0 || n.array()[1] != w1)
        cout << n.array()[0] << " " << n.array()[1] << endl;
    assert(n.array()[0] == w0);
    assert(n.array()[1] == w1);
    assert(n.get<0>() == w0);
    assert(n.get<1>() == w1);
    return true;
}

bool check_u128(uint128_t n, const char *s)
{
    std::stringstream ss;
    ss << n;
    assert(ss.str() == s);
    return true;
}

uint128_t factorial(uint32_t n)
{
    if (n < 2) return n;
    uint128_t ret = 1;
    for (uint32_t i = 2; i <= n; ++i)
        ret *= i;
    return ret;
}

uint128_t fibonacci(uint32_t n)
{
    if (n < 2) return n;
    uint128_t a = 1, b = 1, c;
    n -= 2;
    while (n--)
        c = a + b, a = b, b = c;
    return b;
}

uint128_t perm(uint32_t n, uint32_t k)
{
    uint128_t ret = 1;
    for (uint32_t i = n-k+1; k <= n; ++i)
        ret *= i;
    return ret;
}

uint128_t comb(uint32_t n, uint32_t k)
{
    k = std::min(k,n-k);
    uint128_t ret = 1;
    for (uint32_t i = 1; i <= k; ++i)
        ret *= n+1-i, ret /= i;
    return ret;
}

uint128_t gcd(uint128_t a, uint128_t b)
{
    if (a < b) std::swap(a,b);
    uint128_t t;
    while (b)
        t = a%b, a = b, b = t;
    return a;
}

void test_ctor()
{
    check_u128(uint128_t(),0,0);
    // 64
    check_u128(uint128_t(700,-700),700,-700);
    check_u128(uint128_t(2305843009213693951ull,0),2305843009213693951ull,0);
    check_u128(uint128_t(0,2305843009213693951),0,2305843009213693951);
    check_u128(uint128_t(89,107),89,107);
    check_u128(uint128_t(1000000007u,1000000009u),1000000007u,1000000009u);
    check_u128(uint128_t(1000000000061ull,1000000000063ull),1000000000061ull,1000000000063ull);
    // 32
    check_u128(uint128_t(5014321u,212761408u,2999999999u,6112u),913803289215927089ull,26253840113151ull);
    check_u128(uint128_t(15u,240u,65535u,4294901760u),1030792151055ull,18446462598732906495ull);
    // 16
    check_u128(uint128_t(16,32,64,128,256,512,1024,2048),36029071898968080ull,576465150383489280ull);
    check_u128(uint128_t(7017,62144,412,1507,1103,79,12777,6969),424184563502160745ull,1961653989498881103ull);
    // 8
    check_u128(uint128_t(204,215,130,173,135,234,238,200,3,238,165,112,87,83,250,72),
                         14478767720495241164ull,5258607149925658115ull);
    check_u128(uint128_t(201,245,0,62,2,235,26,218,238,244,149,118,135,69,21,219),
                         15716132244525479369ull,15786600516929582318ull);
    // 1
    check_u128(uint128_t(0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,
                         0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,
                         1,0,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,
                         0,1,0,1,1,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0),
                         14346338644655984136ull,4675209317535610437ull);
    check_u128(uint128_t(0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,
                         1,1,1,1,0,1,0,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,
                         1,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,
                         1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1),
                         7617186964671749594ull,12220001005671563757ull);
    // initializer list
    uint128_t n1 = {128,511};
    check_u128(n1,128,511);
    uint128_t n2{257};
    check_u128(n2,257,0);
    n2 = {};
    check_u128(n2,0,0);
}

void test_conv_ints()
{
    int8_t i8 = -5;
    int16_t i16 = -43;
    int32_t i32 = 99;
    int64_t i64 = 10000000000ll;
    uint8_t u8 = 63;
    uint16_t u16 = 12000;
    uint32_t u32 = 2147483648;
    uint64_t u64 = 1000000000039ull;
    uint128_t n1;
    check_u128(n1,0,0);
    n1 = true;
    check_u128(n1,1,0);
    n1 = false;
    check_u128(n1,0,0);
    assert(bool(uint128_t(false)) == false);
    assert(bool(uint128_t(true)) == true);
    n1 = i8;
    check_u128(n1,-5ull,-1ull);
    assert(int8_t(n1) == i8);
    n1 = i16;
    check_u128(n1,-43ull,-1ull);
    assert(int16_t(n1) == i16);
    n1 = i32;
    check_u128(n1,99ull,0ull);
    assert(int32_t(n1) == i32);
    n1 = i64;
    check_u128(n1,10000000000ull,0ull);
    assert(int64_t(n1) == i64);
    n1 = u8;
    check_u128(n1,63ull,0ull);
    assert(uint8_t(n1) == u8);
    n1 = u16;
    check_u128(n1,12000ull,0ull);
    assert(uint16_t(n1) == u16);
    n1 = u32;
    check_u128(n1,2147483648ull,0ull);
    assert(uint32_t(n1) == u32);
    n1 = u64;
    check_u128(n1,1000000000039ull,0ull);
    assert(uint64_t(n1) == u64);
    tkoz::sll_t sll = 2000000000003ll;
    tkoz::ull_t ull = 2000000000123ull;
    n1 = sll;
    check_u128(n1,2000000000003ull,0ull);
    assert(tkoz::sll_t(n1) == sll);
    n1 = ull;
    check_u128(n1,2000000000123ull,0ull);
    assert(tkoz::ull_t(n1) == ull);
}

void test_conv_floats()
{
    // float/double -> uint128_t
    uint128_t n1;
    n1 = 0.0f;
    assert(n1 == 0);
    n1 = -0.0;
    assert(n1 == 0);
    n1 = 1.1f;
    assert(n1 == 1);
    n1 = 1.9f;
    assert(n1 == 1);
    n1 = 2.1;
    assert(n1 == 2);
    n1 = 2.9;
    assert(n1 == 2);
    n1 = 1e8f;
    assert(n1 == 100000000);
    n1 = 1000000007.0f;
    assert(n1 == 1000000000);
    n1 = 1000000033.0f;
    assert(n1 == 1000000064);
#if TKOZ_CPP17_OR_NEWER // binary floating point literals
    n1 = 0x1.p-2;
    assert(n1 == 0);
    n1 = 0x1.p+2;
    assert(n1 == 4);
    n1 = 0x1.8p+8;
    assert(n1 == 384);
    n1 = 0x1.ffffp+8;
    assert(n1 == 511);
#endif
    n1 = tkoz::_2pow_fp32(64,true);
    check_u128(n1,0ull,-1ull);
    n1 = tkoz::_2pow_fp64(64,false);
    check_u128(n1,0ull,1ull);
    n1 = tkoz::_2pow_fp32(127);
    check_u128(n1,0ull,1ull<<63);
    n1 = tkoz::_2pow_fp64(128);
    check_u128(n1,0ull,0ull);
    n1 = 3.14159265358979323864 * 100;
    check_u128(n1,314,0);
    n1 = 1e200;
    check_u128(n1,0,0);
    n1 = 1e100;
    check_u128(n1,0,0);
    n1 = 1.15e30;
    check_u128(n1,16906513001148841984ull,62341624917ull);
    n1 = 1.15e60;
    check_u128(n1,0,0);
    n1 = 46876176.893661986;
    check_u128(n1,46876176,0);
    n1 = 1.15e50;
    check_u128(n1,0,7519885477801885696ull);
    n1 = 1e30f;
    check_u128(n1,0,54210109440ull);
    n1 = 0.0714f;
    check_u128(n1,0,0);
    n1 = 0.0622071;
    check_u128(n1,0,0);
    n1 = -1.0f;
    assert(n1 == uint128_t(-1));
    n1 = -10.0;
    assert(n1 == uint128_t(-10));
    // uint128_t -> float/double
    n1 = 1000000000039ull;
    assert(double(n1) == 1000000000039.0);
    assert(float(n1) == 999999995904.0f);
    n1.set<0>(1ull<<63);
    n1.set<1>(1ull);
    assert(float(n1) == tkoz::_2pow_fp32(64) + tkoz::_2pow_fp32(63));
    assert(double(n1) == tkoz::_2pow_fp64(64) + tkoz::_2pow_fp64(63));
    n1.set<0>((1ull<<63) | 0x7ffull);
    assert(float(n1) == tkoz::_2pow_fp32(64) + tkoz::_2pow_fp32(63));
    assert(double(n1) == tkoz::_2pow_fp64(64) + tkoz::_2pow_fp64(63));
    n1.set<0>((1ull<<63) | 0xc00ull);
    assert(float(n1) == tkoz::_2pow_fp32(64) + tkoz::_2pow_fp32(63) + tkoz::_2pow_fp32(12));
    assert(double(n1) == tkoz::_2pow_fp64(64) + tkoz::_2pow_fp64(63) + tkoz::_2pow_fp64(12));
    n1 = -1;
    assert(n1.get<0>() == -1ull);
    assert(n1.get<1>() == -1ull);
    assert(float(n1) == __builtin_inff32());
    assert(double(n1) == tkoz::_2pow_fp64(128));
    n1 = 1000000000000000003ull;
    assert(float(n1) == 999999984306749440.0f);
    assert(double(n1) == 1.0e18);
    n1.set<0>(0);
    n1.set<1>(-1);
    assert(float(n1) == __builtin_inff32());
    assert(double(n1) == tkoz::_2pow_fp64(128));
}

void test_inc_dec()
{
    // pre
    uint128_t n1 = -2;
    assert(++n1 == -1);
    assert(++n1 == 0);
    assert(++n1 == 1);
    assert(++n1 == 2);
    assert(--n1 == 1);
    assert(--n1 == 0);
    assert(--n1 == -1);
    assert(--n1 == -2);
    // post
    uint128_t n2(-2ull,100);
    assert(n2++ == uint128_t(-2ull,100));
    assert(n2++ == uint128_t(-1ull,100));
    assert(n2++ == uint128_t(0,101));
    assert(n2 == uint128_t(1,101));
    assert(n2-- == uint128_t(1,101));
    assert(n2-- == uint128_t(0,101));
    assert(n2-- == uint128_t(-1ull,100));
    assert(n2 == uint128_t(-2ull,100));
}

void test_unary()
{
    uint128_t n1(778626958168965ull,915861347186786128ull);
    assert(~n1 == uint128_t(18445965446751382650ull,17530882726522765487ull));
    assert(!n1 == false);
    assert(!!n1 == true);
    assert(!n1 == !bool(n1));
    assert(+n1 == n1);
    assert(-n1 == uint128_t(18445965446751382651ull,17530882726522765487ull));
    assert(-n1 == ++~n1);
}

void test_arith()
{
    uint128_t n1,n2;
    uint64_t m;
    // +
    n1 = {5000,6000000};
    n2 = {7000,8000000};
    check_u128(n1+n2,12000,14000000);
    m = 500;
    check_u128((n1+m)+n2,12500,14000000);
    check_u128(n1+(m+n2),12500,14000000);
    m = -1;
    check_u128((n1+m)+n2,11999,14000001);
    check_u128(n1+(m+n2),11999,14000001);
    m = -1;
    n1 += m;
    check_u128(n1,4999,6000001);
    n2 = {10000000000000000000ull,10000000000000000000ull};
    n2 += n2;
    check_u128(n2,1553255926290448384ull,1553255926290448385ull);
    n2 = {1ull<<63};
    n2 += n2;
    assert(n2 == uint128_t(0,1));
    // -
    n1 = {5000,6000000};
    n2 = {7000,8000000};
    check_u128(n2-n1,2000,2000000);
    check_u128(n1-n2,-2000,-2000001);
    m = 4000;
    check_u128(n1-m,1000,6000000);
    check_u128(m-n1,-1000,-6000001);
    m = 6000;
    check_u128(n1-m,-1000,5999999);
    check_u128(m-n1,1000,-6000000);
    n1 -= 5000;
    check_u128(n1,0,6000000);
    n1 -= 1;
    check_u128(n1,-1,5999999);
    n1 -= n1;
    check_u128(n1,0,0);
    n1 -= 1;
    check_u128(n1,-1,-1);
    // *
    n1 = {10000000000ull};
    n2 = {10000000000ull};
    check_u128(n1*n2,7766279631452241920ull,5ull);
    n1 = {1ull<<60,1};
    check_u128(n1*n1,0,(2ull<<60)|(1ull<<56));
    n1 = {660000000000ull};
    n2 = {58000000000ull};
    check_u128(n1*n2,3006047052680396800ull,2075ull);
    n1 = {16000000155ull,4100250000ull};
    n2 = {24000155000ull,4000500250ull};
    check_u128(n1*n2,15067602245832992680ull,14840687569151125842ull);
    assert(n1*n2 == n2*n1);
    n1 = {75,50};
    check_u128(n1*100,7500,5000);
    check_u128(100*n1,7500,5000);
    n1 = {1000000ull,1000000000ull};
    n1 *= 1000000ull;
    check_u128(n1,1000000000000ull,1000000000000000ull);
    n1.set<1>(1000000ull);
    n1 *= 1000000000ull;
    check_u128(n1,3875820019684212736ull,1000000000000054);
    n1 *= 1000000ull;
    check_u128(n1,11515845246265065472ull,3875820019738422844ull);
    check_u128(1000000000039ull*n1,13270102349315047424ull,6542554618405566464ull);
    // /
    n1 = {18361488253670720149ull,3245106884460086638ull};
    n2 = {15206061505931127463ull,270270ull};
    check_u128(n1/n2,12006870858509ull,0ull);
    check_u128(n2/n1,0,0);
    n1 = n2 - 1;
    check_u128(n2/n1,1,0);
    ++n1;
    check_u128(n2/n1,1,0);
    ++n1;
    check_u128(n2/n1,0,0);
    n1 = uint128_t(1) << 127;
    n2 = (uint128_t(1) << 61) - 1;
    check_u128(n1/n2,32,4);
    n1.set<1>(15000000000000ull);
    m = 80000000000ull;
    check_u128(n1/m,9223372036854775808ull,187ull);
    m = 21000000000000000ull;
    check_u128(n1/m,13176245766935394ull,0ull);
    static_assert(std::is_same<decltype(m/n1),uint64_t>::value);
    static_assert(std::is_same<decltype(n1/m),uint128_t>::value);
    assert((1ull<<63)/n1 == 0);
    n1 = {1ull<<60};
    assert((1ull<<63)/n1 == 8);
    assert((1ull<<63)/(n1+1) == 7);
    // %
    n1 = {1709625502996782229ull,1570352452579947ull};
    n2 = {16973066792291431840ull,24935ull};
    check_u128(n1%n2,1316845146740855797ull,22524);
    check_u128(n2%n1,n2.get<0>(),n2.get<1>());
    check_u128(n1%n1,0,0);
    check_u128(n1%(n1+1),n1.get<0>(),n1.get<1>());
    check_u128(n1%(n1-1),1,0);
    static_assert(std::is_same<decltype(n1%m),uint64_t>::value);
    static_assert(std::is_same<decltype(m%n1),uint64_t>::value);
    m = (1ull<<61)-1;
    assert(m%n1 == m);
    assert(m%n2 == m);
    n1 = {(1ull<<31)-1};
    assert(m%n1 == (1ull<<30)-1);
    m = 19846589136158943ull;
    n1 = 9861896489586ull;
    assert(n1%m == n1.get<0>());
    assert(m%n1 == 4453399111911ull);
    n1.set<1>(3);
    assert(n1%m == 7951571414011350ull);
    // <<
    n1 = 1;
    assert(n1 << 0 == 1);
    assert(n1 << 63 == 1ull << 63);
    assert(n1 << 64 == uint128_t(0,1));
    assert(n1 << 127 == uint128_t(0,1ull<<63));
    n1 = {15416247988908425523ull,503378360877312ull};
    n1 <<= 17;
    check_u128(n1,557312134575685632ull,10638576295782493155ull);
    n1 <<= 23;
    check_u128(n1,3999534019174727680ull,7151998602121043452ull);
    n1 <<= 64;
    check_u128(n1,0ull,3999534019174727680ull);
    n1 <<= 32;
    check_u128(n1,0ull,0ull);
    // >>
    n1 = uint128_t(1) << 127;
    assert(n1 >> 0 == n1);
    assert(n1 >> 63 == uint128_t(0,1));
    assert(n1 >> 64 == uint128_t(1ull<<63,0));
    assert(n1 >> 127 == 1);
    n1 = {15416247988908425523ull,503378360877312ull};
    n1 >>= 6;
    check_u128(n1,240878874826694148ull,7865286888708ull);
    n1 >>= 64;
    check_u128(n1,7865286888708ull,0ull);
    n1 >>= 16;
    check_u128(n1,120014753ull,0ull);
    n1 >>= 42;
    check_u128(n1,0ull,0ull);
}

void test_cmp()
{
    ;
}

void test_bit()
{
    ;
}

void test_io()
{
    ;
}

void test_divmodpow()
{
    ;
}

#if 1

int main()
{
    test_ctor();
    test_conv_ints();
    test_conv_floats();
    test_inc_dec();
    test_unary();
    test_arith();
    test_cmp();
    test_bit();
    test_io();
    test_divmodpow();
    //assert(factorial(64).array()[0] == (1ul << 63));
    //assert(factorial(64).array()[0] == (1ull << 63));
    //assert(factorial(128) == uint128_t(1) << 127);
    //assert(factorial(130) == 0);
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
