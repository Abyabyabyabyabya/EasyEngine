///
/// \file   mmatrix_calc.hpp
/// \brief  行列演算定義ヘッダ
///
///         コンパイル時行列演算を1部サポートしています。
///         デフォルトだと使用できず、EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATIONマクロの指定で可能になるものがあります。
///
/// \author 板場
///
/// \attention 1部のコンパイル時行列演算を行うためには、テンポラリオブジェクトを生成しない処理を選択する必要があるが、
///            速度を求めるのであればデフォルトの処理が良いと思う。
///            一見テンポラリオブジェクトを作らないほうが早いように思われるが、
///            コンパイラによる最適化が望めるのはデフォルトの方。
///
/// \par    履歴
///         - 2020/8/3
///             - ヘッダ追加
///             - 定義済み行列演算移行
///         - 2020/8/4
///             - テンポラリオブジェクトを生成しない行列演算定義
///         - 2020/8/5
///             - SIMD演算を使用した行列の乗算関数定義
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

    template <class MatrixTy>
    struct TransposeRow {
        static constexpr size_t kDimension = MatrixTy::kNumColumns;
        constexpr TransposeRow(const MatrixTy& Original, const size_t RowNum) : original_{Original}, row_num_{RowNum}{}
        constexpr float operator[](const size_t Column) const {
            return original_[Column][row_num_];
        }
    private :
        const MatrixTy& original_;
        const size_t row_num_;
    };
    template <class MatrixTy>
    class TransposeRef {
    public :
        static constexpr size_t kNumRows = MatrixTy::kNumColumns;
        static constexpr size_t kNumColumns = MatrixTy::kNumRows;
        constexpr TransposeRef(const MatrixTy& Original) : original_{Original} {}
        constexpr TransposeRow<MatrixTy> operator[](size_t Row) const noexcept {
            return TransposeRow<MatrixTy>{original_, Row}; 
        }
    private :
        const MatrixTy& original_;
    };

    #define EGEG_MLIB_DEFINE_MATRIX_NONCOPY_OPERATOR(OpType, Op)\
    template <class LTy, class RTy>\
    class Matrix##OpType {\
    public :\
        static_assert(IsSameDimension<LTy, RTy>::value, "the dimension of 'LTy' and 'RTy' must be the same");\
        static constexpr size_t kNumRows = LTy::kNumRows;\
        static constexpr size_t kNumColumns = LTy::kNumColumns;\
        class Row {\
        public :\
            static constexpr size_t kDimension = Matrix##OpType::kNumColumns;\
            constexpr Row(const Matrix##OpType& Expr, size_t RowNum) noexcept :\
                expr_{Expr}, row_num_{RowNum} {}\
            constexpr float operator[](size_t Column) const {\
                return expr_.l_[row_num_][Column] Op expr_.r_[row_num_][Column];\
            }\
        private :\
            const Matrix##OpType& expr_;\
            const size_t row_num_;\
        };\
        constexpr Matrix##OpType(const LTy& L, const RTy& R) noexcept : l_{L}, r_{R} {}\
        constexpr Row operator[](size_t RowNum) const noexcept {\
            return Row{*this, RowNum};\
        }\
    private :\
        const LTy& l_;\
        const RTy& r_;\
    };

    EGEG_MLIB_DEFINE_MATRIX_NONCOPY_OPERATOR(Add, +);
    EGEG_MLIB_DEFINE_MATRIX_NONCOPY_OPERATOR(Sub, -);
    template <class LTy, class RTy>
    class MatrixMul {
    public :
        static_assert(IsSameDimension<LTy, TransposeRef<RTy>>::value, "the dimension of 'LTy' and 'RTyT' must be the same");
        static constexpr size_t kNumRows = LTy::kNumRows;
        static constexpr size_t kNumColumns = LTy::kNumColumns;
        class Row {
        public :
            static constexpr size_t kDimension = MatrixMul::kNumColumns;
            constexpr Row(const MatrixMul& Expr, size_t RowNum) noexcept :
                expr_{Expr}, row_num_{RowNum} {}
            constexpr float operator[](size_t Column) const {
                return default_noncopy_operation::dot(expr_.l_[row_num_], expr_.r_[Column]);
            }
        private :
            const MatrixMul& expr_;
            const size_t row_num_;
        };
        constexpr MatrixMul(const LTy& L, const RTy& R) noexcept : l_{L}, r_{R} {}
        constexpr Row operator[](size_t RowNum) const noexcept {
            return Row{*this, RowNum};
        }
    private :
        const LTy& l_;
        const TransposeRef<RTy> r_;
    };
    template <class LTy>
    class MatrixMul<LTy, float> {
    public :
        static constexpr size_t kNumRows = LTy::kNumRows;
        static constexpr size_t kNumColumns = LTy::kNumColumns;
        class Row {
        public :
            static constexpr size_t kDimension = MatrixMul::kNumColumns;
            constexpr Row(const MatrixMul& Expr, size_t RowNum) noexcept :
                expr_{Expr}, row_num_{RowNum} {}
            constexpr float operator[](size_t Column) const {
                return expr_.l_[row_num_][Column] * expr_.r_;
            }
        private :
            const MatrixMul& expr_;
            const size_t row_num_;
        };
        constexpr MatrixMul(const LTy& L, const float R) noexcept : l_{L}, r_{R} {}
        constexpr Row operator[](size_t RowNum) const noexcept {
            return Row{*this, RowNum};
        }
    private :
        const LTy& l_;
        const float r_;
    };

    template <class LTy, class RTy>
    static constexpr bool kIsMultipliable = LTy::kNumColumns == RTy::kNumRows;
    template <class LTy, class RTy>
    using MultipleType = std::enable_if_t<kIsMultipliable<LTy,RTy>,MatrixType<LTy::kNumRows,RTy::kNumColumns>>;
    template <class MTy>
    using TransposeType = typename Matrix<MTy::kNumColumns, MTy::kNumRows>::Type;

    DirectX::XMMATRIX loadMatrix3x3(const Matrix3x3&);
    DirectX::XMMATRIX loadMatrix3x4(const Matrix3x4&);
    DirectX::XMMATRIX loadMatrix4x3(const Matrix4x3&);
    DirectX::XMMATRIX loadMatrix4x4(const Matrix4x4&);
    void storeMatrix3x3(Matrix3x3&, DirectX::FXMMATRIX);
    void storeMatrix3x4(Matrix3x4&, DirectX::FXMMATRIX);
    void storeMatrix4x3(Matrix4x3&, DirectX::FXMMATRIX);
    void storeMatrix4x4(Matrix4x4&, DirectX::FXMMATRIX);
  } // namespace matrix_impl

/******************************************************************************

    matrix calculation

******************************************************************************/
  namespace default_operation {
    template <class MatrixTy>
    inline matrix_impl::TransposeType<MatrixTy> transpose(const MatrixTy& M) noexcept {
        matrix_impl::TransposeType<MatrixTy> t;
        for(int i=0; i<MatrixTy::kNumRows; ++i)
            for(int j=0; j<MatrixTy::kNumColumns; ++j)
                t[j][i] = M[i][j];
        return t;
    }
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
    inline constexpr matrix_impl::Matrix<MatrixTy::kNumRows, MatrixTy::kNumColumns>
      operator+(const MatrixTy& L, const MatrixTy& R) noexcept {
        return default_operation::matrixAdd(L, R);
    }
    template <class MatrixTy>
    inline constexpr matrix_impl::Matrix<MatrixTy::kNumRows, MatrixTy::kNumColumns>
      operator-(const MatrixTy& L, const MatrixTy& R) noexcept {
        return default_operation::matrixSub(L, R);
    }
    template <class MatrixTy>
    inline constexpr matrix_impl::Matrix<MatrixTy::kNumRows, MatrixTy::kNumColumns>
      operator*(const MatrixTy& L, const float R) noexcept {
        return default_operation::matrixMul(L, R);
    }
    template <class MatrixTy>
    inline constexpr matrix_impl::Matrix<MatrixTy::kNumRows, MatrixTy::kNumColumns>
      operator/(const MatrixTy& L, const float R) noexcept {
        return default_operation::matrixDiv(L, R);
    }
    template <class LhTy, class RhTy>
    inline matrix_impl::MultipleType<LhTy, RhTy> matrixMul(const LhTy& L, const RhTy& R) noexcept {
        using RetTy = matrix_impl::MultipleType<LhTy, RhTy>;
        const matrix_impl::TransposeType<RhTy> kTR = transpose(R);
        RetTy mul;
        for(int i=0; i<RetTy::kNumRows; ++i)
            for( int j=0; j<RetTy::kNumColumns; ++j)
                mul[i][j] = dot(
                  vector_impl::VectorType<LhTy::kNumColumns>{L[i]}, 
                  vector_impl::VectorType<RhTy::kNumRows>{kTR[j]});
        return mul;
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MultipleType<LhTy, RhTy> operator*(const LhTy& L, const RhTy& R) noexcept {
        return default_operation::matrixMul(L, R);
    }
  } // namespace default_operation
  namespace default_noncopy_operation {
    template <class MTy>
    inline constexpr matrix_impl::TransposeRef<MTy> transpose(const MTy& M) noexcept {
        return matrix_impl::TransposeRef{M};
    }
    
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixAdd<LhTy, RhTy> matrixAdd(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixAdd{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixAdd<LhTy, RhTy> operator+(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixAdd{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixSub<LhTy, RhTy> matrixSub(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixSub{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixSub<LhTy, RhTy> operator-(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixSub{L, R};
    }
    template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, RhTy> matrixMul(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixMul{L, R};
    }template <class LhTy, class RhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, RhTy> operator*(const LhTy& L, const RhTy& R) noexcept {
        return matrix_impl::MatrixMul{L, R};
    }
    template <class LhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, float> matrixMul(const LhTy& L, const float R) noexcept {
        return matrix_impl::MatrixMul{LhTy, R};
    }
    template <class LhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, float> operator*(const LhTy& L, const float R) noexcept {
        return matrix_impl::MatrixMul{LhTy, R};
    }
    template <class LhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, float> matrixDiv(const LhTy& L, const float R) noexcept {
        return matrix_impl::MatrixMul{LhTy, 1.0F/R};
    }
    template <class LhTy>
    inline constexpr matrix_impl::MatrixMul<LhTy, float> operator/(const LhTy& L, const float R) noexcept {
        return matrix_impl::MatrixMul{LhTy, 1.0F/R};
    }
  } // namespace default_noncopy_operation
  namespace simd_operation {
    inline Matrix3x3 matrixMul(const Matrix3x3& L, const Matrix3x3& R) {
        auto l = matrix_impl::loadMatrix3x3(L);
        auto r = matrix_impl::loadMatrix3x3(R);
        Matrix3x3 ret;
        matrix_impl::storeMatrix3x3(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix3x4 matrixMul(const Matrix3x3& L, const Matrix3x4& R) {
        auto l = matrix_impl::loadMatrix3x3(L);
        auto r = matrix_impl::loadMatrix3x4(R);
        Matrix3x4 ret;
        matrix_impl::storeMatrix3x4(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix3x3 matrixMul(const Matrix3x4& L, const Matrix4x3& R) {
        auto l = matrix_impl::loadMatrix3x4(L);
        auto r = matrix_impl::loadMatrix4x3(R);
        Matrix3x3 ret;
        matrix_impl::storeMatrix3x3(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix3x4 matrixMul(const Matrix3x4& L, const Matrix4x4& R) {
        auto l = matrix_impl::loadMatrix3x4(L);
        auto r = matrix_impl::loadMatrix4x4(R);
        Matrix3x4 ret;
        matrix_impl::storeMatrix3x4(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix4x3 matrixMul(const Matrix4x3& L, const Matrix3x3& R) {
        auto l = matrix_impl::loadMatrix4x3(L);
        auto r = matrix_impl::loadMatrix3x3(R);
        Matrix4x3 ret;
        matrix_impl::storeMatrix4x3(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix4x4 matrixMul(const Matrix4x3& L, const Matrix3x4& R) {
        auto l = matrix_impl::loadMatrix4x3(L);
        auto r = matrix_impl::loadMatrix3x4(R);
        Matrix4x4 ret;
        matrix_impl::storeMatrix4x4(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix4x3 matrixMul(const Matrix4x4& L, const Matrix4x3& R) {
        auto l = matrix_impl::loadMatrix4x4(L);
        auto r = matrix_impl::loadMatrix4x3(R);
        Matrix4x3 ret;
        matrix_impl::storeMatrix4x3(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
    inline Matrix4x4 matrixMul(const Matrix4x4& L, const Matrix4x4& R) {
        auto l = matrix_impl::loadMatrix4x4(L);
        auto r = matrix_impl::loadMatrix4x4(R);
        Matrix4x4 ret;
        matrix_impl::storeMatrix4x4(ret, DirectX::XMMatrixMultiply(l, r));
        return ret;
    }
  } // namespace simd_operation

  namespace matrix_impl {
    DirectX::XMMATRIX loadMatrix3x3(const Matrix3x3& M) {
        return DirectX::XMLoadFloat3x3(reinterpret_cast<const DirectX::XMFLOAT3X3*>(&M));
    }
    DirectX::XMMATRIX loadMatrix3x4(const Matrix3x4& M) {
        return DirectX::XMLoadFloat3x4(reinterpret_cast<const DirectX::XMFLOAT3X4*>(&M));
    }
    DirectX::XMMATRIX loadMatrix4x3(const Matrix4x3& M) {
        return DirectX::XMLoadFloat4x3(reinterpret_cast<const DirectX::XMFLOAT4X3*>(&M));
    }
    DirectX::XMMATRIX loadMatrix4x4(const Matrix4x4& M) {
        return DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&M));
    }
    void storeMatrix3x3(Matrix3x3& D, DirectX::FXMMATRIX S) {
        DirectX::XMStoreFloat3x3(reinterpret_cast<DirectX::XMFLOAT3X3*>(&D), S);
    }
    void storeMatrix3x4(Matrix3x4& D, DirectX::FXMMATRIX S) {
        DirectX::XMStoreFloat3x4(reinterpret_cast<DirectX::XMFLOAT3X4*>(&D), S);
    }
    void storeMatrix4x3(Matrix4x3& D, DirectX::FXMMATRIX S) {
        DirectX::XMStoreFloat4x3(reinterpret_cast<DirectX::XMFLOAT4X3*>(&D), S);
    }
    void storeMatrix4x4(Matrix4x4& D, DirectX::FXMMATRIX S) {
        DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&D), S);
    }
  } // namespace matrix_impl
} // namespace m_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_MLIB_MMATRIX_CALC_HEADER_
// EOF
