#pragma once

class GraphicsEngine {
public:
    static void Create();
    static void Release();

    GraphicsEngine(const GraphicsEngine &) = delete;
};