#include <windows.h>

#include "graphics/directx11.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "data/elements.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // MessageBox(
    //     NULL, 
    //     L"Hello World!", 
    //     L"Just another Hello World program!",
    //     MB_ICONEXCLAMATION | MB_OK
    // );
    GraphicsEngine::Create();
    InputSystem::Create();
    ElementManager::Create();

    AppWindow window(hInstance, hPrevInstance, lpCmdLine, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (window.isRunning());

    ElementManager::Release();
    GraphicsEngine::Release();
    InputSystem::Release();

    return 0;
}