#include "graphics/directx11.h"

#include "elementary/math.h"

#ifdef __GNUC__
#define ALIGN(x) __attribute__((aligned(x)))
#else
#define ALIGN(x) __declspec(align(x))
#endif

struct ALIGN(16) constant {
    mat4x4 m_world;
    mat4x4 m_view;
    mat4x4 m_proj;
    unsigned int m_time;
};

AppWindow::AppWindow() : Window() {}

void AppWindow::onCreate() {
    Window::onCreate();

    input = new InputSystem();
    engine = new GraphicsEngine();

    input->AddListener(this);

    engine->Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

    VERTEX vertex_list[] = {
        {{-0.5f, -0.5f, -0.5f}, {0, 0, 0}, {1, 1, 1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0, 1}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 1, 0}, {0, 0, 1}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {0, 1, 1}},
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 1}, {0, 1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0, 0, 0}},
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 1}, {1, 0, 0}},
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 1, 0}}
    };
    
    UINT size_vertex_list = ARRAYSIZE(vertex_list);

    UINT index_list[] = {
        0, 1, 2, 
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        1, 6, 5,
        5, 2, 1,
        7, 0, 3,
        3, 4, 7,
        3, 2, 5,
        5, 4, 3,
        7, 6, 1,
        1, 0, 7
    };

    UINT size_index_list = ARRAYSIZE(index_list);

    engine->CreateIndexBuffer(index_list, size_index_list);

    engine->CompileShader(L"shaders/VertexShader.hlsl", "vsmain", "vs_5_0");
    vs = engine->CreateVertexShader();
    engine->CreateVertexBuffer(vertex_list, sizeof(VERTEX), size_vertex_list);
    engine->ReleaseBlob();

    engine->CompileShader(L"shaders/PixelShader.hlsl", "psmain", "ps_5_0");
    ps = engine->CreatePixelShader();
    engine->ReleaseBlob();

    constant cc;
    cc.m_time = 0;

    engine->CreateConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate() {
    Window::onUpdate();

    input->Update();
    
    engine->ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = getClientWindowRect();
    engine->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    ///
    constant cc;

    delta_pos += delta_time / 10.0f;

    if (delta_pos > 1.0f)
        delta_pos = 0.0f;

    delta_scale += delta_time * 2.0f;

    cc.m_world = mat4x4::scale(vec3(scale_cube, scale_cube, scale_cube));
    cc.m_world *= mat4x4::rotation(rot_x, rot_y, 0);
    cc.m_view = mat4x4::identity;
    cc.m_proj = mat4x4::orthoLH(
        (rc.right - rc.left) / 300.0f,
        (rc.bottom - rc.top) / 300.0f,
        -4.0f,
        4.0f
    );

    cc.m_time = GetTickCount();
    engine->UpdateConstantBuffer(&cc);
    ///

    engine->SetConstantBuffer(vs);
    engine->SetConstantBuffer(ps);

    engine->SetVertexShader(vs);
    engine->SetPixelShader(ps);

    engine->SetVertexBuffer();
    engine->SetIndexBuffer();

    engine->DrawIndexedTriangleList();

    engine->Present(true);

    old_delta = new_delta;
    new_delta = GetTickCount();

    delta_time = old_delta ? (new_delta - old_delta) / 1000.0f : 0;
}

void AppWindow::onDestroy() {
    Window::onDestroy();

    ps->Release();
    vs->Release();
    input->Release();
    engine->Release();
}

void AppWindow::onFocus() {
    Window::onFocus();
}

void AppWindow::onKillFocus() {
    Window::onKillFocus();
}

void AppWindow::onKeyDown(int key) {
    if (key == 'W')
        rot_x += 3.141f * delta_time;
    else if (key == 'S')
        rot_x -= 3.141f * delta_time;
    
    else if (key == 'A')
        rot_y += 3.141f * delta_time;
    else if (key == 'D')
        rot_y -= 3.141f * delta_time;
}

void AppWindow::onKeyUp(int key) {
    
}

void AppWindow::onMouseMove(const vec2 &delta_mouse_pos) {
    rot_x -= delta_mouse_pos.y * delta_time;
    rot_y -= delta_mouse_pos.x * delta_time;
}

void AppWindow::onLeftMouseDown(const vec2 &delta_mouse_pos) {
     scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const vec2 &delta_mouse_pos) {
     scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const vec2 &delta_mouse_pos) {
     scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const vec2 &delta_mouse_pos) {
     scale_cube = 1.0f;
}