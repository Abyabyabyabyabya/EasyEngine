// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "easy_engine.hpp"
#include <cassert>
#include <string>
#include "egeg_state.hpp"

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace egeg_ns = easy_engine;
std::unique_ptr<egeg_ns::EasyEngine::Impl> egeg_ns::EasyEngine::impl_{};

/******************************************************************************

    EasyEngine::Impl

******************************************************************************/
struct egeg_ns::EasyEngine::Impl  {
    void WindowEventProcess(HWND, UINT, WPARAM, LPARAM);

    // 宣言順に依存関係あり。
    //  宣言とは逆順に破棄が行われる
    std::unique_ptr<WindowManager> wmanager_;
    Clock clock_;
    std::unique_ptr<UpdateManager<EasyEngine>> umanager_;
    std::unique_ptr<i_lib::InputManager> imanager_;
    std::unique_ptr<g_lib::GraphicManager> gmanager_;
};

/******************************************************************************

    EasyEngine::

/******************************************************************************/
void egeg_ns::EasyEngine::run() {
    auto init_res = startUp();
    if(!init_res) {
        // ログ出力 : エンジンの初期化に失敗しました。
        //            詳細 : init_res.what()
        return;
    }

    // ゲームループ
    try {
        MSG msg{};
        Clock clock{};
        while( msg.message != WM_QUIT ) {
            // メッセージ処理
            if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) ) {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
            // ゲーム処理
            else {
                clock.update();
                auto elapsed = clock.elapsed();
                if(elapsed.microseconds() >= kTPF<std::micro>) {
                    clock = Clock{};
                    impl_->umanager_->run(elapsed);
                    SetWindowText(window().handle(), std::to_wstring(elapsed.nanoseconds()).c_str());
                }
            }
        }
    }
    catch(const std::exception& e) {
        shutDown();
        // ログ出力 : 補足されない例外により終了しました。
        //            詳細 : e.what()
    }
    catch(...) {
        shutDown();
        // ログ出力 : 補足されない例外により終了しました。
        //            詳細 : unknown error
    }

    shutDown();

    // ログ出力 : 正常終了

    return;
}

// エンジン初期化
// サブシステムの初期化順には依存関係がある
// impl_のメンバに生成したマネージャーを直代入しているのもそういった理由
egeg_ns::t_lib::DetailedResult<bool, const char*> egeg_ns::EasyEngine::startUp() {
    using namespace t_lib;
    using namespace i_lib;

    if(impl_) return Success{};

    auto failure = [&](const char* Message)->DetailedResult<bool, const char*> {
        impl_.reset();
        return {Failure{}, Message};
    };

  // サブシステムスタートアップ
    try {
        impl_ = std::make_unique<Impl>();
        impl_->wmanager_ = WindowManager::create();
        if(!impl_->wmanager_) return failure("EasyEngine::startUp : ウィンドウマネージャーの生成に失敗しました。");
        impl_->clock_ = Clock{};
        impl_->umanager_ = UpdateManager<EasyEngine>::create();
        if(!impl_->umanager_) return failure("EasyEngine::startUp : 更新マネージャーの生成に失敗しました。");
        impl_->imanager_ = i_lib::InputManager::create();
        if(!impl_->imanager_) return failure("EasyEngine::startUp : 入力マネージャーの生成に失敗しました。");
        impl_->gmanager_ = g_lib::GraphicManager::create();
        if(!impl_->gmanager_) return failure("EasyEngine::startUp : 描画マネージャーの生成に失敗しました。");
    } catch(const std::exception& e) {
        char err_msg[1024] = "EasyEngine::startUP : ";
        strcat_s(err_msg, e.what());
        return failure(err_msg);
    }

    window().addCallback(impl_.get(), &EasyEngine::Impl::WindowEventProcess);

    return Success{};
}

void egeg_ns::EasyEngine::shutDown() noexcept {
    impl_.reset();
}

egeg_ns::WindowManager& egeg_ns::EasyEngine::window() noexcept{
    assert(impl_&&impl_->wmanager_ && "エンジンの初期化が正常に終了していません。");
    return *impl_->wmanager_;
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

egeg_ns::g_lib::GraphicManager& egeg_ns::EasyEngine::graphics() noexcept {
    assert(impl_&&impl_->gmanager_ && "エンジンの初期化が正常に終了していません。");
    return *impl_->gmanager_;
}

/******************************************************************************

    EasyEngine::Impl::

******************************************************************************/
void egeg_ns::EasyEngine::Impl::WindowEventProcess(
  const HWND hWnd, const UINT Msg, const WPARAM wParam, const LPARAM lParam) {
    switch(Msg) {
    case WM_KEYDOWN :
        if(wParam==VK_ESCAPE)
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
    case WM_SYSKEYDOWN :
    case WM_KEYUP :
    case WM_SYSKEYUP :
        imanager_->keyEvent(Msg, wParam, lParam);
        break;
    }
}
// EOF
