///
/// \file   field.hpp
/// \brief  フィールド関係定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/26
///             - ヘッダ追加
///             - Field<…> 定義
///             - FieldTag<…> 定義
///             - 補助定義、宣言(IsField, TypeIndex, AlwaysTrue)
///
#ifndef INCLUDED_EGEG_TLIB_FIELD_HEADER_
#define INCLUDED_EGEG_TLIB_FIELD_HEADER_

#include <cstdint>
#include <type_traits>
#include <istream>

namespace easy_engine {
namespace t_lib {
template <class ETy, class IndexTy, class PredTy>
class Field;

  namespace impl {
    template <class>
    struct IsField : std::false_type {};
    template <class ETy, class IdxTy, class PredTy>
    struct IsField<Field<ETy, IdxTy, PredTy>> : std::true_type {};

    template <uint32_t N, class T>
    struct TypeIndex;

    template <class ElemTy>
    struct AlwaysTrue {
        bool operator()(const ElemTy&) const noexcept {
            return true;
        }
    };
  } // namespace impl

template <class ETy, uint32_t NIndex, class PredTy=impl::AlwaysTrue<ETy>, class TIndex=void>
using FieldTag = Field<ETy, impl::TypeIndex<NIndex, TIndex>, PredTy>;

/******************************************************************************

    Field

******************************************************************************/
///
/// \class  Field
/// \brief  フィールド
///
///         メンバ的オブジェクトです。
///         第3型引数に、代入条件をチェックするファンクタを指定することができます。
///
/// \tparam ElemTy : フィールド要素型
/// \tparam IndexTy   : 同一要素型のフィールドを区別するインデックス
/// \tparam PredTy    : 代入可否判定ファンクタ
///
/// \details ファンクタは代入予定の値をconst参照で受け取り、boolを返却するoperator()を定義する必要があります。\n
///          このとき、trueで代入が行われ、falseでは代入が行われません。\n
///          状態を保持するファンクタを持たせる場合、コンストラクタで初期化する必要があります。\n
///          要素型が同一であれば、異なるフィールド間で代入処理が可能です。\n
///          その時に代入されるのは要素のみで、代入可否判定ファンクタが影響を受けることはありません。\n
///          代入可否判定ファンクタを変更したい場合は、setPredicate()を使用して下さい。
/// 
template <class ElemTy, class IndexTy, class PredTy=impl::AlwaysTrue<ElemTy>>
class Field : private PredTy {
public :
  // alias
    using ElemType = ElemTy;
    using PredType = PredTy;

  // concepts
    static_assert(std::is_invocable_r_v<bool, PredTy, ElemType>, "'PredTy' is invalid functor type");

    Field() = default;
    template <class Ty>
    Field(Ty&& Right) noexcept(noexcept(Field{std::forward<Ty>(Right), PredTy{}, impl::IsField<std::decay_t<Ty>>{}}))
        : Field{std::forward<Ty>(Right), PredTy{}, impl::IsField<std::decay_t<Ty>>{}} {}
    template <class Ty, class PTy>
    Field(Ty&& Right, PTy&& Pred)
        noexcept(noexcept(Field{std::forward<Ty>(Right),std::forward<PTy>(Pred),impl::IsField<std::decay_t<Ty>>{}}))
        : Field{std::forward<Ty>(Right), std::forward<PTy>(Pred), impl::IsField<std::decay_t<Ty>>{}} {}

    ///
    /// \brief  値をセット
    ///
    ///         フィールドのセット、値のセットどちらも可能です。
    ///         代入可否判定ファンクタは変更されません。
    ///
    /// \tparam Ty   : セットする値の型
    /// \param Right : セットする値
    ///
    /// \return セット後フィールドへの参照
    ///
    template <class Ty>
    Field& operator=(Ty&& Right) noexcept(noexcept(assign(std::forward<Ty>(Right),impl::IsField<std::decay_t<Ty>>{}))){
        return assign(std::forward<Ty>(Right), impl::IsField<std::decay_t<Ty>>{});
    }
    ///< operator=同様
    template <class Ty>
    void set(Ty&& Right) noexcept(noexcept(*this = std::forward<Ty>(Right))) {
        *this = std::forward<Ty>(Right);
    }

    const ElemType& get() const & noexcept { return element_; }
    ElemType get() && noexcept { return std::move(element_); }

    operator const ElemType&() const noexcept {
        return get();
    }

    ///
    /// \brief  代入可否ファンクタをセット
    ///
    ///         Field<…>::PredTypeにコピー可能、もしくはムーブ可能なファンクタのみ受け付けます。
    ///         代入可否ファンクタの型ごと変換することはできません。
    ///
    /// \tparam PredTy_ : セットするファンクタの型
    /// \param[in] Pred : セットするファンクタ
    ///
    template <class PredTy_>
    void setPredicate(PredTy_&& Pred) noexcept(noexcept(*static_cast<PredType*>(this) = std::forward<PredTy_>(Pred))) {
        *static_cast<PredType*>(this) = std::forward<PredTy_>(Pred);
    }

    const PredType& predicate() const noexcept { return *static_cast<PredType*>(this); }

private :
    template <class Ty, class PTy>
    Field(Ty&& Right, PTy&& Pred, std::true_type)
        noexcept(noexcept(Field{std::forward<Ty>(Right).get(), std::forward<PTy>(Pred), std::false_type{}}))
        : Field{std::forward<Ty>(Right).get(), std::forward<PTy>(Pred), std::false_type{}} {
      // construct from Field
    }
    template <class Ty, class PTy>
    Field(Ty&& Right, PTy&& Pred, std::false_type) 
        noexcept(std::is_nothrow_constructible_v<ElemType, Ty> && std::is_nothrow_constructible_v<PredTy, PTy>)
        : PredTy{std::forward<PTy>(Pred)},
          element_{std::forward<Ty>(Right)} {
      // construct from Value
    }

    template <class Ty>
    Field& assign(Ty&& Right, std::true_type) 
        noexcept(noexcept(assign(std::forward<Ty>(Right).get(), std::false_type{}))) {
      // assign from Field
        return assign(std::forward<Ty>(Right).get(), std::false_type{});
    }
    template <class Ty>
    Field& assign(Ty&& Right, std::false_type) noexcept(noexcept(PredTy::operator()(Right))) {
      // assign from Value
        if(PredTy::operator()(Right))
            element_ = std::forward<Ty>(Right);
        return *this;
    }

    ElemType element_;
};

template <class ElemTy, class IdxTy, class PredTy>
std::istream& operator>>(std::istream& Stream, Field<ElemTy, IdxTy, PredTy>& Fld) {
    ElemTy elem;
    Stream >> elem;
    Fld.set(std::move(elem));
    return Stream;
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_FIELD_HEADER_
// EOF
