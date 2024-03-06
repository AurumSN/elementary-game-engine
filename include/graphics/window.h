#pragma once

#include <windows.h>
#include "input/input_system.h"

class Window {
public:
    static RECT GetClientWindowRect();
    static RECT GetScreenSize();

    Window(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        int width,
        int height
    );
    Window(const Window &) = delete;
    ~Window();

    bool isRunning();

    Window &operator=(const Window &) = delete;
};

class AppWindow : public Window, public InputListener {
public:
    static float rot_x;
    static float rot_y;
    static float light_rot_y;

    static float forward;
    static float rightward;
    static float upward;

    AppWindow(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        int width,
        int height
    );
    AppWindow(const AppWindow &) = delete;
    ~AppWindow();
};