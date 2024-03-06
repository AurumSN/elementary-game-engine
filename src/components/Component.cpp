#include "elementary/component.h"

void Component::Load(std::wstring arguments, ElementData &data,  Element *base) {}

void Component::Init() {
    _transform = _base->GetTransform();
}
void Component::Update() {}

std::shared_ptr<Transform> Component::GetTransform() {
    return _transform;
}

Component::Component(Element *base) : _base(base), _transform(nullptr) {}
Component::~Component() {}