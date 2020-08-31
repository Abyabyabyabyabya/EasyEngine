 // çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "pixel_shader.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    PixelShader::

******************************************************************************/
easy_engine::g_lib::PixelShader::PixelShader(const char* FilePath) {
    auto blob = shader_impl::loadShaderFile(FilePath);
    if(!blob) return;

    Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreatePixelShader(blob.bytecode, blob.size, nullptr, &ps)))
        return;

    shader_ = std::move(ps);
}
// EOF
