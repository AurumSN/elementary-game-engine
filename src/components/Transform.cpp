#include "elementary/component.h"

#include <string>

void Transform::Load(std::wstring arguments, ElementData &data, Element *base) {
    int state = 0;
    std::wstring arg;
    float x, y, z;
    position = vec3(0, 0, 0);
    rotation = vec3(0, 0, 0);
    scale = vec3(1, 1, 1);
    std::wstringstream ss(arguments);

    while (ss) {
        switch (state) {
        case 1:
            ss >> position;
            state = -state;
            break;
        case 2:
            ss >> rotation;
            state = -state;
            break;
        case 3:
            ss >> scale;
            state = -state;
            break;
        default:
            ss >> arg;
            if (arg.compare(L"-v3") == 0)
                state = -state + 1;
        }
    }
}

mat4x4 Transform::GetModelMatrix() {
    if (parent)
        return parent->GetModelMatrix() * mat4x4::rotation(rotation.x, rotation.y, rotation.z) * mat4x4::scale(scale) * mat4x4::translation(position);
    
    return mat4x4::rotation(rotation.x, rotation.y, rotation.z) * mat4x4::scale(scale) * mat4x4::translation(position);
}

vec4 Transform::GetPosition() {
    if (parent)
        return parent->GetModelMatrix() * vec4::point(position);
    return position;
}

Transform::Transform( Element *base) : Component(base) {}
Transform::~Transform() {}