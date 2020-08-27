// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "texture.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace tex_ns = easy_engine::g_lib;


/******************************************************************************

    Texture::

******************************************************************************/
tex_ns::Texture::Texture(const char* FilePath) {
    // 画像ファイル読み込み
    //  … 後々 …
    // テクスチャ作成
    //  d3dDevice->CreateTexture2D(&desc, image_data, &tex);
    // ビュー作成
    //  d3dDevice->CreateShaderResourceView(tex, nullptr, &srv);
    D3D11_RASTERIZER_DESC;
    D3D11_SAMPLER_DESC;
    D3D11_BLEND_DESC;
}
// EOF
