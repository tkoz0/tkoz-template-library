# generate tests for the tuple thing

L = ' abcdefghijklmnopqrstuvwxyz'
newline = '\n'

def test_tuple(n):
    n1 = ','.join(map(str,range(1,n+1)))
    n2 = ','.join(map(str,range(101,100+n+1)))
    n3 = ','.join(map(str,range(100,100+n)))
    n4 = ','.join(map(str,range(102,100+2*n+1,2)))
    n5 = ','.join(map(str,range(n+1,2*n+1)))
    n6 = ','.join(map(str,[i*(n+i) for i in range(1,n+1)]))
    n7 = ','.join(map(str,[i*i for i in range(1,n+1)]))
    n8 = ','.join(map(str,[3*i for i in range(1,n+1)]))
    b00 = ','.join('0'*n)
    b10 = ','.join('1'+'0'*(n-1))
    b01 = ','.join('0'*(n-1)+'1')
    b11 = ','.join('1'*n)
    newline = '\n'
    return f'''\
void test_tuple{n}()
{{
    static_assert(std::is_same_v<tuple{n}<int>,tuple{n}<{','.join(['int']*n)}>>);
    typedef tuple{n}<int> ti;
    ti t1;
    t1 = {{{n1}}};
    assert({' && '.join(f't1.{L[i]} == {i}' for i in range(1,n+1))});
    assert({' && '.join(f'&t1.get<{i-1}>() == &t1.{L[i]}' for i in range(1,n+1))});
    {f'{newline}    '.join(f't1.set<{i-1}>({100+i});' for i in range(1,n+1))}
    assert(t1 == (ti{{{n2}}}));
    assert({' && '.join(f't1.{L[i]} == {100+i}' for i in range(1,n+1))});
    assert(!bool(ti{{{b00}}}) && !(ti{{{b00}}}));
    assert(bool(ti{{{b10}}}) && !!(ti{{{b10}}}));
    assert(bool(ti{{{b01}}}) && !!(ti{{{b01}}}));
    assert(bool(ti{{{b11}}}) && !!(ti{{{b11}}}));
    assert(t1-- == (ti{{{n2}}}));
    assert(t1 == (ti{{{n3}}}));
    assert(t1++ == (ti{{{n3}}}));
    assert(t1 == (ti{{{n2}}}));
    assert(--t1 == (ti{{{n3}}}));
    assert(t1 == (ti{{{n3}}}));
    assert(++t1 == (ti{{{n2}}}));
    assert(t1 == (ti{{{n2}}}));
    assert(-t1 == (ti{{{','.join(f'-{100+i}' for i in range(1,n+1))}}}));
    assert(+t1 == (ti{{{n2}}}));
    assert(~t1 == (ti{{{','.join(f'~{100+i}' for i in range(1,n+1))}}}));
    assert((ti{{{n1}}}) + (ti{{{n2}}}) == (ti{{{n4}}}));
    assert((ti{{{n4}}}) - (ti{{{n1}}}) == (ti{{{n2}}}));
    assert((ti{{{n1}}}) * (ti{{{n5}}}) == (ti{{{n6}}}));
    assert((ti{{{n7}}}) / (ti{{{n1}}}) == (ti{{{n1}}}));
}}
'''

MAX_TUPLE_SIZE = 26
assert 2 <= MAX_TUPLE_SIZE <= 26

print(f'''\
#include <cassert>

#include "../../src/util/tuples.hpp"

using namespace tkoz;
''')

for n in range(2,MAX_TUPLE_SIZE+1):
    print(test_tuple(n))

print(f'''\
int main()
{{
    {f'{newline}    '.join(f'test_tuple{i}();' for i in range(2,MAX_TUPLE_SIZE+1))}
    return 0;
}}
''')
