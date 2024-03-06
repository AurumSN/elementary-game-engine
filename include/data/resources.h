#pragma once

#include <unordered_map>
#include <string>
#include <memory>

class Resource {
public:
    Resource(const wchar_t *full_path);
    virtual ~Resource();
protected:
    std::wstring full_path;
};

class ResourceManager {
public:
    ResourceManager();
    virtual ~ResourceManager();

    std::shared_ptr<Resource> CreateResourceFromFile(const wchar_t *file_path);
private:
    std::unordered_map<std::wstring, std::shared_ptr<Resource>> resource_map;
protected:
    virtual Resource *CreateResourceFromFileConcrete(const wchar_t *file_path) = 0;
};