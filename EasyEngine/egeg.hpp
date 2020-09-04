///
/// \file   egeg.hpp
/// \brief  EasyEngine�̋@�\��S�Ċ܂ރw�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/7/23
///             - �w�b�_�[�ǉ�
///             - ���O��Ԃ��`
///         - 2020/9/2
///             - ���O��ԕʖ��錾
///             - EasyEngine�C���N���[�h�A�ʖ���`
///         - 2020/9/3
///             - �����p���O��Ԃ�錾
///
#ifndef INCLUDED_EGEG_HEADER_
#define INCLUDED_EGEG_HEADER_

/******************************************************************************

    namespace

******************************************************************************/
namespace easy_engine { // EasyEngine�p���O���
    namespace a_lib{}
    namespace g_lib{}
    namespace i_lib{}
    namespace m_lib{}
    namespace p_lib{}
    namespace t_lib{}
} // namespace easy_engine

namespace egeg          = easy_engine;          // EasyEngine�p���O���
namespace egeg_audio    = easy_engine::a_lib;   // �I�[�f�B�I�p���O���
namespace egeg_graphics = easy_engine::g_lib;   // �`��p���O���
namespace egeg_input    = easy_engine::i_lib;   // ���͗p���O���
namespace egeg_math     = easy_engine::m_lib;   // ���w�p���O���
namespace egeg_physics  = easy_engine::p_lib;   // �����p���O���
namespace egeg_template = easy_engine::t_lib;   // �e���v���[�g�p���O���

/******************************************************************************

    include

******************************************************************************/
#include "easy_engine.hpp"

/******************************************************************************

    alias

******************************************************************************/
namespace easy_engine { using EGEG = EasyEngine; }

#endif // !INCLUDED_EGEG_HEADER_
// EOF
