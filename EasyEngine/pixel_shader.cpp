 // �쐬�� : ��
/******************************************************************************

    include

******************************************************************************/
#include "pixel_shader.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    PixelShader::

******************************************************************************/
easy_engine::g_lib::PixelShader::PixelShader(const char* FilePath) {
    if(auto blob = shader_impl::loadShaderFile(FilePath))
        EasyEngine::graphics().d3d11Device().CreatePixelShader(blob.bytecode, blob.size, nullptr, &shader_);
}
// EOF
