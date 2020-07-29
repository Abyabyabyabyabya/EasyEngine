///
/// \file   mvector.hpp
/// \brief  算術用数値コンテナ群定義ヘッダ
///
///         コンテナはコンパイル時定数(constexpr)になることができます。
///         コンパイル時のベクトル演算、行列演算も一部サポートしていますが、デフォルトでは使用できないことがあります。
///         使用するには、egeg::m_lib::compile_time_calculation 名前空間を明示的に指定するか、
///         このヘッダをインクルードする直前で EGEG_MLIB_USE_COMPILE_TIME_CALCULATION マクロを定義してください。
///         一方でEGEG_MLIB_USE_RUN_TIME_CALCULATIONマクロを定義すると、実行時用計算関数が使用できます。
///         どちらも指定されていない場合、デフォルトの名前空間が選択されます。
///
/// \attention 名前空間を明示的に指定する方法ではなく、EGEG_MLIB_USE_COMPILE_TIME_CALCULATIONマクロを定義して
///            コンパイル時計算関数を使用した場合、それ以降の関数呼び出しが全てコンパイル時計算用のものになります。\n
///            以上の理由から、ヘッダでのマクロ定義を行ってはいけません。\n
///            マクロを定義した.cppファイルで、速度重視の実行時用関数を呼び出したい場合は、
///            egeg::m_lib::run_time_calculation名前空間にある同一名の関数を使用してください。\n
///            …compile_time_calculation名前空間、及び…run_time_calculation名前空間のusing宣言を行ってはいけません。
///
/// \author 板場
///
/// \par    履歴
///         - 2020/7/28
///             - ヘッダ追加
///             - VectorND 定義
///             - MatrixMxN 定義
///             - ベクトル演算プロトタイプ宣言(速度重視実行時用、コンパイル時計算用)
///
/// \note   実行時用名前空間、コンパイル時用名前空間について\n
///         元々は実行時用名前空間は指定しなくても良いようにしていたが、\n
///         using namespace egeg::m_lib;　とせずに\n
///         using namespace egeg::m_lib::compile_time_calculation;\n
///         としてコンパイル時用関数を呼び出そうとしたときに、
///         ADLにより…run_time_calculation名前空間も検索の対象となり、オーバーロード解決が曖昧になる問題が発生したため、
///         現在(2020/7/28)の形になった。\n
///         実行時計算用関数について\n
///         上手く扱えていない。デフォルトでは使用できないようにしている。
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_HEADER_

#include <cstddef>
#include <stdexcept>
#include <DirectXMath.h>

namespace easy_engine {
namespace m_lib {
#ifdef EGEG_MLIB_USE_COMPILE_TIME_CALCULATION
  inline namespace compile_time_calculation {}
#elif defined EGEG_MLIB_USE_RUN_TIME_CALCULATION
  inline namespace run_time_calculation {}
#else // default
  inline namespace compile_time_calculation {}
#endif // EGEG_MLIB_USE_COMPILE_TIME_CALCULATION

struct Vector2D;
struct Vector3D;
struct Vector4D;

  namespace impl {
    [[noreturn]] void rangeError(std::string&& Func) {
        throw std::logic_error("out-of-range access detected. func: "+Func);
    }

    DirectX::XMVECTOR load(const Vector2D&);
    DirectX::XMVECTOR load(const Vector3D&);
    DirectX::XMVECTOR load(const Vector4D&);
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
    template <size_t N> constexpr Vector2D(const float (&XY)[N]) noexcept;
    template <size_t N> Vector2D& operator=(const float (&XY)[N]) noexcept;

    float& operator[](size_t Index);
    float operator[](size_t Index) const;
    Vector2D& operator+=(const Vector2D&) noexcept;
    Vector2D& operator-=(const Vector2D&) noexcept;
    Vector2D& operator*=(float) noexcept;
    Vector2D& operator/=(float) noexcept;
};
using Vector2DA =
#ifdef _MSC_VER
__declspec(align(16)) Vector2D;
#else
__attribute__((aligned(16))) Vector2D;
#endif

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
    template <size_t N> constexpr Vector3D(const float (&XYZ)[N]) noexcept;
    template <size_t N> Vector3D& operator=(const float (&XYZ)[N]) noexcept;

    float& operator[](size_t Index);
    float operator[](size_t Index) const;
    Vector3D& operator+=(const Vector3D&) noexcept;
    Vector3D& operator-=(const Vector3D&) noexcept;
    Vector3D& operator*=(float) noexcept;
    Vector3D& operator/=(float) noexcept;
};
using Vector3DA =
#ifdef _MSC_VER
__declspec(align(16)) Vector3D;
#else  
__attribute__((aligned(16))) Vector3D;
#endif

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
    template <size_t N> constexpr Vector4D(const float (&XYZW)[N]) noexcept;
    template <size_t N> Vector4D& operator=(const float (&XYZW)[N]) noexcept;

    float& operator[](size_t Index);
    float operator[](size_t Index) const;
    Vector4D& operator+=(const Vector4D&) noexcept;
    Vector4D& operator-=(const Vector4D&) noexcept;
    Vector4D& operator*=(float) noexcept;
    Vector4D& operator/=(float) noexcept;
};
using Vector4DA =
#ifdef _MSC_VER
__declspec(align(16)) Vector4D;
#else
__attribute__((aligned(16))) Vector4D
#endif

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

    Vector3D& operator[](size_t Index);
    const Vector3D& operator[](size_t Index) const;
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

    Vector4D& operator[](size_t Index);
    const Vector4D& operator[](size_t Index) const;
};
using Matrix4x4A = 
#ifdef _MSC_VER
__declspec(align(16)) Matrix4x4;
#else
__attribute__((aligned(16))) Matrix4x4;
#endif

/******************************************************************************

    vector calculation

******************************************************************************/
  namespace run_time_calculation {
    template <class Vector> DirectX::XMVECTOR vectorAdd(const Vector&, const Vector&);
    template <class Vector> DirectX::XMVECTOR vectorSub(const Vector&, const Vector&);
    template <class Vector> DirectX::XMVECTOR vectorMul(const Vector&, float);
    template <class Vector> DirectX::XMVECTOR vectorDiv(const Vector&, float);
    DirectX::XMVECTOR operator+(const Vector2D&, const Vector2D&);
    DirectX::XMVECTOR operator-(const Vector2D&, const Vector2D&);
    DirectX::XMVECTOR operator*(const Vector2D&, float);
    DirectX::XMVECTOR operator/(const Vector2D&, float);
    float dot(const Vector2D&, const Vector2D&);
    float cross(const Vector2D&, const Vector2D&);
    DirectX::XMVECTOR operator+(const Vector3D&, const Vector3D&);
    DirectX::XMVECTOR operator-(const Vector3D&, const Vector3D&);
    DirectX::XMVECTOR operator*(const Vector3D&, float);
    DirectX::XMVECTOR operator/(const Vector3D&, float);
    float dot(const Vector3D&, const Vector3D&);
    Vector3D cross(const Vector3D&, const Vector3D&);
    DirectX::XMVECTOR operator+(const Vector4D&, const Vector4D&);
    DirectX::XMVECTOR operator-(const Vector4D&, const Vector4D&);
    DirectX::XMVECTOR operator*(const Vector4D&, float);
    DirectX::XMVECTOR operator/(const Vector4D&, float);
    float dot(const Vector4D&, const Vector4D&);
    Vector4D cross(const Vector4D&, const Vector4D&, const Vector4D&);
  } // namespace run_time_calculation
  namespace compile_time_calculation {
    constexpr Vector2D operator+(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector2D vectorAdd(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector2D operator-(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector2D vectorSub(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector2D operator*(const Vector2D&, float) noexcept;
    constexpr Vector2D vectorMul(const Vector2D&, float) noexcept;
    constexpr Vector2D operator/(const Vector2D&, float);
    constexpr Vector2D vectorDiv(const Vector2D&, float);
    constexpr float dot(const Vector2D&, const Vector2D&) noexcept;
    constexpr float cross(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector3D operator+(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector3D vectorAdd(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector3D operator-(const Vector3D& ,const Vector3D&) noexcept;
    constexpr Vector3D vectorSub(const Vector3D& ,const Vector3D&) noexcept;
    constexpr Vector3D operator*(const Vector3D&, float) noexcept;
    constexpr Vector3D vectorMul(const Vector3D&, float) noexcept;
    constexpr Vector3D operator/(const Vector3D&, float);
    constexpr Vector3D vectorDiv(const Vector3D&, float);
    constexpr float dot(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector3D cross(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector4D operator+(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D vectorAdd(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D operator-(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D vectorSub(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D operator*(const Vector4D&, float) noexcept;
    constexpr Vector4D vectorMul(const Vector4D&, float) noexcept;
    constexpr Vector4D operator/(const Vector4D&, float);
    constexpr Vector4D vectorDiv(const Vector4D&, float);
    constexpr float dot(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D cross(const Vector4D&, const Vector4D&, const Vector4D&) noexcept;
  } // namespace compile_time_calculation

/******************************************************************************

    matrix calculation

******************************************************************************/
  namespace run_time_calculation {

  } // namespace run_time_calculation
  namespace compile_time_calculation {

  } // namespace compile_time_calculation

/******************************************************************************

    Vector2D::

******************************************************************************/
inline constexpr Vector2D::Vector2D(const float X, const float Y) noexcept : x{X}, y{Y} {}
template <size_t N>
inline constexpr Vector2D::Vector2D(const float (&XY)[N]) noexcept : x{XY[0]}, y{XY[1]} {
    static_assert(N>=2, "the number of elements in 'XY' must be at least 2");
}
template <size_t N>
inline Vector2D& Vector2D::operator=(const float (&XY)[N]) noexcept {
    static_assert(N>=2, "the number of elements in 'XY' must be at least 2");

    x = XY[0];
    y = XY[1];
    return *this;
}
inline float& Vector2D::operator[](size_t Idx) {
    if(Idx>=2) impl::rangeError("Vector2D::operatorp[]");
    return v[Idx];
}
inline float Vector2D::operator[](size_t Idx) const {
    if(Idx>=2) impl::rangeError("Vector2D::operator[]");
    return v[Idx];
}
inline Vector2D& Vector2D::operator+=(const Vector2D& V) noexcept {
    x += V.x;
    y += V.y;
    return *this;
}
inline Vector2D& Vector2D::operator-=(const Vector2D& V) noexcept {
    x -= V.x;
    y -= V.y;
    return *this;
}
inline Vector2D& Vector2D::operator*=(const float S) noexcept {
    x *= S;
    y *= S;
    return *this;
}
inline Vector2D& Vector2D::operator/=(const float S) noexcept {
    *this *= 1.0F/S;
    return *this;
}

/******************************************************************************

    Vector3D::

******************************************************************************/
inline constexpr Vector3D::Vector3D(const float X, const float Y, const float Z) noexcept : x{X}, y{Y}, z{Z} {}
template <size_t N>
inline constexpr Vector3D::Vector3D(const float (&XYZ)[N]) noexcept : x{XYZ[0]}, y{XYZ[1]}, z{XYZ[2]} {
    static_assert(N>=3, "the number of elements in 'XYZ' must be at least 3");
}
template <size_t N>
inline Vector3D& Vector3D::operator=(const float (&XYZ)[N]) noexcept {
    static_assert(N>=3, "the number of elements in 'XYZ' must be at least 3");

    x = XYZ[0];
    y = XYZ[1];
    z = XYZ[2];
    return *this;
}
inline float& Vector3D::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
inline float Vector3D::operator[](size_t Idx) const {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
//inline Vector3D& Vector3D::operator+=(const Vector3D&

/******************************************************************************

    Vector4D::

******************************************************************************/
inline constexpr Vector4D::Vector4D(const float X, const float Y, const float Z, const float W) noexcept :
  x{X}, y{Y}, z{Z}, w{W} {}
template <size_t N>
inline constexpr Vector4D::Vector4D(const float (&XYZW)[N]) noexcept : x{XYZW[0]}, y{XYZW[1]}, z{XYZW[2]}, w{XYZW[3]} {
    static_assert(N>=4, "the number of elements in 'XYZW' must be at least 4");
}
template <size_t N>
inline Vector4D& Vector4D::operator=(const float (&XYZW)[N]) noexcept {
    static_assert(N>=4, "the number of elements in 'XYZW' must be at least 4");

    x = XYZW[0];
    y = XYZW[1];
    z = XYZW[2];
    w = XYZW[3];
    return *this;
}
inline float& Vector4D::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}
inline float Vector4D::operator[](size_t Idx) const {
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
inline Vector3D& Matrix3x3::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix3x3::operator[](size_t Idx) const {
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
inline Vector4D& Matrix3x4::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix3x4::operator[](size_t Idx) const {
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
inline Vector3D& Matrix4x3::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix4x3::operator[](size_t Idx) const {
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
inline Vector4D& Matrix4x4::operator[](size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix4x4::operator[](size_t Idx) const {
    if(Idx>=4) impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}

/******************************************************************************

    vector calculation define

******************************************************************************/
  namespace run_time_calculation {
    template <class Vector>
    inline DirectX::XMVECTOR vectorAdd(const Vector& L, const Vector& R) {
        return DirectX::XMVectorAdd(impl::load(L), impl::load(R));
    }
    template <class Vector>
    inline DirectX::XMVECTOR vectorAdd(DirectX::FXMVECTOR L, const Vector& R) {
        return DirectX::XMVectorAdd(L, impl::load(R));
    }
    template <class Vector>
    inline DirectX::XMVECTOR vectorSub(const Vector& L, const Vector& R) {
        return DirectX::XMVectorSubtract(impl::load(L), impl::load(R));
    }
    template <class Vector>
    inline DirectX::XMVECTOR vectorSub(DirectX::FXMVECTOR L, const Vector& R) {
        return DirectX::XMVectorSubtract(L, impl::load(R));
    }
    template <class Vector>
    inline DirectX::XMVECTOR vectorMul(const Vector& L, const float R) {
        alignas(16) const float value = R;
        return DirectX::XMVectorMultiply(impl::load(L), _mm_load1_ps(&value));
    }
    template <class Vector>
    inline DirectX::XMVECTOR vectorDiv(const Vector& L, const float R) {
        alignas(16) const float value = R;
        return DirectX::XMVectorDivide(impl::load(L), _mm_load1_ps(&value));
    }
    inline DirectX::XMVECTOR operator+(const Vector2D& L, const Vector2D& R) { return run_time_calculation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector2D& L, const Vector2D& R) { return run_time_calculation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector2D& L, const float R) { return run_time_calculation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector2D& L, const float R) { return run_time_calculation::vectorDiv(L, R); }
    inline float dot(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Dot(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline float cross(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Cross(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline DirectX::XMVECTOR operator+(const Vector3D& L, const Vector3D& R) { return run_time_calculation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector3D& L, const Vector3D& R) { return run_time_calculation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector3D& L, const float R) { return run_time_calculation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector3D& L, const float R) { return run_time_calculation::vectorDiv(L, R); }
    inline float dot(const Vector3D& L, const Vector3D& R) {
        return DirectX::XMVector3Dot(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline Vector3D cross(const Vector3D& L, const Vector3D& R) {
        return Vector3D{DirectX::XMVector3Cross(impl::load(L), impl::load(R)).m128_f32};
    }
    inline DirectX::XMVECTOR operator+(const Vector4D& L, const Vector4D& R) { return run_time_calculation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator+(DirectX::FXMVECTOR L, const Vector4D& R) { return run_time_calculation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector4D& L, const Vector4D& R) { return run_time_calculation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator-(DirectX::FXMVECTOR L, const Vector4D& R) { return run_time_calculation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector4D& L, const float R) { return run_time_calculation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector4D& L, const float R) { return run_time_calculation::vectorDiv(L, R); }
    inline float dot(const Vector4D& L, const Vector4D& R) {
        return DirectX::XMVector4Dot(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) {
        return Vector4D{DirectX::XMVector4Cross(impl::load(V1), impl::load(V2), impl::load(V3)).m128_f32};
    }
  } // namespace run_time_calculation

  namespace compile_time_calculation {
    inline constexpr Vector2D operator+(const Vector2D& L, const Vector2D& R) noexcept {
        return compile_time_calculation::vectorAdd(L, R);
    }
    inline constexpr Vector2D vectorAdd(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x+R.x, L.y+R.y};
    }
    inline constexpr Vector2D operator-(const Vector2D& L, const Vector2D& R) noexcept {
        return compile_time_calculation::vectorSub(L, R);
    }
    inline constexpr Vector2D vectorSub(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x-R.x, L.y-R.y};
    }
    inline constexpr Vector2D operator*(const Vector2D& L, const float R) noexcept {
        return compile_time_calculation::vectorMul(L, R);
    }
    inline constexpr Vector2D vectorMul(const Vector2D& L, const float R) noexcept {
        return Vector2D{L.x*R, L.y*R};
    }
    inline constexpr Vector2D operator/(const Vector2D& L, const float R) {
        return compile_time_calculation::vectorDiv(L, R);
    }
    inline constexpr Vector2D vectorDiv(const Vector2D& L, const float R) {
        return compile_time_calculation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector2D& L, const Vector2D& R) noexcept {
        return (L.x*R.x) + (L.y*R.y);
    }
    inline constexpr float cross(const Vector2D& L, const Vector2D& R) noexcept {
        return (L.x*R.y) - (L.y*R.x);
    }
    inline constexpr Vector3D operator+(const Vector3D& L, const Vector3D& R) noexcept {
        return compile_time_calculation::vectorAdd(L, R);
    }
    inline constexpr Vector3D vectorAdd(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x+R.x, L.y+R.y, L.z+R.z};
    }
    inline constexpr Vector3D operator-(const Vector3D& L, const Vector3D& R) noexcept {
        return compile_time_calculation::vectorSub(L, R);
    }
    inline constexpr Vector3D vectorSub(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x-R.x, L.y-R.y, L.z-R.z};
    }
    inline constexpr Vector3D operator*(const Vector3D& L, const float R) noexcept {
        return compile_time_calculation::vectorMul(L, R);
    }
    inline constexpr Vector3D vectorMul(const Vector3D& L, const float R) noexcept {
        return Vector3D{L.x*R, L.y*R, L.z*R};
    }
    inline constexpr Vector3D operator/(const Vector3D& L, const float R) {
        return compile_time_calculation::vectorDiv(L, R);
    }
    inline constexpr Vector3D vectorDiv(const Vector3D& L, const float R) {
        return compile_time_calculation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector3D& L, const Vector3D& R) noexcept {
        return (L.x*R.x) + (L.y*R.y) + (L.z*R.z);
    }
    inline constexpr Vector3D cross(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D {(L.y*R.z) - (L.z*R.y), (L.z*R.x) - (L.x*R.z), (L.x*R.y) - (L.y*R.x)};
    }
    inline constexpr Vector4D operator+(const Vector4D& L, const Vector4D& R) noexcept {
        return compile_time_calculation::vectorAdd(L, R);
    }
    inline constexpr Vector4D vectorAdd(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x+R.x, L.y+R.y, L.z+R.z, L.w+R.w};
    }
    inline constexpr Vector4D operator-(const Vector4D& L, const Vector4D& R) noexcept {
        return compile_time_calculation::vectorSub(L, R);
    }
    inline constexpr Vector4D vectorSub(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x-R.x, L.y-R.y, L.z-R.z, L.w-R.w};
    }
    inline constexpr Vector4D operator*(const Vector4D& L, const float R) noexcept {
        return compile_time_calculation::vectorMul(L, R);
    }
    inline constexpr Vector4D vectorMul(const Vector4D& L, const float R) noexcept {
        return Vector4D{L.x*R, L.y*R, L.z*R, L.w*R};
    }
    inline constexpr Vector4D operator/(const Vector4D& L, const float R) {
        return compile_time_calculation::vectorDiv(L, R);
    }
    inline constexpr Vector4D vectorDiv(const Vector4D& L, const float R) {
        return compile_time_calculation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector4D& L, const Vector4D& R) noexcept {
        return (L.x*R.x) + (L.y*R.y) + (L.z*R.z) + (L.w*R.w);
    }
    // 参考 : https://docs.microsoft.com/en-us/windows/win32/api/directxmath/nf-directxmath-xmvector4cross
    inline constexpr Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) noexcept {
        return Vector4D {
            V1.y*(V2.z*V3.w-V3.z*V2.w) - V1.z*(V2.y*V3.w-V3.y*V2.w) + V1.w*(V2.y*V3.z-V3.y*V2.z),
            V1.x*(V3.z*V2.w-V2.z*V3.w) - V1.z*(V3.x*V2.w-V2.x*V3.w) + V1.w*(V3.x*V2.z-V2.x*V3.z),
            V1.x*(V2.y*V3.w-V3.y*V2.w) - V1.y*(V2.x*V3.w-V3.x*V2.w) + V1.w*(V2.x*V3.y-V3.x*V2.y),
            V1.x*(V3.y*V2.z-V2.y*V3.z) - V1.y*(V3.x*V2.z-V2.x*V3.z) + V1.z*(V3.x*V2.y-V2.x*V3.y)
        };
    }
  } // namespace compile_time_calculation

  namespace impl {
    inline DirectX::XMVECTOR load(const Vector2D& V) { return DirectX::XMVECTOR{V.x, V.y}; }
    inline DirectX::XMVECTOR load(const Vector3D& V) { return DirectX::XMVECTOR{V.x, V.y, V.z}; }
    inline DirectX::XMVECTOR load(const Vector4DA& V) { return _mm_load_ps(V.v); }
  } // namespace impl
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
// EOF
