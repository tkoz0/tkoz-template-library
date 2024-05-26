#include <stdexcept>
#include <string>

/*
#define CHECK_THROW(expr) (static_cast<bool>(expr) ? void(0) : \
throw std::runtime_error(std::string(#expr) + " FILE=" \
+ std::string(__FILE__) + " LINE=" +  std::to_string(__LINE__)))
*/

// fails when expression does not throw exception
#define assert_throw(expr) \
do { try { expr; assert(0); } \
catch (...) {} } while(0)
