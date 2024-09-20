#pragma once

#include <cstddef>
#include <cstdint>

// these assumptions are made throughout the code
// which may not be a good practice

// for now, this library is written to compile with gcc for x86_64 systems
// significant changes may be needed to make it work elsewhere

static_assert(sizeof(bool) == 1);
static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);
static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);

/*
static_assert(std::is_same_v<uint8_t, unsigned char>);
static_assert(std::is_same_v<uint16_t, unsigned short>);
static_assert(std::is_same_v<uint32_t, unsigned int>);
static_assert(std::is_same_v<uint64_t, unsigned long>);
static_assert(std::is_same_v<int8_t, signed char>);
static_assert(std::is_same_v<int16_t, signed short>);
static_assert(std::is_same_v<int32_t, signed int>);
static_assert(std::is_same_v<int64_t, signed long>);
*/

static_assert(sizeof(void*) == 8);
static_assert(sizeof(bool*) == 8);
static_assert(sizeof(float*) == 8);
static_assert(sizeof(double*) == 8);
static_assert(sizeof(uint8_t*) == 8);
static_assert(sizeof(uint16_t*) == 8);
static_assert(sizeof(uint32_t*) == 8);
static_assert(sizeof(uint64_t*) == 8);
static_assert(sizeof(int8_t*) == 8);
static_assert(sizeof(int16_t*) == 8);
static_assert(sizeof(int32_t*) == 8);
static_assert(sizeof(int64_t*) == 8);

namespace tkoz
{

typedef bool bit_t;
typedef float fp32_t;
typedef double fp64_t;
typedef signed char schar_t;
typedef unsigned char uchar_t;
typedef signed short sshort_t;
typedef unsigned short ushort_t;
typedef signed int sint_t;
typedef unsigned int uint_t;
typedef signed long slong_t;
typedef unsigned long ulong_t;
typedef signed long long sll_t;
typedef unsigned long long ull_t;

static_assert(sizeof(bit_t) == 1);
static_assert(sizeof(fp32_t) == 4);
static_assert(sizeof(fp64_t) == 8);
static_assert(sizeof(schar_t) == 1);
static_assert(sizeof(uchar_t) == 1);
static_assert(sizeof(sshort_t) == 2);
static_assert(sizeof(ushort_t) == 2);
static_assert(sizeof(sint_t) == 4);
static_assert(sizeof(uint_t) == 4);
static_assert(sizeof(slong_t) == 8);
static_assert(sizeof(ulong_t) == 8);
static_assert(sizeof(sll_t) == 8);
static_assert(sizeof(ull_t) == 8);

// typedef these in the tkoz namespace because why not

using int8_t = std::int8_t;
using int16_t = std::int16_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;
using uint8_t = std::uint8_t;
using uint16_t = std::uint16_t;
using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;

}
