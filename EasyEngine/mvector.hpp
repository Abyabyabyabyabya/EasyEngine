///
/// \file   mvector
/// \brief  算術用数値コンテナ
/// \author 板場
///
///
/// \par    履歴
///         - 2020/7/28
///             - ヘッダ追加
///             - VectorND 定義
///             - MatrixMxN 定義
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_HEADER_

#include <cstddef>
#include <stdexcept>

namespace easy_engine {
namespace m_lib {
  namespace impl {
    [[noreturn]] void rangeError(std::string&& Func) {
        throw std::logic_error("out-of-range access detected. func: "+Func);
    }
  } // namespace impl

/******************************************************************************

    Vector2D

******************************************************************************/
struct Vector2D {
    union {
        struct {
            float x, y;
        };
        float v[2];
    };

    Vector2D() = default;
    Vector2D(const Vector2D&) = default;
    Vector2D& operator=(const Vector2D&) = default;
    Vector2D(Vector2D&&) = default;
    Vector2D& operator=(Vector2D&&) = default;

    constexpr Vector2D(float X, float Y) noexcept;
    constexpr Vector2D(const float (&XY)[2]) noexcept;

    constexpr float& operator[](size_t Index);
};

/******************************************************************************

    Vector3D

******************************************************************************/
struct Vector3D {
    union {
        struct {
            float x, y, z;
        };
        float v[3];
    };

    Vector3D() = default;
    Vector3D(const Vector3D&) = default;
    Vector3D& operator=(const Vector3D&) = default;
    Vector3D(Vector3D&&) = default;
    Vector3D& operator=(Vector3D&&) = default;

    constexpr Vector3D(float X, float Y, float Z) noexcept;
    constexpr Vector3D(const float (&XYZ)[3]) noexcept;

    constexpr float& operator[](size_t Index);
};

/******************************************************************************

    Vector4D

******************************************************************************/
struct Vector4D {
    union {
        struct {
            float x, y, z, w;
        };
        float v[4];
    };

    Vector4D() = default;
    Vector4D(const Vector4D&) = default;
    Vector4D& operator=(const Vector4D&) = default;
    Vector4D(Vector4D&&) = default;
    Vector4D& operator=(Vector4D&&) = default;

    constexpr Vector4D(float X, float Y, float Z, float W) noexcept;
    constexpr Vector4D(const float (&XYZW)[4]) noexcept;

    constexpr float& operator[](size_t Index);
};

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

    constexpr Vector3D& operator[](size_t Index);
};

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

    constexpr Vector4D& operator[](size_t Index);
};

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

    constexpr Vector3D& operator[](size_t Index);
};

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

    constexpr Vector4D& operator[](size_t Index);
};

/******************************************************************************

    Vector2D::

******************************************************************************/
inline constexpr Vector2D::Vector2D(const float X, const float Y) noexcept : x{X}, y{Y} {}
inline constexpr Vector2D::Vector2D(const float (&XY)[2]) noexcept : x{XY[0]}, y{XY[1]} {}
inline constexpr float& Vector2D::operator[](size_t Idx) {
    if(Idx>=2) impl::rangeError("Vector2D::operatorp[]");
    return v[Idx];
}

/******************************************************************************

    Vector3D::

******************************************************************************/
inline constexpr Vector3D::Vector3D(const float X, const float Y, const float Z) noexcept : x{X}, y{Y}, z{Z} {}
inline constexpr Vector3D::Vector3D(const float (&XYZ)[3]) noexcept : x{XYZ[0]}, y{XYZ[1]}, z{XYZ[2]} {}
inline constexpr float& Vector3D::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}

/******************************************************************************

    Vector4D::

******************************************************************************/
inline constexpr Vector4D::Vector4D(const float X, const float Y, const float Z, const float W) noexcept :
  x{X}, y{Y}, z{Z}, w{W} {}
inline constexpr Vector4D::Vector4D(const float (&XYZW)[4]) noexcept : x{XYZW[0]}, y{XYZW[1]}, z{XYZW[2]}, w{XYZW[3]}{}
inline constexpr float& Vector4D::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}

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
inline constexpr Vector3D& Matrix3x3::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x3::operator[]");
    return row[Idx];
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
inline constexpr Vector4D& Matrix3x4::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x4::operator[]");
    return row[Idx];
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
inline constexpr Vector3D& Matrix4x3::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x3::operator[]");
    return row[Idx];
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
inline constexpr Vector4D& Matrix4x4::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}

} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
// EOF
