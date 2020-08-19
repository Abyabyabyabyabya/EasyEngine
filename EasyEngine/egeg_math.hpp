///
/// \file   egeg_math.hpp
/// \brief  算術ライブラリ群
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
///         - 2020/8/3
///             - ヘッダ追加
///         - 2020/8/19
///             - ヘッダコメント修正
///
/// \note   名前空間について\n
///         必ず一つの名前空間を明示的な指定なしで選択できるようにしているので、
///         その時のデフォルトではない名前空間をusing宣言により省略できるようにすると
///         オーバーロード解決が曖昧になってしまう。
///         default_noncopy_operationの関数群について\n
///         遅延評価によりテンポラリオブジェクトの生成を抑制しているが、
///         default_operationの関数群でもコンパイラによる最適化で同じような効果が期待できるかも。
///         実行時計算用関数について\n
///         上手く扱えていない。デフォルトでは使用できないようにしている。\n
///
#ifndef INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_
#define INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_

namespace easy_engine {
namespace m_lib {
#ifdef EGEG_MLIB_USE_SIMD_OPERATION
  inline namespace simd_operation {}
#elif defined EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATION
  inline namespace default_noncopy_operation {}
#else // default
  inline namespace default_operation {}
#endif // EGEG_MLIB_USE_SIMD_OPERATION
} // namespace m_lib
} // namespace easy_engine

#include "angle.hpp"
#include "mmatrix.hpp"
#include "mmatrix_calc.hpp"
#include "mvector.hpp"
#include "mvector_calc.hpp"

#endif // INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_
// EOF
