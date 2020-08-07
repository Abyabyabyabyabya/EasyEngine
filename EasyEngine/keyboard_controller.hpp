///
/// \file   keyboard_controller.hpp
/// \brief  �L�[�{�[�h�p�R���g���[���[
///
/// \author ��
///
/// \par    ����
///         - 2020/8/7
///             - �w�b�_�ǉ�
///
#ifndef INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_

#include "controller.hpp"
#include "keyboard.hpp"

namespace easy_engine {
namespace i_lib {

template <class TargetTy>
class KeyboardController : public Controller<TargetTy> {
public :

// override
    void run() override;
private :

};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_
// EOF
