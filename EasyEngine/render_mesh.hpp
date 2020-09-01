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

#include <map>
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

namespace easy_engine {
namespace g_lib {

class RenderMesh {
public :
    struct IndexData {
        ID3D11Buffer* buffer;
        DXGI_FORMAT format;
        UINT offset;
    };
    struct VertexData {
        ID3D11Buffer* buffer;
        UINT stride;
        UINT offset;
    };

    void setIndices(const IndexBuffer& Buffer);
    template <class ...Rest>
    void setVertices(UINT StartSlot, const VertexBuffer& Buffer, Rest ...Buffers);

    IndexData indices() const noexcept { return indices_; }
    const std::map<UINT, VertexData>& vertices() const noexcept { return vertices_; }
private :
    IndexData indices_;
    std::map<UINT, VertexData> vertices_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_RENDER_MESH_HEADER_
// EOF
