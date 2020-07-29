#pragma once

#include "mvector.hpp"

template <size_t Index>
struct arr_add {
    template <size_t N1, size_t N2>
    void operator()(float(&A1)[N1], const float(&A2)[N2]) const noexcept { 
        static_assert( (N1>=Index) && (N2>=Index), "err" );
        A1[Index-1] += A2[Index-1];
        arr_add<Index-1>{}(A1, A2);
    }
};

template <>
struct arr_add<0> {
    template <size_t N1, size_t N2>
    void operator()(float(&)[N1], const float(&)[N2]) const noexcept {};
};

constexpr int digit(long long Value, uint32_t Digit) {
    return Digit>>1 ? digit(Value/10, Digit>>1) : Value%10;
}
