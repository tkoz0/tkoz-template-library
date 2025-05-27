//
// Compile time tests related to metaprogramming utils
//

#include <tkoz/stl/Meta.hpp>

// only checking compile time stuff, does not need to run anything
int main()
{
    using namespace tkoz::stl::meta;

    // tests for isSame
    static_assert(isSame<bool,bool>);
    static_assert(!isSame<bool*,bool>);
    static_assert(!isSame<bool**,bool>);
    static_assert(!isSame<bool&,bool>);
    static_assert(!isSame<bool&&,bool>);
    static_assert(!isSame<bool&,bool&&>);
    static_assert(!isSame<const bool,bool>);
    static_assert(isSame<void*,void*>);
    static_assert(!isSame<void*,void**>);
    static_assert(!isSame<void**,void*>);

    // check of default sign (note char and signed char are different)
    static_assert(!isSame<char,signed char>);
    static_assert(!isSame<char,unsigned char>);
    static_assert(isSame<short,signed short>);
    static_assert(!isSame<short,unsigned short>);
    static_assert(isSame<int,signed int>);
    static_assert(!isSame<int,unsigned int>);
    static_assert(isSame<long,signed long>);
    static_assert(!isSame<long,unsigned long>);
    static_assert(isSame<long long,signed long long>);
    static_assert(!isSame<long long,unsigned long long>);

    // tests fore removeRef
    static_assert(isSame<removeRef<bool>,bool>);
    static_assert(isSame<removeRef<bool&>,bool>);
    static_assert(isSame<removeRef<bool&&>,bool>);
    static_assert(isSame<removeRef<void*>,void*>);
    static_assert(isSame<removeRef<void*&>,void*>);
    static_assert(isSame<removeRef<void*&&>,void*>);

    // tests for isSameAsAny
    static_assert(!isSameAsAny<char,signed char,unsigned char>);
    static_assert(!isSameAsAny<bool>);
    static_assert(isSameAsAny<bool,bool>);
    static_assert(isSameAsAny<bool,void,bool>);
    static_assert(!isSameAsAny<bool,void,void*>);
    static_assert(!isSameAsAny<char,int,int,int>);
}
