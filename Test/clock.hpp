#pragma once

#include <chrono>

template <class ClockImplTy = std::chrono::high_resolution_clock>
class Clock {
public :
    using ClockImplType = ClockImplTy;
    using DurationType = typename ClockImplType::duration;

    class Time {
    public :
        Time() = default;
        Time(DurationType DurationType) : duration_{DurationType} 
        {}

        long long seconds() const noexcept {
            return cast<std::chrono::seconds>().count();
        }
        long long milliseconds() const noexcept {
            return cast<std::chrono::milliseconds>().count();
        }
        long long microseconds() const noexcept {
            return cast<std::chrono::microseconds>().count();
        }
        long long nanoseconds() const noexcept {
            return cast<std::chrono::nanoseconds>().count();
        }

    private :
        template <class DurationTy>
        DurationTy cast() const noexcept {
            return std::chrono::duration_cast<DurationTy>(duration_);
        }
        template <>
        DurationType cast<DurationType>() const noexcept {
            return duration_;
        }
        DurationType duration_;
    };

    Clock() :
        start_{ClockImplType::now()},
        point_{start_},
        delta_{},
        elapsed_{}
    {}

    void update() {
        using namespace std::chrono;
        auto now = ClockImplType::now();
        delta_ = now - point_;
        elapsed_ += delta_;
        point_ = now;
    }

    Time delta() {
        return Time{delta_};
    }

    Time elapsed() {
        return Time{elapsed_};
    }

private :
    typename ClockImplType::time_point start_;
    typename ClockImplType::time_point point_;
    DurationType delta_;
    DurationType elapsed_;
};
