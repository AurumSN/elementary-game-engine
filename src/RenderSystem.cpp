#include "graphics/directx11.h"

#include <d3dcompiler.h>
#include <stdexcept>
#include "graphics/components/buffers.h"
#include "graphics/components/shaders.h"

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {
    swapchain->SetFullscreenState(FALSE, nullptr);

    swapchain->Release();
    dev->Release();
    devcon->Release();
    backbuffer->Release();
}

void RenderSystem::CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height) {
    DXGI_SWAP_CHAIN_DESC scd = {};

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

std::shared_ptr<VertexBuffer> RenderSystem::CreateVertexBuffer(const void *vertex_list, UINT vertex_size, UINT list_size, const void *shader_byte_code, size_t shader_byte_size) {
    return std::make_shared<VertexBuffer>(vertex_list, vertex_size, list_size, shader_byte_code, shader_byte_size, this);
}

std::shared_ptr<IndexBuffer> RenderSystem::CreateIndexBuffer(const void *index_list, UINT list_size) {
    return std::make_shared<IndexBuffer>(index_list, list_size, this);
}

std::shared_ptr<ConstantBuffer> RenderSystem::CreateConstantBuffer(const void *buffer, UINT buffer_size) {
    return std::make_shared<ConstantBuffer>(buffer, buffer_size, this);
}

void RenderSystem::Present(bool vsync) {
    swapchain->Present(vsync, 0);
}

void RenderSystem::CompileShader(const wchar_t *file_name, const char *entry_point_name, const char *target_name, void** shader_byte_code, size_t* shader_byte_size) {
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

    *shader_byte_code = blob->GetBufferPointer();
    *shader_byte_size = blob->GetBufferSize();
}

std::shared_ptr<VertexShader> RenderSystem::CreateVertexShader(const void *shader_byte_code, size_t shader_byte_size) {
    return std::make_shared<VertexShader>(shader_byte_code, shader_byte_size, this);
}

std::shared_ptr<PixelShader> RenderSystem::CreatePixelShader(const void *shader_byte_code, size_t shader_byte_size) {
    return std::make_shared<PixelShader>(shader_byte_code, shader_byte_size, this);
}

void RenderSystem::ReleaseCompiledShader() {
    if (blob)
        blob->Release();
}

void RenderSystem::ClearRenderTargetColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) {
    FLOAT clear_color[] = {red, green, blue, alpha};
    devcon->ClearRenderTargetView(backbuffer, clear_color);
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);
}

void RenderSystem::SetVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) {
    UINT stride = vertex_buffer->vertex_size;
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &vertex_buffer->buffer, &stride, &offset);
    devcon->IASetInputLayout(vertex_buffer->layout);
}

void RenderSystem::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) {
    devcon->IASetIndexBuffer(index_buffer->buffer, DXGI_FORMAT_R32_UINT, 0);
}

void RenderSystem::DrawTriangleList(UINT vertex_count, UINT start_vertex_index) {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->Draw(vertex_count, start_vertex_index);
}

void RenderSystem::DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location) {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void RenderSystem::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index) {
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    devcon->Draw(vertex_count, start_vertex_index);
}

void RenderSystem::SetViewportSize(UINT width, UINT height) {
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    devcon->RSSetViewports(1, &vp);
}

void RenderSystem::SetVertexShader(const std::shared_ptr<VertexShader> &vertex_shader) {
    devcon->VSSetShader(vertex_shader->shader, nullptr, 0);
}

void RenderSystem::SetPixelShader(const std::shared_ptr<PixelShader> &pixel_shader) {
    devcon->PSSetShader(pixel_shader->shader, nullptr, 0);
}

void RenderSystem::SetConstantBuffer(const std::shared_ptr<VertexShader> &vertex_shader, const std::shared_ptr<ConstantBuffer> &buffer) {
    devcon->VSSetConstantBuffers(0, 1, &buffer->buffer);
}

void RenderSystem::SetConstantBuffer(const std::shared_ptr<PixelShader> &pixel_shader, const std::shared_ptr<ConstantBuffer> &buffer) {
    devcon->PSSetConstantBuffers(0, 1, &buffer->buffer);
}

void RenderSystem::SetTexture(const std::shared_ptr<VertexShader> &vertex_shader, const std::shared_ptr<Texture> &texture) {
    devcon->VSSetShaderResources(0, 1, &texture->shader_resource_view);
}

void RenderSystem::SetTexture(const std::shared_ptr<PixelShader> &pixel_shader, const std::shared_ptr<Texture> &texture) {
    devcon->PSSetShaderResources(0, 1, &texture->shader_resource_view);
}