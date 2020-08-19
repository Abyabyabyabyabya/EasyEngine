#include <Windows.h>
#include <iostream>
#include "xinput_gamepad.hpp"
#include "controller.hpp"
#include "xinput_controller.hpp"
#include "keyboard_controller.hpp"
#include "input_manager.hpp"

using namespace easy_engine::i_lib;

struct O {
    void v(uint8_t Flag) noexcept {
        if(isUp(Flag))
            exit(0);
    }
    virtual void n(uint8_t Flag) {
    }
    void nocfunc(float Value) {
        if(Value > 0.8)
        exit(0);
    }
    void func(float, float) noexcept {
    
    }
};
struct D : O {
    void n(uint8_t Flag) override {

        if(isDown(Flag))
            exit(0);
    }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    XInputP1 pad;
    O o;
    D d;
    XInputController<O> ctrler{&pad, &o};
    ctrler.map(XInputController<O>::Buttons::kA, &O::v);
    ctrler.map(XInputController<O>::Triggers::kLTrigger, &O::nocfunc);
    ctrler.map(XInputController<O>::Sticks::kLStick, &O::func);

    ctrler.map(XInputController<O>::Buttons::kA, &O::v,
               XInputController<O>::Triggers::kLTrigger, &O::nocfunc,
               XInputController<O>::Sticks::kLStick, &O::func);

    ctrler.unmap(XInputController<O>::Buttons::kA);
    ctrler.map(XInputController<O>::Buttons::kLThumbStick, &O::n);

    while(true) {
        pad.update();
        if(isUp(pad.getState().a))
            ctrler.resetTarget(&d);
        ctrler.run();
    }

    using OController = KeyboardController<O>;
    OController k{nullptr,&o};
    k.map(OController::Keys::k0, &O::v);
    k.map(OController::Keys::kCapsLock, &O::n);
    k.unmap(OController::Keys::kCapsLock, OController::Keys::k0);

    

}
