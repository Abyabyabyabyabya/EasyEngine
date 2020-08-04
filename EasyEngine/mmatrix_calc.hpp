///
/// \file   mmatrix_calc.hpp
/// \brief  行列演算定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/8/3
///             - ヘッダ追加
///             - 定義済み行列演算移行
///
#ifndef INCLUDED_EGEG_MLIB_MMATRIX_CALC_HEADER_
#define INCLUDED_EGEG_MLIB_MMATRIX_CALC_HEADER_

#include <DirectXMath.h>
#include "mmatrix.hpp"
#include "mvector_calc.hpp" // 行列の乗算内で内積を使用

namespace easy_engine {
namespace m_lib {
  namespace matrix_impl {
    template <size_t Row, size_t Column> struct Matrix {};
    template <> struct Matrix<3, 3> { using Type = Matrix3x3; };
    template <> struct Matrix<3, 4> { using Type = Matrix3x4; };
    template <> struct Matrix<4, 3> { using Type = Matrix4x3; };
    template <> struct Matrix<4, 4> { using Type = Matrix4x4; };
    template <size_t Row, size_t Column> using MatrixType = typename Matrix<Row, Column>::Type;

    template <class LTy, class RTy>
    static constexpr bool kIsMultipliable = LTy::kColumnDimension == RTy::kRowDimension;
    template <class LTy, class RTy>
    using ResultType = std::enable_if_t<kIsMultipliable<LTy,RTy>,MatrixType<LTy::kRowDimension,RTy::kColumnDimension>>;
    template <class MTy>
    using TransposeType = typename Matrix<MTy::kColumnDimension, MTy::kRowDimension>::Type;

    template <class MatrixTy>
    struct TransColumn {
        static constexpr size_t kDimension = MatrixTy::kColumnDimension;
        constexpr TransColumn(const MatrixTy& Original, const size_t Row) : original_{Original}, row_{Row} {}
        constexpr float operator[](const size_t I) const {
            return original_[I][row_];
        }
    private :
        const MatrixTy& original_;
        const size_t row_;
    };

    template <class MatrixTy>
    class TransposeRef {
    public :
        static constexpr size_t kRowDimension = MatrixTy::kColumnDimension;
        static constexpr size_t kColumnDimension = MatrixTy::kRowDimension;
        constexpr TransposeRef(const MatrixTy& Original) : original_{Original} {}
        constexpr TransColumn<MatrixTy> operator[](size_t I) const noexcept {
            return TransColumn<MatrixTy>{original_, I}; 
        }
    private :
        const MatrixTy& original_;
    };
  } // namespace matrix_impl

/******************************************************************************

    matrix calculation

******************************************************************************/
    template <class MTy>
    inline constexpr matrix_impl::TransposeRef<MTy> transpose(const MTy& M) noexcept {
        return matrix_impl::TransposeRef<MTy>{M};
    }

  namespace default_operation {
    inline constexpr Matrix3x3 matrixAdd(const Matrix3x3& L, const Matrix3x3& R) noexcept {
        return Matrix3x3{
            L._00+R._00, L._01+R._01, L._02+R._02,
            L._10+R._10, L._11+R._11, L._12+R._12,
            L._20+R._20, L._21+R._21, L._22+R._22
        };
    }
    inline constexpr Matrix3x3 matrixSub(const Matrix3x3& L, const Matrix3x3& R) noexcept {
        return Matrix3x3{
            L._00-R._00, L._01-R._01, L._02-R._02,
            L._10-R._10, L._11-R._11, L._12-R._12,
            L._20-R._20, L._21-R._21, L._22-R._22
        };
    }
    inline constexpr Matrix3x3 matrixMul(const Matrix3x3& L, const float R) noexcept {
        return Matrix3x3{
            L._00*R, L._01*R, L._02*R,
            L._10*R, L._11*R, L._12*R,
            L._20*R, L._21*R, L._22*R
        };
    }
    inline constexpr Matrix3x3 matrixDiv(const Matrix3x3& L, const float R) noexcept {
        return default_operation::matrixMul(L, 1.0F/R);
    }
    inline constexpr Matrix3x4 matrixAdd(const Matrix3x4& L, const Matrix3x4& R) noexcept {
        return Matrix3x4{
            L._00+R._00, L._01+R._01, L._02+R._02, L._03+R._03,
            L._10+R._10, L._11+R._11, L._12+R._12, L._13+R._13,
            L._20+R._20, L._21+R._21, L._22+R._22, L._23+R._23
        };
    }
    inline constexpr Matrix3x4 matrixSub(const Matrix3x4& L, const Matrix3x4& R) noexcept {
        return Matrix3x4{
            L._00-R._00, L._01-R._01, L._02-R._02, L._03-R._03,
            L._10-R._10, L._11-R._11, L._12-R._12, L._13-R._13,
            L._20-R._20, L._21-R._21, L._22-R._22, L._23-R._23
        };
    }
    inline constexpr Matrix3x4 matrixMul(const Matrix3x4& L, const float R) noexcept {
        return Matrix3x4{
            L._00*R, L._01*R, L._02*R, L._03*R,
            L._10*R, L._11*R, L._12*R, L._13*R,
            L._20*R, L._21*R, L._22*R, L._23*R
        };
    }
    inline constexpr Matrix3x4 matrixDiv(const Matrix3x4& L, const float R) noexcept {
        return default_operation::matrixMul(L, 1.0F/R);
    }
    inline constexpr Matrix4x3 matrixAdd(const Matrix4x3& L, const Matrix4x3& R) noexcept {
        return Matrix4x3{
            L._00+R._00, L._01+R._01, L._02+R._02,
            L._10+R._10, L._11+R._11, L._12+R._12,
            L._20+R._20, L._21+R._21, L._22+R._22,
            L._30+R._30, L._31+R._31, L._32+R._32
        };
    }
    inline constexpr Matrix4x3 matrixSub(const Matrix4x3& L, const Matrix4x3& R) noexcept {
        return Matrix4x3{
            L._00-R._00, L._01-R._01, L._02-R._02,
            L._10-R._10, L._11-R._11, L._12-R._12,
            L._20-R._20, L._21-R._21, L._22-R._22,
            L._30-R._30, L._31-R._31, L._32-R._32
        };
    }
    inline constexpr Matrix4x3 matrixMul(const Matrix4x3& L, const float R) noexcept {
        return Matrix4x3{
            L._00*R, L._01*R, L._02*R,
            L._10*R, L._11*R, L._12*R,
            L._20*R, L._21*R, L._22*R,
            L._30*R, L._31*R, L._32*R
        };
    }
    inline constexpr Matrix4x3 matrixDiv(const Matrix4x3& L, const float R) noexcept {
        return default_operation::matrixMul(L, 1.0F/R);
    }
    inline constexpr Matrix4x4 matrixAdd(const Matrix4x4& L, const Matrix4x4& R) noexcept {
        return Matrix4x4{
            L._00+R._00, L._01+R._01, L._02+R._02, L._03+R._03,
            L._10+R._10, L._11+R._11, L._12+R._12, L._13+R._13,
            L._20+R._20, L._21+R._21, L._22+R._22, L._23+R._23,
            L._30+R._30, L._31+R._31, L._32+R._32, L._33+R._33
        };
    }
    inline constexpr Matrix4x4 matrixSub(const Matrix4x4& L, const Matrix4x4& R) noexcept {
        return Matrix4x4{
            L._00-R._00, L._01-R._01, L._02-R._02, L._03-R._03,
            L._10-R._10, L._11-R._11, L._12-R._12, L._13-R._13,
            L._20-R._20, L._21-R._21, L._22-R._22, L._23-R._23,
            L._30-R._30, L._31-R._31, L._32-R._32, L._33-R._33
        };
    }
    inline constexpr Matrix4x4 matrixMul(const Matrix4x4& L, const float R) noexcept {
        return Matrix4x4{
            L._00*R, L._01*R, L._02*R, L._03*R,
            L._10*R, L._11*R, L._12*R, L._13*R,
            L._20*R, L._21*R, L._22*R, L._23*R,
            L._30*R, L._31*R, L._32*R, L._33*R
        };
    }
    inline constexpr Matrix4x4 matrixDiv(const Matrix4x4& L, const float R) noexcept {
        return default_operation::matrixMul(L, 1.0F/R);
    }
    template <class MatrixTy>
    inline constexpr MatrixTy operator+(const MatrixTy& L, const MatrixTy& R) noexcept {
        return default_operation::matrixAdd(L, R);
    }
    template <class MatrixTy>
    inline constexpr MatrixTy operator-(const MatrixTy& L, const MatrixTy& R) noexcept {
        return default_operation::matrixSub(L, R);
    }
    template <class MatrixTy>
    inline constexpr MatrixTy operator*(const MatrixTy& L, const float R) noexcept {
        return default_operation::matrixMul(L, R);
    }
    template <class MatrixTy>
    inline constexpr MatrixTy operator/(const MatrixTy& L, const float R) noexcept {
        return default_operation::matrixDiv(L, R);
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::ResultType<LhTy, RhTy> matrixMul(const LhTy& L, const RhTy& R) noexcept {
        using RetTy = matrix_impl::ResultType<LhTy, RhTy>;
        const matrix_impl::TransposeType<RhTy> kTR = transpose(R);
        RetTy mul;
        for(int i=0; i<RetTy::kRowDimension; ++i)
            for( int j=0; j<RetTy::kColumnDimension; ++j)
                mul[i][j] = dot(L[i], kTR[j]);
        return mul;
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::ResultType<LhTy, RhTy> operator*(const LhTy& L, const RhTy& R) noexcept {
        return default_operation::matrixMul(L, R);
    }
  } // namespace default_operation
  namespace default_noncopy_operation {

  } // namespace default_noncopy_operation
  namespace simd_operation {

  } // namespace simd_operation
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MMATRIX_CALC_HEADER_
// EOF
