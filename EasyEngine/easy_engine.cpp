// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "easy_engine.hpp"
#include <cassert>

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace egeg_ns = easy_engine;
std::unique_ptr<egeg_ns::EasyEngine::Impl> egeg_ns::EasyEngine::impl_{};

/******************************************************************************

    EasyEngine::Impl

******************************************************************************/
struct egeg_ns::EasyEngine::Impl  {
    // 宣言順に依存関係あり。
    //  宣言とは逆順に破棄が行われる
    Clock clock_;
    std::unique_ptr<UpdateManager<EasyEngine>> umanager_;
    std::unique_ptr<i_lib::InputManager> imanager_;
    std::unique_ptr<g_lib::GraphicsManager> gmanager_;
};

/******************************************************************************

    EasyEngine::

/******************************************************************************/
void egeg_ns::EasyEngine::run() {
    auto init_res = initialize();
    if(!init_res) {
        // ログ出力 : エンジンの初期化に失敗しました。
        //            詳細 : init_res.what()
        return;
    }

    // ゲームループ
    try {
        // LOOP
    }
    catch(const std::exception& e) {
        // ログ出力 : 補足されない例外により終了しました。
        //            詳細 : e.what()
    }
    catch(...) {
        // ログ出力 : 補足されない例外により終了しました。
        //            詳細 : unknown error
    }

    finalize();

    // ログ出力 : 正常終了

    return;
}

// エンジン初期化
// サブシステムの初期化順には依存関係がある
egeg_ns::t_lib::DetailedResult<bool, const char*> egeg_ns::EasyEngine::initialize() {
    using namespace t_lib;
    using namespace i_lib;

    if(impl_) return Success{};

    impl_ = std::make_unique<Impl>();

  // サブシステムスタートアップ
    impl_->clock_ = Clock{};
    impl_->umanager_ = UpdateManager<EasyEngine>::create();
    if(!impl_->umanager_) return {Failure{}, "EasyEngine::initialize : 更新マネージャーの生成に失敗しました。"};
    impl_->imanager_ = i_lib::InputManager::create();
    if(!impl_->imanager_) return {Failure{}, "EasyEngine::initialize : 入力マネージャーの生成に失敗しました。"};
    impl_->gmanager_ = g_lib::GraphicsManager::create();
    if(!impl_->gmanager_) return {Failure{}, "EasyEngine::initialize : 描画マネージャーの生成に失敗しました。"};

    return Success{};
}

void egeg_ns::EasyEngine::finalize() noexcept {
    impl_.reset();
}

const egeg_ns::Clock& egeg_ns::EasyEngine::clock() noexcept {
    assert(impl_ && "エンジンの初期化が正常に終了していません。");
    return impl_->clock_;
}

egeg_ns::UpdateManager<egeg_ns::EasyEngine>& egeg_ns::EasyEngine::updator() noexcept {
    assert(impl_&&impl_->umanager_ && "エンジンの初期化が正常に終了していません。");
    return *impl_->umanager_;
}

egeg_ns::i_lib::InputManager& egeg_ns::EasyEngine::input() noexcept {
    assert(impl_&&impl_->imanager_ && "エンジンの初期化が正常に終了していません。");
    return *impl_->imanager_;
}

egeg_ns::g_lib::GraphicsManager& egeg_ns::EasyEngine::renderer() noexcept {
    assert(impl_&&impl_->gmanager_ && "エンジンの初期化が正常に終了していません。");
    return *impl_->gmanager_;
}
// EOF
