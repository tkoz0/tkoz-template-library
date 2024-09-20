
#include <array>
#include <cassert>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../../src/fwnum/uint128_t.hpp"
#include "../test_common.hpp"
#include "../../src/util/tuples.hpp"
using tkoz::uint128_t;
using tkoz::tuple2;
using tkoz::tuple3;
using std::cout;
using std::endl;
using std::array;
using std::vector;
using std::string;
using std::strong_ordering;

bool check_u128(uint128_t n, uint64_t w0, uint64_t w1)
{
    bool ret = n.get<0>() == w0 && n.get<1>() == w1;
    if (!ret)
    {
        printf("expected: %20lu %20lu\n",w0,w1);
        printf("actual:   %20lu %20lu\n",n.get<0>(),n.get<1>());
    }
    assert(ret);
    assert(n.get<0>() == w0 && n.get<1>() == w1);
    return ret;
}

bool check_u128(uint128_t a, uint128_t b)
{
    if (a != b)
    {
        printf("expected: %20lu %20lu\n",b.get<0>(),b.get<1>());
        printf("actual:   %20lu %20lu\n",a.get<0>(),a.get<1>());
    }
    assert(a == b);
    assert(a.get<0>() == b.get<0>() && a.get<1>() == b.get<1>());
    return a == b;
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

vector<tuple2<uint128_t,array<uint64_t,2>>> tests_ctor_u64 =
{
    {uint128_t(0,0),{0,0}},
    {uint128_t(700,-700u),{700,-700u}},
    {uint128_t(2305843009213693951ull,0),{2305843009213693951ull,0}},
    {uint128_t(0,2305843009213693951),{0,2305843009213693951ull}},
    {uint128_t(8618658619856981ull,0),{8618658619856981ull,0}},
    {uint128_t(0,8618658619856981ull),{0,8618658619856981ull}},
    {uint128_t(89,107),{89,107}},
    {uint128_t(1000000000061ull,1000000000063ull),{1000000000061ull,1000000000063ull}}
};

vector<tuple2<uint128_t,array<uint32_t,4>>> tests_ctor_u32 =
{
    {uint128_t(),{0,0,0,0}},
    {uint128_t(913803289215927089ull,26253840113151ull),{5014321u,212761408u,2999999999u,6112u}},
    {uint128_t(1030792151055ull,18446462598732906495ull),{15u,240u,65535u,4294901760u}}
};

vector<tuple2<uint128_t,array<uint16_t,8>>> tests_ctor_u16 =
{
    {uint128_t(),{0,0,0,0,0,0,0,0}},
    {uint128_t(36029071898968080ull,576465150383489280ull),{16,32,64,128,256,512,1024,2048}},
    {uint128_t(424184563502160745ull,1961653989498881103ull),{7017,62144,412,1507,1103,79,12777,6969}}
};

vector<tuple2<uint128_t,array<uint8_t,16>>> tests_ctor_u8 =
{
    {uint128_t(),{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {uint128_t(14478767720495241164ull,5258607149925658115ull),{204,215,130,173,135,234,238,200,3,238,165,112,87,83,250,72}},
    {uint128_t(15716132244525479369ull,15786600516929582318ull),{201,245,0,62,2,235,26,218,238,244,149,118,135,69,21,219}}
};

vector<tuple2<uint128_t,array<bool,128>>> tests_ctor_bool =
{
    {uint128_t(),{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {uint128_t(14346338644655984136ull,4675209317535610437ull),{
    0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,
    0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,
    1,0,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,
    0,1,0,1,1,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0}},
    {uint128_t(7617186964671749594ull,12220001005671563757ull),{
    0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,
    1,1,1,1,0,1,0,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,
    1,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,
    1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1}}
};

void run_tests_ctor()
{
    uint128_t z;
    assert(check_u128(z,0,0));
    assert(check_u128(uint128_t(),0,0));
    for (auto &test : tests_ctor_u64)
    {
        uint128_t &n = test.a;
        auto &w = test.b;
        assert(check_u128(n,uint128_t(w[0],w[1])));
    }
    for (auto &test : tests_ctor_u32)
    {
        uint128_t &n = test.a;
        auto &w = test.b;
        assert(check_u128(n,uint128_t(w[0],w[1],w[2],w[3])));
    }
    for (auto &test : tests_ctor_u16)
    {
        uint128_t &n = test.a;
        auto &w = test.b;
        assert(check_u128(n,uint128_t(w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7])));
    }
    for (auto &test : tests_ctor_u8)
    {
        uint128_t &n = test.a;
        auto &w = test.b;
        assert(check_u128(n,uint128_t(w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10],w[11],w[12],w[13],w[14],w[15])));
    }
    for (auto &test : tests_ctor_bool)
    {
        uint128_t &n = test.a;
        auto &w = test.b;
        assert(check_u128(n,uint128_t(w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10],w[11],w[12],w[13],w[14],w[15],
        w[16],w[17],w[18],w[19],w[20],w[21],w[22],w[23],w[24],w[25],w[26],w[27],w[28],w[29],w[30],w[31],
        w[32],w[33],w[34],w[35],w[36],w[37],w[38],w[39],w[40],w[41],w[42],w[43],w[44],w[45],w[46],w[47],
        w[48],w[49],w[50],w[51],w[52],w[53],w[54],w[55],w[56],w[57],w[58],w[59],w[60],w[61],w[62],w[63],
        w[64],w[65],w[66],w[67],w[68],w[69],w[70],w[71],w[72],w[73],w[74],w[75],w[76],w[77],w[78],w[79],
        w[80],w[81],w[82],w[83],w[84],w[85],w[86],w[87],w[88],w[89],w[90],w[91],w[92],w[93],w[94],w[95],
        w[96],w[97],w[98],w[99],w[100],w[101],w[102],w[103],w[104],w[105],w[106],w[107],w[108],w[109],w[110],w[111],
        w[112],w[113],w[114],w[115],w[116],w[117],w[118],w[119],w[120],w[121],w[122],w[123],w[124],w[125],w[126],w[127])));
    }
    // initializer list
    uint128_t n1 = {128,511};
    check_u128(n1,128,511);
    uint128_t n2{257};
    check_u128(n2,257,0);
    n2 = {};
    check_u128(n2,0,0);
    n1 = {9581689465817586198ull,4958619846981639ull};
    check_u128(n1,9581689465817586198ull,4958619846981639ull);
    uint128_t n3{};
    check_u128(n3,0,0);
}

void run_tests_conv_ints()
{
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    uint128_t n1;
    check_u128(n1,0,0);
    // bool
    n1 = true;
    check_u128(n1,1,0);
    n1 = false;
    check_u128(n1,0,0);
    assert(bool(uint128_t(false)) == false);
    assert(bool(uint128_t(true)) == true);
    assert(bool(uint128_t(0,1)) == true);
    assert(bool(uint128_t(0,-1)) == true);
    assert(bool(uint128_t(1,0)) == true);
    assert(bool(uint128_t(-1,0)) == true);
    assert(bool(uint128_t()) == false);
    // int8_t
    i8 = -5;
    n1 = i8;
    check_u128(n1,-5ull,-1ull);
    assert(int8_t(n1) == i8);
    i8 = 73;
    n1 = i8;
    check_u128(n1,73,0);
    assert(int8_t(n1) == i8);
    // int16_t
    i16 = -43;
    n1 = i16;
    check_u128(n1,-43ull,-1ull);
    assert(int16_t(n1) == i16);
    i16 = 27001;
    n1 = i16;
    check_u128(n1,27001,0);
    assert(int16_t(n1) == i16);
    // int32_t
    i32 = 99;
    n1 = i32;
    check_u128(n1,99ull,0ull);
    assert(int32_t(n1) == i32);
    i32 = -16830123;
    n1 = i32;
    check_u128(n1,-16830123,-1);
    assert(int32_t(n1) == i32);
    // int64_t
    i64 = 10000000000ll;
    n1 = i64;
    check_u128(n1,10000000000ull,0ull);
    assert(int64_t(n1) == i64);
    i64 = -17000456000123000ll;
    n1 = i64;
    check_u128(n1,-17000456000123000ll,-1);
    assert(int64_t(n1) == i64);
    // uint8_t
    u8 = 63;
    n1 = u8;
    check_u128(n1,63ull,0ull);
    assert(uint8_t(n1) == u8);
    u8 = 179;
    n1 = u8;
    check_u128(n1,179,0);
    assert(uint8_t(n1) == u8);
    // uint16_t
    u16 = 12000;
    n1 = u16;
    check_u128(n1,12000ull,0ull);
    assert(uint16_t(n1) == u16);
    u16 = 55001;
    n1 = u16;
    check_u128(n1,55001,0);
    assert(uint16_t(n1) == u16);
    // uint32_t
    u32 = 2147483648;
    n1 = u32;
    check_u128(n1,2147483648ull,0ull);
    assert(uint32_t(n1) == u32);
    u32 = 999999999;
    n1 = u32;
    check_u128(n1,999999999,0);
    assert(uint32_t(n1) == u32);
    // uint64_t
    u64 = 1000000000039ull;
    n1 = u64;
    check_u128(n1,1000000000039ull,0ull);
    assert(uint64_t(n1) == u64);
    u64 = 56001002003004005ull;
    n1 = u64;
    check_u128(n1,56001002003004005ull,0);
    // sll_t and ull_t
    tkoz::sll_t sll = 2000000000003ll;
    tkoz::ull_t ull = 2000000000123ull;
    n1 = sll;
    check_u128(n1,2000000000003ull,0ull);
    assert(tkoz::sll_t(n1) == sll);
    n1 = ull;
    check_u128(n1,2000000000123ull,0ull);
    assert(tkoz::ull_t(n1) == ull);
    sll = -15016017018019ll;
    ull = 15016017018019ull;
    n1 = sll;
    check_u128(n1,-15016017018019ll,-1);
    assert(tkoz::sll_t(n1) == sll);
    n1 = ull;
    check_u128(n1,15016017018019ull,0);
    assert(tkoz::ull_t(n1) == ull);
}

vector<tuple2<float,uint128_t>> tests_fp32_u128 =
{
    {0.0f,0},
    {-0.0f,0},
    {1.0f,1},
    {-1.0f,-1},
    {1.9f,1},
    {-1.9f,-1},
    {20.999999f,20},
    {1000000007.0f,1000000000},
    {1000000033.0f,1000000064},
    {758195681.0f,758195712},
    {1e10,10000000000ull},
    {3.1415926535*1000,3141},
    {894615894368913498.0f,894615917953024000ull},
    {75686864781894687561963673.0f,uint128_t(4611686018427387904ull,4102993ull)},
    {18485169561986598136596134985613489.0f,uint128_t(0,1002083046129664ull)},
    {0.01f,0},
    {-0.09f,0},
    {-25587519846829764586495.0f,-uint128_t(1884756444054552576ull,1387ull)},
    {1e-40,0},
    {-1e-42,0},
    {tkoz::_2pow_fp32(64),uint128_t(0,1)},
    {tkoz::_2pow_fp32(64,true),uint128_t(0,-1)},
    {tkoz::_2pow_fp32(127),uint128_t(0,1ull<<63)},
    {std::numeric_limits<float>::max(),uint128_t(0,((1ull<<24)-1)<<40)},
    {std::numeric_limits<float>::denorm_min(),0}
};

vector<tuple2<double,uint128_t>> tests_fp64_u128 =
{
    {0.0,0},
    {-0.0,0},
    {1e-10,0},
    {1e-290,0},
    {-1e-320,0},
    {-1.0,-1},
    {1.0,1},
    {3.9,3},
    {-4.9,-4},
    {1152921504606847103.0,1152921504606846976ull},
    {1152921504606847105.0,1152921504606847232ull},
    {1e19,10000000000000000000ull},
    {1e27,uint128_t(11515845259552620544ull,54210108ull)},
    {1e35,uint128_t(0,5421010862427522ull)},
    {1e40,uint128_t(0,7145508105175236608ull)},
    {1e60,0},
    {1.85618415e55,0},
    {86581346859619836589134659.0,uint128_t(4023161871220604928ull,4693584ull)},
    {tkoz::_2pow_fp64(64),uint128_t(0,1)},
    {tkoz::_2pow_fp64(64,true),uint128_t(0,-1)},
    {8.5862986598649823e209,0},
    {std::numeric_limits<double>::max(),0},
    {std::numeric_limits<double>::min(),0},
    {std::numeric_limits<double>::denorm_min(),0}
};

vector<tuple2<uint128_t,float>> tests_u128_fp32 =
{
    {0,0.0f},
    {1000000000039ull,999999995904.0f},
    {uint128_t(1)<<127,1.7014118e38},
    {uint128_t((1<<24)-1)<<104,std::numeric_limits<float>::max()},
    {uint128_t((1<<25)-1)<<103,std::numeric_limits<float>::infinity()},
    {uint128_t(0,1),tkoz::_2pow_fp32(64)},
    {1,1.0f},
    {2,2.0f},
    {358268946189,358268960768.0f},
    {uint128_t(2429093157220639448ull,22530451ull),4.15613466e26},
    {uint128_t(5560142162894520320ull,532107365719316355ull),9.8156484e36},
    {-1,std::numeric_limits<float>::infinity()},
    {8785168,8785168.0},
    {uint128_t(1ull<<40,1),tkoz::_2pow_fp32(64)},
    {uint128_t(-1,1ull<<26),tkoz::_2pow_fp32(90)},
    {1000000000000000003ull,999999984306749440.0f}
};

vector<tuple2<uint128_t,double>> tests_u128_fp64 =
{
    {0,0.0},
    {1,1.0},
    {2,2.0},
    {1000000000039ull,1000000000039.0},
    {-1,3.402823669209385e38},
    {uint128_t(0,1ull<<63),tkoz::_2pow_fp64(127)},
    {uint128_t(0,1),tkoz::_2pow_fp64(64)},
    {uint128_t(0,-1),3.402823669209385e38},
    {uint128_t(3458925926657767873ull,5057027489140638645ull),9.328569186589137e37},
    {uint128_t(17396962758215522735ull,378719ull),6.986149865813965e24},
    {11386581346589143686ull,1.1386581346589143e19},
    {uint128_t(0,7),tkoz::_2pow_fp64(64)+tkoz::_2pow_fp64(65)+tkoz::_2pow_fp64(66)},
    {1000000000000000003ull,1e18}
};

void run_tests_conv_floats()
{
    for (auto &test : tests_fp32_u128)
    {
        float f = test.a;
        uint128_t n = test.b;
        if (n != f || f != n)
        {
            printf("float: %f with bits %u\n",f,tkoz::_fp32_to_bits(f));
            assert(check_u128(uint128_t(f),n));
        }
    }
    for (auto &test : tests_fp64_u128)
    {
        double f = test.a;
        uint128_t n = test.b;
        if (n != f || f != n)
        {
            printf("float: %lf with bits %lu\n",f,tkoz::_fp64_to_bits(f));
            assert(check_u128(uint128_t(f),n));
        }
    }
    for (auto &test : tests_u128_fp32)
    {
        uint128_t n = test.a;
        float f = test.b;
        if (float(n) != f)
        {
            printf("number: %20lu %20lu\n",n.get<0>(),n.get<1>());
            float f = float(n);
            printf("converted: %f with bits %u\n",f,tkoz::_fp32_to_bits(f));
            printf("expected:  %f with bits %u\n",f,tkoz::_fp32_to_bits(f));
            assert(0);
        }
    }
    for (auto &test : tests_u128_fp64)
    {
        uint128_t n = test.a;
        double f = test.b;
        if (double(n) != f)
        {
            printf("number: %20lu %20lu\n",n.get<0>(),n.get<1>());
            double f = double(n);
            printf("converted: %lf with bits %u\n",f,tkoz::_fp32_to_bits(f));
            printf("expected:  %lf with bits %u\n",f,tkoz::_fp32_to_bits(f));
            assert(0);
        }
    }
}

vector<tuple2<uint128_t,uint128_t>> tests_inc =
{
    {-2,-1},
    {-1,0},
    {0,1},
    {1,2},
    {{-2ull,25},{-1ull,25}},
    {{-1ull,25},{0,26}},
    {{0,26},{1,26}},
    {{1,26},{2,26}},
    {{15000000,27},{15000001,27}}
};

vector<tuple2<uint128_t,uint128_t>> tests_dec =
{
    {2,1},
    {1,0},
    {0,-1},
    {-1,-2},
    {{2,66},{1,66}},
    {{1,66},{0,66}},
    {{0,66},{-1ull,65}},
    {{-1ull,65},{-2ull,65}},
    {{61000000000ull,80},{60999999999ull,80}}
};

void run_tests_inc_dec()
{
    for (auto &test : tests_inc)
    {
        uint128_t a = test.a;
        assert(check_u128(++a,test.b));
        assert(check_u128(a,test.b));
        a = test.a;
        assert(check_u128(a++,test.a));
        assert(check_u128(a,test.b));
        static_assert(std::is_same<uint128_t&,decltype(++a)>::value);
        static_assert(std::is_same<uint128_t,decltype(a++)>::value);
    }
    for (auto &test : tests_dec)
    {
        uint128_t a = test.a;
        assert(check_u128(--a,test.b));
        assert(check_u128(a,test.b));
        a = test.a;
        assert(check_u128(a--,test.a));
        assert(check_u128(a,test.b));
        static_assert(std::is_same<uint128_t&,decltype(--a)>::value);
        static_assert(std::is_same<uint128_t,decltype(a--)>::value);
    }
}

vector<tuple2<uint128_t,uint128_t>> tests_inv =
{
    {{778626958168965ull,915861347186786128ull},{18445965446751382650ull,17530882726522765487ull}},
    {{0,0},{-1ull,-1ull}}
};

vector<tuple2<uint128_t,uint128_t>> tests_pos =
{
    {{0,0},{0,0}},
    {{64,0},{64,0}},
    {{0,64},{0,64}}
};

vector<tuple2<uint128_t,uint128_t>> tests_neg =
{
    {{778626958168965ull,915861347186786128ull},{18445965446751382651ull,17530882726522765487ull}},
    {{0,0},{0,0}},
    {{1,0},{-1ull,-1ull}}
};

vector<tuple2<uint128_t,bool>> tests_not =
{
    {0,true},
    {1,false},
    {{1,0},false},
    {{0,1},false}
};

void run_tests_unary()
{
    uint128_t n;
    static_assert(std::is_same_v<uint128_t,decltype(~n)>);
    static_assert(std::is_same_v<uint128_t,decltype(+n)>);
    static_assert(std::is_same_v<uint128_t,decltype(-n)>);
    static_assert(std::is_same_v<bool,decltype(!n)>);
    for (auto &test : tests_inv)
        assert(check_u128(~test.a,test.b));
    for (auto &test : tests_pos)
        assert(check_u128(+test.a,test.b));
    for (auto &test : tests_neg)
        assert(check_u128(-test.a,test.b));
    for (auto &test : tests_not)
        if ((!test.a) != test.b)
        {
            printf("not fail: %20lu %20lu\n",test.a.get<0>(),test.a.get<1>());
            assert(0);
        }
}

// here, 'U' means uint128_t and 'u' means uint64_t (for operand types)

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_add_UU =
{
    {{5000,6000000},{7000,8000000},{12000,14000000}},
    {{890,49675},{-1ull,-1ull},{889,49675}},
    {{890,49675},{-1ull},{889,49676}},
    {{10000000000000000000ull,10000000000000000000ull},{10000000000000000000ull,10000000000000000000ull},{1553255926290448384ull,1553255926290448385ull}},
    {{6489624861868954638ull,14093465918658998643ull},{7285691845918634986ull,6109561634891568641ull},{13775316707787589624ull,1756283479841015668ull}}
};

vector<tuple3<uint128_t,uint64_t,uint128_t>> tests_add_Uu =
{
    {{5000,6000000},500,{5500,6000000}},
    {{1ull<<63},1ull<<63,{0,1}},
    {{5000,6000000},-1ull,{4999,6000001}},
    {{},0,{}}
};

vector<tuple3<uint64_t,uint128_t,uint128_t>> tests_add_uU =
{
    {500,{7000,8000000},{7500,8000000}},
    {1ull<<63,{1ull<<63},{0,1}},
    {-1ull,{7000,8000000},{6999,8000001}},
    {0,{},{}}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_sub_UU =
{
    {{5000,6000000},{7000,8000000},{-2000ull,-2000001ull}},
    {{7000,8000000},{5000,6000000},{2000,2000000}},
    {{13874112545481479920ull,4615318442884491913ull},{14507363812416151806ull,1028115828251952345ull},{17813492806774879730ull,3587202614632539567ull}},
    {{10744852760760557535ull,27025197111ull},{10744852760760557534ull,27025197110ull},{1,1}}
};

vector<tuple3<uint128_t,uint64_t,uint128_t>> tests_sub_Uu =
{
    {0,1,{-1ull,-1ull}},
    {1,0,1},
    {{5000,6000000},4000,{1000,6000000}},
    {{5000,6000000},6000,{-1000ull,5999999}}
};

vector<tuple3<uint64_t,uint128_t,uint128_t>> tests_sub_uU =
{
    {0,{1,1},{-1ull,-2ull}},
    {600,{599,0},{1,0}},
    {600,{601,0},{-1ull,-1ull}},
    {750,{700,7000},{50,-7000ull}}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_mul_UU =
{
    {10000000000ull,10000000000ull,{7766279631452241920ull,5ull}},
    {{-1ull},{-1ull},{1,18446744073709551614ull}},
    {660000000000ull,58000000000ull,{3006047052680396800ull,2075ull}},
    {{16000000155ull,4100250000ull},{24000155000ull,4000500250ull},{15067602245832992680ull,14840687569151125842ull}},
    {0,0,0},
    {{0,1},{0,1},0},
    {{1,0},{1,0},{1,0}},
    {{98168489516389ull,5981894918365ull},0,0},
    {{10912442324333365785ull,4964749849579962886ull},{13477537699412120217ull,15432475005582382ull},{1299908576727059185ull,9616282453013265286ull}}
};

vector<tuple3<uint128_t,uint64_t,uint128_t>> tests_mul_Uu =
{
    {{75,50},100,{7500,5000}},
    {{1648596134895689ull,41986534},0,0},
    {{5230725515093458174ull,508569526262872ull},123456789,{12244549545089033942ull,12090612831777895944ull}}
};

vector<tuple3<uint64_t,uint128_t,uint128_t>> tests_mul_uU =
{
    {100,{75,50},{7500,5000}},
    {0,{1896518943659ull,5916},0},
    {9876543210u,{5136287352436767740ull,50879542195396ull},{8803178291587218520ull,6241685927711501509ull}}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_div_UU =
{
    {{11791420680597925785ull,26442762239677822ull},{73,0},{161526310693122271ull,362229619721614ull}},
    {{11791420680597925785ull,26442762239677822ull},{2359861848688236511ull,0},{206699755711728963ull,0}},
    {{11791420680597925785ull,26442762239677822ull},{12421768102059824260ull,442},{59734249024021ull,0}},
    {{391763781272346594ull,46782487223ull},{391763781272346593ull,46782487223ull},1},
    {{391763781272346593ull,46782487223ull},{391763781272346593ull,46782487223ull},1},
    {{391763781272346592ull,46782487223ull},{391763781272346593ull,46782487223ull},0},
    {98652846981345ull,98652846981344ull,1},
    {98652846981345ull,98652846981345ull,1},
    {98652846981345ull,98652846981346ull,0},
    {519586189365891ull,58368ull,8901901544ull},
    {519586189365891ull,{0,58368ull},0},
    {{0,0},{9856348618923586ull,49138651945981684ull},0}
};

vector<tuple3<uint128_t,uint64_t,uint128_t>> tests_div_Uu =
{
    {{10982017663836653174ull,8044},43878265,{3382006816964696ull,0}},
    {{6624101342368053831ull,2323247329959ull},867575572547457756ull,{49397828006902ull,0}},
    {{6624101342368053831ull,2323247329959ull},26895108,{14407409191359791249ull,86381}},
    {13648156348956198346ull,26895108,507458692820ull},
    {13648156348956198346ull,13648156348956198346ull,1ull},
    {13648156348956198346ull,-1ull,0ull}
};

vector<tuple3<uint64_t,uint128_t,uint64_t>> tests_div_uU =
{
    {10000000000000000000ull,9999999999999999999ull,1},
    {10000000000000000000ull,10000000000000000000ull,1},
    {10000000000000000000ull,10000000000000000001ull,0},
    {0,{938465981639ull,95183},0},
    {-1ull,{0,1},0}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_mod_UU =
{
    {{1709625502996782229ull,1570352452579947ull},{16973066792291431840ull,24935ull},{1316845146740855797ull,22524}},
    {{16973066792291431840ull,24935ull},{1709625502996782229ull,1570352452579947ull},{16973066792291431840ull,24935ull}},
    {{2986459816348956189ull,98361895689986ull},{2986459816348956189ull,98361895689986ull},0},
    {{2986459816348956190ull,98361895689986ull},{2986459816348956189ull,98361895689986ull},1},
    {{2986459816348956189ull,98361895689985ull},{2986459816348956189ull,98361895689986ull},{2986459816348956189ull,98361895689985ull}},
    {{1709625502996782229ull,1570352452579947ull},16,5},
    {{1709625502996782229ull,1570352452579947ull},74658986324526ull,3058550422369ull},
    {986293845891364ull,{1709625502996782229ull,1570352452579947ull},986293845891364ull},
    {986293845891364ull,1,0}
};

vector<tuple3<uint128_t,uint64_t,uint64_t>> tests_mod_Uu =
{
    {9451689346589163489ull,186438561536893ull,30914835961ull},
    {39586138,186438561536893ull,39586138},
    {{1709625502996782229ull,1570352452579947ull},16,5},
    {{1709625502996782229ull,1570352452579947ull},74658986324526ull,3058550422369ull},
    {0,4185683465189346ull,0}
};

vector<tuple3<uint64_t,uint128_t,uint64_t>> tests_mod_uU =
{
    {4356913486581963489ull,{0,1},4356913486581963489ull},
    {4356913486581963489ull,{4356913486581963489ull,0},0ull},
    {9451689346589163489ull,186438561536893ull,30914835961ull},
    {39586138,186438561536893ull,39586138},
    {0,{196581689986358ull,194386518964138865ull},0}
};

void run_tests_arith()
{
    uint128_t n1,n2;
    uint64_t m;
    static_assert(std::is_same_v<decltype(n1+n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1+m),uint128_t>);
    static_assert(std::is_same_v<decltype(m+n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1-n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1-m),uint128_t>);
    static_assert(std::is_same_v<decltype(m-n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1*n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1*m),uint128_t>);
    static_assert(std::is_same_v<decltype(m*n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1/n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1/m),uint128_t>);
    static_assert(std::is_same_v<decltype(m/n2),uint64_t>);
    static_assert(std::is_same_v<decltype(n1%n2),uint128_t>);
    static_assert(std::is_same_v<decltype(n1%m),uint64_t>);
    static_assert(std::is_same_v<decltype(m%n2),uint64_t>);
    for (auto &test : tests_add_UU)
        assert(check_u128(test.a+test.b,test.c) && check_u128(test.b+test.a,test.c));
    for (auto &test : tests_add_Uu)
        assert(check_u128(test.a+test.b,test.c) && check_u128(test.b+test.a,test.c));
    for (auto &test : tests_add_uU)
        assert(check_u128(test.a+test.b,test.c) && check_u128(test.b+test.a,test.c));
    for (auto &test : tests_sub_UU)
        assert(check_u128(test.a-test.b,test.c) && check_u128(test.b-test.a,-test.c));
    for (auto &test : tests_sub_Uu)
        assert(check_u128(test.a-test.b,test.c) && check_u128(test.b-test.a,-test.c));
    for (auto &test : tests_sub_uU)
        assert(check_u128(test.a-test.b,test.c) && check_u128(test.b-test.a,-test.c));
    for (auto &test : tests_mul_UU)
        assert(check_u128(test.a*test.b,test.c) && check_u128(test.b*test.a,test.c));
    for (auto &test : tests_mul_Uu)
        assert(check_u128(test.a*test.b,test.c) && check_u128(test.b*test.a,test.c));
    for (auto &test : tests_mul_uU)
        assert(check_u128(test.a*test.b,test.c) && check_u128(test.b*test.a,test.c));
    for (auto &test : tests_div_UU)
        assert(check_u128(test.a/test.b,test.c));
    for (auto &test : tests_div_Uu)
        assert(check_u128(test.a/test.b,test.c));
    for (auto &test : tests_div_uU)
        assert(check_u128(test.a/test.b,test.c));
    for (auto &test : tests_mod_UU)
        assert(check_u128(test.a%test.b,test.c));
    for (auto &test : tests_mod_Uu)
        assert(check_u128(test.a%test.b,test.c));
    for (auto &test : tests_mod_uU)
        assert(check_u128(test.a%test.b,test.c));
}

vector<tuple3<uint128_t,uint32_t,uint128_t>> tests_shl =
{
    {1,0,1},
    {1,63,1ull<<63},
    {1,64,{0,1}},
    {1,127,{0,1ull<<63}},
    {{15416247988908425523ull,503378360877312ull},17,{557312134575685632ull,10638576295782493155ull}},
    {{15416247988908425523ull,503378360877312ull},40,{3999534019174727680ull,7151998602121043452ull}},
    {{15416247988908425523ull,503378360877312ull},64,{0,15416247988908425523ull}},
    {{15416247988908425523ull,503378360877312ull},84,{0,4458497076605485056ull}},
    {{15416247988908425523ull,503378360877312ull},100,{0,14085028931480584192ull}},
    {{15416247988908425523ull,503378360877312ull},127,{0,1ull<<63}},
    {{15416247988908425524ull,503378360877312ull},126,0},
    {{15416247988908425524ull,503378360877312ull},124,{0,1ull<<62}}
};

vector<tuple3<uint128_t,uint32_t,uint128_t>> tests_shr =
{
    {{0,1ull<<63},0,{0,1ull<<63}},
    {{0,1ull<<63},63,{0,1}},
    {{0,1ull<<63},64,{1ull<<63,0}},
    {{0,1ull<<63},127,1},
    {{15416247988908425523ull,503378360877312ull},6,{240878874826694148ull,7865286888708ull}},
    {{15416247988908425523ull,503378360877312ull},64,{503378360877312ull,0}},
    {{15416247988908425523ull,503378360877312ull},70,{7865286888708ull,0ull}},
    {{15416247988908425523ull,503378360877312ull},86,{120014753ull,0ull}},
    {{15416247988908425523ull,503378360877312ull},110,7},
    {{15416247988908425523ull,503378360877312ull},112,1},
    {{15416247988908425523ull,503378360877312ull},113,0}
};

void run_tests_shift()
{
    uint128_t n;
    uint32_t s;
    static_assert(std::is_same_v<decltype(n<<s),uint128_t>);
    static_assert(std::is_same_v<decltype(n>>s),uint128_t>);
    for (auto &test : tests_shl)
        assert(check_u128(test.a<<test.b,test.c));
    for (auto &test : tests_shr)
        assert(check_u128(test.a>>test.b,test.c));
}

vector<tuple3<uint128_t,uint128_t,bool>> tests_lt =
{
    {0,0,false},
    {0,1,true},
    {1,0,false},
    {-1,1,false},
    {1,-1,true},
    {1,1,false},
    {{50,100},{51,100},true},
    {{51,100},{50,100},false},
    {{50,100},{50,100},false},
    {{190,274},{190,275},true},
    {{190,275},{190,274},false},
    {{190,275},{190,275},false}
};

vector<tuple3<uint128_t,uint128_t,bool>> tests_gt =
{
    {0,0,false},
    {0,1,false},
    {1,0,true},
    {-1,1,true},
    {1,-1,false},
    {1,1,false},
    {{50,100},{51,100},false},
    {{51,100},{50,100},true},
    {{50,100},{50,100},false},
    {{190,274},{190,275},false},
    {{190,275},{190,274},true},
    {{190,275},{190,275},false}
};

vector<tuple3<uint128_t,uint128_t,bool>> tests_le =
{
    {0,0,true},
    {0,1,true},
    {1,0,false},
    {-1,1,false},
    {1,-1,true},
    {1,1,true},
    {{50,100},{51,100},true},
    {{51,100},{50,100},false},
    {{50,100},{50,100},true},
    {{190,274},{190,275},true},
    {{190,275},{190,274},false},
    {{190,275},{190,275},true}
};

vector<tuple3<uint128_t,uint128_t,bool>> tests_ge =
{
    {0,0,true},
    {0,1,false},
    {1,0,true},
    {-1,1,true},
    {1,-1,false},
    {1,1,true},
    {{50,100},{51,100},false},
    {{51,100},{50,100},true},
    {{50,100},{50,100},true},
    {{190,274},{190,275},false},
    {{190,275},{190,274},true},
    {{190,275},{190,275},true}
};

vector<tuple3<uint128_t,uint128_t,bool>> tests_eq =
{
    {0,0,true},
    {0,1,false},
    {1,0,false},
    {-1,1,false},
    {1,-1,false},
    {1,1,true},
    {{50,100},{51,100},false},
    {{51,100},{50,100},false},
    {{50,100},{50,100},true},
    {{190,274},{190,275},false},
    {{190,275},{190,274},false},
    {{190,275},{190,275},true}
};

vector<tuple3<uint128_t,uint128_t,bool>> tests_ne =
{
    {0,0,false},
    {0,1,true},
    {1,0,true},
    {-1,1,true},
    {1,-1,true},
    {1,1,false},
    {{50,100},{51,100},true},
    {{51,100},{50,100},true},
    {{50,100},{50,100},false},
    {{190,274},{190,275},true},
    {{190,275},{190,274},true},
    {{190,275},{190,275},false}
};

const auto so_eq = strong_ordering::equal;
const auto so_gt = strong_ordering::greater;
const auto so_lt = strong_ordering::less;

vector<tuple3<uint128_t,uint128_t,strong_ordering>> tests_3w =
{
    {0,0,so_eq},
    {0,1,so_lt},
    {1,0,so_gt},
    {-1,1,so_gt},
    {1,-1,so_lt},
    {1,1,so_eq},
    {{50,100},{51,100},so_lt},
    {{51,100},{50,100},so_gt},
    {{50,100},{50,100},so_eq},
    {{190,274},{190,275},so_lt},
    {{190,275},{190,274},so_gt},
    {{190,275},{190,275},so_eq}
};

void run_tests_cmp()
{
    uint128_t a,b;
    static_assert(std::is_same_v<bool,decltype(a<b)>);
    static_assert(std::is_same_v<bool,decltype(a>b)>);
    static_assert(std::is_same_v<bool,decltype(a<=b)>);
    static_assert(std::is_same_v<bool,decltype(a>=b)>);
    static_assert(std::is_same_v<bool,decltype(a==b)>);
    static_assert(std::is_same_v<bool,decltype(a!=b)>);
    static_assert(std::is_same_v<strong_ordering,decltype(a<=>b)>);
    for (auto &test : tests_lt)
        if ((test.a < test.b) != test.c || (test.a >= test.b) == test.c)
        {
            printf("lt fail: %20lu %20lu < %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_gt)
        if ((test.a > test.b) != test.c || (test.a <= test.b) == test.c)
        {
            printf("gt fail: %20lu %20lu > %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_le)
        if ((test.a <= test.b) != test.c || (test.a > test.b) == test.c)
        {
            printf("le fail: %20lu %20lu <= %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_ge)
        if ((test.a >= test.b) != test.c || (test.a < test.b) == test.c)
        {
            printf("ge fail: %20lu %20lu >= %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_eq)
        if ((test.a == test.b) != test.c || (test.a != test.b) == test.c)
        {
            printf("eq fail: %20lu %20lu == %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_ne)
        if ((test.a != test.b) != test.c || (test.a == test.b) == test.c)
        {
            printf("ne fail: %20lu %20lu != %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    for (auto &test : tests_3w)
        if ((test.a <=> test.b) != test.c)
        {
            printf("3w fail: %20lu %20lu <=> %20lu %20lu\n",test.a.get<0>(),test.a.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
}

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_and =
{
    {0,0,0},
    {{0xF075,0x1468},{0x6D39,0x81AB},{0x6031,0x0028}},
    {14722986639237902741ull,15540288497471672345ull,14123853602564886545ull},
    {{17126818370297690416ull,5422033984243549132ull},{9651633835398074024ull,8187814354070456369ull},{9628745000909670432ull,4693002626259140608ull}}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_or =
{
    {0,0,0},
    {{0xF075,0x1468},{0x6D39,0x81AB},{0xFD7D,0x95EB}},
    {14722986639237902741ull,15540288497471672345ull,16139421534144688541ull},
    {{17126818370297690416ull,5422033984243549132ull},{9651633835398074024ull,8187814354070456369ull},{17149707204786094008ull,8916845712054864893ull}}
};

vector<tuple3<uint128_t,uint128_t,uint128_t>> tests_xor =
{
    {0,0,0},
    {{0xF075,0x1468},{0x6D39,0x81AB},{0x9D4C,0x95C3}},
    {14722986639237902741ull,15540288497471672345ull,2015567931579801996ull},
    {{17126818370297690416ull,5422033984243549132ull},{9651633835398074024ull,8187814354070456369ull},{7520962203876423576ull,4223843085795724285ull}}
};

void run_tests_bit()
{
    uint128_t a,b;
    static_assert(std::is_same_v<uint128_t,decltype(a&b)>);
    static_assert(std::is_same_v<uint128_t,decltype(a|b)>);
    static_assert(std::is_same_v<uint128_t,decltype(a^b)>);
    for (auto &test : tests_and)
        assert(check_u128(test.a&test.b,test.c) && check_u128(test.b&test.a,test.c));
    for (auto &test : tests_or)
        assert(check_u128(test.a|test.b,test.c) && check_u128(test.b|test.a,test.c));
    for (auto &test : tests_xor)
        assert(check_u128(test.a^test.b,test.c) && check_u128(test.b^test.a,test.c));
}

vector<tuple2<string,uint128_t>> tests_in =
{
    {"0",0},
    {"1",1},
    {"-1",-1},
    {"-340282366920938463463374607431768211455",1},
    {"10",10},
    {"123456789",123456789},
    {"1111111111111111111111111111111111111",{10255828924854202823ull,60233454026972468ull}},
    {"2305843009213693951",2305843009213693951},
    {"618970019642690137449562111",{-1ull,33554431ull}},
    {"162259276829213363391578010288127",{-1ull,8796093022207ull}},
    {"170141183460469231731687303715884105727",{-1ull,9223372036854775807ull}},
    {"782786248960173099269845268286417344",{9661079823431510464ull,42434927585719930ull}}
};

vector<tuple2<uint128_t,string>> tests_out =
{
    {0,"0"},
    {1,"1"},
    {-1,"340282366920938463463374607431768211455"},
    {10,"10"},
    {123456789,"123456789"},
    {{10255828924854202823ull,60233454026972468ull},"1111111111111111111111111111111111111"},
    {2305843009213693951,"2305843009213693951"},
    {{-1ull,33554431ull},"618970019642690137449562111"},
    {{-1ull,8796093022207ull},"162259276829213363391578010288127"},
    {{-1ull,9223372036854775807ull},"170141183460469231731687303715884105727"},
    {{9661079823431510464ull,42434927585719930ull},"782786248960173099269845268286417344"}
};

void run_tests_io()
{
    std::stringstream ss;
    uint128_t ui;
    for (auto &test : tests_in)
    {
        ss.clear();
        ss.str(test.a);
        ss >> ui;
        assert(ss.eof());
        assert(!ss.fail());
        if (ui != test.b)
        {
            printf("stream>> fail: %s\n",test.a.c_str());
            printf("%20lu %20lu != %20lu %20lu\n",ui.get<0>(),ui.get<1>(),test.b.get<0>(),test.b.get<1>());
            assert(0);
        }
    }
    for (auto &test : tests_out)
    {
        ss.clear();
        ss.str("");
        ss << test.a;
        assert(ss.good());
        if (ss.str() != test.b)
        {
            printf("stream<< fail: %20lu %20lu\n",test.a.get<0>(),test.a.get<1>());
            printf("%s != %s\n",ss.str().c_str(),test.b.c_str());
            assert(0);
        }
    }
}

void run_tests_other()
{
    // TODO
}

int main()
{
    run_tests_ctor();
    run_tests_conv_ints();
    run_tests_conv_floats();
    run_tests_inc_dec();
    run_tests_unary();
    run_tests_arith();
    run_tests_shift();
    run_tests_cmp();
    run_tests_bit();
    run_tests_io();
    run_tests_other();
    return 0;
}

#if 0 // some other thing for testing stream operators

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
