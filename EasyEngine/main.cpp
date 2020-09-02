#include <Windows.h>
#include "easy_engine.hpp"
#include "render_mesh.hpp"
#include "shader_slot.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    easy_engine::EasyEngine::run();

    using namespace easy_engine::g_lib;

    ShaderSlot slot;
    slot.setConstant(0, {ConstantBuffer<int>{}, ConstantBuffer<float>{}});
}
