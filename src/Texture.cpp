#include "data/textures.h"

#include <DirectXTex.h>
#include <stdexcept>

Texture::Texture(const wchar_t *full_path) : Resource(full_path) {
    DirectX::ScratchImage image_data;
    HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

    if (SUCCEEDED(res))
        res = DirectX::CreateTexture(GraphicsEngine::Get()->GetRenderSystem()->dev, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &texture);
    else
        throw std::runtime_error("Textures were not created successfully");

    if (FAILED(res))
        throw std::runtime_error("Textures were not created successfully");

    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = image_data.GetMetadata().format;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
    desc.Texture2D.MostDetailedMip = 0;

    D3D11_SAMPLER_DESC sampler_desc = {};
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = image_data.GetMetadata().mipLevels;

    res = GraphicsEngine::Get()->GetRenderSystem()->dev->CreateSamplerState(&sampler_desc, &sampler_state);
    
    if (FAILED(res))
        throw std::runtime_error("Textures were not created successfully");

    res = GraphicsEngine::Get()->GetRenderSystem()->dev->CreateShaderResourceView(texture, &desc, &shader_resource_view);

    if (FAILED(res))
        throw std::runtime_error("Textures were not created successfully");
}

Texture::~Texture() {
    texture->Release();
}