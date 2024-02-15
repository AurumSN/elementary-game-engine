#include "graphics/window.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include "elementary/math.h"
#include "input/input_system.h"

class GraphicsEngine {
public:
    GraphicsEngine();
    GraphicsEngine(const GraphicsEngine &) = delete;
    bool Init(HWND hWnd, int width, int height);
    bool Release();

    bool CreateVertexBuffer(void *list_vertices, UINT size_vertex, UINT size_list);
    bool CreateIndexBuffer(void *list_indices, UINT size_list);
    bool CreateConstantBuffer(void *buffer, UINT size_buffer);
    void UpdateConstantBuffer(void *buffer);
    bool Present(bool vsync);

    bool CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name);
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

class AppWindow : public Window, public InputListener {
public:
    AppWindow();
    AppWindow(const AppWindow &) = delete;

    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onFocus() override;
    virtual void onKillFocus() override;

    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onMouseMove(const vec2 &delta_mouse_pos);
    virtual void onLeftMouseDown(const vec2 &delta_mouse_pos);
    virtual void onLeftMouseUp(const vec2 &delta_mouse_pos);
    virtual void onRightMouseDown(const vec2 &delta_mouse_pos);
    virtual void onRightMouseUp(const vec2 &delta_mouse_pos);
private:
    InputSystem input;
    GraphicsEngine engine;
    ID3D11VertexShader *vs;
    ID3D11PixelShader *ps;

    float old_delta;
    float new_delta;
    float delta_time;

    float delta_pos;
    float delta_scale;

    float rot_x = 0.0f;
    float rot_y = 0.0f;

    float scale_cube = 1;
};