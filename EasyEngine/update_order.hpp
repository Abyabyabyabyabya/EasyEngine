///
/// \file   update_order.hpp
/// \brief  更新順序定義ヘッダ
///
///         更新マネージャーに更新処理を登録する際の、
///         優先順位指定に使用します。
///         必要に合わせて変更を加えてください。
///
#ifndef INCLUDED_EGEG_UPDATE_ORDER_HEADER_
#define INCLUDED_EGEG_UPDATE_ORDER_HEADER_

namespace easy_engine {
enum UpdateOrder {
  kUpdateBegin = 5,



  kUpdateEnd,
  kCollisionDetection,
  kRenderBegin,



  kRenderEnd,
  kRenderScreen,
};
}
#endif // !INCLUDED_EGEG_UPDATE_ORDER_HEADER_
// EOF
