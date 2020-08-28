// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "graphic_manager.hpp"
#include "egeg_state.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"
#include "update_order.hpp"

#pragma comment(lib, "d3d11.lib")

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace gm_ns = easy_engine::g_lib;
namespace {
    class BaseLayer : public gm_ns::Layer {
    public :
        BaseLayer(ID3D11Device* D3DDevice, ID3D11Texture2D* BackBuffer) : Layer{} {
            // スワップチェインのバックバッファを参照する各種ビューを作成
            Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
            if(FAILED(D3DDevice->CreateRenderTargetView(BackBuffer, nullptr, &rtv)))
                return;
            Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
            if(FAILED(D3DDevice->CreateShaderResourceView(BackBuffer, nullptr, &srv)))
                return;

            resource_ = BackBuffer;
            layer_ = std::move(rtv);
            texture_ = std::move(srv);
        }
    };

    DXGI_SWAP_CHAIN_DESC swapChainDesc();

    constexpr D3D_FEATURE_LEVEL kFeatureLevels[] {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

#ifdef _DEBUG
    constexpr UINT kDeviceCreateFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
    constexpr UINT kDeviceCreateFlag = 0U;
#endif
} // unnamed namespace


/******************************************************************************

    GraphicManager::

******************************************************************************/
gm_ns::GraphicManager::~GraphicManager() = default;

std::unique_ptr<gm_ns::GraphicManager> gm_ns::GraphicManager::create() {
    std::unique_ptr<GraphicManager> ptr{new GraphicManager{}};
    
    // DirectXを初期化
    if(FAILED(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                kDeviceCreateFlag,
                kFeatureLevels,
                t_lib::arraySize(kFeatureLevels),
                D3D11_SDK_VERSION,
                &swapChainDesc(),
                &ptr->swap_chain_,
                &ptr->device_,
                &ptr->feature_level_,
                &ptr->context_))) {
        if(FAILED(D3D11CreateDeviceAndSwapChain(
                    nullptr,
                    D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_WARP,
                    nullptr,
                    kDeviceCreateFlag,
                    kFeatureLevels,
                    t_lib::arraySize(kFeatureLevels),
                    D3D11_SDK_VERSION,
                    &swapChainDesc(),
                    &ptr->swap_chain_,
                    &ptr->device_,
                    &ptr->feature_level_,
                    &ptr->context_))) {
            return nullptr;
        }
    }
    
    // ベースレイヤーを初期化
    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
    if(FAILED(ptr->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &back_buffer)))
        return nullptr;
    ptr->base_layer_ = BaseLayer{ptr->device_.Get(), back_buffer.Get()};

    // 描画処理を登録
    ptr->task_ = EasyEngine::updator().registerTask(ptr.get(), &GraphicManager::render, UpdateOrder::kRenderEnd+1);

    return ptr;
}

void gm_ns::GraphicManager::capture(const char* FileName, const gm_ns::Texture& Image) {
    // d3dDevice.ResourceCopy(Image.resource());
    // save to file
}

void gm_ns::GraphicManager::render(Time) {
    swap_chain_->Present(0, 0);
}


/******************************************************************************

    others

******************************************************************************/
namespace { DXGI_SWAP_CHAIN_DESC swapChainDesc() {
    using namespace easy_engine;
    return DXGI_SWAP_CHAIN_DESC {
        DXGI_MODE_DESC {                    // BufferDesc
            kWindowWidth<UINT>,                      // .Width
            kWindowHeight<UINT>,                     // .Height
            DXGI_RATIONAL{                           // .RefreshRate
                kFPS<UINT>,                                 // .Numerator
                1U,                                         // .Denominator
            },
            DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, // .Format
            DXGI_MODE_SCANLINE_ORDER{},              // .SwanlineOrdering,
            DXGI_MODE_SCALING{}                      // .Scaling
        },
        DXGI_SAMPLE_DESC {                  // SampleDesc
            1U,                                 // .Count
            0U                                  // .Quality
        },
        DXGI_USAGE_RENDER_TARGET_OUTPUT |   // BufferUsage
        DXGI_USAGE_SHADER_INPUT,
        1U,                                 // BufferCount
        EasyEngine::window().handle(),      // OutputWindowl
        state::kWindowed,                   // Windowed
        DXGI_SWAP_EFFECT{},                 // SwapEffect
        DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH // Flags
    };
} }
// EOF
