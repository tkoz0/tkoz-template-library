///
/// Template metaprogramming utilities for more advanced calculations
///

#pragma once

namespace tkoz::metacalc
{

/// Logical AND of a parameter pack
template <bool ...values>
static constexpr bool packAnd = (true && ... && values);

/// Logical OR of a parameter pack
template <bool ...values>
static constexpr bool packOr = (false || ... || values);

} // namespace tkoz::metacalc
