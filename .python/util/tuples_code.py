# generate the code for the tuple thing

L = ' abcdefghijklmnopqrstuvwxyz'

def tuple(n):
    assert 2 <= n <= 26
    return f'''\
template <typename T1, {', '.join(f'typename T{i} = T{i-1}' for i in range(2,n+1))}>
struct tuple{n}
{{
#define OPEQ_TUPLE(OP) template <typename U, typename std::enable_if_t<std::is_same_v<U,tuple{n}>,bool> = true> \\
    inline tuple{n} &operator OP(const U &rhs) {{ {' '.join(f'{L[i]} OP rhs.{L[i]};' for i in range(1,n+1))} return *this; }}
#define OPEQ_OTHER(OP) template <typename U, typename std::enable_if_t<!std::is_same_v<U,tuple{n}>,bool> = true> \\
    inline tuple{n} &operator OP(const U &rhs) {{ {' '.join(f'{L[i]} OP rhs;' for i in range(1,n+1))} return *this; }}
#define OP_BINARY(OP) friend inline auto operator OP(const tuple{n} &lhs, const tuple{n} &rhs) \\
    {{ return make_tuple{n}({', '.join(f'lhs.{L[i]} OP rhs.{L[i]}' for i in range(1,n+1))}); }}
#define OP_EQ_BIN(OP) OPEQ_TUPLE(OP##=) OPEQ_OTHER(OP##=) OP_BINARY(OP)
#define OP_UNARY(OP) friend inline auto operator OP(const tuple{n} &tup) {{ return make_tuple{n}({', '.join(f'OP tup.{L[i]}' for i in range(1,n+1))}); }}
#define OP_PRE(OP) inline tuple{n} &operator OP() {{ {' '.join(f'OP {L[i]};' for i in range(1,n+1))} return *this; }}
#define OP_POST(OP) inline tuple{n} operator OP(int) {{ tuple{n} ret = *this; OP(*this); return ret; }}
    {' '.join(f'T{i} {L[i]};' for i in range(1,n+1))}
    inline constexpr tuple{n}({', '.join(f'const T{i} &{L[i]} = T{i}()' for i in range(1,n+1))}): {', '.join(f'{L[i]}({L[i]})' for i in range(1,n+1))} {{}}
    {' '.join(f'GET({i-1},T{i},{L[i]})' for i in range(1,n+1))}
    {' '.join(f'GETC({i-1},T{i},{L[i]})' for i in range(1,n+1))}
    {' '.join(f'SET({i-1},T{i},{L[i]})' for i in range(1,n+1))}
    OP_EQ_BIN(+) OP_EQ_BIN(-) OP_EQ_BIN(*) OP_EQ_BIN(/) OP_EQ_BIN(%)
    OP_EQ_BIN(&) OP_EQ_BIN(|) OP_EQ_BIN(^) OP_EQ_BIN(<<) OP_EQ_BIN(>>)
    OP_UNARY(-) OP_UNARY(+) OP_UNARY(~) OP_UNARY(*) OP_UNARY(&)
    OP_PRE(++) OP_POST(++) OP_PRE(--) OP_POST(--) OP_BINARY(&&) OP_BINARY(||)
    inline constexpr bool operator!() const {{ return !bool(*this); }}
    inline constexpr operator bool() const {{ return {' || '.join(f'bool({L[i]})' for i in range(1,n+1))}; }}
    inline constexpr bool operator==(const tuple{n} &tup) const = default;
    inline constexpr auto operator<=>(const tuple{n} &tup) const = default;
#undef OPEQ_TUPLE
#undef OPEQ_OTHER
#undef OP_BINARY
#undef OP_EQ_BIN
#undef OP_UNARY
#undef OP_PRE
#undef OP_POST
}};

template <{', '.join(f'typename T{i}' for i in range(1,n+1))}>
inline constexpr tuple{n}<{','.join(f'T{i}' for i in range(1,n+1))}> make_tuple{n}({', '.join(f'const T{i} &{L[i]}' for i in range(1,n+1))}) {{ return tuple{n}<{','.join(f'T{i}' for i in range(1,n+1))}>({','.join(L[1:n+1])}); }}
'''

print(f'''\
#pragma once

#include <compare>
#include <cstddef>
#include <type_traits>

namespace tkoz
{{

#define GET(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \\
    inline constexpr TV &get() {{ return MV; }}
#define GETC(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \\
    inline constexpr const TV &get() const {{ return MV; }}
#define SET(IV,TV,MV) template <size_t i, typename std::enable_if_t<i==IV,bool> = true> \\
    inline void set(const TV &val) {{ MV = val; }}
''')

MAX_TUPLE_SIZE = 26
assert 2 <= MAX_TUPLE_SIZE <= 26

for n in range(2,MAX_TUPLE_SIZE+1):
    print(tuple(n))

print(f'''\
#undef GET
#undef GETC
#undef SET

}}
''')
