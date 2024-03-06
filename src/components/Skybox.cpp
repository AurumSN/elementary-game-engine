#include "elementary/component.h"

Skybox::Skybox(Element *base) : Component(base) {}
Skybox::~Skybox() {}

void Skybox::Update() {
    _transform->position = Camera::GetCameraPosition();
}