//
/// \file   texture.hpp
/// \brief  �e�N�X�`����`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/24
///             - �w�b�_�ǉ�
///             - Texture ��`
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_HEADER_

#include "texture_resource.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    Texture

******************************************************************************/
///
/// \brief  �e�N�X�`��(�V�F�[�_�[���\�[�X)
///
///         �R���X�g���N�^�Ŏw�肵���摜�t�@�C�����e�N�X�`���Ƃ��ĕێ����܂��B
///         �t�@�C�������w�肵�ăR���X�g���N�^���Ăяo�����ꍇ�A�ǂݍ��ݏ������������܂��B
///
/// \par    �ǂݍ��݂�x�����������ꍇ
///         - �f�t�H���g�R���X�g���N�^�ō\�z�����e�N�X�`���ɑ��
///           Texture texture{};
///             �c
///           texture = Texture{"hogehoge.png"};
///
class Texture : public TextureResource {
public :
    Texture() = default;
    virtual ~Texture() = default;
    
    ///
    /// \brief  �ǂݍ��݂𔺂��\�z
    ///
    /// \param[in] FilePath : �ǂݍ��މ摜�̃t�@�C���p�X
    ///
    Texture(const char* FilePath);

    ///
    /// \brief  �L���ȃe�N�X�`�����ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return TextureResource::isValid() && texture_; }
    operator bool() const noexcept { return isValid(); }

    /// �e�N�X�`�����擾
    ID3D11ShaderResourceView* texture() const noexcept { return texture_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF
