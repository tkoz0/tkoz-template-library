#include <cstddef>
#include <cstdint>
#include <utility>
#include <initializer_list>
#include <string>
#include <stdexcept>
#include <algorithm>

namespace tkoz
{

// class for packing bits into an array efficiently
// dynamically allocated, not resizeable
class BitArray
{
private:
    typedef uint64_t _word_t; // array word type
    static_assert(sizeof(_word_t) == 1 || sizeof(_word_t) == 2
               || sizeof(_word_t) == 4 || sizeof(_word_t) == 8);
    _word_t *_arr; // array storing bits
    size_t _len; // size of array in bits
    inline void _swap(BitArray &arr) noexcept
    { std::swap(_arr,arr._arr); std::swap(_len,arr._len); }
    struct _iter
    {
        _word_t *_p;
        size_t _i;
        inline constexpr _iter(_word_t *p, size_t i): _p(p), _i(i) {}
        inline bool operator*() const noexcept { return *_p & (((_word_t)1ull) << _i); }
        inline _iter operator++() noexcept
        { ++_i; if (_i == word_size_bits) { ++_p, _i = 0; } return *this; }
        inline _iter operator--() noexcept
        { if (_i == 0) {--_p, _i = word_size_bits;} --_i; return *this; }
        inline _iter operator++(int) noexcept { _iter ret = *this; ++(*this); return ret; }
        inline _iter operator--(int) noexcept { _iter ret = *this; --(*this); return ret; }
        inline bool operator==(_iter o) const noexcept { return _p == o._p && _i == o._i; }
        inline bool operator!=(_iter o) const noexcept { return _p != o._p || _i != o._i; }
        inline bool operator<(_iter o) const noexcept { return _p < o._p || (_p == o._p && _i < o._i); }
        inline bool operator>(_iter o) const noexcept { return _p > o._p || (_p == o._p && _i > o._i); }
        inline bool operator<=(_iter o) const noexcept { return _p < o._p || (_p == o._p && _i <= o._i); }
        inline bool operator>=(_iter o) const noexcept { return _p > o._p || (_p == o._p && _i >= o._i); }
    };
public:
    // size of internal array element (bytes)
    static const constexpr size_t word_size_bytes = sizeof(_word_t);
    // size of internal array element (bits)
    static const constexpr size_t word_size_bits = 8*word_size_bytes;
    // number of bits used to index within an internal array word
    static const constexpr size_t index_split_bits =
        word_size_bytes == 1 ? 3 :
        word_size_bytes == 2 ? 4 :
        word_size_bytes == 4 ? 5 :
        word_size_bytes == 8 ? 6 : -1;
    // mask to extract bits for indexing within internal array word
    static const constexpr size_t index_split_mask = (1 << index_split_bits) - 1;
    inline BitArray() noexcept: _arr(nullptr), _len(0) {}
    inline ~BitArray() { delete[] _arr; _arr = nullptr; }
    // initializer list ctor
    BitArray(const std::initializer_list<bool> &vals)
    {
        _len = vals.size();
        _arr = new _word_t[(_len >> index_split_bits) + ((_len & index_split_mask) != 0)];
        auto vi = vals.begin();
        size_t i = 0;
        while (vi != vals.end()) set(i++,*(vi++));
    }
    // size ctor with (optional) fill value
    BitArray(size_t n, bool v = false): _len(n)
    {
        size_t l = (n >> index_split_bits) + ((n & index_split_mask) != 0);
        _arr = new _word_t[l];
        std::fill_n(_arr,l,(v ? (_word_t)-1 : 0));
    }
    BitArray(const BitArray &arr): _len(arr._len)
    {
        size_t l = (arr._len >> index_split_bits) + ((arr._len & index_split_mask) != 0);
        _arr = new _word_t[l];
        std::copy_n(arr._arr,l,_arr);
    }
    BitArray(BitArray &&arr) { _swap(arr); }
    BitArray &operator=(const BitArray &arr) { BitArray tmp(arr); _swap(tmp); return *this; }
    BitArray &operator=(BitArray &&arr) { _swap(arr); return *this; }
    // array size (number of bits stored)
    inline size_t size() const { return _len; }
    // access element
    inline bool get(size_t i) const
    { return _arr[i >> index_split_bits] & (((_word_t)1ull) << (i & index_split_mask)); }
    inline bool operator[](size_t i) const { return get(i); }
    // access with bound check
    inline bool at(size_t i) const
    {
        if (i >= _len) throw std::out_of_range("BitArray out of bounds at index "+std::to_string(i));
        return get(i);
    }
    // set bit value to 1 at index
    inline void set1(size_t i)
    { _arr[i >> index_split_bits] |= (((_word_t)1ull) << (i & index_split_mask)); }
    // set bit value to 0 at index
    inline void set0(size_t i)
    { _arr[i >> index_split_bits] &= ~(((_word_t)1ull) << (i & index_split_mask)); }
    // set bit value at index
    inline void set(size_t i, bool v) { v ? set1(i) : set0(i); }
    typedef _iter iter;
    inline _iter begin() const { return _iter(_arr,0); }
    inline _iter end() const { return _iter(_arr+(_len>>index_split_bits),_len&index_split_mask); }
};

}
