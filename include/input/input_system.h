#pragma once

#include <unordered_set>
#include "elementary/math.h"

class InputListener {
public:
    InputListener();

    virtual void onKeyDown(int key) = 0;
    virtual void onKeyUp(int key) = 0;

    virtual void onMouseMove(const vec2 &mouse_pos) = 0;

    virtual void onLeftMouseDown(const vec2 &mouse_pos) = 0;
    virtual void onLeftMouseUp(const vec2 &mouse_pos) = 0;

    virtual void onRightMouseDown(const vec2 &mouse_pos) = 0;
    virtual void onRightMouseUp(const vec2 &mouse_pos) = 0;
};

class InputSystem {
public:
    InputSystem();

    void Update();
    void AddListener(InputListener *listener);
    void RemoveListener(InputListener *listener);

    void SetCursorPosition(const vec2 &pos);
    void ShowCursor(bool show);
private:
    std::unordered_set<InputListener *> m_set_listeners;
    unsigned char keys_state[256] = {};
    unsigned char old_keys_state[256] = {};
    vec2 old_mouse_pos;
    bool first_time = true;
};