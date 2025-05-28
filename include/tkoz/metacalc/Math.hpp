///
/// Mathematical calculations with template metaprogramming
///

#pragma once

#include <tkoz/metacalc/Lists.hpp>

#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

namespace tkoz::metacalc
{

namespace _detail
{

template <bool getMax, isList List0>
struct _MaxMinImpl
{
    using Lo = ListSplitLo<List0>;
    using Hi = ListSplitHi<List0>;
    static constexpr List0::tValueType loMax = _MaxMinImpl<getMax,Lo>::value;
    static constexpr List0::tValueType hiMax = _MaxMinImpl<getMax,Hi>::value;
    static constexpr List0::tValueType value =
        getMax ? (loMax > hiMax ? loMax : hiMax)
               : (loMax < hiMax ? loMax : hiMax);
};

template <bool getMax, typename ValueType, ValueType value0>
struct _MaxMinImpl<getMax,List<ValueType,value0>>
{
    static constexpr ValueType value = value0;
};

} // namespace _detail

/// Maximum of a parameter pack
template <typename ValueType, ValueType value0, ValueType ...values>
static const constexpr ValueType packMax =
    _detail::_MaxMinImpl<true,List<ValueType,value0,values...>>::value;

/// Minimum of a parameter pack
template <typename ValueType, ValueType value0, ValueType ...values>
static const constexpr ValueType packMin =
    _detail::_MaxMinImpl<false,List<ValueType,value0,values...>>::value;

/// Sum of a parameter pack
template <typename ValueType, ValueType ...values>
static const constexpr ValueType packSum =
    (static_cast<ValueType>(0) + ... + values);

/// Product of a parameter pack
template <typename ValueType, ValueType ...values>
static const constexpr ValueType packProd =
    (static_cast<ValueType>(1) * ... * values);

} // namespace tkoz::metacalc
