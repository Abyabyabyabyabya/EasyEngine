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
///
#ifndef INCLUDED_EGEG_HEADER_
#define INCLUDED_EGEG_HEADER_

/******************************************************************************

    namespace

******************************************************************************/
namespace easy_engine { // EasyEngine用名前空間
    namespace a_lib{}   // AudioLIBrary       オーディオライブラリ用名前空間
    namespace g_lib{}   // GraphicsLIBrary    描画ライブラリ用名前空間
    namespace i_lib{}   // InpurLIBrary       入力ライブラリ用名前空間
    namespace m_lib{}   // MathLIBrary        数学ライブラリ用名前空間
    namespace t_lib{}   // TemplateLIBrary    テンプレートライブラリ用名前空間
}
namespace egeg = easy_engine;

/******************************************************************************

    include

******************************************************************************/
#include "easy_engine.hpp"

/******************************************************************************

    alias

******************************************************************************/
using EGEG = egeg::EasyEngine;

#endif // !INCLUDED_EGEG_HEADER_
// EOF
