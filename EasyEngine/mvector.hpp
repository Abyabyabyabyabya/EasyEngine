///
/// \file   mvector.hpp
/// \brief  �Z�p�p���l�R���e�i�Q��`�w�b�_
///
///         �R���e�i�̓R���p�C�����萔(constexpr)�ɂȂ邱�Ƃ��ł��܂��B
///         ���Z�ɂ͕����̏������قȂ�֐����g�p���邱�Ƃ��ł��܂��B
///         ���̃w�b�_���C���N���[�h���钼�O�ŁA
///         EGEG_MLIB_USE_SIMD_OPERATION�}�N�����`����ƁASIMD���Z���s���֐����I������܂��B
///         EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATION�}�N�����`����ƁA�v�Z���ʂ�ۑ�����ꎞ�I�u�W�F�N�g�𐶐����Ȃ�
///         �֐����I������܂��B
///         ���ɉ������Ȃ���΃f�t�H���g�̊֐����w�肳��܂��B
///         �R���p�C�����̃x�N�g�����Z�A�s�񉉎Z���ꕔ�T�|�[�g���Ă��܂����ASIMD���Z���s���֐��ł̓T�|�[�g���Ă��܂���B
///
/// \attention ���O��Ԃ𖾎��I�Ɏw�肷����@�ł͂Ȃ��A�}�N�����`����
///            �g�p����֐���I�������ꍇ�A����ȍ~�̊֐��Ăяo�����S�Ă��̃}�N���ɂ��I���������̂ɂȂ�܂��B\n
///            �ȏ�̗��R����A�w�b�_�ł̃}�N����`���s���Ă͂����܂���B\n
///            �}�N�����`����.cpp�t�@�C���ŁA�قȂ��ނ̊֐����Ăяo�������ꍇ�́A
///            �s�x���O��Ԃ𖾎��I�ɏC�����Ċ֐���I�����Ă��������B\n
///            egeg::m_lib::default_operation�Aegeg::m_lib::default_noncopy_operation�y��egeg::m_lib::simd_operation
///            ���O��Ԃ�using�錾�ɂ��ȗ����Ă͂����܂���B
///
/// \author ��
///
/// \par    ����
///         - 2020/7/28
///             - �w�b�_�ǉ�
///             - VectorND ��`
///             - MatrixMxN ��`
///             - �x�N�g�����Z�v���g�^�C�v�錾(���x�d�����s���p�A�R���p�C�����v�Z�p)
///         - 2020/8/3
///             - �s�񉉎Z�ǉ�
///             - �w�b�_����
///
/// \note   ���O��Ԃɂ���\n
///         �K����̖��O��Ԃ𖾎��I�Ȏw��Ȃ��őI���ł���悤�ɂ��Ă���̂ŁA
///         ���̎��̃f�t�H���g�ł͂Ȃ����O��Ԃ�using�錾�ɂ��ȗ��ł���悤�ɂ����
///         �I�[�o�[���[�h�������B���ɂȂ��Ă��܂��B
///         default_noncopy_operation�̊֐��Q�ɂ���\n
///         �x���]���ɂ��e���|�����I�u�W�F�N�g�̐�����}�����Ă��邪�A
///         default_operation�̊֐��Q�ł��R���p�C���ɂ��œK���œ����悤�Ȍ��ʂ����҂ł���B
///         ���s���v�Z�p�֐��ɂ���\n
///         ��肭�����Ă��Ȃ��B�f�t�H���g�ł͎g�p�ł��Ȃ��悤�ɂ��Ă���B\n
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_HEADER_

#include <cstddef>
#include <stdexcept>

namespace easy_engine {
namespace m_lib {
  namespace vector_impl {
    [[noreturn]] void rangeError(std::string&& Func) {
        throw std::logic_error("out-of-range access detected. func: "+Func);
    }
  } // namespace vector_impl

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
    template <class Ty, class=std::enable_if_t<Ty::kDimension==kDimension>>
    constexpr Vector2D(const Ty&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector2D&> operator=(const Ty&) noexcept;

    float& operator[](size_t Index);
    constexpr float operator[](size_t Index) const;
    Vector2D& operator+=(const Vector2D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector2D&> operator+=(const Ty&) noexcept;
    Vector2D& operator-=(const Vector2D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector2D&> operator-=(const Ty&) noexcept;
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
    template <class Ty, class=std::enable_if_t<Ty::kDimension==kDimension>>
    constexpr Vector3D(const Ty&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector3D&> operator=(const Ty&) noexcept;

    float& operator[](size_t Index);
    constexpr float operator[](size_t Index) const;
    Vector3D& operator+=(const Vector3D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector3D&> operator+=(const Ty&) noexcept;
    Vector3D& operator-=(const Vector3D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector3D&> operator-=(const Ty&) noexcept;
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
    template <class Ty, class=std::enable_if_t<Ty::kDimension==kDimension>>
    constexpr Vector4D(const Ty&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector4D&> operator=(const Ty&) noexcept;

    float& operator[](size_t Index);
    constexpr float operator[](size_t Index) const;
    Vector4D& operator+=(const Vector4D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector4D&> operator+=(const Ty&) noexcept;
    Vector4D& operator-=(const Vector4D&) noexcept;
    template <class Ty>
    std::enable_if_t<Ty::kDimension==kDimension, Vector4D&> operator-=(const Ty&) noexcept;
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

    Vector2D::

******************************************************************************/
inline constexpr Vector2D::Vector2D(const float X, const float Y) noexcept : v{X, Y} {}
template <size_t N>
inline constexpr Vector2D::Vector2D(const float (&XY)[N]) noexcept : v{XY[0], XY[1]} {
    static_assert(N>=2, "'XY' must have at least two elements");
}
template <size_t N>
inline Vector2D& Vector2D::operator=(const float (&XY)[N]) noexcept {
    static_assert(N>=2, "'XY' must have at least two elements");

    v[0] = XY[0];
    v[1] = XY[1];
    return *this;
}
template <class Ty, class>
inline constexpr Vector2D::Vector2D(const Ty& Temp) noexcept : v{Temp[0], Temp[1]} {}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector2D::kDimension, Vector2D&>
  Vector2D::operator=(const Ty& Temp) noexcept {
    v[0] = Temp[0];
    v[1] = Temp[1];
    return *this;
}
inline float& Vector2D::operator[](const size_t Idx) {
    if(Idx>=2) vector_impl::rangeError("Vector2D::operatorp[]");
    return v[Idx];
}
inline constexpr float Vector2D::operator[](const size_t Idx) const {
    if(Idx>=2) vector_impl::rangeError("Vector2D::operator[]");
    return v[Idx];
}
inline Vector2D& Vector2D::operator+=(const Vector2D& V) noexcept {
    v[0] += V.v[0];
    v[1] += V.v[1];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector2D::kDimension, Vector2D&>
  Vector2D::operator+=(const Ty& Temp) noexcept {
    v[0] += Temp[0];
    v[1] += Temp[1];
    return *this;
}
inline Vector2D& Vector2D::operator-=(const Vector2D& V) noexcept {
    v[0] -= V.v[0];
    v[1] -= V.v[1];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector2D::kDimension, Vector2D&>
  Vector2D::operator-=(const Ty& Temp) noexcept {
    v[0] -= Temp[0];
    v[1] -= Temp[1];
    return *this;
}
inline Vector2D& Vector2D::operator*=(const float S) noexcept {
    v[0] *= S;
    v[1] *= S;
    return *this;
}
inline Vector2D& Vector2D::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Vector3D::

******************************************************************************/
inline constexpr Vector3D::Vector3D(const float X, const float Y, const float Z) noexcept : v{X, Y, Z} {}
template <size_t N>
inline constexpr Vector3D::Vector3D(const float (&XYZ)[N]) noexcept : v{XYZ[0], XYZ[1], XYZ[2]} {
    static_assert(N>=3, "'XYZ' must have at least three elements");
}
template <size_t N>
inline Vector3D& Vector3D::operator=(const float (&XYZ)[N]) noexcept {
    static_assert(N>=3, "'XYZ' must have at least three elements");

    v[0] = XYZ[0];
    v[1] = XYZ[1];
    v[2] = XYZ[2];
    return *this;
}
template <class Ty, class>
inline constexpr Vector3D::Vector3D(const Ty& Temp) noexcept : v{Temp[0], Temp[1], Temp[2]} {}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector3D::kDimension, Vector3D&>
  Vector3D::operator=(const Ty& Temp) noexcept {
    v[0] = Temp[0];
    v[1] = Temp[1];
    v[2] = Temp[2];
    return *this;
}
inline float& Vector3D::operator[](const size_t Idx) {
    if(Idx>=3) vector_impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
inline constexpr float Vector3D::operator[](const size_t Idx) const {
    if(Idx>=3) vector_impl::rangeError("Vector3D::operator[]");
    return v[Idx];
}
inline Vector3D& Vector3D::operator+=(const Vector3D& V) noexcept {
    v[0] += V.v[0];
    v[1] += V.v[1];
    v[2] += V.v[2];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector3D::kDimension, Vector3D&>
  Vector3D::operator+=(const Ty& Temp) noexcept {
    v[0] += Temp[0];
    v[1] += Temp[1];
    v[2] += Temp[2];
    return *this;
}
inline Vector3D& Vector3D::operator-=(const Vector3D& V) noexcept {
    v[0] -= V.v[0];
    v[1] -= V.v[1];
    v[2] -= V.v[2];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector3D::kDimension, Vector3D&>
  Vector3D::operator-=(const Ty& Temp) noexcept {
    v[0] -= Temp[0];
    v[1] -= Temp[1];
    v[2] -= Temp[2];
    return *this;
}
inline Vector3D& Vector3D::operator*=(const float S) noexcept {
    v[0] *= S;
    v[1] *= S;
    v[2] *= S;
    return *this;
}
inline Vector3D& Vector3D::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}

/******************************************************************************

    Vector4D::

******************************************************************************/
inline constexpr Vector4D::Vector4D(const float X, const float Y, const float Z, const float W) noexcept : v{X,Y,Z,W}{}
template <size_t N>
inline constexpr Vector4D::Vector4D(const float (&XYZW)[N]) noexcept : v{XYZW[0], XYZW[1], XYZW[2], XYZW[3]} {
    static_assert(N>=4, "'XYZW' must have at least four elements");
}
template <size_t N>
inline Vector4D& Vector4D::operator=(const float (&XYZW)[N]) noexcept {
    static_assert(N>=4, "'XYZW' must have at least four elements");

    v[0] = XYZW[0];
    v[1] = XYZW[1];
    v[2] = XYZW[2];
    v[3] = XYZW[3];
    return *this;
}
template <class Ty, class>
inline constexpr Vector4D::Vector4D(const Ty& Temp) noexcept : v{Temp[0], Temp[1], Temp[2], Temp[3]} {}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector4D::kDimension, Vector4D&>
  Vector4D::operator=(const Ty& Temp) noexcept {
    v[0] = Temp[0];
    v[1] = Temp[1];
    v[2] = Temp[2];
    v[3] = Temp[3];
    return *this;
}
inline float& Vector4D::operator[](const size_t Idx) {
    if(Idx>=4) vector_impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}
inline constexpr float Vector4D::operator[](const size_t Idx) const {
    if(Idx>=4) vector_impl::rangeError("Vector4D::operator[]");
    return v[Idx];
}
inline Vector4D& Vector4D::operator+=(const Vector4D& V) noexcept {
    v[0] += V.v[0];
    v[1] += V.v[1];
    v[2] += V.v[2];
    v[3] += V.v[3];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector4D::kDimension, Vector4D&>
  Vector4D::operator+=(const Ty& Temp) noexcept {
    v[0] += Temp[0];
    v[1] += Temp[1];
    v[2] += Temp[2];
    v[3] += Temp[3];
    return *this;
}
inline Vector4D& Vector4D::operator-=(const Vector4D& V) noexcept {
    v[0] -= V.v[0];
    v[1] -= V.v[1];
    v[2] -= V.v[2];
    v[3] -= V.v[3];
    return *this;
}
template <class Ty>
inline std::enable_if_t<Ty::kDimension==Vector4D::kDimension, Vector4D&>
  Vector4D::operator-=(const Ty& Temp) noexcept {
    v[0] -= Temp[0];
    v[1] -= Temp[1];
    v[2] -= Temp[2];
    v[3] -= Temp[3];
    return *this;
}
Vector4D& Vector4D::operator*=(const float S) noexcept {
    v[0] *= S;
    v[1] *= S;
    v[2] *= S;
    v[3] *= S;
    return *this;
}
inline Vector4D& Vector4D::operator/=(const float S) noexcept {
    return *this *= 1.0F/S;
}
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_HEADER_
// EOF
