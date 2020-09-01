///
/// \file   update_order.hpp
/// \brief  更新順序定義ヘッダ
///
///         更新マネージャーに更新処理を登録する際の、
///         優先順位指定に使用します。
///         必要に合わせて変更を加えてください。
///
/// \attention kUpdateBegin
///            kUpdateEnd
///            kRenderBegin
///            kRenderEnd について、\n
///            更新処理登録時に使用することは問題ありませんが、
///            位置関係の変更、数値の代入等々、変更を加えてはいけません。
///
#ifndef INCLUDED_EGEG_UPDATE_ORDER_HEADER_
#define INCLUDED_EGEG_UPDATE_ORDER_HEADER_

namespace easy_engine {
enum UpdateOrder {
  kUpdateBegin = 5,
// ↓↓↓ 自由に追加、削除してね ↓↓↓

    

// ↑↑↑ 自由に追加、削除してね ↑↑↑
  kUpdateEnd,
///////////////////////////////////////////////
  kRenderBegin,
// ↓↓↓ 自由に追加、削除してね ↓↓↓

    

// ↑↑↑ 自由に追加、削除してね ↑↑↑
  kRenderEnd,
  kRenderScreen,
///////////////////////////////////////////////
// ↓↓↓ 自由に追加、削除してね ↓↓↓

    

// ↑↑↑ 自由に追加、削除してね ↑↑↑
};
}
#endif // !INCLUDED_EGEG_UPDATE_ORDER_HEADER_
// EOF
