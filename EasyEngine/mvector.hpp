///
/// \file   mvector.hpp
/// \brief  算術用数値コンテナ群定義ヘッダ
///
///         コンテナはコンパイル時定数(constexpr)になることができます。
///         演算には複数の処理が異なる関数を使用することができます。
///         このヘッダをインクルードする直前で、
///         EGEG_MLIB_USE_SIMD_OPERATIONマクロを定義すると、SIMD演算を行う関数が選択されます。
///         EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATIONマクロを定義すると、計算結果を保存する一時オブジェクトを生成しない
///         関数が選択されます。
///         特に何もしなければデフォルトの関数が指定されます。
///         コンパイル時のベクトル演算、行列演算も一部サポートしていますが、SIMD演算を行う関数ではサポートしていません。
///
/// \attention 名前空間を明示的に指定する方法ではなく、マクロを定義して
///            使用する関数を選択した場合、それ以降の関数呼び出しが全てそのマクロにより選択されるものになります。\n
///            以上の理由から、ヘッダでのマクロ定義を行ってはいけません。\n
///            マクロを定義した.cppファイルで、異なる種類の関数を呼び出したい場合は、
///            都度名前空間を明示的に修飾して関数を選択してください。\n
///            egeg::m_lib::default_operation、egeg::m_lib::default_noncopy_operation及びegeg::m_lib::simd_operation
///            名前空間をusing宣言により省略してはいけません。
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
/// \note   名前空間について\n
///         必ず一つの名前空間を明示的な指定なしで選択できるようにしているので、
///         その時のデフォルトではない名前空間をusing宣言により省略できるようにすると
///         オーバーロード解決が曖昧になってしまう。
///         default_noncopy_operationの関数群について\n
///         遅延評価によりテンポラリオブジェクトの生成を抑制しているが、
///         default_operationの関数群でもコンパイラによる最適化で同じような効果が期待できる。
///         実行時計算用関数について\n
///         上手く扱えていない。デフォルトでは使用できないようにしている。\n
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_HEADER_

#include <cstddef>
#include <stdexcept>
#include <DirectXMath.h>

namespace easy_engine {
namespace m_lib {
#ifdef EGEG_MLIB_USE_SIMD_OPERATION
  inline namespace simd_operation {}
#elif defined EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATION
  inline namespace default_noncopy_operation {}
#else // default
  inline namespace default_operation {}
#endif // EGEG_MLIB_USE_SIMD_OPERATION

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

  #define EGEG_MLIB_DECL_DEFINE_VECTOR_OPERATOR(OpType, Op)\
    template <class LTy, class RTy>\
    class Vector##OpType {\
    public :\
        static_assert(LTy::kDimension==RTy::kDimension, "the dimension of 'LTy' and 'RTy' must be the same");\
        static constexpr size_t kDimension = LTy::kDimension;\
        constexpr Vector##OpType(const LTy& L, const RTy& R) noexcept : l{L}, r{R} {}\
        constexpr float operator[](const size_t I) const {\
            if(I>=kDimension) rangeError("VectorOperator::operator[]");\
            return l[I] Op r[I];\
        }\
    private :\
        const LTy& l;\
        const RTy& r;\
    };\
    template <class LTy>\
    class Vector##OpType<LTy, float> {\
    public :\
        static constexpr size_t kDimension = LTy::kDimension;\
        constexpr Vector##OpType(const LTy& L, const float R) noexcept : l{L}, r{R} {}\
        constexpr float operator[](const size_t I) const {\
            if(I>=kDimension) rangeError("VectorOperator::operator[]");\
            return l[I] Op r;\
        }\
    private :\
        const LTy& l;\
        const float r;\
    }
    
    EGEG_MLIB_DECL_DEFINE_VECTOR_OPERATOR(Add, +);
    EGEG_MLIB_DECL_DEFINE_VECTOR_OPERATOR(Sub, -);
    EGEG_MLIB_DECL_DEFINE_VECTOR_OPERATOR(Mul, *);
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

    static constexpr size_t kDimension = 2U;
    Vector2D() = default;
    Vector2D(const Vector2D&) = default;
    Vector2D& operator=(const Vector2D&) = default;
    Vector2D(Vector2D&&) = default;
    Vector2D& operator=(Vector2D&&) = default;

    constexpr Vector2D(float X, float Y) noexcept;
    template <size_t N> constexpr Vector2D(const float (&XY)[N]) noexcept;
    template <size_t N> Vector2D& operator=(const float (&XY)[N]) noexcept;
    template <class TempTy, class=std::enable_if_t<TempTy::kDimension==kDimension>>
    constexpr Vector2D(const TempTy&) noexcept;
    template <class TempTy, class=std::enable_if_t<TempTy::kDimension==kDimension>>
    Vector2D& operator=(const TempTy&) noexcept;

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

    static constexpr size_t kDimension = 3U;
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

    static constexpr size_t kDimension = 4U;
    Vector4D() = default;
    Vector4D(const Vector4D&) = default;
    Vector4D& operator=(const Vector4D&) = default;
    Vector4D(Vector4D&&) = default;
    Vector4D& operator=(Vector4D&&) = default;

    constexpr Vector4D(float X, float Y, float Z, float W) noexcept;
    template <size_t N> constexpr Vector4D(const float (&XYZW)[N]) noexcept;
    template <size_t N> Vector4D& operator=(const float (&XYZW)[N]) noexcept;
    template <class TempTy, class=std::enable_if_t<TempTy::kDimension==kDimension>>
    constexpr Vector4D(const TempTy&) noexcept;
    template <class TempTy, class=std::enable_if_t<TempTy::kDimension==kDimension>>
    Vector4D& operator=(const TempTy&) noexcept;

    float& operator[](size_t Index);
    constexpr float operator[](size_t Index) const;
    Vector4D& operator+=(const Vector4D&) noexcept;
    template <class TempTy, class=std::enable_if_t<TempTy::kDimension==kDimension>>
    Vector4D& operator+=(const TempTy&) noexcept;
    Vector4D& operator-=(const Vector4D&) noexcept;
    Vector4D& operator*=(float) noexcept;
    Vector4D& operator/=(float) noexcept;

    template <class T>
    constexpr Vector4D(const T& Temp ) noexcept :
        x{Temp[0]}, y{Temp[1]}, z{Temp[2]}, w{Temp[3]} {}
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
  namespace default_operation {
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
  } // namespace default_operation
  namespace default_noncopy_operation {
    template <class LHTy, class RHTy> constexpr impl::VectorAdd<LHTy, RHTy> vectorAdd(const LHTy&, const RHTy&);
    template <class LHTy, class RHTy> constexpr impl::VectorAdd<LHTy, RHTy> operator+(const LHTy&, const RHTy&);
    template <class LHTy, class RHTy> constexpr impl::VectorSub<LHTy, RHTy> vectorSub(const LHTy&, const RHTy&);
    template <class LHTy, class RHTy> constexpr impl::VectorSub<LHTy, RHTy> operator-(const LHTy&, const RHTy&);
    template <class LHTy> constexpr impl::VectorMul<LHTy, float> vectorMul(const LHTy&, float);
    template <class LHTy> constexpr impl::VectorMul<LHTy, float> operator*(const LHTy&, float);
    template <class LHTy> constexpr impl::VectorMul<LHTy, float> vectorDiv(const LHTy&, float);
    template <class LHTy> constexpr impl::VectorMul<LHTy, float> operator/(const LHTy&, float);
    template <class VectorTy> constexpr float dot(const VectorTy&, const VectorTy&) noexcept;
    constexpr float cross(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector3D cross(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector4D cross(const Vector4D&, const Vector4D&, const Vector4D&) noexcept;
  } // namespace default_noncopy_operation
  namespace simd_operation {
    template <class VectorTy> DirectX::XMVECTOR vectorAdd(const VectorTy&, const VectorTy&);
    template <class VectorTy> DirectX::XMVECTOR vectorSub(const VectorTy&, const VectorTy&);
    template <class VectorTy> DirectX::XMVECTOR vectorMul(const VectorTy&, float);
    template <class VectorTy> DirectX::XMVECTOR vectorDiv(const VectorTy&, float);
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
  } // namespace simd_operation

/******************************************************************************

    matrix calculation

******************************************************************************/
  namespace default_operation {

  } // namespace default_operation
  namespace default_noncopy_operation {

  } // namespace default_noncopy_operation
  namespace simd_operation {

  } // namespace simd_operation

/******************************************************************************

    Vector2D::

******************************************************************************/
inline constexpr Vector2D::Vector2D(const float X, const float Y) noexcept : x{X}, y{Y} {}
template <size_t N>
inline constexpr Vector2D::Vector2D(const float (&XY)[N]) noexcept : v{XY[0], XY[1]} {
    static_assert(N>=2, "the number of elements in 'XY' must be at least 2");
}
template <size_t N>
inline Vector2D& Vector2D::operator=(const float (&XY)[N]) noexcept {
    static_assert(N>=2, "the number of elements in 'XY' must be at least 2");

    x = XY[0];
    y = XY[1];
    return *this;
}
template <class TempTy, class>
inline constexpr Vector2D::Vector2D(const TempTy& Temp) noexcept : v{Temp[0], Temp[1]} {}
template <class TempTy, class>
inline Vector2D& Vector2D::operator=(const TempTy& Temp) noexcept {
    x = Temp[0];
    y = Temp[1];
    return *this;
}
inline float& Vector2D::operator[](const size_t Idx) {
    if(Idx>=2) impl::rangeError("Vector2D::operatorp[]");
    return v[Idx];
}
inline float Vector2D::operator[](const size_t Idx) const {
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
    return *this *= 1.0F/S;
}

/******************************************************************************

    Vector3D::

******************************************************************************/
inline constexpr Vector3D::Vector3D(const float X, const float Y, const float Z) noexcept : x{X}, y{Y}, z{Z} {}
template <size_t N>
inline constexpr Vector3D::Vector3D(const float (&XYZ)[N]) noexcept : v{XYZ[0], XYZ[1], XYZ[2]} {
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
inline float& Vector3D::operator[](const size_t Idx) {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
inline float Vector3D::operator[](const size_t Idx) const {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
inline Vector3D& Vector3D::operator+=(const Vector3D& V) noexcept {
    x += V.x;
    y += V.y;
    z += V.z;
    return *this;
}
inline Vector3D& Vector3D::operator-=(const Vector3D& V) noexcept {
    x -= V.x;
    y -= V.y;
    z -= V.z;
    return *this;
}
inline Vector3D& Vector3D::operator*=(const float S) noexcept {
    x *= S;
    y *= S;
    z *= S;
    return *this;
}
inline Vector3D& Vector3D::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Vector4D::

******************************************************************************/
inline constexpr Vector4D::Vector4D(const float X, const float Y, const float Z, const float W) noexcept :
  x{X}, y{Y}, z{Z}, w{W} {}
template <size_t N>
inline constexpr Vector4D::Vector4D(const float (&XYZW)[N]) noexcept : v{XYZW[0], XYZW[1], XYZW[2], XYZW[3]} {
    static_assert(N>=4, "the number of elements in 'XYZW' must be at least 4");
}
template <size_t N>
inline Vector4D& Vector4D::operator=(const float (&XYZW)[N]) noexcept {
    static_assert(N>=4, "the number of elements in 'XYZW' must be at least 4");

    v[0] = XYZW[0];
    v[1] = XYZW[1];
    v[2] = XYZW[2];
    v[3] = XYZW[3];
    return *this;
}
template <class TempTy, class>
inline constexpr Vector4D::Vector4D(const TempTy& Temp) noexcept : v{Temp[0], Temp[1], Temp[2], Temp[3]} {}
template <class TempTy, class>
inline Vector4D& Vector4D::operator=(const TempTy& Temp) noexcept {
    v[0] = Temp[0];
    v[1] = Temp[1];
    v[2] = Temp[2];
    v[3] = Temp[3];
    return *this;
}
inline float& Vector4D::operator[](const size_t Idx) {
    if(Idx>=4) impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}
inline constexpr float Vector4D::operator[](const size_t Idx) const {
    if(Idx>=4) impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}
inline Vector4D& Vector4D::operator+=(const Vector4D& V) noexcept {
    x += V.x;
    y += V.y;
    z += V.z;
    w += V.w;
    return *this;
}
template <class TempTy, class>
inline Vector4D& Vector4D::operator+=(const TempTy& Temp) noexcept {
    x += Temp[0];
    y += Temp[1];
    z += Temp[2];
    w += Temp[3];
    return *this;
}
inline Vector4D& Vector4D::operator-=(const Vector4D& V) noexcept {
    x -= V.x;
    y -= V.y;
    z -= V.z;
    w -= V.w;
    return *this;
}
inline Vector4D& Vector4D::operator*=(const float S) noexcept {
    x *= S;
    y *= S;
    z *= S;
    w *= S;
    return *this;
}
inline Vector4D& Vector4D::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
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
inline Vector3D& Matrix3x3::operator[](const size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix3x3::operator[](const size_t Idx) const {
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
inline Vector4D& Matrix3x4::operator[](const size_t Idx) {
    if(Idx>=3) impl::rangeError("Matrix3x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix3x4::operator[](const size_t Idx) const {
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
inline Vector3D& Matrix4x3::operator[](const size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x3::operator[]");
    return row[Idx];
}
inline const Vector3D& Matrix4x3::operator[](const size_t Idx) const {
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
inline Vector4D& Matrix4x4::operator[](const size_t Idx) {
    if(Idx>=4) impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}
inline const Vector4D& Matrix4x4::operator[](const size_t Idx) const {
    if(Idx>=4) impl::rangeError("Matrix4x4::operator[]");
    return row[Idx];
}

/******************************************************************************

    vector calculation define

******************************************************************************/
  namespace default_operation {
    inline constexpr Vector2D operator+(const Vector2D& L, const Vector2D& R) noexcept {
        return default_operation::vectorAdd(L, R);
    }
    inline constexpr Vector2D vectorAdd(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x+R.x, L.y+R.y};
    }
    inline constexpr Vector2D operator-(const Vector2D& L, const Vector2D& R) noexcept {
        return default_operation::vectorSub(L, R);
    }
    inline constexpr Vector2D vectorSub(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x-R.x, L.y-R.y};
    }
    inline constexpr Vector2D operator*(const Vector2D& L, const float R) noexcept {
        return default_operation::vectorMul(L, R);
    }
    inline constexpr Vector2D vectorMul(const Vector2D& L, const float R) noexcept {
        return Vector2D{L.x*R, L.y*R};
    }
    inline constexpr Vector2D operator/(const Vector2D& L, const float R) {
        return default_operation::vectorDiv(L, R);
    }
    inline constexpr Vector2D vectorDiv(const Vector2D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector2D& L, const Vector2D& R) noexcept {
        return (L.x*R.x) + (L.y*R.y);
    }
    inline constexpr float cross(const Vector2D& L, const Vector2D& R) noexcept {
        return (L.x*R.y) - (L.y*R.x);
    }
    inline constexpr Vector3D operator+(const Vector3D& L, const Vector3D& R) noexcept {
        return default_operation::vectorAdd(L, R);
    }
    inline constexpr Vector3D vectorAdd(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x+R.x, L.y+R.y, L.z+R.z};
    }
    inline constexpr Vector3D operator-(const Vector3D& L, const Vector3D& R) noexcept {
        return default_operation::vectorSub(L, R);
    }
    inline constexpr Vector3D vectorSub(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x-R.x, L.y-R.y, L.z-R.z};
    }
    inline constexpr Vector3D operator*(const Vector3D& L, const float R) noexcept {
        return default_operation::vectorMul(L, R);
    }
    inline constexpr Vector3D vectorMul(const Vector3D& L, const float R) noexcept {
        return Vector3D{L.x*R, L.y*R, L.z*R};
    }
    inline constexpr Vector3D operator/(const Vector3D& L, const float R) {
        return default_operation::vectorDiv(L, R);
    }
    inline constexpr Vector3D vectorDiv(const Vector3D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector3D& L, const Vector3D& R) noexcept {
        return (L.x*R.x) + (L.y*R.y) + (L.z*R.z);
    }
    inline constexpr Vector3D cross(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D {(L.y*R.z) - (L.z*R.y), (L.z*R.x) - (L.x*R.z), (L.x*R.y) - (L.y*R.x)};
    }
    inline constexpr Vector4D operator+(const Vector4D& L, const Vector4D& R) noexcept {
        return default_operation::vectorAdd(L, R);
    }
    inline constexpr Vector4D vectorAdd(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x+R.x, L.y+R.y, L.z+R.z, L.w+R.w};
    }
    inline constexpr Vector4D operator-(const Vector4D& L, const Vector4D& R) noexcept {
        return default_operation::vectorSub(L, R);
    }
    inline constexpr Vector4D vectorSub(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x-R.x, L.y-R.y, L.z-R.z, L.w-R.w};
    }
    inline constexpr Vector4D operator*(const Vector4D& L, const float R) noexcept {
        return default_operation::vectorMul(L, R);
    }
    inline constexpr Vector4D vectorMul(const Vector4D& L, const float R) noexcept {
        return Vector4D{L.x*R, L.y*R, L.z*R, L.w*R};
    }
    inline constexpr Vector4D operator/(const Vector4D& L, const float R) {
        return default_operation::vectorDiv(L, R);
    }
    inline constexpr Vector4D vectorDiv(const Vector4D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
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
  } // namespace default_operation
  namespace default_noncopy_operation {
    template <class LHTy, class RHTy>
    inline constexpr impl::VectorAdd<LHTy, RHTy> vectorAdd(const LHTy& L, const RHTy& R) { 
        return impl::VectorAdd<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr impl::VectorAdd<LHTy, RHTy> operator+(const LHTy& L, const RHTy& R) { 
        return impl::VectorAdd<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr impl::VectorSub<LHTy, RHTy> vectorSub(const LHTy& L, const RHTy& R) {
        return impl::VectorSub<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr impl::VectorSub<LHTy, RHTy> operator-(const LHTy& L, const RHTy& R) {
        return impl::VectorSub<LHTy, RHTy>{L, R};
    }
    template <class LHTy>
    inline constexpr impl::VectorMul<LHTy, float> vectorMul(const LHTy& L, const float R) {
        return impl::VectorMul<LHTy, float>{L, R};
    }
    template <class LHTy>
    inline constexpr impl::VectorMul<LHTy, float> operator*(const LHTy& L, const float R) {
        return impl::VectorMul<LHTy, float>{L, R};
    }
    template <class LHTy>
    inline constexpr impl::VectorMul<LHTy, float> vectorDiv(const LHTy& L, const float R) {
        return impl::VectorMul<LHTy, float>{L, 1.0F/R};
    }
    template <class LHTy>
    inline constexpr impl::VectorMul<LHTy, float> operator/(const LHTy& L, const float R) {
        return impl::VectorMul<LHTy, float>{L, 1.0F/R};
    }
    template <class VectorTy>
    inline constexpr float dot(const VectorTy& L, const VectorTy& R) noexcept {
        return default_operation::dot(L, R);
    }
    inline constexpr float cross(const Vector2D& L, const Vector2D& R) noexcept {
        return default_operation::cross(L, R);
    }
    inline constexpr Vector3D cross(const Vector3D& L, const Vector3D& R) noexcept {
        return default_operation::cross(L, R);
    }
    inline constexpr Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) noexcept {
        return default_operation::cross(V1, V2, V3);
    }
  } // namespace default_noncopy_operation
  namespace simd_operation {
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorAdd(const VectorTy& L, const VectorTy& R) {
        //return DirectX::XMVectorAdd(impl::load(L), impl::load(R));
        return DirectX::XMVectorAdd(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorAdd(DirectX::FXMVECTOR L, const VectorTy& R) {
        //return DirectX::XMVectorAdd(L, impl::load(R));
        return DirectX::XMVectorAdd(L, *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorSub(const VectorTy& L, const VectorTy& R) {
        //return DirectX::XMVectorSubtract(impl::load(L), impl::load(R));
        return DirectX::XMVectorSubtract(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorSub(DirectX::FXMVECTOR L, const VectorTy& R) {
        //return DirectX::XMVectorSubtract(L, impl::load(R));
        return DirectX::XMVectorSubtract(L, *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorMul(const VectorTy& L, const float R) {
        return DirectX::XMVectorMultiply(*reinterpret_cast<const __m128*>(&L), _mm_load1_ps(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorDiv(const VectorTy& L, const float R) {
        return DirectX::XMVectorDivide(*reinterpret_cast<const __m128*>(&L), _mm_load1_ps(&R));
    }
    inline DirectX::XMVECTOR operator+(const Vector2D& L, const Vector2D& R) { return simd_operation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector2D& L, const Vector2D& R) { return simd_operation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector2D& L, const float R) { return simd_operation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector2D& L, const float R) { return simd_operation::vectorDiv(L, R); }
    inline float dot(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Dot(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline float cross(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Cross(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline DirectX::XMVECTOR operator+(const Vector3D& L, const Vector3D& R) { return simd_operation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector3D& L, const Vector3D& R) { return simd_operation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector3D& L, const float R) { return simd_operation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector3D& L, const float R) { return simd_operation::vectorDiv(L, R); }
    inline float dot(const Vector3D& L, const Vector3D& R) {
        return DirectX::XMVector3Dot(impl::load(L), impl::load(R)).m128_f32[0];
    }
    inline Vector3D cross(const Vector3D& L, const Vector3D& R) {
        return Vector3D{DirectX::XMVector3Cross(impl::load(L), impl::load(R)).m128_f32};
    }
    inline DirectX::XMVECTOR operator+(const Vector4D& L, const Vector4D& R) { return simd_operation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator+(DirectX::FXMVECTOR L, const Vector4D& R) { return simd_operation::vectorAdd(L, R); }
    inline DirectX::XMVECTOR operator-(const Vector4D& L, const Vector4D& R) { return simd_operation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator-(DirectX::FXMVECTOR L, const Vector4D& R) { return simd_operation::vectorSub(L, R); }
    inline DirectX::XMVECTOR operator*(const Vector4D& L, const float R) { return simd_operation::vectorMul(L, R); }
    inline DirectX::XMVECTOR operator/(const Vector4D& L, const float R) { return simd_operation::vectorDiv(L, R); }
    inline float dot(const Vector4D& L, const Vector4D& R) {
        //return DirectX::XMVector4Dot(impl::load(L), impl::load(R)).m128_f32[0];
        return DirectX::XMVector4Dot(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R)).m128_f32[0];
    }
    inline Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) {
        //return Vector4D{DirectX::XMVector4Cross(impl::load(V1), impl::load(V2), impl::load(V3)).m128_f32};
        return Vector4D{DirectX::XMVector4Cross(*reinterpret_cast<const __m128*>(&V1),
                                                *reinterpret_cast<const __m128*>(&V2),
                                                *reinterpret_cast<const __m128*>(&V3)).m128_f32};
    }
  } // namespace simd_operation

  namespace impl {
    inline DirectX::XMVECTOR load(const Vector2D& V) { return DirectX::XMVECTOR{V.x, V.y}; }
    inline DirectX::XMVECTOR load(const Vector3D& V) { return DirectX::XMVECTOR{V.x, V.y, V.z}; }
    inline DirectX::XMVECTOR load(const Vector4DA& V) { return _mm_load_ps(V.v); }
  } // namespace impl
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
// EOF
