//
// Compile time tests for List (parameter pack)
//

#include <tkoz/metacalc/Lists.hpp>

#include <tkoz/stl/Meta.hpp>

// tests for large instantiations
#define BIG_TESTS 0
// tests for even larger instantiations
#define HUGE_TESTS 0

int main()
{
    using namespace tkoz::metacalc;
    namespace meta = tkoz::stl::meta;

    // IsList
    static_assert(isList<List<bool>>);
    static_assert(!isList<bool>);
    static_assert(!isList<double>);

    // IsIndexList
    static_assert(isIndexList<List<tkoz::stl::usize_t,3,8,5>>);
    static_assert(isIndexList<IndexList<7,4,2>>);
    static_assert(!isIndexList<int>);
    static_assert(!isIndexList<List<char,'a','A'>>);
    static_assert(!isIndexList<List<bool,true,false>>);
    static_assert(!isIndexList<List<float>>);
    static_assert(!isIndexList<List<double,2.5>>);

    // IndexRange
    static_assert(meta::isSame<IndexRange<0,0>,IndexList<>>);
    static_assert(meta::isSame<IndexRange<0,1>,IndexList<0>>);
    static_assert(meta::isSame<IndexRange<0,2>,IndexList<0,1>>);
    static_assert(meta::isSame<IndexRange<18,18>,IndexList<>>);
    static_assert(meta::isSame<IndexRange<18,19>,IndexList<18>>);
    static_assert(meta::isSame<IndexRange<18,20>,IndexList<18,19>>);
    static_assert(meta::isSame<IndexRange<0,10>,IndexList<0,1,2,3,4,5,6,7,8,9>>);
    static_assert(meta::isSame<IndexRange<10,20>,IndexList<10,11,12,13,14,15,16,17,18,19>>);
#if BIG_TESTS
    IndexRange<100,1000>();
    IndexRange<0,1100>();
#endif
#if HUGE_TESTS
    IndexRange<12000,20000>();
    IndexRange<5,50000>();
#endif
    // the below should not compile
    //IndexRange<100,99>();
    //IndexRange<5,3>();
    //IndexRange<25,5>();

    // ConcatLists
    static_assert(meta::isSame<ConcatLists<List<bool>>,List<bool>>);
    static_assert(meta::isSame<ConcatLists<List<bool,true,false>,List<bool,false,true>>,
                               List<bool,true,false,false,true>>);
    static_assert(meta::isSame<ConcatLists<List<int,100,101,102>,List<int,200,201>,List<int,300>>,
                               List<int,100,101,102,200,201,300>>);
#if BIG_TESTS
    ConcatLists<IndexRange<100,1000>>();
    ConcatLists<IndexRange<0,100>,IndexRange<100,200>>();
#endif
    // does not compile
    //ConcatLists<List<int,0>,List<bool,false>>();
    //ConcatLists<float>();

    // ListSelect
    static_assert(meta::isSame<ListSelect<IndexList<10,11,12,13,14,15>,IndexList<1,2,3>>,
                               IndexList<11,12,13>>);
    static_assert(meta::isSame<ListSelect<List<int>,IndexList<>>,
                               List<int>>);
    static_assert(meta::isSame<ListSelect<List<int,-5,-10,-15,-20>,IndexList<3>>,
                               List<int,-20>>);

    // ListSplitLo
    static_assert(meta::isSame<ListSplitLo<IndexRange<10,10>>,IndexList<>>);
    static_assert(meta::isSame<ListSplitLo<IndexRange<10,11>>,IndexList<>>);
    static_assert(meta::isSame<ListSplitLo<IndexRange<10,12>>,IndexList<10>>);
    static_assert(meta::isSame<ListSplitLo<IndexRange<105,130>>,IndexRange<105,117>>);
    static_assert(meta::isSame<ListSplitLo<IndexRange<102,124>>,IndexRange<102,113>>);

    // ListSplitHi
    static_assert(meta::isSame<ListSplitHi<IndexRange<10,10>>,IndexList<>>);
    static_assert(meta::isSame<ListSplitHi<IndexRange<10,11>>,IndexList<10>>);
    static_assert(meta::isSame<ListSplitHi<IndexRange<10,12>>,IndexList<11>>);
    static_assert(meta::isSame<ListSplitHi<IndexRange<105,130>>,IndexRange<117,130>>);
    static_assert(meta::isSame<ListSplitHi<IndexRange<102,124>>,IndexRange<113,124>>);
}
