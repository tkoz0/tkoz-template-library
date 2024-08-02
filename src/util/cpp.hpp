/*
Macros for handling C++ standards
*/

#define TKOZ_CPP98_VALUE 199711L
#define TKOZ_CPP03_VALUE 199711L
#define TKOZ_CPP11_VALUE 201103L
#define TKOZ_CPP14_VALUE 201402L
#define TKOZ_CPP17_VALUE 201703L
#define TKOZ_CPP20_VALUE 202002L
#define TKOZ_CPP23_VALUE 202302L

#if __cplusplus == TKOZ_CPP03_VALUE
#define TKOZ_CPP98_EXACTLY 1
#define TKOZ_CPP03_EXACTLY 1
#else
#define TKOZ_CPP98_EXACTLY 0
#define TKOZ_CPP03_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP11_VALUE
#define TKOZ_CPP11_EXACTLY 1
#else
#define TKOZ_CPP11_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP14_VALUE
#define TKOZ_CPP14_EXACTLY 1
#else
#define TKOZ_CPP14_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP17_VALUE
#define TKOZ_CPP17_EXACTLY 1
#else
#define TKOZ_CPP17_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP20_VALUE
#define TKOZ_CPP20_EXACTLY 1
#else
#define TKOZ_CPP20_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP23_VALUE
#define TKOZ_CPP23_EXACTLY 1
#else
#define TKOZ_CPP23_EXACTLY 0
#endif

#if __cplusplus == TKOZ_CPP03_VALUE

#define TKOZ_CPP11_OR_NEWER 0
#define TKOZ_CPP14_OR_NEWER 0
#define TKOZ_CPP17_OR_NEWER 0
#define TKOZ_CPP20_OR_NEWER 0
#define TKOZ_CPP23_OR_NEWER 0

#elif __cplusplus == TKOZ_CPP11_VALUE

#define TKOZ_CPP11_OR_NEWER 1
#define TKOZ_CPP14_OR_NEWER 0
#define TKOZ_CPP17_OR_NEWER 0
#define TKOZ_CPP20_OR_NEWER 0
#define TKOZ_CPP23_OR_NEWER 0

#elif __cplusplus == TKOZ_CPP14_VALUE

#define TKOZ_CPP11_OR_NEWER 1
#define TKOZ_CPP14_OR_NEWER 1
#define TKOZ_CPP17_OR_NEWER 0
#define TKOZ_CPP20_OR_NEWER 0
#define TKOZ_CPP23_OR_NEWER 0

#elif __cplusplus == TKOZ_CPP17_VALUE

#define TKOZ_CPP11_OR_NEWER 1
#define TKOZ_CPP14_OR_NEWER 1
#define TKOZ_CPP17_OR_NEWER 1
#define TKOZ_CPP20_OR_NEWER 0
#define TKOZ_CPP23_OR_NEWER 0

#elif __cplusplus == TKOZ_CPP20_VALUE

#define TKOZ_CPP11_OR_NEWER 1
#define TKOZ_CPP14_OR_NEWER 1
#define TKOZ_CPP17_OR_NEWER 1
#define TKOZ_CPP20_OR_NEWER 1
#define TKOZ_CPP23_OR_NEWER 0

#elif __cplusplus == TKOZ_CPP23_VALUE

#define TKOZ_CPP11_OR_NEWER 1
#define TKOZ_CPP14_OR_NEWER 1
#define TKOZ_CPP17_OR_NEWER 1
#define TKOZ_CPP20_OR_NEWER 1
#define TKOZ_CPP23_OR_NEWER 1

#else
#error "unknown cpp standard: " __cplusplus
#endif
