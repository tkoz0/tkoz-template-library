/*
Range similar to in python3
*/

#pragma once
#include <cstddef>
#ifdef DEBUG_PRINT
#include <iostream>
#include "../test/test_common.hpp"
#endif

namespace tkoz
{

// range for increment or decrement to share code
template <bool _inc, typename T>
class _step1range
{
private:
    T _start, _stop;
    struct _iter
    {
        T _i;
        inline constexpr _iter(T i) noexcept: _i(i) {}
        inline T operator*() const noexcept { return _i; }
        inline _iter operator++() noexcept { return _iter(_inc ? ++_i : --_i); }
        inline _iter operator++(int) noexcept { return _iter(_inc ? _i++ : _i--); }
        inline _iter operator--() noexcept { return _iter(_inc ? --_i : ++_i); }
        inline _iter operator--(int) noexcept { return _iter(_inc ? _i-- : _i++); }
        inline bool operator==(_iter o) const noexcept { return _i == o._i; }
        inline bool operator!=(_iter o) const noexcept { return _i != o._i; }
        inline bool operator<(_iter o) const noexcept { return _inc ? _i < o._i : _i > o._i; }
        inline bool operator>(_iter o) const noexcept { return _inc ? _i > o._i : _i < o._i; }
        inline bool operator<=(_iter o) const noexcept { return _inc ? _i <= o._i : _i >= o._i; }
        inline bool operator>=(_iter o) const noexcept { return _inc ? _i >= o._i : _i <= o._i; }
        inline operator T() const noexcept { return _i; }
    };
public:
    // number type
    typedef T num_t;
    // iterator type
    typedef _iter iter;
    // constructor for number of elements, iterates range [0,n)
    // for increment, 0 to n-1, for decrement, n-1 to 0
    inline constexpr _step1range(T n = 0) noexcept: _start(_inc ? 0 : n-1), _stop(_inc ? n : -1) {}
    // iterates range starting at start, ending 1 before stop
    // for increment, start to stop-1, for decrement, start to stop+1
    inline constexpr _step1range(T start, T stop) noexcept: _start(start), _stop(stop) {}
    // iterator to start number
    inline constexpr _iter begin() const noexcept { return _iter(_start); }
    // iterator to 1 past last number
    inline constexpr _iter end() const noexcept { return _iter(_stop); }
};

// increment range (allows overflow)
template <typename T = std::size_t>
using IncRange = _step1range<true,T>;

// decrement range (allows underflow)
template <typename T = std::size_t>
using DecRange = _step1range<false,T>;

// general range
// if step size is 1 (or -1), should use IncRange (or DecRange) instead
// to have negative step size, a signed type must be used
// behavior is undefined if step size is 0
template <typename T = std::size_t>
class Range
{
private:
    T _start, _stop, _step;
    struct _iter
    {
        T _i, _s;
        inline constexpr _iter(T i, T s) noexcept: _i(i), _s(s) {}
        inline T operator*() const noexcept { return _i; }
        inline _iter operator++() noexcept { return _iter(_i += _s, _s); }
        inline _iter operator--() noexcept { return _iter(_i -= _s, _s); }
        inline _iter operator++(int) noexcept { _iter ret = *this; ++(*this); return ret; }
        inline _iter operator--(int) noexcept { _iter ret = *this; --(*this); return ret; }
        inline bool operator==(_iter o) const noexcept { return _i == o._i; }
        inline bool operator!=(_iter o) const noexcept { return _i != o._i; }
        inline bool operator<(_iter o) const noexcept { return _i < o._i; }
        inline bool operator>(_iter o) const noexcept { return _i > o._i; }
        inline bool operator<=(_iter o) const noexcept { return _i <= o._i; }
        inline bool operator>=(_iter o) const noexcept { return _i >= o._i; }
        inline operator T() const noexcept { return _i; }
    };
public:
    // number type
    typedef T num_t;
    // iterator type
    typedef _iter iter;
    // increment from 0 to n-1
    inline constexpr Range(T n = 0) noexcept: _start(0), _stop(n), _step(1) {}
    // increment from start to stop-1
    // if stop <= start, range is empty
    inline constexpr Range(T start, T stop) noexcept: _start(start), _stop(stop < start ? start : stop), _step(1) {}
    // range with step size
    // for positive step, range is empty when stop <= start
    // for negative step, range is empty when stop >= start
    // undefined behavior if step is 0
    inline Range(T start, T stop, T step) noexcept: _start(start), _step(step)
    {
#ifdef DEBUG_PRINT
        std::cout << "tkoz::Range(" << debug_int(start) << "," << debug_int(stop) << "," << debug_int(step) << ")" << std::endl;
#endif
        T m = (stop-start) % step;
#ifdef DEBUG_PRINT
        std::cout << "tkoz::Range temp m = (" << debug_int(stop) << "-" << debug_int(start) << ")%" << debug_int(step)
            << "=" << debug_int(stop-start) << "%" << debug_int(step) << "=" << debug_int(m) << std::endl;
#endif
        if ((step > 0 && stop <= start) || (step < 0 && stop >= start))
            _stop = start;
        else
            _stop = m == 0 ? stop : stop + step - m;
#ifdef DEBUG_PRINT
        std::cout << "tkoz::Range{_start=" << debug_int(_start) << ",_stop=" << debug_int(_stop) << ",step=" << debug_int(_step) << "}" << std::endl;
#endif
    }
    // iterator to start number
    inline constexpr _iter begin() const noexcept { return _iter(_start,_step); }
    // iterator 1 past last number
    inline constexpr _iter end() const noexcept { return _iter(_stop,_step); }
};

}
