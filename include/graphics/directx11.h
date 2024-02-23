#pragma once

#include <d3d11.h>

class RenderSystem {
public:
    RenderSystem();
    RenderSystem(const RenderSystem &) = delete;
    ~RenderSystem();

    void CreateDeviceAndSwapChain(HWND hWnd, int width, int height);
    void CreateVertexBuffer(void *list_vertices, UINT size_vertex, UINT size_list);
    void CreateIndexBuffer(void *list_indices, UINT size_list);
    void CreateConstantBuffer(void *buffer, UINT size_buffer);
    void UpdateConstantBuffer(void *buffer);
    void Present(bool vsync);

    void CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name);
    ID3D11VertexShader *CreateVertexShader();
    ID3D11PixelShader *CreatePixelShader();
    void ReleaseBlob();

    void ClearRenderTargetColor(float red, float green, float blue, float alpha);
    void SetVertexBuffer();
    void SetIndexBuffer();
    void DrawTriangleList();
    void DrawIndexedTriangleList();
    void DrawTriangleStrip();
    void SetViewportSize(UINT width, UINT height);

    void SetVertexShader(ID3D11VertexShader* vertex_shader);
    void SetPixelShader(ID3D11PixelShader* pixel_shader);

    void SetConstantBuffer(ID3D11VertexShader* vertex_shader);
    void SetConstantBuffer(ID3D11PixelShader* pixel_shader);
    
    //bool InitDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
private:
    ID3DBlob *blob = nullptr;
    IDXGISwapChain *swapchain = nullptr;
    ID3D11Device *dev = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11DeviceContext *devcon = nullptr;
    ID3D11RenderTargetView *backbuffer = nullptr;
    ID3D11InputLayout *pLayout = nullptr;
    ID3D11Buffer *pVBuffer = nullptr;
    UINT vertexSize = 0;
    UINT vBufferSize = 0;
    ID3D11Buffer *pIBuffer = nullptr;
    UINT iBufferSize = 0;
    ID3D11Buffer *pCBuffer = nullptr;
};

class GraphicsEngine {
public:
    static GraphicsEngine *Get();
    static void Create();
    static void Release();

    GraphicsEngine(const GraphicsEngine &) = delete;

    RenderSystem *GetRenderSystem();

private:
    static GraphicsEngine *engine;

    RenderSystem *render_system = nullptr;

    GraphicsEngine();
    ~GraphicsEngine();
};