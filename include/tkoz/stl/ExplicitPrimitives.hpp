///
/// Wrappers for primitive types that do not allow implicit conversions
///

#pragma once

#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

#include <compare>

namespace tkoz::stl::wrapper
{

/// \brief Wrapper for a primitive that prevents implicit conversions
/// \tparam Type primitive type
///
/// The corresponding primitive is allowed to be converted to an
/// ExplicitPrimitive object, but not the other way because a workaround
/// could not be found for the implicit conversion system in C++ yet.
/// Using this class can provide a way to write more type safe code by keeping
/// operations to the same type.
///
/// \todo Is there a way to allow implicit conversion to the primitive?
template <concepts::isPrimitive Type>
struct ExplicitPrimitive
{
private:
    /// The value contained in this wrapper
    Type mValue;

public:
    /// The type of value in this ExplicitPrimitive object
    using ValueType = Type;

    /// Size of the contained value
    static constexpr usize_t cValueSize = sizeof(ValueType);

    /// Default constructor
    [[nodiscard]] inline constexpr ExplicitPrimitive() noexcept: mValue() {}

    /// Wrap a primitive (implicit only allowed for matching type)
    template <concepts::isPrimitive OtherType>
    [[nodiscard]] inline constexpr explicit(!meta::isSame<OtherType,Type>)
    ExplicitPrimitive(OtherType value) noexcept: mValue(value) {}

    /// Construct from another ExplicitPrimitive
    template <concepts::isPrimitive OtherType>
    [[nodiscard]] inline constexpr explicit
    ExplicitPrimitive(const ExplicitPrimitive &other) noexcept
        : mValue(other.mValue) {}

    /// Conversion to a primitive (explicit only)
    /// \note could not find a workaround to allow implicit conversion yet
    /// \todo is there a way to allow an implicit operator Type()
    template <concepts::isPrimitive OtherType>
    [[nodiscard]] inline constexpr explicit operator OtherType() const noexcept
    {
        return static_cast<OtherType>(mValue);
    }

    /// Conversion to another ExplicitPrimitive
    template <concepts::isPrimitive OtherType>
    [[nodiscard]] inline constexpr explicit
    operator ExplicitPrimitive<OtherType>() const noexcept
    {
        return ExplicitPrimitive<OtherType>(mValue);
    }

    /// Get the value as the primitive type
    [[nodiscard]] inline constexpr Type value() const noexcept
    {
        return mValue;
    }

    /// binary addition (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator+(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue + b.mValue);
    }

    /// binary subtraction (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator-(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue - b.mValue);
    }

    /// unary positive (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator+() const noexcept
    {
        return ExplicitPrimitive(+mValue);
    }

    /// unary negative (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator-() const noexcept
    {
        return ExplicitPrimitive(-mValue);
    }

    /// unary invert bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,ExplicitPrimitive>
    operator~() const noexcept
    {
        return ExplicitPrimitive(~mValue);
    }

    /// binary multiplication (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator*(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue * b.mValue);
    }

    /// binary division (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>
    operator/(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue / b.mValue);
    }

    /// binary modulus (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>
    operator%(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue % b.mValue);
    }

    /// unary pre increment (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>&
    operator++() noexcept
    {
        ++mValue;
        return *this;
    }

    /// unary post increment (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard("prefer pre-increment when return value is unused")]]
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>
    operator++(int) noexcept
    {
        ExplicitPrimitive ret = *this;
        ++mValue;
        return ret;
    }

    /// unary pre decrement (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>&
    operator--() noexcept
    {
        --mValue;
        return *this;
    }

    /// unary post decrement (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard("prefer pre-decrement when return value is unused")]]
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>
    operator--(int) noexcept
    {
        ExplicitPrimitive ret = *this;
        --mValue;
        return ret;
    }

    /// binary compare equal (all types)
    /// automatically generates operator!=
    [[nodiscard]] inline constexpr bool
    operator==(const ExplicitPrimitive &other) const noexcept
    {
        return mValue == other.mValue;
    }

    /// binary compare 3 way (all types)
    /// automatically generates < <= > >=
    /// integer types are strongly ordered
    /// floating point types are partially ordered
    template <typename _Dummy = Type>
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,
        meta::Conditional<concepts::isPrimitiveInteger<_Dummy>,
                          std::strong_ordering,std::partial_ordering>>
    operator<=>(const ExplicitPrimitive &other) const noexcept
    {
        return mValue <=> other.mValue;
    }

    /// binary and bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,ExplicitPrimitive>
    operator&(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue & b.mValue);
    }

    /// binary or bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,ExplicitPrimitive>
    operator|(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue | b.mValue);
    }

    /// binary xor bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] friend inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,ExplicitPrimitive>
    operator^(const ExplicitPrimitive &a, const ExplicitPrimitive &b) noexcept
    {
        return ExplicitPrimitive(a.mValue ^ b.mValue);
    }

    /// binary left shift (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>
    operator<<(const ExplicitPrimitive &s) const noexcept
    {
        return ExplicitPrimitive(mValue << s);
    }

    /// binary right shift (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>
    operator>>(const ExplicitPrimitive &s) const noexcept
    {
        return ExplicitPrimitive(mValue >> s);
    }

    /// immediate addition (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>&
    operator+=(const ExplicitPrimitive &other) noexcept
    {
        mValue += other.mValue;
        return *this;
    }

    /// immediate subtraction (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>&
    operator-=(const ExplicitPrimitive &other) noexcept
    {
        mValue -= other.mValue;
        return *this;
    }

    /// immediate multiplication (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>&
    operator*=(const ExplicitPrimitive &other) noexcept
    {
        mValue *= other.mValue;
        return *this;
    }

    /// immediate division (numbers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveNumber<_Dummy>,ExplicitPrimitive>&
    operator/=(const ExplicitPrimitive &other) noexcept
    {
        mValue /= other.mValue;
        return *this;
    }

    /// immediate modulus (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>&
    operator%=(const ExplicitPrimitive &other) noexcept
    {
        mValue %= other.mValue;
        return *this;
    }

    /// immedeiate and bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,
                  ExplicitPrimitive>&
    operator&=(const ExplicitPrimitive &other) noexcept
    {
        mValue &= other.mValue;
        return *this;
    }

    /// immediate or bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,
                   ExplicitPrimitive>&
    operator|=(const ExplicitPrimitive &other) noexcept
    {
        mValue |= other.mValue;
        return *this;
    }

    /// immediate xor bits (integers only)
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveIntegerOrBool<_Dummy>,
                   ExplicitPrimitive>&
    operator^=(const ExplicitPrimitive &other) noexcept
    {
        mValue ^= other.mValue;
        return *this;
    }

    /// immediate shift left (integers only, primitive shift amount)
    /// implicit conversions are allowed for the shift amount
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>&
    operator<<=(int s) noexcept
    {
        mValue <<= s;
        return *this;
    }

    /// immediate shift left (integers only, explicit primitive shift amount)
    template <typename OtherType>
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<OtherType>,ExplicitPrimitive>&
    operator<<=(const ExplicitPrimitive<OtherType> &other) noexcept
    {
        return (*this) <<= static_cast<int>(other);
    }

    /// immediate shift right (integers only, primitive shift amount)
    /// implicit conversions are allowed for the shift amount
    template <typename _Dummy = Type> // needed for SFINAE
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<_Dummy>,ExplicitPrimitive>&
    operator>>=(int s) noexcept
    {
        mValue >>= s;
        return *this;
    }

    /// immediate shift right (integers only, explicit primitive shift amount)
    template <typename OtherType>
    inline constexpr
    meta::EnableIf<concepts::isPrimitiveInteger<OtherType>,ExplicitPrimitive>&
    operator>>=(const ExplicitPrimitive<OtherType> &other) noexcept
    {
        return (*this) >>= static_cast<int>(other);
    }
};

using ExplicitBool    = ExplicitPrimitive<bool>;
using ExplicitChar    = ExplicitPrimitive<char>;
using ExplicitSChar   = ExplicitPrimitive<signed char>;
using ExplicitUChar   = ExplicitPrimitive<unsigned char>;
using ExplicitSShort  = ExplicitPrimitive<signed short>;
using ExplicitUShort  = ExplicitPrimitive<unsigned short>;
using ExplicitSInt    = ExplicitPrimitive<signed int>;
using ExplicitUInt    = ExplicitPrimitive<unsigned int>;
using ExplicitSLong   = ExplicitPrimitive<signed long>;
using ExplicitULong   = ExplicitPrimitive<unsigned long>;
using ExplicitSLL     = ExplicitPrimitive<signed long long>;
using ExplicitULL     = ExplicitPrimitive<unsigned long long>;
using ExplicitFloat   = ExplicitPrimitive<float>;
using ExplicitDouble  = ExplicitPrimitive<double>;
using ExplicitLDouble = ExplicitPrimitive<long double>;

} // namespace tkoz::stl::wrapper
