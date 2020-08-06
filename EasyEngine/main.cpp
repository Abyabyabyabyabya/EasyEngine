#include <Windows.h>
#include <iostream>
#include "xinput_gamepad.hpp"
#include "controller.hpp"
#include "xinput_controller.hpp"

using namespace easy_engine::i_lib;

struct O {
    void v(uint8_t) noexcept {
    
    }
    void nocfunc(float) noexcept {
    
    }
    void func(float, float) noexcept {
    
    }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    XInputP1 pad;
    O o;
    XInputController<O> ctrler{&pad};
    ctrler.map(XInputController<O>::Buttons::kA, &O::v);
    ctrler.map(XInputController<O>::Triggers::kLTrigger, &O::nocfunc);
    ctrler.map(XInputController<O>::Sticks::kLStick, &O::func);

    ctrler.map(XInputController<O>::Buttons::kA, &O::v,
               XInputController<O>::Triggers::kLTrigger, &O::nocfunc,
               XInputController<O>::Sticks::kLStick, &O::func);

    while(true) {
        pad.update();
        if(isUp(pad.getState().y))
            break;

        ctrler.run();
    }
}
