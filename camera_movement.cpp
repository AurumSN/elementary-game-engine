#include "elementary/component.h"

#include <sstream>
#include "graphics/window.h"
#include "elementary/time.h"

#include <iostream>

class CameraMovement : public Component {
public:
    CameraMovement(Element *base) : Component(base) {}
    ~CameraMovement() {}

    virtual void Load(std::wstring arguments, ElementData &data, Element *base) override {
        std::wstringstream ss(arguments);
        ss >> speed;
    }
    virtual void Update() override {
        
    // mat4x4 world_cam = mat4x4::rotation(rot_x, rot_y, 0.0f);

    // vec3 new_pos = world_camera.getTranslation() + (world_cam.getXDirection() * rightward + world_cam.getYDirection() * upward + world_cam.getZDirection() * forward) * Time::GetDeltaTime();

    // world_cam *= mat4x4::translation(new_pos);
        _transform->rotation = vec3(AppWindow::rot_x, AppWindow::rot_y);
        mat4x4 mat = mat4x4::rotationY(AppWindow::rot_y);
        _transform->position += (mat.getXDirection() * AppWindow::rightward + mat.getYDirection() * AppWindow::upward + mat.getZDirection() *  AppWindow::forward) * Time::GetDeltaTime() * speed;
    }
protected:
    float speed = 0.0f;
};