// �쐬�� : ��
/******************************************************************************

    include

******************************************************************************/
#include "keyboard.hpp"

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace keyboard_ns = easy_engine::i_lib;
namespace {
    constexpr size_t kBlockSize = sizeof(uint8_t)*8U;        // �R���e�i��1�u���b�N��bit��
    constexpr size_t kNumContainerBlock = 256U / kBlockSize; // 256bit ��ۑ����邽�߂ɕK�v�ȗv�f��
    constexpr size_t blockIdx(const uint8_t VK) noexcept { return static_cast<uint8_t>(VK * (1.0F/8.0F)); }
    constexpr uint8_t keyMask(const uint8_t VK) noexcept { return VK % 8; }
} // unnamed namespace

/******************************************************************************

    Keyboard::

******************************************************************************/
keyboard_ns::Keyboard::Keyboard() : raw_(kNumContainerBlock), last_(kNumContainerBlock) {}

void keyboard_ns::Keyboard::eventProcessing(const UINT Mes, const WPARAM wPrm, const LPARAM lPrm) noexcept {
    auto getDetailedVK = [wPrm]()->uint8_t { // �C���L�[�̏ꍇ���E����ʂ������z�L�[�R�[�h��ԋp
        if(wPrm==VK_SHIFT)
            return GetKeyState(VK_LSHIFT) ? VK_LSHIFT : VK_RSHIFT;
        if(wPrm==VK_CONTROL)
            return GetKeyState(VK_LCONTROL) ? VK_LCONTROL : VK_RCONTROL;
        if(wPrm==VK_MENU)
            return GetKeyState(VK_LMENU) ? VK_LMENU : VK_RMENU;
        return wPrm;
    };

    switch(Mes) {
    case WM_SYSKEYDOWN :
    case WM_KEYDOWN :
        keyDown(getDetailedVK());
        break;
    case WM_SYSKEYUP :
    case WM_KEYUP :
        keyUp(getDetailedVK());
        break;
    }
}

// ��Ԃ��i�[����\���̂̐擪�����Ԃ�ύX���Ă����B
// �|�C���^�ɂ�葖�����Ă��邽�߁A�g�p���Ă��Ȃ�padding�̈�ɂ��Ă���Ԃ̕ύX���s����
void keyboard_ns::Keyboard::update() {
    for(size_t i=0; i<kNumContainerBlock; ++i)
      for(size_t j=0; j<kBlockSize; ++j) {
          uint8_t vk = static_cast<uint8_t>(i*kBlockSize + j);
          InputFlagType* ptr = state_.padding0 + vk;
          *ptr = newState(vk);
      }

    std::swap(raw_, last_); // ���݂̏�Ԃ�O��̏�ԂցAraw_�͐V�K�C�x���g�ɂ��㏑�������悤�ɂȂ�
}

// �z��A�N�Z�X�ɂ���
// blockIdx�ɂ��Ԃ����l�́Auint8_t �̍ő�l255��n���Ă��؂�̂Ă���������31�ɂȂ�B�c 255 * (1.0F/8.0F) = 31.875F;
// �L�[�̏�Ԋi�[�p�R���e�i�̗v�f����32�Ȃ̂ŁA�͈͊O�A�N�Z�X�̗�O�͔������Ȃ�
void keyboard_ns::Keyboard::keyDown(const uint8_t VK) noexcept {
    raw_[blockIdx(VK)] |= keyMask(VK);
}

void keyboard_ns::Keyboard::keyUp(const uint8_t VK) noexcept {
    raw_[blockIdx(VK)] &= ~keyMask(VK);
}

keyboard_ns::InputFlagType keyboard_ns::Keyboard::newState(const uint8_t VK) const noexcept {
    auto isDown = [VK](const std::vector<uint8_t>& State)->bool {
        return State[blockIdx(VK)] & keyMask(VK);
    };

    if(!isDown(last_) && !isDown(raw_)) return kNoInput;
    if(isDown(last_) && isDown(raw_))   return kInput;
    if(isDown(raw_))                    return kDown;
                                        return kUp;
}
// EOF
