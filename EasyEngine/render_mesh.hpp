///
/// \file   render_mesh.hpp
/// \brief  �`��p���b�V����`�w�b�_
///
/// \authro ��
///
/// \par    ����
///         - 2020/9/1
///             - �w�b�_�ǉ�
///             - RenderMesh ��`
///
#ifndef INCLUDED_EGEG_GLIB_RENDER_MESH_HEADER_
#define INCLUDED_EGEG_GLIB_RENDER_MESH_HEADER_

#include <vector>
#include <map>
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

namespace easy_engine {
namespace g_lib {

class RenderMesh {
public :
    struct Index {
        IndexBuffer buffer;
        UINT offset;
    };
    struct Vertex {
        VertexBuffer buffer;
        UINT offset;
    };

    ///
    /// \brief  ���_�C���f�b�N�X�o�b�t�@���Z�b�g
    ///
    /// \param[in] Buffer : �Z�b�g����C���f�b�N�X�o�b�t�@
    /// \param[in] Offset : �g�p����v�f�܂ł̃I�t�Z�b�g
    ///
    void setIndex(const IndexBuffer& Buffer, const UINT Offset) noexcept { setIndex(Index{Buffer, Offset}); }
    void setIndex(const Index& Index) noexcept { index_ = Index; }

    ///
    /// \brief  ���_�o�b�t�@���Z�b�g
    ///
    /// \param[in] Slot   : �Z�b�g����X���b�g�ԍ�
    /// \param[in] Buffer : �Z�b�g���钸�_�o�b�t�@
    /// \param[in] Offset : �g�p����v�f�܂ł̃I�t�Z�b�g
    ///
    void setVertex(const UINT Slot, const VertexBuffer& Buffer, const UINT Offset) {
        setVertex(Slot, Vertex{Buffer, Offset});
    }
    void setVertex(const UINT Slot, const Vertex& Vertex) {
        vertices_[Slot] = Vertex;
    }
    ///
    /// \brief  �X���b�g�ԍ����A���������_�o�b�t�@���X�g���Z�b�g
    ///
    ///         Vertices�̐擪�v�f���X���b�g�ԍ�StartSlot�ɃZ�b�g����܂��B
    ///         �c��̃f�[�^�́A����1�����Z���ꂽ�X���b�g�ԍ��ɃZ�b�g����܂��B
    ///
    /// \param[in] StartSlot : �X���b�g�J�n�ԍ�
    /// \param[in] Vertices  : �Z�b�g���钸�_�o�b�t�@���X�g
    ///
    void setVertices(UINT StartSlot, const std::vector<Vertex>& Vertices) {
        for(auto& vertex : Vertices)
            setVertex(StartSlot++, vertex);
    }


    ///< ���_�C���f�b�N�X���擾
    Index index() const noexcept { return index_; }
    ///< �X���b�g�ԍ��Ƀ}�b�v���ꂽ���_�f�[�^���擾
    const std::map<UINT, Vertex>& vertices() const noexcept { return vertices_; }
private :
    Index index_;
    std::map<UINT, Vertex> vertices_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_RENDER_MESH_HEADER_
// EOF
