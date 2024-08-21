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

#define GET(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \
    inline constexpr TV &get() { return MV; }
#define GETC(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \
    inline constexpr const TV &get() const { return MV; }
#define SET(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \
    inline void set(const TV &val) { MV = val; }

template <typename T1, typename T2 = T1>
struct tuple2
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple2>,bool> = true> \
    inline tuple2 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple2>,bool> = true> \
    inline tuple2 &operator OP(const U &rhs) { a OP rhs; b OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple2 &lhs, const tuple2 &rhs) \
    { return make_tuple2(lhs.a OP rhs.a, lhs.b OP rhs.b); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple2 &tup) { return make_tuple2(OP tup.a, OP tup.b); }
#define OP_PRE(OP) inline tuple2 &operator OP() { OP a; OP b; return *this; }
#define OP_POST(OP) inline tuple2 operator OP(int) { tuple2 ret = *this; OP(*this); return ret; }
    T1 a; T2 b;
    inline constexpr tuple2(const T1 &a = T1(), const T2 &b = T2()): a(a), b(b) {}
    GET(0,T1,a) GET(1,T2,b)
    GETC(0,T1,a) GETC(1,T2,b)
    SET(0,T1,a) SET(1,T2,b)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b); }
    inline constexpr bool operator==(const tuple2 &tup) const = default;
    inline constexpr auto operator<=>(const tuple2 &tup) const = default;
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
struct tuple3
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple3>,bool> = true> \
    inline tuple3 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple3>,bool> = true> \
    inline tuple3 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple3 &lhs, const tuple3 &rhs) \
    { return make_tuple3(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple3 &tup) { return make_tuple3(OP tup.a, OP tup.b, OP tup.c); }
#define OP_PRE(OP) inline tuple3 &operator OP() { OP a; OP b; OP c; return *this; }
#define OP_POST(OP) inline tuple3 operator OP(int) { tuple3 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c;
    inline constexpr tuple3(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3()): a(a), b(b), c(c) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c); }
    inline constexpr bool operator==(const tuple3 &tup) const = default;
    inline constexpr auto operator<=>(const tuple3 &tup) const = default;
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
struct tuple4
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple4>,bool> = true> \
    inline tuple4 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple4>,bool> = true> \
    inline tuple4 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple4 &lhs, const tuple4 &rhs) \
    { return make_tuple4(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple4 &tup) { return make_tuple4(OP tup.a, OP tup.b, OP tup.c, OP tup.d); }
#define OP_PRE(OP) inline tuple4 &operator OP() { OP a; OP b; OP c; OP d; return *this; }
#define OP_POST(OP) inline tuple4 operator OP(int) { tuple4 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d;
    inline constexpr tuple4(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4()): a(a), b(b), c(c), d(d) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d); }
    inline constexpr bool operator==(const tuple4 &tup) const = default;
    inline constexpr auto operator<=>(const tuple4 &tup) const = default;
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
struct tuple5
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple5>,bool> = true> \
    inline tuple5 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple5>,bool> = true> \
    inline tuple5 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple5 &lhs, const tuple5 &rhs) \
    { return make_tuple5(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple5 &tup) { return make_tuple5(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e); }
#define OP_PRE(OP) inline tuple5 &operator OP() { OP a; OP b; OP c; OP d; OP e; return *this; }
#define OP_POST(OP) inline tuple5 operator OP(int) { tuple5 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e;
    inline constexpr tuple5(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5()): a(a), b(b), c(c), d(d), e(e) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e); }
    inline constexpr bool operator==(const tuple5 &tup) const = default;
    inline constexpr auto operator<=>(const tuple5 &tup) const = default;
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
struct tuple6
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple6>,bool> = true> \
    inline tuple6 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple6>,bool> = true> \
    inline tuple6 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple6 &lhs, const tuple6 &rhs) \
    { return make_tuple6(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple6 &tup) { return make_tuple6(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f); }
#define OP_PRE(OP) inline tuple6 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; return *this; }
#define OP_POST(OP) inline tuple6 operator OP(int) { tuple6 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f;
    inline constexpr tuple6(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6()): a(a), b(b), c(c), d(d), e(e), f(f) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f); }
    inline constexpr bool operator==(const tuple6 &tup) const = default;
    inline constexpr auto operator<=>(const tuple6 &tup) const = default;
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
struct tuple7
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple7>,bool> = true> \
    inline tuple7 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple7>,bool> = true> \
    inline tuple7 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple7 &lhs, const tuple7 &rhs) \
    { return make_tuple7(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple7 &tup) { return make_tuple7(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g); }
#define OP_PRE(OP) inline tuple7 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; return *this; }
#define OP_POST(OP) inline tuple7 operator OP(int) { tuple7 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g;
    inline constexpr tuple7(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7()): a(a), b(b), c(c), d(d), e(e), f(f), g(g) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g); }
    inline constexpr bool operator==(const tuple7 &tup) const = default;
    inline constexpr auto operator<=>(const tuple7 &tup) const = default;
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
struct tuple8
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple8>,bool> = true> \
    inline tuple8 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple8>,bool> = true> \
    inline tuple8 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple8 &lhs, const tuple8 &rhs) \
    { return make_tuple8(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple8 &tup) { return make_tuple8(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h); }
#define OP_PRE(OP) inline tuple8 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; return *this; }
#define OP_POST(OP) inline tuple8 operator OP(int) { tuple8 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h;
    inline constexpr tuple8(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h); }
    inline constexpr bool operator==(const tuple8 &tup) const = default;
    inline constexpr auto operator<=>(const tuple8 &tup) const = default;
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
struct tuple9
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple9>,bool> = true> \
    inline tuple9 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple9>,bool> = true> \
    inline tuple9 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple9 &lhs, const tuple9 &rhs) \
    { return make_tuple9(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple9 &tup) { return make_tuple9(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i); }
#define OP_PRE(OP) inline tuple9 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; return *this; }
#define OP_POST(OP) inline tuple9 operator OP(int) { tuple9 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i;
    inline constexpr tuple9(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i); }
    inline constexpr bool operator==(const tuple9 &tup) const = default;
    inline constexpr auto operator<=>(const tuple9 &tup) const = default;
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
struct tuple10
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple10>,bool> = true> \
    inline tuple10 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple10>,bool> = true> \
    inline tuple10 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple10 &lhs, const tuple10 &rhs) \
    { return make_tuple10(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple10 &tup) { return make_tuple10(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j); }
#define OP_PRE(OP) inline tuple10 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; return *this; }
#define OP_POST(OP) inline tuple10 operator OP(int) { tuple10 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j;
    inline constexpr tuple10(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j); }
    inline constexpr bool operator==(const tuple10 &tup) const = default;
    inline constexpr auto operator<=>(const tuple10 &tup) const = default;
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
struct tuple11
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple11>,bool> = true> \
    inline tuple11 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple11>,bool> = true> \
    inline tuple11 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple11 &lhs, const tuple11 &rhs) \
    { return make_tuple11(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple11 &tup) { return make_tuple11(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k); }
#define OP_PRE(OP) inline tuple11 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; return *this; }
#define OP_POST(OP) inline tuple11 operator OP(int) { tuple11 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k;
    inline constexpr tuple11(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k); }
    inline constexpr bool operator==(const tuple11 &tup) const = default;
    inline constexpr auto operator<=>(const tuple11 &tup) const = default;
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
struct tuple12
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple12>,bool> = true> \
    inline tuple12 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple12>,bool> = true> \
    inline tuple12 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple12 &lhs, const tuple12 &rhs) \
    { return make_tuple12(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple12 &tup) { return make_tuple12(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l); }
#define OP_PRE(OP) inline tuple12 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; return *this; }
#define OP_POST(OP) inline tuple12 operator OP(int) { tuple12 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l;
    inline constexpr tuple12(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l); }
    inline constexpr bool operator==(const tuple12 &tup) const = default;
    inline constexpr auto operator<=>(const tuple12 &tup) const = default;
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
struct tuple13
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple13>,bool> = true> \
    inline tuple13 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple13>,bool> = true> \
    inline tuple13 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple13 &lhs, const tuple13 &rhs) \
    { return make_tuple13(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple13 &tup) { return make_tuple13(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m); }
#define OP_PRE(OP) inline tuple13 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; return *this; }
#define OP_POST(OP) inline tuple13 operator OP(int) { tuple13 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m;
    inline constexpr tuple13(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m); }
    inline constexpr bool operator==(const tuple13 &tup) const = default;
    inline constexpr auto operator<=>(const tuple13 &tup) const = default;
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
struct tuple14
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple14>,bool> = true> \
    inline tuple14 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple14>,bool> = true> \
    inline tuple14 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple14 &lhs, const tuple14 &rhs) \
    { return make_tuple14(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple14 &tup) { return make_tuple14(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n); }
#define OP_PRE(OP) inline tuple14 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; return *this; }
#define OP_POST(OP) inline tuple14 operator OP(int) { tuple14 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n;
    inline constexpr tuple14(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n); }
    inline constexpr bool operator==(const tuple14 &tup) const = default;
    inline constexpr auto operator<=>(const tuple14 &tup) const = default;
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
struct tuple15
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple15>,bool> = true> \
    inline tuple15 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple15>,bool> = true> \
    inline tuple15 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple15 &lhs, const tuple15 &rhs) \
    { return make_tuple15(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple15 &tup) { return make_tuple15(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o); }
#define OP_PRE(OP) inline tuple15 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; return *this; }
#define OP_POST(OP) inline tuple15 operator OP(int) { tuple15 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o;
    inline constexpr tuple15(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o); }
    inline constexpr bool operator==(const tuple15 &tup) const = default;
    inline constexpr auto operator<=>(const tuple15 &tup) const = default;
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
struct tuple16
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple16>,bool> = true> \
    inline tuple16 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple16>,bool> = true> \
    inline tuple16 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple16 &lhs, const tuple16 &rhs) \
    { return make_tuple16(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple16 &tup) { return make_tuple16(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p); }
#define OP_PRE(OP) inline tuple16 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; return *this; }
#define OP_POST(OP) inline tuple16 operator OP(int) { tuple16 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p;
    inline constexpr tuple16(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p); }
    inline constexpr bool operator==(const tuple16 &tup) const = default;
    inline constexpr auto operator<=>(const tuple16 &tup) const = default;
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
struct tuple17
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple17>,bool> = true> \
    inline tuple17 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple17>,bool> = true> \
    inline tuple17 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple17 &lhs, const tuple17 &rhs) \
    { return make_tuple17(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple17 &tup) { return make_tuple17(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q); }
#define OP_PRE(OP) inline tuple17 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; return *this; }
#define OP_POST(OP) inline tuple17 operator OP(int) { tuple17 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q;
    inline constexpr tuple17(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q); }
    inline constexpr bool operator==(const tuple17 &tup) const = default;
    inline constexpr auto operator<=>(const tuple17 &tup) const = default;
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
struct tuple18
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple18>,bool> = true> \
    inline tuple18 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple18>,bool> = true> \
    inline tuple18 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple18 &lhs, const tuple18 &rhs) \
    { return make_tuple18(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple18 &tup) { return make_tuple18(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r); }
#define OP_PRE(OP) inline tuple18 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; return *this; }
#define OP_POST(OP) inline tuple18 operator OP(int) { tuple18 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r;
    inline constexpr tuple18(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r); }
    inline constexpr bool operator==(const tuple18 &tup) const = default;
    inline constexpr auto operator<=>(const tuple18 &tup) const = default;
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
struct tuple19
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple19>,bool> = true> \
    inline tuple19 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple19>,bool> = true> \
    inline tuple19 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple19 &lhs, const tuple19 &rhs) \
    { return make_tuple19(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple19 &tup) { return make_tuple19(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s); }
#define OP_PRE(OP) inline tuple19 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; return *this; }
#define OP_POST(OP) inline tuple19 operator OP(int) { tuple19 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s;
    inline constexpr tuple19(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s); }
    inline constexpr bool operator==(const tuple19 &tup) const = default;
    inline constexpr auto operator<=>(const tuple19 &tup) const = default;
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
struct tuple20
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple20>,bool> = true> \
    inline tuple20 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple20>,bool> = true> \
    inline tuple20 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple20 &lhs, const tuple20 &rhs) \
    { return make_tuple20(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple20 &tup) { return make_tuple20(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t); }
#define OP_PRE(OP) inline tuple20 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; return *this; }
#define OP_POST(OP) inline tuple20 operator OP(int) { tuple20 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t;
    inline constexpr tuple20(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t); }
    inline constexpr bool operator==(const tuple20 &tup) const = default;
    inline constexpr auto operator<=>(const tuple20 &tup) const = default;
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
struct tuple21
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple21>,bool> = true> \
    inline tuple21 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple21>,bool> = true> \
    inline tuple21 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple21 &lhs, const tuple21 &rhs) \
    { return make_tuple21(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple21 &tup) { return make_tuple21(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u); }
#define OP_PRE(OP) inline tuple21 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; return *this; }
#define OP_POST(OP) inline tuple21 operator OP(int) { tuple21 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u;
    inline constexpr tuple21(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u); }
    inline constexpr bool operator==(const tuple21 &tup) const = default;
    inline constexpr auto operator<=>(const tuple21 &tup) const = default;
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
struct tuple22
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple22>,bool> = true> \
    inline tuple22 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple22>,bool> = true> \
    inline tuple22 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; v OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple22 &lhs, const tuple22 &rhs) \
    { return make_tuple22(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple22 &tup) { return make_tuple22(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v); }
#define OP_PRE(OP) inline tuple22 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; return *this; }
#define OP_POST(OP) inline tuple22 operator OP(int) { tuple22 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v;
    inline constexpr tuple22(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21(), const T22 &v = T22()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v); }
    inline constexpr bool operator==(const tuple22 &tup) const = default;
    inline constexpr auto operator<=>(const tuple22 &tup) const = default;
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
struct tuple23
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple23>,bool> = true> \
    inline tuple23 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple23>,bool> = true> \
    inline tuple23 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; v OP rhs; w OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple23 &lhs, const tuple23 &rhs) \
    { return make_tuple23(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple23 &tup) { return make_tuple23(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w); }
#define OP_PRE(OP) inline tuple23 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; return *this; }
#define OP_POST(OP) inline tuple23 operator OP(int) { tuple23 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w;
    inline constexpr tuple23(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21(), const T22 &v = T22(), const T23 &w = T23()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w); }
    inline constexpr bool operator==(const tuple23 &tup) const = default;
    inline constexpr auto operator<=>(const tuple23 &tup) const = default;
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
struct tuple24
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple24>,bool> = true> \
    inline tuple24 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple24>,bool> = true> \
    inline tuple24 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; v OP rhs; w OP rhs; x OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple24 &lhs, const tuple24 &rhs) \
    { return make_tuple24(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple24 &tup) { return make_tuple24(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x); }
#define OP_PRE(OP) inline tuple24 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; return *this; }
#define OP_POST(OP) inline tuple24 operator OP(int) { tuple24 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x;
    inline constexpr tuple24(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21(), const T22 &v = T22(), const T23 &w = T23(), const T24 &x = T24()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x); }
    inline constexpr bool operator==(const tuple24 &tup) const = default;
    inline constexpr auto operator<=>(const tuple24 &tup) const = default;
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
struct tuple25
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple25>,bool> = true> \
    inline tuple25 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; y OP rhs.y; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple25>,bool> = true> \
    inline tuple25 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; v OP rhs; w OP rhs; x OP rhs; y OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple25 &lhs, const tuple25 &rhs) \
    { return make_tuple25(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x, lhs.y OP rhs.y); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple25 &tup) { return make_tuple25(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x, OP tup.y); }
#define OP_PRE(OP) inline tuple25 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; OP y; return *this; }
#define OP_POST(OP) inline tuple25 operator OP(int) { tuple25 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x; T25 y;
    inline constexpr tuple25(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21(), const T22 &v = T22(), const T23 &w = T23(), const T24 &x = T24(), const T25 &y = T25()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x), y(y) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x) GET(24,T25,y)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x) GETC(24,T25,y)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x) SET(24,T25,y)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x) || bool(y); }
    inline constexpr bool operator==(const tuple25 &tup) const = default;
    inline constexpr auto operator<=>(const tuple25 &tup) const = default;
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
struct tuple26
{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple26>,bool> = true> \
    inline tuple26 &operator OP(const U &rhs) { a OP rhs.a; b OP rhs.b; c OP rhs.c; d OP rhs.d; e OP rhs.e; f OP rhs.f; g OP rhs.g; h OP rhs.h; i OP rhs.i; j OP rhs.j; k OP rhs.k; l OP rhs.l; m OP rhs.m; n OP rhs.n; o OP rhs.o; p OP rhs.p; q OP rhs.q; r OP rhs.r; s OP rhs.s; t OP rhs.t; u OP rhs.u; v OP rhs.v; w OP rhs.w; x OP rhs.x; y OP rhs.y; z OP rhs.z; return *this; }
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple26>,bool> = true> \
    inline tuple26 &operator OP(const U &rhs) { a OP rhs; b OP rhs; c OP rhs; d OP rhs; e OP rhs; f OP rhs; g OP rhs; h OP rhs; i OP rhs; j OP rhs; k OP rhs; l OP rhs; m OP rhs; n OP rhs; o OP rhs; p OP rhs; q OP rhs; r OP rhs; s OP rhs; t OP rhs; u OP rhs; v OP rhs; w OP rhs; x OP rhs; y OP rhs; z OP rhs; return *this; }
#define OP_BINARY(OP) friend inline auto operator OP(const tuple26 &lhs, const tuple26 &rhs) \
    { return make_tuple26(lhs.a OP rhs.a, lhs.b OP rhs.b, lhs.c OP rhs.c, lhs.d OP rhs.d, lhs.e OP rhs.e, lhs.f OP rhs.f, lhs.g OP rhs.g, lhs.h OP rhs.h, lhs.i OP rhs.i, lhs.j OP rhs.j, lhs.k OP rhs.k, lhs.l OP rhs.l, lhs.m OP rhs.m, lhs.n OP rhs.n, lhs.o OP rhs.o, lhs.p OP rhs.p, lhs.q OP rhs.q, lhs.r OP rhs.r, lhs.s OP rhs.s, lhs.t OP rhs.t, lhs.u OP rhs.u, lhs.v OP rhs.v, lhs.w OP rhs.w, lhs.x OP rhs.x, lhs.y OP rhs.y, lhs.z OP rhs.z); }
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple26 &tup) { return make_tuple26(OP tup.a, OP tup.b, OP tup.c, OP tup.d, OP tup.e, OP tup.f, OP tup.g, OP tup.h, OP tup.i, OP tup.j, OP tup.k, OP tup.l, OP tup.m, OP tup.n, OP tup.o, OP tup.p, OP tup.q, OP tup.r, OP tup.s, OP tup.t, OP tup.u, OP tup.v, OP tup.w, OP tup.x, OP tup.y, OP tup.z); }
#define OP_PRE(OP) inline tuple26 &operator OP() { OP a; OP b; OP c; OP d; OP e; OP f; OP g; OP h; OP i; OP j; OP k; OP l; OP m; OP n; OP o; OP p; OP q; OP r; OP s; OP t; OP u; OP v; OP w; OP x; OP y; OP z; return *this; }
#define OP_POST(OP) inline tuple26 operator OP(int) { tuple26 ret = *this; OP(*this); return ret; }
    T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; T10 j; T11 k; T12 l; T13 m; T14 n; T15 o; T16 p; T17 q; T18 r; T19 s; T20 t; T21 u; T22 v; T23 w; T24 x; T25 y; T26 z;
    inline constexpr tuple26(const T1 &a = T1(), const T2 &b = T2(), const T3 &c = T3(), const T4 &d = T4(), const T5 &e = T5(), const T6 &f = T6(), const T7 &g = T7(), const T8 &h = T8(), const T9 &i = T9(), const T10 &j = T10(), const T11 &k = T11(), const T12 &l = T12(), const T13 &m = T13(), const T14 &n = T14(), const T15 &o = T15(), const T16 &p = T16(), const T17 &q = T17(), const T18 &r = T18(), const T19 &s = T19(), const T20 &t = T20(), const T21 &u = T21(), const T22 &v = T22(), const T23 &w = T23(), const T24 &x = T24(), const T25 &y = T25(), const T26 &z = T26()): a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p), q(q), r(r), s(s), t(t), u(u), v(v), w(w), x(x), y(y), z(z) {}
    GET(0,T1,a) GET(1,T2,b) GET(2,T3,c) GET(3,T4,d) GET(4,T5,e) GET(5,T6,f) GET(6,T7,g) GET(7,T8,h) GET(8,T9,i) GET(9,T10,j) GET(10,T11,k) GET(11,T12,l) GET(12,T13,m) GET(13,T14,n) GET(14,T15,o) GET(15,T16,p) GET(16,T17,q) GET(17,T18,r) GET(18,T19,s) GET(19,T20,t) GET(20,T21,u) GET(21,T22,v) GET(22,T23,w) GET(23,T24,x) GET(24,T25,y) GET(25,T26,z)
    GETC(0,T1,a) GETC(1,T2,b) GETC(2,T3,c) GETC(3,T4,d) GETC(4,T5,e) GETC(5,T6,f) GETC(6,T7,g) GETC(7,T8,h) GETC(8,T9,i) GETC(9,T10,j) GETC(10,T11,k) GETC(11,T12,l) GETC(12,T13,m) GETC(13,T14,n) GETC(14,T15,o) GETC(15,T16,p) GETC(16,T17,q) GETC(17,T18,r) GETC(18,T19,s) GETC(19,T20,t) GETC(20,T21,u) GETC(21,T22,v) GETC(22,T23,w) GETC(23,T24,x) GETC(24,T25,y) GETC(25,T26,z)
    SET(0,T1,a) SET(1,T2,b) SET(2,T3,c) SET(3,T4,d) SET(4,T5,e) SET(5,T6,f) SET(6,T7,g) SET(7,T8,h) SET(8,T9,i) SET(9,T10,j) SET(10,T11,k) SET(11,T12,l) SET(12,T13,m) SET(13,T14,n) SET(14,T15,o) SET(15,T16,p) SET(16,T17,q) SET(17,T18,r) SET(18,T19,s) SET(19,T20,t) SET(20,T21,u) SET(21,T22,v) SET(22,T23,w) SET(23,T24,x) SET(24,T25,y) SET(25,T26,z)
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr operator bool() const { return bool(a) || bool(b) || bool(c) || bool(d) || bool(e) || bool(f) || bool(g) || bool(h) || bool(i) || bool(j) || bool(k) || bool(l) || bool(m) || bool(n) || bool(o) || bool(p) || bool(q) || bool(r) || bool(s) || bool(t) || bool(u) || bool(v) || bool(w) || bool(x) || bool(y) || bool(z); }
    inline constexpr bool operator==(const tuple26 &tup) const = default;
    inline constexpr auto operator<=>(const tuple26 &tup) const = default;
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
