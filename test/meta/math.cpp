#include "../../src/meta/math.hpp"
using namespace tkoz::meta;
int main() {}

static_assert(factorial_v<0> == 1);
static_assert(factorial_v<1> == 1);
static_assert(factorial_v<2> == 2);
static_assert(factorial_v<3> == 6);
static_assert(factorial_v<4> == 24);
static_assert(factorial_v<5> == 120);
static_assert(factorial_v<6> == 720);
static_assert(factorial_v<7> == 5040);
static_assert(factorial_v<8> == 40320);
static_assert(factorial_v<9> == 362880);

static_assert(gcd_v<1,0> == 1);
static_assert(gcd_v<2,4> == 2);
static_assert(gcd_v<6,15> == 3);
static_assert(gcd_v<20,52> == 4);
static_assert(gcd_v<24,0> == 24);
static_assert(gcd_v<113,1103> == 1);
static_assert(gcd_v<1103,113> == 1);
static_assert(gcd_v<250,625> == 125);
static_assert(gcd_v<625,250> == 125);

static_assert(fibonacci_v<0> == 0);
static_assert(fibonacci_v<1> == 1);
static_assert(fibonacci_v<2> == 1);
static_assert(fibonacci_v<3> == 2);
static_assert(fibonacci_v<4> == 3);
static_assert(fibonacci_v<5> == 5);
static_assert(fibonacci_v<6> == 8);
static_assert(fibonacci_v<7> == 13);
static_assert(fibonacci_v<8> == 21);
static_assert(fibonacci_v<9> == 34);
