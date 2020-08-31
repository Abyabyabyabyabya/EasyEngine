///
/// \file   shader_slot.hpp
/// \brief  シェーダー基底クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/28
///             - ヘッダ追加
///             - Shader 定義
///         - 2020/8/31
///             - ヘッダ名変更(shader.hpp -> shader_slot.hpp)
///             - クラス名変更(Shader -> ShaderSlot)
///
#ifndef INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
#define INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_

#include <map>
#include <d3d11.h>
#include <wrl.h>
#include "constant_buffer.hpp"
#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  ShaderSlot
/// \brief  シェーダースロット
///
///         シェーダーへの入力を格納します。
///
class ShaderSlot {
public :
    virtual ~ShaderSlot() = default;

    ///
    /// \brief  定数をセット
    ///
    ///         複数の定数を一度にセットすることができます。
    ///         その場合、StartSlotから順に1つずつスロットがずれていきます。
    ///         スロットを飛ばしてセットしたい場合、複数の呼び出しに分けてください。
    ///
    /// \tparam DataTy : セットする定数のデータ型
    ///
    /// \param[in] StartSlot : セット開始スロット
    /// \param[in] Constant  : StartSlotにセットする定数
    /// \param[in] Constants : 残りの定数リスト
    ///
    template <class DataTy, class ...Rest>
    void setConstant(const UINT StartSlot, const ConstantBuffer<DataTy>& Constant, Rest ...Constants) {
        setConstant(StartSlot, Constant.buffer());
        setConstant(StartSlot+1, Constants...);
    }
    
    ///
    /// \brief  テクスチャをセット
    ///
    ///         詳細は setConstant と同様です。
    ///
    /// \param[in] StartSlot : セット開始スロット
    /// \param[in] Texture   : StartSlotにセットするテクスチャ
    /// \param[in] Textures  : 残りのテクスチャリスト
    ///
    template <class ...Rest>
    void setTexture(const UINT StartSlot, const Texture& Texture, Rest ...Textures) {
        setTexture(StartSlot, Texture.texture());
        setTexture(StartSlot+1, Textures...);
    }

    // TODO : sampler


    ///< スロット番号にマップされた定数バッファを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>>& constants() const noexcept { return constants_; }
    ///< スロット番号にマップされたテクスチャを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>& textures() const noexcept { return textures_; }
    ///< スロット番号にマップされたサンプラーを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>>& samplers() const noexcept { return samplers_; }
protected :
    ShaderSlot() = default;
private :
    void setConstant(const UINT) const noexcept {}
    void setConstant(const UINT Slot, ID3D11Buffer* Buffer) { constants_[Slot] = Buffer; }
    void setTexture(const UINT) const noexcept {}
    void setTexture(const UINT Slot, ID3D11ShaderResourceView* View) { textures_[Slot] = View; }
    void setSampler(const UINT) const noexcept {}
    void setSampler(const UINT Slot, ID3D11SamplerState* State) { samplers_[Slot] = State; }

    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> constants_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
// EOF
