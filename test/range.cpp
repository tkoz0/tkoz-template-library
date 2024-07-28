#include <vector>
#include <cassert>

//#define DEBUG_PRINT

#include "../src/range.hpp"
#include "test_common.hpp"
using std::cout;
using std::endl;

using tkoz::Range;
using tkoz::IncRange;
using tkoz::DecRange;

// compare a range with the values it should generate
template <typename TKOZ_RANGE>
void check_range(TKOZ_RANGE r, std::initializer_list<typename TKOZ_RANGE::num_t> l)
{
#ifdef DEBUG_PRINT
    cout << "expected  :";
    for (auto i : l)
        cout << " " << debug_int(i);
    cout << endl;
#endif
    std::vector<typename TKOZ_RANGE::num_t> v;
    for (size_t i : r)
    {
        v.push_back(i);
        assert(v.size() < 1000); // if it gets too big, expect there is an issue
    }
    if (v.empty())
        assert(r.begin() == r.end());
#ifdef DEBUG_PRINT
    cout << "calculated:";
    for (auto i : v)
        cout << " " << debug_int(i);
    cout << endl;
#endif
    assert(v == std::vector<typename TKOZ_RANGE::num_t>(l));
}

int main()
{
    check_range(Range<std::size_t>(5),{0,1,2,3,4});
    check_range(Range<std::size_t>(5,10),{5,6,7,8,9});
    check_range(Range<std::size_t>(),{});
    check_range(Range<std::size_t>(0),{});
    check_range(Range<std::size_t>(11,99,11),{11,22,33,44,55,66,77,88});
    check_range(Range<std::size_t>(11,100,11),{11,22,33,44,55,66,77,88,99});
    check_range(Range<std::size_t>(25,25,6),{});
    check_range(Range<size_t>(25,26),{25});
    check_range(Range<size_t>(25,25),{});
    check_range(Range<size_t>(25,24),{});
    check_range(Range<size_t>(40,50,3),{40,43,46,49});
    check_range(Range<size_t>(40,49,3),{40,43,46});
    check_range(Range<size_t>(40,40,3),{});
    check_range(Range<size_t>(40,39,3),{});
    check_range(Range<size_t>(40,10,3),{});
    check_range(Range<int64_t>(),{});
    check_range(Range<int64_t>(7),{0,1,2,3,4,5,6});
    check_range(Range<int64_t>(4,9),{4,5,6,7,8});
    check_range(Range<int64_t>(4,18,5),{4,9,14});
    check_range(Range<int64_t>(4,19,5),{4,9,14});
    check_range(Range<int64_t>(4,20,5),{4,9,14,19});
    check_range(Range<int64_t>(4,-8,-3),{4,1,-2,-5});
    check_range(Range<int64_t>(4,-9,-3),{4,1,-2,-5,-8});
    check_range(Range<int64_t>(4,1,-3),{4});
    check_range(Range<int64_t>(4,2,-3),{4});
    check_range(Range<int64_t>(4,3,-3),{4});
    check_range(Range<int64_t>(4,4,-3),{});
    check_range(Range<int64_t>(4,5,-3),{});
    check_range(Range<int64_t>(-12,-11,-6),{});
    check_range(Range<int64_t>(-12,-12,-6),{});
    check_range(Range<int64_t>(-12,-13,-6),{-12});
    check_range(Range<int64_t>(-12,-24,-6),{-12,-18});
    check_range(Range<int64_t>(-12,-25,-6),{-12,-18,-24});
    check_range(IncRange<std::size_t>(),{});
    check_range(IncRange<std::size_t>(4),{0,1,2,3});
    check_range(IncRange<std::size_t>(3,7),{3,4,5,6});
    check_range(DecRange<std::size_t>(),{});
    check_range(DecRange<std::size_t>(6),{5,4,3,2,1,0});
    check_range(DecRange<std::size_t>(7,3),{7,6,5,4});
    auto r1 = IncRange<size_t>();
    auto r2 = DecRange<size_t>();
    assert(r1.begin() == r1.end());
    assert(r2.begin() == r2.end());
    check_range(IncRange<int>(-3,4),{-3,-2,-1,0,1,2,3});
    check_range(DecRange<int>(3,-4),{3,2,1,0,-1,-2,-3});
    check_range(IncRange<int>(-7,-7),{});
    check_range(DecRange<int>(7,7),{});
    check_range(Range<int64_t>(10,5,-2),{10,8,6});
    check_range(Range<int64_t>(10,6,-2),{10,8});
    check_range(Range<int64_t>(30,-21,-13),{30,17,4,-9});
    check_range(Range<int64_t>(30,-22,-13),{30,17,4,-9});
    check_range(Range<int64_t>(30,-23,-13),{30,17,4,-9,-22});
    check_range(Range<int64_t>(30,-24,-13),{30,17,4,-9,-22});
    check_range(Range<int8_t>(-100,100,30),{-100,-70,-40,-10,20,50,80});
    check_range(Range<int8_t>(-100,110,30),{-100,-70,-40,-10,20,50,80});
    check_range(Range<int8_t>(-100,111,30),{-100,-70,-40,-10,20,50,80,110});
    check_range(Range<int8_t>(100,-110,-30),{100,70,40,10,-20,-50,-80});
    check_range(Range<int8_t>(100,-111,-30),{100,70,40,10,-20,-50,-80,-110});
    check_range(Range<int8_t>(120,126,2),{120,122,124});
    check_range(Range<int8_t>(120,127,2),{120,122,124,126});
    check_range(Range<int8_t>(-124,-126,-3),{-124});
    check_range(Range<int8_t>(-124,-127,-3),{-124});
    check_range(Range<int8_t>(-124,-128,-3),{-124,-127});
    return 0;
}
