///
/// \fiel   graphics_manager.hpp
/// \brief  グラフィックマネージャー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/21
///             - ヘッダ追加
///             - GraphicsManager 定義
///
#ifndef INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
#define INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_

#include <memory>
#include "noncopyable.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {

class GraphicsManager final : t_lib::Noncopyable<GraphicsManager> {
public :
    friend EasyEngine;

private :
    static std::unique_ptr<GraphicsManager> create(); // EasyEngineクラスにより呼び出される関数
    GraphicsManager() = default;
};

} // namespace g_lib
} // namespace easy_engine
#endif  // !INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
// EOF
