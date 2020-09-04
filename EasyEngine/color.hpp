///
/// \file   color.hpp
/// \brief  色に関する宣言、定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/4
///             - ヘッダ追加
///             - ColorMask 定義
///                 - 定数定義
///             - ColorBitMask 定義
///                 - 定数定義
///
#ifndef INCLUDED_EGEG_GLIB_COLOR_HEADER_
#define INCLUDED_EGEG_GLIB_COLOR_HEADER_

#include <cstdint>

namespace easy_engine {
namespace g_lib {

using ColorFlag = std::uint8_t;
using ColorUint = std::uint32_t;


/******************************************************************************

    ColorMask

******************************************************************************/
///
/// \brief  カラーマスク
///
///         色を一色256段階(0~255)で表現します。
///         非テンプレートパラメータで有効な色をRGBA別に指定します。
///
/// \tparam Red   : 赤色(0:無効　非0:有効)
/// \tparam Green : 緑色(0:無効　非0:有効)
/// \tparam Blue  : 青色(0:無効　非0:有効)
/// \tparam Alpha : 透過(0:無効　非0:有効)
///
template <unsigned Red, unsigned Green, unsigned Blue, unsigned Alpha>
class ColorMask {
    static constexpr std::uint8_t state(const unsigned Flag) noexcept { return Flag ? 0xff : 0; }
public :
    static constexpr ColorFlag kMaskRed   = state(Red);
    static constexpr ColorFlag kMaskGreen = state(Green);
    static constexpr ColorFlag kMaskBlue  = state(Blue);
    static constexpr ColorFlag kMaskAlpha = state(Alpha);
    static constexpr ColorUint kMask = (kMaskRed)|(kMaskGreen<<8)|(kMaskBlue<<16)|(kMaskAlpha<<24);
};

template <unsigned Red, unsigned Green, unsigned Blue, unsigned Alpha>
constexpr ColorUint kColorMask = ColorMask<Red, Green, Blue, Alpha>::kMask;
constexpr ColorUint kMaskRed   = kColorMask<1,0,0,0>;
constexpr ColorUint kMaskGreen = kColorMask<0,1,0,0>;
constexpr ColorUint kMaskBlue  = kColorMask<0,0,1,0>;
constexpr ColorUint kMaskAlpha = kColorMask<0,0,0,1>;
constexpr ColorUint kMaskRGBA  = kColorMask<1,1,1,1>;


/******************************************************************************

    Color

******************************************************************************/
///
/// \brief  ColorUintデコーダー
///
///         RGBAを表すColorUintの拡張版です。
///         各関数を利用して各色の値を取得できます。
///
class Color {
public :
    constexpr Color(const ColorUint RGBA) noexcept : color_{RGBA} {}
    constexpr ColorUint rgba() const noexcept { return color_; }
    constexpr ColorFlag red() const noexcept   { return (rgba()&ColorMask<1,0,0,0>::kMask); }
    constexpr ColorFlag green() const noexcept { return (rgba()&ColorMask<0,1,0,0>::kMask)>>8; }
    constexpr ColorFlag blue() const noexcept  { return (rgba()&ColorMask<0,0,1,0>::kMask)>>16; }
    constexpr ColorFlag alpha() const noexcept { return (rgba()&ColorMask<0,0,0,1>::kMask)>>24; }
private :
    ColorUint color_;
};

constexpr Color kRed   = Color{0xff000000};
constexpr Color kGreen = Color{0x00ff0000};
constexpr Color kBlue  = Color{0x0000ff00};
constexpr Color kWhite = Color{0xffffffff};
constexpr Color kBlack = Color{0x000000ff};


/******************************************************************************

    ColorBitMask

******************************************************************************/
///
/// \brief  カラービットマスク
///
///         色を直接表現しません。
///         非テンプレートパラメータで有効な色をRGBA別に指定します。
///
/// \tparam Red   : 赤色(0:無効　非0:有効)
/// \tparam Green : 緑色(0:無効　非0:有効)
/// \tparam Blue  : 青色(0:無効　非0:有効)
/// \tparam Alpha : 透過(0:無効　非0:有効)
///
template <unsigned Red, unsigned Green, unsigned Blue, unsigned Alpha>
class ColorBitMask {
    static constexpr ColorFlag state(const unsigned Flag) noexcept { return Flag ? 1U:0U; }
public :
    static constexpr ColorFlag kMaskRed   = state(Red);
    static constexpr ColorFlag kMaskGreen = state(Green);
    static constexpr ColorFlag kMaskBlue  = state(Blue);
    static constexpr ColorFlag kMaskAlpha = state(Alpha);
    static constexpr ColorFlag kMask = (kMaskRed)|(kMaskGreen<<1)|(kMaskBlue<<2)|(kMaskAlpha<<3);
};

template <unsigned Red, unsigned Green, unsigned Blue, unsigned Alpha>
constexpr ColorFlag kColorBitMask = ColorBitMask<Red, Green, Blue, Alpha>::kMask;
constexpr ColorFlag kBitMaskRed   = kColorBitMask<1,0,0,0>;
constexpr ColorFlag kBitMaskGreen = kColorBitMask<0,1,0,0>;
constexpr ColorFlag kBitMaskBlue  = kColorBitMask<0,0,1,0>;
constexpr ColorFlag kBitMaskAlpha = kColorBitMask<0,0,0,1>;
constexpr ColorFlag kBitMaskRGBA  = kColorBitMask<1,1,1,1>;

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_COLOR_HEADER_
// EOF
