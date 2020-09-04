///
/// \file   task_manager.hpp
/// \brief  タスクマネージャー定義ヘッダ
///
/// \author 板場
///
/// \note   TaskTyについて、boolに変換可能であることを表すコンセプトを追加しようとしたが\n
///         C++17 std::is_convertible_v<…> では暗黙的な変換しか判定ができず不完全。\n
///         C++20 では、std::convertible_toにより実現可能。
///
/// \par    履歴
///         - 2020/7/25
///             - ヘッダ追加
///             - TaskManager<…> 定義
///         - 2020/7/26
///             - TaskTy に関するコンセプトを追加
///             - コメント追加
///
#ifndef INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_
#define INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_

#include <cstdint>
#include <type_traits>
#include "noncopyable.hpp"
#include "event_container.hpp"

namespace easy_engine {
namespace t_lib {
    
/******************************************************************************

    TaskManager

******************************************************************************/
//
/// \class  TaskManager
/// \brief  タスクマネージャー
///
///         バッチ処理をサポートします。
///         タスクは優先度によりスケジューリングされ、優先度は小さいほど高く、先に呼び出されます。
///
/// \tparam TaskTy : 登録するタスクの型
/// \tparam DefaultPriority : デフォルトで設定する優先度
///
/// \details TaskTy はファンクタ型か、戻り値型(引数型リスト) の形で指定します。
///
/// \attention TaskTy はboolに変換可能(暗黙、明示的問わず)である必要があります。
///
template <class TaskTy, uint32_t DefaultPriority=0U>
class TaskManager {
public :
  // aliases
    using TaskType = event_impl::EventType<TaskTy>;

  // concepts
    static_assert(std::is_default_constructible_v<TaskType>, "'TaskType' must be the default constructible type");
    static_assert(std::is_move_constructible_v<TaskType>, "'TaskType' must be the movable type");
    static_assert(std::is_move_assignable_v<TaskType>, "'TaskType' must be the movable type");

  // nested class
    ///< タスク登録情報
    class TaskInfo final : Noncopyable<TaskInfo> {
    public :
        friend TaskManager;

        TaskInfo() = default;
        TaskInfo(TaskInfo&& Right) noexcept : id_{Right.id_}, priority_{Right.priority_}, manager_{Right.manager_} {
            Right.manager_ = nullptr; 
        }
        TaskInfo& operator=(TaskInfo&& Right) noexcept {
            id_ = Right.id_;
            priority_ = Right.priority_;
            manager_ = Right.manager_;
            Right.manager_ = nullptr;

            return *this;
        }
        ~TaskInfo() { exitFromManager(); }
        void exitFromManager() { if(manager_) manager_->unregisterTask(*this); }

    private :
        TaskInfo(size_t ID,uint32_t Priority,TaskManager* Manager) : id_{ID}, priority_{Priority}, manager_{Manager} {}
        size_t id_;
        uint32_t priority_;
        TaskManager* manager_;
    };

  // functions
    ///
    /// \brief  タスクを登録
    ///
    ///         タスクの優先度は小さいほど高く、先に呼び出されます。
    ///         戻り値のオブジェクトはタスクの登録解除に必要です。
    ///         また、スコープから抜けると自動でタスクの登録を解除するので、
    ///         必要であればメンバ変数として保持するなどして、スコープを伸ばしてください。
    ///
    /// \tparam TaskTy_ : 登録するタスク型
    /// \param[in] Task : 登録するタスク
    /// \param[in] Priority : タスクの優先度
    ///
    /// \return タスクの登録情報
    ///
    template <class TaskTy_>
    [[nodiscard]] TaskInfo registerTask(TaskTy_&& Task, uint32_t Priority=DefaultPriority) {
        return TaskInfo{insert(Priority, TaskType{std::forward<TaskTy_>(Task)}), Priority, this};
    }

    ///
    /// \brief  タスクを解除
    ///
    /// \param[in] Info : タスクの情報(登録時に生成される)
    ///
    void unregisterTask(TaskInfo& Info) {
        tasks_[Info.priority_][Info.id_] = TaskType{};
        indices_to_free_[Info.priority_].emplace(Info.id_);

        Info.manager_ = nullptr;
    }

    ///
    /// \brief  保持している全タスクを実行
    ///
    ///         実行後もタスクは保持されます。
    ///         解除する必要があれば、unregisterTask(…)を呼び出して下さい。
    ///
    /// \tparam ArgTypes : 実行するタスクに渡す引数型リスト
    /// \param[in] Args  : 実行するタスクに渡す引数リスト
    ///
    /// \note 引数を完全転送していない理由は、複数の呼び出しに渡す必要があるから。(moveによる不具合を防ぐ)
    ///
    template <class ...ArgTypes>
    void run(ArgTypes ...Args) {
        for(auto& container : tasks_)
          for(auto& task : container.second)
            if(task) task(Args...);
    }

private :
    ///
    /// \brief  挿入
    ///
    ///         戻り値は挿入位置
    ///         TaskInfoのIDとして使用する
    ///
    size_t insert(uint32_t Priority, TaskType&& Task) {
        auto& container = tasks_[Priority];

      // 空き領域に挿入
        if(auto free_stack=indices_to_free_.find(Priority); free_stack!=indices_to_free_.end() &&
           free_stack->second.size()) {
            size_t idx_to_free = free_stack->second.top();
            container[idx_to_free] = std::move(Task);
            free_stack->second.pop();
            return idx_to_free;
        }

      // 末尾に挿入
        container.emplace_back(std::move(Task));
        return container.size()-1;
    }
    
    std::map<uint32_t, EventVector<TaskType>> tasks_;        // tasks_[Priority][Task]
    std::map<uint32_t, std::stack<size_t>> indices_to_free_; // indices_to_free_[Priority]
};

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_
// EOF
