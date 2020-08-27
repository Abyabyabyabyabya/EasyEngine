//
/// \file   texture.hpp
/// \brief  �e�N�X�`���n���h����`�w�b�_
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

#include <type_traits>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

///
/// \class  Texture
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
class Texture {
public :
    Texture() = default;
    
    ///
    /// \brief  �ǂݍ��݂𔺂��\�z
    ///
    /// \tparam StrTy : ������^
    /// \param[in] FilePath : �ǂݍ��މ摜�̃t�@�C���p�X
    ///
    template <class StrTy>
    Texture(StrTy&& FilePath) {
        load(std::forward<StrTy>(FilePath));
    }

    ///
    /// \brief  �L���ȃe�N�X�`�����ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept {
        return view_;
    }
    operator bool() const noexcept {
        return isValid();
    }

    ///< ���\�[�X���擾
    ID3D11Texture2D* resource() const noexcept { return resource_.Get(); }
    ///< �r���[���擾
    ID3D11ShaderResourceView* view() const noexcept { return view_.Get(); }

private :
    void load(const char*);
    Microsoft::WRL::ComPtr<ID3D11Texture2D> resource_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF