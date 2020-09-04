///
/// \file   geometry_shader.hpp
/// \brief  �W�I���g���V�F�[�_�[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/2
///             - �w�b�_�ǉ�
///             - GeometryShader ��`
///
#ifndef INCLUDED_EGEG_GLIB_GEOMETRY_SHADER_HEADER_
#define INCLUDED_EGEG_GLIB_GEOMETRY_SHADER_HEADER_

#include "shader_common.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    GeometryShader

******************************************************************************/
///
/// \brief  �W�I���g���V�F�[�_�[
///
/// \par    �ǂݍ��݂�x�����������ꍇ
///         - �f�t�H���g�R���X�g���N�^�ō\�z�����V�F�[�_�[�ɑ��
///           GeometryShader gs{};
///             �c
///           gs = GeometryShader{"hogehoge.xxx", �c};
///
/// \attention  ���̃N���X�P�̂ł��g�p�ł��܂����A�V�F�[�_�[���Ƃɂ��̃N���X�����Ƃ����ڍ׃N���X���`��������\n
///             �ǐ����オ��܂����A�������オ��Ǝv���̂ł����߂��܂��B\n
///
class GeometryShader {
public :
    GeometryShader() = default;

    ///
    /// \brief  �ǂݍ��݂𔺂��R���X�g���N�^
    ///
    /// \param[in] ShaderFilePath : �ǂݍ��ރV�F�[�_�[�t�@�C���̃p�X
    ///
    GeometryShader(const char* ShaderFilePath);

    ///
    /// \brief  �L���ȃW�I���g���V�F�[�_�[���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return shader_; }
    operator bool() const noexcept { return isValid(); }


    /// �V�F�[�_�[�I�u�W�F�N�g���擾
    ID3D11GeometryShader* shader() const noexcept { return shader_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_GEOMETRY_SHADER_HEADER_
// EOF
