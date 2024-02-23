#include "graphics/directx11.h"

GraphicsEngine::GraphicsEngine(HWND hWnd, int width, int height) {
    render_system = new RenderSystem(hWnd, width, height);
}

GraphicsEngine::~GraphicsEngine() {
    delete render_system;
}

RenderSystem *GraphicsEngine::getRenderSystem() {

    return render_system;
}