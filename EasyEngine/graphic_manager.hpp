///
/// \fiel   graphic_manager.hpp
/// \brief  グラフィックマネージャー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/21
///             - ヘッダ追加
///             - GraphicManager 定義
///
#ifndef INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_
#define INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_

#include <mutex>
#include <memory>
#include <vector>
#include <d3d11.h>
#include <wrl.h>
#include "noncopyable.hpp"
#include "update_manager.hpp"
#include "draw_context.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {

/******************************************************************************

    GraphicManager

******************************************************************************/
///
/// \brief  描画マネージャー
///
///         このクラスへのアクセスは、EasyEngine::graphics()を使用してください。
///
class GraphicManager final : t_lib::Noncopyable<GraphicManager> {
public :
    friend EasyEngine;

    ~GraphicManager();

    TextureResource capture(const TextureResource& Texture);
    void saveTexture(const char* FileName, const TextureResource& Image);
    Layer baseLayer() const noexcept { return base_layer_; }

    // note : スレッドセーフに実装
    void executeContext(const DrawContext& Context);


    /// 使用しているD3D機能レベルを取得
    D3D_FEATURE_LEVEL d3dFeatureLevel() const noexcept { return feature_level_; }
    /// D3Dデバイスを取得
    ID3D11Device& d3d11Device() const noexcept { return *device_.Get(); }
    /// D3Dイミディエイトコンテキストを取得
    ID3D11DeviceContext& d3d11Context() const noexcept { return *context_.Get(); }
private :
    static std::unique_ptr<GraphicManager> create(); // EasyEngineクラスにより呼び出される関数
    GraphicManager() = default;
    void render(Time);

    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
    Layer base_layer_;
    typename UpdateManager<EasyEngine>::TaskInfo task_;
    std::mutex drawing_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_
// EOF
