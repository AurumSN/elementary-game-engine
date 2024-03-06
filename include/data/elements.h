#pragma once

#include <windows.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "data/textures.h"
#include "data/meshes.h"
#include "graphics/components/shaders.h"
#include "graphics/components/buffers.h"

class Element;
class Component;
class Transform;
class Renderer;

struct ElementData {
    std::unordered_map<std::wstring, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::wstring, std::shared_ptr<Mesh>> meshes;
    std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> pixel_shaders;
    std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> vertex_shaders;
    std::unordered_map<std::wstring, std::shared_ptr<Element>> elements;
};

class Element : public Resource {
public:
    static std::unordered_map<std::wstring, std::shared_ptr<Component> (*)(Element *base)> generators;

    Element(const wchar_t *full_path);
    ~Element();

    std::shared_ptr<Transform> GetTransform();
    std::shared_ptr<Renderer> GetRenderer();
    std::shared_ptr<Component> *GetComponents();
    UINT GetComponentCount();
    std::shared_ptr<Component> GetComponent(UINT id);
};