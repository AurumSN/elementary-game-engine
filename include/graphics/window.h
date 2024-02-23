#pragma once

#include <windows.h>
#include <d3d11.h>
#include <chrono>
#include "input/input_system.h"

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
);

class Window {
public:
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

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onDestroy();
    virtual void onFocus();
    virtual void onKillFocus();

    RECT getClientWindowRect();

    HWND getHWND();

    Window &operator=(const Window &) = delete;
protected:
    HWND hWnd;
    bool bRunning;
    bool bIsInit = false;
    
    int MessageLoop();
};

class AppWindow : public Window, public InputListener {
public:
    AppWindow(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        int width,
        int height
    );
    AppWindow(const AppWindow &) = delete;

    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onFocus() override;
    virtual void onKillFocus() override;

    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onMouseMove(const vec2 &mouse_pos);
    virtual void onLeftMouseDown(const vec2 &mouse_pos);
    virtual void onLeftMouseUp(const vec2 &mouse_pos);
    virtual void onRightMouseDown(const vec2 &mouse_pos);
    virtual void onRightMouseUp(const vec2 &mouse_pos);
private:
    ID3D11VertexShader *vs;
    ID3D11PixelShader *ps;
    
    std::chrono::high_resolution_clock::time_point old_delta;
    std::chrono::high_resolution_clock::time_point new_delta;
    float delta_time;

    float delta_pos;
    float delta_scale;

    float rot_x = 0.0f;
    float rot_y = 0.0f;

    float scale_cube = 1;
    float forward = 0.0f;
    float rightward = 0.0f;
    float upward = 0.0f;

    bool hideMouse = true;
    bool lastHideMouse = true;
    vec2 lastMousePos = vec2(0, 0);

    mat4x4 world_cam;
};