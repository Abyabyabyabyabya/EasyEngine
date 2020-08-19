///
/// \file   input_device.hpp
/// \brief  ���̓f�o�C�X����`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/5
///             - �w�b�_�ǉ�
///             - InputDevice ��`
///
#ifndef INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_

#include "noncopyable.hpp"
#include "input_state.hpp"

namespace easy_engine {
namespace i_lib {

/******************************************************************************

    InputDevice

******************************************************************************/
///
/// \class  InputDevice
/// \brief  ���̓f�o�C�X���
///
///         ���͂Ɋւ���N���X�͂��̃N���X�����Ƃ��Ă��������B
///         �R�s�[�̓f�t�H���g�ŋ֎~���Ă��܂��B
///         �h���N���X�ŁA�R�s�[���T�|�[�g����ꍇ�́A�����I�ɃR�s�[���Z���`���Ă��������B
///         
class InputDevice : t_lib::Noncopyable<InputDevice> {
public :
    virtual ~InputDevice() = default;

    ///
    /// \brief  �X�V����
    ///
    ///         �h���N���X�͂��̊֐����I�[�o�[���C�h���A
    ///         ���͏�Ԃ̍X�V���s���Ă��������B
    ///
    virtual void update() = 0;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_
// EOF
