#pragma once
#include <stdexcept>
#include <string>
#include <iostream>
#include <type_traits>

/*
#define CHECK_THROW(expr) (static_cast<bool>(expr) ? void(0) : \
throw std::runtime_error(std::string(#expr) + " FILE=" \
+ std::string(__FILE__) + " LINE=" +  std::to_string(__LINE__)))
*/

// fails when expression does not throw exception
#define assert_throw(expr) \
do { try { expr; assert(0); } \
catch (...) {} } while(0)

template <typename T>
struct debug_print_int_ret
{ typedef T type; };
template <>
struct debug_print_int_ret<int8_t>
{ typedef int32_t type; };
template <>
struct debug_print_int_ret<uint8_t>
{ typedef uint32_t type; };

// convert integer to a type that wont print as characters
// in particular this gives a different type for int8_t and uint8_t
template <typename T>
typename debug_print_int_ret<T>::type debug_int(T v)
{ return (typename debug_print_int_ret<T>::type)v; }
