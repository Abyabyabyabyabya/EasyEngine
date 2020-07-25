///
/// \file   noncopyable.hpp
/// \brief  コピー禁止ミックスイン定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/24
///             - ヘッダ追加
///             - Noncopyable<…> 定義(未完)
///         - 2020/7/25
///             - Noncopyable<…> 完成
///
#ifndef INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_
#define INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_

namespace easy_engine {
namespace t_lib {

///
/// \class  Noncopyable
/// \brief  コピー禁止ミックスイン
///
///         コピー禁止属性を付与したいクラスで、このミックスインをprivate継承してください。
///         テンプレートクラスです。
///         クラス毎に専用のコピー禁止ミックスインを利用することで、なるべくEBOが効くようにしています。
///
/// \tparam DerivedTy : コピー禁止属性を付与するクラス
///
template <class DerivedTy>
class Noncopyable {
public :
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;

protected :
    Noncopyable() = default;
    ~Noncopyable() = default;
};

} // namespace t_lib
} // namespace easy_engine

#endif // !INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_
// EOF
