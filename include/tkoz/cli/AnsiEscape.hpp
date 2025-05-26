///
/// ANSI escape codes for terminal text color and formatting
///

#pragma once

namespace tkoz::cli
{

/// reset to default style
static const constexpr char cReset[]            = "\033[0m";

/// bold text
static const constexpr char cBold[]             = "\033[1m";

/// faint text
static const constexpr char cFaint[]            = "\033[2m";

/// italic text
static const constexpr char cItalic[]           = "\033[3m";

/// underline
static const constexpr char cUnderlineSingle[] = "\033[4m";

/// slow blinking
static const constexpr char cBlinkSlow[]       = "\033[5m";

/// fast blinking
static const constexpr char cBlinkFast[]       = "\033[6m";

/// switch foreground and background color
static const constexpr char cInvertOn[]        = "\033[7m";

/// hide text
static const constexpr char cHideOn[]          = "\033[8m";

/// cross/strikethrough text
static const constexpr char cCrossOn[]         = "\033[9m";

/// \brief font type font type (0-9)
///
/// this was not supported in the testing environment
template <int N> requires (N >= 0) && (N < 10)
static const constexpr char cFont[] = {'\033','[','1',
    static_cast<char>('0'+N),'m','\x00'};

/// double underline
static const constexpr char cUnderlineDouble[] = "\033[21m";

/// set intensity back to normal
static const constexpr char cNormalIntensity[] = "\033[22m";

/// set style back to normal
static const constexpr char cNormalStyle[]     = "\033[23m";

/// remove underlining
static const constexpr char cUnderlineOff[]    = "\033[24m";

/// remove blinking
static const constexpr char cBlinkOff[]        = "\033[25m";

/// remove inversion of foreground and background colors
static const constexpr char cInvertOff[]       = "\033[27m";

/// show text
static const constexpr char cHideOff[]         = "\033[28m";

/// remove cross/strikethrough
static const constexpr char cCrossOff[]        = "\033[29m";

//
// basic colors (for both foreground and background)
// 3 bit (8) are non bright
// 4 bit (16) include the bright ones, prefixed with a B
//

/// foreground color black
static const constexpr char cFgBlack[]   = "\033[30m";

/// foreground color red
static const constexpr char cFgRed[]     = "\033[31m";

/// foreground color green
static const constexpr char cFgGreen[]   = "\033[32m";

/// foreground color yellow
static const constexpr char cFgYellow[]  = "\033[33m";

/// foreground color blue
static const constexpr char cFgBlue[]    = "\033[34m";

/// foreground color magenta
static const constexpr char cFgMagenta[] = "\033[35m";

/// foreground color cyan
static const constexpr char cFgCyan[]    = "\033[36m";

/// foreground color white
static const constexpr char cFgWhite[]   = "\033[37m";

/// background color black
static const constexpr char cBgBlack[]   = "\033[40m";

/// background color red
static const constexpr char cBgRed[]     = "\033[41m";

/// background color green
static const constexpr char cBgGreen[]   = "\033[42m";

/// background color yellow
static const constexpr char cBgYellow[]  = "\033[43m";

/// background color blue
static const constexpr char cBgBlue[]    = "\033[44m";

/// background color magenta
static const constexpr char cBgMagenta[] = "\033[45m";

/// background color cyan
static const constexpr char cBgCyan[]    = "\033[46m";

/// background color white
static const constexpr char cBgWhite[]   = "\033[47m";

/// foreground color bright black
static const constexpr char cFgBBlack[]   = "\033[90m";

/// foreground color bright red
static const constexpr char cFgBRed[]     = "\033[91m";

/// foreground color bright green
static const constexpr char cFgBGreen[]   = "\033[92m";

/// foreground color bright yellow
static const constexpr char cFgBYellow[]  = "\033[93m";

/// foreground color bright blue
static const constexpr char cFgBBlue[]    = "\033[94m";

/// foreground color bright magenta
static const constexpr char cFgBMagenta[] = "\033[95m";

/// foreground color bright cyan
static const constexpr char cFgBCyan[]    = "\033[96m";

/// foreground color bright white
static const constexpr char cFgBWhite[]   = "\033[97m";

/// background color bright black
static const constexpr char cBgBBlack[]   = "\033[100m";

/// background color bright red
static const constexpr char cBgBRed[]     = "\033[101m";

/// background color bright green
static const constexpr char cBgBGreen[]   = "\033[102m";

/// background color bright yellow
static const constexpr char cBgBYellow[]  = "\033[103m";

/// background color bright blue
static const constexpr char cBgBBlue[]    = "\033[104m";

/// background color bright magenta
static const constexpr char cBgBMagenta[] = "\033[105m";

/// background color bright cyan
static const constexpr char cBgBCyan[]    = "\033[106m";

/// background color bright white
static const constexpr char cBgBWhite[]   = "\033[107m";

namespace _detail
{

// compile time string as parameter pack
template <char ...chars>
struct _MetaStr
{
    static const constexpr char value[] = {chars...,0};
};

// join _MetaStrs by concatenating parameter packs to a new _MetaStr
template <typename ...Strs>
struct _MetaStrJoinImpl
{
    using type = _MetaStr<>;
};

template <char ...chars>
struct _MetaStrJoinImpl<_MetaStr<chars...>>
{
    using type = _MetaStr<chars...>;
};

template <char ...chars1, char ...chars2, typename ...Strs>
struct _MetaStrJoinImpl<_MetaStr<chars1...>,_MetaStr<chars2...>,Strs...>
{
    using type = _MetaStrJoinImpl<_MetaStr<chars1...,chars2...>,Strs...>::type;
};

// interface for joining _MetaStrs
template <typename ...Strs>
struct _MetaStrJoin
{
    // _MetaStr type with joined parameter pack
    using type = _MetaStrJoinImpl<Strs...>::type;
    // string constant value
    static const constexpr auto value = type::value;
};

// convert int to _MetaStr
template <int N, bool S, typename T>
struct _IntToMetaStrImpl;

template <int N, bool S, char ...chars> requires (N > 0)
struct _IntToMetaStrImpl<N,S,_MetaStr<chars...>>
{
    using type = _IntToMetaStrImpl<N/10,false,
        _MetaStr<static_cast<char>('0'+(N%10)),chars...>>::type;
};

template <char ...chars>
struct _IntToMetaStrImpl<0,true,_MetaStr<chars...>>
{
    using type = _MetaStr<'0'>;
};

template <char ...chars>
struct _IntToMetaStrImpl<0,false,_MetaStr<chars...>>
{
    using type = _MetaStr<chars...>;
};

// interface to convert int to _MetaStr
template <int N>
using _IntAsMetaStr = _IntToMetaStrImpl<N,true,_MetaStr<>>::type;

} // namespace _detail

/// \brief 8 bit foreground color
///
/// - 0-7 standard colors
/// - 8-15 bright colors
/// - 16-231 RGB cube
/// - 232-255 grayscale
/// - RGB cube is 16 + 36*R + 6*G + B where 0 <= R,G,B < 6
/// - grayscale is 232(black) to 255(white)
template <int N> requires (N >= 0) && (N < 256)
static const constexpr auto cFgColor8 = _detail::_MetaStrJoin<
    _detail::_MetaStr<'\033','[','3','8',';','5',';'>,
    _detail::_IntAsMetaStr<N>,_detail::_MetaStr<'m'>>::value;

/// 8 bit foreground gray color: 0(black) to 15(white)
template <int N> requires (N >= 0) && (N < 16)
static const constexpr auto cFgGray8 = cFgColor8<232+N>;

/// 8 bit foreground RGB color: 0 <= R,G,B < 6
template <int R, int G, int B>
requires (R >= 0) && (G >= 0) && (B >= 0) && (R < 6) && (G < 6) && (B < 6)
static const constexpr auto cFgRgb8 = cFgColor8<16+36*R+6*G+B>;

/// \brief 8 bit background color
///
/// - 0-7 standard colors
/// - 8-15 bright colors
/// - 16-231 RGB cube
/// - 232-255 grayscale
/// - RGB cube is 16 + 36*R + 6*G + B where 0 <= R,G,B < 6
/// - grayscale is 232(black) to 255(white)
template <int N> requires (N >= 0) && (N < 256)
static const constexpr auto cBgColor8 = _detail::_MetaStrJoin<
    _detail::_MetaStr<'\033','[','4','8',';','5',';'>,
    _detail::_IntAsMetaStr<N>,_detail::_MetaStr<'m'>>::value;

/// 8 bit background gray color: 0(black) to 15(white)
template <int N> requires (N >= 0) && (N < 16)
static const constexpr auto cBgGray8 = cBgColor8<232+N>;

/// 8 bit background RGB color: 0 <= R,G,B < 6
template <int R, int G, int B>
requires (R >= 0) && (G >= 0) && (B >= 0) && (R < 6) && (G < 6) && (B < 6)
static const constexpr auto cBgRgb8 = cBgColor8<16+36*R+6*G+B>;

/// 24 bit foreground color (0 <= R,G,B < 256)
template <int R, int G, int B>
requires (R >= 0) && (G >= 0) && (B >= 0)
      && (R < 256) && (G < 256) && (B < 256)
static const constexpr auto cFgColor24 = _detail::_MetaStrJoin<
    _detail::_MetaStr<'\033','[','3','8',';','2',';'>,
    _detail::_IntAsMetaStr<R>,_detail::_MetaStr<';'>,
    _detail::_IntAsMetaStr<G>,_detail::_MetaStr<';'>,
    _detail::_IntAsMetaStr<B>,_detail::_MetaStr<'m'>>::value;

/// 24 bit background color (0 <= R,G,B < 256)
template <int R, int G, int B>
requires (R >= 0) && (G >= 0) && (B >= 0)
      && (R < 256) && (G < 256) && (B < 256)
static const constexpr auto cBgColor24 = _detail::_MetaStrJoin<
    _detail::_MetaStr<'\033','[','4','8',';','2',';'>,
    _detail::_IntAsMetaStr<R>,_detail::_MetaStr<';'>,
    _detail::_IntAsMetaStr<G>,_detail::_MetaStr<';'>,
    _detail::_IntAsMetaStr<B>,_detail::_MetaStr<'m'>>::value;

//
// cursor, scrolling, and clearing
//

namespace _detail
{

template <int N, char C>
static const constexpr auto _EscHelper = _MetaStrJoin<
    _MetaStr<'\033','['>,_IntAsMetaStr<N>,_MetaStr<C>>::value;

} // namespace _detail

/// move cursor to position
template <int R, int C> requires (R >= 0) && (C >= 0)
static const constexpr auto cCursorMoveTo = _detail::_MetaStrJoin<
    _detail::_MetaStr<'\033','['>,_detail::_IntAsMetaStr<R>,
    _detail::_MetaStr<';'>,
    _detail::_IntAsMetaStr<C>,_detail::_MetaStr<'H'>>::value;

/// move cursor up
template <int N> requires (N >= 0)
static const constexpr auto cCursorMoveUp = _detail::_EscHelper<N,'A'>;

/// move cursor down
template <int N> requires (N >= 0)
static const constexpr auto cCursorMoveDown = _detail::_EscHelper<N,'B'>;

/// move cursor right
template <int N> requires (N >= 0)
static const constexpr auto cCursorMoveRight = _detail::_EscHelper<N,'C'>;

/// move cursor up
template <int N> requires (N >= 0)
static const constexpr auto cCursorMoveLeft = _detail::_EscHelper<N,'D'>;

/// scroll up
template <int N> requires (N > 0)
static const constexpr auto cScrollUp = _detail::_EscHelper<N,'S'>;

/// scroll down
template <int N> requires (N > 0)
static const constexpr auto cScrollDown = _detail::_EscHelper<N,'T'>;

/// clear screen to the ending
static const constexpr char cClearScreenEnd[] = "\033[0J";

/// clear screen to the beginning
static const constexpr char cClearScreenBeg[] = "\033[1J";

/// clear whole screen
static const constexpr char cClearScreenAll[] = "\033[2J";

/// clear screen buffer
static const constexpr char cClearScreenBuf[] = "\033[3J";

/// clear line to the ending
static const constexpr char cClearLineEnd[]   = "\033[0K";

/// clear line to the beginning
static const constexpr char cClearLindeBeg[]   = "\033[1K";

/// clear whole line
static const constexpr char cClearLineAll[]   = "\033[2K";

} // namespace tkoz::cli
