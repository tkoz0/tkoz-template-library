#include <vector>
#include <cassert>
#include "../src/range.hpp"

using tkoz::Range;
using tkoz::IncRange;
using tkoz::DecRange;

template <typename TKOZ_RANGE>
void check_range(TKOZ_RANGE r, std::initializer_list<typename TKOZ_RANGE::num_t> l)
{
    std::vector<size_t> v;
    for (size_t i : r) v.push_back(i);
    assert(v == std::vector<size_t>(l));
}

int main()
{
    check_range(Range<std::size_t>(5),{0,1,2,3,4});
    check_range(Range<std::size_t>(5,10),{5,6,7,8,9});
    check_range(Range<std::size_t>(),{});
    check_range(Range<std::size_t>(11,99,11),{11,22,33,44,55,66,77,88});
    check_range(Range<std::size_t>(11,100,11),{11,22,33,44,55,66,77,88,99});
    check_range(Range<std::size_t>(25,25,6),{});
    check_range(IncRange<std::size_t>(),{});
    check_range(IncRange<std::size_t>(4),{0,1,2,3});
    check_range(IncRange<std::size_t>(3,7),{3,4,5,6});
    check_range(DecRange<std::size_t>(),{});
    check_range(DecRange<std::size_t>(6),{5,4,3,2,1,0});
    check_range(DecRange<std::size_t>(7,3),{7,6,5,4});
    return 0;
}
