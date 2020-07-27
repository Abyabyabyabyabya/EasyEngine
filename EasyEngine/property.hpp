///
/// \file   property.hpp
/// \brief  プロパティ定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/26
///             - ヘッダ追加
///             - PropertyBase<…> 定義
///             - Property<…> 定義
///
#ifndef INCLUDED_EGEG_TLIB_PROPERTY_HEADER_
#define INCLUDED_EGEG_TLIB_PROPERTY_HEADER_

#include <type_traits>
#include "field.hpp"

namespace easy_engine {
namespace t_lib {
template <class ...FieldTypes>
class Property;
    
  namespace impl {
    template <class ...FieldTypes> class PropertyBase;
    template <> class PropertyBase<> {}; // empty PropertyBase
    template <class FieldType, class ...Rest>
    class PropertyBase<FieldType, Rest...> : protected FieldType, protected PropertyBase<Rest...> {
        static_assert(impl::IsField<FieldType>::value, "'FieldType' must be of type Field<…>");
    };
    template <class ...FieldTypes, class ...Rest>
    class PropertyBase<Property<FieldTypes...>, Rest...> : protected PropertyBase<FieldTypes..., Rest...> {};

    template <class ...FieldTypes> struct Assignment;
    template <> class Assignment<> { // empty Assignment
        template <class PropertyTy> void operator()(PropertyTy&, PropertyTy&&) const noexcept {};
    };
    template <class FieldType, class ...Rest>
    struct Assignment<FieldType, Rest...> : private Assignment<Rest...> {
        template <class PropertyTy>
        void operator()(PropertyTy& Left, PropertyTy&& Right) const {
            // 2度moveされる可能性があるが、moveされるのはプロパティ内の対象フィールド(FieldType)のみ
             Left.template field<FieldType>() = std::forward<PropertyTy>(Right).template field<FieldType>();
            Assignment<Rest...>::operator()(Left, std::forward<PropertyTy>(Right));
        }
    };
    template <class ...FieldTypes, class ...Rest>
    struct Assignment<Property<FieldTypes...>, Rest...> : private Assignment<FieldTypes..., Rest...> {
      // Property<…> の…の中にPropertyがある場合はこっち
        template <class PropertyTy>
        void operator()(PropertyTy& Left, PropertyTy&& Right) const {
            Assignment<FieldTypes..., Rest...>::operator()(Left, std::forward<PropertyTy>(Right));
        }
    };
  } // namespace impl


/******************************************************************************

    Property

******************************************************************************/
///
/// \class  Property
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
class Property : private impl::PropertyBase<FieldTypes...>, private impl::Assignment<FieldTypes...> {
public :
    Property() = default;
    Property(std::istream& Istream) {
        Istream >> *this;
    }
    template <class PropertyTy>
    Property(PropertyTy&& Right) {
        impl::Assignment<FieldTypes...>::operator()(*this, std::forward<PropertyTy>(Right));
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
        static_assert(impl::IsField<FieldType>::value, "'FieldType' must be of type 'Field<…>'");
        static_assert(std::is_base_of_v<FieldType, Property>, "'FieldType' must be base for this Property<…>'");

        return *static_cast<const FieldType*>(this);
    }
};

  namespace impl {
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
  } // namespace impl

///< 入力ストリームからプロパティへの入力
template <class ...FieldTypes>
std::istream& operator>>(std::istream& Istream, Property<FieldTypes...>& Prop) {
    impl::Extractor<FieldTypes...>{Istream, Prop};
    return Istream;
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_PROPERTY_HEADER_
// EOF
