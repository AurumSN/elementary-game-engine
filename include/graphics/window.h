#pragma once

#include <windows.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
);

class Window {
public:
    Window();
    Window(const Window &) = delete;

    bool Init(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow
    );
    bool Release();

    int MessageLoop();

    bool isRunning();

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onDestroy();
    virtual void onFocus();
    virtual void onKillFocus();

    RECT getClientWindowRect();

    HWND getHWND();
    void setHWND(HWND hWnd);

    Window &operator=(const Window &) = delete;
protected:
    HWND hWnd;
    bool bRunning;
};