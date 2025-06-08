///
/// Pointer type relying on unused space
///

#pragma once

#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Types.hpp>

namespace tkoz::stl
{

/// \brief Store a pointer with 6 bytes for 48 bit virtual addresses
/// \tparam Type the type pointed to
///
/// This class relies on the observation that although pointers are 8 bytes on
/// x86_64, the virtual address space is usually no larger than 48 bits with
/// the top 16 bits being zero. This space is used for memory alignment. At the
/// cost of a more expensive dereference and losing memory alignment, these 2
/// bytes can be used with more memory efficiency. This class is not really
/// appropriate to use for single pointers. It is best for arrays and fitting
/// a pointer into a space where it will not increase memory usage.
/// A const SixBytePointer does not apply const to the pointed to object. To
/// point to a const object, the Type parameter must be const.
///
/// This class only works with big endian currently.
/// This class only stores a pointer, does not manage memory.
/// Clients are responsible for freeing dynamic memory.
template <typename Type>
class SixBytePointer
{
private:

    static_assert(sizeof(Type*) == 8, "do not use this class in 32 bit mode");

    /// pointer value
    ushort_t mPtr[3];

    /// union for accessing pointer in 16 byte components
    union UnionHelper
    {
        Type *p;
        ushort_t s[4];
    };

    inline void _setPtr(Type *ptr)
    {
        UnionHelper h;
        h.p = ptr;
        mPtr[0] = h.s[0];
        mPtr[1] = h.s[1];
        mPtr[2] = h.s[2];
    }

public:

    /// \brief initialize as null pointer
    [[nodiscard]] inline SixBytePointer() noexcept: mPtr{0,0,0} {}

    /// \brief initialize from a pointer (allowed to be null)
    /// \param ptr the pointer to store
    [[nodiscard]] inline SixBytePointer(Type *ptr) noexcept
    {
        _setPtr(ptr);
    }

    /// \brief get the pointer
    /// \return a full 8 byte dereferenceable pointer (if not null)
    [[nodiscard]] inline Type* ptr() const noexcept
    {
        UnionHelper h;
        h.s[0] = mPtr[0];
        h.s[1] = mPtr[1];
        h.s[2] = mPtr[2];
        h.s[3] = 0;
        return h.p;
    }

    /// \brief dereference the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>&
    operator*() const noexcept
    {
        return *ptr();
    }

    /// \brief access member of the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>*
    operator->() const noexcept
    {
        return ptr();
    }

    /// \brief boolean equivalent (is the pointer non null)
    [[nodiscard]] inline operator bool() const noexcept
    {
        return mPtr[0] && mPtr[1] && mPtr[2];
    }

    /// \brief compare equality with another pointer
    [[nodiscard]] inline bool operator==(
        const SixBytePointer &other) const noexcept
    {
        return ptr() == other.ptr();
    }

    /// \brief compare 3 way with another pointer
    [[nodiscard]] inline auto operator<=>(
        const SixBytePointer &other) const noexcept
    {
        return ptr() <=> other.ptr();
    }

    /// \brief add to a pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    [[nodiscard]] inline SixBytePointer operator+(
        OffsetType offset) const noexcept
    {
        return SixBytePointer(ptr() + offset);
    }

    /// \brief subtract from a pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    [[nodiscard]] inline SixBytePointer operator-(
        OffsetType offset) const noexcept
    {
        return SixBytePointer(ptr() - offset);
    }

    /// \brief pre increment
    inline SixBytePointer& operator++() noexcept
    {
        _setPtr(ptr()+1);
        return *this;
    }

    /// \brief post increment
    [[nodiscard("prefer pre increment when return value is unused")]]
    inline SixBytePointer operator++(int) noexcept
    {
        SixBytePointer ret = *this;
        ++(*this);
        return ret;
    }

    /// \brief pre decrement
    inline SixBytePointer& operator--() noexcept
    {
        _setPtr(ptr()-1);
        return *this;
    }

    /// \brief post decrement
    [[nodiscard("prefer pre decrement when return value is unused")]]
    inline SixBytePointer operator--(int) noexcept
    {
        SixBytePointer ret = *this;
        --(*this);
        return ret;
    }
};

} // namespace tkoz::stl
