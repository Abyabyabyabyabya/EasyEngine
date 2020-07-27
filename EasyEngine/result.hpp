///
/// \file   result.hpp
/// \brief  �֐��߂�l�p�e���v���[�g�N���X�Q��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/7/27
///             - �w�b�_�ǉ�
///             - Result<�c> ��`
///             - DetailedResult<�c> ��`
///
#ifndef INCLUDED_EGEG_TLIB_RESULT_HEADER_
#define INCLUDED_EGEG_TLIB_RESULT_HEADER_

#include <stdexcept>
#include <type_traits>

namespace easy_engine {
namespace t_lib {
  namespace impl {
    [[noreturn]] void referenceError(std::string&& Func) {
        throw std::logic_error("reference to invalid value. func: "+Func);
    };
  } // namespace impl

struct Success{};
struct Failure{};

/******************************************************************************

    Result

******************************************************************************/
///
/// \class  Result
/// \brief  ��Ԃ����߂�l
///
///         �g�p��) 
///          ����: �c return Result{Success{}};
///          ���s: �c return Result{Failure{}, "hoghoge error"};
///         Result ���ȗ����Areturn {Success{}, �c};�@�ƋL�q���邱�Ƃ��\�ł��B
///
/// \tparam ValueTy : �߂�l�Ƃ��ĕێ�����l�̌^
///
/// \attention  Result<bool>�Ƃ��ăC���X�^���X�����邱�Ƃ��֎~���Ă��܂��B\n
///             ��������g�����炢�Ȃ�A�g�ݍ��݌^��bool���g���܂��傤�B
///
/// \note   value_�̍\�z�ɂ���\n
///         Result�̍\�z���AValueTy���N���X�̏ꍇ�̓f�t�H���g�̃R���X�g���N�^���Ăяo����邪�A\n
///         �g�ݍ��݌^�̏ꍇ�͌Ă΂�Ȃ��悤�ȃV�`���G�[�V����������B\n
///         �f�t�H���g�\�z���s����V�`���G�[�V�����ɂ����āA���̒l���g�p����邱�Ƃ͖����Ƃ����O��Ɋ�Â��A\n
///         �ق�̂�����Ƃ����œK���̂���
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
        if(!*this) impl::referenceError("Result<�c>::get");
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
/// \brief  ��ԂƁA�ڍׂ����߂�l
///
///         Result�̊g���łł��B
///         ��Ԃɒǉ����āA�ڍׂ�ێ����邱�Ƃ��ł��܂��B
///         �g�p��)
///          DetailedResult<Hoge*, std::string> f() {
///              ����: return {Success{}, new Hoge{}};
///              ���s: return {Failure{}, nullptr, "dead"};
///          }
///
/// \tparam ValueTy  : �߂�l�Ƃ��ĕێ�����l�̌^
/// \tparam DetailTy : �ڍׂƂ��ĕێ�����l�̌^
///
/// \note   �f�t�H���g�\�z�ɂ��āAResult�Ɠ��l
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
        if(!*this) impl::referenceError("DetailedResult<�c>::get");
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
class DetailedResult<bool, DetailTy> { // bool�^�ւ̕������ꉻ
public :
  // alias
    using ValueType = bool;
    using DetailType = DetailTy;

  // functions
    DetailedResult(Success) noexcept(std::is_nothrow_constructible_v<DetailType>) :
        condition_{true} /* detail_{default} */ {}

    template <class DtlTy>
    DetailedResult(Failure, DtlTy&& Detail) noexcept(noexcept(detail_(std::forward<DtlTy>(Detail)))) :
        condition_{false},
        detail_(std::forward<DtlTy>(Detail)) {}

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
