#include "data/resources.h"

#include <filesystem>

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

std::shared_ptr<Resource> ResourceManager::CreateResourceFromFile(const wchar_t *file_path) {
    std::wstring full_path = std::filesystem::absolute(file_path);

    auto it = resource_map.find(full_path);

    if (it != resource_map.end())
        return it->second;

    Resource *raw_res = this->CreateResourceFromFileConcrete(full_path.c_str());

    if (raw_res) {
        std::shared_ptr<Resource> res(raw_res);
        resource_map[full_path] = res;
        return res;
    }
    
    return nullptr;
}