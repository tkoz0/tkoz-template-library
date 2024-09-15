/*
Convenient tuples for more sizes than just std::pair
- public member variables labeled by letters a-z
- if not all types specified, remaining types use last specified type
- includes get<i>() and set<i>(value) for variables
- overloads operators for some convenient parallel operations
  - compound assignment with tuple of same type applies in parallel
  - compound assignment with other type applies it to each member
  - increment/decrement applying to each member
  - unary and binary operators make new tuples of appropriate type
- supports lexicographic comparators
- supports conversion to bool
*/

#pragma once

#include <compare>
#include <cstddef>
#include <type_traits>

namespace tkoz
{

#define GET(IV,TV,MV) template <size_t ind, typename std::enable_if_t<ind==IV,bool> = true> \
    inline constexpr TV &get() { return MV; }
#define GETC(IV,TV,MV) template <size_t ind, typename std::enable_if_t<ind==IV,bool> = true> \
    inline constexpr const TV &get() const { return MV; }
#define SET(IV,TV,MV) template <size_t ind, typename std::enable_if_t<ind==IV,bool> = true> \
    inline void set(const TV &val) { MV = val; }

template <typename T1, typename T2 = T1>
struct tuple2;

template <typename T1, typename T2>
inline constexpr tuple2<T1,T2> make_tuple2(const T1 &a, const T2 &b);

template <typename T1, typename T2>
struct tuple2
{
#define OPEQ_TUPLE(OP) inline constexpr tuple2 &operator OP(const tuple2 &rhs) { a OP rhs.a; b OP rhs.b; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple2 &lhs, const tuple2 &rhs) \
    { return make_tuple2(lhs.a OP rhs.a, lhs.b OP rhs.b); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple2 &tup) { return make_tuple2(OP tup.a, OP tup.b); }
#define OP_PRE(OP) inline constexpr tuple2 &operator OP() { OP a; OP b; return *this; }
#define OP_POST(OP) inline constexpr tuple2 operator OP(int) { tuple2 ret = *this; OP(*this); return ret; }
    T1 a; T2 b;
    inline constexpr tuple2(): a(), b() {}
    inline constexpr tuple2(const T1 &a, const T2 &b): a(a), b(b) {}
    GET(0,T1,a) GET(1,T2,b)
    GETC(0,T1,a) GETC(1,T2,b)
    SET(0,T1,a) SET(1,T2,b)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b); }
    inline constexpr bool operator==(const tuple2 &tup) const { return a == tup.a && b == tup.b; }
    inline constexpr auto operator<=>(const tuple2 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        return b <=> tup.b;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2>
inline constexpr tuple2<T1,T2> make_tuple2(const T1 &a, const T2 &b) { return tuple2<T1,T2>(a,b); }

template <typename T1, typename T2 = T1, typename T3 = T2>
struct tuple3;

template <typename T1, typename T2, typename T3>
inline constexpr tuple3<T1,T2,T3> make_tuple3(const T1 &a, const T2 &b, const T3 &c);

template <typename T1, typename T2, typename T3>
struct tuple3
{
#define OPEQ_TUPLE(OP) inline constexpr tuple3 &operator OP(const tuple3 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple3 &lhs, const tuple3 &rhs) \
    { return make_tuple3(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple3 &tup) { return make_tuple3(OP tup.a, OP tup.b, OP tup.c); }
#define OP_PRE(OP) inline constexpr tuple3 &operator OP() { OP a; OP b; OP c; return *this; }
#define OP_POST(OP) inline constexpr tuple3 operator OP(int) { tuple3 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c;
    inline constexpr tuple3(): a(), b(), c() {}
    inline constexpr tuple3(const T1 &a, const T2 &b, const T3 &c): a(a), b(b), c(c) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c); }
    inline constexpr bool operator==(const tuple3 &tup) const { return a == tup.a && b == tup.b && c == tup.c; }
    inline constexpr auto operator<=>(const tuple3 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        return c <=> tup.c;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3>
inline constexpr tuple3<T1,T2,T3> make_tuple3(const T1 &a, const T2 &b, const T3 &c) { return tuple3<T1,T2,T3>(a,b,c); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3>
struct tuple4;

template <typename T1, typename T2, typename T3, typename T4>
inline constexpr tuple4<T1,T2,T3,T4> make_tuple4(const T1 &a, const T2 &b, const T3 &c, const T4 &d);

template <typename T1, typename T2, typename T3, typename T4>
struct tuple4
{
#define OPEQ_TUPLE(OP) inline constexpr tuple4 &operator OP(const tuple4 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple4 &lhs, const tuple4 &rhs) \
    { return make_tuple4(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple4 &tup) { return make_tuple4(OP tup.a, OP tup.b, OP tup.c, OP tup.d); }
#define OP_PRE(OP) inline constexpr tuple4 &operator OP() { OP a; OP b; OP c; OP d; return *this; }
#define OP_POST(OP) inline constexpr tuple4 operator OP(int) { tuple4 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d;
    inline constexpr tuple4(): a(), b(), c(), d() {}
    inline constexpr tuple4(const T1 &a, const T2 &b, const T3 &c, const T4 &d): a(a), b(b), c(c), d(d) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d); }
    inline constexpr bool operator==(const tuple4 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d; }
    inline constexpr auto operator<=>(const tuple4 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        return d <=> tup.d;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4>
inline constexpr tuple4<T1,T2,T3,T4> make_tuple4(const T1 &a, const T2 &b, const T3 &c, const T4 &d) { return tuple4<T1,T2,T3,T4>(a,b,c,d); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4>
struct tuple5;

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline constexpr tuple5<T1,T2,T3,T4,T5> make_tuple5(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e);

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct tuple5
{
#define OPEQ_TUPLE(OP) inline constexpr tuple5 &operator OP(const tuple5 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple5 &lhs, const tuple5 &rhs) \
    { return make_tuple5(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple5 &tup) { return make_tuple5(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e); }
#define OP_PRE(OP) inline constexpr tuple5 &operator OP() { OP a; OP b; OP c; OP d; OP e; return *this; }
#define OP_POST(OP) inline constexpr tuple5 operator OP(int) { tuple5 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e;
    inline constexpr tuple5(): a(), b(), c(), d(), e() {}
    inline constexpr tuple5(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e): a(a), b(b), c(c), d(d), e(e) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e); }
    inline constexpr bool operator==(const tuple5 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e; }
    inline constexpr auto operator<=>(const tuple5 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        return e <=> tup.e;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline constexpr tuple5<T1,T2,T3,T4,T5> make_tuple5(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e) { return tuple5<T1,T2,T3,T4,T5>(a,b,c,d,e); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5>
struct tuple6;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline constexpr tuple6<T1,T2,T3,T4,T5,T6> make_tuple6(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct tuple6
{
#define OPEQ_TUPLE(OP) inline constexpr tuple6 &operator OP(const tuple6 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple6 &lhs, const tuple6 &rhs) \
    { return make_tuple6(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple6 &tup) { return make_tuple6(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f); }
#define OP_PRE(OP) inline constexpr tuple6 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; return *this; }
#define OP_POST(OP) inline constexpr tuple6 operator OP(int) { tuple6 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f;
    inline constexpr tuple6(): a(), b(), c(), d(), e(), f() {}
    inline constexpr tuple6(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f): a(a), b(b), c(c), d(d), e(e), f(f) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f); }
    inline constexpr bool operator==(const tuple6 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f; }
    inline constexpr auto operator<=>(const tuple6 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        return f <=> tup.f;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline constexpr tuple6<T1,T2,T3,T4,T5,T6> make_tuple6(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f) { return tuple6<T1,T2,T3,T4,T5,T6>(a,b,c,d,e,f); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6>
struct tuple7;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline constexpr tuple7<T1,T2,T3,T4,T5,T6,T7> make_tuple7(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct tuple7
{
#define OPEQ_TUPLE(OP) inline constexpr tuple7 &operator OP(const tuple7 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple7 &lhs, const tuple7 &rhs) \
    { return make_tuple7(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple7 &tup) { return make_tuple7(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g); }
#define OP_PRE(OP) inline constexpr tuple7 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; return *this; }
#define OP_POST(OP) inline constexpr tuple7 operator OP(int) { tuple7 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g;
    inline constexpr tuple7(): a(), b(), c(), d(), e(), f(), g() {}
    inline constexpr tuple7(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g): a(a), b(b), c(c), d(d), e(e), f(f), g(g) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g); }
    inline constexpr bool operator==(const tuple7 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g; }
    inline constexpr auto operator<=>(const tuple7 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        return g <=> tup.g;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline constexpr tuple7<T1,T2,T3,T4,T5,T6,T7> make_tuple7(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g) { return tuple7<T1,T2,T3,T4,T5,T6,T7>(a,b,c,d,e,f,g); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7>
struct tuple8;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline constexpr tuple8<T1,T2,T3,T4,T5,T6,T7,T8> make_tuple8(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct tuple8
{
#define OPEQ_TUPLE(OP) inline constexpr tuple8 &operator OP(const tuple8 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple8 &lhs, const tuple8 &rhs) \
    { return make_tuple8(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple8 &tup) { return make_tuple8(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h); }
#define OP_PRE(OP) inline constexpr tuple8 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; return *this; }
#define OP_POST(OP) inline constexpr tuple8 operator OP(int) { tuple8 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h;
    inline constexpr tuple8(): a(), b(), c(), d(), e(), f(), g(), h() {}
    inline constexpr tuple8(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h); }
    inline constexpr bool operator==(const tuple8 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h; }
    inline constexpr auto operator<=>(const tuple8 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        return h <=> tup.h;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline constexpr tuple8<T1,T2,T3,T4,T5,T6,T7,T8> make_tuple8(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h) { return tuple8<T1,T2,T3,T4,T5,T6,T7,T8>(a,b,c,d,e,f,g,h); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8>
struct tuple9;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline constexpr tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9> make_tuple9(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct tuple9
{
#define OPEQ_TUPLE(OP) inline constexpr tuple9 &operator OP(const tuple9 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple9 &lhs, const tuple9 &rhs) \
    { return make_tuple9(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple9 &tup) { return make_tuple9(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i); }
#define OP_PRE(OP) inline constexpr tuple9 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; return *this; }
#define OP_POST(OP) inline constexpr tuple9 operator OP(int) { tuple9 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i;
    inline constexpr tuple9(): a(), b(), c(), d(), e(), f(), g(), h(), i() {}
    inline constexpr tuple9(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i); }
    inline constexpr bool operator==(const tuple9 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i; }
    inline constexpr auto operator<=>(const tuple9 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        return i <=> tup.i;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline constexpr tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9> make_tuple9(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i) { return tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9>(a,b,c,d,e,f,g,h,i); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9>
struct tuple10;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
inline constexpr tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> make_tuple10(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
struct tuple10
{
#define OPEQ_TUPLE(OP) inline constexpr tuple10 &operator OP(const tuple10 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple10 &lhs, const tuple10 &rhs) \
    { return make_tuple10(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple10 &tup) { return make_tuple10(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j); }
#define OP_PRE(OP) inline constexpr tuple10 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; return *this; }
#define OP_POST(OP) inline constexpr tuple10 operator OP(int) { tuple10 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j;
    inline constexpr tuple10(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j() {}
    inline constexpr tuple10(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j); }
    inline constexpr bool operator==(const tuple10 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j; }
    inline constexpr auto operator<=>(const tuple10 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        return j <=> tup.j;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
inline constexpr tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> make_tuple10(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j) { return tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(a,b,c,d,e,f,g,h,i,j); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10>
struct tuple11;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
inline constexpr tuple11<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> make_tuple11(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
struct tuple11
{
#define OPEQ_TUPLE(OP) inline constexpr tuple11 &operator OP(const tuple11 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple11 &lhs, const tuple11 &rhs) \
    { return make_tuple11(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple11 &tup) { return make_tuple11(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k); }
#define OP_PRE(OP) inline constexpr tuple11 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; return *this; }
#define OP_POST(OP) inline constexpr tuple11 operator OP(int) { tuple11 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k;
    inline constexpr tuple11(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k() {}
    inline constexpr tuple11(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k); }
    inline constexpr bool operator==(const tuple11 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k; }
    inline constexpr auto operator<=>(const tuple11 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        return k <=> tup.k;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
inline constexpr tuple11<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> make_tuple11(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k) { return tuple11<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(a,b,c,d,e,f,g,h,i,j,k); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11>
struct tuple12;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
inline constexpr tuple12<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> make_tuple12(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
struct tuple12
{
#define OPEQ_TUPLE(OP) inline constexpr tuple12 &operator OP(const tuple12 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple12 &lhs, const tuple12 &rhs) \
    { return make_tuple12(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple12 &tup) { return make_tuple12(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l); }
#define OP_PRE(OP) inline constexpr tuple12 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; return *this; }
#define OP_POST(OP) inline constexpr tuple12 operator OP(int) { tuple12 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l;
    inline constexpr tuple12(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l() {}
    inline constexpr tuple12(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l); }
    inline constexpr bool operator==(const tuple12 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l; }
    inline constexpr auto operator<=>(const tuple12 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        return l <=> tup.l;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
inline constexpr tuple12<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> make_tuple12(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l) { return tuple12<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(a,b,c,d,e,f,g,h,i,j,k,l); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12>
struct tuple13;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
inline constexpr tuple13<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> make_tuple13(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
struct tuple13
{
#define OPEQ_TUPLE(OP) inline constexpr tuple13 &operator OP(const tuple13 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple13 &lhs, const tuple13 &rhs) \
    { return make_tuple13(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple13 &tup) { return make_tuple13(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m); }
#define OP_PRE(OP) inline constexpr tuple13 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; return *this; }
#define OP_POST(OP) inline constexpr tuple13 operator OP(int) { tuple13 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m;
    inline constexpr tuple13(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m() {}
    inline constexpr tuple13(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m); }
    inline constexpr bool operator==(const tuple13 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m; }
    inline constexpr auto operator<=>(const tuple13 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        return m <=> tup.m;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
inline constexpr tuple13<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> make_tuple13(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m) { return tuple13<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(a,b,c,d,e,f,g,h,i,j,k,l,m); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13>
struct tuple14;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
inline constexpr tuple14<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> make_tuple14(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
struct tuple14
{
#define OPEQ_TUPLE(OP) inline constexpr tuple14 &operator OP(const tuple14 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple14 &lhs, const tuple14 &rhs) \
    { return make_tuple14(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple14 &tup) { return make_tuple14(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n); }
#define OP_PRE(OP) inline constexpr tuple14 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; return *this; }
#define OP_POST(OP) inline constexpr tuple14 operator OP(int) { tuple14 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n;
    inline constexpr tuple14(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n() {}
    inline constexpr tuple14(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n); }
    inline constexpr bool operator==(const tuple14 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n; }
    inline constexpr auto operator<=>(const tuple14 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        return n <=> tup.n;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
inline constexpr tuple14<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> make_tuple14(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n) { return tuple14<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(a,b,c,d,e,f,g,h,i,j,k,l,m,n); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14>
struct tuple15;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
inline constexpr tuple15<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15> make_tuple15(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
struct tuple15
{
#define OPEQ_TUPLE(OP) inline constexpr tuple15 &operator OP(const tuple15 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple15 &lhs, const tuple15 &rhs) \
    { return make_tuple15(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple15 &tup) { return make_tuple15(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o); }
#define OP_PRE(OP) inline constexpr tuple15 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; return *this; }
#define OP_POST(OP) inline constexpr tuple15 operator OP(int) { tuple15 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o;
    inline constexpr tuple15(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o() {}
    inline constexpr tuple15(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o); }
    inline constexpr bool operator==(const tuple15 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o; }
    inline constexpr auto operator<=>(const tuple15 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        return o <=> tup.o;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
inline constexpr tuple15<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15> make_tuple15(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o) { return tuple15<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15>
struct tuple16;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
inline constexpr tuple16<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16> make_tuple16(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
struct tuple16
{
#define OPEQ_TUPLE(OP) inline constexpr tuple16 &operator OP(const tuple16 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple16 &lhs, const tuple16 &rhs) \
    { return make_tuple16(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple16 &tup) { return make_tuple16(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p); }
#define OP_PRE(OP) inline constexpr tuple16 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; return *this; }
#define OP_POST(OP) inline constexpr tuple16 operator OP(int) { tuple16 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p;
    inline constexpr tuple16(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p() {}
    inline constexpr tuple16(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p); }
    inline constexpr bool operator==(const tuple16 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p; }
    inline constexpr auto operator<=>(const tuple16 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        return p <=> tup.p;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
inline constexpr tuple16<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16> make_tuple16(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p) { return tuple16<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16>
struct tuple17;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
inline constexpr tuple17<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17> make_tuple17(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
struct tuple17
{
#define OPEQ_TUPLE(OP) inline constexpr tuple17 &operator OP(const tuple17 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple17 &lhs, const tuple17 &rhs) \
    { return make_tuple17(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple17 &tup) { return make_tuple17(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q); }
#define OP_PRE(OP) inline constexpr tuple17 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; return *this; }
#define OP_POST(OP) inline constexpr tuple17 operator OP(int) { tuple17 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q;
    inline constexpr tuple17(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q() {}
    inline constexpr tuple17(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q); }
    inline constexpr bool operator==(const tuple17 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q; }
    inline constexpr auto operator<=>(const tuple17 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        return q <=> tup.q;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
inline constexpr tuple17<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17> make_tuple17(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q) { return tuple17<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17>
struct tuple18;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
inline constexpr tuple18<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18> make_tuple18(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
struct tuple18
{
#define OPEQ_TUPLE(OP) inline constexpr tuple18 &operator OP(const tuple18 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple18 &lhs, const tuple18 &rhs) \
    { return make_tuple18(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple18 &tup) { return make_tuple18(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r); }
#define OP_PRE(OP) inline constexpr tuple18 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; return *this; }
#define OP_POST(OP) inline constexpr tuple18 operator OP(int) { tuple18 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r;
    inline constexpr tuple18(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r() {}
    inline constexpr tuple18(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r); }
    inline constexpr bool operator==(const tuple18 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r; }
    inline constexpr auto operator<=>(const tuple18 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        return r <=> tup.r;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
inline constexpr tuple18<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18> make_tuple18(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r) { return tuple18<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18>
struct tuple19;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
inline constexpr tuple19<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19> make_tuple19(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
struct tuple19
{
#define OPEQ_TUPLE(OP) inline constexpr tuple19 &operator OP(const tuple19 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple19 &lhs, const tuple19 &rhs) \
    { return make_tuple19(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple19 &tup) { return make_tuple19(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s); }
#define OP_PRE(OP) inline constexpr tuple19 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; return *this; }
#define OP_POST(OP) inline constexpr tuple19 operator OP(int) { tuple19 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s;
    inline constexpr tuple19(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s() {}
    inline constexpr tuple19(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s); }
    inline constexpr bool operator==(const tuple19 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s; }
    inline constexpr auto operator<=>(const tuple19 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        return s <=> tup.s;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
inline constexpr tuple19<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19> make_tuple19(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s) { return tuple19<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19>
struct tuple20;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
inline constexpr tuple20<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20> make_tuple20(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
struct tuple20
{
#define OPEQ_TUPLE(OP) inline constexpr tuple20 &operator OP(const tuple20 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple20 &lhs, const tuple20 &rhs) \
    { return make_tuple20(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple20 &tup) { return make_tuple20(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t); }
#define OP_PRE(OP) inline constexpr tuple20 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; return *this; }
#define OP_POST(OP) inline constexpr tuple20 operator OP(int) { tuple20 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t;
    inline constexpr tuple20(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t() {}
    inline constexpr tuple20(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t); }
    inline constexpr bool operator==(const tuple20 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t; }
    inline constexpr auto operator<=>(const tuple20 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        return t <=> tup.t;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
inline constexpr tuple20<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20> make_tuple20(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t) { return tuple20<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20>
struct tuple21;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
inline constexpr tuple21<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21> make_tuple21(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
struct tuple21
{
#define OPEQ_TUPLE(OP) inline constexpr tuple21 &operator OP(const tuple21 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple21 &lhs, const tuple21 &rhs) \
    { return make_tuple21(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple21 &tup) { return make_tuple21(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u); }
#define OP_PRE(OP) inline constexpr tuple21 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; return *this; }
#define OP_POST(OP) inline constexpr tuple21 operator OP(int) { tuple21 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u;
    inline constexpr tuple21(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u() {}
    inline constexpr tuple21(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u); }
    inline constexpr bool operator==(const tuple21 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u; }
    inline constexpr auto operator<=>(const tuple21 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        return u <=> tup.u;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
inline constexpr tuple21<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21> make_tuple21(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u) { return tuple21<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20, typename T22 = T21>
struct tuple22;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
inline constexpr tuple22<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22> make_tuple22(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
struct tuple22
{
#define OPEQ_TUPLE(OP) inline constexpr tuple22 &operator OP(const tuple22 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple22 &lhs, const tuple22 &rhs) \
    { return make_tuple22(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple22 &tup) { return make_tuple22(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v); }
#define OP_PRE(OP) inline constexpr tuple22 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; return *this; }
#define OP_POST(OP) inline constexpr tuple22 operator OP(int) { tuple22 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v;
    inline constexpr tuple22(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u(), v() {}
    inline constexpr tuple22(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v); }
    inline constexpr bool operator==(const tuple22 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u && v == tup.v; }
    inline constexpr auto operator<=>(const tuple22 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        if ((cmp = (u <=> tup.u)) != 0) return cmp;
        return v <=> tup.v;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
inline constexpr tuple22<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22> make_tuple22(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v) { return tuple22<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20, typename T22 = T21, typename T23 = T22>
struct tuple23;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
inline constexpr tuple23<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23> make_tuple23(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
struct tuple23
{
#define OPEQ_TUPLE(OP) inline constexpr tuple23 &operator OP(const tuple23 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple23 &lhs, const tuple23 &rhs) \
    { return make_tuple23(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple23 &tup) { return make_tuple23(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w); }
#define OP_PRE(OP) inline constexpr tuple23 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; return *this; }
#define OP_POST(OP) inline constexpr tuple23 operator OP(int) { tuple23 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w;
    inline constexpr tuple23(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u(), v(), w() {}
    inline constexpr tuple23(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w); }
    inline constexpr bool operator==(const tuple23 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u && v == tup.v && w == tup.w; }
    inline constexpr auto operator<=>(const tuple23 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        if ((cmp = (u <=> tup.u)) != 0) return cmp;
        if ((cmp = (v <=> tup.v)) != 0) return cmp;
        return w <=> tup.w;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
inline constexpr tuple23<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23> make_tuple23(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w) { return tuple23<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20, typename T22 = T21, typename T23 = T22, typename T24 = T23>
struct tuple24;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
inline constexpr tuple24<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24> make_tuple24(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
struct tuple24
{
#define OPEQ_TUPLE(OP) inline constexpr tuple24 &operator OP(const tuple24 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple24 &lhs, const tuple24 &rhs) \
    { return make_tuple24(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple24 &tup) { return make_tuple24(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x); }
#define OP_PRE(OP) inline constexpr tuple24 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; return *this; }
#define OP_POST(OP) inline constexpr tuple24 operator OP(int) { tuple24 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x;
    inline constexpr tuple24(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u(), v(), w(), x() {}
    inline constexpr tuple24(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x); }
    inline constexpr bool operator==(const tuple24 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u && v == tup.v && w == tup.w && x == tup.x; }
    inline constexpr auto operator<=>(const tuple24 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        if ((cmp = (u <=> tup.u)) != 0) return cmp;
        if ((cmp = (v <=> tup.v)) != 0) return cmp;
        if ((cmp = (w <=> tup.w)) != 0) return cmp;
        return x <=> tup.x;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
inline constexpr tuple24<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24> make_tuple24(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x) { return tuple24<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20, typename T22 = T21, typename T23 = T22, typename T24 = T23, typename T25 = T24>
struct tuple25;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
inline constexpr tuple25<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25> make_tuple25(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
struct tuple25
{
#define OPEQ_TUPLE(OP) inline constexpr tuple25 &operator OP(const tuple25 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; y OP rhs.y; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple25 &lhs, const tuple25 &rhs) \
    { return make_tuple25(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x, lhs.y OP rhs.y); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple25 &tup) { return make_tuple25(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x, OP tup.y); }
#define OP_PRE(OP) inline constexpr tuple25 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; OP y; return *this; }
#define OP_POST(OP) inline constexpr tuple25 operator OP(int) { tuple25 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x; T25 y;
    inline constexpr tuple25(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u(), v(), w(), x(), y() {}
    inline constexpr tuple25(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x), y(y) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x) GET(24,T25,y)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x) GETC(24,T25,y)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x) SET(24,T25,y)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x) || bool(y); }
    inline constexpr bool operator==(const tuple25 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u && v == tup.v && w == tup.w && x == tup.x && y == tup.y; }
    inline constexpr auto operator<=>(const tuple25 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        if ((cmp = (u <=> tup.u)) != 0) return cmp;
        if ((cmp = (v <=> tup.v)) != 0) return cmp;
        if ((cmp = (w <=> tup.w)) != 0) return cmp;
        if ((cmp = (x <=> tup.x)) != 0) return cmp;
        return y <=> tup.y;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
inline constexpr tuple25<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25> make_tuple25(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y) { return tuple25<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y); }

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8, typename T10 = T9, typename T11 = T10, typename T12 = T11, typename T13 = T12, typename T14 = T13, typename T15 = T14, typename T16 = T15, typename T17 = T16, typename T18 = T17, typename T19 = T18, typename T20 = T19, typename T21 = T20, typename T22 = T21, typename T23 = T22, typename T24 = T23, typename T25 = T24, typename T26 = T25>
struct tuple26;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
inline constexpr tuple26<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26> make_tuple26(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y, const T26 &z);

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
struct tuple26
{
#define OPEQ_TUPLE(OP) inline constexpr tuple26 &operator OP(const tuple26 &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; y OP rhs.y; z OP rhs.z; return *this; }
#define OP_BINARY(OP) friend inline constexpr auto operator OP(const tuple26 &lhs, const tuple26 &rhs) \
    { return make_tuple26(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x, lhs.y OP rhs.y, lhs.z OP rhs.z); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline constexpr auto operator OP(const tuple26 &tup) { return make_tuple26(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x, OP tup.y, OP tup.z); }
#define OP_PRE(OP) inline constexpr tuple26 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; OP y; OP z; return *this; }
#define OP_POST(OP) inline constexpr tuple26 operator OP(int) { tuple26 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x; T25 y; T26 z;
    inline constexpr tuple26(): a(), b(), c(), d(), e(), f(), g(), h(), i(), j(), k(), l(), m(), n(), o(), p(), q(), r(), s(), t(), u(), v(), w(), x(), y(), z() {}
    inline constexpr tuple26(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y, const T26 &z): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x), y(y), z(z) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x) GET(24,T25,y) GET(25,T26,z)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x) GETC(24,T25,y) GETC(25,T26,z)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x) SET(24,T25,y) SET(25,T26,z)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x) || bool(y) || bool(z); }
    inline constexpr bool operator==(const tuple26 &tup) const { return a == tup.a && b == tup.b && c == tup.c && d == tup.d && e == tup.e && f == tup.f && g == tup.g && h == tup.h && i == tup.i && j == tup.j && k == tup.k && l == tup.l && m == tup.m && n == tup.n && o == tup.o && p == tup.p && q == tup.q && r == tup.r && s == tup.s && t == tup.t && u == tup.u && v == tup.v && w == tup.w && x == tup.x && y == tup.y && z == tup.z; }
    inline constexpr auto operator<=>(const tuple26 &tup) const
    {
        auto cmp = (a <=> tup.a);
        if (cmp != 0) return cmp;
        if ((cmp = (b <=> tup.b)) != 0) return cmp;
        if ((cmp = (c <=> tup.c)) != 0) return cmp;
        if ((cmp = (d <=> tup.d)) != 0) return cmp;
        if ((cmp = (e <=> tup.e)) != 0) return cmp;
        if ((cmp = (f <=> tup.f)) != 0) return cmp;
        if ((cmp = (g <=> tup.g)) != 0) return cmp;
        if ((cmp = (h <=> tup.h)) != 0) return cmp;
        if ((cmp = (i <=> tup.i)) != 0) return cmp;
        if ((cmp = (j <=> tup.j)) != 0) return cmp;
        if ((cmp = (k <=> tup.k)) != 0) return cmp;
        if ((cmp = (l <=> tup.l)) != 0) return cmp;
        if ((cmp = (m <=> tup.m)) != 0) return cmp;
        if ((cmp = (n <=> tup.n)) != 0) return cmp;
        if ((cmp = (o <=> tup.o)) != 0) return cmp;
        if ((cmp = (p <=> tup.p)) != 0) return cmp;
        if ((cmp = (q <=> tup.q)) != 0) return cmp;
        if ((cmp = (r <=> tup.r)) != 0) return cmp;
        if ((cmp = (s <=> tup.s)) != 0) return cmp;
        if ((cmp = (t <=> tup.t)) != 0) return cmp;
        if ((cmp = (u <=> tup.u)) != 0) return cmp;
        if ((cmp = (v <=> tup.v)) != 0) return cmp;
        if ((cmp = (w <=> tup.w)) != 0) return cmp;
        if ((cmp = (x <=> tup.x)) != 0) return cmp;
        if ((cmp = (y <=> tup.y)) != 0) return cmp;
        return z <=> tup.z;
    }
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
inline constexpr tuple26<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26> make_tuple26(const T1 &a, const T2 &b, const T3 &c, const T4 &d, const T5 &e, const T6 &f, const T7 &g, const T8 &h, const T9 &i, const T10 &j, const T11 &k, const T12 &l, const T13 &m, const T14 &n, const T15 &o, const T16 &p, const T17 &q, const T18 &r, const T19 &s, const T20 &t, const T21 &u, const T22 &v, const T23 &w, const T24 &x, const T25 &y, const T26 &z) { return tuple26<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z); }

#undef GET
#undef GETC
#undef SET

}

