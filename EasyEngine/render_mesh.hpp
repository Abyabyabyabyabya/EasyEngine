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
    /// \brief  頂点インデックスバッファをセット
    ///
    /// \param[in] Buffer : セットするインデックスバッファ
    /// \param[in] Offset : 使用する要素までのオフセット
    ///
    void setIndex(const IndexBuffer& Buffer, const UINT Offset) noexcept { setIndex(Index{Buffer, Offset}); }
    void setIndex(const Index& Index) noexcept { index_ = Index; }

    ///
    /// \brief  頂点バッファをセット
    ///
    /// \param[in] Slot   : セットするスロット番号
    /// \param[in] Buffer : セットする頂点バッファ
    /// \param[in] Offset : 使用する要素までのオフセット
    ///
    void setVertex(const UINT Slot, const VertexBuffer& Buffer, const UINT Offset) {
        setVertex(Slot, Vertex{Buffer, Offset});
    }
    void setVertex(const UINT Slot, const Vertex& Vertex) {
        vertices_[Slot] = Vertex;
    }
    ///
    /// \brief  スロット番号が連続した頂点バッファリストをセット
    ///
    ///         Verticesの先頭要素がスロット番号StartSlotにセットされます。
    ///         残りのデータは、順に1ずつ加算されたスロット番号にセットされます。
    ///
    /// \param[in] StartSlot : スロット開始番号
    /// \param[in] Vertices  : セットする頂点バッファリスト
    ///
    void setVertices(UINT StartSlot, const std::vector<Vertex>& Vertices) {
        for(auto& vertex : Vertices)
            setVertex(StartSlot++, vertex);
    }


    ///< 頂点インデックスを取得
    Index index() const noexcept { return index_; }
    ///< スロット番号にマップされた頂点データを取得
    const std::map<UINT, Vertex>& vertices() const noexcept { return vertices_; }
private :
    Index index_;
    std::map<UINT, Vertex> vertices_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_RENDER_MESH_HEADER_
// EOF
