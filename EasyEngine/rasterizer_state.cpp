// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "rasterizer_state.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace rs_ns = easy_engine::g_lib;
namespace {
    constexpr D3D11_FILL_MODE kRasterizerFillModeMap[] {
        D3D11_FILL_WIREFRAME, // kWireframe
        D3D11_FILL_SOLID      // kSolid
    };

    constexpr D3D11_CULL_MODE kRasterizerCullModeMap[] {
        D3D11_CULL_NONE,  // kNone
        D3D11_CULL_FRONT, // kFront
        D3D11_CULL_BACK   // kBack
    };

    D3D11_RASTERIZER_DESC convertToD3DDesc(const rs_ns::RasterizerDesc&);
} // unnamed namespace


/******************************************************************************

    RasterizerState::

******************************************************************************/
rs_ns::RasterizerState::RasterizerState(const rs_ns::RasterizerDesc& Desc) {
    EasyEngine::graphics().d3d11Device().CreateRasterizerState(&convertToD3DDesc(Desc), &state_);
}


/******************************************************************************

    others

******************************************************************************/
namespace { D3D11_RASTERIZER_DESC convertToD3DDesc(const rs_ns::RasterizerDesc& Desc) {
    using namespace easy_engine::t_lib;
    return D3D11_RASTERIZER_DESC {
        kRasterizerFillModeMap[enumValue(Desc.fill_mode)],
        kRasterizerCullModeMap[enumValue(Desc.cull_mode)],
        Desc.front==rs_ns::RasterizerFront::kClockWise ? TRUE : FALSE,
        Desc.depth_bias,
        Desc.depth_bias_clamp,
        Desc.slope_scaled_depth_bias,
        Desc.depth_clip_enable,
        Desc.scissor_enable,
        Desc.multisample_enable,
        Desc.antialiased_line_enable
    };
}}
// EOF
