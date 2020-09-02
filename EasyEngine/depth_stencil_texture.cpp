// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "depth_stencil_texture.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace dstexture_ns = easy_engine::g_lib;
namespace {
    constexpr DXGI_FORMAT kFormatMap[] {
        DXGI_FORMAT_D32_FLOAT_S8X24_UINT, // D32_FLOAT_S8X24_UINT
        DXGI_FORMAT_D32_FLOAT,            // D32_FLOAT
        DXGI_FORMAT_D24_UNORM_S8_UINT,    // D24_UNORM_S8_UINT
        DXGI_FORMAT_D16_UNORM             // D16_UNORM
    };
} // unnamed namespace


/******************************************************************************

    DepthStencilTexture::

******************************************************************************/
dstexture_ns::DepthStencilTexture::DepthStencilTexture(const UINT Width, const UINT Height, const DepthStencilTexture::Format TexFormat, const UINT SCount, const UINT SQuality) :
  TextureResource {
    D3D11_TEXTURE2D_DESC {
      Width, Height,
      0, 1,
      kFormatMap[t_lib::enumValue(TexFormat)],
      DXGI_SAMPLE_DESC {
        SCount, SQuality
      },
      D3D11_USAGE::D3D11_USAGE_DEFAULT,
      D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL,
      0U,
      0U}
  } {
    if(!TextureResource::isValid()) return;

    // ÉrÉÖÅ[ÇçÏê¨
    EasyEngine::graphics().d3d11Device().CreateDepthStencilView(resource(), nullptr, &texture_);
}
// EOF
