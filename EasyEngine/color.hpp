///
/// \file   color.hpp
/// \brief  �F�Ɋւ���錾�A��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/4
///             - �w�b�_�ǉ�
///             - ColorMask ��`
///                 - �萔��`
///             - ColorBitMask ��`
///                 - �萔��`
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
/// \brief  �J���[�}�X�N
///
///         �F����F256�i�K(0~255)�ŕ\�����܂��B
///         ��e���v���[�g�p�����[�^�ŗL���ȐF��RGBA�ʂɎw�肵�܂��B
///
/// \tparam Red   : �ԐF(0:�����@��0:�L��)
/// \tparam Green : �ΐF(0:�����@��0:�L��)
/// \tparam Blue  : �F(0:�����@��0:�L��)
/// \tparam Alpha : ����(0:�����@��0:�L��)
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
/// \brief  ColorUint�f�R�[�_�[
///
///         RGBA��\��ColorUint�̊g���łł��B
///         �e�֐��𗘗p���Ċe�F�̒l���擾�ł��܂��B
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
/// \brief  �J���[�r�b�g�}�X�N
///
///         �F�𒼐ڕ\�����܂���B
///         ��e���v���[�g�p�����[�^�ŗL���ȐF��RGBA�ʂɎw�肵�܂��B
///
/// \tparam Red   : �ԐF(0:�����@��0:�L��)
/// \tparam Green : �ΐF(0:�����@��0:�L��)
/// \tparam Blue  : �F(0:�����@��0:�L��)
/// \tparam Alpha : ����(0:�����@��0:�L��)
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
