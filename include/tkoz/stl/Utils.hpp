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
[[nodiscard]] inline constexpr meta::RemoveRef<Type>&& move(Type &&t) noexcept
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
inline constexpr void swap(Type &a, Type &b)
{
    Type t(move(a));
    a = move(b);
    b = move(t);
}

/// \brief forwarding reference (lvalue to lvalue)
/// \tparam Type the type being passed
/// \param t the passed argument to preserve reference type for
/// \note supposedly equivalent to the implementation in libstdc++
template <typename Type>
[[nodiscard]] inline constexpr
Type&& fwdRef(meta::RemoveRef<Type> &t) noexcept
{
    return static_cast<Type&&>(t);
}

/// \brief forwarding reference (rvalue to rvalue, pass by value to rvalue)
/// \tparam Type the type being passed
/// \param t the passed argument to preserve reference type for
/// \note supposedly equivalent to the implementation in libstdc++
template <typename Type>
[[nodiscard]] inline constexpr
Type&& fwdRef(meta::RemoveRef<Type> &&t) noexcept
{
    static_assert(!meta::isLVRef<Type>, "cannot forward rvalue as lvalue");
    return static_cast<Type&&>(t);
}

} // namespace tkoz::stl
