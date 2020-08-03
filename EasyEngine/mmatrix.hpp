///
/// \file   mmatrix.hpp
/// \brief  行列構造体定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/8/3
///             - ヘッダ追加
///             - 行列構造体移行
///
#ifndef INCLUDED_EGEG_MLIB_MMATRIX_HEADER_
#define INCLUDED_EGEG_MLIB_MMATRIX_HEADER_

#include "mvector.hpp"

namespace easy_engine {
namespace m_lib {

/******************************************************************************

    Matrix3x3

******************************************************************************/
struct Matrix3x3 {
    union {
        struct {
            float _00, _01, _02;
            float _10, _11, _12;
            float _20, _21, _22;
        };
        float m[3][3];
        Vector3D row[3];
    };

    static constexpr size_t kRowDimension = 3;
    static constexpr size_t kColumnDimension = 3;
    Matrix3x3() = default;
    Matrix3x3(const Matrix3x3&) = default;
    Matrix3x3& operator=(const Matrix3x3&) = default;
    Matrix3x3(Matrix3x3&&) = default;
    Matrix3x3& operator=(Matrix3x3&&) = default;

    constexpr Matrix3x3(float _00, float _01, float _02, 
                        float _10, float _11, float _12,
                        float _20, float _21, float _22) noexcept;
    constexpr Matrix3x3(const float (&Mat)[9]) noexcept;
    constexpr Matrix3x3(const float (&Mat)[3][3]) noexcept;

    Vector3D& operator[](size_t Index);
    const Vector3D& operator[](size_t Index) const;
    Matrix3x3& operator+=(const Matrix3x3&) noexcept;
    Matrix3x3& operator-=(const Matrix3x3&) noexcept;
    Matrix3x3& operator*=(float) noexcept;
    Matrix3x3& operator/=(float) noexcept;
};
using Matrix3x3A = 
#ifdef _MSC_VER
__declspec(align(16)) Matrix3x3;
#else
__attribute__((aligned(16))) Matrix3x3;
#endif

/******************************************************************************

    Matrix3x4

******************************************************************************/
struct Matrix3x4 {
    union {
        struct {
            float _00, _01, _02, _03;
            float _10, _11, _12, _13;
            float _20, _21, _22, _23;
        };
        float m[3][4];
        Vector4D row[3];
    };

    static constexpr size_t kRowDimension = 3;
    static constexpr size_t kColumnDimension = 4;
    Matrix3x4() = default;
    Matrix3x4(const Matrix3x4&) = default;
    Matrix3x4& operator=(const Matrix3x4&) = default;
    Matrix3x4(Matrix3x4&&) = default;
    Matrix3x4& operator=(Matrix3x4&&) = default;

    constexpr Matrix3x4(float _00, float _01, float _02, float _03,
                        float _10, float _11, float _12, float _13,
                        float _20, float _21, float _22, float _23) noexcept;
    constexpr Matrix3x4(const float (&Mat)[12]) noexcept;
    constexpr Matrix3x4(const float (&Mat)[3][4]) noexcept;

    Vector4D& operator[](size_t Index);
    const Vector4D& operator[](size_t Index) const;
    Matrix3x4& operator+=(const Matrix3x4&) noexcept;
    Matrix3x4& operator-=(const Matrix3x4&) noexcept;
    Matrix3x4& operator*=(float) noexcept;
    Matrix3x4& operator/=(float) noexcept;
};
using Matrix3x4A =
#ifdef _MSC_VER
__declspec(align(16)) Matrix3x4;
#else
__attribute__((aligned(16))) Matrix3x4;
#endif

/******************************************************************************

    Matrix4x3

******************************************************************************/
struct Matrix4x3 {
    union {
        struct {
            float _00, _01, _02;
            float _10, _11, _12;
            float _20, _21, _22;
            float _30, _31, _32;
        };
        float m[4][3];
        Vector3D row[4];
    };

    static constexpr size_t kRowDimension = 4;
    static constexpr size_t kColumnDimension = 3;
    Matrix4x3() = default;
    Matrix4x3(const Matrix4x3&) = default;
    Matrix4x3& operator=(const Matrix4x3&) = default;
    Matrix4x3(Matrix4x3&&) = default;
    Matrix4x3& operator=(Matrix4x3&&) = default;

    constexpr Matrix4x3(float _00, float _01, float _02,
                        float _10, float _11, float _12,
                        float _20, float _21, float _22,
                        float _30, float _31, float _32) noexcept;
    constexpr Matrix4x3(const float (&Mat)[12]) noexcept;
    constexpr Matrix4x3(const float (&Mat)[4][3]) noexcept;

    Vector3D& operator[](size_t Index);
    const Vector3D& operator[](size_t Index) const;
    Matrix4x3& operator+=(const Matrix4x3&) noexcept;
    Matrix4x3& operator-=(const Matrix4x3&) noexcept;
    Matrix4x3& operator*=(float) noexcept;
    Matrix4x3& operator/=(float) noexcept;
};
using Matrix4x3A =
#ifdef _MSC_VER
__declspec(align(16)) Matrix4x3;
#else
__attribute__((aligned(16))) Matrix4x3;
#endif

/******************************************************************************

    Matrix4x4

******************************************************************************/
struct Matrix4x4 {
    union {
        struct {
            float _00, _01, _02, _03;
            float _10, _11, _12, _13;
            float _20, _21, _22, _23;
            float _30, _31, _32, _33;
        };
        float m[4][4];
        Vector4D row[4];
    };

    static constexpr size_t kRowDimension = 4;
    static constexpr size_t kColumnDimension = 4;
    Matrix4x4() = default;
    Matrix4x4(const Matrix4x4&) = default;
    Matrix4x4& operator=(const Matrix4x4&) = default;
    Matrix4x4(Matrix4x4&&) = default;
    Matrix4x4& operator=(Matrix4x4&&) = default;

    constexpr Matrix4x4(float _00, float _01, float _02, float _03,
                        float _10, float _11, float _12, float _13,
                        float _20, float _21, float _22, float _23,
                        float _30, float _31, float _32, float _33) noexcept;
    constexpr Matrix4x4(const float (&Mat)[16]) noexcept;
    constexpr Matrix4x4(const float (&Mat)[4][4]) noexcept;
    constexpr Matrix4x4(const Vector4D (&Row)[4]) noexcept :
        row{Row[0], Row[1], Row[2], Row[3]} {}

    Vector4D& operator[](size_t Index);
    const Vector4D& operator[](size_t Index) const;
    Matrix4x4& operator+=(const Matrix4x4&) noexcept;
    Matrix4x4& operator-=(const Matrix4x4&) noexcept;
    Matrix4x4& operator*=(float) noexcept;
    Matrix4x4& operator/=(float) noexcept;
};
using Matrix4x4A = 
#ifdef _MSC_VER
__declspec(align(16)) Matrix4x4;
#else
__attribute__((aligned(16))) Matrix4x4;
#endif

/******************************************************************************

    Matrix3x3::

******************************************************************************/
inline constexpr Matrix3x3::Matrix3x3(const float _00_, const float _01_, const float _02_,
                                      const float _10_, const float _11_, const float _12_,
                                      const float _20_, const float _21_, const float _22_ ) noexcept : 
  _00{_00_}, _01{_01_}, _02{_02_}, _10{_10_}, _11{_11_}, _12{_12_}, _20{_20_}, _21{_21_}, _22{_22_} {}
inline constexpr Matrix3x3::Matrix3x3(const float (&Mat)[9]) noexcept : 
  _00{Mat[0]}, _01{Mat[1]}, _02{Mat[2]}, _10{Mat[3]}, _11{Mat[4]}, _12{Mat[5]}, _20{Mat[6]}, _21{Mat[7]}, _22{Mat[8]}{}
inline constexpr Matrix3x3::Matrix3x3(const float (&Mat)[3][3]) noexcept :
  _00{Mat[0][0]}, _01{Mat[0][1]}, _02{Mat[0][2]},
  _10{Mat[1][0]}, _11{Mat[1][1]}, _12{Mat[1][2]},
  _20{Mat[2][0]}, _21{Mat[2][1]}, _22{Mat[2][2]} {}
inline Vector3D& Matrix3x3::operator[](const size_t Idx) {
    if(Idx>=3) vector_impl::rangeError("Matrix3x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix3x3::operator[](const size_t Idx) const {
    if(Idx>=3) vector_impl::rangeError("Matrix3x3::operator[]");
    return row[Idx];
}
inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& M) noexcept {
    _00 += M._00; _01 += M._01; _02 += M._02;
    _10 += M._10; _11 += M._11; _12 += M._12;
    _20 += M._20; _21 += M._21; _22 += M._22;
    return *this;
}
inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& M) noexcept {
    _00 -= M._00; _01 -= M._01; _02 -= M._02;
    _10 -= M._10; _11 -= M._11; _12 -= M._12;
    _20 -= M._20; _21 -= M._21; _22 -= M._22;
    return *this;
}
inline Matrix3x3& Matrix3x3::operator*=(const float S) noexcept {
    _00 *= S; _01 *= S; _02 *= S;
    _10 *= S; _11 *= S; _12 *= S;
    _20 *= S; _21 *= S; _22 *= S;
    return *this; 
}
inline Matrix3x3& Matrix3x3::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Matrix3x4::

******************************************************************************/
inline constexpr Matrix3x4::Matrix3x4(const float _00_, const float _01_, const float _02_, const float _03_,
                                      const float _10_, const float _11_, const float _12_, const float _13_,
                                      const float _20_, const float _21_, const float _22_, const float _23_) noexcept:
  _00{_00_}, _01{_01_}, _02{_02_}, _03{_03_},
  _10{_10_}, _11{_11_}, _12{_12_}, _13{_13_},
  _20{_20_}, _21{_21_}, _22{_22_}, _23{_23_} {}
inline constexpr Matrix3x4::Matrix3x4(const float (&Mat)[12]) noexcept :
  _00{Mat[0]}, _01{Mat[1]}, _02{Mat[2]}, _03{Mat[3]},
  _10{Mat[4]}, _11{Mat[5]}, _12{Mat[6]}, _13{Mat[7]},
  _20{Mat[8]}, _21{Mat[9]}, _22{Mat[10]}, _23{Mat[11]} {}
inline constexpr Matrix3x4::Matrix3x4(const float (&Mat)[3][4]) noexcept :
  _00{Mat[0][0]}, _01{Mat[0][1]}, _02{Mat[0][2]}, _03{Mat[0][3]},
  _10{Mat[1][0]}, _11{Mat[1][1]}, _12{Mat[1][2]}, _13{Mat[1][3]},
  _20{Mat[2][0]}, _21{Mat[2][1]}, _22{Mat[2][2]}, _23{Mat[2][3]} {}
inline Vector4D& Matrix3x4::operator[](const size_t Idx) {
    if(Idx>=3) vector_impl::rangeError("Matrix3x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix3x4::operator[](const size_t Idx) const {
    if(Idx>=3) vector_impl::rangeError("Matrix3x4::operator[]");
    return row[Idx];
}
inline Matrix3x4& Matrix3x4::operator+=(const Matrix3x4& M) noexcept {
    _00 += M._00; _01 += M._01; _02 += M._02; _03 += M._03;
    _10 += M._10; _11 += M._11; _12 += M._12; _13 += M._13;
    _20 += M._20; _21 += M._21; _22 += M._22; _23 += M._23;
    return *this;
}
inline Matrix3x4& Matrix3x4::operator-=(const Matrix3x4& M) noexcept {
    _00 -= M._00; _01 -= M._01; _02 -= M._02; _03 -= M._03;
    _10 -= M._10; _11 -= M._11; _12 -= M._12; _13 -= M._13;
    _20 -= M._20; _21 -= M._21; _22 -= M._22; _23 -= M._23;
    return *this;
}
inline Matrix3x4& Matrix3x4::operator*=(const float S) noexcept {
    _00 *= S; _01 *= S; _02 *= S; _03 *= S;
    _10 *= S; _11 *= S; _12 *= S; _13 *= S;
    _20 *= S; _21 *= S; _22 *= S; _23 *= S;
    return *this;
}
inline Matrix3x4& Matrix3x4::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Matrix4x3::

******************************************************************************/
inline constexpr Matrix4x3::Matrix4x3(const float _00_, const float _01_, const float _02_,
                                      const float _10_, const float _11_, const float _12_,
                                      const float _20_, const float _21_, const float _22_,
                                      const float _30_, const float _31_, const float _32_) noexcept :
  _00{_00_}, _01{_01_}, _02{_02_},
  _10{_10_}, _11{_11_}, _12{_12_},
  _20{_20_}, _21{_21_}, _22{_22_},
  _30{_30_}, _31{_31_}, _32{_32_} {}
inline constexpr Matrix4x3::Matrix4x3(const float (&Mat)[12]) noexcept :
  _00{Mat[0]}, _01{Mat[1]}, _02{Mat[2]},
  _10{Mat[3]}, _11{Mat[4]}, _12{Mat[5]},
  _20{Mat[6]}, _21{Mat[7]}, _22{Mat[8]},
  _30{Mat[9]}, _31{Mat[10]}, _32{Mat[11]} {}
inline constexpr Matrix4x3::Matrix4x3(const float (&Mat)[4][3]) noexcept :
  _00{Mat[0][0]}, _01{Mat[0][1]}, _02{Mat[0][2]},
  _10{Mat[1][0]}, _11{Mat[1][1]}, _12{Mat[1][2]},
  _20{Mat[2][0]}, _21{Mat[2][1]}, _22{Mat[2][2]},
  _30{Mat[3][0]}, _31{Mat[3][1]}, _32{Mat[3][2]} {}
inline Vector3D& Matrix4x3::operator[](const size_t Idx) {
    if(Idx>=4) vector_impl::rangeError("Matrix4x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix4x3::operator[](const size_t Idx) const {
    if(Idx>=4) vector_impl::rangeError("Matrix4x3::operator[]");
    return row[Idx];
}
inline Matrix4x3& Matrix4x3::operator+=(const Matrix4x3& M) noexcept {
    _00 += M._00; _01 += M._01; _02 += M._02;
    _10 += M._10; _11 += M._11; _12 += M._12;
    _20 += M._20; _21 += M._21; _22 += M._22;
    _30 += M._30; _31 += M._31; _32 += M._32;
    return *this;
}
inline Matrix4x3& Matrix4x3::operator-=(const Matrix4x3& M) noexcept {
    _00 -= M._00; _01 -= M._01; _02 -= M._02;
    _10 -= M._10; _11 -= M._11; _12 -= M._12;
    _20 -= M._20; _21 -= M._21; _22 -= M._22;
    _30 -= M._30; _31 -= M._31; _32 -= M._32;
    return *this;
}
inline Matrix4x3& Matrix4x3::operator*=(const float S) noexcept {
    _00 *= S; _01 *= S; _02 *= S;
    _10 *= S; _11 *= S; _12 *= S;
    _20 *= S; _21 *= S; _22 *= S;
    _30 *= S; _31 *= S; _32 *= S;
    return *this;
}
inline Matrix4x3& Matrix4x3::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Matrix4x4::

******************************************************************************/
inline constexpr Matrix4x4::Matrix4x4(const float _00_, const float _01_, const float _02_, const float _03_,
                                      const float _10_, const float _11_, const float _12_, const float _13_,
                                      const float _20_, const float _21_, const float _22_, const float _23_,
                                      const float _30_, const float _31_, const float _32_, const float _33_) noexcept:
  _00{_00_}, _01{_01_}, _02{_02_}, _03{_03_},
  _10{_10_}, _11{_11_}, _12{_12_}, _13{_13_},
  _20{_20_}, _21{_21_}, _22{_22_}, _23{_23_},
  _30{_30_}, _31{_31_}, _32{_32_}, _33{_33_} {}
inline constexpr Matrix4x4::Matrix4x4(const float (&Mat)[16]) noexcept :
  _00{Mat[0]}, _01{Mat[1]}, _02{Mat[2]}, _03{Mat[3]},
  _10{Mat[4]}, _11{Mat[5]}, _12{Mat[6]}, _13{Mat[7]},
  _20{Mat[8]}, _21{Mat[9]}, _22{Mat[10]}, _23{Mat[11]},
  _30{Mat[12]}, _31{Mat[13]}, _32{Mat[14]}, _33{Mat[15]} {}
inline constexpr Matrix4x4::Matrix4x4(const float (&Mat)[4][4]) noexcept :
  _00{Mat[0][0]}, _01{Mat[0][1]}, _02{Mat[0][2]}, _03{Mat[0][3]},
  _10{Mat[1][0]}, _11{Mat[1][1]}, _12{Mat[1][2]}, _13{Mat[1][3]},
  _20{Mat[2][0]}, _21{Mat[2][1]}, _22{Mat[2][2]}, _23{Mat[2][3]},
  _30{Mat[3][0]}, _31{Mat[3][1]}, _32{Mat[3][2]}, _33{Mat[3][3]} {}
inline Vector4D& Matrix4x4::operator[](const size_t Idx) {
    if(Idx>=4) vector_impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix4x4::operator[](const size_t Idx) const {
    if(Idx>=4) vector_impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}
inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& M) noexcept {
    _00 += M._00; _01 += M._01; _02 += M._02; _03 += M._03;
    _10 += M._10; _11 += M._11; _12 += M._12; _13 += M._13;
    _20 += M._20; _21 += M._21; _22 += M._22; _23 += M._23;
    _30 += M._30; _31 += M._31; _32 += M._32; _33 += M._33;
    return *this;
}
inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& M) noexcept {
    _00 -= M._00; _01 -= M._01; _02 -= M._02; _03 -= M._03;
    _10 -= M._10; _11 -= M._11; _12 -= M._12; _13 -= M._13;
    _20 -= M._20; _21 -= M._21; _22 -= M._22; _23 -= M._23;
    _30 -= M._30; _31 -= M._31; _32 -= M._32; _33 -= M._33;
    return *this;
}
inline Matrix4x4& Matrix4x4::operator*=(const float S) noexcept {
    _00 *= S; _01 *= S; _02 *= S; _03 *= S;
    _10 *= S; _11 *= S; _12 *= S; _13 *= S;
    _20 *= S; _21 *= S; _22 *= S; _23 *= S;
    _30 *= S; _31 *= S; _32 *= S; _33 *= S;
    return *this;
}
inline Matrix4x4& Matrix4x4::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MMATRIX_HEADER_
// EOF
