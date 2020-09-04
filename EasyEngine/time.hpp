///
/// \file   time.hpp
/// \brief  時間関係クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/20
///             - ヘッダ追加
///             - Time 定義
///             - Clock 定義
///
#ifndef INCLUDED_EGEG_TIME_HEADER_
#define INCLUDED_EGEG_TIME_HEADER_

#include <chrono>

namespace easy_engine {

using ClockUsed = std::chrono::high_resolution_clock; ///< 使用している時間計測用クラス
using Nanoseconds  = std::chrono::nanoseconds;  ///< 時間単位「ナノ秒(1/1000マイクロ秒)」
using Microseconds = std::chrono::microseconds; ///< 時間単位「マイクロ秒(1/1000ミリ秒)」
using Milliseconds = std::chrono::milliseconds; ///< 時間単位「ミリ秒(1/1000秒)」
using Seconds      = std::chrono::seconds;      ///< 時間単位「秒」
using Minutes      = std::chrono::minutes;      ///< 時間単位「分」
using Hours        = std::chrono::hours;        ///< 時間単位「時」

/******************************************************************************

    Time

******************************************************************************/
///
/// \brief  時間保持用コンテナ
///
///         初期化には、上記時間単位クラスを用います。
///         例.) Time time = Seconds{10}; // time に10秒をセット
///
class Time {
public :
    using RepType = ClockUsed::rep;
    using Duration = ClockUsed::duration;

    constexpr Time() = default;
    constexpr Time(const Duration& Right) noexcept : time_{Right} {}
    template <class RepTy, class PeriodTy>
    constexpr Time(const std::chrono::duration<RepTy, PeriodTy>& Right) noexcept :
        time_{std::chrono::duration_cast<Duration>(Right)} {}
    Time& operator=(const Duration& Right) noexcept {
        time_ = Right;
        return *this;
    }
    template <class RepTy, class PeriodTy>
    Time& operator=(const std::chrono::duration<RepTy, PeriodTy>& Right) noexcept {
        time_ = std::chrono::duration_cast<Duration>(Right);
        return *this;
    }

    RepType nanoseconds() const noexcept(noexcept(Nanoseconds{}.count())) {
        return cast<Nanoseconds>().count();
    }
    RepType microseconds() const noexcept(noexcept(Microseconds{}.count())) {
        return cast<Microseconds>().count();
    }
    RepType milliseconds() const noexcept(noexcept(Milliseconds{}.count())) {
        return cast<Milliseconds>().count();
    }
    RepType seconds() const noexcept(noexcept(Seconds{}.count())) {
        return cast<Seconds>().count();
    }
    RepType minutes() const noexcept(noexcept(Minutes{}.count())) {
        return cast<Minutes>().count();
    }
    RepType hours() const noexcept(noexcept(Hours{}.count())) {
        return cast<Hours>().count();
    }

    Time& operator+=(const Time& Right) noexcept(noexcept(time_+=time_)) {
        time_ += Right.time_;
        return *this;
    }
    Time& operator-=(const Time& Right) noexcept(noexcept(time_-=time_)) {
        time_ -= Right.time_;
        return *this;
    }
    Time& operator*=(const RepType Right) noexcept(noexcept(time_*=RepType{})) {
        time_ *= Right;
        return *this;
    }
    Time& operator/=(const RepType Right) noexcept(noexcept(time_/=RepType{})) {
        time_ /= Right;
        return *this;
    }
    Time& operator%=(const RepType Right) noexcept(noexcept(time_%=RepType{})) {
        time_ %= Right;
        return *this;
    }
    Time& operator%=(const Time& Right) noexcept(noexcept(time_%=RepType{})) {
        time_ %= Right.time_;
        return *this;
    }

private :
    template <class DurationTy>
    DurationTy cast() const noexcept {
        return std::chrono::duration_cast<DurationTy>(time_);
    }
    template <>
    Duration cast<Duration>() const noexcept {
        return time_;
    }

    Duration time_{};

public :
  // arithmethic
    friend constexpr Time operator+(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_+Right.time_));
    friend constexpr Time operator-(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_-Right.time_));
    friend constexpr Time operator*(const Time& Left, RepType Right) noexcept(noexcept(Left.time_*Right));
    friend constexpr Time operator/(const Time& Left, RepType Right) noexcept(noexcept(Left.time_/Right));
    friend constexpr Time operator%(const Time& Left, RepType Right) noexcept(noexcept(Left.time_%Right));
  // comparisons
    friend constexpr bool operator==(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_==Right.time_));
    friend constexpr bool operator!=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_==Right.time_));
    friend constexpr bool operator<(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_<Right.time_));
    friend constexpr bool operator<=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_<=Right.time_));
    friend constexpr bool operator>(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_>Right.time_));
    friend constexpr bool operator>=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_>=Right.time_));
};

/******************************************************************************

    Clock

******************************************************************************/
///
/// \brief  時間計測クラス
///
///         常に最新の時間を見るクラスではありません。
///         update()をひとつの区切りとしています。
///
class Clock {
public :
    ///
    /// \brief  コンストラクタ
    ///
    ///         時間計測を開始します。
    ///
    Clock() noexcept :
        start_{ClockUsed::now()},
        last_point_{start_},
        delta_{},
        elapsed_{} {}

    ///
    /// \brief  更新
    ///
    void update() noexcept(
      noexcept(delta_=ClockUsed::now()-last_point_)&&
      noexcept(elapsed_+=delta_)&&
      noexcept(last_point_=ClockUsed::now())) {
        auto now = ClockUsed::now();
        delta_ = now - last_point_;
        elapsed_ += delta_;
        last_point_ = now;
    }

    ///
    /// \brief  計測開始時間
    ///
    ClockUsed::time_point started() const noexcept {
        return start_;
    }

    ///
    /// \brief  直近の更新と、そのひとつ前の更新との時間差
    ///
    Time delta() const noexcept {
        return Time{delta_};
    }

    ///
    /// \brief  計測開始から、直近の更新までの経過時間
    ///
    Time elapsed() const noexcept {
        return Time{elapsed_};
    }

private :
    typename ClockUsed::time_point start_;
    typename ClockUsed::time_point last_point_;
    typename ClockUsed::duration delta_;
    typename ClockUsed::duration elapsed_;
};

/******************************************************************************

    Time Arithmetic

******************************************************************************/
inline constexpr Time operator+(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_+Right.time_)) {
    return Time{Left.time_ + Right.time_};
}

inline constexpr Time operator-(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_-Right.time_)) {
    return Time{Left.time_ - Right.time_};
}

inline constexpr Time operator*(const Time& Left, const typename Time::RepType Right) noexcept(
  noexcept(Left.time_*Right)) {
    return Time{Left.time_ * Right};
}

inline constexpr Time operator/(const Time& Left, const typename Time::RepType Right) noexcept(
  noexcept(Left.time_/Right)) {
    return Time{Left.time_ / Right};
}

inline constexpr Time operator%(const Time& Left, const typename Time::RepType Right) noexcept(
  noexcept(Left.time_%Right)) {
    return Time{Left.time_ % Right};
}

/******************************************************************************

    Time Comparisons

******************************************************************************/
inline constexpr bool operator==(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_==Right.time_)) {
    return Left.time_ == Right.time_;
}

inline constexpr bool operator!=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_!=Right.time_)) {
    return Left.time_ != Right.time_;
}

inline constexpr bool operator<(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_<Right.time_)) {
    return Left.time_ < Right.time_;
}

inline constexpr bool operator<=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_<=Right.time_)) {
    return Left.time_ <= Right.time_;
}

inline constexpr bool operator>(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_>Right.time_)) {
    return Left.time_ > Right.time_;
}

inline constexpr bool operator>=(const Time& Left, const Time& Right) noexcept(noexcept(Left.time_>=Right.time_)) {
    return Left.time_ >= Right.time_;
}

} // namespace easy_engine
#endif // !INCLUDED_EGEG_TIME_HEADER_
// EOF
