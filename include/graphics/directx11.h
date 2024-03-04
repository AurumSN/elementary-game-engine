#pragma once

#include <d3d11.h>
#include <memory>

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class Texture;
class ElementManager;

class RenderSystem {
public:
    RenderSystem();
    RenderSystem(const RenderSystem &) = delete;
    ~RenderSystem();

    void CreateSwapChain(HWND hWnd, UINT width, UINT height);
    std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void *vertex_list, UINT vertex_size, UINT list_size, const void *shader_byte_code, size_t shader_byte_size);
    std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void *index_list, UINT list_size);
    std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const void *buffer, UINT buffer_size);

    void CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name, void** shader_byte_code, size_t* shader_byte_size);
    std::shared_ptr<VertexShader> CreateVertexShader(const void *shader_byte_code, size_t shader_byte_size);
    std::shared_ptr<PixelShader> CreatePixelShader(const void *shader_byte_code, size_t shader_byte_size);
    void ReleaseCompiledShader();
    
    void SetRasterizerState(bool cull_front);

    void SetFullScreen(bool fullscreen, UINT width, UINT height);
    void Resize(UINT width, UINT height);
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

    void SetTexture(const std::shared_ptr<VertexShader> &vertex_shader, const std::shared_ptr<Texture> *textures, UINT texture_count);
    void SetTexture(const std::shared_ptr<PixelShader> &pixel_shader, const std::shared_ptr<Texture> *textures, UINT texture_count);
    
    //bool InitDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
private:
    ID3DBlob *blob = nullptr;
    
    ID3D11RasterizerState *cull_front_state = nullptr;
    ID3D11RasterizerState *cull_back_state = nullptr;

    IDXGISwapChain *swapchain = nullptr;
    ID3D11Device *dev = nullptr;
    IDXGIDevice *dxgi_device = nullptr;
    IDXGIAdapter *dxgi_adapter = nullptr;
    IDXGIFactory *dxgi_factory = nullptr;
    D3D_FEATURE_LEVEL feature_level;
    ID3D11DeviceContext *devcon = nullptr;
    ID3D11RenderTargetView *backbuffer = nullptr;
    ID3D11DepthStencilView *depth_stencil_view = nullptr;

    friend class VertexBuffer;
    friend class IndexBuffer;
    friend class ConstantBuffer;
    friend class VertexShader;
    friend class PixelShader;
    friend class Texture;

    void InitRasterizerState();
    void ReloadBuffers(UINT width, UINT height);
};

class GraphicsEngine {
public:
    static GraphicsEngine *Get();
    static void Create();
    static void Release();

    GraphicsEngine(const GraphicsEngine &) = delete;

    RenderSystem *GetRenderSystem();
    // TextureManager *GetTexManager();
    // MeshManager *GetMeshManager();

    void GetVertexMeshLayoutShader(void **shader_byte_code, size_t *shader_byte_size);
private:
    static GraphicsEngine *engine;

    RenderSystem *render_system = nullptr;

    unsigned char vertex_mesh_layout_shader_byte_code[1024];
    size_t vertex_mesh_layout_shader_byte_size = 0;

    GraphicsEngine();
    ~GraphicsEngine();
};