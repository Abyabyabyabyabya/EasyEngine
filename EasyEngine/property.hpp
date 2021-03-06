///
/// \file   property.hpp
/// \brief  プロパティ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/7/26
///             - ヘッダ追加
///             - PropertyBase<…> 定義
///             - Property<…> 定義
///         - 2020/7/27
///             - コメント追加
///             - デフォルトの関数で事足りることに気が付き、作業途中だったAssignment<…>を削除
///
#ifndef INCLUDED_EGEG_TLIB_PROPERTY_HEADER_
#define INCLUDED_EGEG_TLIB_PROPERTY_HEADER_

#include <type_traits>
#include "field.hpp"

namespace easy_engine {
namespace t_lib {
template <class ...FieldTypes>
class Property;
    
  namespace prop_impl {
    template <class ...FieldTypes> class PropertyBase;
    template <> class PropertyBase<> {}; // empty PropertyBase
    template <class FieldType, class ...Rest>
    class PropertyBase<FieldType, Rest...> : protected FieldType, protected PropertyBase<Rest...> {
        static_assert(prop_impl::IsField<FieldType>::value, "'FieldType' must be of type Field<…>");
    };
    template <class ...FieldTypes, class ...Rest>
    class PropertyBase<Property<FieldTypes...>, Rest...> : protected PropertyBase<FieldTypes..., Rest...> {};

    template <class ...FieldTypes> struct Assignment;
    template <> class Assignment<> { // empty Assignment
        template <class PropertyTy> void operator()(PropertyTy&, PropertyTy&&) const noexcept {};
    };
  } // namespace prop_impl


/******************************************************************************

    Property

******************************************************************************/
///
/// \brief  プロパティ
///
///         Field<…> を複数保持します。
///         代入可否判定、入力ストリームからのデータ入力などField<…>同様の機能を提供します。
///         フィールドへのアクセスはfield()を使用します。
///
/// \see    Field
///
/// \tparam FieldTypes  : 保持するフィールドの型リスト
///
template <class ...FieldTypes>
class Property : private prop_impl::PropertyBase<FieldTypes...> { //, private prop_impl::Assignment<FieldTypes...> {
public :
    Property() = default;

    ///
    /// \brief  入力ストリームからのデータで初期化
    ///
    ///         入力ストリームから、フィールドの数だけパラメータを入力します。
    ///         その際、FieldTypes... の並びで読み込まれます。
    ///
    /// \param[in] Istream  : データを読み込む入力ストリーム
    ///
    Property(std::istream& Istream) {
        Istream >> *this;
    }

    template <class FieldType>
    FieldType& field() & noexcept {
        return const_cast<FieldType&>(access<FieldType>());
    }

    template <class FieldType>
    const FieldType& field() const & noexcept {
        return access<FieldType>();
    }


    template <class FieldType>
    FieldType field() && noexcept {
        return std::move(field<FieldType>());
    }

private :
    template <class FieldType>
    const FieldType& access() const noexcept {
        static_assert(field_impl::IsField<FieldType>::value, "'FieldType' must be of type 'Field<…>'");
        static_assert(std::is_base_of_v<FieldType, Property>, "'FieldType' must be base for this Property<…>'");

        return *static_cast<const FieldType*>(this);
    }
};

  namespace prop_impl {
    template <class ...FieldTypes> struct Extractor;
    template <>
    struct Extractor<> { // empty Extractor
        template <class ...FieldTypes> Extractor(std::istream&, Property<FieldTypes...>&) noexcept {}
    };

    template <class First, class ...Rest>
    struct Extractor<First, Rest...> {
        template < class ...FieldTypes>
        Extractor(std::istream& Istream, Property<FieldTypes...>& Prop) {
            Extractor<Rest...>{Istream >> Prop.field<First>(), Prop};
        }
    };
  } // namespace prop_impl

///< 入力ストリームからプロパティへの入力
template <class ...FieldTypes>
std::istream& operator>>(std::istream& Istream, Property<FieldTypes...>& Prop) {
    prop_impl::Extractor<FieldTypes...>{Istream, Prop};
    return Istream;
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_PROPERTY_HEADER_
// EOF
