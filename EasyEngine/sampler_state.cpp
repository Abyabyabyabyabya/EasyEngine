// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "sampler_state.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace sampler_ns = easy_engine::g_lib;
namespace {
    constexpr D3D11_FILTER kSamplerFilterMap[] {
        D3D11_FILTER_MIN_MAG_MIP_POINT,                          // kMinMagMipPoint
        D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,                   // kMinMagPointMipLinear
        D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,             // kMinPointMagLinearMipPoint
        D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,                   // kMinPointMagMipLinear
        D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,                   // kMinLinearMagMipPoint
        D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,            // MinLinearMagPointMipLinear
        D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,                   // MinMagLinearMipPoint
        D3D11_FILTER_MIN_MAG_MIP_LINEAR,                         // MinMagMipLinear
        D3D11_FILTER_ANISOTROPIC,                                // kAnisotropic
        D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,               // kComparisonMinMagMipPoint
        D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,        // kComparisonMinMagPointMipLinear
        D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,  // kComparisonMinPointMagLinearMipPoin
        D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,        // kComparisonMinPointMagMipLinear
        D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,        // kComparisonMinLinearMagMipPoint
        D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR, // MComparisoninLinearMagPointMipLinear
        D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,        // MComparisoninMagLinearMipPoint
        D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,              // MComparisoninMagMipLinear
        D3D11_FILTER_COMPARISON_ANISOTROPIC,                     // kComparisonAnisotropic
        D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT,                  // kMinimumMinMagMipPoint
        D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,           // kMinimumMinMagPointMipLinear
        D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,     // kMinimumMinPointMagLinearMipPoint
        D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,           // kMinimumMinPointMagMipLinear
        D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,           // kMinimumMinLinearMagMipPoint
        D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,    // MMinimuminLinearMagPointMipLinear
        D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,           // MMinimuminMagLinearMipPoint
        D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,                 // MMinimuminMagMipLinear
        D3D11_FILTER_MINIMUM_ANISOTROPIC,                        // kMinimumAnisotropic
        D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT,                  // kMaximumMinMagMipPoint
        D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,           // kMaximumMinMagPointMipLinear
        D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,     // kMaximumMinPointMagLinearMipPoint
        D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,           // kMaximumMinPointMagMipLinear
        D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,           // kMaximumMinLinearMagMipPoint
        D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,    // MMaximuminLinearMagPointMipLinear
        D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,           // MMaximuminMagLinearMipPoint
        D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,                 // MMaximuminMagMipLinear
        D3D11_FILTER_MAXIMUM_ANISOTROPIC                         // kMaximumAnisotropic
    };                                                              
                                                                    
    constexpr D3D11_TEXTURE_ADDRESS_MODE kSamplerAddressModeMap[] { 
        D3D11_TEXTURE_ADDRESS_WRAP,       // kWrap
        D3D11_TEXTURE_ADDRESS_MIRROR,     // kMirror
        D3D11_TEXTURE_ADDRESS_CLAMP,      // kClamp
        D3D11_TEXTURE_ADDRESS_BORDER,     // kBorder
        D3D11_TEXTURE_ADDRESS_MIRROR_ONCE // kMirrorOnce
    };

    constexpr D3D11_COMPARISON_FUNC kSamplerComparisonMap[] {
        D3D11_COMPARISON_NEVER,         // kNever
        D3D11_COMPARISON_LESS,          // kLess
        D3D11_COMPARISON_EQUAL,         // kEqual
        D3D11_COMPARISON_LESS_EQUAL,    // kLessEqual
        D3D11_COMPARISON_GREATER,       // kGreater
        D3D11_COMPARISON_NOT_EQUAL,     // kNotEqual
        D3D11_COMPARISON_GREATER_EQUAL, // kGreaterEqual
        D3D11_COMPARISON_ALWAYS         // kAlways
    };

    D3D11_SAMPLER_DESC convertToD3DDesc(const sampler_ns::SamplerDesc&);
} // unnamed namespace


/******************************************************************************

    SamplerState::

******************************************************************************/
sampler_ns::SamplerState::SamplerState(const sampler_ns::SamplerDesc& Desc) {
    EasyEngine::graphics().d3d11Device().CreateSamplerState(&convertToD3DDesc(Desc), &state_);
}


/******************************************************************************

    others

******************************************************************************/
namespace { 
  constexpr float toNormal(const std::uint8_t Color) { return Color * (1.0F/255.0F); }
  D3D11_SAMPLER_DESC convertToD3DDesc(const sampler_ns::SamplerDesc& Desc) {
    using namespace easy_engine::t_lib;
    float kBorderColor[4] {
        toNormal(Desc.border_color.red()),
        toNormal(Desc.border_color.green()),
        toNormal(Desc.border_color.blue()),
        toNormal(Desc.border_color.alpha()),
    };
    return D3D11_SAMPLER_DESC {
        kSamplerFilterMap[enumValue(Desc.filter)],
        kSamplerAddressModeMap[enumValue(Desc.address_u)],
        kSamplerAddressModeMap[enumValue(Desc.address_v)],
        kSamplerAddressModeMap[enumValue(Desc.address_w)],
        Desc.mip_lod_bias,
        Desc.max_anisotropy,
        kSamplerComparisonMap[enumValue(Desc.comparison)],
        *kBorderColor,
        Desc.min_lod,
        Desc.max_lod
    };
  }
}
// EOF
