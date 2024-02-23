#include "graphics/window.h"

#include <d3d11.h>
#include <chrono>
#include "elementary/math.h"
#include "input/input_system.h"

class RenderSystem {
public:
    RenderSystem(HWND hWnd, int width, int height);
    RenderSystem(const RenderSystem &) = delete;
    ~RenderSystem();

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
    GraphicsEngine(HWND hWnd, int width, int height);
    GraphicsEngine(const GraphicsEngine &) = delete;
    ~GraphicsEngine();

    RenderSystem *getRenderSystem();
private:
    RenderSystem *render_system = nullptr;
};

class AppWindow : public Window, public InputListener {
public:
    // AppWindow(
    //     HINSTANCE hInstance,
    //     HINSTANCE hPrevInstance,
    //     LPSTR lpCmdLine,
    //     int nCmdShow
    // );
    AppWindow();
    AppWindow(const AppWindow &) = delete;

    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onFocus() override;
    virtual void onKillFocus() override;

    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onMouseMove(const vec2 &mouse_pos);
    virtual void onLeftMouseDown(const vec2 &mouse_pos);
    virtual void onLeftMouseUp(const vec2 &mouse_pos);
    virtual void onRightMouseDown(const vec2 &mouse_pos);
    virtual void onRightMouseUp(const vec2 &mouse_pos);
private:
    InputSystem *input;
    GraphicsEngine *engine;
    ID3D11VertexShader *vs;
    ID3D11PixelShader *ps;
    
    std::chrono::system_clock::time_point old_delta;
    std::chrono::system_clock::time_point new_delta;
    float delta_time;

    float delta_pos;
    float delta_scale;

    float rot_x = 0.0f;
    float rot_y = 0.0f;

    float scale_cube = 1;
    float forward = 0.0f;
    float rightward = 0.0f;
    float upward = 0.0f;

    bool hideMouse = false;
    bool lastHideMouse = false;
    vec2 lastMousePos = vec2(0, 0);

    mat4x4 world_cam;
};