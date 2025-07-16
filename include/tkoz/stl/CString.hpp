///
/// C string wrapper with more features
///

#pragma once

#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/Exceptions.hpp>
#include <tkoz/stl/Types.hpp>
#include <tkoz/stl/Utils.hpp>

namespace tkoz::stl
{

/// \brief extended C string
/// \tparam CharType character type
/// \tparam allowNull whether to allow a null C string
///
/// This class wraps a dynamically allocated C string (a null-terminated array
/// of characters) and manages the memory. It may also store the null pointer
/// which is different from the empty string, and also has size 0. Behavior is
/// undefined if a null character is inserted anywhere other than at the end or
/// if the null terminator is changed.
/// This string is mutable but cannot be resized except by assignment with
/// another string. Operations with regular C strings are supported, and in most
/// contexts assume the length of the C string is unknown.
template <typename _CharType = char, bool _allowNull = true>
class CString
{
public:

    /// character type
    using CharType = _CharType;

    /// is null pointer allowed
    static constexpr bool allowNull = _allowNull;

private:

    /// pointer to the null terminated string value or nullptr
    CharType *_ptr;

    /// copy pointer to member value
    inline void _copyFrom(const CString &other)
    {
        if constexpr (allowNull)
        {
            if (!other._ptr)
            {
                _ptr = nullptr;
                return;
            }
        }
        const usize_t l = ptrLen(other._ptr);
        _ptr = new CharType[l+1];
        ptrCopy(other._ptr,_ptr);
    }

    /// swap with other
    inline void _swapWith(CString &other) noexcept
    {
        swap(_ptr,other._ptr);
    }

    /// copies ptr to destination
    /// increments given destination pointer
    /// excludes null terminator
    static inline void _copySrcDst(
        const CharType *src, CharType *&dst) noexcept
    {
        if constexpr (allowNull)
        {
            if (!src)
                return;
        }
        while (*src)
            *(dst++) = *(src++);
    }

public:

    /// \brief initialize as null string
    [[nodiscard]] inline CString() noexcept: _ptr(nullptr) {}

    /// \brief initialize from a C string
    /// \param ptr a null-terminated C string, or nullptr
    [[nodiscard]] inline CString(const CharType *ptr)
    {
        if constexpr (allowNull)
        {
            if (!ptr)
            {
                _ptr = nullptr;
                return;
            }
        }
        const usize_t l = ptrLen(ptr);
        _ptr = new CharType[l+1];
        ptrCopy(ptr,_ptr);
    }

    /// \brief initialize with a repeated character
    /// \param count string length
    /// \param value character value
    ///
    /// Character value must be nonzero.
    [[nodiscard]] inline CString(const usize_t count, const CharType value)
    {
        _ptr = new CharType[count+1];
        for (usize_t i = 0; i < count; ++i)
            _ptr[i] = value;
        _ptr[count] = static_cast<CharType>(0);
    }

    /// \brief destructor
    inline ~CString()
    {
        delete[] _ptr;
    }

    /// \brief copy constructor
    /// \param other another CString
    [[nodiscard]] inline CString(const CString &other)
    {
        _copyFrom(other);
    }

    /// \brief copy assignment
    /// \param other another CString
    /// \return reference to *this
    inline CString& operator=(const CString &other)
    {
        CString tmp(other);
        _swapWith(tmp);
        return *this;
    }

    /// \brief move constructor
    /// \param other another CString
    [[nodiscard]] inline CString(CString &&other) noexcept
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    /// \brief move assignment
    /// \param other another CString
    /// \return reference to *this
    inline CString& operator=(CString &&other) noexcept
    {
        _swapWith(other);
        return *this;
    }

    /// \brief length of the string (excludes null terminator) (linear time)
    /// \return string length
    [[nodiscard]] inline usize_t len() const noexcept
    {
        return ptrLen(_ptr);
    }

    /// \brief length of the string (excludes null terminator) (linear time)
    /// \return string length
    [[nodiscard]] inline usize_t size() const noexcept
    {
        return len();
    }

    /// \brief const pointer to the string value
    /// \return const C string pointer
    [[nodiscard]] inline const CharType* ptr() const noexcept
    {
        return _ptr;
    }

    /// \brief non const pointer to the string value
    /// \return non const C string pointer
    [[nodiscard]] inline CharType* ptr() noexcept
    {
        return _ptr;
    }

    /// \brief true if non null and non empty
    /// \return boolean representation of the string (true if positive length)
    [[nodiscard]] inline operator bool() const noexcept
    {
        if constexpr (allowNull)
            return _ptr && _ptr[0];
        else
            return _ptr[0];
    }

    /// \brief is string null (not the same as the empty string)
    /// \return true if the string stored is nullptr
    /// \note this function should be avoidid if allowNull == false
    [[nodiscard]] inline bool isNull() const noexcept
    {
        if constexpr (allowNull)
            return !_ptr;
        else
            return false;
    }

    /// \brief compares 2 null-terminated C strings for equality
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if both C strings are equal
    ///
    /// Corresponding characters are compared sequentially until the end of one
    /// or mismatched characters.
    [[nodiscard]] static inline bool ptrCmpEq(
        const CharType *s1, const CharType *s2) noexcept
    {
        if constexpr (allowNull)
        {
            if (!s1)
                return !s2;
            if (!s2)
                return false;
        }
        while (*s1 && *s2)
            if (*(s1++) != *(s2++))
                return false;
        return *s1 == *s2;
    }

    /// \brief compare 2 null-terminated C strings for inequality
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if both C strings are different
    ///
    /// Compares for inequality. Negation of ptrCmpEq()
    [[nodiscard]] static inline bool ptrCmpNe(
        const CharType * const s1, const CharType * const s2) noexcept
    {
        return !ptrCmpEq(s1,s2);
    }

    /// \brief compares 2 null-terminated C strings (3 way compare)
    /// \param s1 first string
    /// \param s2 second string
    /// \return 3 way ordering of the 2 C strings
    ///
    /// Null pointers (if allowed) have the lowest value. Otherwise,
    /// corresponding characters are compared until one ends or the character
    /// pair is mismatched. The string whose end is reached first is lower,
    /// otherwise the values of the mismatched characters are compared.
    [[nodiscard]] static inline auto ptrCmp3way(
        const CharType *s1, const CharType *s2) noexcept
    {
        if constexpr (allowNull)
        {
            if (!s1 || !s2)
                return s1 <=> s2;
        }
        while (*s1 && *s2)
        {
            if (*s1 != *s2)
                return *s1 <=> *s2;
            ++s1, ++s2;
        }
        return *s1 <=> *s2;
    }

    /// \brief compare 2 null-terminated C strings (less than)
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is less than s2 (see ptrCmp3way())
    [[nodiscard]] static inline bool ptrCmpLt(
        const CharType * const s1, const CharType * const s2) noexcept
    {
        return ptrCmp3way(s1,s2) < 0;
    }

    /// \brief compare 2 null-terminated C strings (less than or equal to)
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is less than or equal to s2 (see ptrCmp3way())
    [[nodiscard]] static inline bool ptrCmpLe(
        const CharType * const s1, const CharType * const s2) noexcept
    {
        return ptrCmp3way(s1,s2) <= 0;
    }

    /// \brief compare 2 null-terminated C strings (greater than)
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is greater than s2 (see ptrCmp3way())
    [[nodiscard]] static inline bool ptrCmpGt(
        const CharType * const s1, const CharType * const s2) noexcept
    {
        return ptrCmp3way(s1,s2) > 0;
    }

    /// \brief compare 2 null-terminated C strings (greater than or equal to)
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is greater than than or equal to s2
    /// (see ptrCmp3way())
    [[nodiscard]] static inline bool ptrCmpGe(
        const CharType * const s1, const CharType * const s2) noexcept
    {
        return ptrCmp3way(s1,s2) >= 0;
    }

    /// \brief compare equality
    /// \param left a CString
    /// \param right a CString
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CString &left, const CString &right) noexcept
    {
        return ptrCmpEq(left._ptr,right._ptr);
    }

    /// \brief compare equality
    /// \param left a pointer
    /// \param right a CString
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CharType * const left, const CString &right) noexcept
    {
        return ptrCmpEq(left,right._ptr);
    }

    /// \brief compare equality
    /// \param left a CString
    /// \param right a pointer
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CString &left, const CharType * const right) noexcept
    {
        return ptrCmpEq(left._ptr,right);
    }

    /// \brief compare 3 way
    /// \param left a CString
    /// \param right a CString
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CString &left, const CString &right) noexcept
    {
        return ptrCmp3way(left._ptr,right._ptr);
    }

    /// \brief compare 3 way
    /// \param left a pointer
    /// \param right a CString
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CharType * const left, const CString &right) noexcept
    {
        return ptrCmp3way(left,right._ptr);
    }

    /// \brief compare 3 way
    /// \param left a CString
    /// \param right a pointer
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CString &left, const CharType * const right) noexcept
    {
        return ptrCmp3way(left._ptr,right);
    }

    /// \brief create CString from an existing C string
    /// \param ptr the C string to wrap
    ///
    /// This class becomes the owner of the memory once this is done.
    /// It must be safe to delete[] ptr.
    [[nodiscard]] static inline CString ptrWrap(CharType * const ptr) noexcept
    {
        CString ret;
        ret._ptr = ptr;
        return ret;
    }

    /// \brief find the length of a C string
    /// \param ptr string to find length of
    ///
    /// The length excludes the null terminator. Null pointers have length 0.
    [[nodiscard]] static inline usize_t ptrLen(const CharType *ptr) noexcept
    {
        if constexpr (allowNull)
        {
            if (!ptr)
                return 0;
        }
        usize_t l = 0;
        while (*ptr)
            ++ptr, ++l;
        return l;
    }

    /// \brief allocate another string with the same value
    /// \param s string to copy
    ///
    /// The string is copied including null terminator. If nullCheck is false,
    /// the given pointer must not be null. If nullCheck is true, then nullptr
    /// is returned if given a null string. The pointer returned, if not null,
    /// must be deallocated with delete[].
    [[nodiscard]] static inline CharType* ptrCopyNew(const CharType * const ptr)
    {
        if constexpr (allowNull)
        {
            if (!ptr)
                return nullptr;
        }
        usize_t l = CString<CharType,false>::ptrLen(ptr);
        CharType *t = new CharType[l+1];
        ptrCopy(ptr,t);
        return t;
    }

    /// \brief copy a C string to another array
    /// \param src source string
    /// \param dst destination to write the copy
    ///
    /// Behavior is undefined if dst does not have enough space to copy src
    /// (including the null terminator). This function is potentially unsafe.
    /// Both pointers must not be null.
    static inline void ptrCopy(const CharType *src, CharType *dst) noexcept
    {
        while (*src)
            *(dst++) = *(src++);
        *dst = static_cast<CharType>(0);
    }

    /// \brief allocate a new string with the concatenated result
    /// \param s1 first string
    /// \param s2 second string
    ///
    /// Concatenates 2 strings into a newly allocated result. If nullCheck is
    /// true, then nullptr is returned when both inputs are null. If nullCheck
    /// is false, then both inputs must not be null. If the result is non null,
    /// it must be deallocated with delete[]. Result is only null if both inputs
    /// are null. If non null, result is null terminated.
    [[nodiscard]] static inline CharType* ptrConcatNew(
        const CharType *s1, const CharType *s2)
    {
        if constexpr (allowNull)
        {
            if (!s1)
                return ptrCopyNew(s2);
            if (!s2)
                return CString<CharType,false>::ptrCopyNew(s1);
        }
        const usize_t l1 = CString<CharType,false>::ptrLen(s1);
        const usize_t l2 = CString<CharType,false>::ptrLen(s2);
        CharType *t = new CharType[l1+l2+1];
        CharType *p = t;
        while (*s1)
            *(p++) = *(s1++);
        while (*s2)
            *(p++) = *(s2++);
        *p = static_cast<CharType>(0);
        return t;
    }

    /// \brief concatenate 2 strings into an array
    /// \param s1 first string
    /// \param s2 second string
    /// \param dst destination
    ///
    /// If dst is null or does not have enough space for the result, behavior
    /// is undefined. The null terminator is written to dst after s1 and s2.
    static inline void ptrConcat(
        const CharType * const s1, const CharType * const s2,
        CharType *dst) noexcept
    {
        _copySrcDst(s1,dst);
        _copySrcDst(s2,dst);
        *dst = static_cast<CharType>(0);
    }

    /// \brief concatenate 2 strings (both of this class)
    [[nodiscard]] friend inline CString operator+(
        const CString &left, const CString &right)
    {
        if constexpr (allowNull)
        {
            if (!left._ptr)
                return right;
            if (!right._ptr)
                return left;
        }
        const usize_t l1 = CString<CharType,false>::ptrLen(left._ptr);
        const usize_t l2 = CString<CharType,false>::ptrLen(right._ptr);
        CharType *s = new CharType[l1+l2+1];
        ptrConcat(left._ptr,right._ptr,s);
        return ptrWrap(s);
    }

    /// \brief concatenate 2 strings (c string on left)
    [[nodiscard]] friend inline CString operator+(
        const CharType * const left, const CString &right)
    {
        if constexpr (allowNull)
        {
            if (!left)
                return right;
            if (!right._ptr)
                return CString(left);
        }
        const usize_t l1 = CString<CharType,false>::ptrLen(left);
        const usize_t l2 = CString<CharType,false>::ptrLen(right._ptr);
        CharType *s = new CharType[l1+l2+1];
        ptrConcat(left,right._ptr,s);
        return ptrWrap(s);
    }

    /// \brief concatenate 2 strings (c string on right)
    [[nodiscard]] friend inline CString operator+(
        const CString &left, const CharType * const right)
    {
        if constexpr (allowNull)
        {
            if (!left._ptr)
                return CString(right);
            if (!right)
                return left;
        }
        const usize_t l1 = CString<CharType,false>::ptrLen(left._ptr);
        const usize_t l2 = CString<CharType,false>::ptrLen(right);
        CharType *s = new CharType[l1+l2+1];
        ptrConcat(left._ptr,right,s);
        return ptrWrap(s);
    }

    /// \brief concatenate another string to the end
    inline CString& operator+=(const CharType * const other)
    {
        if constexpr (allowNull)
        {
            if (!other)
                return *this;
            if (!_ptr)
                return (*this = CString(other));
        }
        const usize_t l1 = CString<CharType,false>::ptrLen(_ptr);
        const usize_t l2 = CString<CharType,false>::ptrLen(other);
        CharType *ptr = new CharType[l1+l2+1];
        CString<CharType,false>::ptrConcat(_ptr,other,ptr);
        delete[] _ptr;
        _ptr = ptr;
        return *this;
    }

    /// \brief concatenate another string to the end
    inline CString& operator+=(const CString &other)
    {
        return (*this += other._ptr);
    }

    /// \brief (non const) access to a character
    /// \param i the index
    /// \return reference to ith character
    ///
    /// Behavior is undefined if i is ouf of bounds or string is null.
    /// The valid range is [0,len()] (which includes the null terminator).
    /// String length changes if null is assigned anywhere other than the end.
    ///
    /// \note considered implementing signed and unsigned arguments separately
    /// to support negative indexing but decided to make operator[] fast
    [[nodiscard]] inline CharType& operator[](usize_t i) noexcept
    {
        return _ptr[i];
    }

    [[nodiscard]] inline const CharType& operator[](usize_t i) const noexcept
    {
        return _ptr[i];
    }

    /// \brief (non const) access to a character
    /// \tparam IndexType type of index (bool or integer primitive)
    /// \param i the index
    /// \return reference to character at that index
    /// \throw NullError if the string value is nullptr
    /// \throw IndexError if the index is out of bounds
    ///
    /// Accesses a character like operator[] except it checks bounds and throws
    /// an exception when the string is null or i is outside the valid range.
    /// In addition, signed types are supported with a valid range of
    /// [-len(),len()] and accessing negative indexes start with -1 for the
    /// character before the null terminator. This function requires linear
    /// time because the string length is not stored.
    template <concepts::isPrimitiveIntegerOrBool IndexType>
    [[nodiscard]] inline CharType& at(IndexType i)
    {
        if constexpr (allowNull)
        {
            if (!_ptr)
                throw NullError("string pointer is null");
        }
        if constexpr (concepts::isBool<IndexType>)
        {
            if (i && !(*_ptr))
                throw IndexError("index too large");
            return _ptr[i];
        }
        else
        {
            if constexpr (concepts::isPrimitiveSignedInteger<IndexType>)
            {
                const ssize_t j = static_cast<ssize_t>(i);
                if (j < 0)
                {
                    const usize_t l = len();
                    if (j < -static_cast<ssize_t>(l))
                        throw IndexError("index too small");
                    return (*this)[l + static_cast<usize_t>(j)];
                }
            }
            // unsigned indexing
            CharType *p = _ptr;
            while (i > 0 && *p)
                --i, ++p;
            if (i > 0)
                throw IndexError("index too large");
            return *p;
        }
    }

    /// \brief const access to a character
    /// \return character by value
    /// \throw NullError or IndexError
    ///
    /// See non const version for details.
    template <concepts::isPrimitiveIntegerOrBool IndexType>
    [[nodiscard]] inline const CharType& at(IndexType i) const
    {
        return const_cast<CString*>(this)->at(i);
    }

    /// \todo precondition and postcondition assert macros
    /// invariant test after each mutator
    /// conditionally enabled at compile time
    /// use them for the unit testing code
    /// condition check macros group by fast, medium, slow
    /// - fast should be < linear
    /// - medium should be quasilinear
    /// - slow should be > linear
    /// other
    /// - rename CString to CStringTemplate and typedef CString with char
    /// - maybe split up declarations and definitions
    /// - template parameter for null character or character traits

    /// \todo other member functions
    /// - operator std::string (implicit conversion)
    /// - iterators
    /// - istream,ostream (>> and <<)
    /// - constexpr where appropriate
    /// - find, rfind, replace, substr
    /// - split, join, lowerCase, upperCase
    /// - eqIgnoreCase, cmpIgnoreCase
    /// - startsWith, endsWith
    /// - user defined suffix operator""
    /// - variable args ptrConcatNew and ptrConcatSrcDst
    /// - see std::basic_string for more ideas

    /// \todo further string ideas
    /// - CStringView (non owning C string)
    /// - StaticString (fixed length string allowing nulls)
    /// - DynamicString (implementation closer to that of std::string)
    /// - StringView (non owning view of StaticString or DynamicString)
    /// - FormatString (for easily formatting with values)
    /// - RegexString (for matching to patterns)
};

} // namespace tkoz::stl
