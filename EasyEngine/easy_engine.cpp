// �쐬�� : ��
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

    // �錾���Ɉˑ��֌W����B
    //  �錾�Ƃ͋t���ɔj�����s����
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
        // ���O�o�� : �G���W���̏������Ɏ��s���܂����B
        //            �ڍ� : init_res.what()
        return;
    }

    // �Q�[�����[�v
    try {
        MSG msg{};
        Clock clock{};
        while( msg.message != WM_QUIT ) {
            // ���b�Z�[�W����
            if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) ) {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
            // �Q�[������
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
        // ���O�o�� : �⑫����Ȃ���O�ɂ��I�����܂����B
        //            �ڍ� : e.what()
    }
    catch(...) {
        shutDown();
        // ���O�o�� : �⑫����Ȃ���O�ɂ��I�����܂����B
        //            �ڍ� : unknown error
    }

    shutDown();

    // ���O�o�� : ����I��

    return;
}

// �G���W��������
// �T�u�V�X�e���̏��������ɂ͈ˑ��֌W������
// impl_�̃����o�ɐ��������}�l�[�W���[�𒼑�����Ă���̂��������������R
egeg_ns::t_lib::DetailedResult<bool, const char*> egeg_ns::EasyEngine::startUp() {
    using namespace t_lib;
    using namespace i_lib;

    if(impl_) return Success{};

    auto failure = [&](const char* Message)->DetailedResult<bool, const char*> {
        impl_.reset();
        return {Failure{}, Message};
    };

  // �T�u�V�X�e���X�^�[�g�A�b�v
    try {
        impl_ = std::make_unique<Impl>();
        impl_->wmanager_ = WindowManager::create();
        if(!impl_->wmanager_) return failure("EasyEngine::startUp : �E�B���h�E�}�l�[�W���[�̐����Ɏ��s���܂����B");
        impl_->clock_ = Clock{};
        impl_->umanager_ = UpdateManager<EasyEngine>::create();
        if(!impl_->umanager_) return failure("EasyEngine::startUp : �X�V�}�l�[�W���[�̐����Ɏ��s���܂����B");
        impl_->imanager_ = i_lib::InputManager::create();
        if(!impl_->imanager_) return failure("EasyEngine::startUp : ���̓}�l�[�W���[�̐����Ɏ��s���܂����B");
        impl_->gmanager_ = g_lib::GraphicManager::create();
        if(!impl_->gmanager_) return failure("EasyEngine::startUp : �`��}�l�[�W���[�̐����Ɏ��s���܂����B");
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
    assert(impl_&&impl_->wmanager_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
    return *impl_->wmanager_;
}

const egeg_ns::Clock& egeg_ns::EasyEngine::clock() noexcept {
    assert(impl_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
    return impl_->clock_;
}

egeg_ns::UpdateManager<egeg_ns::EasyEngine>& egeg_ns::EasyEngine::updator() noexcept {
    assert(impl_&&impl_->umanager_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
    return *impl_->umanager_;
}

egeg_ns::i_lib::InputManager& egeg_ns::EasyEngine::input() noexcept {
    assert(impl_&&impl_->imanager_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
    return *impl_->imanager_;
}

egeg_ns::g_lib::GraphicManager& egeg_ns::EasyEngine::graphics() noexcept {
    assert(impl_&&impl_->gmanager_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
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
