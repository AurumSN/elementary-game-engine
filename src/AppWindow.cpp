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

// AppWindow::AppWindow(
//     HINSTANCE hInstance,
//     HINSTANCE hPrevInstance,
//     LPSTR lpCmdLine,
//     int nCmdShow
// ) : Window(
//     hInstance,
//     hPrevInstance,
//     lpCmdLine,
//     nCmdShow
// ) {}

AppWindow::AppWindow() : Window::Window() {}

void AppWindow::onCreate() {
    Window::onCreate();

    input = new InputSystem();
    engine = new GraphicsEngine(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

    input->AddListener(this);
    input->ShowCursor(!hideMouse);
    if (hideMouse) {
        lastMousePos = vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        input->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }

    world_cam = mat4x4::translation(vec3(0, 0, -2));

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

    engine->getRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

    engine->getRenderSystem()->CompileShader(L"shaders/VertexShader.hlsl", "vsmain", "vs_5_0");
    vs = engine->getRenderSystem()->CreateVertexShader();
    engine->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(VERTEX), size_vertex_list);
    engine->getRenderSystem()->ReleaseBlob();

    engine->getRenderSystem()->CompileShader(L"shaders/PixelShader.hlsl", "psmain", "ps_5_0");
    ps = engine->getRenderSystem()->CreatePixelShader();
    engine->getRenderSystem()->ReleaseBlob();

    constant cc;
    cc.m_time = 0;

    engine->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    
    new_delta = std::chrono::high_resolution_clock::now();
}

void AppWindow::onUpdate() {
    Window::onUpdate();

    input->Update();
    
    engine->getRenderSystem()->ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = getClientWindowRect();
    engine->getRenderSystem()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    ///
    constant cc;

    // delta_pos += delta_time / 10.0f;

    // if (delta_pos > 1.0f)
    //     delta_pos = 0.0f;

    // delta_scale += delta_time * 2.0f;

    // cc.m_world = mat4x4::scale(vec3(scale_cube, scale_cube, scale_cube));
    // cc.m_world *= mat4x4::rotation(rot_x, rot_y, 0);

    vec3 new_pos = world_cam.getTranslation() + (world_cam.getXDirection() * rightward + world_cam.getYDirection() * upward + world_cam.getZDirection() * forward) * delta_time;

    world_cam = mat4x4::rotationX(rot_x) * mat4x4::rotationY(rot_y) * mat4x4::translation(new_pos);

    cc.m_world = mat4x4::identity;
    cc.m_view = world_cam.getInverse();
    // cc.m_proj = mat4x4::orthoLH(
    //     (rc.right - rc.left) / 300.0f,
    //     (rc.bottom - rc.top) / 300.0f,
    //     -4.0f,
    //     4.0f
    // );
    cc.m_proj = mat4x4::perspectiveFovLH(
        1.57f,
        (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top),
        0.1f,
        100.0f
    );
    
    std::cout << 1.0 / delta_time << std::endl;

    cc.m_time = GetTickCount();
    engine->getRenderSystem()->UpdateConstantBuffer(&cc);
    ///

    engine->getRenderSystem()->SetConstantBuffer(vs);
    engine->getRenderSystem()->SetConstantBuffer(ps);

    engine->getRenderSystem()->SetVertexShader(vs);
    engine->getRenderSystem()->SetPixelShader(ps);

    engine->getRenderSystem()->SetVertexBuffer();
    engine->getRenderSystem()->SetIndexBuffer();

    engine->getRenderSystem()->DrawIndexedTriangleList();

    engine->getRenderSystem()->Present(true);

    old_delta = new_delta;
    new_delta = std::chrono::high_resolution_clock::now();

    delta_time = std::chrono::duration_cast<std::chrono::microseconds>(new_delta - old_delta).count() * 0.000001f;
}

void AppWindow::onDestroy() {
    Window::onDestroy();

    ps->Release();
    vs->Release();

    delete input;
    delete engine;
}

void AppWindow::onFocus() {
    Window::onFocus();
    input->AddListener(this);
    if (hideMouse) {
        lastMousePos = vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
        input->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }
}

void AppWindow::onKillFocus() {
    Window::onKillFocus();
    input->RemoveListener(this);
}

void AppWindow::onKeyDown(int key) {
    if (key == 'W')
        forward = 1.0f;
    else if (key == 'S')
        forward = -1.0f;
    else if (key == 'A')
        rightward = -1.0f;
    else if (key == 'D')
        rightward = 1.0f;
    else if (key == VK_SPACE)
        upward = 1.0f;
    else if (key == VK_LCONTROL)
        upward = -1.0f;
    else if (key == VK_ESCAPE && lastHideMouse == hideMouse) {
        hideMouse = !hideMouse;
        input->ShowCursor(!hideMouse);
        if (hideMouse) {
            RECT rc = getClientWindowRect();
            lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
            input->SetCursorPosition(lastMousePos);
        }
    }
}

void AppWindow::onKeyUp(int key) {
    forward = 0.0f;
    rightward = 0.0f;
    upward = 0.0f;
    lastHideMouse = hideMouse;
}

void AppWindow::onMouseMove(const vec2 &mouse_pos) {

    rot_x += (mouse_pos.y - lastMousePos.y) * 0.005f;
    rot_y += (mouse_pos.x - lastMousePos.x) * 0.005f;

    if (rot_x > 1.57f)
        rot_x = 1.57f;
    else if (rot_x < - 1.57f)
        rot_x = -1.57f;

    if (hideMouse) {
        RECT rc = getClientWindowRect();
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        input->SetCursorPosition(lastMousePos);
    }
    else
        lastMousePos = mouse_pos;
}

void AppWindow::onLeftMouseDown(const vec2 &mouse_pos) {
     scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const vec2 &mouse_pos) {
     scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const vec2 &mouse_pos) {
     scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const vec2 &mouse_pos) {
     scale_cube = 1.0f;
}