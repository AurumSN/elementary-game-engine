#pragma once

#include <string>
#include <d3d11.h>
#include <memory>
#include "data/resources.h"
#include "graphics/directx11.h"

class Texture : public Resource {
public:
    Texture(const wchar_t *full_path);
    ~Texture();
private:
    ID3D11Resource *texture = nullptr;
    ID3D11ShaderResourceView *shader_resource_view = nullptr;

    friend class RenderSystem;
};

class TextureManager : public ResourceManager {
public:
    TextureManager();
    ~TextureManager();

    std::shared_ptr<Texture> CreateTextureFromFile(const wchar_t *file_path);
protected:
    virtual Resource *CreateResourceFromFileConcrete(const wchar_t *file_path);
};