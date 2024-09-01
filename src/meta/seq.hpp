#include <array>
#include <cstddef>
#include <type_traits>

namespace tkoz::meta
{

// compile time sequence of values (parameter pack)
template <typename T, T ...vs> struct seq {};

// compile time sequence of indexes
template <size_t ...vs> using iseq = seq<size_t,vs...>;

namespace _internal
{

template <typename T, typename ...SEQ> struct _concat_seq_helper
{
    using type = seq<T>;
};

template <typename T, T ...us, T ...vs>
auto _concat_seq_func(seq<T,us...>, seq<T,vs...>)
{
    return seq<T,us...,vs...>();
}

template <typename T, typename U, U ...us, typename ...SEQ>
struct _concat_seq_helper<T,seq<U,us...>,SEQ...>
{
    static_assert(std::is_same_v<T,U>,"all sequences must have same value type");
    using type = decltype(_concat_seq_func(seq<T,us...>(),typename _concat_seq_helper<T,SEQ...>::type()));
};

}

// concatenate sequences (all must have same value type)
template <typename ...SEQ> struct concat_seq_s
{
    static_assert(sizeof...(SEQ),"must use at least 1 sequence");
};

// concatenate sequences (all must have same value type)
template <typename T, T ...us, typename ...SEQ>
struct concat_seq_s<seq<T,us...>,SEQ...>
{
    using type = _internal::_concat_seq_helper<T,seq<T,us...>,SEQ...>::type;
};

// concatenate sequences (all must have same value type)
template <typename ...SEQ>
using concat_seq_t = concat_seq_s<SEQ...>::type;

namespace _internal
{

// sequence for [lo,hi] using binary divide and conquer to avoid linear recursion depth
template <typename T, T lo, T hi>
struct _make_seq_b
{
    static_assert(lo < hi);
    static constexpr T _mid = (lo+hi)/2;
    using type = decltype(_concat_seq_func(typename _make_seq_b<T,lo,_mid>::type(), typename _make_seq_b<T,_mid+1,hi>::type()));
};

template <typename T, T lo>
struct _make_seq_b<T,lo,lo>
{
    using type = seq<T,lo>;
};

// sequence for [lo,hi] using basic linear recursion depth
template <typename T, T lo, T hi, T ...vs>
struct _make_seq_l
{
    static_assert(lo < hi);
    using type = _make_seq_l<T,lo,hi-1,hi,vs...>::type;
};

template <typename T, T lo, T ...vs>
struct _make_seq_l<T,lo,lo,vs...>
{
    using type = seq<T,lo,vs...>;
};

// typedef for the one to use (_make_seq_b or _make_seq_l)
template <typename T, T lo, T hi>
using _make_seq = _make_seq_b<T,lo,hi>;

}

// sequence from range [lo,hi)
template <typename T, T lo, T hi>
struct seq_range_s
{
    static_assert(lo < hi);
    using type = _internal::_make_seq<T,lo,hi-1>::type;
};

template <typename T, T lo>
struct seq_range_s<T,lo,lo>
{
    using type = seq<T>;
};

// index sequence from range [lo,hi)
template <size_t lo, size_t hi>
using iseq_range_s = seq_range_s<size_t,lo,hi>;

// sequence from range [lo,hi)
template <typename T, T lo, T hi>
using seq_range_t = seq_range_s<T,lo,hi>::type;

// index sequence from range [lo,hi)
template <size_t lo, size_t hi>
using iseq_range_t = iseq_range_s<lo,hi>::type;

// static array from parameter pack
template <typename T, T ...vs>
struct array_s
{
    static constexpr std::array<T,sizeof...(vs)> value = {vs...};
};

// static array from parameter pack
template <typename T, T ...vs>
static constexpr std::array<T,sizeof...(vs)> array_v = {vs...};

// static array from parameter pack
template <typename T, typename ...Ts>
static constexpr auto array_f(T v, Ts ...vs)
{
    return std::array<T,1+sizeof...(vs)>{v,vs...};
}

// static array from parameter pack with map function
template <typename F, typename T, typename ...Ts>
static constexpr auto map_array_f(F f, T v, Ts ...vs)
{
    return std::array<decltype(f(v)),1+sizeof...(vs)>{f(v),f(vs)...};
}

namespace _internal
{

template <typename T, T ...vs>
constexpr std::array<T,sizeof...(vs)> _seq_to_arr(seq<T,vs...>) { return {vs...}; }

}

// static array from sequence type
template <typename T> struct seq_array_s {};

// static array from sequence type
template <typename T, T ...vs>
struct seq_array_s<seq<T,vs...>>
{
    static constexpr std::array<T,sizeof...(vs)> value = _internal::_seq_to_arr(seq<T,vs...>());
};

// static array from sequence type
template <typename T, T ...vs>
static constexpr std::array<T,sizeof...(vs)> seq_array_v = seq_array_s<seq<T,vs...>>::value;

// static array from sequence type
template <typename T, T ...vs>
static constexpr std::array<T,sizeof...(vs)> seq_array_v<seq<T,vs...>> = seq_array_v<T,vs...>;

// static array from sequence type with mapping function
template <typename F, typename T, T ...vs>
static constexpr auto seqmap_array_f(F f, seq<T,vs...>)
{
    return std::array<decltype(f(T())),sizeof...(vs)>{f(vs)...};
}

namespace _internal
{

template <typename T, T ...vs, size_t ...is>
seq<T,array_v<T,vs...>[is]...> _take_from_parameter_pack(seq<T,vs...>,iseq<is...>) {}

}

// take part of beginning of a sequence
template <typename SEQ, size_t len> struct take_seq_beg_s {};

// take part of beginning of a sequence
template <typename T, T ...vs, size_t len>
struct take_seq_beg_s<seq<T,vs...>,len>
{
    static_assert(len <= sizeof...(vs));
    using type = decltype(_internal::_take_from_parameter_pack(seq<T,vs...>(),iseq_range_t<0,len>()));
};

// take part of beginning of a sequence
template <typename T, size_t len>
using take_seq_beg_t = take_seq_beg_s<T,len>::type;

// take part of ending of a sequence
template <typename SEQ, size_t len> struct take_seq_end_s {};

// take part of ending of a sequence
template <typename T, T ...vs, size_t len>
struct take_seq_end_s<seq<T,vs...>,len>
{
    static_assert(len <= sizeof...(vs));
    using type = decltype(_internal::_take_from_parameter_pack(seq<T,vs...>(),iseq_range_t<sizeof...(vs)-len,sizeof...(vs)>()));
};

// take part of ending of a sequence
template <typename SEQ, size_t len>
using take_seq_end_t = take_seq_end_s<SEQ,len>::type;

}
