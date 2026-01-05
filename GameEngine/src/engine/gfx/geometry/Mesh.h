#pragma once
#include "engine/gfx/geometry/Buffer.h"
#include "engine/gfx/material/Material.h"
#include <memory>

class Mesh {
public:
    Mesh(
        std::shared_ptr<VertexArray> vArr,
        std::shared_ptr<IndexBuffer> iBuffer,
        std::shared_ptr<Material> material
    )
        : m_VertexArray(std::move(vArr)),
        m_IndexBuffer(std::move(iBuffer)),
        m_Material(std::move(material))
    {
    }

    void bind() const;
    void unbind() const;

    VertexArray* getVertexArray() const { return m_VertexArray.get(); }
    IndexBuffer* getIndexBuffer() const { return m_IndexBuffer.get(); }
    std::shared_ptr<Material> getMaterial() const { return m_Material; }

private:
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Material> m_Material;
};
