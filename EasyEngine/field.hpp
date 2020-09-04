///
/// \file   field.hpp
/// \brief  �t�B�[���h�֌W��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/7/26
///             - �w�b�_�ǉ�
///             - Field<�c> ��`
///             - FieldTag<�c> ��`
///             - �⏕��`�A�錾(IsField, TypeIndex, AlwaysTrue)
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

  namespace field_impl {
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
  } // namespace field_impl

template <class ETy, uint32_t NIndex, class PredTy=field_impl::AlwaysTrue<ETy>, class TIndex=void>
using FieldTag = Field<ETy, field_impl::TypeIndex<NIndex, TIndex>, PredTy>;

/******************************************************************************

    Field

******************************************************************************/
///
/// \brief  �t�B�[���h
///
///         �����o�I�I�u�W�F�N�g�ł��B
///         ��3�^�����ɁA����������`�F�b�N����t�@���N�^���w�肷�邱�Ƃ��ł��܂��B
///
/// \tparam ElemTy : �t�B�[���h�v�f�^
/// \tparam IndexTy   : ����v�f�^�̃t�B�[���h����ʂ���C���f�b�N�X
/// \tparam PredTy    : ����۔���t�@���N�^
///
/// \details �t�@���N�^�͑���\��̒l��const�Q�ƂŎ󂯎��Abool��ԋp����operator()���`����K�v������܂��B\n
///          ���̂Ƃ��Atrue�ő�����s���Afalse�ł͑�����s���܂���B\n
///          ��Ԃ�ێ�����t�@���N�^����������ꍇ�A�R���X�g���N�^�ŏ���������K�v������܂��B\n
///          �v�f�^������ł���΁A�قȂ�t�B�[���h�Ԃő���������\�ł��B\n
///          ���̎��ɑ�������̂͗v�f�݂̂ŁA����۔���t�@���N�^���e�����󂯂邱�Ƃ͂���܂���B\n
///          ����۔���t�@���N�^��ύX�������ꍇ�́AsetPredicate()���g�p���ĉ������B
/// 
template <class ElemTy, class IndexTy, class PredTy=field_impl::AlwaysTrue<ElemTy>>
class Field : private PredTy {
public :
  // alias
    using ElemType = ElemTy;
    using PredType = PredTy;

  // concepts
    static_assert(std::is_invocable_r_v<bool, PredTy, ElemType>, "'PredTy' is invalid functor type");

    Field() = default;
    template <class Ty>
    Field(Ty&& Right) noexcept(noexcept(Field{std::forward<Ty>(Right), PredTy{}, field_impl::IsField<std::decay_t<Ty>>{}}))
        : Field{std::forward<Ty>(Right), PredTy{}, field_impl::IsField<std::decay_t<Ty>>{}} {}
    template <class Ty, class PTy>
    Field(Ty&& Right, PTy&& Pred)
        noexcept(noexcept(Field{std::forward<Ty>(Right),std::forward<PTy>(Pred),field_impl::IsField<std::decay_t<Ty>>{}}))
        : Field{std::forward<Ty>(Right), std::forward<PTy>(Pred), field_impl::IsField<std::decay_t<Ty>>{}} {}

    ///
    /// \brief  �l���Z�b�g
    ///
    ///         �t�B�[���h�̃Z�b�g�A�l�̃Z�b�g�ǂ�����\�ł��B
    ///         ����۔���t�@���N�^�͕ύX����܂���B
    ///
    /// \tparam Ty   : �Z�b�g����l�̌^
    /// \param Right : �Z�b�g����l
    ///
    /// \return �Z�b�g��t�B�[���h�ւ̎Q��
    ///
    template <class Ty>
    Field& operator=(Ty&& Right) noexcept(noexcept(assign(std::forward<Ty>(Right),field_impl::IsField<std::decay_t<Ty>>{}))){
        return assign(std::forward<Ty>(Right), field_impl::IsField<std::decay_t<Ty>>{});
    }
    ///< operator=���l
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
    /// \brief  ����ۃt�@���N�^���Z�b�g
    ///
    ///         Field<�c>::PredType�ɃR�s�[�\�A�������̓��[�u�\�ȃt�@���N�^�̂ݎ󂯕t���܂��B
    ///         ����ۃt�@���N�^�̌^���ƕϊ����邱�Ƃ͂ł��܂���B
    ///
    /// \tparam PredTy_ : �Z�b�g����t�@���N�^�̌^
    /// \param[in] Pred : �Z�b�g����t�@���N�^
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
