///
/// \file   time.hpp
/// \brief  ���Ԋ֌W�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/20
///             - �w�b�_�ǉ�
///             - Time ��`
///             - Clock ��`
///
#ifndef INCLUDED_EGEG_TIME_HEADER_
#define INCLUDED_EGEG_TIME_HEADER_

#include <chrono>

namespace easy_engine {

using ClockUsed = std::chrono::high_resolution_clock; ///< �g�p���Ă��鎞�Ԍv���p�N���X
using Nanoseconds  = std::chrono::nanoseconds;  ///< ���ԒP�ʁu�i�m�b(1/1000�}�C�N���b)�v
using Microseconds = std::chrono::microseconds; ///< ���ԒP�ʁu�}�C�N���b(1/1000�~���b)�v
using Milliseconds = std::chrono::milliseconds; ///< ���ԒP�ʁu�~���b(1/1000�b)�v
using Seconds      = std::chrono::seconds;      ///< ���ԒP�ʁu�b�v
using Minutes      = std::chrono::minutes;      ///< ���ԒP�ʁu���v
using Hours        = std::chrono::hours;        ///< ���ԒP�ʁu���v

/******************************************************************************

    Time

******************************************************************************/
///
/// \class  Time
/// \brief  ���ԕێ��p�R���e�i
///
///         �������ɂ́A��L���ԒP�ʃN���X��p���܂��B
///         ��.) Time time = Seconds{10}; // time ��10�b���Z�b�g
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
/// \class  Clock
/// \brief  ���Ԍv���N���X
///
///         ��ɍŐV�̎��Ԃ�����N���X�ł͂���܂���B
///         update()���ЂƂ̋�؂�Ƃ��Ă��܂��B
///
class Clock {
public :
    ///
    /// \brief  �R���X�g���N�^
    ///
    ///         ���Ԍv�����J�n���܂��B
    ///
    Clock() noexcept :
        start_{ClockUsed::now()},
        last_point_{start_},
        delta_{},
        elapsed_{} {}

    ///
    /// \brief  �X�V
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
    /// \brief  ���߂̍X�V�ƁA���̂ЂƂO�̍X�V�Ƃ̎��ԍ�
    ///
    Time delta() const noexcept {
        return Time{delta_};
    }

    ///
    /// \brief  �v���J�n����A���߂̍X�V�܂ł̌o�ߎ���
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
