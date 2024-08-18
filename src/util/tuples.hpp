/*
Convenient tuples for more sizes than STL provides.
TODO add the rest up to tuple sizes of 26
TODO specialize std::get
TODO specialize std::hash
TODO specialize std::less
TODO specialize some operators
TODO put STL specializations in /src/stl/
*/

#pragma once

namespace tkoz
{

template <typename T1, typename T2 = T1>
struct tuple2 { T1 a; T2 b; };

template <typename T1, typename T2 = T1, typename T3 = T2>
struct tuple3 { T1 a; T2 b; T3 c; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3>
struct tuple4 { T1 a; T2 b; T3 c; T4 d; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4>
struct tuple5 { T1 a; T2 b; T3 c; T4 d; T5 e; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5>
struct tuple6 { T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6>
struct tuple7 { T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7>
struct tuple8 { T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; };

template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 = T3, typename T5 = T4, typename T6 = T5, typename T7 = T6, typename T8 = T7, typename T9 = T8>
struct tuple9 { T1 a; T2 b; T3 c; T4 d; T5 e; T6 f; T7 g; T8 h; T9 i; };

}
