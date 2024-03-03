#pragma once

#include <windows.h>
#include <d3d11.h>
#include <chrono>
#include <memory>
#include "input/input_system.h"
#include "data/textures.h"
#include "data/meshes.h"
#include "graphics/components/buffers.h"
#include "graphics/components/shaders.h"

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
    virtual void onSize();

    RECT getClientWindowRect();
    RECT getScreenSize();

    HWND getHWND();

    Window &operator=(const Window &) = delete;
protected:
    HWND hWnd;
    bool bRunning;
    bool bInit = false;

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
    void UpdateCamera();
    void UpdateModel();
    void UpdateSkyBox();
    void DrawMesh(
        const std::shared_ptr<Mesh> &mesh, 
        const std::shared_ptr<VertexShader> &vertex_shader, 
        const std::shared_ptr<PixelShader> &pixel_shader, 
        const std::shared_ptr<ConstantBuffer> &constant_buffer,
        const std::shared_ptr<Texture> &texture
    );
private:
    std::shared_ptr<VertexBuffer> vertex_buffer;
    std::shared_ptr<IndexBuffer> index_buffer;

    std::shared_ptr<VertexShader> vertex_shader;
    std::shared_ptr<PixelShader> pixel_shader;
    std::shared_ptr<ConstantBuffer> constant_buffer;

    std::shared_ptr<PixelShader> sky_pixel_shader;
    std::shared_ptr<ConstantBuffer> sky_constant_buffer;

    std::shared_ptr<Texture> tex;
    std::shared_ptr<Texture> sky_tex;

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Mesh> sky_mesh;



    
    std::chrono::high_resolution_clock::time_point old_delta;
    std::chrono::high_resolution_clock::time_point new_delta;
    float delta_time;

    float delta_pos;
    float delta_scale;

    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float light_rot_y = 0.0f;

    float scale_cube = 1;
    float forward = 0.0f;
    float rightward = 0.0f;
    float upward = 0.0f;

    bool play_state = false;
    bool fullscreen_state = false;
    vec2 lastMousePos = vec2(0, 0);

    mat4x4 world_camera;
    mat4x4 view_camera;
    mat4x4 proj_camera;
};