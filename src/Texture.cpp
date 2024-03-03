#include "data/textures.h"

#include <DirectXTex.h>
#include <stdexcept>

Texture::Texture(const wchar_t *full_path) : Resource(full_path) {
    DirectX::ScratchImage image_data;
    HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

    if (SUCCEEDED(res))
        res = DirectX::CreateTexture(GraphicsEngine::Get()->GetRenderSystem()->dev, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &texture);
    else
        throw std::runtime_error("Textures were not created successfully");

    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = image_data.GetMetadata().format;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
    desc.Texture2D.MostDetailedMip = 0;

    GraphicsEngine::Get()->GetRenderSystem()->dev->CreateShaderResourceView(texture, &desc, &shader_resource_view);
}

Texture::~Texture() {
    texture->Release();
}