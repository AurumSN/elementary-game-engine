#include <windows.h>

#include "graphics/directx11.h"

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

    AppWindow window;
    
    window.Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    while (window.isRunning()) {
        window.MessageLoop();
    }

    return 0;
}