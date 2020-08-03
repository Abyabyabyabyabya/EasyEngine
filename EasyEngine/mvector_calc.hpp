///
/// \file   mvector_calc.hpp
/// \brief  ベクトル演算定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/8/3
///             - ヘッダ追加
///             - 定義済みベクトル演算移行
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_

#include "mvector.hpp"
#include <DirectXMath.h>

namespace easy_engine {
namespace m_lib {
  namespace vector_impl {
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

    template <class Ty> struct isVector : std::false_type {};
    template <> struct isVector<Vector2D> : std::true_type {};
    template <> struct isVector<Vector3D> : std::true_type {};
    template <> struct isVector<Vector4D> : std::true_type {};
    template <class LhTy, class RhTy> struct isVector<VectorAdd<LhTy, RhTy>> : std::true_type {};
    template <class LhTy, class RhTy> struct isVector<VectorSub<LhTy, RhTy>> : std::true_type {};
    template <class LhTy, class RhTy> struct isVector<VectorMul<LhTy, RhTy>> : std::true_type {};
    template <class Ty>
    constexpr bool kIsVector = isVector<Ty>::value;

    DirectX::XMVECTOR load(const Vector2D&);
    DirectX::XMVECTOR load(const Vector3D&);
    DirectX::XMVECTOR load(const Vector4D&);
  } // namespace vector_impl

/******************************************************************************

    vector calculation

******************************************************************************/
  namespace default_operation {
    inline constexpr Vector2D vectorAdd(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x+R.x, L.y+R.y};
    }
    inline constexpr Vector2D vectorSub(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L.x-R.x, L.y-R.y};
    }
    inline constexpr Vector2D vectorMul(const Vector2D& L, const float R) noexcept {
        return Vector2D{L.x*R, L.y*R};
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
    inline constexpr Vector3D vectorAdd(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x+R.x, L.y+R.y, L.z+R.z};
    }
    inline constexpr Vector3D vectorSub(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L.x-R.x, L.y-R.y, L.z-R.z};
    }
    inline constexpr Vector3D vectorMul(const Vector3D& L, const float R) noexcept {
        return Vector3D{L.x*R, L.y*R, L.z*R};
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
    inline constexpr Vector4D vectorAdd(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x+R.x, L.y+R.y, L.z+R.z, L.w+R.w};
    }
    inline constexpr Vector4D vectorSub(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L.x-R.x, L.y-R.y, L.z-R.z, L.w-R.w};
    }
    inline constexpr Vector4D vectorMul(const Vector4D& L, const float R) noexcept {
        return Vector4D{L.x*R, L.y*R, L.z*R, L.w*R};
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
    template <class VectorTy>
    inline constexpr std::enable_if_t<vector_impl::kIsVector<VectorTy>, VectorTy> 
      operator+(const VectorTy& L, const VectorTy& R) noexcept {
        return default_operation::vectorAdd(L, R);
    }
    template <class VectorTy>
    inline constexpr std::enable_if_t<vector_impl::kIsVector<VectorTy>, VectorTy>
      operator-(const VectorTy& L, const VectorTy& R) noexcept {
        return default_operation::vectorSub(L, R);
    }
    template <class VectorTy>
    inline constexpr std::enable_if_t<vector_impl::kIsVector<VectorTy>, VectorTy>
      operator*(const VectorTy& L, const float R) noexcept {
        return default_operation::vectorMul(L, R);
    }
    template <class VectorTy>
    inline constexpr std::enable_if_t<vector_impl::kIsVector<VectorTy>, VectorTy>
      operator/(const VectorTy& L, const float R) noexcept {
        return default_operation::vectorDiv(L, R);
    }
  } // namespace default_operation
  namespace default_noncopy_operation {
    template <class LHTy, class RHTy>
    inline constexpr vector_impl::VectorAdd<LHTy, RHTy> vectorAdd(const LHTy& L, const RHTy& R) { 
        return vector_impl::VectorAdd<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr vector_impl::VectorAdd<LHTy, RHTy> operator+(const LHTy& L, const RHTy& R) { 
        return vector_impl::VectorAdd<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr vector_impl::VectorSub<LHTy, RHTy> vectorSub(const LHTy& L, const RHTy& R) {
        return vector_impl::VectorSub<LHTy, RHTy>{L, R};
    }
    template <class LHTy, class RHTy>
    inline constexpr vector_impl::VectorSub<LHTy, RHTy> operator-(const LHTy& L, const RHTy& R) {
        return vector_impl::VectorSub<LHTy, RHTy>{L, R};
    }
    template <class LHTy>
    inline constexpr vector_impl::VectorMul<LHTy, float> vectorMul(const LHTy& L, const float R) {
        return vector_impl::VectorMul<LHTy, float>{L, R};
    }
    template <class LHTy>
    inline constexpr vector_impl::VectorMul<LHTy, float> operator*(const LHTy& L, const float R) {
        return vector_impl::VectorMul<LHTy, float>{L, R};
    }
    template <class LHTy>
    inline constexpr vector_impl::VectorMul<LHTy, float> vectorDiv(const LHTy& L, const float R) {
        return vector_impl::VectorMul<LHTy, float>{L, 1.0F/R};
    }
    template <class LHTy>
    inline constexpr vector_impl::VectorMul<LHTy, float> operator/(const LHTy& L, const float R) {
        return vector_impl::VectorMul<LHTy, float>{L, 1.0F/R};
    }
  } // namespace default_noncopy_operation
  namespace simd_operation {
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorAdd(const VectorTy& L, const VectorTy& R) {
        return DirectX::XMVectorAdd(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorAdd(DirectX::FXMVECTOR L, const VectorTy& R) {
        return DirectX::XMVectorAdd(L, *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorSub(const VectorTy& L, const VectorTy& R) {
        return DirectX::XMVectorSubtract(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R));
    }
    template <class VectorTy>
    inline DirectX::XMVECTOR vectorSub(DirectX::FXMVECTOR L, const VectorTy& R) {
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
    template <class LhTy, class RhTy>
    inline DirectX::XMVECTOR operator+(const LhTy& L, const RhTy& R) {
        return simd_operation::vectorAdd(L, R);
    }
    template <class LhTy, class RhTy>
    inline DirectX::XMVECTOR operator-(const LhTy& L, const RhTy& R) {
        return simd_operation::vectorSub(L, R); }
    template <class LhTy>
    inline DirectX::XMVECTOR operator*(const LhTy& L, const float R) { return simd_operation::vectorMul(L, R);
    }
    template <class LhTy>
    inline DirectX::XMVECTOR operator/(const LhTy& L, const float R) {
        return simd_operation::vectorDiv(L, R);
    }
    inline float dot(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Dot(vector_impl::load(L), vector_impl::load(R)).m128_f32[0];
    }
    inline float cross(const Vector2D& L, const Vector2D& R) {
        return DirectX::XMVector2Cross(vector_impl::load(L), vector_impl::load(R)).m128_f32[0];
    }
    inline float dot(const Vector3D& L, const Vector3D& R) {
        return DirectX::XMVector3Dot(vector_impl::load(L), vector_impl::load(R)).m128_f32[0];
    }
    inline Vector3D cross(const Vector3D& L, const Vector3D& R) {
        return Vector3D{DirectX::XMVector3Cross(vector_impl::load(L), vector_impl::load(R)).m128_f32};
    }
    inline float dot(const Vector4D& L, const Vector4D& R) {
        return DirectX::XMVector4Dot(*reinterpret_cast<const __m128*>(&L), *reinterpret_cast<const __m128*>(&R)).m128_f32[0];
    }
    inline Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) {
        return Vector4D{DirectX::XMVector4Cross(*reinterpret_cast<const __m128*>(&V1),
                                                *reinterpret_cast<const __m128*>(&V2),
                                                *reinterpret_cast<const __m128*>(&V3)).m128_f32};
    }
  } // namespace simd_operation

  namespace vector_impl {
    inline DirectX::XMVECTOR load(const Vector2D& V) { return DirectX::XMVECTOR{V.x, V.y}; }
    inline DirectX::XMVECTOR load(const Vector3D& V) { return DirectX::XMVECTOR{V.x, V.y, V.z}; }
    inline DirectX::XMVECTOR load(const Vector4DA& V) { return _mm_load_ps(V.v); }
  } // namespace vector_impl
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_
// EOF
