#pragma once

#include <memory>
#include <sstream>
#include "data/textures.h"
#include "data/meshes.h"
#include "graphics/components/shaders.h"
#include "graphics/components/buffers.h"
#include "elementary/math.h"
#include "data/elements.h"

class Transform;

class Component {
public:
    Component(Element *base);
    ~Component();

    virtual void Load(std::wstring arguments, ElementData &data, Element *base);
    virtual void Init();
    virtual void Update(); 

    std::shared_ptr<Transform> GetTransform();
protected:
    Element *_base = nullptr;
    std::shared_ptr<Transform> _transform = nullptr;
};

class Transform : public Component {
public:
    vec3 position = vec3::zero;
    vec3 rotation = vec3::zero;
    vec3 scale = vec3::zero;

    std::shared_ptr<Transform> parent = nullptr;

    Transform(Element *base);
    ~Transform();

    virtual void Load(std::wstring arguments, ElementData &data, Element *base) override;
    mat4x4 GetModelMatrix();
    vec4 GetPosition();
};

#define RENDERER_FLAGS_NONE 0x0
#define RENDERER_FLAGS_CULL_BACK 0x1
#define RENDERER_FLAGS_CULL_FRONT 0x2
#define RENDERER_FLAGS_DEFAULT 0x1
#define RENDERER_FLAGS_ALL 0x2

class Renderer : public Component {
public:
    Renderer(Element *base);
    ~Renderer();

    virtual void Load(std::wstring arguments, ElementData &data, Element *base) override;
    virtual void Update() override;

    void Render();
protected:
    UINT flags = 0;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<PixelShader> pixel_shader;
    std::shared_ptr<VertexShader> vertex_shader;
    std::shared_ptr<ConstantBuffer> constant_buffer;
    std::shared_ptr<Texture> *textures;
    UINT texture_count = 0;
};

class Camera : public Component {
public:
    static mat4x4 GetViewMatrix();
    static mat4x4 GetProjectionMatrix();
    static vec4 GetCameraPosition();

    Camera(Element *base);
    ~Camera();

    virtual void Update(); 
protected:
    static mat4x4 _viewMatrix;
    static mat4x4 _projectionMatrix;
    static vec4 _cameraPosition;
};

class Skybox : public Component {
public:
    Skybox(Element *base);
    ~Skybox();

    virtual void Update(); 
};