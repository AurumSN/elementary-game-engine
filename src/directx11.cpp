#include "graphics/directx11.h"

#include <cmath>
#include <iostream>
#include "elementary/math.h"

struct __attribute__((aligned(16))) constant {
    mat4x4 m_world;
    mat4x4 m_view;
    mat4x4 m_proj;
    unsigned int m_time;
};

AppWindow::AppWindow() : Window() {}

void AppWindow::onCreate() {
    Window::onCreate();

    input.AddListener(this);

    engine.Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

    VERTEX vertex_list[] = {
        {{-0.5f, -0.5f, -0.5f}, {0, 0, 0}, {1, 1, 1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0, 1}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 1, 0}, {0, 0, 1}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {0, 1, 1}},
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 1}, {0, 1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0, 0, 0}},
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 1}, {1, 0, 0}},
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 1, 0}}
    };
    
    UINT size_vertex_list = ARRAYSIZE(vertex_list);

    UINT index_list[] = {
        0, 1, 2, 
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        1, 6, 5,
        5, 2, 1,
        7, 0, 3,
        3, 4, 7,
        3, 2, 5,
        5, 4, 3,
        7, 6, 1,
        1, 0, 7
    };

    UINT size_index_list = ARRAYSIZE(index_list);

    engine.CreateIndexBuffer(index_list, size_index_list);

    engine.CompileShader(L"shaders/VertexShader.hlsl", "vsmain", "vs_5_0");
    vs = engine.CreateVertexShader();
    std::cout << engine.CreateVertexBuffer(vertex_list, sizeof(VERTEX), size_vertex_list) << std::endl;
    engine.ReleaseBlob();

    engine.CompileShader(L"shaders/PixelShader.hlsl", "psmain", "ps_5_0");
    ps = engine.CreatePixelShader();
    engine.ReleaseBlob();

    constant cc;
    cc.m_time = 0;

    engine.CreateConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate() {
    Window::onUpdate();

    input.Update();
    
    engine.ClearRenderTargetColor(0, 0.3f, 0.4f, 1);

    RECT rc = getClientWindowRect();
    engine.SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    //
    constant cc;

    delta_pos += delta_time / 10.0f;

    if (delta_pos > 1.0f)
        delta_pos = 0.0f;

    delta_scale += delta_time * 2.0f;

    cc.m_world = mat4x4::scale(vec3(scale_cube, scale_cube, scale_cube));
    cc.m_world *= mat4x4::rotation(rot_x, rot_y, 0);
    cc.m_view = mat4x4::identity;
    cc.m_proj = mat4x4::orthoLH(
        (rc.right - rc.left) / 300.0f,
        (rc.bottom - rc.top) / 300.0f,
        -4.0f,
        4.0f
    );

    cc.m_time = GetTickCount();
    engine.UpdateConstantBuffer(&cc);
    //

    engine.SetConstantBuffer(vs);
    engine.SetConstantBuffer(ps);

    engine.SetVertexShader(vs);
    engine.SetPixelShader(ps);

    engine.SetVertexBuffer();
    engine.SetIndexBuffer();

    engine.DrawIndexedTriangleList();

    engine.Present(true);

    old_delta = new_delta;
    new_delta = GetTickCount();

    delta_time = old_delta ? (new_delta - old_delta) / 1000.0f : 0;
}

void AppWindow::onDestroy() {
    Window::onDestroy();

    ps->Release();
    vs->Release();
    engine.Release();
}

void AppWindow::onFocus() {
    Window::onFocus();
}

void AppWindow::onKillFocus() {
    Window::onKillFocus();
}

void AppWindow::onKeyDown(int key) {
    if (key == 'W')
        rot_x += 3.141f * delta_time;
    else if (key == 'S')
        rot_x -= 3.141f * delta_time;
    
    else if (key == 'A')
        rot_y += 3.141f * delta_time;
    else if (key == 'D')
        rot_y -= 3.141f * delta_time;
}

void AppWindow::onKeyUp(int key) {
    
}

void AppWindow::onMouseMove(const vec2 &delta_mouse_pos) {
    rot_x -= delta_mouse_pos.y * delta_time;
    rot_y -= delta_mouse_pos.x * delta_time;
}

void AppWindow::onLeftMouseDown(const vec2 &delta_mouse_pos) {
     scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const vec2 &delta_mouse_pos) {
     scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const vec2 &delta_mouse_pos) {
     scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const vec2 &delta_mouse_pos) {
     scale_cube = 1.0f;
}






GraphicsEngine::GraphicsEngine() {}

bool GraphicsEngine::Init(HWND hWnd, int width, int height) {
    // D3D_DRIVER_TYPE driver_types[] = {
    //     D3D_DRIVER_TYPE_HARDWARE,
    //     D3D_DRIVER_TYPE_WARP,
    //     D3D_DRIVER_TYPE_REFERENCE
    // };
    // UINT num_driver_types = ARRAYSIZE(driver_types);

    // D3D_FEATURE_LEVEL feature_levels[] = {
    //     D3D_FEATURE_LEVEL_11_0
    // };
    // UINT num_feature_levels = ARRAYSIZE(feature_levels);

    // HRESULT res = 0;
    // for (UINT i = 0; i < num_driver_types; i++) {
    //     res = D3D11CreateDevice(NULL, driver_types[i], NULL, 0, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &dev, &featureLevel, &devcon);

    //     if (SUCCEEDED(res))
    //         break;
    // }

    // if (FAILED(res))
    //     return false;





    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = TRUE;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D11CreateDeviceAndSwapChain(
        nullptr, 
        D3D_DRIVER_TYPE_HARDWARE, 
        nullptr, 
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        nullptr,
        &devcon
    );

    ID3D11Texture2D *pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);

    dev->CreateRenderTargetView(pBackBuffer, nullptr, &backbuffer);
    pBackBuffer->Release();

    return true;

    devcon->OMSetRenderTargets(1, &backbuffer, nullptr);

    D3D11_VIEWPORT viewport;

    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = width;
    viewport.Height = height;

    devcon->RSSetViewports(1, &viewport);

    // Pipeline
    // ID3D10Blob *VS, *PS;
    // D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "VShader", "vs_5_0", 0, 0, &VS, nullptr);
    // D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "PShader", "ps_5_0", 0, 0, &PS, nullptr);

    // dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVS);
    // dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPS);

    // devcon->VSSetShader(pVS, 0, 0);
    // devcon->PSSetShader(pPS, 0, 0);

    // D3D11_INPUT_ELEMENT_DESC ied[] = {
    //     {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    //     {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    // };

    // dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    // devcon->IASetInputLayout(pLayout);

    // // Graphics
    // VERTEX vertices[] = {
    //     {{ 0.00f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    //     {{ 0.45f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
    //     {{-0.45f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
    // };

    // D3D11_BUFFER_DESC bd;
    // ZeroMemory(&bd, sizeof(bd));

    // bd.Usage = D3D11_USAGE_DYNAMIC;
    // bd.ByteWidth = sizeof(VERTEX) * 3;
    // bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    // bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // dev->CreateBuffer(&bd, nullptr, &pVBuffer);

    // D3D11_MAPPED_SUBRESOURCE ms;
    // devcon->Map(pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    // std::memcpy(ms.pData, vertices, sizeof(vertices));
    // devcon->Unmap(pVBuffer, 0);

    return true;
}

bool GraphicsEngine::Release() {
    swapchain->SetFullscreenState(FALSE, nullptr);

    swapchain->Release();
    dev->Release();
    devcon->Release();
    backbuffer->Release();
    pVBuffer->Release();
    pIBuffer->Release();
    pCBuffer->Release();
    pLayout->Release();

    return true;
}

bool GraphicsEngine::CreateVertexBuffer(void *list_vertices, UINT size_vertex, UINT size_list) {
    if (pVBuffer)
        pVBuffer->Release();
    if (pLayout)
        pLayout->Release();
    
    D3D11_BUFFER_DESC buff_desc = {};
    buff_desc.Usage = D3D11_USAGE_DEFAULT;
    buff_desc.ByteWidth = size_vertex * size_list;
    buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buff_desc.CPUAccessFlags = 0;
    buff_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_vertices;

    vertexSize = size_vertex;
    vBufferSize = size_list;

    if (FAILED(dev->CreateBuffer(&buff_desc, &init_data, &pVBuffer)))
        return false;
    
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT size_layout = ARRAYSIZE(layout);

    HRESULT hr;
    if (FAILED(hr = dev->CreateInputLayout(layout, size_layout, blob->GetBufferPointer(), blob->GetBufferSize(), &pLayout))) {
        std::cout << hr << std::endl;
        return false;
    }

    return true;
}

bool GraphicsEngine::CreateIndexBuffer(void *list_indices, UINT size_list) {
    if (pIBuffer)
        pIBuffer->Release();
    
    D3D11_BUFFER_DESC buff_desc = {};
    buff_desc.Usage = D3D11_USAGE_DEFAULT;
    buff_desc.ByteWidth = 4 * size_list;
    buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buff_desc.CPUAccessFlags = 0;
    buff_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_indices;

    iBufferSize = size_list;

    if (FAILED(dev->CreateBuffer(&buff_desc, &init_data, &pIBuffer)))
        return false;

    return true;
}

bool GraphicsEngine::CreateConstantBuffer(void *buffer, UINT size_buffer) {
    if (pCBuffer)
        pCBuffer->Release();
    
    D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

    if (FAILED(dev->CreateBuffer(&buff_desc, &init_data, &pCBuffer)))
        return false;

    return true;
}

void GraphicsEngine::UpdateConstantBuffer(void *buffer) {
    devcon->UpdateSubresource(pCBuffer, 0, nullptr, buffer, 0, 0);
}

bool GraphicsEngine::Present(bool vsync) {
    swapchain->Present(vsync, 0);

    return true;
}

bool GraphicsEngine::CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name) {
    ID3DBlob* error_blob = nullptr;
    if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, target_name, 0, 0, &blob, &error_blob))) {
        if (error_blob) {
            char *s = (char *)error_blob->GetBufferPointer();
            std::cout << s << std::endl;
            error_blob->Release();
        }
        return false;
    }

    return true;
}

ID3D11VertexShader *GraphicsEngine::CreateVertexShader() {
    ID3D11VertexShader *vs;

    if (FAILED(dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs)))
        return nullptr;

    return vs;
}

ID3D11PixelShader *GraphicsEngine::CreatePixelShader() {
    ID3D11PixelShader *vs;

    if (FAILED(dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs)))
        return nullptr;

    return vs;
}

void GraphicsEngine::ReleaseBlob() {
    if (blob)
        blob->Release();
}

void GraphicsEngine::ClearRenderTargetColor(float red, float green, float blue, float alpha) {
    FLOAT clear_color[] = {red, green, blue, alpha};
    devcon->ClearRenderTargetView(backbuffer, clear_color);
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);
}

void GraphicsEngine::SetVertexBuffer() {
    UINT stride = vertexSize;
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
    devcon->IASetInputLayout(pLayout);
}

void GraphicsEngine::SetIndexBuffer() {
    devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void GraphicsEngine::DrawTriangleList() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->Draw(vBufferSize, 0);
}

void GraphicsEngine::DrawIndexedTriangleList() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->DrawIndexed(iBufferSize, 0, 0);
}

void GraphicsEngine::DrawTriangleStrip() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    devcon->Draw(vBufferSize, 0);
}

void GraphicsEngine::SetViewportSize(UINT width, UINT height) {
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    devcon->RSSetViewports(1, &vp);
}

void GraphicsEngine::SetVertexShader(ID3D11VertexShader* vertex_shader) {
    devcon->VSSetShader(vertex_shader, nullptr, 0);
}

void GraphicsEngine::SetPixelShader(ID3D11PixelShader* pixel_shader) {
    devcon->PSSetShader(pixel_shader, nullptr, 0);
}

void GraphicsEngine::SetConstantBuffer(ID3D11VertexShader* vertex_shader) {
    devcon->VSSetConstantBuffers(0, 1, &pCBuffer);
}

void GraphicsEngine::SetConstantBuffer(ID3D11PixelShader* pixel_shader) {
    devcon->PSSetConstantBuffers(0, 1, &pCBuffer);
}

// bool GraphicsEngine::InitDeviceAndSwapChain(HWND hWnd, UINT width, UINT height) {
//     DXGI_SWAP_CHAIN_DESC desc;
//     ZeroMemory(&desc, sizeof(desc));
//     desc.BufferCount = 1;
//     desc.BufferDesc.Width = width;
//     desc.BufferDesc.Height = height;
//     desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//     desc.BufferDesc.RefreshRate.Numerator = 60;
//     desc.BufferDesc.RefreshRate.Denominator = 1;
//     desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//     desc.OutputWindow = hWnd;
//     desc.SampleDesc.Count = 1;
//     desc.SampleDesc.Quality = 0;
//     desc.Windowed = TRUE;

//     // HRESULT hr = dxgiFactory->CreateSwapChain(dev, &desc, &swapchain);

//     HRESULT hr = D3D11CreateDeviceAndSwapChain(
//         nullptr, 
//         D3D_DRIVER_TYPE_HARDWARE, 
//         nullptr, 
//         0,
//         nullptr,
//         0,
//         D3D11_SDK_VERSION,
//         &desc,
//         &swapchain,
//         &dev,
//         nullptr,
//         &devcon
//     );

//     if (FAILED(hr))
//         return false;

//     ID3D11Texture2D *pBackBuffer = nullptr;
//     hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);

//     if (FAILED(hr))
//         return false;

//     dev->CreateRenderTargetView(pBackBuffer, nullptr, &backbuffer);
//     pBackBuffer->Release();

//     if (FAILED(hr))
//         return false;

//     return true;
// }