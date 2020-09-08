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
        DXGI_FORMAT_UNKNOWN,                    // kUnknown
        DXGI_FORMAT_R32G32B32A32_TYPELESS,      // kRGBA32Typeless
        DXGI_FORMAT_R32G32B32A32_FLOAT,         // kRGBA32Float
        DXGI_FORMAT_R32G32B32A32_UINT,          // kRGBA32Uint
        DXGI_FORMAT_R32G32B32A32_SINT,          // kRGBA32Sint
        DXGI_FORMAT_R32G32B32_TYPELESS,         // kRGB32Typeless
        DXGI_FORMAT_R32G32B32_FLOAT,            // kRGB32Float
        DXGI_FORMAT_R32G32B32_UINT,             // kRGB32Uint
        DXGI_FORMAT_R32G32B32_SINT,             // kRGB32Sint
        DXGI_FORMAT_R16G16B16A16_TYPELESS,      // kRGBA16Typeless
        DXGI_FORMAT_R16G16B16A16_FLOAT,         // kRGBA16Float
        DXGI_FORMAT_R16G16B16A16_UNORM,         // kRGBA16Unorm
        DXGI_FORMAT_R16G16B16A16_UINT,          // kRGBA16Uint
        DXGI_FORMAT_R16G16B16A16_SNORM,         // kRGBA16Snorm
        DXGI_FORMAT_R16G16B16A16_SINT,          // kRGBA16Sint
        DXGI_FORMAT_R32G32_TYPELESS,            // kRG32Typeless
        DXGI_FORMAT_R32G32_FLOAT,               // kRG32Float
        DXGI_FORMAT_R32G32_UINT,                // kRG32Uint
        DXGI_FORMAT_R32G32_SINT,                // kRG32Sint
        DXGI_FORMAT_R32G8X24_TYPELESS,          // kR32G8X24Typeless
        DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,   // kR32FloatX8x24Typeless
        DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,    // kX32TypelessG8X24Uint
        DXGI_FORMAT_R10G10B10A2_TYPELESS,       // kRGB10A2Typeless
        DXGI_FORMAT_R10G10B10A2_UNORM,          // kRGB10A2Unorm
        DXGI_FORMAT_R10G10B10A2_UINT,           // kRGB10A2Uint
        DXGI_FORMAT_R11G11B10_FLOAT,            // kRG11B10Float
        DXGI_FORMAT_R8G8B8A8_TYPELESS,          // kRGBA8Typeless
        DXGI_FORMAT_R8G8B8A8_UNORM,             // kRGBA8Unorm
        DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,        // kRGBA8UnormSRGB
        DXGI_FORMAT_R8G8B8A8_UINT,              // kRGBA8Uint
        DXGI_FORMAT_R8G8B8A8_SNORM,             // kRGBA8Snorm
        DXGI_FORMAT_R8G8B8A8_SINT,              // kRGBA8Sint
        DXGI_FORMAT_R16G16_TYPELESS,            // kRG16Typeless
        DXGI_FORMAT_R16G16_FLOAT,               // kRG16Float
        DXGI_FORMAT_R16G16_UNORM,               // kRG16Unorm
        DXGI_FORMAT_R16G16_UINT,                // kRG16Uint
        DXGI_FORMAT_R16G16_SNORM,               // kRG16Snorm
        DXGI_FORMAT_R16G16_SINT,                // kRG16Sint
        DXGI_FORMAT_R32_TYPELESS,               // kR32Typeless
        DXGI_FORMAT_R32_FLOAT,                  // kR32Float
        DXGI_FORMAT_R32_UINT,                   // kR32Uint
        DXGI_FORMAT_R32_SINT,                   // kR32Sint
        DXGI_FORMAT_R24G8_TYPELESS,             // kR24G8Typeless
        DXGI_FORMAT_R24_UNORM_X8_TYPELESS,      // kR24UnormX8Typeless
        DXGI_FORMAT_X24_TYPELESS_G8_UINT,       // kX24TypelessG8Uint
        DXGI_FORMAT_R8G8_TYPELESS,              // kRG8Typeless
        DXGI_FORMAT_R8G8_UNORM,                 // kRG8Unorm
        DXGI_FORMAT_R8G8_UINT,                  // kRG8Uint
        DXGI_FORMAT_R8G8_SNORM,                 // kRG8Snorm
        DXGI_FORMAT_R8G8_SINT,                  // kRG8Sint
        DXGI_FORMAT_R16_TYPELESS,               // kR16Typeless
        DXGI_FORMAT_R16_FLOAT,                  // kR16Float
        DXGI_FORMAT_R16_UNORM,                  // kR16Unorm
        DXGI_FORMAT_R16_UINT,                   // kR16Uint
        DXGI_FORMAT_R16_SNORM,                  // kR16Snorm
        DXGI_FORMAT_R16_SINT,                   // kR16Sint
        DXGI_FORMAT_R8_TYPELESS,                // kR8Typeless
        DXGI_FORMAT_R8_UNORM,                   // kR8Unorm
        DXGI_FORMAT_R8_UINT,                    // kR8Uint
        DXGI_FORMAT_R8_SNORM,                   // kR8Snorm
        DXGI_FORMAT_R8_SINT,                    // kR8Sint
        DXGI_FORMAT_A8_UNORM,                   // kA8Unorm
        DXGI_FORMAT_R1_UNORM,                   // kR1Unorm
        DXGI_FORMAT_R9G9B9E5_SHAREDEXP,         // kRGB9E5SharedExp
        DXGI_FORMAT_R8G8_B8G8_UNORM,            // kRG8BG8Unorm
        DXGI_FORMAT_G8R8_G8B8_UNORM,            // kGR8GB8Unorm
        DXGI_FORMAT_BC1_TYPELESS,               // kBC1Typeless
        DXGI_FORMAT_BC1_UNORM,                  // kBC1Unorm
        DXGI_FORMAT_BC1_UNORM_SRGB,             // kBC1UnormSRGB
        DXGI_FORMAT_BC2_TYPELESS,               // kBC2Typeless
        DXGI_FORMAT_BC2_UNORM,                  // kBCUnorm
        DXGI_FORMAT_BC2_UNORM_SRGB,             // kBC2UnormSRGB
        DXGI_FORMAT_BC3_TYPELESS,               // kBC3Typeless
        DXGI_FORMAT_BC3_UNORM,                  // kBC3Unorm
        DXGI_FORMAT_BC3_UNORM_SRGB,             // kBC3UnormSRGB
        DXGI_FORMAT_BC4_TYPELESS,               // kBC4Typeless
        DXGI_FORMAT_BC4_UNORM,                  // kBC4Unorm
        DXGI_FORMAT_BC4_SNORM,                  // kBC4Snorm
        DXGI_FORMAT_BC5_TYPELESS,               // kBC5Typeless
        DXGI_FORMAT_BC5_UNORM,                  // kBC5Unorm
        DXGI_FORMAT_BC5_SNORM,                  // kBC5Snorm
        DXGI_FORMAT_B5G6R5_UNORM,               // kB5G6R5Unorm
        DXGI_FORMAT_B5G5R5A1_UNORM,             // kBGR5A1Unorm
        DXGI_FORMAT_B8G8R8A8_UNORM,             // kBGRA8Unorm
        DXGI_FORMAT_B8G8R8X8_UNORM,             // kBGRX8Unorm
        DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM, // kRGB10XRBiasA2Unorm
        DXGI_FORMAT_B8G8R8A8_TYPELESS,          // kBGRA8Typeless
        DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,        // kBGRA8UnormSRGB
        DXGI_FORMAT_B8G8R8X8_TYPELESS,          // kBGRX8Typeless
        DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,        // kBGRX8UnormSRGB
        DXGI_FORMAT_BC6H_TYPELESS,              // kBC6HTypeless
        DXGI_FORMAT_BC6H_UF16,                  // kBC6HUF16
        DXGI_FORMAT_BC6H_SF16,                  // kBC6HSF16
        DXGI_FORMAT_BC7_TYPELESS,               // kBC7Typeless
        DXGI_FORMAT_BC7_UNORM,                  // kBC7Unorm
        DXGI_FORMAT_BC7_UNORM_SRGB,             // kBC7UnormSRGB
        DXGI_FORMAT_B4G4R4A4_UNORM,             // kBGRA4Unorm
    };
} // unnamed namespace


/******************************************************************************

    Layer

******************************************************************************/
layer_ns::Layer::Layer(const unsigned Width, const unsigned Height, const Layer::Format TexFormat, const UINT SCount, const UINT SQuality) :
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
