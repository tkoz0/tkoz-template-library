#include <cassert>
#include <iostream>
using std::cout, std::endl;

#include "../../src/util/vtuple.hpp"
using tkoz::vtuple, tkoz::make_vtuple, tkoz::concat_vtuple;

template <typename ...Ts>
std::ostream &print_comma_sep(std::ostream &os, const vtuple<Ts...>&) { return os; }

template <typename T>
std::ostream &print_comma_sep(std::ostream &os, const vtuple<T> &t)
{
    os << t.template get<0>();
    return os;
}

template <typename T1, typename T2, typename ...Ts>
std::ostream &print_comma_sep(std::ostream &os, const vtuple<T1,T2,Ts...> &t)
{
    os << t.template get<0>() << ",";
    print_comma_sep(os,t.vs);
    return os;
}

template <typename ...Ts>
std::ostream &operator<<(std::ostream &os, const vtuple<Ts...> &t)
{
    os << "(";
    print_comma_sep(os,t);
    os << ")";
    return os;
}

int main()
{
    typedef vtuple<bool,int,double> type1;
    static_assert(std::is_same_v<type1,decltype(make_vtuple(false,0,0.0))>);
    static_assert(std::is_same_v<bool,decltype(type1::v)>);
    static_assert(std::is_same_v<vtuple<int,double>,decltype(type1::vs)>);
    static_assert(std::is_same_v<bool,type1::type<0>>);
    static_assert(std::is_same_v<int,type1::type<1>>);
    static_assert(std::is_same_v<double,type1::type<2>>);
    typedef vtuple<double,int,bool> type2;
    type1 t1,t2;
    assert(t1.get<0>() == false);
    assert(t1.get<1>() == 0);
    assert(t1.get<2>() == 0.0);
    t1 = {true,5,10.0};
    assert(t1.get<0>() == true);
    assert(t1.get<1>() == 5);
    assert(t1.get<2>() == 10.0);
    assert(bool(t1));
    assert(t1 == make_vtuple(true,make_vtuple(5,10.0)));
    assert(t1 == make_vtuple(true,make_vtuple(5,make_vtuple(10.0))));
    assert(t1 != type1());
    t2 = t1;
    assert(t1 == t2);
    t2.set<0>(false);
    t2.set<1>(0);
    t2.set<2>(0.0);
    assert(t2 == type1());
    assert(!t2);
    assert(type1(false,0,0.0) < type1(false,0,1.0));
    assert(type1() <= type1());
    type2 t3;
    t1 = {true,5,10.0};
    t3 = {10.0,5,true};
    assert(concat_vtuple(t1,t3) == make_vtuple(true,5,10.0,10.0,5,true));
    auto [t1x,t1y,t1z] = t1;
    static_assert(std::is_same_v<decltype(t1x),bool>);
    static_assert(std::is_same_v<decltype(t1y),int>);
    static_assert(std::is_same_v<decltype(t1z),double>);
    assert(t1x == true);
    assert(t1y == 5);
    assert(t1z == 10.0);
    vtuple<int,int,int,int> t4(1,2,3,4);
    --t4;
    assert(t4 == (vtuple<int,int,int,int>{0,1,2,3}));
    ++t4;
    assert(t4 == (vtuple<int,int,int,int>{1,2,3,4}));
    t4 *= vtuple<int,int,int,int>{5,6,7,8};
    assert(t4 == (vtuple<int,int,int,int>{5,12,21,32}));
    t4 >>= vtuple<int,int,int,int>{1,1,1,1};
    assert(t4 == make_vtuple(2,6,10,16));
    assert(-t4 == make_vtuple(-2,-6,-10,-16));
    return 0;
}
