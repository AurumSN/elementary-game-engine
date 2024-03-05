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
#define ELEMENTS_FLAGS_DEFAULT 0xa
#define ELEMENTS_FLAGS_ALL 0xf

class Element : public Resource, public std::enable_shared_from_this<Element> {
public:
    static void Load(const wchar_t *file_path);
    static void Draw(UINT flags);
    static void UpdateConstantBuffer(const constant *cc, UINT flags);

    Element(const wchar_t *full_path);
    ~Element();

    void Draw();
    void UpdateConstantBuffer(const constant *cc);
private:
    static std::unordered_map<std::wstring, std::shared_ptr<Texture>> global_textures;
    static std::unordered_map<std::wstring, std::shared_ptr<Mesh>> global_meshes;
    static std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> global_pixel_shaders;
    static std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> global_vertex_shaders;
    static std::unordered_map<std::wstring, std::shared_ptr<Element>> global_elements;

    static std::shared_ptr<Element> *element_list;
    static UINT element_count;

    UINT flags = 0;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<PixelShader> pixel_shader;
    std::shared_ptr<VertexShader> vertex_shader;
    std::shared_ptr<ConstantBuffer> constant_buffer;
    std::shared_ptr<Texture> *textures;
    UINT texture_count = 0;
};

class ElementManager : public ResourceManager {
public:
    ElementManager();
    ~ElementManager();

    std::shared_ptr<Element> CreateElementFromFile(const wchar_t *file_path);
protected:
    virtual Resource *CreateResourceFromFileConcrete(const wchar_t *file_path);
};