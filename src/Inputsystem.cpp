#include "input/input_system.h"

#include <Windows.h>
#include <cstring>
#include <iostream>

InputSystem::InputSystem() {}

void InputSystem::Update() {
    POINT cmp = {};
    GetCursorPos(&cmp);
    vec2 current_mouse_pos = vec2(cmp.x, cmp.y);

    if (first_time) {
        old_mouse_pos = vec2(current_mouse_pos.x, current_mouse_pos.y);
        first_time = false;
    }

    if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y) {
        std::unordered_set<InputListener *>::iterator it = m_set_listeners.begin();

        while (it != m_set_listeners.end()) {
            (*it)->onMouseMove(vec2(current_mouse_pos.x, current_mouse_pos.y));
            it++;
        }
    }

    old_mouse_pos = vec2(current_mouse_pos.x, current_mouse_pos.y);

    if (GetKeyboardState(keys_state)) {
        for (unsigned int i = 0; i < 256; i++) {
            if (keys_state[i] & 0x80) {
                std::unordered_set<InputListener *>::iterator it = m_set_listeners.begin();

                while (it != m_set_listeners.end()) {
                    if (i == VK_LBUTTON) {
                        if (keys_state[i] != old_keys_state[i])
                            (*it)->onLeftMouseDown(vec2(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else if (i == VK_RBUTTON) {
                        if (keys_state[i] != old_keys_state[i])
                            (*it)->onRightMouseDown(vec2(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else
                        (*it)->onKeyDown(i);
                        
                    it++;
                }
            }
            else {
                if (keys_state[i] != old_keys_state[i]) {
                    std::unordered_set<InputListener *>::iterator it = m_set_listeners.begin();

                    while (it != m_set_listeners.end()) {
                        if (i == VK_LBUTTON)
                            (*it)->onLeftMouseUp(vec2(current_mouse_pos.x, current_mouse_pos.y));
                        else if (i == VK_RBUTTON)
                            (*it)->onRightMouseUp(vec2(current_mouse_pos.x, current_mouse_pos.y));
                        else
                            (*it)->onKeyUp(i);

                        it++;
                    }
                }
            }
        }
        memcpy(old_keys_state, keys_state, sizeof(unsigned char) * 256);
    }
}

void InputSystem::AddListener(InputListener *listener) {
    m_set_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener *listener) {
    m_set_listeners.erase(listener);
}

void InputSystem::SetCursorPosition(const vec2 &pos) {
    SetCursorPos(pos.x, pos.y);
}


void InputSystem::ShowCursor(bool show) {
    ::ShowCursor(show);
}