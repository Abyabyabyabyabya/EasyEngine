// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "layer.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace layer_ns = easy_engine::g_lib;


/******************************************************************************

    Layer

******************************************************************************/
layer_ns::Layer::Layer(const UINT Width, const UINT Height, const UINT SCount, const UINT SQuality) :
    Texture{} {
    // テクスチャを作成
    Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2d;
    D3D11_TEXTURE2D_DESC tex_desc;
    tex_desc.Width = Width;
    tex_desc.Height = Height;
    tex_desc.MipLevels = 0;
    tex_desc.ArraySize = 1;
    tex_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT;
    tex_desc.SampleDesc.Count = SCount;
    tex_desc.SampleDesc.Quality = SQuality;
    tex_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
    tex_desc.CPUAccessFlags = 0U;
    tex_desc.MiscFlags = 0U;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateTexture2D(&tex_desc, nullptr, &tex2d)))
        return;

    // 各種ビューを作成
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateRenderTargetView(tex2d.Get(), nullptr, &rtv)))
        return;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateShaderResourceView(tex2d.Get(), nullptr, &srv)))
        return;


    resource_ = std::move(tex2d);
    layer_    = std::move(rtv);
    texture_  = std::move(srv);
}
// EOF
