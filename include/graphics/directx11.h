#pragma once

#include <d3d11.h>
#include <memory>
#include "data/textures.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class Texture;

class RenderSystem {
public:
    RenderSystem();
    RenderSystem(const RenderSystem &) = delete;
    ~RenderSystem();

    void CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
    std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void *vertex_list, UINT vertex_size, UINT list_size, const void *shader_byte_code, size_t shader_byte_size);
    std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void *index_list, UINT list_size);
    std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const void *buffer, UINT buffer_size);

    void CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name, void** shader_byte_code, size_t* shader_byte_size);
    std::shared_ptr<VertexShader> CreateVertexShader(const void *shader_byte_code, size_t shader_byte_size);
    std::shared_ptr<PixelShader> CreatePixelShader(const void *shader_byte_code, size_t shader_byte_size);
    void ReleaseCompiledShader();

    void Present(bool vsync);

    void ClearRenderTargetColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha);
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer);
    void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
    void DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
    void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
    void SetViewportSize(UINT width, UINT height);

    void SetVertexShader(const std::shared_ptr<VertexShader> &vertex_shader);
    void SetPixelShader(const std::shared_ptr<PixelShader> &pixel_shader);

    void SetConstantBuffer(const std::shared_ptr<VertexShader> &vertex_shader, const std::shared_ptr<ConstantBuffer> &buffer);
    void SetConstantBuffer(const std::shared_ptr<PixelShader> &pixel_shader, const std::shared_ptr<ConstantBuffer> &buffer);

    void SetTexture(const std::shared_ptr<VertexShader> &vertex_shader, const std::shared_ptr<Texture> &texture);
    void SetTexture(const std::shared_ptr<PixelShader> &pixel_shader, const std::shared_ptr<Texture> &texture);
    
    //bool InitDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
private:
    ID3DBlob *blob = nullptr;
    IDXGISwapChain *swapchain = nullptr;
    ID3D11Device *dev = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11DeviceContext *devcon = nullptr;
    ID3D11RenderTargetView *backbuffer = nullptr;

    friend class VertexBuffer;
    friend class IndexBuffer;
    friend class ConstantBuffer;
    friend class VertexShader;
    friend class PixelShader;
    friend class Texture;
};

class GraphicsEngine {
public:
    static GraphicsEngine *Get();
    static void Create();
    static void Release();

    GraphicsEngine(const GraphicsEngine &) = delete;

    RenderSystem *GetRenderSystem();
    TextureManager *GetTexManager();

private:
    static GraphicsEngine *engine;

    RenderSystem *render_system = nullptr;
    TextureManager *tex_manager = nullptr;

    GraphicsEngine();
    ~GraphicsEngine();
};