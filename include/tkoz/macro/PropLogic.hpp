///
/// Custom operators implemented with macros
///

#pragma once

// Operator precedence is important to consider. The best that can be done for
// custom operators is probably pick a precedence level and have the operator
// match that level and its associativity.
// (1) LTR a::b
// (2) LTR a() a[] a++ a-- a.b a->b
// (3) RTL ++a --a +a -a !a ~a *a &a
// (4) LTR a.*b a->*b
// (5) LTR a*b a/b a%b
// (6) LTR a+b a-b
// (7) LTR a<<b a>>b
// (8) LTR a<=>b
// (9) LTR a<b a<=b a>b a>=b
// (10) LTR a==b a!=b
// (11) LTR a&b
// (12) LTR a^b
// (13) LTR a|b
// (14) LTR a&&b
// (15) LTR a||b
// (16) RTL a=b a+=b a-=b a*=b a/=b a%=b a<<=b a>>=b a&=b a^=b a|=b
// (17) LTR a,b

namespace tkoz::_macro
{

// iff (if and only if) implementation
// use operator, (left to right associative)
// evaluation order:
// 1: (bool convertible) , _iff_empty , (bool convertible)
// 2: _iff_value , (bool convertible)
// 3: (bool result)
// similar implementation for IF/IMPLIED_BY and THEN/IMPLIES

struct _iff_value
{
    bool _v;
    constexpr inline _iff_value(bool b): _v(b) {}
    template <typename Any>
    constexpr friend inline bool operator,(
        const _iff_value &left, const Any &right)
    {
        return left._v == static_cast<bool>(right);
    }
};

struct _iff_empty
{
    template <typename Any>
    constexpr friend inline _iff_value operator,(
        const Any &left, const _iff_empty &right)
    {
        static_cast<void>(right);
        return _iff_value(static_cast<bool>(left));
    }
};

struct _then_value
{
    bool _v;
    constexpr inline _then_value(bool b): _v(b) {}
    template <typename Any>
    constexpr friend inline bool operator,(
        const _then_value &left, const Any &right)
    {
        return !left._v || static_cast<bool>(right);
    }
};

struct _then_empty
{
    template <typename Any>
    constexpr friend inline _then_value operator,(
        const Any &left, const _then_empty &right)
    {
        static_cast<void>(right);
        return _then_value(static_cast<bool>(left));
    }
};

struct _if_value
{
    bool _v;
    constexpr inline _if_value(bool b): _v(b) {}
    template <typename Any>
    constexpr friend inline bool operator,(
        const _if_value &left, const Any &right)
    {
        return !static_cast<bool>(right) || left._v;
    }
};

struct _if_empty
{
    template <typename Any>
    constexpr friend inline _if_value operator,(
        const Any &left, const _if_empty &right)
    {
        static_cast<void>(right);
        return _if_value(static_cast<bool>(left));
    }
};

} // namespace tkoz::_macro

/// if and only if operator, same precedence as comma
/// intended to be used as: expr1 IF_AND_ONLY_IF expr2
/// true when both operands have the same truth value
#define IF_AND_ONLY_IF , ::tkoz::_macro::_iff_empty() ,

/// short name for IF_AND_ONLY_IF
#define IFF IF_AND_ONLY_IF

/// implies operator, same precedence as comma
/// intended to be used as: expr1 IMPLIES expr2
/// false when left operand is true and right operand is false
#define IMPLIES , ::tkoz::_macro::_then_empty() ,

/// then operator (same as implies)
#define THEN IMPLIES

/// implied by operator, same predence as comma
/// intended to be used as: expr1 IMPLIED_BY expr2
/// false when right operand is true and left operand is false
#define IMPLIED_BY , ::tkoz::_macro::_if_empty() ,

/// if operator (same as implied by)
#define IF IMPLIED_BY
