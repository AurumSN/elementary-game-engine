#include "data/textures.h"

TextureManager::TextureManager() : ResourceManager() {}
TextureManager::~TextureManager() {}

std::shared_ptr<Texture> TextureManager::CreateTextureFromFile(const wchar_t *file_path)
{
    return std::static_pointer_cast<Texture>(std::shared_ptr<Resource>(CreateResourceFromFileConcrete(file_path)));
}

Resource *TextureManager::CreateResourceFromFileConcrete(const wchar_t *file_path)
{
    Texture *tex = new Texture(file_path);


    return tex;
}
