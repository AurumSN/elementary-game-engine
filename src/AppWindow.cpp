#include "graphics/window.h"

#include "elementary/math.h"
#include "graphics/directx11.h"

// #include <iostream>


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

    play_state = true;
    fullscreen_state = false;

    InputSystem::Get()->ShowCursor(!play_state);

    tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\brick.png");
    sky_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\sky.jpg");
    
    mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"assets\\meshes\\suzanne.obj");
    sky_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"assets\\meshes\\sphere.obj");

    if (play_state) {
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        InputSystem::Get()->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }

    world_camera = mat4x4::translation(vec3(0, 0, -2));

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

    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"shaders/SkyBoxShader.hlsl", "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
    sky_pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    constant cc;

    constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    sky_constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    
    new_delta = std::chrono::high_resolution_clock::now();
}

void AppWindow::onUpdate() {
    Window::onUpdate();

    InputSystem::Get()->Update();

    this->Render();
}

void AppWindow::onDestroy() {
    Window::onDestroy();

    GraphicsEngine::Get()->GetRenderSystem()->SetFullScreen(false, 1, 1);
}

void AppWindow::onFocus() {
    Window::onFocus();
    InputSystem::Get()->AddListener(this);
    if (play_state) {
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

void AppWindow::onSize() {
    Window::onSize();
    RECT rc = this->getClientWindowRect();
    //GraphicsEngine::Get()->GetRenderSystem()->Resize(rc.right - rc.left, rc.bottom - rc.top);
    GraphicsEngine::Get()->GetRenderSystem()->Resize(rc.right, rc.bottom);
    this->Render();
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
}

void AppWindow::onKeyUp(int key) {
    forward = 0.0f;
    rightward = 0.0f;
    upward = 0.0f;

    if (key == 'G') {
        play_state = !play_state;
        std::cout << play_state << std::endl;
        InputSystem::Get()->ShowCursor(!play_state);
        if (play_state) {
            RECT rc = getClientWindowRect();
            lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
            InputSystem::Get()->SetCursorPosition(lastMousePos);
        }
    }
    else if (key == 'F') {
        fullscreen_state = !fullscreen_state;

        RECT size_screen = this->getScreenSize();

        GraphicsEngine::Get()->GetRenderSystem()->SetFullScreen(fullscreen_state, size_screen.right, size_screen.bottom);
    }
}

void AppWindow::onMouseMove(const vec2 &mouse_pos) {

    if (!play_state)
        return;

    rot_x += (mouse_pos.y - lastMousePos.y) * 0.005f;
    rot_y += (mouse_pos.x - lastMousePos.x) * 0.005f;

    if (rot_x > 1.57f)
        rot_x = 1.57f;
    else if (rot_x < - 1.57f)
        rot_x = -1.57f;

    if (play_state) {
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

void AppWindow::Render() {
    GraphicsEngine::Get()->GetRenderSystem()->ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = getClientWindowRect();
    GraphicsEngine::Get()->GetRenderSystem()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    Update();

    GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState(false);
    DrawMesh(mesh, vertex_shader, pixel_shader, constant_buffer, tex);

    GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState(true);
    DrawMesh(sky_mesh, vertex_shader, sky_pixel_shader, sky_constant_buffer, sky_tex);

    GraphicsEngine::Get()->GetRenderSystem()->Present(true);

    old_delta = new_delta;
    new_delta = std::chrono::high_resolution_clock::now();

    delta_time = std::chrono::duration_cast<std::chrono::microseconds>(new_delta - old_delta).count() * 0.000001f;
}

void AppWindow::Update() {
    UpdateCamera();
    UpdateModel();
    UpdateSkyBox();
    light_rot_y += 0.707f * delta_time;
}

void AppWindow::UpdateCamera() {
    RECT rc = getClientWindowRect();
    mat4x4 world_cam = mat4x4::rotation(rot_x, rot_y, 0.0f);

    vec3 new_pos = world_camera.getTranslation() + (world_cam.getXDirection() * rightward + world_cam.getYDirection() * upward + world_cam.getZDirection() * forward) * delta_time;

    world_cam *= mat4x4::translation(new_pos);

    world_camera = world_cam;
    view_camera = world_cam.getInverse();
    // proj_camera = mat4x4::orthoLH(
    //     (rc.right - rc.left) / 300.0f,
    //     (rc.bottom - rc.top) / 300.0f,
    //     -4.0f,
    //     4.0f
    // );
    proj_camera = mat4x4::perspectiveFovLH(
        1.57f,
        (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top),
        0.1f,
        100.0f
    );
}

void AppWindow::UpdateModel() {
    constant cc;

    cc.world = mat4x4::identity;
    cc.view = view_camera;
    cc.proj = proj_camera;
    cc.camera_position = world_camera.getTranslation();
    cc.light_direction = vec4::point(mat4x4::rotationY(light_rot_y).getZDirection());

    constant_buffer->Update(&cc);
}

void AppWindow::UpdateSkyBox() {
    constant cc;

    cc.world = mat4x4::scale(vec3(100.0f, 100.0f, 100.0f)) * mat4x4::translation(world_camera.getTranslation());
    cc.view = view_camera;
    cc.proj = proj_camera;
    cc.camera_position = world_camera.getTranslation();
    cc.light_direction = vec4::point(mat4x4::rotationY(light_rot_y).getZDirection());

    sky_constant_buffer->Update(&cc);
}

void AppWindow::DrawMesh(
    const std::shared_ptr<Mesh> &mesh, 
    const std::shared_ptr<VertexShader> &vertex_shader, 
    const std::shared_ptr<PixelShader> &pixel_shader, 
    const std::shared_ptr<ConstantBuffer> &constant_buffer,
    const std::shared_ptr<Texture> &texture
) {
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(vertex_shader, constant_buffer);
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(pixel_shader, constant_buffer);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexShader(vertex_shader);
    GraphicsEngine::Get()->GetRenderSystem()->SetPixelShader(pixel_shader);
    
    GraphicsEngine::Get()->GetRenderSystem()->SetTexture(pixel_shader, texture);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexBuffer(mesh->GetVertexBuffer());
    GraphicsEngine::Get()->GetRenderSystem()->SetIndexBuffer(mesh->GetIndexBuffer());

    GraphicsEngine::Get()->GetRenderSystem()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
}