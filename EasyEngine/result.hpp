///
/// \file   result.hpp
/// \brief  関数戻り値用テンプレートクラス群定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/7/27
///             - ヘッダ追加
///             - Result<…> 定義
///             - DetailedResult<…> 定義
///         - 2020/8/21
///             - DetailedResult<…> コンストラクタのnoexcept指定修正
///
#ifndef INCLUDED_EGEG_TLIB_RESULT_HEADER_
#define INCLUDED_EGEG_TLIB_RESULT_HEADER_

#include <stdexcept>
#include <type_traits>

namespace easy_engine {
namespace t_lib {
  namespace result_impl {
    [[noreturn]] inline void referenceError(std::string&& Func) {
        throw std::logic_error("reference to invalid value. func: "+Func);
    };
  } // namespace result_impl

struct Success{};
struct Failure{};

/******************************************************************************

    Result

******************************************************************************/
///
/// \class  Result
/// \brief  状態を持つ戻り値
///
///         使用例) 
///          成功: … return Result<…>{Success{}};
///          失敗: … return Result<…>{Failure{}, "hoghoge error"};
///          クラス名を省略し、return {Success{}, …};　と記述することも可能です。
///
/// \tparam ValueTy : 戻り値として保持する値の型
///
/// \attention  Result<bool>としてインスタンス化することを禁止しています。\n
///             ↑これを使うくらいなら、組み込み型のboolを使いましょう。
///
/// \note   value_の構築について\n
///         Resultの構築時、ValueTyがクラスの場合はデフォルトのコンストラクタが呼び出されるが、\n
///         組み込み型の場合は呼ばれないようなシチュエーションがある。\n
///         デフォルト構築が行われるシチュエーションにおいて、その値が使用されることは無いという前提に基づく、\n
///         ほんのちょっとした最適化のつもり
///
template <class ValueTy>
class Result {
public :
  // alias
    using ValueType = ValueTy;

  // functions
    template <class ValTy>
    Result(Success, ValTy&& Value) noexcept(std::is_nothrow_constructible_v<ValueType, ValTy>) :
        condition_{true},
        value_{std::forward<ValTy>(Value)} {}

    Result(Failure) noexcept(std::is_nothrow_constructible_v<ValueType>) :
        condition_{false} /* value_{default} */ {}
    template <class ValTy>
    Result(Failure, ValTy&& InvalidValue) noexcept(std::is_nothrow_constructible_v<ValueType, ValTy>) :
        condition_{false},
        value_{std::forward<ValTy>(InvalidValue)} {}

    ValueType& get() {
        if(!*this) result_impl::referenceError("Result<…>::get");
        return value_;
    }
    ValueType& operator*() { return get(); }
    ValueType* operator->() { return &get(); }

    explicit operator bool() const noexcept { return condition_; }
    operator ValueType() && { return std::move(get()); }
    
private :
    bool condition_;
    ValueType value_;
};
template <> class Result<bool>;

/******************************************************************************

    DetailedResult

******************************************************************************/
///
/// \class  DetailedResult
/// \brief  状態と、詳細を持つ戻り値
///
///         Resultの拡張版です。
///         状態に追加して、詳細を保持することができます。
///         使用例)
///          DetailedResult<Hoge*, std::string> f() {
///              成功: return {Success{}, new Hoge{}};
///              失敗: return {Failure{}, nullptr, "dead"};
///          }
///
/// \tparam ValueTy  : 戻り値として保持する値の型
/// \tparam DetailTy : 詳細として保持する値の型
///
/// \note   デフォルト構築について、Resultと同様
/// \see    Result
///
template <class ValueTy, class DetailTy>
class DetailedResult {
public :
  // alias
    using ValueType = ValueTy;
    using DetailType = DetailTy;

  // functions
    template <class ValTy>
    DetailedResult(Success, ValTy&& Value) 
      noexcept(std::is_nothrow_constructible_v<ValueType, ValTy> && std::is_nothrow_constructible_v<DetailType>) :
        condition_{true},
        value_{std::forward<ValTy>(Value)} /* detail_{default} */ {}

    template <class DtlTy>
    DetailedResult(Failure, DtlTy&& Details)
      noexcept(std::is_nothrow_constructible_v<ValueType> && noexcept(detail_(std::forward<DtlTy>(Details)))) :
        condition_{false}, /* value_{default} */
        detail_(std::forward<DtlTy>(Details)) {}
    template <class ValTy, class DtlTy>
    DetailedResult(Failure, DtlTy&& Details, ValTy&& InvalidValue)
      noexcept(std::is_nothrow_constructible_v<ValueType, ValTy> && noexcept(detail_(std::forward<DtlTy>(Details)))) :
        condition_{false},
        value_{std::forward<ValTy>(InvalidValue)},
        detail_(std::forward<DtlTy>(Details)) {}

    ValueType& get() {
        if(!*this) result_impl::referenceError("DetailedResult<…>::get");
        return value_;
    }
    ValueType& operator*() { return get(); }
    ValueType* operator->() { return &get(); }

    const DetailType& detail() const noexcept { return detail_; }

    explicit operator bool() const noexcept { return condition_; }
    operator ValueType() && { return std::move(get()); }

private :
    bool condition_;
    ValueTy value_;
    DetailType detail_;
};

template <class DetailTy>
class DetailedResult<bool, DetailTy> { // bool型への部分特殊化
public :
  // alias
    using ValueType = bool;
    using DetailType = DetailTy;

  // functions
    DetailedResult(Success) noexcept(std::is_nothrow_constructible_v<DetailType>) :
        condition_{true} /* detail_{default} */ {}

    template <class DtlTy>
    DetailedResult(Failure, DtlTy&& Detail) noexcept(noexcept(DetailTy{std::forward<DtlTy>(Detail)})) :
        condition_{false},
        detail_{std::forward<DtlTy>(Detail)} {}

    bool get() const noexcept { return condition_; }
    bool operator*() const noexcept { return get(); }

    const DetailType& detail() const noexcept { return detail_; }

    explicit operator bool() const noexcept { return get(); }

private :
    bool condition_;
    DetailType detail_;
};

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_RESULT_HEADER_
// EOF
