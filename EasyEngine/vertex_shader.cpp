// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "vertex_shader.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    VertexShader::

******************************************************************************/
easy_engine::g_lib::VertexShader::VertexShader(const char* FilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout) {
    auto blob = loadShaderFile(FilePath);
    if(!blob) return;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateVertexShader(blob.bytecode, blob.size, nullptr, &vs)))
        return;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> il;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateInputLayout(Layout.data(), Layout.size(), blob.bytecode, blob.size, &il)))
        return;

    shader_ = std::move(vs);
    layout_ = std::move(il);
}
// EOF
