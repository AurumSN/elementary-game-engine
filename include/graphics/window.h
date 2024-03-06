#pragma once

#include <windows.h>
#include <d3d11.h>
#include <chrono>
#include <memory>
#include "input/input_system.h"
#include "data/elements.h"

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
);

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

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onDestroy();
    virtual void onFocus();
    virtual void onKillFocus();
    virtual void onSize();

    HWND getHWND();

    Window &operator=(const Window &) = delete;
protected:
    static HWND hWnd;
    bool bRunning;
    bool bInit = false;

    int MessageLoop();
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

    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onFocus() override;
    virtual void onKillFocus() override;
    virtual void onSize() override;

    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onMouseMove(const vec2 &mouse_pos);
    virtual void onLeftMouseDown(const vec2 &mouse_pos);
    virtual void onLeftMouseUp(const vec2 &mouse_pos);
    virtual void onRightMouseDown(const vec2 &mouse_pos);
    virtual void onRightMouseUp(const vec2 &mouse_pos);

    void Render();
    void Update();
    void DrawMesh(
        const std::shared_ptr<Mesh> &mesh, 
        const std::shared_ptr<VertexShader> &vertex_shader, 
        const std::shared_ptr<PixelShader> &pixel_shader, 
        const std::shared_ptr<ConstantBuffer> &constant_buffer,
        const std::shared_ptr<Texture> *textures, 
        UINT texture_count
    );
private:
    bool play_state = false;
    bool fullscreen_state = false;
    vec2 lastMousePos = vec2(0, 0);
};