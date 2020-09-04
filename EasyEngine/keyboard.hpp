///
/// \file   keyboard.hpp
/// \brief  入力デバイス「キーボード」
///
/// \authro 板場
///
/// \par    履歴
///         - 2020/8/6
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_ILIB_KEYBOARD_HEADER_
#define INCLUDED_EGEG_ILIB_KEYBOARD_HEADER_

#include <vector>
#include <Windows.h>
#include "input_device.hpp"

namespace easy_engine {
namespace i_lib {

/******************************************************************************

    Keyboard

******************************************************************************/
///
/// \brief  キーボード
///
///         update()のみでは入力状態の更新は行われません。
///         evnentProcessing(…)によるイベント処理と組み合わせる必要があります。
///
class Keyboard : public InputDevice {
public :
    ///
    /// \struct 入力状態格納用構造体
    ///
    /// \details それぞれのメンバが、その名前が示すキーの状態を格納しています。\n
    ///          egeg::i_lib 名前空間にあるis~~ 関数を使用することで簡単に状態を調べることができます。
    ///
    struct State {
        InputFlagType padding0[8];           // 0x00 ~ 0x07
        InputFlagType backspace;             // 0x08
        InputFlagType tab;                   // 0x09
        InputFlagType padding1[3];           // 0x0A ~ 0x0C
        InputFlagType enter;                 // 0x0D
        InputFlagType padding2[13];          // 0x0E ~ 0x1A
        InputFlagType escape;                // 0x1B
        InputFlagType padding3[4];           // 0x1C ~ 0x1F
        InputFlagType space;                 // 0x20
        InputFlagType padding4[4];           // 0x21 ~ 0x24
        InputFlagType left;                  // 0x25
        InputFlagType up;                    // 0x26
        InputFlagType right;                 // 0x27
        InputFlagType down;                  // 0x28
        InputFlagType padding5[7];           // 0x29 ~ 0x2F
        InputFlagType zero;                  // 0x30
        InputFlagType one;                   // 0x31
        InputFlagType two;                   // 0x32
        InputFlagType three;                 // 0x33
        InputFlagType four;                  // 0x34
        InputFlagType five;                  // 0x35
        InputFlagType six;                   // 0x36
        InputFlagType seven;                 // 0x37
        InputFlagType eight;                 // 0x38
        InputFlagType nine;                  // 0x39
        InputFlagType padding6[7];           // 0x3A ~ 0x40
        InputFlagType a;                     // 0x41
        InputFlagType b;                     // 0x42
        InputFlagType c;                     // 0x43
        InputFlagType d;                     // 0x44
        InputFlagType e;                     // 0x45
        InputFlagType f;                     // 0x46
        InputFlagType g;                     // 0x47
        InputFlagType h;                     // 0x48
        InputFlagType i;                     // 0x49
        InputFlagType j;                     // 0x4A
        InputFlagType k;                     // 0x4B
        InputFlagType l;                     // 0x4C
        InputFlagType m;                     // 0x4D
        InputFlagType n;                     // 0x4E
        InputFlagType o;                     // 0x4F
        InputFlagType p;                     // 0x50
        InputFlagType q;                     // 0x51
        InputFlagType r;                     // 0x52
        InputFlagType s;                     // 0x53
        InputFlagType t;                     // 0x54
        InputFlagType u;                     // 0x55
        InputFlagType v;                     // 0x56
        InputFlagType w;                     // 0x57
        InputFlagType x;                     // 0x58
        InputFlagType y;                     // 0x59
        InputFlagType z;                     // 0x5A
        InputFlagType left_windows;          // 0x5B
        InputFlagType right_windows;         // 0x5C
        InputFlagType padding7[3];           // 0x5D ~ 0x5F
        InputFlagType numpad_0;              // 0x60
        InputFlagType numpad_1;              // 0x61
        InputFlagType numpad_2;              // 0x62
        InputFlagType numpad_3;              // 0x63
        InputFlagType numpad_4;              // 0x64
        InputFlagType numpad_5;              // 0x65
        InputFlagType numpad_6;              // 0x66
        InputFlagType numpad_7;              // 0x67
        InputFlagType numpad_8;              // 0x68
        InputFlagType numpad_9;              // 0x69
        InputFlagType padding8[6];           // 0x6A ~ 0x6F
        InputFlagType f1;                    // 0x70
        InputFlagType f2;                    // 0x71
        InputFlagType f3;                    // 0x72
        InputFlagType f4;                    // 0x73
        InputFlagType f5;                    // 0x74
        InputFlagType f6;                    // 0x75
        InputFlagType f7;                    // 0x76
        InputFlagType f8;                    // 0x77
        InputFlagType f9;                    // 0x78
        InputFlagType f10;                   // 0x79
        InputFlagType f11;                   // 0x7A
        InputFlagType f12;                   // 0x7B
        InputFlagType padding9[36];          // 0x7C ~ 0x9F
        InputFlagType left_shift;            // 0xA0
        InputFlagType right_shift;           // 0xA1
        InputFlagType left_ctrl;             // 0xA2
        InputFlagType right_ctrl;            // 0xA3
        InputFlagType left_alt;              // 0xA4
        InputFlagType right_alt;             // 0xA5
        InputFlagType padding10[20];         // 0xA6 ~ 0xB9
        InputFlagType colon;                 // 0xBA
        InputFlagType semicolon;             // 0xBB
        InputFlagType comma;                 // 0xBC
        InputFlagType minus;                 // 0xBD
        InputFlagType period;                // 0xBE
        InputFlagType slash;                 // 0xBF
        InputFlagType atmark;                // 0xC0
        InputFlagType padding11[26];         // 0xC1 ~ 0xDA
        InputFlagType left_square_bracket;   // 0xDB
        InputFlagType backslash;             // 0xDC
        InputFlagType right_square_bracket;  // 0xDD
        InputFlagType caret;                 // 0xDE
        InputFlagType padding12[17];         // 0xDF ~ 0xEF
        InputFlagType caps_lock;             // 0xF0
        InputFlagType padding13[2];          // 0xF1 ~ 0xF2
        InputFlagType kanji;                 // 0xF3
        InputFlagType padding14[11];         // 0xF4 ~ 0xFE
    };

    Keyboard();

    ///
    /// \brief  イベント処理
    ///
    ///         Windowsのコールバック関数にこの関数を記述してください。
    ///         入力状態を取得します。
    ///         入力状態の更新はこの関数では行われません。update関数を使用してください。
    ///
    /// \param[in] Msg : イベントメッセージ
    /// \param[in] wParam : イベント詳細
    /// \param[in] lParam : イベント詳細
    ///
    void eventProcessing(UINT Msg, WPARAM wParam, LPARAM lParam) noexcept;

    ///
    /// \brief  入力状態を取得
    ///
    /// \return 入力状態を格納した構造体
    ///
    const State& getState() const noexcept { return state_; }

// override
    void update() override;
private :
    void keyDown(uint8_t) noexcept;
    void keyUp(uint8_t) noexcept;
    InputFlagType newState(uint8_t) const noexcept;

    State state_{};
    std::vector<uint8_t> raw_;
    std::vector<uint8_t> last_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_KEYBOARD_HEADER_
// EOF
