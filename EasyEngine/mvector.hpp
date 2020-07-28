///
/// \file   mvector.hpp
/// \brief  �Z�p�p���l�R���e�i�Q��`�w�b�_
///
///         �R���e�i�̓R���p�C�����萔(constexpr)�ɂȂ邱�Ƃ��ł��܂��B
///         �R���p�C�����̃x�N�g�����Z�A�s�񉉎Z���ꕔ�T�|�[�g���Ă��܂����A�f�t�H���g�ł͎g�p�ł��܂���B
///         �g�p����ɂ́Aegeg::m_lib::compile_time_calculation ���O��Ԃ𖾎��I�Ɏw�肷�邩�A
///         ���̃w�b�_���C���N���[�h���钼�O�� EGEG_MLIB_USE_COMPILE_TIME_CALCULATION �}�N�����`���Ă��������B
///
/// \attention ���O��Ԃ𖾎��I�Ɏw�肷����@�ł͂Ȃ��A�}�N�����`���ăR���p�C�����v�Z�֐����g�p�����ꍇ�A
///            ����ȍ~�̊֐��Ăяo�����S�ăR���p�C�����v�Z�p�̂��̂ɂȂ�܂��B\n
///            �ȏ�̗��R����A�w�b�_�ł̃}�N����`���s���Ă͂����܂���B\n
///            �}�N�����`����.cpp�t�@�C���ŁA���x�d���̎��s���p�֐����Ăяo�������ꍇ�́A
///            egeg::m_lib::run_time_calculation���O��Ԃɂ��铯�ꖼ�̊֐����g�p���Ă��������B\n
///            �ccompile_time_calculation���O��ԁA�y�сcrun_time_calculation���O��Ԃ�using�錾���s���Ă͂����܂���B
///
/// \author ��
///
/// \par    ����
///         - 2020/7/28
///             - �w�b�_�ǉ�
///             - VectorND ��`
///             - MatrixMxN ��`
///             - �x�N�g�����Z�v���g�^�C�v�錾(���x�d�����s���p�A�R���p�C�����v�Z�p)
///
/// \note   ���s���p���O��ԁA�R���p�C�����p���O��Ԃɂ���\n
///         ���X�͎��s���p���O��Ԃ͎w�肵�Ȃ��Ă��ǂ��悤�ɂ��Ă������A\n
///         using namespace egeg::m_lib;�@�Ƃ�����\n
///         using namespace egeg::m_lib::compile_time_calculation;\n
///         �Ƃ��ăR���p�C�����p�֐����Ăяo�����Ƃ����Ƃ��ɁA
///         ADL�ɂ��crun_time_calculation���O��Ԃ������̑ΏۂƂȂ�A�I�[�o�[���[�h�������B���ɂȂ��肪�����������߁A
///         ����(2020/7/28)�̌`�ɂȂ����B
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
#else
  inline namespace run_time_calculation {}
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

    constexpr float& operator[](size_t Index);
    Vector2D& operator+=(const Vector2D&) noexcept;
    Vector2D& operator-=(const Vector2D&) noexcept;
    Vector2D& operator*=(float) noexcept;
    Vector2D& operator/=(float) noexcept;
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
    template <size_t N> constexpr Vector3D(const float (&XYZ)[N]) noexcept;
    template <size_t N> Vector3D& operator=(const float (&XYZ)[N]) noexcept;

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
    template <size_t N> constexpr Vector4D(const float (&XYZW)[N]) noexcept;
    template <size_t N> Vector4D& operator=(const float (&XYZW)[N]) noexcept;

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

    vector calculation

******************************************************************************/
  namespace run_time_calculation {
    Vector2D operator+(const Vector2D&, const Vector2D&);
    Vector2D vectorAdd(const Vector2D&, const Vector2D&);
    Vector2D operator-(const Vector2D&, const Vector2D&);
    Vector2D vectorSub(const Vector2D&, const Vector2D&);
    Vector2D operator*(const Vector2D&, float);
    Vector2D vectorMul(const Vector2D&, float);
    Vector2D operator/(const Vector2D&, float);
    Vector2D vectorDiv(const Vector2D&, float);
    float dot(const Vector2D&, const Vector2D&);
    float cross(const Vector2D&, const Vector2D&);
    Vector3D operator+(const Vector3D&, const Vector3D&);
    Vector3D vectorAdd(const Vector3D&, const Vector3D&);
    Vector3D operator-(const Vector3D&, const Vector3D&);
    Vector3D vectorSub(const Vector3D&, const Vector3D&);
    Vector3D operator*(const Vector3D&, float);
    Vector3D vectorMul(const Vector3D&, float);
    Vector3D operator/(const Vector3D&, float);
    Vector3D vectorDiv(const Vector3D&, float);
    float dot(const Vector3D&, const Vector3D&);
    Vector3D cross(const Vector3D&, const Vector3D&);
    Vector4D operator+(const Vector4D&, const Vector4D&);
    Vector4D vectorAdd(const Vector4D&, const Vector4D&);
    Vector4D operator-(const Vector4D&, const Vector4D&);
    Vector4D vectorSub(const Vector4D&, const Vector4D&);
    Vector4D operator*(const Vector4D&, float);
    Vector4D vectorMul(const Vector4D&, float);
    Vector4D operator/(const Vector4D&, float);
    Vector4D vectorDiv(const Vector4D&, float);
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
    constexpr Vector2D operator/(const Vector2D&, float) noexcept;
    constexpr Vector2D vectorDiv(const Vector2D&, float) noexcept;
    constexpr float dot(const Vector2D&, const Vector2D&) noexcept;
    constexpr float cross(const Vector2D&, const Vector2D&) noexcept;
    constexpr Vector3D vectorAdd(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector3D vectorSub(const Vector3D& ,const Vector3D&) noexcept;
    constexpr Vector3D vectorMul(const Vector3D&, float) noexcept;
    constexpr Vector3D vectorDiv(const Vector3D&, float) noexcept;
    constexpr float dot(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector3D cross(const Vector3D&, const Vector3D&) noexcept;
    constexpr Vector4D vectorAdd(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D vectorSub(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D vectorMul(const Vector4D&, float) noexcept;
    constexpr Vector4D vectorDiv(const Vector4D&, float) noexcept;
    constexpr float dot(const Vector4D&, const Vector4D&) noexcept;
    constexpr Vector4D cross(const Vector4D&, const Vector4D&, const Vector4D&) noexcept;
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
inline constexpr float& Vector2D::operator[](size_t Idx) {
    if(Idx>=2) impl::rangeError("Vector2D::operatorp[]");
    return v[Idx];
}
inline Vector2D& Vector2D::operator+=(const Vector2D& V) noexcept {
    using namespace DirectX;
    *this = XMVectorAdd(impl::load(*this), impl::load(V)).m128_f32;
    return *this;
}
inline Vector2D& Vector2D::operator-=(const Vector2D& V) noexcept {
    using namespace DirectX;
    auto res = XMVectorSubtract(impl::load(*this), impl::load(V)).m128_f32;
    return *this;
}
inline Vector2D& Vector2D::operator*=(const float S) noexcept {
    using namespace DirectX;
    *this = XMVectorMultiply(impl::load(*this), XMVectorReplicate(S)).m128_f32;
    return *this;
}
inline Vector2D& Vector2D::operator/=(const float S) noexcept {
    using namespace DirectX;
    *this = XMVectorDivide(impl::load(*this), XMVectorReplicate(S)).m128_f32;
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
inline constexpr float& Vector3D::operator[](size_t Idx) {
    if(Idx>=3) impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}

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

  namespace impl {
    inline DirectX::XMVECTOR load(const Vector2D& V) { return DirectX::XMVECTOR{V.x, V.y}; }
    inline DirectX::XMVECTOR load(const Vector3D& V) { return DirectX::XMVECTOR{V.x, V.y, V.z}; }
    inline DirectX::XMVECTOR load(const Vector4D& V) { return DirectX::XMVECTOR{V.x, V.y, V.z, V.w}; }
  }

} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
// EOF
