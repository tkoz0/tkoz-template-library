///
/// Pointer type relying on unused space
///

#pragma once

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
    ushort_t _ptr[3];

    /// union for accessing pointer in 16 byte components
    union UnionHelper
    {
        Type *p;
        ushort_t s[4];
    };

public:

    /// \brief initialize as null pointer
    [[nodiscard]] inline SixBytePointer() noexcept: _ptr({0,0,0}) {}

    /// \brief initialize from a pointer (allowed to be null)
    /// \param ptr the pointer to store
    [[nodiscard]] inline SixBytePointer(Type *ptr) noexcept
    {
        UnionHelper h;
        h.p = ptr;
        _ptr[0] = h.s[0];
        _ptr[1] = h.s[1];
        _ptr[2] = h.s[2];
    }

    /// \brief get the pointer (const)
    /// \return a full 8 byte dereferenceable pointer (if not null)
    [[nodiscard]] inline Type* ptr() noexcept
    {
        UnionHelper h;
        h.s[0] = _ptr[0];
        h.s[1] = _ptr[1];
        h.s[2] = _ptr[2];
        h.s[3] = 0;
        return h.p;
    }

    /// \brief get the pointer (non const)
    /// \return a full 8 byte dereferenceable pointer (if not null)
    [[nodiscard]] inline const Type* ptr() const noexcept
    {
        return const_cast<const Type*>(
            const_cast<SixBytePointer*>(this)->ptr());
    }

    /// \brief dereference the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SNIFAE
    [[nodiscard]] inline meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>&
    operator*() noexcept
    {
        return *ptr();
    }

    /// \brief dereference the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline const meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>&
    operator*() const noexcept
    {
        return *ptr();
    }

    /// \brief access member of the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>*
    operator->() noexcept
    {
        return ptr();
    }

    /// \brief access member of the represented pointer (no null check)
    /// \note not available for void pointer
    template <typename _Dummy = Type> // needed for SFINAE
    [[nodiscard]] inline const meta::EnableIf<!meta::isVoid<_Dummy>,_Dummy>*
    operator->() const noexcept
    {
        return ptr();
    }

    /// \brief boolean equivalent (is the pointer non null)
    [[nodiscard]] inline operator bool() const noexcept
    {
        return _ptr[0] && _ptr[1] && _ptr[2];
    }
};

} // namespace tkoz::stl
