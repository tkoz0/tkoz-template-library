///
/// Exceptions for common things
///

#pragma once

namespace tkoz::stl
{

/// base exception type
/// - does not do any dynamic memory management
/// - designed to only hold a C string constant message
/// - subclasses can add additional relevant information
class Exception
{
private:

    /// exception message
    const char *mMsg;

public:

    /// Default initialize without a message
    [[nodiscard]] inline Exception() noexcept: mMsg(nullptr) {}

    /// Initialize with a message
    [[nodiscard]] inline Exception(const char * const msg): mMsg(msg) {}

    /// Virtual destructor to enable inheriting
    virtual ~Exception() = default;

    /// copy constructor
    [[nodiscard]] inline Exception(const Exception &other) = default;

    /// move constructor
    [[nodiscard]] inline Exception(Exception &&other) = default;

    /// copy assignment
    inline Exception& operator=(const Exception &other) = default;

    /// move assignment
    inline Exception& operator=(Exception &&other) = default;

    /// get the exception message (allowed to be nullptr)
    [[nodiscard]] inline const char* message() const noexcept
    {
        return mMsg;
    }

    /// replace the exception message (allowed to be nullptr)
    void setMessage(const char * const msg)
    {
        mMsg = msg;
    }
};

/// base exception type for most errors
class RuntimeError : public Exception
{
public:
    RuntimeError(): Exception() {}
    RuntimeError(const char * const msg): Exception(msg) {}
    virtual ~RuntimeError() = default;
};

/// base exception type for math errors
class MathError : public Exception
{
public:
    MathError(): Exception() {}
    MathError(const char * const msg): Exception(msg) {}
    virtual ~MathError() = default;
};

/// attempt to dereference a null pointer
/// example: smart pointer with null check
class NullError : public RuntimeError
{
public:
    NullError(): RuntimeError() {}
    NullError(const char * const msg): RuntimeError(msg) {}
};

/// argument value to a function in invalid
/// example: empty list provided when length must be positive
class ArgumentError : public RuntimeError
{
public:
    ArgumentError(): RuntimeError() {}
    ArgumentError(const char * const msg): RuntimeError(msg) {}
};

/// argument (usually a number) is out of the valid domain
/// example: negative number for square root
class DomainError : public MathError
{
public:
    DomainError(): MathError() {}
    DomainError(const char * const msg): MathError(msg) {}
};

/// attempted to exceed length limit
/// example: allocate too much memory for a container
class LengthError : public RuntimeError
{
public:
    LengthError(): RuntimeError() {}
    LengthError(const char * const msg): RuntimeError(msg) {}
};

/// attempted to access an index outside of the valid range
/// example: index is beyond the end of an array
class IndexError : public RuntimeError
{
public:
    IndexError(): RuntimeError() {}
    IndexError(const char * const msg): RuntimeError(msg) {}
};

/// arithmetic overflow
/// example: multiplying 2 number with a result too large to store
class OverflowError : public MathError
{
public:
    OverflowError(): MathError() {}
    OverflowError(const char * const msg): MathError(msg) {}
};

/// arithmetic underflow
/// example: subtracting from an unsigned 0
class UnderflowError : public MathError
{
public:
    UnderflowError(): MathError() {}
    UnderflowError(const char * const msg): MathError(msg) {}
};

/// format of an argument is invalid
/// example: bad string format
class FormatError : public RuntimeError
{
public:
    FormatError(): RuntimeError() {}
    FormatError(const char * const msg): RuntimeError(msg) {}
};

/// error converting type to another
class CastError : public RuntimeError
{
public:
    CastError(): RuntimeError() {}
    CastError(const char * const msg): RuntimeError(msg) {}
};

} // namespace tkoz::stl
