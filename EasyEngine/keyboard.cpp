// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "keyboard.hpp"

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace keyboard_ns = easy_engine::i_lib;
namespace {
    constexpr size_t kBlockSize = sizeof(uint8_t)*8U;        // コンテナの1ブロックのbit数
    constexpr size_t kNumContainerBlock = 256U / kBlockSize; // 256bit を保存するために必要な要素数
    constexpr size_t blockIdx(const uint8_t VK) noexcept { return static_cast<uint8_t>(VK * (1.0F/8.0F)); }
    constexpr uint8_t keyMask(const uint8_t VK) noexcept { return VK % 8; }
} // unnamed namespace

/******************************************************************************

    Keyboard::

******************************************************************************/
keyboard_ns::Keyboard::Keyboard() : raw_(kNumContainerBlock), last_(kNumContainerBlock) {}

void keyboard_ns::Keyboard::eventProcessing(const UINT Mes, const WPARAM wPrm, const LPARAM lPrm) noexcept {
    auto getDetailedVK = [wPrm]()->uint8_t { // 修飾キーの場合左右を区別した仮想キーコードを返却
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

// 状態を格納する構造体の先頭から状態を変更していく。
// ポインタにより走査しているため、使用していないpadding領域についても状態の変更が行われる
void keyboard_ns::Keyboard::update() {
    for(size_t i=0; i<kNumContainerBlock; ++i)
      for(size_t j=0; j<kBlockSize; ++j) {
          uint8_t vk = static_cast<uint8_t>(i*kBlockSize + j);
          InputFlagType* ptr = state_.padding0 + vk;
          *ptr = newState(vk);
      }

    std::swap(raw_, last_); // 現在の状態を前回の状態へ、raw_は新規イベントにより上書きされるようになる
}

// 配列アクセスについて
// blockIdxにより返される値は、uint8_t の最大値255を渡しても切り捨てが発生して31になる。… 255 * (1.0F/8.0F) = 31.875F;
// キーの状態格納用コンテナの要素数は32なので、範囲外アクセスの例外は発生しない
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
