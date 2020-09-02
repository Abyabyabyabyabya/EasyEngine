///
/// \file   egeg.hpp
/// \brief  EasyEngineの機能を全て含むヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/7/23
///             - ヘッダー追加
///             - 名前空間を定義
///         - 2020/9/2
///             - 名前空間別名宣言
///             - EasyEngineインクルード、別名定義
///
#ifndef INCLUDED_EGEG_HEADER_
#define INCLUDED_EGEG_HEADER_

/******************************************************************************

    namespace

******************************************************************************/
namespace easy_engine { // EasyEngine用名前空間
    namespace a_lib{} 
    namespace g_lib{} 
    namespace i_lib{} 
    namespace m_lib{} 
    namespace t_lib{}
} // namespace easy_engine

namespace egeg          = easy_engine;          // EasyEngine用名前空間
namespace egeg_audio    = easy_engine::a_lib;   // オーディオ用名前空間
namespace egeg_graphics = easy_engine::g_lib;   // 描画用名前空間
namespace egeg_input    = easy_engine::i_lib;   // 入力用名前空間
namespace egeg_math     = easy_engine::m_lib;   // 数学用名前空間
namespace egeg_template = easy_engine::t_lib;   // テンプレート用名前空間

/******************************************************************************

    include

******************************************************************************/
#include "easy_engine.hpp"

/******************************************************************************

    alias

******************************************************************************/
namespace easy_engine { using EGEG = EasyEngine; }

#endif // !INCLUDED_EGEG_HEADER_
// EOF
