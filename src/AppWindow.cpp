#include "graphics/window.h"

#include "elementary/math.h"
#include "elementary/time.h"
#include "graphics/directx11.h"

// #include <iostream>




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

    // earth_color_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\earth_color.jpg");
    // earth_spec_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\earth_spec.jpg");
    // earth_night_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\earth_night.jpg");
    // clouds_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\clouds.jpg");
    // sky_tex = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(L"assets\\textures\\stars_map.jpg");
    
    // mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"assets\\meshes\\sphere_hq.obj");
    // sky_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"assets\\meshes\\sphere.obj");

    resources = std::make_shared<ElementManager>(L"assets/elements/resources.txt");

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

    // void *shader_byte_code = nullptr;
    // size_t shader_byte_size = 0;

    // GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"assets/shaders/VertexShader.hlsl", "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
    // vertex_shader = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, shader_byte_size);
    // GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    // GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"assets/shaders/PixelShader.hlsl", "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
    // pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
    // GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    // GraphicsEngine::Get()->GetRenderSystem()->CompileShader(L"assets/shaders/SkyBoxShader.hlsl", "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
    // sky_pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
    // GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

    // constant cc;

    // constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    // sky_constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
    
    Time::_InitTime();
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

    // GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState(false);
    // std::shared_ptr<Texture> list_tex[4] = { earth_color_tex, earth_spec_tex, clouds_tex, earth_night_tex };
    // DrawMesh(mesh, vertex_shader, pixel_shader, constant_buffer, list_tex, 4);

    // GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState(true);
    // list_tex[0] = sky_tex;
    // DrawMesh(sky_mesh, vertex_shader, sky_pixel_shader, sky_constant_buffer, list_tex, 1);

    resources->Draw(ELEMENTS_FLAGS_ALL);

    GraphicsEngine::Get()->GetRenderSystem()->Present(true);

    Time::_UpdateTime();
}

void AppWindow::Update() {
    UpdateCamera();
    UpdateModel();
    UpdateSkyBox();
    light_rot_y += 0.707f * Time::GetDeltaTime();
}

void AppWindow::UpdateCamera() {
    RECT rc = getClientWindowRect();
    mat4x4 world_cam = mat4x4::rotation(rot_x, rot_y, 0.0f);

    vec3 new_pos = world_camera.getTranslation() + (world_cam.getXDirection() * rightward + world_cam.getYDirection() * upward + world_cam.getZDirection() * forward) * Time::GetDeltaTime();

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
    cc.time = Time::GetTime();

    // constant_buffer->Update(&cc);
    resources->UpdateConstantBuffer(&cc, ELEMENTS_FLAGS_ALL & ~ELEMENTS_FLAGS_SKYBOX);
}

void AppWindow::UpdateSkyBox() {
    constant cc;

    cc.world = mat4x4::scale(vec3(100.0f, 100.0f, 100.0f)) * mat4x4::translation(world_camera.getTranslation());
    cc.view = view_camera;
    cc.proj = proj_camera;
    cc.camera_position = world_camera.getTranslation();
    cc.light_direction = vec4::point(mat4x4::rotationY(light_rot_y).getZDirection());
    cc.time = Time::GetTime();

    // sky_constant_buffer->Update(&cc);
    resources->UpdateConstantBuffer(&cc, ELEMENTS_FLAGS_ALL & ~ELEMENTS_FLAGS_NOT_SKYBOX);
}

void AppWindow::DrawMesh(
    const std::shared_ptr<Mesh> &mesh, 
    const std::shared_ptr<VertexShader> &vertex_shader, 
    const std::shared_ptr<PixelShader> &pixel_shader, 
    const std::shared_ptr<ConstantBuffer> &constant_buffer,
    const std::shared_ptr<Texture> *textures, 
    UINT texture_count
) {
    
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(vertex_shader, constant_buffer);
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(pixel_shader, constant_buffer);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexShader(vertex_shader);
    GraphicsEngine::Get()->GetRenderSystem()->SetPixelShader(pixel_shader);
    
    GraphicsEngine::Get()->GetRenderSystem()->SetTexture(pixel_shader, textures, texture_count);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexBuffer(mesh->GetVertexBuffer());
    GraphicsEngine::Get()->GetRenderSystem()->SetIndexBuffer(mesh->GetIndexBuffer());

    GraphicsEngine::Get()->GetRenderSystem()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
}