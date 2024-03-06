#include "data/meshes.h"

MeshManager::MeshManager() : ResourceManager() {}
MeshManager::~MeshManager() {}

std::shared_ptr<Mesh> MeshManager::CreateMeshFromFile(const wchar_t *file_path) {
    return std::static_pointer_cast<Mesh>(CreateResourceFromFile(file_path));
}

Resource *MeshManager::CreateResourceFromFileConcrete(const wchar_t *file_path) {
    return new Mesh(file_path);
}