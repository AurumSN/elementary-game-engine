#include "data/elements.h"

ElementManager::ElementManager() : ResourceManager() {}
ElementManager::~ElementManager() {}

std::shared_ptr<Element> ElementManager::CreateElementFromFile(const wchar_t *file_path) {
    return std::static_pointer_cast<Element>(CreateResourceFromFile(file_path));
}

Resource *ElementManager::CreateResourceFromFileConcrete(const wchar_t *file_path) {
    return new Element(file_path);
}
