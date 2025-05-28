///
/// Lists for template metaprogramming
///

#pragma once

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

namespace tkoz::metacalc
{

using tkoz::stl::usize_t;

/// \brief Store a list/sequence of values in a parameter pack
/// \tparam ValueType type of values to store
/// \tparam values values in the list
template <typename ValueType, ValueType ...values>
struct List
{
    using tValueType = ValueType;
    static constexpr ValueType cValues[] = {values...};
    static constexpr usize_t cLength = sizeof...(values);
};

namespace _detail
{
template <typename T>
struct _IsListImpl: tkoz::stl::meta::FalseValue {};
template <typename ValueType, ValueType ...values>
struct _IsListImpl<List<ValueType,values...>>: tkoz::stl::meta::TrueValue {};
} // namespace _detail

template <typename T>
concept isList = _detail::_IsListImpl<T>::value;

/// \brief list of indexes (usize_t integers >= 0)
/// \tparam values integer indexes (>= 0)
template <usize_t ...values>
using IndexList = List<usize_t,values...>;

template <typename T>
concept isIndexList = isList<T>
    && tkoz::stl::meta::isSame<typename T::tValueType,tkoz::stl::usize_t>;

namespace _detail
{

// use decltype(_ConcatList2(type1(),type2())) to concatenate parameter packs
template <typename ValueType, ValueType ...values1, ValueType ...values2>
auto _ConcatList2(List<ValueType,values1...>, List<ValueType,values2...>)
{
    return List<ValueType,values1...,values2...>();
}

template <usize_t beg, usize_t end>
struct _MakeIndexRange
{
    static_assert(beg <= end);
    // construct sequence with binary split to limit recursion depth
    static constexpr const usize_t mid = (beg + end) / 2;
    using left = _MakeIndexRange<beg,mid>::type;
    using right = _MakeIndexRange<mid,end>::type;
    using type = decltype(_ConcatList2(left(),right()));
};

template <usize_t n>
struct _MakeIndexRange<n,n> { using type = IndexList<>; };

template <usize_t n>
struct _MakeIndexRange<n,n+1> { using type = IndexList<n>; };

} // namespace _detail

/// \brief Create an index sequence [beg,end)
/// \tparam beg starting index
/// \tparam end one past end index
///
/// The resulting type is IndexList<beg,beg+1,beg+2,...,end-1>
template <usize_t beg, usize_t end>
    requires (beg <= end)
using IndexRange = _detail::_MakeIndexRange<beg,end>::type;

// concat lists implemented as a simple fold for now
// there probably will not be enough for binary splitting to benefit
namespace _detail
{

template <isList List0, isList ...Lists>
    requires (true && ...
        && tkoz::stl::meta::isSame<typename Lists::tValueType,
                                   typename List0::tValueType>)
struct _ConcatListImpl
{
    using type = List0;
};

template <typename ValueType,
          ValueType ...values0,
          ValueType ...values1,
          isList ...Lists>
    requires (true && ...
        && tkoz::stl::meta::isSame<typename Lists::tValueType,ValueType>)
struct _ConcatListImpl<List<ValueType,values0...>,
                       List<ValueType,values1...>,
                       Lists...>
{
    using type = _ConcatListImpl<decltype(
        _ConcatList2(List<ValueType,values0...>(),
                     List<ValueType,values1...>())),Lists...>::type;
};

} // namespace _detail

/// \brief Concatenates parameter packs of List types into a new List
/// \tparam List0 first List (at least one required)
/// \tparam Lists other List types, must have same ValueType
template <isList List0, isList ...Lists>
    requires (true && ...
        && tkoz::stl::meta::isSame<typename List0::tValueType,
                                   typename Lists::tValueType>)
using ConcatLists = _detail::_ConcatListImpl<List0,Lists...>::type;

namespace _detail
{

template <typename ValueType, ValueType ...values, usize_t ...indexes>
auto _listSelectImpl(List<ValueType,values...>, IndexList<indexes...>)
{
    return List<ValueType,List<ValueType,values...>::cValues[indexes]...>();
}

template <typename ValueType, ValueType ...values>
auto _listSplitImplLo(List<ValueType,values...> list)
{
    static constexpr usize_t half = sizeof...(values) / 2;
    using IS = IndexRange<0,half>;
    return _listSelectImpl(list,IS());
}

template <typename ValueType, ValueType ...values>
auto _listSplitImplHi(List<ValueType,values...> list)
{
    static constexpr usize_t half = sizeof...(values) / 2;
    using IS = IndexRange<half,sizeof...(values)>;
    return _listSelectImpl(list,IS());
}

} // namespace _detail

/// Select parts of a List parameter pack by indexes
/// \tparam List0 list to select from
/// \tparam Indexes indexes to select
template <isList List0, isIndexList Indexes>
using ListSelect = decltype(_detail::_listSelectImpl(List0(),Indexes()));

/// Select lower half indexes from a list (for binary split)
/// \tparam List0 list to select from
template <isList List0>
using ListSplitLo = decltype(_detail::_listSplitImplLo(List0()));

/// Select upper half indexes from a list (for binary split)
/// \tparam List0 list to select from
template <isList List0>
using ListSplitHi = decltype(_detail::_listSplitImplHi(List0()));

} // namespace tkoz::metacalc
