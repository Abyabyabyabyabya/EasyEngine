///
/// \file   pixel_shader.hpp
/// \brief  �s�N�Z���V�F�[�_�[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/28
///             - �w�b�_�ǉ�
///             - PixelShader ��`
///
#ifndef INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_
#define INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_

#include "shader.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  PixelShader
/// \brief  �s�N�Z���V�F�[�_�[
///
/// \par    �ǂݍ��݂�x�����������ꍇ
///         - �f�t�H���g�R���X�g���N�^�ō\�z�����V�F�[�_�[�ɑ��
///           PixelShader ps{};
///             �c
///           ps = PixelShader{"hogehoge.xxx", �c};
///
/// \attention  ���̃N���X�P�̂ł��g�p�ł��܂����A�V�F�[�_�[���Ƃɂ��̃N���X�����Ƃ����ڍ׃N���X���`��������\n
///             �ǐ����オ��܂����A�������オ��Ǝv���̂ł����߂��܂��B\n
///             �R�s�[(or���[�u)���s�����Ƃ��A�R�s�[�����̂̓V�F�[�_�[�I�u�W�F�N�g�݂̂ł��B\n
///             set�����ɂ���Đݒ肳�ꂽ�V�F�[�_�[�ւ̓��͂̓R�s�[����܂���B
///
class PixelShader : public Shader {
public :
    PixelShader() = default;

    ///
    /// \brief  �ǂݍ��݂𔺂��R���X�g���N�^
    ///
    /// \param[in] ShaderFilePath : �ǂݍ��ރV�F�[�_�[�t�@�C���̃p�X
    ///
    PixelShader(const char* ShaderFilePath);

    ///
    /// \brief  �L���ȃs�N�Z���V�F�[�_�[������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return shader_; }
    operator bool() const noexcept { return isValid(); }


    ///< �V�F�[�_�[�I�u�W�F�N�g���擾
    ID3D11PixelShader* shader() const noexcept { return shader_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_PIXEL_SHADER_HEADER_
// EOF
