///
/// \file   vertex_shader.hpp
/// \brief  ���_�V�F�[�_�[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/28
///             - �w�b�_�ǉ�
///             - VertexShader ��`
///
#ifndef INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_
#define INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_

#include <vector>
#include "shader_common.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  VertexShader
/// \brief  ���_�V�F�[�_�[
///
/// \par    �ǂݍ��݂�x�����������ꍇ
///         - �f�t�H���g�R���X�g���N�^�ō\�z�����V�F�[�_�[�ɑ��
///           VertexShader vs{};
///             �c
///           vs = VertexShader{"hogehoge.xxx", �c};
///
/// \attention  ���̃N���X�P�̂ł��g�p�ł��܂����A�V�F�[�_�[���Ƃɂ��̃N���X�����Ƃ����ڍ׃N���X���`��������\n
///             �ǐ����オ��܂����A�������オ��Ǝv���̂ł����߂��܂��B\n
///
class VertexShader {
public :
    virtual ~VertexShader() = default;
    VertexShader() = default;

    ///
    /// \brief  �ǂݍ��݂𔺂��R���X�g���N�^
    ///
    /// \param[in] ShaderFilePath : �ǂݍ��ރV�F�[�_�[�t�@�C���̃p�X
    /// \param[in] InputLayout    : �ǂݍ��ޒ��_�V�F�[�_�[�̓��̓��C�A�E�g
    ///
    VertexShader(const char* ShaderFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout);

    ///
    /// \brief  �L���Ȓ��_�V�F�[�_�[������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return shader_ && layout_; }
    operator bool() const noexcept { return isValid(); }

    
    ///< �V�F�[�_�[�I�u�W�F�N�g���擾
    ID3D11VertexShader* shader() const noexcept { return shader_.Get(); }
    ///< ���̓��C�A�E�g�I�u�W�F�N�g���擾
    ID3D11InputLayout* layout() const noexcept { return layout_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_VERTEX_SHADER_HEADER_
// EOF
