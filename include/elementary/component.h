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
    
    mat4x4 GetModelMatrix();
    vec4 GetPosition();
};

class Renderer : public Component {
public:
    Renderer(Element *base);
    ~Renderer();
};

class Camera : public Component {
public:
    static mat4x4 GetViewMatrix();
    static mat4x4 GetProjectionMatrix();
    static vec4 GetCameraPosition();

    Camera(Element *base);
    ~Camera();
};

class Skybox : public Component {
public:
    Skybox(Element *base);
    ~Skybox();
};