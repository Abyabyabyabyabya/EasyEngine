///
/// \file   draw_context.hpp
/// \brief  描画コンテキスト定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/10
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
#define INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER

#include <d3d11.h>
#include <wrl.h>
#include "layer.hpp"
#include "depth_stencil_texture.hpp"
#include "depth_stencil_state.hpp"
#include "blend_state.hpp"
#include "rasterizer_state.hpp"
#include "sampler_state.hpp"
#include "shader_slot.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "render_mesh.hpp"

namespace easy_engine {
namespace g_lib {

class DrawContext {
public :
    DrawContext();

    ///
    /// \brief  テクスチャをキャプチャ
    ///
    ///         引数のテクスチャをキャプチャして返却
    ///         戻り値のテクスチャは画像ファイルとして保存することが可能
    ///
    /// \param[in] Texture : キャプチャするテクスチャ
    ///
    /// \return キャプチャ済みテクスチャ
    ///
    TextureResource capture(const TextureResource& Texture);
    
    ///
    /// \brief  コンテキストをクリア
    ///
    void clear();
    ///
    /// \brief  レイヤーをクリア(塗りつぶす)
    ///
    /// \param[in] Target : クリアするレイヤー
    /// \param[in] ClearColor : 塗りつぶす色
    ///
    void clearLayer(const Layer& Target, const float(&ClearColor)[4]);

    ///
    /// \brief  描画対象となるレイヤーをセット
    ///
    /// \param[in] Target       : セットするレイヤー
    /// \param[in] DepthStencil : 深度テクスチャ
    ///
    void setLayer(const Layer& Target, const DepthStencilTexture& DepthStencil=DepthStencilTexture{});
    ///
    /// \brief  描画対象となるレイヤーを一度に複数セット
    ///
    /// \param[in] Targets   : セットするレイヤーリスト
    /// \param[in] DepthStencil : 深度テクスチャ
    ///
    void setLayer(const std::vector<Layer>& Targets, const DepthStencilTexture& DepthStencil=DepthStencilTexture{});

    ///
    /// \brief  ブレンドの状態をセット
    ///
    /// \param[in] BS          : ブレンドの状態定義オブジェクト
    /// \param[in] BlendFactor : ブレンド時定数
    /// \param[in] SampleMask  : マルチサンプル描画ターゲットにおいての、サンプル用マスク
    ///
    /// BlendFactorはブレンドステートのブレンド係数に、kBlendFactorかkInvBlendFactorが選択されているときのみ有効
    //  
    ///
    void setBlendState(const BlendState& BS, const float(&BlendFactor)[4], UINT SampleMask=kMaskRGBA);
    ///
    /// \brief  深度ステンシルの状態をセット
    ///
    /// \param[in] DS         : 深度ステンシルの状態定義オブジェクト
    /// \param[in] StencilRef : ステンシルテストで使用する参照値
    ///
    void setDepthStencilState(const DepthStencilState& DS, UINT StencilRef=0);
    ///
    ///
    /// \brief  ラスタライザの状態をセット
    ///
    /// \param[in] RS : ラスタライザの状態定義オブジェクト
    ///
    void setRasterizerState(const RasterizerState& RS);

    ///
    /// \brief  頂点シェーダ―をセット
    ///
    /// \param[in] VS : 頂点シェーダ―
    ///
    void setVertexShader(const VertexShader& VS);
    ///
    /// \brief  頂点シェーダ―のシェーダースロットをセット
    ///
    /// \param[in] Slot : スロット
    ///
    void setVertexShaderSlot(const ShaderSlot& Slot);
    ///
    /// \brief  ジオメトリシェーダ―をセット
    ///
    /// \param[in] GS : ジオメトリシェーダ―
    ///
    void setGeometryShader(const GeometryShader& GS);
    ///
    /// \brief  ジオメトリシェーダーのシェーダースロットをセット
    ///
    /// \param[in] Slot : スロット
    ///
    void setGeometryShaderSlot(const ShaderSlot& Slot);
    ///
    /// \brief  ピクセルシェーダ―をセット
    ///
    /// \param[in] PS : ピクセルシェーダ―
    ///
    void setPixelShader(const PixelShader& PS);
    ///
    /// \brief  ピクセルシェーダーのシェーダースロットをセット
    ///
    /// \param[in] Slot : スロット
    ///
    void setPixelShaderSlot(const ShaderSlot& Slot);

    ///
    /// \brief  メッシュを描画
    ///
    /// \param[in] Mesh : 描画するメッシュ
    /// \param[in] IndexCount : 描画する頂点数
    /// \param[in] BaseIndexLocation : 描画を開始する頂点インデックスの開始点
    /// \param[in] BaseVertexLocation : 描画を開始する頂点の開始点
    ///
    void draw(const RenderMesh& Mesh, UINT IndexCount, UINT BaseIndexLocation=0, INT BaseVertexLocation=0);
    ///
    /// \brief  メッシュのインスタンシング描画
    ///
    /// \param[in] InstanceCount : 描画するインスタンス数
    /// \param[in] Mesh : 描画するメッシュ
    /// \param[in] IndexCountPerMesh : メッシュ毎の描画する頂点数
    /// \param[in] BaseIndexLocation : 描画を開始する頂点インデックスの開始点
    /// \param[in] BaseVertexLocation : 描画を開始する頂点の開始点
    /// \param[in] StartInstanceLocation : 描画を開始するインスタンスの開始点
    ///
    void drawInstanced(UINT InstanceCount, const RenderMesh& Mesh, UINT IndexCountPerMesh, UINT BaseIndexLocation=0, INT BaseVertexLocation=0, UINT StartInstanceLocation=0);
    
    ///
    /// \brief  コンテキストを確定
    ///
    ///         この関数を呼び出した後に、コンテキストに変更を加えることが可能です。
    ///         この場合、再度finish関数が呼び出されるまで、前回のコンテキストは保持されます。
    ///
    void finish();

    ///
    /// \brief  有効な描画コンテクストかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return context_; }
    operator bool() const noexcept { return context_; }


    ///< ディファードコンテキストを取得
    ID3D11DeviceContext* context() const noexcept { return context_.Get(); }
    ///< 描画コマンドリストを取得
    ID3D11CommandList* commands() const noexcept { return commands_.Get(); }
protected :
    DrawContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& Context) noexcept : context_{Context} {}
private :
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<ID3D11CommandList> commands_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
// EOF
