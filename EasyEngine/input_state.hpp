///
/// \file   input_state.hpp
/// \brief  ���͏�ԂɊւ����`�Q�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/5
///             - �w�b�_�ǉ�
///             - InputFlagType ��`
///             - ���͏�Ԕ���֐���`
///
#ifndef INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_
#define INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_

#include <cstdint>

namespace easy_engine {
namespace i_lib {

using InputFlagType = uint8_t;

constexpr InputFlagType kNoInput = 0b000U; ///< ���͂Ȃ�
constexpr InputFlagType kInput   = 0b001U; ///< ���͂���t���O
constexpr InputFlagType kDown    = 0b010U; ///< ��������t���O
constexpr InputFlagType kUp      = 0b100U; ///< ���㒼��t���O

///
/// \brief  ���͂��肩�ǂ�������
///
/// \param[in] State : ���肷����͂̏��
///
/// \return ���͂������true�@�Ȃ����false
///
inline constexpr bool isInput(const InputFlagType State) noexcept {
    return State & kInput;
}

///
/// \brief  ���͂��p����Ԃɂ��邩�ǂ�������
///
///         ���͒���̏�Ԃ�false�Ƃ݂Ȃ��܂��B
///
/// \param[in] State : ���肷����͂̏��
///
/// \return �p����Ԃł����true�@�łȂ����false
///
inline constexpr bool isHold(const InputFlagType State) noexcept {
    return State == kInput;
}

///
/// \brief  ���͒���̏�Ԃ��ǂ�������
///
/// \param[in] State : ���肷����͂̏��
///
/// \return ���͒���ł����true�@�����łȂ����false
///
inline constexpr bool isDown(const InputFlagType State) noexcept {
    return State & kDown;
}

///
/// \brief  ���͉�������̏�Ԃ��ǂ�������
///
/// \param[in] State : ���肷����͂̏��
///
/// \ return ��������ł����true�@�����łȂ����false
///
inline constexpr bool isUp(const InputFlagType State) noexcept {
    return State & kUp;
}

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_
// EOF
