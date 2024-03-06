#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "data/textures.h"
#include "data/meshes.h"
#include "graphics/components/shaders.h"
#include "graphics/components/buffers.h"
#include "elementary/math.h"

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

    static void Load(const wchar_t *file_path);
    static void UpdateElements();

    Element(const wchar_t *full_path);
    ~Element();

    void Init();
    void Update();

    std::shared_ptr<Transform> GetTransform();
    std::shared_ptr<Renderer> GetRenderer();
    std::shared_ptr<Component> *GetComponents();
    UINT GetComponentCount();
    std::shared_ptr<Component> GetComponent(UINT id);
private:
    static ElementData global;

    static std::shared_ptr<Element> *element_list;
    static UINT element_count;

    std::shared_ptr<Transform> transform = nullptr;
    std::shared_ptr<Renderer> renderer = nullptr;
    std::shared_ptr<Component> *components = nullptr;
    UINT component_count = 0;
};

class ElementManager : public ResourceManager {
public:
    ElementManager();
    ~ElementManager();

    std::shared_ptr<Element> CreateElementFromFile(const wchar_t *file_path);
protected:
    virtual Resource *CreateResourceFromFileConcrete(const wchar_t *file_path);
};