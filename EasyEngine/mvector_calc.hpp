///
/// \file   mvector_calc.hpp
/// \brief  ベクトル演算定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/3
///             - ヘッダ追加
///             - 定義済みベクトル演算移行
///
#ifndef INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_
#define INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_

#include <DirectXMath.h>
#include "mvector.hpp"

namespace easy_engine {
namespace m_lib {
  namespace vector_impl {
    template <size_t Dimension> struct Vector{};
    template <> struct Vector<2U> { using Type = Vector2D; };
    template <> struct Vector<3U> { using Type = Vector3D; };
    template <> struct Vector<4U> { using Type = Vector4D; };
    template <size_t Dimension> using VectorType = typename Vector<Dimension>::Type;

    template <class Ty> struct IsVector : std::false_type {};
    template <> struct IsVector<Vector2D> : std::true_type {};
    template <> struct IsVector<Vector3D> : std::true_type {};
    template <> struct IsVector<Vector4D> : std::true_type {};

    template <class LTy, class RTy>
    struct IsSameDimension {
        static constexpr bool value = LTy::kDimension==RTy::kDimension;
    };

  #define EGEG_MLIB_DEFINE_VECTOR_NONCOPY_OPERATOR(OpType, Op)\
    template <class LTy, class RTy, class=std::enable_if_t<IsVector<LTy>::value&&IsVector<RTy>::value>>\
    class Vector##OpType {\
    public :\
        static_assert(LTy::kDimension==RTy::kDimension, "the dimension of 'LTy' and 'RTy' must be the same");\
        static constexpr size_t kDimension = LTy::kDimension;\
        constexpr Vector##OpType(const LTy& L, const RTy& R) noexcept : l_{L}, r_{R} {}\
        constexpr float operator[](const size_t I) const {\
            if(I>=kDimension) rangeError("VectorOperator::operator[]");\
            return l_[I] Op r_[I];\
        }\
    private :\
        const LTy& l_;\
        const RTy& r_;\
    };\
    template <class LTy>\
    class Vector##OpType<LTy, float> {\
    public :\
        static constexpr size_t kDimension = LTy::kDimension;\
        constexpr Vector##OpType(const LTy& L, const float R) noexcept : l_{L}, r_{R} {}\
        constexpr float operator[](const size_t I) const {\
            if(I>=kDimension) rangeError("VectorOperator::operator[]");\
            return l_[I] Op r_;\
        }\
    private :\
        const LTy& l_;\
        const float r_;\
    }
    
    EGEG_MLIB_DEFINE_VECTOR_NONCOPY_OPERATOR(Add, +);
    EGEG_MLIB_DEFINE_VECTOR_NONCOPY_OPERATOR(Sub, -);
    EGEG_MLIB_DEFINE_VECTOR_NONCOPY_OPERATOR(Mul, *);
    template <class LTy, class RTy, class=std::enable_if_t<IsSameDimension<LTy, RTy>::value&&LTy::kDimension==3U>>
    class Vector3DCross {
    public :
        static constexpr size_t kDimension = Vector3D::kDimension;
        constexpr Vector3DCross(const LTy& L, const RTy& R) : l_{L}, r_{R} {}
        constexpr float operator[](const size_t I) const {
            if(I>=kDimension) rangeError("Vector3D::cross-product");
            const size_t first = circulation(I+1);
            const size_t second = circulation(first+1);
            return (l_[first]*r_[second]) - (l_[second]*r_[first]);
        }
    private :
        constexpr size_t circulation(const size_t N) const noexcept { return N>=kDimension ? 0 : N; }
        const LTy& l_;
        const RTy& r_;
    };
    template <class LhTy, class RhTy> struct IsVector<VectorAdd<LhTy, RhTy>> : std::true_type {};
    template <class LhTy, class RhTy> struct IsVector<VectorSub<LhTy, RhTy>> : std::true_type {};
    template <class LhTy, class RhTy> struct IsVector<VectorMul<LhTy, RhTy>> : std::true_type {};
    template <class Ty>
    constexpr bool kIsVector = IsVector<Ty>::value;


    DirectX::XMVECTOR load(const Vector2D&);
    DirectX::XMVECTOR load(const Vector3D&);
    DirectX::XMVECTOR load(const Vector4D&);
  } // namespace vector_impl

/******************************************************************************

    vector calculation

******************************************************************************/
  namespace default_operation {
    inline constexpr Vector2D vectorAdd(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L[0]+R[0], L[1]+R[1]};
    }
    inline constexpr Vector2D vectorSub(const Vector2D& L, const Vector2D& R) noexcept {
        return Vector2D{L[0]-R[0], L[1]-R[1]};
    }
    inline constexpr Vector2D vectorMul(const Vector2D& L, const float R) noexcept {
        return Vector2D{L[0]*R, L[1]*R};
    }
    inline constexpr Vector2D vectorDiv(const Vector2D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector2D& L, const Vector2D& R) noexcept {
        return (L[0]*R[0]) + (L[1]*R[1]);
    }
    inline constexpr float cross(const Vector2D& L, const Vector2D& R) noexcept {
        return (L[0]*R[1]) - (L[1]*R[0]);
    }
    inline constexpr Vector3D vectorAdd(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L[0]+R[0], L[1]+R[1], L[2]+R[2]};
    }
    inline constexpr Vector3D vectorSub(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D{L[0]-R[0], L[1]-R[1], L[2]-R[2]};
    }
    inline constexpr Vector3D vectorMul(const Vector3D& L, const float R) noexcept {
        return Vector3D{L[0]*R, L[1]*R, L[2]*R};
    }
    inline constexpr Vector3D vectorDiv(const Vector3D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector3D& L,const Vector3D& R)noexcept{
        return (L[0]*R[0]) + (L[1]*R[1]) + (L[2]*R[2]);
    }
    inline constexpr Vector3D cross(const Vector3D& L, const Vector3D& R) noexcept {
        return Vector3D {(L[1]*R[2]) - (L[2]*R[1]), (L[2]*R[0]) - (L[0]*R[2]), (L[0]*R[1]) - (L[1]*R[0])};
    }
    inline constexpr Vector4D vectorAdd(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L[0]+R[0], L[1]+R[1], L[2]+R[2], L[3]+R[3]};
    }
    inline constexpr Vector4D vectorSub(const Vector4D& L, const Vector4D& R) noexcept {
        return Vector4D{L[0]-R[0], L[1]-R[1], L[2]-R[2], L[3]-R[3]};
    }
    inline constexpr Vector4D vectorMul(const Vector4D& L, const float R) noexcept {
        return Vector4D{L[0]*R, L[1]*R, L[2]*R, L[3]*R};
    }
    inline constexpr Vector4D vectorDiv(const Vector4D& L, const float R) {
        return default_operation::vectorMul(L, 1.0F/R);
    }
    inline constexpr float dot(const Vector4D& L, const Vector4D& R) noexcept {
        return (L[0]*R[0]) + (L[1]*R[1]) + (L[2]*R[2]) + (L[3]*R[3]);
    }
    // 参考 : https://docs.microsoft.com/en-us/windows/win32/api/directxmath/nf-directxmath-xmvector4cross
    inline constexpr Vector4D cross(const Vector4D& V1, const Vector4D& V2, const Vector4D& V3) noexcept {
        return Vector4D {
            V1[1]*(V2[2]*V3[3]-V3[2]*V2[3]) - V1[2]*(V2[1]*V3[3]-V3[1]*V2[3]) + V1[3]*(V2[1]*V3[2]-V3[1]*V2[2]),
            V1[0]*(V3[2]*V2[3]-V2[2]*V3[3]) - V1[2]*(V3[0]*V2[3]-V2[0]*V3[3]) + V1[3]*(V3[0]*V2[2]-V2[0]*V3[2]),
            V1[0]*(V2[1]*V3[3]-V3[1]*V2[3]) - V1[1]*(V2[0]*V3[3]-V3[0]*V2[3]) + V1[3]*(V2[0]*V3[1]-V3[0]*V2[1]),
            V1[0]*(V3[1]*V2[2]-V2[1]*V3[2]) - V1[1]*(V3[0]*V2[2]-V2[0]*V3[2]) + V1[2]*(V3[0]*V2[1]-V2[0]*V3[1])
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
    template <class LhTy, class RhTy>
    inline constexpr vector_impl::VectorAdd<LhTy, RhTy> vectorAdd(const LhTy& L, const RhTy& R) { 
        return vector_impl::VectorAdd<LhTy, RhTy>{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr vector_impl::VectorAdd<LhTy, RhTy> operator+(const LhTy& L, const RhTy& R) { 
        return vector_impl::VectorAdd<LhTy, RhTy>{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr vector_impl::VectorSub<LhTy, RhTy> vectorSub(const LhTy& L, const RhTy& R) {
        return vector_impl::VectorSub<LhTy, RhTy>{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr vector_impl::VectorSub<LhTy, RhTy> operator-(const LhTy& L, const RhTy& R) {
        return vector_impl::VectorSub<LhTy, RhTy>{L, R};
    }
    template <class LhTy>
    inline constexpr vector_impl::VectorMul<LhTy, float> vectorMul(const LhTy& L, const float R) {
        return vector_impl::VectorMul<LhTy, float>{L, R};
    }
    template <class LhTy>
    inline constexpr vector_impl::VectorMul<LhTy, float> operator*(const LhTy& L, const float R) {
        return vector_impl::VectorMul<LhTy, float>{L, R};
    }
    template <class LhTy>
    inline constexpr vector_impl::VectorMul<LhTy, float> vectorDiv(const LhTy& L, const float R) {
        return vector_impl::VectorMul<LhTy, float>{L, 1.0F/R};
    }
    template <class LhTy>
    inline constexpr vector_impl::VectorMul<LhTy, float> operator/(const LhTy& L, const float R) {
        return vector_impl::VectorMul<LhTy, float>{L, 1.0F/R};
    }
    template <class LhTy, class RhTy>
    inline constexpr std::enable_if_t<LhTy::kDimension==2&&RhTy::kDimension==2, float>
      dot(const LhTy& L, const RhTy& R) noexcept {
        return (L[0]*R[0]) + (L[1]*R[1]);
    }
    template <class LhTy, class RhTy>
    inline constexpr std::enable_if_t<LhTy::kDimension==2&&RhTy::kDimension==2, float>
      cross(const LhTy& L, const RhTy& R) noexcept {
        return (L[0]*R[1]) - (L[1]*R[0]);
    }
    template <class LhTy, class RhTy>
    inline constexpr std::enable_if_t<LhTy::kDimension==3&&RhTy::kDimension==3, float>
      dot(const LhTy& L, const RhTy& R) noexcept {
        return (L[0]*R[0]) + (L[1]*R[1]) + (L[2]*R[2]);
    }
    template <class LhTy, class RhTy>
    inline constexpr vector_impl::Vector3DCross<LhTy, RhTy> cross(const LhTy& L, const RhTy& R) noexcept {
        return vector_impl::Vector3DCross{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr std::enable_if_t<LhTy::kDimension==4&&RhTy::kDimension==4, float>
      dot(const LhTy& L, const RhTy& R) noexcept {
        return (L[0]*R[0]) + (L[1]*R[1]) + (L[2]*R[2]) + (L[3]*R[3]);
    }
    template <class FTy, class STy, class TTy>
    inline constexpr std::enable_if_t<FTy::kDimension==4&&STy::kDimension==4&&TTy::kDimension==4, Vector4D>
      cross(const FTy& F, const STy& S, const TTy& T) noexcept {
        // 規則性が分からないため、テンポラリオブジェクトを生成せざるを得ない
        return Vector4D {
            F[1]*(S[2]*T[3]-T[2]*S[3]) - F[2]*(S[1]*T[3]-T[1]*S[3]) + F[3]*(S[1]*T[2]-T[1]*S[2]),
            F[0]*(T[2]*S[3]-S[2]*T[3]) - F[2]*(T[0]*S[3]-S[0]*T[3]) + F[3]*(T[0]*S[2]-S[0]*T[2]),
            F[0]*(S[1]*T[3]-T[1]*S[3]) - F[1]*(S[0]*T[3]-T[0]*S[3]) + F[3]*(S[0]*T[1]-T[0]*S[1]),
            F[0]*(T[1]*S[2]-S[1]*T[2]) - F[1]*(T[0]*S[2]-S[0]*T[2]) + F[2]*(T[0]*S[1]-S[0]*T[1])
        }; 
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
    inline DirectX::XMVECTOR load(const Vector2D& V) { return DirectX::XMVECTOR{V[0], V[1]}; }
    inline DirectX::XMVECTOR load(const Vector3D& V) { return DirectX::XMVECTOR{V[0], V[1], V[2]}; }
    inline DirectX::XMVECTOR load(const Vector4DA& V) { return _mm_load_ps(V.v); }
  } // namespace vector_impl
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MVECTOR_CALC_HEADER_
// EOF
