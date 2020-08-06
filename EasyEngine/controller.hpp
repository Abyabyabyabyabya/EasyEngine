///
/// \file   controller.hpp
/// \brief  �R���g���[���[��`�w�b�_
///
///         �R���g���[���[�͑���\�I�u�W�F�N�g�Ɠ��̓f�o�C�X�̈ˑ��֌W���z������ړI�Ő݌v����܂��B
///         �T�O�I�ɁA�R���g���[���[�͓��̓L�[�Ə����̃}�b�s���O���s���܂��B
///
/// \author ��
///
/// \par    ����
///         - 2020/8/6
///             - �w�b�_�ǉ�
///             - Controller ��`
///
#ifndef INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_

#include <stdexcept>
#include "noncopyable.hpp"

namespace easy_engine {
namespace i_lib {
  namespace ctrler_impl {
      [[noreturn]] void invokeError() {
          throw std::logic_error{"invalid target function invoked"}; 
      }
  } // namespace ctrler_impl

///
/// \class  Controller
/// \brief  �R���g���[���[���
///
///         �e��f�o�C�X�ɑΉ������h���N���X�ŁA���͂ɑΉ������֐���o�^���鏈�����������Ă��������B
///         �R���g���[���[�̓f�o�C�X�ł͂���܂���B
///         �Ӑ}���Ȃ��R�s�[�ɂ��s�������邽�߁A�f�t�H���g�ŃR�s�[���֎~���Ă��܂��B
///         �h���N���X�ŁA�R�s�[���T�|�[�g����ꍇ�́A�����I�ɃR�s�[���Z���`���Ă��������B
///
/// \tparam TargetTy : ����Ώۂ̃I�u�W�F�N�g�^
///
template <class TargetTy>
class Controller : t_lib::Noncopyable<Controller<TargetTy>> {
public :
    using TargetType = TargetTy;

    Controller(TargetType* Target=nullptr) noexcept : target_{Target} {}
    virtual ~Controller() = default;

    ///
    /// \brief  ���̊֐����Ăяo���ꂽ���_�̓��͏�Ԃŏ������s��
    ///
    virtual void run() = 0;

    ///
    /// \brief  ����Ώۂ��Z�b�g
    ///
    ///         �f�t�H���g�ł́A����Ώۂ��������܂��B
    ///
    /// \param[in] Target : �Z�b�g���鑀��Ώ�
    ///
    void resetTarget(TargetType* Target=nullptr) noexcept { target_ = Target; }
    ///
    /// \brief  ����Ώۂ̃A�h���X���擾
    ///
    ///         nullptr���ԋp���ꂽ�ꍇ�A����Ώۂ����Ȃ����Ƃ�\���܂��B
    ///
    /// \return ����Ώۂ̃A�h���X
    ///
    const TargetType* getTarget() const noexcept { return target_; }

protected :
    template <class RetTy, class ...FArgTypes, class ...ArgTypes>
    RetTy invoke(RetTy(TargetType::*Function)(FArgTypes...), ArgTypes&& ...Args) const {
        if(!target_) ctrler_impl::invokeError();
        return (target_->*Function)(std::forward<ArgTypes>(Args)...);
    }
    template <class RetTy, class ...FArgTypes, class ...ArgTypes>
    RetTy invoke(RetTy(TargetType::*Function)(FArgTypes...) const, ArgTypes&& ...Args) const {
        if(!target_) ctrler_impl::invokeError();
        return (target_->*Function)(std::forward<ArgTypes>(Args)...);
    }

private :
    TargetType* target_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_
// EOF
