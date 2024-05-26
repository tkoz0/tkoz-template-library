/*
Range similar to in python3
*/
#include <cstddef>

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
    typedef _iter iter;
    // constructor for number of elements, iterates range [0,n)
    // for increment, 0 to n-1, for decrement, n-1 to 0
    inline constexpr _step1range(T n = 0) noexcept: _start(_inc ? 0 : n-1), _stop(_inc ? n : -1) {}
    // iterates range starting at start, ending 1 before stop
    // for increment, start to stop-1, for decrement, start to stop+1
    inline constexpr _step1range(T start, T stop) noexcept: _start(start), _stop(stop) {}
    inline constexpr _iter begin() const noexcept { return _iter(_start); }
    inline constexpr _iter end() const noexcept { return _iter(_stop); }
};

// increment range
template <typename T = std::size_t>
using irange = _step1range<true,T>;

// decrement range
template <typename T = std::size_t>
using drange = _step1range<false,T>;

// general range (increment only)
// TODO support negative step size
template <typename T = std::size_t>
class range
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
    typedef _iter iter;
    // increment from 0 to n-1
    inline constexpr range(T n = 0) noexcept: _start(0), _stop(n), _step(1) {}
    // increment from start to stop-1
    inline constexpr range(T start, T stop) noexcept: _start(start), _stop(stop), _step(1) {}
    // range with step size (undefined behavior if step <= 0 or stop < start)
    inline range(T start, T stop, T step) noexcept: _start(start), _step(step)
    {
        T m = (stop-start) % step;
        _stop = m == 0 ? stop : stop + step - m;
    }
    inline constexpr _iter begin() const noexcept { return _iter(_start,_step); }
    inline constexpr _iter end() const noexcept { return _iter(_stop,_step); }
};

}
