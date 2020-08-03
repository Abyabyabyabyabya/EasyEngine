#ifndef INCLUDED_TEST_OPERATION_HPP
#define INCLUDED_TEST_OPERATION_HPP

#include "mvector.hpp"

template <size_t Index>
struct arr_add {
    template <size_t N1, size_t N2>
    inline void operator()(float(&A1)[N1], const float(&A2)[N2]) const noexcept { 
        static_assert( (N1>=Index) && (N2>=Index), "err" );
        A1[Index-1] += A2[Index-1];
        arr_add<Index-1>{}(A1, A2);
    }
};

template <>
struct arr_add<0> {
    template <size_t N1, size_t N2>
    inline void operator()(float(&)[N1], const float(&)[N2]) const noexcept {};
};


template <class LTy, class RTy>
class Vec4Add {
public :
    constexpr Vec4Add(const LTy& L, const RTy& R) noexcept : l{L}, r{R} {}
    constexpr float operator[](size_t I) const {
        return l[I]+r[I];
    }
private :
    const LTy& l;
    const RTy& r;
};

constexpr int digit(long long Value, uint32_t Digit) {
    return Digit>>1 ? digit(Value/10, Digit>>1) : Value%10;
}
#endif // INCLUDED_TEST_OPERATION_HPP
