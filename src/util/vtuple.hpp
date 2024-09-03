/*
Variadic Tuple
- similar to std::tuple
- publically accessible members
  - v (same as get<0>())
  - vs (the remaining values, possibly an empty tuple)
- member type<i> to get type of ith element
- for tuple of size n
  - access members by get<i>() (0 <= i < n)
  - set members by set<i>(val) (0 <= i < n)
- constructors
  - default
  - vtuple(T v, Ts... vs)
  - vtuple(T v, vtuple<Ts...> vs)
- convertible to bool
- overloaded pre/post increment/decrement for parallel operation
- overloaded compare operators
- overloaded compound assignment for parallel operations
- overloaded unary and binary operators for parallel operations

make_vtuple(v1,v2,...) - create from values, types automatically determined
make_vtuple(v1, vtuple vs) - create from head and tail
concat_vtuple(t1,t2) - concatenates values into a new vtuple in order
*/

#pragma once

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <utility>

namespace tkoz
{

// variadic tuple, a fixed length sequence of values, each with their own type
template <typename ...Ts>
struct vtuple
{
    inline constexpr bool operator!() const noexcept { return false; }
    inline constexpr explicit operator bool() const noexcept { return false; }
    inline vtuple &operator++() noexcept { return *this; }
    inline vtuple &operator--() noexcept { return *this; }
    inline vtuple operator++(int) noexcept { return *this; }
    inline vtuple operator--(int) noexcept { return *this; }
    inline constexpr bool operator==(const vtuple &) const = default;
    inline constexpr auto operator<=>(const vtuple &) const = default;
#define OPEQ(OP) inline vtuple &operator OP(const vtuple&) { return *this; }
    OPEQ(+=) OPEQ(-=) OPEQ(*=) OPEQ(/=) OPEQ(%=)
    OPEQ(&=) OPEQ(|=) OPEQ(^=) OPEQ(<<=) OPEQ(>>=)
#undef OPEQ
#define OPBIN(OP) friend inline auto operator OP(const vtuple&, const vtuple&) { return vtuple(); }
    OPBIN(+) OPBIN(-) OPBIN(*) OPBIN(/) OPBIN(%)
    OPBIN(&) OPBIN(|) OPBIN(^) OPBIN(<<) OPBIN(>>)
#undef OPBIN
#define OPUN(OP) friend inline auto operator OP(const vtuple&) { return vtuple(); }
    OPUN(-) OPUN(+) OPUN(~) OPUN(*) OPUN(&)
#undef OPUN
};

template <typename ...Ts>
inline constexpr vtuple<Ts...> make_vtuple(const Ts&... vs);

template <typename T, typename ...Ts>
inline constexpr vtuple<T,Ts...> make_vtuple(const T &v, const vtuple<Ts...> &vs);

namespace _internal
{

template <size_t i, typename T, typename ...Ts>
struct _vtuple_type { static_assert(i <= sizeof...(Ts)); typedef _vtuple_type<i-1,Ts...>::type type; };

template <typename T, typename ...Ts>
struct _vtuple_type<0,T,Ts...> { typedef T type; };

}

template <typename T, typename ...Ts>
struct vtuple<T,Ts...>
{
public:
    T v;
    vtuple<Ts...> vs;
    // type info
    template <size_t ind> using type = typename _internal::_vtuple_type<ind,T,Ts...>::type;
    // default ctor
    inline constexpr vtuple(): v(), vs() {}
    // initialize with sequence of values
    inline constexpr vtuple(const T &v, const Ts&... vs): v(v), vs(vs...) {}
    // initialize with the first value and another vtuple
    inline constexpr vtuple(const T &v, const vtuple<Ts...> &vs): v(v), vs(vs) {}

    // get

    template <size_t ind, std::enable_if_t<ind==0,bool> = true>
    inline constexpr auto &get() { return v; }
    template <size_t ind, std::enable_if_t<ind!=0,bool> = true>
    inline constexpr auto &get()
    {
        static_assert(ind <= sizeof...(Ts));
        return vs.template get<ind-1>();
    }
    template <size_t ind, std::enable_if_t<ind==0,bool> = true>
    inline constexpr const auto &get() const { return v; }
    template <size_t ind, std::enable_if_t<ind!=0,bool> = true>
    inline constexpr const auto &get() const
    {
        static_assert(ind <= sizeof...(Ts));
        return vs.template get<ind-1>();
    }

    // set

    template <size_t ind, std::enable_if_t<ind==0,bool> = true>
    inline void set(const T &val) { v = val; }
    template <size_t ind, std::enable_if_t<ind!=0,bool> = true>
    inline void set(const type<ind> &val)
    {
        static_assert(ind <= sizeof...(Ts));
        vs.template set<ind-1>(val);
    }

    // bool

    inline constexpr bool operator!() const { return !bool(*this); }
    inline constexpr explicit operator bool() const { return bool(v) || bool(vs); }

    // inc/dec

    inline vtuple &operator++() { ++v; ++vs; return *this; }
    inline vtuple &operator--() { --v; --vs; return *this; }
    inline vtuple operator++(int) { vtuple ret = *this; ++(*this); return ret; }
    inline vtuple operator--(int) { vtuple ret = *this; --(*this); return ret; }

    // compare

    inline constexpr bool operator==(const vtuple &tup) const = default;
    inline constexpr auto operator<=>(const vtuple &tup) const = default;

    // compound assignment
#define OPEQ(OP) inline vtuple &operator OP(const vtuple &tup) { v OP tup.v; vs OP tup.vs; return *this; }
    OPEQ(+=) OPEQ(-=) OPEQ(*=) OPEQ(/=) OPEQ(%=)
    OPEQ(&=) OPEQ(|=) OPEQ(^=) OPEQ(<<=) OPEQ(>>=)
#undef OPEQ

    // binary
#define OPBIN(OP) friend inline auto operator OP(const vtuple &lhs, const vtuple &rhs) { return make_vtuple(lhs.v OP rhs.v, lhs.vs OP rhs.vs); }
    OPBIN(+) OPBIN(-) OPBIN(*) OPBIN(/) OPBIN(%)
    OPBIN(&) OPBIN(|) OPBIN(^) OPBIN(<<) OPBIN(>>)
#undef OPBIN

    // unary
#define OPUN(OP) friend inline auto operator OP(const vtuple &tup) { return make_vtuple(OP tup.v, OP tup.vs); }
    OPUN(-) OPUN(+) OPUN(~) OPUN(*) OPUN(&)
#undef OPUN
};

// create vtuple from sequence of values
template <typename ...Ts>
inline constexpr vtuple<Ts...> make_vtuple(const Ts&... vs)
{
    return vtuple<Ts...>(vs...);
}

// create vtuple with first value and another vtuple
template <typename T, typename ...Ts>
inline constexpr vtuple<T,Ts...> make_vtuple(const T &v, const vtuple<Ts...> &vs)
{
    return vtuple<T,Ts...>(v,vs);
}

namespace _internal
{

template <typename ...Ts, typename ...Us, size_t ...Ti, size_t ...Ui>
inline constexpr vtuple<Ts...,Us...> _concat_vtuple_helper(const vtuple<Ts...> &ts, const vtuple<Us...> &us, std::index_sequence<Ti...>, std::index_sequence<Ui...>)
{
    return make_vtuple(ts.template get<Ti>()..., us.template get<Ui>()...);
}

}

// concatenate 2 vtuples in order into a new vtuple
template <typename ...Ts, typename ...Us, typename Ti = std::make_index_sequence<sizeof...(Ts)>, typename Ui = std::make_index_sequence<sizeof...(Us)>>
inline constexpr vtuple<Ts...,Us...> concat_vtuple(const vtuple<Ts...> &ts, const vtuple<Us...> &us)
{
    return _internal::_concat_vtuple_helper(ts,us,Ti(),Ui());
}

}

// STL specializations to allow use with structured bindings

template <typename ...Ts>
struct std::tuple_size<tkoz::vtuple<Ts...>> : std::integral_constant<size_t,sizeof...(Ts)> {};

template <size_t ind, typename ...Ts>
struct std::tuple_element<ind, tkoz::vtuple<Ts...>> : std::type_identity<typename tkoz::vtuple<Ts...>::type<ind>> {};
