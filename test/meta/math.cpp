#include "../../src/meta/math.hpp"
#include <array>
namespace meta = tkoz::meta;
#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

// min

static_assert(meta::min_v<0,0> == 0);
static_assert(meta::min_v<0,1> == 0);
static_assert(meta::min_v<1,0> == 0);
static_assert(meta::min_v<12,11> == 11);
static_assert(meta::min_v<11,12> == 11);
static_assert(meta::min_v<12,12> == 12);
static_assert(meta::min_v<12,13> == 12);
static_assert(meta::min_v<13,12> == 12);

// max

static_assert(meta::max_v<0,0> == 0);
static_assert(meta::max_v<0,1> == 1);
static_assert(meta::max_v<1,0> == 1);
static_assert(meta::max_v<12,11> == 12);
static_assert(meta::max_v<11,12> == 12);
static_assert(meta::max_v<12,12> == 12);
static_assert(meta::max_v<12,13> == 13);
static_assert(meta::max_v<13,12> == 13);

// all

static_assert(meta::all_v<>);
static_assert(meta::all_v<true>);
static_assert(!meta::all_v<false>);
static_assert(!meta::all_v<false,false>);
static_assert(!meta::all_v<false,true>);
static_assert(!meta::all_v<true,false>);
static_assert(meta::all_v<true,true>);
static_assert(!meta::all_v<true,true,true,true,true,false>);
static_assert(meta::all_v<true,true,true,true>);
static_assert(!meta::all_v<false,true,true,true>);

// any

static_assert(!meta::any_v<>);
static_assert(meta::any_v<true>);
static_assert(!meta::any_v<false>);
static_assert(!meta::any_v<false,false>);
static_assert(meta::any_v<true,false>);
static_assert(meta::any_v<false,true>);
static_assert(meta::any_v<true,true>);
static_assert(!meta::any_v<false,false,false,false,false>);
static_assert(meta::any_v<true,false,false,false>);
static_assert(meta::any_v<false,false,false,true>);

// factorial

constexpr size_t tests_factorial[] =
{
    1ull,1ull,2ull,6ull,24ull,120ull,720ull,5040ull,40320ull,362880ull,3628800ull,
    39916800ull,479001600ull,6227020800ull,87178291200ull,1307674368000ull,
    20922789888000ull,355687428096000ull,6402373705728000ull,121645100408832000ull,2432902008176640000ull
};

template <size_t N = 0>
constexpr bool run_factorial() { return meta::factorial_v<N> == tests_factorial[N] && run_factorial<N+1>(); }

template <>
constexpr bool run_factorial<ARRAY_LEN(tests_factorial)>() { return true; }

static_assert(run_factorial());

// fibonacci

constexpr size_t tests_fibonacci[] =
{
    0ull,1ull,1ull,2ull,3ull,5ull,8ull,13ull,21ull,34ull,55ull,89ull,144ull,233ull,377ull,610ull,987ull,1597ull,2584ull,4181ull,6765ull,
    10946ull,17711ull,28657ull,46368ull,75025ull,121393ull,196418ull,317811ull,514229ull,832040ull,
    1346269ull,2178309ull,3524578ull,5702887ull,9227465ull,14930352ull,24157817ull,39088169ull,63245986ull,102334155ull,
    165580141ull,267914296ull,433494437ull,701408733ull,1134903170ull,
    1836311903ull,2971215073ull,4807526976ull,7778742049ull,12586269025ull,
    20365011074ull,32951280099ull,53316291173ull,86267571272ull,139583862445ull,
    225851433717ull,365435296162ull,591286729879ull,956722026041ull,1548008755920ull,
    2504730781961ull,4052739537881ull,6557470319842ull,10610209857723ull,17167680177565ull,
    27777890035288ull,44945570212853ull,72723460248141ull,117669030460994ull,190392490709135ull,
    308061521170129ull,498454011879264ull,806515533049393ull,1304969544928657ull,2111485077978050ull,
    3416454622906707ull,5527939700884757ull,8944394323791464ull,14472334024676221ull,23416728348467685ull,
    37889062373143906ull,61305790721611591ull,99194853094755497ull,160500643816367088ull,259695496911122585ull,
    420196140727489673ull,679891637638612258ull,1100087778366101931ull,1779979416004714189ull,2880067194370816120ull,
    4660046610375530309ull,7540113804746346429ull,12200160415121876738ull
};

template <size_t N = 0>
constexpr bool run_fibonacci() { return meta::fibonacci_v<N> == tests_fibonacci[N] && run_fibonacci<N+1>(); }

template <>
constexpr bool run_fibonacci<ARRAY_LEN(tests_fibonacci)>() { return true; }

static_assert(run_fibonacci());

// gcd

static_assert(meta::gcd_v<1,0> == 1);
static_assert(meta::gcd_v<0,1> == 1);
static_assert(meta::gcd_v<2,4> == 2);
static_assert(meta::gcd_v<2,5> == 1);
static_assert(meta::gcd_v<2,6> == 2);
static_assert(meta::gcd_v<4,2> == 2);
static_assert(meta::gcd_v<5,2> == 1);
static_assert(meta::gcd_v<6,2> == 2);
static_assert(meta::gcd_v<18,15> == 3);
static_assert(meta::gcd_v<18,12> == 6);
static_assert(meta::gcd_v<75,15> == 15);
static_assert(meta::gcd_v<1103,113> == 1);
static_assert(meta::gcd_v<113,1103> == 1);
static_assert(meta::gcd_v<516,3648> == 12);
static_assert(meta::gcd_v<3648,516> == 12);

// permutations

#define TEST_PERMUTATIONS_ROW_SIZE 10

constexpr size_t tests_permutations[][TEST_PERMUTATIONS_ROW_SIZE] =
{
    {1,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0},
    {1,2,2,0,0,0,0,0,0,0},
    {1,3,6,6,0,0,0,0,0,0},
    {1,4,12,24,24,0,0,0,0,0},
    {1,5,20,60,120,120,0,0,0,0},
    {1,6,30,120,360,720,720,0,0,0},
    {1,7,42,210,840,2520,5040,5040,0,0},
    {1,8,56,336,1680,6720,20160,40320,40320,0},
    {1,9,72,504,3024,15120,60480,181440,362880,362880}
};

template <size_t N>
struct run_permutations_n
{
    static_assert(TEST_PERMUTATIONS_ROW_SIZE > 0);
    template <size_t K>
    static constexpr bool run(std::integral_constant<size_t,K>) { return meta::permutations_v<N,K> == tests_permutations[N][K] && run(std::integral_constant<size_t,K+1>()); }
    static constexpr bool run(std::integral_constant<size_t,TEST_PERMUTATIONS_ROW_SIZE>) { return true; }
};

template <size_t N = 0>
constexpr bool run_permutations() { return run_permutations_n<N>::run(std::integral_constant<size_t,0>()) && run_permutations<N+1>(); }

template <>
constexpr bool run_permutations<ARRAY_LEN(tests_permutations)>() { return true; }

static_assert(run_permutations());

// combinations

#define TEST_COMBINATIONS_ROW_SIZE 10

constexpr size_t tests_combinations[][TEST_COMBINATIONS_ROW_SIZE] =
{
    {1,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0},
    {1,2,1,0,0,0,0,0,0,0},
    {1,3,3,1,0,0,0,0,0,0},
    {1,4,6,4,1,0,0,0,0,0},
    {1,5,10,10,5,1,0,0,0,0},
    {1,6,15,20,15,6,1,0,0,0},
    {1,7,21,35,35,21,7,1,0,0},
    {1,8,28,56,70,56,28,8,1,0},
    {1,9,36,84,126,126,84,36,9,1}
};

template <size_t N>
struct run_combinations_n
{
    static_assert(TEST_COMBINATIONS_ROW_SIZE > 0);
    template <size_t K>
    static constexpr bool run(std::integral_constant<size_t,K>) { return meta::combinations_v<N,K> == tests_combinations[N][K] && run(std::integral_constant<size_t,K+1>()); }
    static constexpr bool run(std::integral_constant<size_t,TEST_COMBINATIONS_ROW_SIZE>) { return true; }
};

template <size_t N = 0>
constexpr bool run_combinations() { return run_combinations_n<N>::run(std::integral_constant<size_t,0>()) && run_combinations<N+1>(); }

template <>
constexpr bool run_combinations<ARRAY_LEN(tests_combinations)>() { return true; }

static_assert(run_combinations());

// main function for output or run time tests

#include <iostream>
int main()
{
    using std::cout, std::endl;
    return 0;
}

