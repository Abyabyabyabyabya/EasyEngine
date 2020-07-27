///
/// \file   property.hpp
/// \brief  �v���p�e�B��`�w�b�_
/// \author ��
///
/// \par    ����
///         - 2020/7/26
///             - �w�b�_�ǉ�
///             - PropertyBase<�c> ��`
///             - Property<�c> ��`
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
        static_assert(impl::IsField<FieldType>::value, "'FieldType' must be of type Field<�c>");
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
            // 2�xmove�����\�������邪�Amove�����̂̓v���p�e�B���̑Ώۃt�B�[���h(FieldType)�̂�
             Left.template field<FieldType>() = std::forward<PropertyTy>(Right).template field<FieldType>();
            Assignment<Rest...>::operator()(Left, std::forward<PropertyTy>(Right));
        }
    };
    template <class ...FieldTypes, class ...Rest>
    struct Assignment<Property<FieldTypes...>, Rest...> : private Assignment<FieldTypes..., Rest...> {
      // Property<�c> �́c�̒���Property������ꍇ�͂�����
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
/// \brief  �v���p�e�B
///
///         Field<�c> �𕡐��ێ����܂��B
///         ����۔���A���̓X�g���[������̃f�[�^���͂Ȃ�Field<�c>���l�̋@�\��񋟂��܂��B
///         �t�B�[���h�ւ̃A�N�Z�X��field()���g�p���܂��B
///
/// \see    Field
///
/// \tparam FieldTypes  : �ێ�����t�B�[���h�̌^���X�g
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
        static_assert(impl::IsField<FieldType>::value, "'FieldType' must be of type 'Field<�c>'");
        static_assert(std::is_base_of_v<FieldType, Property>, "'FieldType' must be base for this Property<�c>'");

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

///< ���̓X�g���[������v���p�e�B�ւ̓���
template <class ...FieldTypes>
std::istream& operator>>(std::istream& Istream, Property<FieldTypes...>& Prop) {
    impl::Extractor<FieldTypes...>{Istream, Prop};
    return Istream;
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_PROPERTY_HEADER_
// EOF