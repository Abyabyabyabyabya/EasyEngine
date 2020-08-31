///
/// \file   vertex_shader.hpp
/// \brief  頂点シェーダー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/28
///             - ヘッダ追加
///             - VertexShader 定義
///
#ifndef INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_

#include <vector>
#include "shader_common.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  VertexShader
/// \brief  頂点シェーダー
///
/// \par    読み込みを遅延させたい場合
///         - デフォルトコンストラクタで構築したシェーダーに代入
///           VertexShader vs{};
///             …
///           vs = VertexShader{"hogehoge.xxx", …};
///
/// \attention  このクラス単体でも使用できますが、シェーダーごとにこのクラスを基底とした詳細クラスを定義した方が\n
///             可読性が上がりますし、可搬性も上がると思うのでお勧めします。\n
///
class VertexShader {
public :
    virtual ~VertexShader() = default;
    VertexShader() = default;

    ///
    /// \brief  読み込みを伴うコンストラクタ
    ///
    /// \param[in] ShaderFilePath : 読み込むシェーダーファイルのパス
    /// \param[in] InputLayout    : 読み込む頂点シェーダーの入力レイアウト
    ///
    VertexShader(const char* ShaderFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout);

    ///
    /// \brief  有効な頂点シェーダーか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return shader_ && layout_; }
    operator bool() const noexcept { return isValid(); }

    
    ///< シェーダーオブジェクトを取得
    ID3D11VertexShader* shader() const noexcept { return shader_.Get(); }
    ///< 入力レイアウトオブジェクトを取得
    ID3D11InputLayout* layout() const noexcept { return layout_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_
// EOF
