#include "graphics/directx11.h"

#include <stdexcept>
#include "data/elements.h"

GraphicsEngine *GraphicsEngine::engine = nullptr;

GraphicsEngine *GraphicsEngine::Get() {
    return engine;
}

void GraphicsEngine::Create() {
    if (engine) 
        throw std::runtime_error("Graphics Engine already exists");

    engine = new GraphicsEngine();
}

void GraphicsEngine::Release() {
    if (engine) 
        delete engine;
}

GraphicsEngine::GraphicsEngine() {
    render_system = new RenderSystem();
    // tex_manager = new TextureManager();
    // mesh_manager = new MeshManager();

    void *shader_byte_code = nullptr;
    size_t shader_byte_size = 0;

    render_system->CompileShader(L"assets/shaders/VertexMeshLayoutShader.hlsl", "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
    memcpy(vertex_mesh_layout_shader_byte_code, shader_byte_code, shader_byte_size);
    vertex_mesh_layout_shader_byte_size = shader_byte_size;
    render_system->ReleaseCompiledShader();
}

GraphicsEngine::~GraphicsEngine() {
    engine = nullptr;
    // delete mesh_manager;
    // delete tex_manager;
    delete render_system;
}

RenderSystem *GraphicsEngine::GetRenderSystem() {
    return render_system;
}

// TextureManager *GraphicsEngine::GetTexManager() {
//     return tex_manager;
// }

// MeshManager *GraphicsEngine::GetMeshManager() {
//     return mesh_manager;
// }

void GraphicsEngine::GetVertexMeshLayoutShader(void **shader_byte_code, size_t *shader_byte_size) {
    *shader_byte_code = vertex_mesh_layout_shader_byte_code;
    *shader_byte_size = vertex_mesh_layout_shader_byte_size;
}