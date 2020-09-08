#include <Windows.h>
#include "easy_engine.hpp"
#include "sampler_state.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    easy_engine::EasyEngine::run();

    using namespace easy_engine::g_lib;
    SamplerState sampler = sampler_presets::linearClamp();
}
