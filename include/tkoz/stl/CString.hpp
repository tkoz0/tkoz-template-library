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
///
/// This class wraps a C string, a null-terminated array of characters.
/// It also stores the length to improve speed of some operations. It may also
/// store the null pointer which is different from the empty string, and also
/// size 0. Behavior is undefined if a null character is inserted anywhere.
/// This string is mutable but cannot be resized. Operations with regular C
/// strings are supported, and in most contexts assume the length of the C
/// string is unknown.
template <typename CharType = char>
class CString
{
private:

    /// pointer to the null terminated string value or nullptr
    CharType *mPtr;
    /// length of string (excluding null terminator) or 0 if it is null
    usize_t mLen;

    /// copy pointer to member value
    inline void _copyFrom(const CString &other)
    {
        if (!other.mPtr)
            mPtr = nullptr, mLen = 0;
        else
        {
            mLen = other.mLen;
            mPtr = new CharType[mLen+1];
            ptrCopy(other.mPtr,mPtr);
        }
    }

    /// swap with other
    inline void _swapWith(CString &other) noexcept
    {
        swap(mPtr,other.mPtr);
        swap(mLen,other.mLen);
    }

    /// copies ptr to destination
    /// increments given destination pointer
    /// excludes null terminator
    template <bool nullCheck>
    static inline void _copySrcDst(
        const CharType *src, CharType *&dst) noexcept
    {
        if constexpr (nullCheck)
        {
            if (!src)
                return;
        }
        while (*src)
            *(dst++) = *(src++);
    }

public:

    /// \brief initialize as null string
    [[nodiscard]] inline CString() noexcept: mPtr(nullptr), mLen(0) {}

    /// \brief initialize from a C string
    /// \param ptr a null-terminated C string, or nullptr
    [[nodiscard]] inline CString(const CharType *ptr)
    {
        if (!ptr)
            mPtr = nullptr, mLen = 0;
        else
        {
            mLen = ptrLen<false>(ptr);
            mPtr = new CharType[mLen+1];
            ptrCopy(ptr,mPtr);
        }
    }

    /// \brief initialize with a repeated character
    /// \param count string length
    /// \param value character value
    ///
    /// Character value must be nonzero.
    [[nodiscard]] inline CString(usize_t count, CharType value)
    {
        mLen = count;
        mPtr = new CharType[mLen+1];
        for (usize_t i = 0; i < mLen; ++i)
            mPtr[i] = value;
        mPtr[mLen] = static_cast<CharType>(0);
    }

    /// \brief destructor
    /// \note do not destruct the same object more than once
    inline ~CString()
    {
        delete[] mPtr;
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
    [[nodiscard]] inline CString(CString &&other) noexcept: CString()
    {
        // *this is default initialized first
        // to prevent swapping unitialized memory
        // TODO this is probably faster if taking from other then set nullptr
        _swapWith(other);
    }

    /// \brief move assignment
    /// \param other another CString
    /// \return reference to *this
    inline CString& operator=(CString &&other) noexcept
    {
        _swapWith(other);
        return *this;
    }

    /// \brief length of the string (excludes null terminator)
    /// \return string length
    [[nodiscard]] inline usize_t len() const noexcept
    {
        return mLen;
    }

    /// \brief length of the string (excludes null terminator)
    /// \return string length
    [[nodiscard]] inline usize_t size() const noexcept
    {
        return mLen;
    }

    /// \brief const pointer to the string value
    /// \return const C string pointer
    [[nodiscard]] inline const CharType* ptr() const noexcept
    {
        return mPtr;
    }

    /// \brief non const pointer to the string value
    /// \return non const C string pointer
    [[nodiscard]] inline CharType* ptr() noexcept
    {
        return mPtr;
    }

    /// \brief true if non null and non empty
    /// \return boolean representation of the string (true if positive length)
    [[nodiscard]] inline operator bool() const noexcept
    {
        return mLen;
    }

    /// \brief is string null (not the same as the empty string)
    /// \return true if the string stored is nullptr
    [[nodiscard]] inline bool isNull() const noexcept
    {
        return !mPtr;
    }

    /// \brief compares 2 null-terminated C strings for equality
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if both C strings are equal
    ///
    /// Corresponding characters are compared sequentially until the end of one
    /// or mismatched characters.
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpEq(
        const CharType *s1, const CharType *s2) noexcept
    {
        if constexpr (nullCheck)
        {
            if (!s1)
                return !s2;
            if (!s2)
                return false;
        }
        const CharType *p1 = s1, *p2 = s2;
        while (*p1 && *p2)
            if (*(p1++) != *(p2++))
                return false;
        return *p1 == *p2;
    }

    /// \brief compare 2 null-terminated C strings for inequality
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if both C strings are different
    ///
    /// Compares for inequality. Negation of ptrCmpEq()
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpNe(
        const CharType *s1, const CharType *s2) noexcept
    {
        return !ptrCmpEq<nullCheck>(s1,s2);
    }

    /// \brief compares 2 null-terminated C strings (3 way compare)
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return 3 way ordering of the 2 C strings
    ///
    /// Null pointers have the lowest value. Otherwise, corresponding characters
    /// are compared until one ends or the character pair is mismatched. The
    /// string whose end is reached first is lower, otherwise the values of the
    /// mismatched characters are compared.
    template <bool nullCheck = true>
    [[nodiscard]] static inline auto ptrCmp3way(
        const CharType *s1, const CharType *s2) noexcept
    {
        if constexpr (nullCheck)
        {
            if (!s1 || !s2)
                return s1 <=> s2;
        }
        const CharType *p1 = s1, *p2 = s2;
        while (*p1 && *p2)
        {
            if (*p1 != *p2)
                return *p1 <=> *p2;
            ++p1, ++p2;
        }
        return *p1 <=> *p2;
    }

    /// \brief compare 2 null-terminated C strings (less than)
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is less than s2 (see ptrCmp3way())
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpLt(
        const CharType *s1, const CharType *s2) noexcept
    {
        return ptrCmp3way<nullCheck>(s1,s2) < 0;
    }

    /// \brief compare 2 null-terminated C strings (less than or equal to)
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is less than or equal to s2 (see ptrCmp3way())
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpLe(
        const CharType *s1, const CharType *s2) noexcept
    {
        return ptrCmp3way<nullCheck>(s1,s2) <= 0;
    }

    /// \brief compare 2 null-terminated C strings (greater than)
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is greater than s2 (see ptrCmp3way())
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpGt(
        const CharType *s1, const CharType *s2) noexcept
    {
        return ptrCmp3way<nullCheck>(s1,s2) > 0;
    }

    /// \brief compare 2 null-terminated C strings (greater than or equal to)
    /// \tparam nullCheck check for null pointers
    /// \param s1 first string
    /// \param s2 second string
    /// \return true if s1 is greater than than or equal to s2
    /// (see ptrCmp3way())
    template <bool nullCheck = true>
    [[nodiscard]] static inline bool ptrCmpGe(
        const CharType *s1, const CharType *s2) noexcept
    {
        return ptrCmp3way<nullCheck>(s1,s2) >= 0;
    }

    /// \brief compare equality
    /// \param left a CString
    /// \param right a CString
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CString &left, const CString &right) noexcept
    {
        if (left.mLen != right.mLen)
            return false;
        return ptrCmpEq(left.mPtr,right.mPtr);
    }

    /// \brief compare equality
    /// \param left a pointer
    /// \param right a CString
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CharType *left, const CString &right) noexcept
    {
        return ptrCmpEq(left,right.mPtr);
    }

    /// \brief compare equality
    /// \param left a CString
    /// \param right a pointer
    /// \return true if both strings are equal
    [[nodiscard]] friend inline bool operator==(
        const CString &left, const CharType *right) noexcept
    {
        return ptrCmpEq(left.mPtr,right);
    }

    /// \brief compare 3 way
    /// \param left a CString
    /// \param right a CString
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CString &left, const CString &right) noexcept
    {
        return ptrCmp3way(left.mPtr,right.mPtr);
    }

    /// \brief compare 3 way
    /// \param left a pointer
    /// \param right a CString
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CharType *left, const CString &right) noexcept
    {
        return ptrCmp3way(left,right.mPtr);
    }

    /// \brief compare 3 way
    /// \param left a CString
    /// \param right a pointer
    /// \return 3 way compare result of both strings
    [[nodiscard]] friend inline auto operator<=>(
        const CString &left, const CharType *right) noexcept
    {
        return ptrCmp3way(left.mPtr,right);
    }

    /// \brief create CString from an existing C string
    /// \param ptr the C string to wrap
    /// \tparam nullCheck check if pointer is null
    ///
    /// This class becomes the owner of the memory once this is done.
    /// It must be safe to delete[] ptr.
    template <bool nullCheck = true>
    [[nodiscard]] static inline CString ptrWrap(CharType *ptr) noexcept
    {
        if constexpr (nullCheck)
        {
            if (!ptr)
                return CString();
        }
        CString ret;
        ret.mPtr = ptr;
        ret.mLen = ptrLen<false>(ptr);
        return ret;
    }

    /// \brief create CString from existing C string with length known
    /// \param ptr the C string to wrap
    /// \param len the string length (must be correct)
    ///
    /// Behavior is undefined if length is incorrect. Length excludes null
    /// terminator and is 0 for nullptr. This class becomes the owner of the
    /// memory. It must be safe to delete[] ptr.
    /// \todo consider making this function private
    [[nodiscard]] static inline CString ptrWrap(
        CharType *ptr, usize_t len) noexcept
    {
        CString ret;
        ret.mPtr = ptr;
        ret.mLen = len;
        return ret;
    }

    /// \brief find the length of a C string
    /// \param s string to find length of
    /// \tparam nullCheck check if pointer is null
    ///
    /// The length excludes the null terminator. If null_check is false, then
    /// the pointer given must not be null. If null_check is true, then null
    /// pointers have string length 0.
    template <bool nullCheck = true>
    [[nodiscard]] static inline usize_t ptrLen(const CharType *ptr) noexcept
    {
        if constexpr (nullCheck)
        {
            if (!ptr)
                return 0;
        }
        usize_t len = 0;
        while (*ptr)
            ++ptr, ++len;
        return len;
    }

    /// \brief allocate another string with the same value
    /// \tparam nullCheck check if pointer is null
    /// \param s string to copy
    ///
    /// The string is copied including null terminator. If nullCheck is false,
    /// the given pointer must not be null. If nullCheck is true, then nullptr
    /// is returned if given a null string. The pointer returned, if not null,
    /// must be deallocated with delete[].
    template <bool nullCheck = true>
    [[nodiscard]] static inline CharType* ptrCopyNew(const CharType *ptr)
    {
        if constexpr (nullCheck)
        {
            if (!ptr)
                return nullptr;
        }
        usize_t len = ptrLen<false>(ptr);
        CharType *t = new CharType[len+1];
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
    /// \tparam nullCheck check if pointer is null
    /// \param s1 first string
    /// \param s2 second string
    ///
    /// Concatenates 2 strings into a newly allocated result. If nullCheck is
    /// true, then nullptr is returned when both inputs are null. If nullCheck
    /// is false, then both inputs must not be null. If the result is non null,
    /// it must be deallocated with delete[]. Result is only null if both inputs
    /// are null. If non null, result is null terminated.
    template <bool nullCheck = true>
    [[nodiscard]] static inline CharType* ptrConcatNew(
        const CharType *s1, const CharType *s2)
    {
        if constexpr (nullCheck)
        {
            if (!s1)
                return ptrCopyNew<true>(s2);
            if (!s2)
                return ptrCopyNew<false>(s1);
        }
        const usize_t len1 = ptrLen<false>(s1), len2 = ptrLen<false>(s2);
        CharType *t = new CharType[len1+len2+1];
        CharType *p = t;
        while (*s1)
            *(p++) = *(s1++);
        while (*s2)
            *(p++) = *(s2++);
        *p = static_cast<CharType>(0);
        return t;
    }

    /// \brief concatenate 2 strings into an array
    /// \tparam nullCheck check if pointer is null
    /// \param s1 first string
    /// \param s2 second string
    /// \param dst destination
    ///
    /// If nullCheck is true, then null pointers are skipped. If dst is null or
    /// does not have enough space for the result, behavior is undefined. The
    /// null terminator is written to dst after s1 and s2.
    template <bool nullCheck = true>
    static inline void ptrConcat(
        const CharType *s1, const CharType *s2, CharType *dst) noexcept
    {
        _copySrcDst<nullCheck>(s1,dst);
        _copySrcDst<nullCheck>(s2,dst);
        *dst = static_cast<CharType>(0);
    }

    /// \brief concatenate 2 strings (both of this class)
    [[nodiscard]] friend inline CString operator+(
        const CString &left, const CString &right)
    {
        if (left.isNull())
            return right;
        if (right.isNull())
            return left;
        const usize_t l = left.len() + right.len();
        CharType *s = new CharType[l+1];
        ptrConcat(left.ptr(),right.ptr(),s);
        return ptrWrap(s,l);
    }

    /// \brief concatenate 2 strings (c string on left)
    [[nodiscard]] friend inline CString operator+(
        const CharType *left, const CString &right)
    {
        if (!left)
            return right;
        if (right.isNull())
            return CString(left);
        const usize_t l = ptrLen<false>(left) + right.len();
        CharType *s = new CharType[l+1];
        ptrConcat(left,right.ptr(),s);
        return ptrWrap(s,l);
    }

    /// \brief concatenate 2 strings (c string on right)
    [[nodiscard]] friend inline CString operator+(
        const CString &left, const CharType *right)
    {
        if (left.isNull())
            return CString(right);
        if (!right)
            return left;
        const usize_t l = left.len() + ptrLen<false>(right);
        CharType *s = new CharType[l+1];
        ptrConcat(left.ptr(),right,s);
        return ptrWrap(s,l);
    }

    /// \brief concatenate another string to the end
    inline CString& operator+=(const CharType *other)
    {
        if (!other)
            return *this;
        if (!mPtr)
            return (*this = CString(other));
        const usize_t len = mLen + ptrLen<false>(other);
        CharType *ptr = new CharType[len+1];
        ptrConcat<false>(mPtr,other,ptr);
        delete[] mPtr;
        mPtr = ptr;
        mLen = len;
        return *this;
    }

    /// \brief concatenate another string to the end
    inline CString& operator+=(const CString &other)
    {
        if (!other.mPtr)
            return *this;
        if (!mPtr)
            return (*this = other);
        const usize_t len = mLen + other.mLen;
        CharType *ptr = new CharType[len+1];
        ptrConcat<false>(mPtr,other.mPtr,ptr);
        delete[] mPtr;
        mPtr = ptr;
        mLen = len;
        return *this;
    }

    /// \brief (non const) access to a character
    /// \tparam IndexType type of index (bool or integer primitive)
    /// \param i the index
    /// \return reference to character at that index
    ///
    /// Behavior is undefined if i is out of bounds. If i is an unsigned type,
    /// the valid range is [0,len()]. If i is a signed type, the valid range is
    /// [-len(),len()]. Negative indexes count starting from the last character
    /// before the null terminator. Behavior is undefined if null is assigned
    /// anywhere other than the null terminator.
    template <typename IndexType>
        requires concepts::isPrimitiveIntegerOrBool<IndexType>
    [[nodiscard]] inline CharType& operator[](IndexType i) noexcept
    {
        if constexpr (concepts::isPrimitiveSignedInteger<IndexType>)
        {
            const usize_t j = static_cast<usize_t>(i);
            if (static_cast<ssize_t>(i) >= 0)
                return mPtr[j];
            return mPtr[mLen + j];
        }
        else
            return mPtr[static_cast<usize_t>(i)];
    }

    /// \brief const access to a character
    /// \return character by value
    ///
    /// See non const version for more details.
    template <typename IndexType>
        requires concepts::isPrimitiveIntegerOrBool<IndexType>
    [[nodiscard]] inline CharType operator[](IndexType i) const noexcept
    {
        return const_cast<CString*>(this)->operator[](i);
    }

    /// \brief (non const) access to a character
    /// \tparam IndexType type of index (bool or integer primitive)
    /// \param i the index
    /// \return reference to character at that index
    /// \throw NullError if the string value is nullptr
    /// \throw IndexError if the index is out of bounds
    ///
    /// Behaves the same as operator[] except it checks bounds and throws an
    /// exception when i is outside the valid range.
    template <typename IndexType>
        requires concepts::isPrimitiveIntegerOrBool<IndexType>
    [[nodiscard]] inline CharType& at(IndexType i)
    {
        if (!mPtr)
            throw NullError("string pointer is null");
        const usize_t j = static_cast<usize_t>(i);
        if constexpr (concepts::isPrimitiveSignedInteger<IndexType>)
        {
            const ssize_t k = static_cast<ssize_t>(i);
            if (k >= 0)
            {
                if (j > mLen)
                    throw IndexError("signed index too large");
                return (*this)[j];
            }
            else
            {
                if (k < -static_cast<ssize_t>(mLen))
                    throw IndexError("signed index too small");
                return (*this)[mLen + j];
            }
        }
        else
        {
            if (j > mLen)
                throw IndexError("unsigned index too large");
            return (*this)[j];
        }
    }

    /// \brief const access to a character
    /// \return character by value
    /// \throw NullError or IndexError
    ///
    /// See non const version for details.
    template <typename IndexType>
        requires concepts::isPrimitiveIntegerOrBool<IndexType>
    [[nodiscard]] inline CharType at(IndexType i) const
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

    /// \todo
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
};

} // namespace tkoz::stl

// TODO CStringView class like this but does not own memory

// TODO String and StringView classes to be similar to STL

// TODO FString for formatting

// TODO RString for regex
