///
/// utility functions
///

#pragma once

#include <tkoz/stl/Meta.hpp>

namespace tkoz::stl
{

/// \brief move reference for a value
/// \tparam Type type of the object
/// \param t the value to get a move reference for
/// \return a move reference to `t`
template <typename Type>
[[nodiscard]] inline meta::RemoveRef<Type>&& move(Type &&t) noexcept
{
    return static_cast<meta::RemoveRef<Type>&&>(t);
}

/// \brief swap 2 values efficiently
/// \tparam Type type of values
/// \param a one of the values
/// \param b one of the values
///
/// In order to efficiently swap custom types, they must implement the move
/// constructor and move assignment.
template <typename Type>
inline void swap(Type &a, Type &b)
{
    Type t(move(a));
    a = move(b);
    b = move(t);
}

} // namespace tkoz::stl
