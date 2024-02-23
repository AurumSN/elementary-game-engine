#include "graphics/window.h"

#include <stdexcept>

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
) {
    Window *window;
    switch (Msg) {
    case WM_CREATE:
        window = (Window *)((LPCREATESTRUCT)lParam)->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
        window->setHWND(hWnd);
        window->onCreate();
        break;
    case WM_SETFOCUS:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        window->onFocus();
        break;
    case WM_KILLFOCUS:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        window->onKillFocus();
        break;
    case WM_DESTROY:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        window->onDestroy();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return 0;
}

Window::Window() {}

void Window::Init(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = 0;
    // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass1";
    wc.lpszMenuName = L"";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    if (!RegisterClassEx(&wc))
        throw std::runtime_error("Could not register class");

    RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

    hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW, 
        L"WindowClass1", 
        L"Out First Windowed Program", 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        wr.right - wr.left, 
        wr.bottom - wr.top,
        nullptr, 
        nullptr, 
        hInstance, 
        this
    );

    if (!hWnd)
        throw std::runtime_error("Could not create window");

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    bRunning = true;
}

Window::~Window() {
    DestroyWindow(hWnd);
        //throw std::runtime_error("Could not destroy window");
}

int Window::MessageLoop() {
    this->onUpdate();

    MSG msg;

    ZeroMemory(&msg, sizeof(MSG));

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
            break;
    }

    Sleep(0);

    return msg.wParam;
}

bool Window::isRunning() {
    return bRunning;
}


void Window::onCreate() {}
void Window::onUpdate() {}
void Window::onDestroy() { 
    bRunning = false; 
}
void Window::onFocus() {}
void Window::onKillFocus() {}

RECT Window::getClientWindowRect() {
    RECT rc;
    GetClientRect(hWnd, &rc);
    return rc;
}

HWND Window::getHWND() {
    return hWnd;
}
void Window::setHWND(HWND hWnd) {
    this->hWnd = hWnd;
}