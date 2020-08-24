///
/// \file   model.hpp
/// \brief  モデルハンドラ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/24
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_GLIB_MODEL_HEADER_
#define INCLUDED_EGEG_GLIB_MODEL_HEADER_

#include "resource_common.hpp"
#include "graphics_manager.hpp"

namespace easy_engine {
namespace g_lib {

class Model : public Resource {
public :
    template <class StrTy>
    Model(StrTy&& FilePath) : Resource{EasyEngine::renderer().modelLoad(std::forward<StrTy>(FilePath)} {}

    void update(Time DeltaTime) { EasyEngine::renderer().modelUpdate(handle(), DeltaTime); }
    void setAnimatino(int AnimID) { EasyEngine::renderer().modelSetAnimation(handle(), AnimID); }
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_MODEL_HEADER_
// EOF
