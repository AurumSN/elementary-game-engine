#pragma once

#include <d3d11.h>
#include <memory>
#include "data/resources.h"
#include "graphics/directx11.h"
#include "graphics/components/buffers.h"

class Mesh : public Resource {
public:
    Mesh(const wchar_t *full_path);
    ~Mesh();

    std::shared_ptr<VertexBuffer> &GetVertexBuffer();
    std::shared_ptr<IndexBuffer> &GetIndexBuffer();
private:
    std::shared_ptr<VertexBuffer> vertex_buffer;
    std::shared_ptr<IndexBuffer> index_buffer;

    friend class RenderSystem;
};

class MeshManager : public ResourceManager {
public:
    MeshManager();
    ~MeshManager();

    std::shared_ptr<Mesh> CreateMeshFromFile(const wchar_t *file_path);
protected:
    virtual Resource *CreateResourceFromFileConcrete(const wchar_t *file_path);
};

