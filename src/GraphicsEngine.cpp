#include "graphics/directx11.h"

#include <stdexcept>

GraphicsEngine *GraphicsEngine::engine = nullptr;

GraphicsEngine *GraphicsEngine::Get() {
    return engine;
}

void GraphicsEngine::Create() {
    if (engine) 
        throw std::runtime_error("Graphics Engine already exists");

    engine = new GraphicsEngine();
}

void GraphicsEngine::Release() {
    if (engine) 
        delete engine;
}

GraphicsEngine::GraphicsEngine() {
    render_system = new RenderSystem();
    tex_manager = new TextureManager();
}

GraphicsEngine::~GraphicsEngine() {
    engine = nullptr;
    delete tex_manager;
    delete render_system;
}

RenderSystem *GraphicsEngine::GetRenderSystem() {
    return render_system;
}

TextureManager *GraphicsEngine::GetTexManager() {
    return tex_manager;
}