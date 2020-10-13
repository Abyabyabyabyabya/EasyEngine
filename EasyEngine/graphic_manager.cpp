// �쐬�� : ��
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
    class ImmediateContext : public gm_ns::DrawContext {
    public :
        ImmediateContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& Context) noexcept : DrawContext{Context} {}
    };

    class BaseLayer : public gm_ns::Layer {
    public :
        BaseLayer(ID3D11Device* D3DDevice, ID3D11Texture2D* BackBuffer) {
            // �X���b�v�`�F�C���̃o�b�N�o�b�t�@���Q�Ƃ���e��r���[���쐬
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
    
    // DirectX��������
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
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
                &context))) {
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
                    &context))) {
            return nullptr;
        }
    }
    ptr->context_ = ImmediateContext{context};
    
    // �x�[�X���C���[��������
    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
    if(FAILED(ptr->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &back_buffer)))
        return nullptr;
    ptr->base_layer_ = BaseLayer{ptr->device_.Get(), back_buffer.Get()};

    // �`�揈����o�^
    ptr->task_ = EasyEngine::updator().registerTask(ptr.get(), &GraphicManager::render, UpdateOrder::kRenderScreen);

    return ptr;
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
        EasyEngine::window().handle(),      // OutputWindow
        state::kWindowed,                   // Windowed
        DXGI_SWAP_EFFECT{},                 // SwapEffect
        DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH // Flags
    };
} }
// EOF
