//
/// \file   texture.hpp
/// \brief  テクスチャハンドラ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/24
///             - ヘッダ追加
///             - Texture 定義
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_HEADER_

#include <type_traits>
#include "noncopyable.hpp"
#include "resource_common.hpp"
#include "easy_engine.hpp"

namespace easy_engine {
namespace g_lib {

// ※多重アンロードしないよう注意喚起
class Texture : public Resource {
public :
    template <class StrTy>
    Texture(StrTy&& FilePath) : Resource{EasyEngine::renderer().textureLoad(std::forward<StrTy>(FilePath))} {}
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF
