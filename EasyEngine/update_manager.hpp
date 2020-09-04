///
/// \file   update_manager.hpp
/// \brief  更新処理マネージャー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/20
///             - ヘッダ追加
///             - UpdateScheduler 定義
///         - 2020/8/21
///             - 名前変更(ファイル名、クラス名、etc...)
/// 
#ifndef INCLUDED_EGEG_UPDATE_MANAGER_HEADER_
#define INCLUDED_EGEG_UPDATE_MANAGER_HEADER_

#include "task_manager.hpp"
#include "noncopyable.hpp"
#include "time.hpp"

namespace easy_engine {

namespace impl {
using UpdateFunctorType = std::function<void(Time)>;
} // namespace impl
using UpdateTaskInfo = t_lib::TaskManager<impl::UpdateFunctorType>::TaskInfo;

/******************************************************************************

    UpdateManager

******************************************************************************/
///
/// \brief  更新マネージャー
///
///         ゲーム更新処理に関するマネージャーです。
///         関数の登録、スケジューリング、呼び出し等を行います。
///         実装は t_lib::TaskManager<…>です。
///         詳細についても t_lib::TaskManager<…>を参照してください。
/// \see    t_lib::TaskManager
///
/// \tparam AdminTy : マネージャーを管理するクラス型
///
template <class AdminTy>
class UpdateManager final : t_lib::TaskManager<impl::UpdateFunctorType>, t_lib::Noncopyable<UpdateManager<AdminTy>> {
public :
    friend AdminTy;

    using TaskInfo = t_lib::TaskManager<impl::UpdateFunctorType>::TaskInfo;
    using t_lib::TaskManager<impl::UpdateFunctorType>::unregisterTask;

    ///
    /// \brief  タスクを登録
    ///
    ///         更新処理を登録します。
    ///         登録する更新関数はメンバ関数である必要があります。
    ///         登録例.) …registerTask(&hoge, &HogeClass::update, 6U);
    ///         ※registerTaskの戻り値は無視できません。
    ///
    /// \tparam OwnerTy : 関数のオーナークラス型
    /// \param[in] Owner    : 関数のオーナー
    /// \param[in] Function : 登録する更新関数へのポインタ
    /// \param[in] Priority : 関数の優先度
    ///
    /// \return タスクの登録情報
    ///
    template <class OwnerTy>
    [[nodiscard]] UpdateTaskInfo registerTask(
    OwnerTy* Owner, void(OwnerTy::*Function)(Time), const uint32_t Priority=5U) {
        return t_lib::TaskManager<impl::UpdateFunctorType>::registerTask(
            std::bind(Function, Owner, std::placeholders::_1), Priority);
    }

private :
    static std::unique_ptr<UpdateManager> create() { // AdminTyクラスにより呼び出される
        return std::unique_ptr<UpdateManager>(new UpdateManager());
    }
    using t_lib::TaskManager<impl::UpdateFunctorType>::run; // 上同 バッチ処理
    UpdateManager() = default;
};

} // namespace easy_engine
#endif // !INCLUDED_EGEG_UPDATE_MANAGER_HEADER_
// EOF
