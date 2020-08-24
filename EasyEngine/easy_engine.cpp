// �쐬�� : ��
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
    // �錾���Ɉˑ��֌W����B
    //  �錾�Ƃ͋t���ɔj�����s����
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
        // ���O�o�� : �G���W���̏������Ɏ��s���܂����B
        //            �ڍ� : init_res.what()
        return;
    }

    // �Q�[�����[�v
    try {
        // LOOP
    }
    catch(const std::exception& e) {
        // ���O�o�� : �⑫����Ȃ���O�ɂ��I�����܂����B
        //            �ڍ� : e.what()
    }
    catch(...) {
        // ���O�o�� : �⑫����Ȃ���O�ɂ��I�����܂����B
        //            �ڍ� : unknown error
    }

    finalize();

    // ���O�o�� : ����I��

    return;
}

// �G���W��������
// �T�u�V�X�e���̏��������ɂ͈ˑ��֌W������
egeg_ns::t_lib::DetailedResult<bool, const char*> egeg_ns::EasyEngine::initialize() {
    using namespace t_lib;
    using namespace i_lib;

    if(impl_) return Success{};

    impl_ = std::make_unique<Impl>();

  // �T�u�V�X�e���X�^�[�g�A�b�v
    impl_->clock_ = Clock{};
    impl_->umanager_ = UpdateManager<EasyEngine>::create();
    if(!impl_->umanager_) return {Failure{}, "EasyEngine::initialize : �X�V�}�l�[�W���[�̐����Ɏ��s���܂����B"};
    impl_->imanager_ = i_lib::InputManager::create();
    if(!impl_->imanager_) return {Failure{}, "EasyEngine::initialize : ���̓}�l�[�W���[�̐����Ɏ��s���܂����B"};
    impl_->gmanager_ = g_lib::GraphicsManager::create();
    if(!impl_->gmanager_) return {Failure{}, "EasyEngine::initialize : �`��}�l�[�W���[�̐����Ɏ��s���܂����B"};

    return Success{};
}

void egeg_ns::EasyEngine::finalize() noexcept {
    impl_.reset();
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

egeg_ns::g_lib::GraphicsManager& egeg_ns::EasyEngine::renderer() noexcept {
    assert(impl_&&impl_->gmanager_ && "�G���W���̏�����������ɏI�����Ă��܂���B");
    return *impl_->gmanager_;
}
// EOF
