///
/// \file   shader_slot.hpp
/// \brief  �V�F�[�_�[���N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/28
///             - �w�b�_�ǉ�
///             - Shader ��`
///         - 2020/8/31
///             - �w�b�_���ύX(shader.hpp -> shader_slot.hpp)
///             - �N���X���ύX(Shader -> ShaderSlot)
///
#ifndef INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
#define INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_

#include <vector>
#include <map>
#include <d3d11.h>
#include <wrl.h>
#include "constant_buffer.hpp"
#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    ShaderSlot

******************************************************************************/
///
/// \brief  �V�F�[�_�[�X���b�g
///
///         �V�F�[�_�[�ւ̓��͂��i�[���܂��B
///
class ShaderSlot {
public :
    virtual ~ShaderSlot() = default;

    ///
    /// \brief  �萔���Z�b�g
    ///
    /// \param[in] Slot     : �Z�b�g����X���b�g�ԍ�
    /// \param[in] Constant : �Z�b�g����萔
    ///
    void setConstant(const UINT Slot, const ConstantBufferData& Constant) {
        constants_[Slot] = Constant.buffer();
    }
    ///
    /// \brief  �����́A�X���b�g�ԍ����A�������萔���Z�b�g
    ///
    ///         ���X�g�̐擪�v�f���A�X���b�g�ԍ�StartSlot�ɃZ�b�g����܂��B
    ///         �c��̗v�f�͏���1�����Z���ꂽ�X���b�g�ԍ��ɃZ�b�g����܂��B
    ///
    /// \param[in] StartSlot : �X���b�g�J�n�ԍ�
    /// \param[in] Constants : �Z�b�g����萔���X�g
    ///
    void setConstants(UINT StartSlot, const std::vector<ConstantBufferData>& Constants) {
        for(auto& constant : Constants)
            setConstant(StartSlot++, constant);
    }
    
    ///
    /// \brief  �e�N�X�`�����Z�b�g
    ///
    /// \param[in] Slot    : �Z�b�g����X���b�g�ԍ�
    /// \param[in] Texture : �Z�b�g����e�N�X�`��
    ///
    void setTexture(const UINT Slot, const Texture& Texture) {
        textures_[Slot] = Texture.texture();
    }
    ///
    /// \brief  �����́A�X���b�g�ԍ����A�������萔���Z�b�g
    ///
    ///         �ڍׂ�setConstants�Ɠ��l�ł��B
    ///
    /// \param[in] StartSlot : �X���b�g�J�n�ԍ�
    /// \param[in] Textures  : �Z�b�g����e�N�X�`�����X�g
    ///
    void setTextures(UINT StartSlot, const std::vector<Texture>& Textures) {
        for(auto& texture : Textures)
            setTexture(StartSlot++, texture);
    }

    // TODO : sampler


    /// �X���b�g�ԍ��Ƀ}�b�v���ꂽ�萔�o�b�t�@���擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>>& constants() const noexcept { return constants_; }
    /// �X���b�g�ԍ��Ƀ}�b�v���ꂽ�e�N�X�`�����擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>& textures() const noexcept { return textures_; }
    /// �X���b�g�ԍ��Ƀ}�b�v���ꂽ�T���v���[���擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>>& samplers() const noexcept { return samplers_; }
//protected :
    ShaderSlot() = default;
private :
    void setConstant(const UINT) const noexcept {}
    void setTexture(const UINT) const noexcept {}
    void setSampler(const UINT) const noexcept {}

    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> constants_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
// EOF
