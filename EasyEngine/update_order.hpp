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
///            kRenderEnd を変更してはいけません。
///
///
#ifndef INCLUDED_EGEG_UPDATE_ORDER_HEADER_
#define INCLUDED_EGEG_UPDATE_ORDER_HEADER_

namespace easy_engine {

enum UpdateOrder {
    kUpdateBegin = 5,

    // hogehoge
    // 自由に追加、削除してね

    kUpdateEnd,
    kRenderBegin,
    
    // hogehoge
    // 自由に追加、削除してね

    kRenderEnd,
};

}
#endif // !INCLUDED_EGEG_UPDATE_ORDER_HEADER_
// EOF
