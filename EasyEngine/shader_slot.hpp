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

#include <vector>
#include <map>
#include <d3d11.h>
#include <wrl.h>
#include "constant_buffer.hpp"
#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    ShaderSlot

******************************************************************************/
///
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
    /// \param[in] Slot     : セットするスロット番号
    /// \param[in] Constant : セットする定数
    ///
    void setConstant(const UINT Slot, const ConstantBufferData& Constant) {
        constants_[Slot] = Constant.buffer();
    }
    ///
    /// \brief  複数の、スロット番号が連続した定数をセット
    ///
    ///         リストの先頭要素が、スロット番号StartSlotにセットされます。
    ///         残りの要素は順に1ずつ加算されたスロット番号にセットされます。
    ///
    /// \param[in] StartSlot : スロット開始番号
    /// \param[in] Constants : セットする定数リスト
    ///
    void setConstants(UINT StartSlot, const std::vector<ConstantBufferData>& Constants) {
        for(auto& constant : Constants)
            setConstant(StartSlot++, constant);
    }
    
    ///
    /// \brief  テクスチャをセット
    ///
    /// \param[in] Slot    : セットするスロット番号
    /// \param[in] Texture : セットするテクスチャ
    ///
    void setTexture(const UINT Slot, const Texture& Texture) {
        textures_[Slot] = Texture.texture();
    }
    ///
    /// \brief  複数の、スロット番号が連続した定数をセット
    ///
    ///         詳細はsetConstantsと同様です。
    ///
    /// \param[in] StartSlot : スロット開始番号
    /// \param[in] Textures  : セットするテクスチャリスト
    ///
    void setTextures(UINT StartSlot, const std::vector<Texture>& Textures) {
        for(auto& texture : Textures)
            setTexture(StartSlot++, texture);
    }

    // TODO : sampler


    /// スロット番号にマップされた定数バッファを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>>& constants() const noexcept { return constants_; }
    /// スロット番号にマップされたテクスチャを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>& textures() const noexcept { return textures_; }
    /// スロット番号にマップされたサンプラーを取得
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>>& samplers() const noexcept { return samplers_; }
//protected :
    ShaderSlot() = default;
private :
    void setConstant(const UINT) const noexcept {}
    void setTexture(const UINT) const noexcept {}
    void setSampler(const UINT) const noexcept {}

    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> constants_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
// EOF
