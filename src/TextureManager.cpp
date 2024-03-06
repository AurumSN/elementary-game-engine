#include "data/textures.h"

TextureManager::TextureManager() : ResourceManager() {}
TextureManager::~TextureManager() {}

std::shared_ptr<Texture> TextureManager::CreateTextureFromFile(const wchar_t *file_path) {
    return std::static_pointer_cast<Texture>(CreateResourceFromFile(file_path));
}

Resource *TextureManager::CreateResourceFromFileConcrete(const wchar_t *file_path) {
    return new Texture(file_path);
}