#include "graphics/directx11.h"

#include <d3dcompiler.h>
#include <stdexcept>
#include "elementary/math.h"

RenderSystem::RenderSystem() {
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





    
    // scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
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

    

    // return true;

    // devcon->OMSetRenderTargets(1, &backbuffer, nullptr);

    // D3D11_VIEWPORT viewport;

    // ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    // viewport.TopLeftX = 0;
    // viewport.TopLeftY = 0;
    // viewport.Width = width;
    // viewport.Height = height;

    // devcon->RSSetViewports(1, &viewport);

    // // Pipeline
    // // ID3D10Blob *VS, *PS;
    // // D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "VShader", "vs_5_0", 0, 0, &VS, nullptr);
    // // D3DCompileFromFile(L"shaders.shader", nullptr, nullptr, "PShader", "ps_5_0", 0, 0, &PS, nullptr);

    // // dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVS);
    // // dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPS);

    // // devcon->VSSetShader(pVS, 0, 0);
    // // devcon->PSSetShader(pPS, 0, 0);

    // // D3D11_INPUT_ELEMENT_DESC ied[] = {
    // //     {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    // //     {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    // // };

    // // dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    // // devcon->IASetInputLayout(pLayout);

    // // // Graphics
    // // VERTEX vertices[] = {
    // //     {{ 0.00f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    // //     {{ 0.45f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
    // //     {{-0.45f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
    // // };

    // // D3D11_BUFFER_DESC bd;
    // // ZeroMemory(&bd, sizeof(bd));

    // // bd.Usage = D3D11_USAGE_DYNAMIC;
    // // bd.ByteWidth = sizeof(VERTEX) * 3;
    // // bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    // // bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // // dev->CreateBuffer(&bd, nullptr, &pVBuffer);

    // // D3D11_MAPPED_SUBRESOURCE ms;
    // // devcon->Map(pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    // // std::memcpy(ms.pData, vertices, sizeof(vertices));
    // // devcon->Unmap(pVBuffer, 0);

    // return true;
}

RenderSystem::~RenderSystem() {
    swapchain->SetFullscreenState(FALSE, nullptr);

    swapchain->Release();
    dev->Release();
    devcon->Release();
    backbuffer->Release();
    pVBuffer->Release();
    pIBuffer->Release();
    pCBuffer->Release();
    pLayout->Release();
}

void RenderSystem::CreateDeviceAndSwapChain(HWND hWnd, int width, int height) {
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = TRUE;

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
}

void RenderSystem::CreateVertexBuffer(void *list_vertices, UINT size_vertex, UINT size_list) {
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
        throw std::runtime_error("Failed to create vertex buffer");
    
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT size_layout = ARRAYSIZE(layout);

    HRESULT hr;
    if (FAILED(hr = dev->CreateInputLayout(layout, size_layout, blob->GetBufferPointer(), blob->GetBufferSize(), &pLayout)))
        throw std::runtime_error("Failed to create input layout");
}

void RenderSystem::CreateIndexBuffer(void *list_indices, UINT size_list) {
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
        throw std::runtime_error("Failed to create index buffer");
}

void RenderSystem::CreateConstantBuffer(void *buffer, UINT size_buffer) {
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
        throw std::runtime_error("Failed to create constant buffer");
}

void RenderSystem::UpdateConstantBuffer(void *buffer) {
    devcon->UpdateSubresource(pCBuffer, 0, nullptr, buffer, 0, 0);
}

void RenderSystem::Present(bool vsync) {
    swapchain->Present(vsync, 0);
}

void RenderSystem::CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name) {
    ID3DBlob* error_blob = nullptr;
    if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, target_name, 0, 0, &blob, &error_blob))) {
        if (error_blob) {
            char *s = (char *)error_blob->GetBufferPointer();
            throw std::runtime_error(s);
            error_blob->Release();
        }
        else
            throw std::runtime_error("Error occurred when compiling shaders");
    }
}

ID3D11VertexShader *RenderSystem::CreateVertexShader() {
    ID3D11VertexShader *vs;

    if (FAILED(dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs)))
        throw std::runtime_error("Failed to create vertex shader");

    return vs;
}

ID3D11PixelShader *RenderSystem::CreatePixelShader() {
    ID3D11PixelShader *vs;

    if (FAILED(dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs)))
        throw std::runtime_error("Failed to create pixel shader");

    return vs;
}

void RenderSystem::ReleaseBlob() {
    if (blob)
        blob->Release();
}

void RenderSystem::ClearRenderTargetColor(float red, float green, float blue, float alpha) {
    FLOAT clear_color[] = {red, green, blue, alpha};
    devcon->ClearRenderTargetView(backbuffer, clear_color);
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);
}

void RenderSystem::SetVertexBuffer() {
    UINT stride = vertexSize;
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
    devcon->IASetInputLayout(pLayout);
}

void RenderSystem::SetIndexBuffer() {
    devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void RenderSystem::DrawTriangleList() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->Draw(vBufferSize, 0);
}

void RenderSystem::DrawIndexedTriangleList() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->DrawIndexed(iBufferSize, 0, 0);
}

void RenderSystem::DrawTriangleStrip() {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    devcon->Draw(vBufferSize, 0);
}

void RenderSystem::SetViewportSize(UINT width, UINT height) {
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    devcon->RSSetViewports(1, &vp);
}

void RenderSystem::SetVertexShader(ID3D11VertexShader* vertex_shader) {
    devcon->VSSetShader(vertex_shader, nullptr, 0);
}

void RenderSystem::SetPixelShader(ID3D11PixelShader* pixel_shader) {
    devcon->PSSetShader(pixel_shader, nullptr, 0);
}

void RenderSystem::SetConstantBuffer(ID3D11VertexShader* vertex_shader) {
    devcon->VSSetConstantBuffers(0, 1, &pCBuffer);
}

void RenderSystem::SetConstantBuffer(ID3D11PixelShader* pixel_shader) {
    devcon->PSSetConstantBuffers(0, 1, &pCBuffer);
}

// bool RenderSystem::InitDeviceAndSwapChain(HWND hWnd, UINT width, UINT height) {
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