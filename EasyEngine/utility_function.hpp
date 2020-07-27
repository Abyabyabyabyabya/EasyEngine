///
/// \file   utility_function.hpp
/// \brief  少し便利なテンプレート関数群定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/27
///             - ヘッダ追加
///             - arraySize<…>() 定義
///             - enumValue<…>() 定義
///
#ifndef INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_
#define INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_

#include <type_traits>

namespace easy_engine {
namespace t_lib {

///
/// \brief  配列の要素数を取得する
///
///         使用例)
///          int arr[10];
///          size_t size = arraySize(arr);  … size == 「10」
///
/// \tparam ElemTy : 配列の要素型
/// \tparam Size   : 配列の要素数
/// \param[in]     : 要素数を取得する配列
///
/// \return 配列の要素数
///
template <class ElemTy, size_t Size>
constexpr size_t arraySize(const ElemTy(&)[Size]) noexcept {
    return Size;
}

///
/// \brief  基礎型に変換した列挙子を取得する
///
///         スコープなし列挙型でもスコープ付き列挙型でも動作します。
///         使用例)
///          enum class Hoge { Koreha, Rekkyosi, Dayo };
///             … 中略 …
///          auto v = enumValue(Hoge::Koreha);
///
/// \tparam EnumTy   : 列挙型
/// \param[in] Value : 変換する列挙子
///
/// \return 基礎型に変換した列挙子の値
///
/// \attention Valueは列挙子である必要があります。
///
template <class EnumTy>
constexpr auto enumValue(EnumTy Value) noexcept {
    return static_cast<std::underlying_type_t<EnumTy>>(Value);
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_
// EOF
