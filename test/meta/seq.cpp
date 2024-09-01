#include "../../src/meta/seq.hpp"
int main() {}
namespace meta = tkoz::meta;

static_assert(std::is_same_v<meta::seq_range_t<size_t,0,1>,meta::seq<size_t,0>>);
static_assert(std::is_same_v<meta::seq_range_t<size_t,0,2>,meta::seq<size_t,0,1>>);
static_assert(std::is_same_v<meta::seq_range_t<size_t,1,2>,meta::seq<size_t,1>>);
static_assert(std::is_same_v<meta::seq_range_t<size_t,1,3>,meta::seq<size_t,1,2>>);
static_assert(std::is_same_v<meta::seq_range_t<size_t,10,20>,meta::seq<size_t,10,11,12,13,14,15,16,17,18,19>>);
static_assert(std::is_same_v<meta::seq_range_t<int,3,8>,meta::seq<int,3,4,5,6,7>>);

static_assert(std::is_same_v<meta::iseq_range_t<0,6>,meta::iseq<0,1,2,3,4,5>>);
static_assert(std::is_same_v<meta::iseq_range_t<0,16>,meta::iseq<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>>);
// test for recursion depth (default is 900 in gcc)
using depth1 = meta::iseq_range_t<0,1000>;

using s1 = meta::iseq_range_t<5,10>;
using s2 = meta::iseq_range_t<15,20>;
static_assert(std::is_same_v<meta::concat_seq_t<s1>,s1>);
static_assert(std::is_same_v<meta::concat_seq_t<s1,s2>,meta::iseq<5,6,7,8,9,15,16,17,18,19>>);
using s3 = meta::seq_range_t<int,3,7>;
using s4 = meta::seq_range_t<int,10,12>;
using s5 = meta::seq<int,100,101,102>;
static_assert(std::is_same_v<meta::concat_seq_t<s3,s4>,meta::seq<int,3,4,5,6,10,11>>);
static_assert(std::is_same_v<meta::concat_seq_t<s3,s4,s5>,meta::seq<int,3,4,5,6,10,11,100,101,102>>);

static_assert(std::is_same_v<meta::take_seq_beg_t<meta::seq<int,0,1,2,3,4,5,6,7,8,9>,5>,meta::seq<int,0,1,2,3,4>>);
static_assert(std::is_same_v<meta::take_seq_beg_t<meta::iseq<6,11,7,9,4,1>,4>,meta::iseq<6,11,7,9>>);
static_assert(std::is_same_v<meta::take_seq_beg_t<meta::iseq<6,11,7,9,4,1>,6>,meta::iseq<6,11,7,9,4,1>>);
static_assert(std::is_same_v<meta::take_seq_beg_t<meta::iseq<6,11,7,9,4,1>,0>,meta::iseq<>>);

static_assert(std::is_same_v<meta::take_seq_end_t<meta::seq<short,6,6,5,5,4,4>,3>,meta::seq<short,5,4,4>>);
static_assert(std::is_same_v<meta::take_seq_end_t<meta::seq<short,6,6,5,5,4,4>,0>,meta::seq<short>>);
static_assert(std::is_same_v<meta::take_seq_end_t<meta::seq<short,6,6,5,5,4,4>,6>,meta::seq<short,6,6,5,5,4,4>>);
static_assert(std::is_same_v<meta::take_seq_end_t<meta::iseq<0,1,2,3,4,5,6,7,8,9>,5>,meta::iseq_range_t<5,10>>);

static constexpr std::array<int,5> ints1 = {10,20,30,40,50};
static_assert(ints1 == meta::array_v<int,10,20,30,40,50>);
static_assert(ints1 == meta::map_array_f([](int i){return 10*i;},1,2,3,4,5));
static constexpr std::array<size_t,6> ints2 = {1,2,3,4,5,6};
static_assert(ints2 == meta::seq_array_v<size_t,1,2,3,4,5,6>);
static_assert(ints2 == meta::seq_array_v<meta::iseq_range_t<1,7>>);
static_assert(ints1 == meta::array_f(10,20,30,40,50));
static_assert(ints2 == meta::array_f((size_t)1,(size_t)2,(size_t)3,(size_t)4,(size_t)5,(size_t)6));
static constexpr std::array<int,10> ints3 = {0,1,4,9,16,25,36,49,64,81};
static_assert(ints3 == meta::seqmap_array_f([](int i){return i*i;},meta::seq_range_t<int,0,10>()));
// depth testing
static constexpr std::array<size_t,1500> ints4 = meta::seq_array_v<meta::iseq_range_t<10,1510>>;

