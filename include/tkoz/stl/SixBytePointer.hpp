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
/// cost of a more expensive dereference and losing 8 byte memory alignment,
/// these 2 bytes can be discarded for more memory efficiency. This class is
/// not really appropriate to use for single pointers. It is best for arrays
/// and fitting a pointer into a space where it will not increase memory usage.
/// A const SixBytePointer does not attempt to apply const correctness.
///
/// Using this is technically undefined behavior but as long as we have 48 bit
/// virtual addresses on x86_64, it may provide benefits in some use cases.
///
/// This class only works with big endian currently.
/// This class only stores a pointer, does not manage memory.
/// Clients are responsible for freeing dynamic memory.
/// This class does not enforce any const correctness.
template <typename Type>
class SixBytePointer
{
private:

// TODO make a macro library for stuff like this
#if __x86_64__
    static_assert(sizeof(Type*) == 8, "this class is only for x86_64 with "
        "48 bit virtual addresses where the high 16 bits are always zero");
#else
    static_assert(0, "this class is only for x86_64 with "
        "48 bit virtual addresses where the high 16 bits are always zero");
#endif

    /// pointer value
    ushort_t _ptr[3];

    /// union for accessing pointer in 16 byte components
    union UnionHelper
    {
        Type *p;
        ushort_t s[4];
    };

    /// store relevant 6 bytes from pointer
    inline void _setPtr(Type * const ptr) noexcept
    {
        UnionHelper h;
        h.p = ptr;
        _ptr[0] = h.s[0];
        _ptr[1] = h.s[1];
        _ptr[2] = h.s[2];
    }

public:

    /// \brief initialize as null pointer
    [[nodiscard]] inline SixBytePointer() noexcept: _ptr{0,0,0} {}

    /// \brief initialize from a pointer (allowed to be null)
    /// \param ptr the pointer to store
    [[nodiscard]] inline SixBytePointer(Type * const ptr) noexcept
    {
        _setPtr(ptr);
    }

    /// \brief get the pointer
    /// \return a full 8 byte dereferenceable pointer (if not null)
    [[nodiscard]] inline Type* ptr() const noexcept
    {
        UnionHelper h;
        h.s[0] = _ptr[0];
        h.s[1] = _ptr[1];
        h.s[2] = _ptr[2];
        h.s[3] = 0;
        return h.p;
    }

    /// \brief dereference the represented pointer (no null check)
    /// \note not available for void pointer
    /// \note auto& is used because Type& causes a compiler error with void
    [[nodiscard]] inline auto& operator*() const noexcept
        requires (!meta::isVoid<Type>)
    {
        return *ptr();
    }

    /// \brief access member of the represented pointer (no null check)
    /// \note not available for void pointer
    [[nodiscard]] inline Type* operator->() const noexcept
        requires (!meta::isVoid<Type>)
    {
        return ptr();
    }

    /// \brief boolean equivalent (is the pointer non null)
    [[nodiscard]] inline operator bool() const noexcept
    {
        return _ptr[0] && _ptr[1] && _ptr[2];
    }

    /// \brief convert to another pointer (implicit if matching type)
    template <typename OtherType>
    [[nodiscard]] inline explicit(!meta::isSame<Type,OtherType>)
    operator OtherType*() const noexcept
    {
        return reinterpret_cast<OtherType*>(ptr());
    }

    /// \brief convert to another SixBytePointer
    template <typename OtherType>
    [[nodiscard]] inline explicit
    operator SixBytePointer<OtherType>() const noexcept
    {
        return SixBytePointer<OtherType>(static_cast<OtherType*>(*this));
    }

    /// \brief compare pointer equality
    [[nodiscard]] friend inline bool operator==(
        const SixBytePointer left, const SixBytePointer right) noexcept
    {
        return left.ptr() == right.ptr();
    }

    /// \brief compare pointer equality
    template <concepts::isSameIgnoreCV<Type> TypeCV>
    [[nodiscard]] friend inline bool operator==(
        const SixBytePointer left, TypeCV * const right) noexcept
    {
        return left.ptr() == right;
    }

    /// \brief compare pointer equality
    template <concepts::isSameIgnoreCV<Type> TypeCV>
    [[nodiscard]] friend inline bool operator==(
        TypeCV * const left, const SixBytePointer right) noexcept
    {
        return left == right.ptr();
    }

    /// \brief compare pointers 3 way
    [[nodiscard]] friend inline auto operator<=>(
        const SixBytePointer left, const SixBytePointer right) noexcept
    {
        return left.ptr() <=> right.ptr();
    }

    /// \brief compare pointers 3 way
    template <concepts::isSameIgnoreCV<Type> TypeCV>
    [[nodiscard]] friend inline auto operator<=>(
        const SixBytePointer left, TypeCV * const right) noexcept
    {
        return left.ptr() <=> right;
    }

    /// \brief compare pointers 3 way
    template <concepts::isSameIgnoreCV<Type> TypeCV>
    [[nodiscard]] friend inline auto operator<=>(
        TypeCV * const left, const SixBytePointer right) noexcept
    {
        return left <=> right.ptr();
    }

    /// \brief add to a pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    [[nodiscard]] inline SixBytePointer operator+(
        const OffsetType offset) const noexcept
    {
        return SixBytePointer(ptr() + offset);
    }

    /// \brief subtract from a pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    [[nodiscard]] inline SixBytePointer operator-(
        const OffsetType offset) const noexcept
    {
        return SixBytePointer(ptr() - offset);
    }

    /// \brief add to this pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    inline SixBytePointer& operator+=(const OffsetType offset) noexcept
    {
        _setPtr(ptr() + offset);
        return *this;
    }

    /// \brief subtract from this pointer
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    inline SixBytePointer& operator-=(const OffsetType offset) noexcept
    {
        _setPtr(ptr() - offset);
        return *this;
    }

    /// \brief access pointer as an array
    template <tkoz::stl::concepts::isPrimitiveInteger OffsetType>
    [[nodiscard]] inline auto& operator[](const OffsetType offset)
        const noexcept requires (!meta::isVoid<Type>)
    {
        return *(ptr() + offset);
    }

    /// \brief pre increment
    inline SixBytePointer& operator++() noexcept
    {
        _setPtr(ptr() + 1);
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
        _setPtr(ptr() - 1);
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

    /// \brief convert to a signed integer equivalent
    [[nodiscard]] inline sintptr_t toSInt() const noexcept
    {
        return reinterpret_cast<sintptr_t>(ptr());
    }

    /// \brief convert to an unsigned integer equivalent
    [[nodiscard]] inline uintptr_t toUInt() const noexcept
    {
        return reinterpret_cast<uintptr_t>(ptr());
    }

    /// \brief create a SixBytePointer from an integer of pointer size
    /// \param val the integer value
    /// \return a pointer with the integer value
    template <tkoz::stl::concepts::isPrimitiveInteger IntType>
        requires (sizeof(IntType) == sizeof(Type*))
    [[nodiscard]] static inline
    SixBytePointer fromInt(const IntType val) noexcept
    {
        return SixBytePointer(reinterpret_cast<Type*>(val));
    }
};

} // namespace tkoz::stl
