#include "graphics/window.h"

#include "elementary/math.h"
#include "elementary/time.h"
#include "graphics/directx11.h"

#include <iostream>

float AppWindow::rot_x = 0.0f;
float AppWindow::rot_y = 0.0f;
float AppWindow::light_rot_y = 0.0f;

float AppWindow::forward = 0.0f;
float AppWindow::rightward = 0.0f;
float AppWindow::upward = 0.0f;

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

    RECT rc = GetClientWindowRect();

    GraphicsEngine::Get()->GetRenderSystem()->CreateSwapChain(hWnd, rc.right - rc.left, rc.bottom - rc.top);

    InputSystem::Get()->AddListener(this);

    play_state = true;
    fullscreen_state = false;

    InputSystem::Get()->ShowCursor(!play_state);

    Element::Load(L"assets/elements/loader.txt");

    if (play_state) {
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        InputSystem::Get()->SetCursorPosition(lastMousePos);
    }
    else {
        POINT current_mouse_pos = {};
        GetCursorPos(&current_mouse_pos);
        lastMousePos = vec2(current_mouse_pos.x, current_mouse_pos.y);
    }

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
        RECT rc = GetClientWindowRect();
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
    RECT rc = GetClientWindowRect();
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
            RECT rc = GetClientWindowRect();
            lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
            InputSystem::Get()->SetCursorPosition(lastMousePos);
        }
    }
    else if (key == 'F') {
        fullscreen_state = !fullscreen_state;

        RECT size_screen = GetScreenSize();

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
        RECT rc = GetClientWindowRect();
        lastMousePos = vec2((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
        InputSystem::Get()->SetCursorPosition(lastMousePos);
    }
    else
        lastMousePos = mouse_pos;
}

void AppWindow::onLeftMouseDown(const vec2 &mouse_pos) {
    // scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const vec2 &mouse_pos) {
    // scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const vec2 &mouse_pos) {
    // scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const vec2 &mouse_pos) {
    // scale_cube = 1.0f;
}

void AppWindow::Render() {
    GraphicsEngine::Get()->GetRenderSystem()->ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = GetClientWindowRect();
    GraphicsEngine::Get()->GetRenderSystem()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    Update();
    //std::cout << 1.0f / Time::GetDeltaTimeReal() << std::endl;

    Element::UpdateElements();

    GraphicsEngine::Get()->GetRenderSystem()->Present(false);

    Time::_UpdateTime();
}

void AppWindow::Update() {
    Element::UpdateElements();
}