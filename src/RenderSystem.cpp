#include "graphics/directx11.h"

#include <d3dcompiler.h>
#include <stdexcept>
#include "graphics/components/buffers.h"
#include "graphics/components/shaders.h"
#include "data/textures.h"

RenderSystem::RenderSystem() {
    D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(nullptr, driver_types[driver_type_index], nullptr, 0, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &dev, &feature_level, &devcon);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
		throw std::runtime_error("Render System was not created successfully");

	dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device);
	dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter);
	dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory);

    InitRasterizerState();
}

RenderSystem::~RenderSystem() {
    swapchain->SetFullscreenState(FALSE, nullptr);

    swapchain->Release();
    dev->Release();
    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();
    devcon->Release();
    backbuffer->Release();
    depth_stencil_view->Release();
}

void RenderSystem::CreateSwapChain(HWND hWnd, UINT width, UINT height) {
    DXGI_SWAP_CHAIN_DESC desc = {};

    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hWnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    desc.Windowed = TRUE;

    HRESULT hr = dxgi_factory->CreateSwapChain(dev, &desc, &swapchain);

    if (FAILED(hr))
        throw std::runtime_error("Swap Chain was not created successfully");

    ReloadBuffers(width, height);
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

void RenderSystem::SetRasterizerState(bool cull_front) {
    if (cull_front)
        devcon->RSSetState(cull_front_state);
    else
        devcon->RSSetState(cull_back_state);
}


void RenderSystem::SetFullScreen(bool fullscreen, UINT width, UINT height) {
    Resize(width, height);
    swapchain->SetFullscreenState(fullscreen, nullptr);
}

void RenderSystem::Resize(UINT width, UINT height) {
    if (backbuffer)
        backbuffer->Release();
    if (depth_stencil_view)
        depth_stencil_view->Release();

    swapchain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ReloadBuffers(width, height);
}

void RenderSystem::Present(bool vsync) {
    swapchain->Present(vsync, 0);
}

void RenderSystem::ClearRenderTargetColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) {
    FLOAT clear_color[] = {red, green, blue, alpha};
    devcon->ClearRenderTargetView(backbuffer, clear_color);
    devcon->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    devcon->OMSetRenderTargets(1, &backbuffer, depth_stencil_view);
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

void RenderSystem::InitRasterizerState() {
    D3D11_RASTERIZER_DESC desc = {};
    desc.CullMode = D3D11_CULL_FRONT;
    desc.DepthClipEnable = true;
    desc.FillMode = D3D11_FILL_SOLID;

    dev->CreateRasterizerState(&desc, &cull_front_state);

    desc.CullMode = D3D11_CULL_BACK;

    dev->CreateRasterizerState(&desc, &cull_back_state);
}

void RenderSystem::ReloadBuffers(UINT width, UINT height) {
    if (width == 0 || height == 0)
        return;

    ID3D11Texture2D *buffer = nullptr;
    HRESULT hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&buffer);

    if (FAILED(hr))
        throw std::runtime_error("Swap Chain was not created successfully");

    hr = dev->CreateRenderTargetView(buffer, nullptr, &backbuffer);
    buffer->Release();

    if (FAILED(hr))
        throw std::runtime_error("Swap Chain was not created successfully");

    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = width;
    tex_desc.Height = height;
    tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    hr = dev->CreateTexture2D(&tex_desc, nullptr, &buffer);
    
    if (FAILED(hr))
        throw std::runtime_error("Swap Chain was not created successfully");

    hr = dev->CreateDepthStencilView(buffer, nullptr, &depth_stencil_view);
    buffer->Release();

    if (FAILED(hr))
        throw std::runtime_error("Swap Chain was not created successfully");
}