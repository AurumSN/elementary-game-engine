#include "graphics/window.h"

#include "elementary/math.h"
#include "graphics/directx11.h"

//#include <iostream>


#ifdef __GNUC__
#define ALIGN(x) __attribute__((aligned(x)))
#else
#define ALIGN(x) __declspec(align(x))
#endif

struct ALIGN(16) constant {
    mat4x4 world;
    mat4x4 view;
    mat4x4 proj;
    vec4 light_direction;
    vec4 camera_position;
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

AppWindow::AppWindow(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow,
    int width,
    int height
) : Window(
    hInstance,
    hPrevInstance,
    lpCmdLine,
    nCmdShow,
    width,
    height
), InputListener() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
    Window::onCreate();

    RECT rc = getClientWindowRect();

    GraphicsEngine::Get()->GetRenderSystem()->CreateSwapChain(hWnd, rc.right - rc.left, rc.bottom - rc.top);

    InputSystem::Get()->AddListener(this);
    InputSystem::Get()->ShowCursor(!hideMouse);

    tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\brick.png");
    mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"assets\\meshes\\statue.obj");

    if (hideMouse) {
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        InputSystem::Get()->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }

    world_cam = mat4x4::translation(vec3(0, 0, -2));

    vec3 position_list[] = {
        {-0.5f, -0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f}
    };

    vec3 texcoord_list[] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    VERTEX vertex_list[] = {
        {position_list[0], texcoord_list[1]},
        {position_list[1], texcoord_list[0]},
        {position_list[2], texcoord_list[2]},
        {position_list[3], texcoord_list[3]},

        {position_list[4], texcoord_list[1]},
        {position_list[5], texcoord_list[0]},
        {position_list[6], texcoord_list[2]},
        {position_list[7], texcoord_list[3]},

        {position_list[1], texcoord_list[1]},
        {position_list[6], texcoord_list[0]},
        {position_list[5], texcoord_list[2]},
        {position_list[2], texcoord_list[3]},

        {position_list[7], texcoord_list[1]},
        {position_list[0], texcoord_list[0]},
        {position_list[3], texcoord_list[2]},
        {position_list[4], texcoord_list[3]},

        {position_list[3], texcoord_list[1]},
        {position_list[2], texcoord_list[0]},
        {position_list[5], texcoord_list[2]},
        {position_list[4], texcoord_list[3]},

        {position_list[7], texcoord_list[1]},
        {position_list[6], texcoord_list[0]},
        {position_list[1], texcoord_list[2]},
        {position_list[0], texcoord_list[3]}
    };
    
    UINT size_vertex_list = ARRAYSIZE(vertex_list);

    UINT index_list[] = {
         0,  1,  2, 
         2,  3,  0,

         4,  5,  6,
         6,  7,  4,

         8,  9, 10,
        10, 11,  8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    UINT size_index_list = ARRAYSIZE(index_list);

    index_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

    void *shader_byte_code = nullptr;
    size_t shader_byte_size = 0;

    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"shaders/VertexShader.hlsl", "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
    vertex_shader = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, shader_byte_size);
    vertex_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(VERTEX), size_vertex_list, shader_byte_code, shader_byte_size);
    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"shaders/PixelShader.hlsl", "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
    pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    constant cc;

    constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    
    new_delta = std::chrono::high_resolution_clock::now();
}

void AppWindow::onUpdate() {
    Window::onUpdate();

    InputSystem::Get()->Update();
    
    GraphicsEngine::Get()->GetRenderSystem()->ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = getClientWindowRect();
    GraphicsEngine::Get()->GetRenderSystem()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    ///
    constant cc;

    // delta_pos += delta_time / 10.0f;

    // if (delta_pos > 1.0f)
    //     delta_pos = 0.0f;

    // delta_scale += delta_time * 2.0f;

    // cc.m_world = mat4x4::scale(vec3(scale_cube, scale_cube, scale_cube));
    // cc.m_world *= mat4x4::rotation(rot_x, rot_y, 0);

    vec3 new_pos = world_cam.getTranslation() + (world_cam.getXDirection() * rightward + world_cam.getYDirection() * upward + world_cam.getZDirection() * forward) * delta_time;

    world_cam = mat4x4::rotation(rot_x, rot_y, 0.0f) * mat4x4::translation(new_pos);
    mat4x4 light_rot_matrix = mat4x4::rotationY(light_rot_y);
    light_rot_y += 0.707f * delta_time;

    cc.world = mat4x4::identity;
    cc.view = world_cam.getInverse();
    // cc.m_proj = mat4x4::orthoLH(
    //     (rc.right - rc.left) / 300.0f,
    //     (rc.bottom - rc.top) / 300.0f,
    //     -4.0f,
    //     4.0f
    // );
    cc.proj = mat4x4::perspectiveFovLH(
        1.57f,
        (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top),
        0.1f,
        100.0f
    );
    cc.light_direction = vec4::point(light_rot_matrix.getZDirection());
    cc.camera_position = vec4::point(new_pos);
    
    // std::cout << 1.0 / delta_time << std::endl;

    constant_buffer->Update(&cc);
    ///

    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(vertex_shader, constant_buffer);
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(pixel_shader, constant_buffer);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexShader(vertex_shader);
    GraphicsEngine::Get()->GetRenderSystem()->SetPixelShader(pixel_shader);
    
    GraphicsEngine::Get()->GetRenderSystem()->SetTexture(pixel_shader, tex);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexBuffer(mesh->GetVertexBuffer());
    GraphicsEngine::Get()->GetRenderSystem()->SetIndexBuffer(mesh->GetIndexBuffer());

    GraphicsEngine::Get()->GetRenderSystem()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);

    GraphicsEngine::Get()->GetRenderSystem()->Present(true);

    old_delta = new_delta;
    new_delta = std::chrono::high_resolution_clock::now();

    delta_time = std::chrono::duration_cast<std::chrono::microseconds>(new_delta - old_delta).count() * 0.000001f;
}

void AppWindow::onDestroy() {
    Window::onDestroy();
}

void AppWindow::onFocus() {
    Window::onFocus();
    InputSystem::Get()->AddListener(this);
    if (hideMouse) {
        RECT rc = getClientWindowRect();
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        InputSystem::Get()->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }
}

void AppWindow::onKillFocus() {
    Window::onKillFocus();
    InputSystem::Get()->RemoveListener(this);
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
        InputSystem::Get()->ShowCursor(!hideMouse);
        if (hideMouse) {
            RECT rc = getClientWindowRect();
            lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
            InputSystem::Get()->SetCursorPosition(lastMousePos);
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
        InputSystem::Get()->SetCursorPosition(lastMousePos);
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