#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "data/textures.h"
#include "data/meshes.h"
#include "graphics/components/shaders.h"
#include "graphics/components/buffers.h"
#include "elementary/math.h"

#define ELEMENTS_FLAGS_NONE 0x0
#define ELEMENTS_FLAGS_SKYBOX 0x1
#define ELEMENTS_FLAGS_NOT_SKYBOX 0x2
#define ELEMENTS_FLAGS_CULL_FRONT 0x4
#define ELEMENTS_FLAGS_CULL_BACK 0x8
#define ELEMENTS_FLAGS_ALL 0xf

class AppWindow;
class ElementManager;

class Element {
public:
    Element(
        UINT flags,
        std::shared_ptr<Mesh> mesh, 
        std::shared_ptr<PixelShader> pixel_shader,
        std::shared_ptr<VertexShader> vertex_shader,
        std::shared_ptr<Texture> *textures,
        UINT texture_count
    );
    ~Element();

    Element(const Element&) = delete;

    void Draw();
    void UpdateConstantBuffer(const constant *cc);
private:
    UINT flags;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<PixelShader> pixel_shader;
    std::shared_ptr<VertexShader> vertex_shader;
    std::shared_ptr<ConstantBuffer> constant_buffer;
    std::shared_ptr<Texture> *textures;
    UINT texture_count;

    friend AppWindow;
    friend ElementManager;
};

class ElementManager {
public:
    static void Create();
    static void Release();

    ElementManager(const wchar_t *file_path);
    ~ElementManager();

    void Draw(UINT flags);
    void UpdateConstantBuffer(const constant *cc, UINT flags);
private:
    static TextureManager *tex_manager;
    static MeshManager *mesh_manager;

    std::unordered_map<std::wstring, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::wstring, std::shared_ptr<Mesh>> meshes;
    std::unordered_map<std::wstring, std::wstring> shaders;
    // std::unordered_map<std::wstring, std::shared_ptr<Material>> materials;
    std::unordered_map<std::wstring, std::shared_ptr<Element>> elements;
};