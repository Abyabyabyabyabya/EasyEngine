///
/// \file   pixel_shader.hpp
/// \brief  ピクセルシェーダー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/28
///             - ヘッダ追加
///             - PixelShader 定義
///
#ifndef INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_

#include "shader_common.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  PixelShader
/// \brief  ピクセルシェーダー
///
/// \par    読み込みを遅延させたい場合
///         - デフォルトコンストラクタで構築したシェーダーに代入
///           PixelShader ps{};
///             …
///           ps = PixelShader{"hogehoge.xxx", …};
///
/// \attention  このクラス単体でも使用できますが、シェーダーごとにこのクラスを基底とした詳細クラスを定義した方が\n
///             可読性が上がりますし、可搬性も上がると思うのでお勧めします。\n
///
class PixelShader {
public :
    PixelShader() = default;

    ///
    /// \brief  読み込みを伴うコンストラクタ
    ///
    /// \param[in] ShaderFilePath : 読み込むシェーダーファイルのパス
    ///
    PixelShader(const char* ShaderFilePath);

    ///
    /// \brief  有効なピクセルシェーダーか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return shader_; }
    operator bool() const noexcept { return isValid(); }


    ///< シェーダーオブジェクトを取得
    ID3D11PixelShader* shader() const noexcept { return shader_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_
// EOF
