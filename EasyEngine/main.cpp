#include <Windows.h>
#include <iostream>
#include "easy_engine.hpp"

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
    easy_engine::EasyEngine::run();
}
