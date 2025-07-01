///
/// unit tests for tkoz::stl::CString (extended C string)
///

#include <tkoz/Test.hpp>

#include <tkoz/stl/CString.hpp>
#include <tkoz/stl/Concepts.hpp>
#include <tkoz/stl/Exceptions.hpp>
#include <tkoz/stl/Meta.hpp>
#include <tkoz/stl/Utils.hpp>

#include <compare>

// instantiate template for accurate code coverage report
template class tkoz::stl::CString<char>;
template class tkoz::stl::CString<wchar_t>;
template class tkoz::stl::CString<int>;
template class tkoz::stl::CString<char,false>;
template class tkoz::stl::CString<wchar_t,false>;
template class tkoz::stl::CString<int,false>;

using CString = tkoz::stl::CString<char>;
using CStringNoNull = tkoz::stl::CString<char,false>;
using WCString = tkoz::stl::CString<wchar_t>;
using WCStringNoNull = tkoz::stl::CString<wchar_t,false>;
using IntString = tkoz::stl::CString<int>;
using IntStringNoNull = tkoz::stl::CString<int,false>;

// default argument is char
static_assert(tkoz::stl::meta::isSame<CString,tkoz::stl::CString<char,true>>);

TEST_RUNNER_MAIN

TEST_CASE_CREATE(testCtorDefault)
{
    CString s1;
    TEST_ASSERT_TRUE(s1.isNull());
    TEST_ASSERT_EQ(s1.ptr(),nullptr);
    TEST_ASSERT_EQ(s1.len(),0);
    TEST_ASSERT_EQ(s1,nullptr);
    TEST_ASSERT_NE(s1,"");
    TEST_ASSERT_NE(s1,"s1");

    const CString s2;
    TEST_ASSERT_TRUE(s2.isNull());
    TEST_ASSERT_EQ(s2.ptr(),nullptr);
    TEST_ASSERT_EQ(s2.len(),0);
    TEST_ASSERT_EQ(s2,nullptr);
    TEST_ASSERT_NE(s2,"");
    TEST_ASSERT_NE(s2,"s2");

    const CString *s3 = new CString;
    TEST_ASSERT_TRUE(s3->isNull());
    TEST_ASSERT_EQ(s3->ptr(),nullptr);
    TEST_ASSERT_EQ(s3->len(),0);
    TEST_ASSERT_EQ(*s3,nullptr);
    TEST_ASSERT_NE(*s3,"");
    TEST_ASSERT_NE(*s3,"s3");

    CString *s4 = new CString;
    TEST_ASSERT_TRUE(s4->isNull());
    TEST_ASSERT_EQ(s4->ptr(),nullptr);
    TEST_ASSERT_EQ(s4->len(),0);
    TEST_ASSERT_EQ(*s4,nullptr);
    TEST_ASSERT_NE(*s4,"");
    TEST_ASSERT_NE(*s4,"s4");

    delete s3;
    delete s4;
}

TEST_CASE_CREATE(testCtorCstr)
{
    CString s1(nullptr);
    TEST_ASSERT_TRUE(s1.isNull());
    TEST_ASSERT_EQ(s1.ptr(),nullptr);
    TEST_ASSERT_EQ(s1.len(),0);
    TEST_ASSERT_EQ(nullptr,s1);
    TEST_ASSERT_NE("",s1);
    TEST_ASSERT_NE("no",s1);

    CString s2("string");
    TEST_ASSERT_FALSE(s2.isNull());
    TEST_ASSERT_NE(nullptr,s2.ptr());
    TEST_ASSERT_EQ(6,s2.len());
    TEST_ASSERT_NE(nullptr,s2);
    TEST_ASSERT_NE("",s2);
    TEST_ASSERT_NE("STRING",s2);
    TEST_ASSERT_EQ("string",s2);
    char *s2p = s2.ptr();
    TEST_ASSERT_EQ(s2p[0],'s');
    TEST_ASSERT_EQ(s2p[1],'t');
    TEST_ASSERT_EQ(s2p[2],'r');
    TEST_ASSERT_EQ(s2p[3],'i');
    TEST_ASSERT_EQ(s2p[4],'n');
    TEST_ASSERT_EQ(s2p[5],'g');
    TEST_ASSERT_EQ(s2p[6],'\0');

    CString s3("");
    TEST_ASSERT_FALSE(s3.isNull());
    TEST_ASSERT_NE(s3.ptr(),nullptr);
    TEST_ASSERT_EQ(s3.len(),0);
    TEST_ASSERT_NE(s3," ");
    TEST_ASSERT_EQ(s3,"");
    TEST_ASSERT_EQ(*s3.ptr(),'\0');
}

TEST_CASE_CREATE(testCtorRepchar)
{
    CString s1(0,'0');
    TEST_ASSERT_FALSE(s1.isNull());
    TEST_ASSERT_NE(s1.ptr(),nullptr);
    TEST_ASSERT_EQ(s1.len(),0);
    TEST_ASSERT_EQ(s1,"");
    TEST_ASSERT_NE(s1,nullptr);
    TEST_ASSERT_EQ(*s1.ptr(),'\0');

    CString s2(1,'Z');
    TEST_ASSERT_EQ(s2.len(),1);
    TEST_ASSERT_NE(s2,"");
    TEST_ASSERT_EQ(s2,"Z");
    TEST_ASSERT_NE(s2,"ZZ");
    TEST_ASSERT_NE(s2,"ZZZ");
    TEST_ASSERT_EQ(s2.ptr()[0],'Z');
    TEST_ASSERT_EQ(s2.ptr()[1],'\0');

    CString s3(12,'_');
    TEST_ASSERT_EQ(s3.len(),12);
    TEST_ASSERT_EQ(s3,"____________");
    TEST_ASSERT_EQ(s3.ptr()[11],'_');
    TEST_ASSERT_EQ(s3.ptr()[12],'\0');
}

TEST_CASE_CREATE(testCtorCopy)
{
    CString s1;
    CString s2(s1);
    TEST_ASSERT_EQ(s1,s2);
    TEST_ASSERT_EQ(s1.ptr(),s2.ptr());
    TEST_ASSERT_EQ(s1.ptr(),nullptr);

    CString s3("Yuuka");
    CString s4(s3);
    TEST_ASSERT_EQ(s3,s4);
    TEST_ASSERT_EQ(s3.len(),5);
    TEST_ASSERT_EQ(s4.len(),5);
    TEST_ASSERT_EQ(s3.ptr()[0],'Y');
    TEST_ASSERT_EQ(s3.ptr()[1],'u');
    TEST_ASSERT_EQ(s3.ptr()[2],'u');
    TEST_ASSERT_EQ(s3.ptr()[3],'k');
    TEST_ASSERT_EQ(s3.ptr()[4],'a');
    TEST_ASSERT_EQ(s3.ptr()[5],'\0');
    TEST_ASSERT_EQ(s4.ptr()[0],'Y');
    TEST_ASSERT_EQ(s4.ptr()[1],'u');
    TEST_ASSERT_EQ(s4.ptr()[2],'u');
    TEST_ASSERT_EQ(s4.ptr()[3],'k');
    TEST_ASSERT_EQ(s4.ptr()[4],'a');
    TEST_ASSERT_EQ(s4.ptr()[5],'\0');
}

TEST_CASE_CREATE(testCtorMove)
{
    CString s1;
    CString s2(tkoz::stl::move(s1)); // value of s1 is now undefined
    TEST_ASSERT_EQ(s2.ptr(),nullptr);
    TEST_ASSERT_EQ(s2,nullptr);
    TEST_ASSERT_EQ(s2.len(),0);

    CString s3("Blue Archive");
    CString s4(tkoz::stl::move(s3)); // value of s3 is now undefined
    TEST_ASSERT_EQ(s4.len(),12);
    TEST_ASSERT_NE(s4,nullptr);
    TEST_ASSERT_EQ(s4,"Blue Archive");
    TEST_ASSERT_EQ(s4.ptr()[0],'B');
    TEST_ASSERT_EQ(s4.ptr()[1],'l');
    TEST_ASSERT_EQ(s4.ptr()[2],'u');
    TEST_ASSERT_EQ(s4.ptr()[3],'e');
    TEST_ASSERT_EQ(s4.ptr()[4],' ');
    TEST_ASSERT_EQ(s4.ptr()[5],'A');
    TEST_ASSERT_EQ(s4.ptr()[6],'r');
    TEST_ASSERT_EQ(s4.ptr()[7],'c');
    TEST_ASSERT_EQ(s4.ptr()[8],'h');
    TEST_ASSERT_EQ(s4.ptr()[9],'i');
    TEST_ASSERT_EQ(s4.ptr()[10],'v');
    TEST_ASSERT_EQ(s4.ptr()[11],'e');
    TEST_ASSERT_EQ(s4.ptr()[12],'\0');
}

TEST_CASE_CREATE(testAssignCopy)
{
    CString s1;
    CString s2;
    CString& s3 = (s2 = s1); // reference to s2
    TEST_ASSERT_EQ(&s2,&s3);
    TEST_ASSERT_EQ(s1,s2);

    s2 = "Noa";
    TEST_ASSERT_EQ(s2.len(),3);
    TEST_ASSERT_EQ(s2.ptr()[0],'N');
    TEST_ASSERT_EQ(s2.ptr()[1],'o');
    TEST_ASSERT_EQ(s2.ptr()[2],'a');
    TEST_ASSERT_EQ(s2.ptr()[3],'\0');

    s3 = "Rio";
    TEST_ASSERT_EQ(s3.len(),3);
    TEST_ASSERT_EQ(s3.ptr()[0],'R');
    TEST_ASSERT_EQ(s3.ptr()[1],'i');
    TEST_ASSERT_EQ(s3.ptr()[2],'o');
    TEST_ASSERT_EQ(s3.ptr()[3],'\0');

    TEST_ASSERT_EQ(s2,"Rio");
    TEST_ASSERT_EQ(&s2,&s3);

    CString s4("Chisato");
    CString s5 = s4;
    TEST_ASSERT_EQ(s4.len(),7);
    TEST_ASSERT_EQ(s5.len(),7);
    TEST_ASSERT_NE(s4.ptr(),s5.ptr());
    TEST_ASSERT_EQ(s4,s5);
    TEST_ASSERT_EQ(s5.ptr()[0],'C');
    TEST_ASSERT_EQ(s5.ptr()[1],'h');
    TEST_ASSERT_EQ(s5.ptr()[2],'i');
    TEST_ASSERT_EQ(s5.ptr()[3],'s');
    TEST_ASSERT_EQ(s5.ptr()[4],'a');
    TEST_ASSERT_EQ(s5.ptr()[5],'t');
    TEST_ASSERT_EQ(s5.ptr()[6],'o');
    TEST_ASSERT_EQ(s5.ptr()[7],'\0');
}

TEST_CASE_CREATE(testAssignMove)
{
    CString s1;
    CString s2 = tkoz::stl::move(s1);
    TEST_ASSERT_EQ(s2,nullptr);
    TEST_ASSERT_EQ(s2.len(),0);

    CString s3("");
    CString s4;
    CString& s5 = (s4 = tkoz::stl::move(s3));
    TEST_ASSERT_EQ(&s4,&s5);
    TEST_ASSERT_EQ(s5.len(),0);
    TEST_ASSERT_NE(s5.ptr(),nullptr);
    TEST_ASSERT_EQ(s5.ptr()[0],'\0');

    CString s6("Takina");
    s4 = tkoz::stl::move(s6); // s6 value now undefined
    TEST_ASSERT_NE(s4.ptr(),nullptr);
    TEST_ASSERT_EQ(s4,"Takina");
    TEST_ASSERT_NE(s4,"");
    TEST_ASSERT_EQ(s4.ptr()[0],'T');
    TEST_ASSERT_EQ(s4.ptr()[1],'a');
    TEST_ASSERT_EQ(s4.ptr()[2],'k');
    TEST_ASSERT_EQ(s4.ptr()[3],'i');
    TEST_ASSERT_EQ(s4.ptr()[4],'n');
    TEST_ASSERT_EQ(s4.ptr()[5],'a');
    TEST_ASSERT_EQ(s4.ptr()[6],'\0');
    TEST_ASSERT_EQ(s5,"Takina");
}

TEST_CASE_CREATE(testLen)
{
    CString s1;
    TEST_ASSERT_EQ(s1.len(),0);
    CString s2("");
    TEST_ASSERT_EQ(s2.len(),0);
    CString s3("\t");
    TEST_ASSERT_EQ(s3.len(),1);
    CString s4("\r\n");
    TEST_ASSERT_EQ(s4.len(),2);
    CString s5(323,'*');
    TEST_ASSERT_EQ(s5.len(),323);
    CString s6("The quick brown fox jumps over the lazy dog");
    TEST_ASSERT_EQ(s6.len(),43);
}

const char* getConstPtr(const CString& s)
{
    return s.ptr();
}

TEST_CASE_CREATE(testPtr)
{
    CString s1;
    TEST_ASSERT_EQ(s1.ptr(),nullptr);
    const char *empty = "";
    CString s2(empty);
    TEST_ASSERT_NE(s2.ptr(),nullptr);
    TEST_ASSERT_NE(s2.ptr(),empty);

    char array[5] = {'w','o','r','d','\0'};
    CString s3(array);
    TEST_ASSERT_NE(array,s3.ptr());
    TEST_ASSERT_EQ(s3,"word");
    array[2] = '\0';
    CString s4(array);
    TEST_ASSERT_NE(array,s4.ptr());
    TEST_ASSERT_NE(s3.ptr(),s4.ptr());
    TEST_ASSERT_EQ(s3,"word");
    TEST_ASSERT_EQ(s4,"wo");

    TEST_ASSERT_EQ(s1.ptr(),getConstPtr(s1));
    TEST_ASSERT_EQ(s2.ptr(),getConstPtr(s2));
    TEST_ASSERT_EQ(s3.ptr(),getConstPtr(s3));
    TEST_ASSERT_EQ(s4.ptr(),getConstPtr(s4));

    const CString *s5 = new CString("content");
    TEST_ASSERT_NE(s5->ptr(),nullptr);
    const CString s6;
    TEST_ASSERT_EQ(s6.ptr(),nullptr);

    delete s5;
}

TEST_CASE_CREATE(testBool)
{
    CString s1;
    TEST_ASSERT_FALSE(s1);
    CString s2("");
    TEST_ASSERT_FALSE(s2);
    CString s3("=");
    TEST_ASSERT_TRUE(s3);
    CString s4("this is a string");
    TEST_ASSERT_TRUE(s4);
}

TEST_CASE_CREATE(testIsNull)
{
    CString s1;
    TEST_ASSERT_TRUE(s1.isNull());
    CString s2(0,'&');
    TEST_ASSERT_FALSE(s2.isNull());
    CString s3("abcdefghijklmnopqrstuvwxyz");
    TEST_ASSERT_FALSE(s3.isNull());
    CString s4("this is a string");
    TEST_ASSERT_FALSE(s4.isNull());
}

// shortened names for strong ordering stuff
using so = std::strong_ordering;
static const so lt = so::less;
static const so gt = so::greater;
static const so eq = so::equal;
static_assert(so::equal == so::equivalent);
using tkoz::stl::usize_t;

// for compare test cases, create an array of test data with this infoi
struct cmp_test_t
{
    const char * const left;
    const char * const right;
    const so cmp;
};

// test data array followed by its length
static const cmp_test_t CMP_TEST_DATA[] =
{
    {nullptr,nullptr,eq},
    {nullptr,"",lt},
    {"",nullptr,gt},
    {nullptr,"nullptr",lt},
    {"nullptr",nullptr,gt},
    {"some","some",eq},
    {"something","some",gt},
    {"some","something",lt},
    {"there","their",gt},
    {"there","there",eq},
    {"there","theyre",lt},
    {"Zebra","apple",lt},
    {"apple","Zebra",gt},
    {"the","the",eq},
    {"the","there",lt},
    {"chap","chip",lt},
    {"shape","shame",gt},
    {"Phosphorus","phosphorus",lt},
    {"trip","trim",gt},
    {"C++","C++",eq},
    {"C","C++",lt},
    {"8999","99",lt},
    {"\t","\n",lt},
    {"\n","\t",gt},
    {"","_",lt},
    {""," ",lt},
    {"64","",gt},
    {" ","",gt},
    {"42","4",gt},
    {"42","5",lt},
    {"893","893",eq},
    {" language","  programming",gt},
    {"MIYAKO SHIKIMORI","miyako shikimori",lt},
    {"yuuki izumi","yuuki izumi",eq},
    {"","",eq},
    {"?xml","xml",lt},
    {nullptr,"!",lt},
    {nullptr,"-_-",lt},
    {"\\=\\",nullptr,gt},
    {"\t\n ",nullptr,gt}
};
[[maybe_unused]] static const usize_t CMP_TEST_COUNT =
    sizeof(CMP_TEST_DATA) / sizeof(CMP_TEST_DATA[0]);

TEST_CASE_CREATE(testPtrCmpEq)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == eq)
        {
            TEST_ASSERT_TRUE(CString::ptrCmpEq(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpEq(left,right));
        }
        else
        {
            TEST_ASSERT_FALSE(CString::ptrCmpEq(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpEq(left,right));
        }
    }
}

TEST_CASE_CREATE(testPtrCmpNe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == eq)
        {
            TEST_ASSERT_FALSE(CString::ptrCmpNe(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpNe(left,right));
        }
        else
        {
            TEST_ASSERT_TRUE(CString::ptrCmpNe(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpNe(left,right));
        }
    }
}

TEST_CASE_CREATE(testPtrCmp3way)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        TEST_ASSERT_EQ(CString::ptrCmp3way(left,right),cmp);
        if (left && right)
            TEST_ASSERT_EQ(CStringNoNull::ptrCmp3way(left,right),cmp);
    }
}

TEST_CASE_CREATE(testPtrCmpLt)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == lt)
        {
            TEST_ASSERT_TRUE(CString::ptrCmpLt(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpLt(left,right));
        }
        else
        {
            TEST_ASSERT_FALSE(CString::ptrCmpLt(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpLt(left,right));
        }
    }
}

TEST_CASE_CREATE(testPtrCmpLe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == gt)
        {
            TEST_ASSERT_FALSE(CString::ptrCmpLe(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpLe(left,right));
        }
        else
        {
            TEST_ASSERT_TRUE(CString::ptrCmpLe(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpLe(left,right));
        }
    }
}

TEST_CASE_CREATE(testPtrCmpGt)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == gt)
        {
            TEST_ASSERT_TRUE(CString::ptrCmpGt(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpGt(left,right));
        }
        else
        {
            TEST_ASSERT_FALSE(CString::ptrCmpGt(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpGt(left,right));
        }
    }
}

TEST_CASE_CREATE(testPtrCmpGe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        if (cmp == lt)
        {
            TEST_ASSERT_FALSE(CString::ptrCmpGe(left,right));
            if (left && right)
                TEST_ASSERT_FALSE(CStringNoNull::ptrCmpGe(left,right));
        }
        else
        {
            TEST_ASSERT_TRUE(CString::ptrCmpGe(left,right));
            if (left && right)
                TEST_ASSERT_TRUE(CStringNoNull::ptrCmpGe(left,right));
        }
    }
}

TEST_CASE_CREATE(testOpEq)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp == 0)
        {
            TEST_ASSERT_EQ(CString(left),CString(right));
            TEST_ASSERT_EQ(left,CString(right));
            TEST_ASSERT_EQ(CString(left),right);
        }
}

TEST_CASE_CREATE(testOpNe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp != 0)
        {
            TEST_ASSERT_NE(CString(left),CString(right));
            TEST_ASSERT_NE(left,CString(right));
            TEST_ASSERT_NE(CString(left),right);
        }
}

TEST_CASE_CREATE(testOp3way)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
    {
        TEST_ASSERT_EQ(CString(left) <=> CString(right), cmp);
        TEST_ASSERT_EQ(left <=> CString(right), cmp);
        TEST_ASSERT_EQ(CString(left) <=> right, cmp);
    }
}

TEST_CASE_CREATE(testOpLt)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp < 0)
        {
            TEST_ASSERT_LT(CString(left),CString(right));
            TEST_ASSERT_LT(left,CString(right));
            TEST_ASSERT_LT(CString(left),right);
        }
}

TEST_CASE_CREATE(testOpLe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp <= 0)
        {
            TEST_ASSERT_LE(CString(left),CString(right));
            TEST_ASSERT_LE(left,CString(right));
            TEST_ASSERT_LE(CString(left),right);
        }
}

TEST_CASE_CREATE(testOpGt)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp > 0)
        {
            TEST_ASSERT_GT(CString(left),CString(right));
            TEST_ASSERT_GT(left,CString(right));
            TEST_ASSERT_GT(CString(left),right);
        }
}

TEST_CASE_CREATE(testOpGe)
{
    for (auto [left,right,cmp] : CMP_TEST_DATA)
        if (cmp >= 0)
        {
            TEST_ASSERT_GE(CString(left),CString(right));
            TEST_ASSERT_GE(left,CString(right));
            TEST_ASSERT_GE(CString(left),right);
        }
}

TEST_CASE_CREATE(testPtrWrap)
{
    char *c1 = new char[1];
    TEST_ASSERT(c1);
    c1[0] = '\0';
    auto s1 = CString::ptrWrap(c1);
    TEST_ASSERT_EQ(s1.len(),0);
    TEST_ASSERT_EQ(c1[0],'\0');

    char *c2 = nullptr;
    auto s2 = CString::ptrWrap(c2);
    TEST_ASSERT_EQ(s2,nullptr);
    TEST_ASSERT_TRUE(s2.isNull());

    char *c3 = new char[20];
    TEST_ASSERT(c3);
    c3[0] = 'V';
    c3[1] = 'l';
    c3[2] = 'a';
    c3[3] = 'd';
    c3[4] = 'i';
    c3[5] = 'L';
    c3[6] = 'E';
    c3[7] = 'N';
    c3[8] = 'A';
    c3[9] =  ' ';
    c3[10] = 'M';
    c3[11] = 'i';
    c3[12] = 'l';
    c3[13] = 'i';
    c3[14] = 'z';
    c3[15] = 'e';
    c3[16] = '\0';
    auto s3 = CStringNoNull::ptrWrap(c3);
    TEST_ASSERT_EQ(s3.len(),16);
    TEST_ASSERT_EQ(s3,"VladiLENA Milize");

    auto s4 = CString::ptrWrap(nullptr);
    TEST_ASSERT_TRUE(s4.isNull());

    char *c4 = new char[14];
    TEST_ASSERT(c4);
    c4[0] = 'S';
    c4[1] = 'e';
    c4[2] = 't';
    c4[3] = 's';
    c4[4] = 'u';
    c4[5] = 'n';
    c4[6] = 'a';
    c4[7] = ' ';
    c4[8] = 'Y';
    c4[9] = 'u';
    c4[10] = 'u';
    c4[11] = 'k';
    c4[12] = 'i';
    c4[13] = '\0';
    auto s5 = CString::ptrWrap(c4);
    TEST_ASSERT_EQ(s5.len(),13);
    TEST_ASSERT_EQ(s5,"Setsuna Yuuki");

    char *c5 = new char[10];
    TEST_ASSERT(c5);
    c5[0] = 'V';
    c5[1] = 'i';
    c5[2] = 'v';
    c5[3] = 'y';
    c5[4] = '\0';
    auto s6 = CString::ptrWrap(c5);
    TEST_ASSERT_EQ(s6.len(),4);
    TEST_ASSERT_EQ(s6,"Vivy");
}

TEST_CASE_CREATE(testPtrLen)
{
    TEST_ASSERT_EQ(CString::ptrLen(nullptr),0);
    char c1[10];
    c1[0] = 'a';
    c1[1] = 'z';
    c1[2] = 'A';
    c1[3] = 'Z';
    c1[4] = '\0';
    TEST_ASSERT_EQ(CStringNoNull::ptrLen(c1),4);
    TEST_ASSERT_TRUE(CString::ptrCmpEq(c1,"azAZ"));
    CString s1("");
    TEST_ASSERT_TRUE(CStringNoNull::ptrCmpEq(s1.ptr(),""));
}

TEST_CASE_CREATE(testPtrCopyNew)
{
    TEST_ASSERT_EQ(CString::ptrCopyNew(nullptr),nullptr);
    char c1[50];
    c1[0] = '[';
    c1[1] = ']';
    c1[2] = '\0';
    char *c2 = CString::ptrCopyNew(c1);
    TEST_ASSERT_EQ(c2,CString("[]"));
    char *c3 = CStringNoNull::ptrCopyNew(c1);
    TEST_ASSERT_EQ(CString::ptrLen(c3),2);
    delete[] c2;
    delete[] c3;
}

TEST_CASE_CREATE(testPtrCopySrcDst)
{
    char c1[100];
    CString::ptrCopy("Aishia",c1);
    TEST_ASSERT_TRUE(CString::ptrCmpEq(c1,"Aishia"));
    c1[2] = '\0';
    char c2[10];
    CString::ptrCopy(c1,c2);
    TEST_ASSERT_TRUE(CString::ptrCmpEq(c2,"Ai"));
    CString::ptrCopy("",c2);
    TEST_ASSERT_TRUE(CString::ptrCmpEq(c2,""));
}

// for concat test cases
struct concat_test_t
{
    const char * const left;
    const char * const right;
    const char * const concat;
};

// test data and length
static const concat_test_t CONCAT_TEST_DATA[] =
{
    {nullptr,nullptr,nullptr},
    {nullptr,"",""},
    {"",nullptr,""},
    {"","derivative","derivative"},
    {"integral","","integral"},
    {"some","thing","something"},
    {"programming "," language","programming  language"},
    {"Lycoris","Recoil","LycorisRecoil"},
    {"Think","Pad","ThinkPad"}
};
[[maybe_unused]] static const usize_t CONCAT_TEST_COUNT =
    sizeof(CONCAT_TEST_DATA) / sizeof(CONCAT_TEST_DATA[0]);

TEST_CASE_CREATE(testPtrConcatNew)
{
    for (auto [left,right,concat] : CONCAT_TEST_DATA)
    {
        char *c1 = CString::ptrConcatNew(left,right);
        TEST_ASSERT_TRUE(CString::ptrCmpEq(c1,concat));
        delete[] c1;
        if (left && right)
        {
            char *c2 = CStringNoNull::ptrConcatNew(left,right);
            TEST_ASSERT_TRUE(CStringNoNull::ptrCmpEq(c2,concat));
            delete[] c2;
        }
    }
}

TEST_CASE_CREATE(testPtrConcat)
{
    char c1[100];
    for (auto [left,right,concat] : CONCAT_TEST_DATA)
    {
        CString::ptrConcat(left,right,c1);
        if (concat)
            TEST_ASSERT_TRUE(CString::ptrCmpEq(c1,concat));
        if (left && right)
        {
            CStringNoNull::ptrConcat(left,right,c1);
            TEST_ASSERT_TRUE(CStringNoNull::ptrCmpEq(c1,concat));
        }
    }
}

TEST_CASE_CREATE(testOpAdd)
{
    for (auto [left,right,concat] : CONCAT_TEST_DATA)
    {
        CString s1 = CString(left) + CString(right);
        CString s2 = left + CString(right);
        CString s3 = CString(left) + right;
        CString ss(concat);
        TEST_ASSERT_EQ(s1,ss);
        TEST_ASSERT_EQ(s2,ss);
        TEST_ASSERT_EQ(s3,ss);
    }
}

TEST_CASE_CREATE(testOpAddEq)
{
    for (auto [left,right,concat] : CONCAT_TEST_DATA)
    {
        CString s1(left);
        CString s2(left);
        CString ss(concat);
        CString &t1 = (s1 += right);
        CString &t2 = (s2 += CString(right));
        TEST_ASSERT_EQ(ss,s1);
        TEST_ASSERT_EQ(ss,s2);
        TEST_ASSERT_EQ(&t1,&s1);
        TEST_ASSERT_EQ(&t2,&s2);
    }
}

TEST_CASE_CREATE(testSubscriptTypes)
{
    CString s1;
    CString& ref = s1;
    const CString& cref = s1;
    using tkoz::stl::move;
    static_cast<void>(s1);
    static_cast<void>(ref);
    static_cast<void>(cref);
    using tkoz::stl::meta::isSame;

    static_assert(isSame<char&,decltype(s1[0])>);
    static_assert(isSame<char&,decltype(ref[0])>);
    static_assert(isSame<const char&,decltype(cref[0])>);
    static_assert(isSame<char&,decltype(move(s1)[0])>);
}

TEST_CASE_CREATE(testAtTypes)
{
    CString s1;
    CString& ref = s1;
    const CString& cref = s1;
    using tkoz::stl::move;
    static_cast<void>(s1);
    static_cast<void>(ref);
    static_cast<void>(cref);
    using tkoz::stl::meta::isSame;

    static_assert(isSame<char&,decltype(s1.at(0))>);
    static_assert(isSame<char&,decltype(ref.at(0))>);
    static_assert(isSame<const char&,decltype(cref.at(0))>);
    static_assert(isSame<char&,decltype(move(s1).at(0))>);
}

////
//TODO subscript modified to not support negative
////

TEST_CASE_CREATE(testSubscriptBool)
{
    CString s1("");
    TEST_ASSERT_EQ(s1[false],'\0');

    CString s2(" ");
    TEST_ASSERT_EQ(s2[false],' ');
    TEST_ASSERT_EQ(s2[true],'\0');

    CString s3("AB");
    TEST_ASSERT_EQ(s3[false],'A');
    TEST_ASSERT_EQ(s3[true],'B');
    tkoz::stl::swap(s3[false],s3[true]);
    TEST_ASSERT_EQ(s3,"BA");
    tkoz::stl::swap(s3[true],s3[false]);
    TEST_ASSERT_EQ(s3,"AB");
    s3[false] = 'C';
    s3[true] = 'D';
    TEST_ASSERT_EQ(s3,"CD");
    TEST_ASSERT_EQ(&s3[false]+1,&s3[true]);
}

// static cast helper
template <typename T, typename U>
T sc(U v)
{
    return static_cast<T>(v);
}

template <tkoz::stl::concepts::isPrimitiveInteger T>
void testSubscriptIntImpl()
{
    CString s1("");
    TEST_ASSERT_EQ(s1[sc<T>(0)],'\0');
    TEST_ASSERT_EQ(&s1[sc<T>(0)],s1.ptr());

    CString s2("A[i]");
    TEST_ASSERT_EQ(s2[sc<T>(0)],'A');
    TEST_ASSERT_EQ(s2[sc<T>(1)],'[');
    TEST_ASSERT_EQ(s2[sc<T>(2)],'i');
    TEST_ASSERT_EQ(s2[sc<T>(3)],']');
    TEST_ASSERT_EQ(s2[sc<T>(4)],'\0');
    tkoz::stl::swap(s2[sc<T>(1)],s2[sc<T>(3)]);
    TEST_ASSERT_EQ(s2,"A]i[");

    CString s3("0123456789");
    TEST_ASSERT_EQ(s3[sc<T>(0)],'0');
    TEST_ASSERT_EQ(s3[sc<T>(1)],'1');
    TEST_ASSERT_EQ(s3[sc<T>(5)],'5');
    TEST_ASSERT_EQ(s3[sc<T>(9)],'9');
    TEST_ASSERT_EQ(s3[sc<T>(10)],'\0');
    TEST_ASSERT_EQ(&s3[sc<T>(2)]+7,&s3[sc<T>(9)]);

    CString s4("a+=b;");
    TEST_ASSERT_EQ(s4[sc<T>(0)],'a');
    TEST_ASSERT_EQ(s4[sc<T>(1)],'+');
    TEST_ASSERT_EQ(s4[sc<T>(2)],'=');
    TEST_ASSERT_EQ(s4[sc<T>(3)],'b');
    TEST_ASSERT_EQ(s4[sc<T>(4)],';');
    TEST_ASSERT_EQ(s4[sc<T>(5)],'\0');
    tkoz::stl::swap(s4[sc<T>(0)],s4[sc<T>(3)]);
    TEST_ASSERT_EQ(s4,"b+=a;");
    TEST_ASSERT_EQ(&s4[sc<T>(0)]+3,&s4[sc<T>(3)]);

    CString s5("forty two");
    TEST_ASSERT_EQ(s5[sc<T>(0)],'f');
    TEST_ASSERT_EQ(s5[sc<T>(1)],'o');
    TEST_ASSERT_EQ(s5[sc<T>(2)],'r');
    TEST_ASSERT_EQ(s5[sc<T>(3)],'t');
    TEST_ASSERT_EQ(s5[sc<T>(4)],'y');
    TEST_ASSERT_EQ(s5[sc<T>(5)],' ');
    TEST_ASSERT_EQ(s5[sc<T>(6)],'t');
    TEST_ASSERT_EQ(s5[sc<T>(7)],'w');
    TEST_ASSERT_EQ(s5[sc<T>(8)],'o');
    TEST_ASSERT_EQ(s5[sc<T>(9)],'\0');
    TEST_ASSERT_EQ(&s5[sc<T>(3)]+4,&s5[sc<T>(7)]);
    TEST_ASSERT_EQ(s5,"forty two");
}

TEST_CASE_CREATE(testSubscriptSchar)
{
    testSubscriptIntImpl<signed char>();
}

TEST_CASE_CREATE(testSubscriptSshort)
{
    testSubscriptIntImpl<signed short>();
}

TEST_CASE_CREATE(testSubscriptSint)
{
    testSubscriptIntImpl<signed int>();
}

TEST_CASE_CREATE(testSubscriptSlong)
{
    testSubscriptIntImpl<signed long>();
}

TEST_CASE_CREATE(testSubscriptSll)
{
    testSubscriptIntImpl<signed long long>();
}

TEST_CASE_CREATE(testSubscriptUchar)
{
    testSubscriptIntImpl<unsigned char>();
}

TEST_CASE_CREATE(testSubscriptUshort)
{
    testSubscriptIntImpl<unsigned short>();
}

TEST_CASE_CREATE(testSubscriptUint)
{
    testSubscriptIntImpl<unsigned int>();
}

TEST_CASE_CREATE(testSubscriptUlong)
{
    testSubscriptIntImpl<unsigned long>();
}

TEST_CASE_CREATE(testSubscriptUll)
{
    testSubscriptIntImpl<unsigned long long>();
}

TEST_CASE_CREATE(testSubscriptOther)
{
    CString s1("");
    TEST_ASSERT_EQ(s1[0],'\0');
    TEST_ASSERT_EQ(s1[0u],'\0');
    TEST_ASSERT_EQ(s1[0ll],'\0');
    TEST_ASSERT_EQ(s1[0ull],'\0');
    TEST_ASSERT_EQ(s1[false],'\0');

    CString s2("0123456789");
    TEST_ASSERT_EQ(s2[0],'0');
    TEST_ASSERT_EQ(s2[1],'1');
    TEST_ASSERT_EQ(s2[5],'5');
    TEST_ASSERT_EQ(s2[8],'8');
    TEST_ASSERT_EQ(s2[9],'9');
    TEST_ASSERT_EQ(s2[10],'\0');
    // "negative indexing" for operator[] not supporting it directly
    usize_t l = s2.len();
    TEST_ASSERT_EQ(s2[l-1],'9');
    TEST_ASSERT_EQ(s2[l-2],'8');
    TEST_ASSERT_EQ(s2[l-5],'5');
    TEST_ASSERT_EQ(s2[l-9],'1');
    TEST_ASSERT_EQ(s2[l-10],'0');

    CString s3("AB");
    TEST_ASSERT_EQ(s3[false],'A');
    TEST_ASSERT_EQ(s3[true],'B');
    TEST_ASSERT_EQ(s3[(short)0],'A');
    TEST_ASSERT_EQ(s3[(long)1],'B');
    tkoz::stl::swap(s3[0],s3[1]);
    TEST_ASSERT_EQ(s3,"BA");
    s3[1] = 'C';
    TEST_ASSERT_EQ(s3,"BC");

    CString *s4 = new CString("(480)(915)(7236)");
    TEST_ASSERT_EQ((*s4)[(signed char)(s4->len()-8)],'5');
    TEST_ASSERT_EQ((*s4)[s4->len()-12],')');
    TEST_ASSERT_EQ((*s4)[(unsigned long long)10],'(');
    delete s4;
}

TEST_CASE_CREATE(testAtBool)
{
    using NE = tkoz::stl::NullError;
    using IE = tkoz::stl::IndexError;

    CString s1;
    TEST_EXCEPTION(s1.at(false),NE);
    TEST_EXCEPTION(s1.at(true),NE);

    s1 = "";
    TEST_ASSERT_EQ(s1.at(false),'\0');
    TEST_EXCEPTION(s1.at(true),IE);

    s1 = "()";
    TEST_ASSERT_EQ(s1.at(false),'(');
    TEST_ASSERT_EQ(s1.at(true),')');
}

template <typename T>
    requires tkoz::stl::concepts::isPrimitiveSignedInteger<T>
void testAtSignedImpl()
{
    using NE = tkoz::stl::NullError;
    using IE = tkoz::stl::IndexError;
    using tkoz::stl::swap;

    CString s1;
    TEST_EXCEPTION(s1.at(sc<T>(0)),NE);
    TEST_EXCEPTION(s1.at(sc<T>(-7)),NE);

    CString s2("");
    TEST_ASSERT_EQ(s2.at(sc<T>(0)),'\0');
    TEST_EXCEPTION(s2.at(sc<T>(-1)),IE);
    TEST_EXCEPTION(s2.at(sc<T>(1)),IE);

    CString s3("0123456789");
    TEST_ASSERT_EQ(s3.at(sc<T>(0)),'0');
    TEST_ASSERT_EQ(s3.at(sc<T>(9)),'9');
    TEST_ASSERT_EQ(s3.at(sc<T>(10)),'\0');
    TEST_ASSERT_EQ(s3.at(sc<T>(-1)),'9');
    TEST_ASSERT_EQ(s3.at(sc<T>(-2)),'8');
    TEST_ASSERT_EQ(s3.at(sc<T>(-9)),'1');
    TEST_ASSERT_EQ(s3.at(sc<T>(-10)),'0');
    TEST_ASSERT_EQ(&s3.at(sc<T>(5)),&s3.at(sc<T>(-5)));
    TEST_ASSERT_EQ(&s3.at(sc<T>(2))+4,&s3.at(sc<T>(-4)));
    swap(s3.at(sc<T>(0)),s3.at(sc<T>(-1)));
    swap(s3.at(sc<T>(1)),s3.at(sc<T>(-2)));
    swap(s3.at(sc<T>(2)),s3.at(sc<T>(-3)));
    swap(s3.at(sc<T>(3)),s3.at(sc<T>(-4)));
    swap(s3.at(sc<T>(4)),s3.at(sc<T>(-5)));
    TEST_ASSERT_EQ(s3,"9876543210");
    TEST_EXCEPTION(s3.at(sc<T>(-11)),IE);
    TEST_EXCEPTION(s3.at(sc<T>(11)),IE);
    TEST_EXCEPTION(s3.at(sc<T>(109)),IE);
    TEST_EXCEPTION(s3.at(sc<T>(-96)),IE);
}

template <typename T>
    requires tkoz::stl::concepts::isPrimitiveUnsignedInteger<T>
void testAtUnsignedImpl()
{
    using NE = tkoz::stl::NullError;
    using IE = tkoz::stl::IndexError;
    using tkoz::stl::swap;

    CString s1;
    TEST_EXCEPTION(s1.at(sc<T>(0)),NE);
    TEST_EXCEPTION(s1.at(sc<T>(199)),NE);

    CString s2("");
    TEST_ASSERT_EQ(s2.at(sc<T>(0)),'\0');
    TEST_EXCEPTION(s2.at(sc<T>(1)),IE);
    TEST_EXCEPTION(s2.at(sc<T>(2)),IE);
    TEST_EXCEPTION(s2.at(sc<T>(19)),IE);

    CString s3("0123456789");
    TEST_ASSERT_EQ(s3.at(sc<T>(0)),'0');
    TEST_ASSERT_EQ(s3.at(sc<T>(1)),'1');
    TEST_ASSERT_EQ(s3.at(sc<T>(2)),'2');
    TEST_ASSERT_EQ(s3.at(sc<T>(3)),'3');
    TEST_ASSERT_EQ(s3.at(sc<T>(4)),'4');
    TEST_ASSERT_EQ(s3.at(sc<T>(5)),'5');
    TEST_ASSERT_EQ(s3.at(sc<T>(6)),'6');
    TEST_ASSERT_EQ(s3.at(sc<T>(7)),'7');
    TEST_ASSERT_EQ(s3.at(sc<T>(8)),'8');
    TEST_ASSERT_EQ(s3.at(sc<T>(9)),'9');
    TEST_ASSERT_EQ(s3.at(sc<T>(10)),'\0');
    TEST_ASSERT_EQ(&s3.at(sc<T>(7))+1,&s3.at(sc<T>(8)));
    TEST_ASSERT_EQ(&s3.at(sc<T>(2))+2,&s3.at(sc<T>(4)));
    swap(s3.at(sc<T>(0)),s3.at(sc<T>(9)));
    swap(s3.at(sc<T>(1)),s3.at(sc<T>(8)));
    swap(s3.at(sc<T>(2)),s3.at(sc<T>(7)));
    swap(s3.at(sc<T>(3)),s3.at(sc<T>(6)));
    swap(s3.at(sc<T>(4)),s3.at(sc<T>(5)));
    TEST_ASSERT_EQ(s3,"9876543210");
    TEST_EXCEPTION(s3.at(sc<T>(11)),IE);
    TEST_EXCEPTION(s3.at(sc<T>(12)),IE);
    TEST_EXCEPTION(s3.at(sc<T>(139)),IE);
}

TEST_CASE_CREATE(testAtSchar)
{
    testAtSignedImpl<signed char>();
}

TEST_CASE_CREATE(testAtSshort)
{
    testAtSignedImpl<signed short>();
}

TEST_CASE_CREATE(testAtSint)
{
    testAtSignedImpl<signed int>();
}

TEST_CASE_CREATE(testAtSlong)
{
    testAtSignedImpl<signed long>();
}

TEST_CASE_CREATE(testAtSll)
{
    testAtSignedImpl<signed long long>();
}

TEST_CASE_CREATE(testAtUchar)
{
    testAtUnsignedImpl<unsigned char>();
}

TEST_CASE_CREATE(testAtUshort)
{
    testAtUnsignedImpl<unsigned short>();
}

TEST_CASE_CREATE(testAtUint)
{
    testAtUnsignedImpl<unsigned int>();
}

TEST_CASE_CREATE(testAtUlong)
{
    testAtUnsignedImpl<unsigned long>();
}

TEST_CASE_CREATE(testAtUll)
{
    testAtUnsignedImpl<unsigned long long>();
}

TEST_CASE_CREATE(testAtOther)
{
    using NE = tkoz::stl::NullError;
    using IE = tkoz::stl::IndexError;
    using tkoz::stl::swap;

    CString s1;
    TEST_EXCEPTION(s1.at(false),NE);
    TEST_EXCEPTION(s1.at(true),NE);
    TEST_EXCEPTION(s1.at(0),NE);
    TEST_EXCEPTION(s1.at(0u),NE);
    TEST_EXCEPTION(s1.at(0l),NE);
    TEST_EXCEPTION(s1.at(0ul),NE);
    TEST_EXCEPTION(s1.at(0ll),NE);
    TEST_EXCEPTION(s1.at(0ull),NE);

    CString s2("ABCDE");
    TEST_EXCEPTION(s2.at(-6),IE);
    TEST_EXCEPTION(s2.at(6),IE);
    TEST_EXCEPTION(s2.at(150000),IE);
    TEST_EXCEPTION(s2.at(-2500000),IE);
    swap(s2.at(1),s2.at(4));
    TEST_ASSERT_EQ(s2,"AECDB");

    CString *s3 = new CString("Xeon E5-2697Av4");
    TEST_EXCEPTION(s3->at(-50),IE);
    TEST_EXCEPTION(s3->at(16u),IE);
    TEST_EXCEPTION(s3->at(17),IE);
    s3->at(11) = '8';
    s3->at(12) = ' ';
    TEST_ASSERT_EQ(*s3,"Xeon E5-2698 v4");
    delete s3;
}

// TODO debug asserts inside CString.hpp for preconditions and invariants
// precondition checks grouped by fast (<linear), medium(quasilinear), slow(>linear)
// optional and handled with macros, require some symbol and make debug/assert/check headers
