///
/// \file   render_mesh.hpp
/// \brief  描画用メッシュ定義ヘッダ
///
/// \authro 板場
///
/// \par    履歴
///         - 2020/9/1
///             - ヘッダ追加
///             - RenderMesh 定義
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
