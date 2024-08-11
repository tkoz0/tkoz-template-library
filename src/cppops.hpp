/*
Functions for the operators
*/

#pragma once

#include "util/cpp.hpp"

namespace tkoz
{

// unary increment/decrement

// `++var`
template <typename T> auto op_preinc (T &a) -> decltype(++a) { return ++a; }
// `var++`
template <typename T> auto op_postinc(T &a) -> decltype(a++) { return a++; }
// `--var`
template <typename T> auto op_predec (T &a) -> decltype(--a) { return --a; }
// `var--`
template <typename T> auto op_postdec(T &a) -> decltype(a--) { return a--; }

// unary logic/bit

// `~var`
template <typename T> auto op_inv(const T &a) -> decltype(~a) { return ~a; }
// `!var`
template <typename T> auto op_not(const T &a) -> decltype(!a) { return !a; }

// unary sign

// `+var`
template <typename T> auto op_pos(const T &a) -> decltype(+a) { return +a; }
// `-var`
template <typename T> auto op_neg(const T &a) -> decltype(-a) { return -a; }

// unary pointer

// `&var`
template <typename T> auto op_addr (const T &a) -> decltype(&a) { return &a; }
// `*var`
template <typename T> auto op_deref(const T &a) -> decltype(*a) { return *a; }

// binary arithmetic

// `var1+var2`
template <typename T, typename U = T> auto op_add(const T &a, const U &b) -> decltype(a+b) { return a+b; }
// `var1-var2`
template <typename T, typename U = T> auto op_sub(const T &a, const U &b) -> decltype(a-b) { return a-b; }
// `var1*var2`
template <typename T, typename U = T> auto op_mul(const T &a, const U &b) -> decltype(a*b) { return a*b; }
// `var1/var2`
template <typename T, typename U = T> auto op_div(const T &a, const U &b) -> decltype(a/b) { return a/b; }
// `var1%var2`
template <typename T, typename U = T> auto op_mod(const T &a, const U &b) -> decltype(a%b) { return a%b; }

// binary shift

// `var1<<var2`
template <typename T, typename U = T> auto op_shl(const T &a, const U &b) -> decltype(a<<b) { return a<<b; }
// `var1>>var2`
template <typename T, typename U = T> auto op_shr(const T &a, const U &b) -> decltype(a>>b) { return a>>b; }

// binary comparator

// `var1<var2`
template <typename T, typename U = T> auto op_lt (const T &a, const U &b) -> decltype(a<b  ) { return a<b;   }
// `var1>var2`
template <typename T, typename U = T> auto op_gt (const T &a, const U &b) -> decltype(a>b  ) { return a>b;   }
// `var1<=var2`
template <typename T, typename U = T> auto op_leq(const T &a, const U &b) -> decltype(a<=b ) { return a<=b;  }
// `var1>=var2`
template <typename T, typename U = T> auto op_geq(const T &a, const U &b) -> decltype(a>=b ) { return a>=b;  }
// `var1==var2`
template <typename T, typename U = T> auto op_eq (const T &a, const U &b) -> decltype(a==b ) { return a==b;  }
// `var1!=var2`
template <typename T, typename U = T> auto op_neq(const T &a, const U &b) -> decltype(a!=b ) { return a!=b;  }
#if TKOZ_CPP20_OR_NEWER
// `var1<=>var2`
template <typename T, typename U = T> auto op_3wc(const T &a, const U &b) -> decltype(a<=>b) { return a<=>b; }
#endif

// binary bits

// `var1&var2`
template <typename T, typename U = T> auto op_and(const T &a, const U &b) -> decltype(a&b) { return a&b; }
// `var1|var2`
template <typename T, typename U = T> auto op_or (const T &a, const U &b) -> decltype(a|b) { return a|b; }
// `var1^var2`
template <typename T, typename U = T> auto op_xor(const T &a, const U &b) -> decltype(a^b) { return a^b; }

// binary logical

// `var1&&var2`
template <typename T, typename U = T> auto op_land(const T &a, const U &b) -> decltype(a&&b) { return a&&b; }
// `var1||var2`
template <typename T, typename U = T> auto op_lor (const T &a, const U &b) -> decltype(a||b) { return a||b; }

// (combined) assignment

// `var1=var2`
template <typename T, typename U = T> auto op_assign(T &a, const U &b) -> decltype(a=b) { return a=b; }
// `var1+=var2`
template <typename T, typename U = T> auto op_add_eq(T &a, const U &b) -> decltype(a+=b) { return a+=b; }
// `var1-=var2`
template <typename T, typename U = T> auto op_sub_eq(T &a, const U &b) -> decltype(a-=b) { return a-=b; }
// `var1*=var2`
template <typename T, typename U = T> auto op_mul_eq(T &a, const U &b) -> decltype(a*=b) { return a*=b; }
// `var1/=var2`
template <typename T, typename U = T> auto op_div_eq(T &a, const U &b) -> decltype(a/=b) { return a/=b; }
// `var1%=var2`
template <typename T, typename U = T> auto op_mod_eq(T &a, const U &b) -> decltype(a%=b) { return a%=b; }
// `var1<<=var2`
template <typename T, typename U = T> auto op_shl_eq(T &a, const U &b) -> decltype(a<<=b) { return a<<=b; }
// `var1>>=var2`
template <typename T, typename U = T> auto op_shr_eq(T &a, const U &b) -> decltype(a>>=b) { return a>>=b; }
// `var1&=var2`
template <typename T, typename U = T> auto op_and_eq(T &a, const U &b) -> decltype(a&=b) { return a&=b; }
// `var1|=var2`
template <typename T, typename U = T> auto op_or_eq(T &a, const U &b) -> decltype(a|=b) { return a|=b; }
// `var1^=var2`
template <typename T, typename U = T> auto op_xor_eq(T &a, const U &b) -> decltype(a^=b) { return a^=b; }

}
