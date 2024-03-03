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
        
        break;
    case WM_SIZE:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (window)
            window->onSize();
        break;
    case WM_SETFOCUS:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (window)
            window->onFocus();
        break;
    case WM_KILLFOCUS:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (window)
            window->onKillFocus();
        break;
    case WM_DESTROY:
        window = (Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (window)
            window->onDestroy();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return 0;
}

Window::Window(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow,
    int width,
    int height
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

    RECT wr = {0, 0, width, height};
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
        nullptr
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

    if (!this->bInit) {
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
        this->onCreate();
        this->bInit = true;
    }
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
    if (bRunning)
        MessageLoop();

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

RECT Window::getScreenSize() {
    RECT rc;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    return rc;
}

HWND Window::getHWND() {
    return hWnd;
}

void Window::onSize() {
    
}