///
/// \file   angle.hpp
/// \brief  度数法と弧度法を表すクラス定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/27
///             - ヘッダ追加
///             - Degrees 定義
///             - Radians 定義
///         - 2020/8/3
///             - 作業用名前を impl から angle_impl へ変更
///
#ifndef INCLUDED_EGEG_MLIB_ANGLE_HEADER_
#define INCLUDED_EGEG_MLIB_ANGLE_HEADER_

#include <corecrt_math_defines.h>
#include <cfloat>

namespace easy_engine {
namespace m_lib {
class Radians;
  namespace angle_impl {
      constexpr bool floatEqual(float, float) noexcept;
  } // namespace impl

/******************************************************************************

    Degrees

******************************************************************************/
class Degrees {
public :
    friend Radians;

    static constexpr float kConvertToDegrees = 180.0F/static_cast<float>(M_PI);

    explicit constexpr Degrees(const float Angle=0.0F) noexcept : angle_{Angle} {}
    constexpr Degrees(const Radians) noexcept;
    Degrees& operator=(const Radians) noexcept;

    constexpr bool operator==(const Degrees D) const noexcept { return angle_impl::floatEqual(angle_, D.angle_); }
    constexpr bool operator!=(const Degrees D) const noexcept { return !(*this==D); }

    constexpr Degrees operator+(const Degrees D) const noexcept { return Degrees{angle_+D.angle_}; }
    constexpr Degrees operator-(const Degrees D) const noexcept { return Degrees{angle_-D.angle_}; }

    Degrees& operator+=(const Degrees D) noexcept { angle_ += D.angle_; return *this; }
    Degrees& operator-=(const Degrees D) noexcept { angle_ -= D.angle_; return *this; }
    Degrees& operator++() noexcept { return *this += Degrees{1.0F}; }
    Degrees operator++(int) noexcept { Degrees temp{*this}; ++*this; return temp; }
    Degrees& operator--() noexcept { return *this -= Degrees{1.0F}; }
    Degrees operator--(int) noexcept { Degrees temp{*this}; --*this; return temp; }

    constexpr operator float() const noexcept { return angle_; }

private :
    float angle_;
};

/******************************************************************************

    Radians

******************************************************************************/
class Radians {
public :
    friend Degrees;

    static constexpr float kConvertToRadians = static_cast<float>(M_PI)/180.0F;

    explicit constexpr Radians(const float Angle=0.0F) noexcept : angle_{Angle} {}
    constexpr Radians(const Degrees Angle) noexcept : angle_{Angle.angle_*kConvertToRadians} {}
    Radians& operator=(const Degrees Angle) noexcept {
        angle_ = Angle.angle_*kConvertToRadians;
        return *this;
    }

    constexpr bool operator==(const Radians R) const noexcept { return angle_impl::floatEqual(angle_, R.angle_); }
    constexpr bool operator!=(const Radians R) const noexcept { return !(*this==R); }

    constexpr Radians operator+(const Radians R) const noexcept { return Radians{angle_+R.angle_}; }
    constexpr Radians operator-(const Radians R) const noexcept { return Radians{angle_-R.angle_}; }

    Radians& operator+=(const Radians R) noexcept { angle_ += R.angle_; return *this; }
    Radians& operator-=(const Radians R) noexcept { angle_ -= R.angle_; return *this; }
    Radians& operator++() noexcept { return *this += Degrees{1.0F}; }
    Radians operator++(int) noexcept { Radians temp{*this}; ++*this; return temp; }
    Radians& operator--() noexcept { return *this -= Degrees{1.0F}; }
    Radians operator--(int) noexcept { Radians temp{*this}; --*this; return temp; }

    constexpr operator float() const noexcept { return angle_; }

private :
    float angle_;
};

inline constexpr Degrees::Degrees(const Radians Angle) noexcept : angle_{Angle.angle_*kConvertToDegrees} {}
inline Degrees& Degrees::operator=(const Radians Angle) noexcept {
    angle_ = Angle.angle_*kConvertToDegrees;
    return *this;
}

  inline constexpr bool angle_impl::floatEqual(float L, float R) noexcept {
      const float diff = (L-R)>0 ? L-R : R-L;
      L = L>0 ? L : -L;
      R = R>0 ? R : -R;

      return diff <= ((L>R) ? L : R) * FLT_EPSILON;
  }
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_ANGLE_HEADER_
// EOF
