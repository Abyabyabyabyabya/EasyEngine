// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "layer.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace layer_ns = easy_engine::g_lib;
namespace {
    constexpr DXGI_FORMAT kFormatMap[] {
        DXGI_FORMAT::DXGI_FORMAT_UNKNOWN,                    // UNKNOWN
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_TYPELESS,      // R32G32B32A32_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,         // R32G32B32A32_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT,          // R32G32B32A32_UINT
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT,          // R32G32B32A32_SINT
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32_TYPELESS,         // R32G32B32_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,            // R32G32B32_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT,             // R32G32B32_UINT
        DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT,             // R32G32B32_SINT
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_TYPELESS,      // R16G16B16A16_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT,         // R16G16B16A16_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UNORM,         // R16G16B16A16_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UINT,          // R16G16B16A16_UINT
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SNORM,         // R16G16B16A16_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SINT,          // R16G16B16A16_SINT
        DXGI_FORMAT::DXGI_FORMAT_R32G32_TYPELESS,            // R32G32_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,               // R32G32_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT,                // R32G32_UINT
        DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT,                // R32G32_SINT
        DXGI_FORMAT::DXGI_FORMAT_R32G8X24_TYPELESS,          // R32G8X24_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,   // R32_FLOAT_X8X24_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,    // X32_TYPELESS_G8X24_UINT
        DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_TYPELESS,       // R10G10B10A2_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UNORM,          // R10G10B10A2_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UINT,           // R10G10B10A2_UINT
        DXGI_FORMAT::DXGI_FORMAT_R11G11B10_FLOAT,            // R11G11B10_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_TYPELESS,          // R8G8B8A8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,             // R8G8B8A8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,        // R8G8B8A8_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT,              // R8G8B8A8_UINT
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SNORM,             // R8G8B8A8_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SINT,              // R8G8B8A8_SINT
        DXGI_FORMAT::DXGI_FORMAT_R16G16_TYPELESS,            // R16G16_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R16G16_FLOAT,               // R16G16_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R16G16_UNORM,               // R16G16_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R16G16_UINT,                // R16G16_UINT
        DXGI_FORMAT::DXGI_FORMAT_R16G16_SNORM,               // R16G16_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R16G16_SINT,                // R16G16_SINT
        DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS,               // R32_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,                  // R32_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R32_UINT,                   // R32_UINT
        DXGI_FORMAT::DXGI_FORMAT_R32_SINT,                   // R32_SINT
        DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS,             // R24G8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS,      // R24_UNORM_X8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_X24_TYPELESS_G8_UINT,       // X24_TYPELESS_G8_UINT
        DXGI_FORMAT::DXGI_FORMAT_R8G8_TYPELESS,              // R8G8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM,                 // R8G8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R8G8_UINT,                  // R8G8_UINT
        DXGI_FORMAT::DXGI_FORMAT_R8G8_SNORM,                 // R8G8_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R8G8_SINT,                  // R8G8_SINT
        DXGI_FORMAT::DXGI_FORMAT_R16_TYPELESS,               // R16_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT,                  // R16_FLOAT
        DXGI_FORMAT::DXGI_FORMAT_R16_UNORM,                  // R16_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R16_UINT,                   // R16_UINT
        DXGI_FORMAT::DXGI_FORMAT_R16_SNORM,                  // R16_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R16_SINT,                   // R16_SINT
        DXGI_FORMAT::DXGI_FORMAT_R8_TYPELESS,                // R8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_R8_UNORM,                   // R8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R8_UINT,                    // R8_UINT
        DXGI_FORMAT::DXGI_FORMAT_R8_SNORM,                   // R8_SNORM
        DXGI_FORMAT::DXGI_FORMAT_R8_SINT,                    // R8_SINT
        DXGI_FORMAT::DXGI_FORMAT_A8_UNORM,                   // A8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R1_UNORM,                   // R1_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R9G9B9E5_SHAREDEXP,         // R9G9B9E5_SHAREDEXP
        DXGI_FORMAT::DXGI_FORMAT_R8G8_B8G8_UNORM,            // R8G8_B8G8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_G8R8_G8B8_UNORM,            // G8R8_G8B8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC1_TYPELESS,               // BC1_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM,                  // BC1_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM_SRGB,             // BC1_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_BC2_TYPELESS,               // BC2_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC2_UNORM,                  // BC2_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC2_UNORM_SRGB,             // BC2_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_BC3_TYPELESS,               // BC3_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM,                  // BC3_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM_SRGB,             // BC3_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_BC4_TYPELESS,               // BC4_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM,                  // BC4_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC4_SNORM,                  // BC4_SNORM
        DXGI_FORMAT::DXGI_FORMAT_BC5_TYPELESS,               // BC5_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM,                  // BC5_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC5_SNORM,                  // BC5_SNORM
        DXGI_FORMAT::DXGI_FORMAT_B5G6R5_UNORM,               // B5G6R5_UNORM
        DXGI_FORMAT::DXGI_FORMAT_B5G5R5A1_UNORM,             // B5G5R5A1_UNORM
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM,             // B8G8R8A8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_UNORM,             // B8G8R8X8_UNORM
        DXGI_FORMAT::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM, // R10G10B10_XR_BIAS_A2_UNORM
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_TYPELESS,          // B8G8R8A8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,        // B8G8R8A8_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_TYPELESS,          // B8G8R8X8_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,        // B8G8R8X8_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_BC6H_TYPELESS,              // BC6H_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC6H_UF16,                  // BC6H_UF16
        DXGI_FORMAT::DXGI_FORMAT_BC6H_SF16,                  // BC6H_SF16
        DXGI_FORMAT::DXGI_FORMAT_BC7_TYPELESS,               // BC7_TYPELESS
        DXGI_FORMAT::DXGI_FORMAT_BC7_UNORM,                  // BC7_UNORM
        DXGI_FORMAT::DXGI_FORMAT_BC7_UNORM_SRGB,             // BC7_UNORM_SRGB
        DXGI_FORMAT::DXGI_FORMAT_B4G4R4A4_UNORM,             // B4G4R4A4_UNORM
    };
} // unnamed namespace


/******************************************************************************

    Layer

******************************************************************************/
layer_ns::Layer::Layer(const UINT Width, const UINT Height, const Layer::Format TexFormat, const UINT SCount, const UINT SQuality) :
  TextureResource{
    D3D11_TEXTURE2D_DESC {
      Width, Height,
      0, 1,
      kFormatMap[t_lib::enumValue(TexFormat)],
      DXGI_SAMPLE_DESC {
        SCount, SQuality
      },
      D3D11_USAGE::D3D11_USAGE_DEFAULT,
      D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
      0U,
      0U}
  } {
    if(!TextureResource::isValid()) return;

    // äeéÌÉrÉÖÅ[ÇçÏê¨
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateRenderTargetView(resource(), nullptr, &rtv)))
        return;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
    if(FAILED(EasyEngine::graphics().d3d11Device().CreateShaderResourceView(resource(), nullptr, &srv)))
        return;


    layer_    = std::move(rtv);
    texture_  = std::move(srv);
}
// EOF
