#include "elementary/component.h"

#include "graphics/window.h"

mat4x4 Camera::_viewMatrix = mat4x4::identity;
mat4x4 Camera::_projectionMatrix = mat4x4::identity;
vec4 Camera::_cameraPosition = vec4::point(vec3::zero);

mat4x4 Camera::GetViewMatrix() {
    return _viewMatrix;
}

mat4x4 Camera::GetProjectionMatrix() {
    return _projectionMatrix;
}

vec4 Camera::GetCameraPosition() {
    return _cameraPosition;
}

void Camera::Update() {
    RECT rc = AppWindow::GetClientWindowRect();

    _cameraPosition = _transform->GetPosition();
    _viewMatrix = _transform->GetModelMatrix().getInverse();
    // _projectionMatrix = mat4x4::orthoLH(
    //     (rc.right - rc.left) / 300.0f,
    //     (rc.bottom - rc.top) / 300.0f,
    //     -4.0f,
    //     4.0f
    // );
    _projectionMatrix = mat4x4::perspectiveFovLH(
        1.57f,
        (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top),
        0.1f,
        100.0f
    );
}

Camera::Camera(Element *base) : Component(base) {}
Camera::~Camera() {}