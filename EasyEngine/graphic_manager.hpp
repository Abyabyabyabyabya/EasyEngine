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
#ifndef INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
#define INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_

#include <memory>
#include <d3d11.h>
#include <wrl.h>
#include "noncopyable.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {

///
/// \class  GraphicManager
/// \brief  描画マネージャー
///
///         このクラスへのアクセスは、EasyEngine::graphics()を使用してください。
///
class GraphicManager final : t_lib::Noncopyable<GraphicManager> {
public :
    friend EasyEngine;

    ~GraphicManager();

    ///
    /// \brief  使用しているD3D機能レベルを取得
    ///
    /// \return 機能レベル
    ///
    D3D_FEATURE_LEVEL d3dFeatureLevel() const noexcept { return feature_level_; }
    
    ///
    /// \brief  D3Dデバイスを取得
    ///
    /// \return D3Dデバイス
    ///
    ID3D11Device& d3d11Device() const noexcept { return *device_.Get(); }

    ///
    /// \brief  D3Dコンテキストを取得
    ///
    /// \return D3Dコンテキスト
    ///
    ID3D11DeviceContext& d3d11Context() const noexcept { return *context_.Get(); }

    //IDXGISwapChain& dxgiSwapChain() const noexcept { return *swap_chain_.Get(); }

private :
    static std::unique_ptr<GraphicManager> create(); // EasyEngineクラスにより呼び出される関数
    GraphicManager() = default;

    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_{};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_{};
    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_{};
};

} // namespace g_lib
} // namespace easy_engine
#endif  // !INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
// EOF
