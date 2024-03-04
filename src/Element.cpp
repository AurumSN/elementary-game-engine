#include "data/elements.h"

#include <iostream>

Element::Element(
    UINT flags,
    std::shared_ptr<Mesh> mesh, 
    std::shared_ptr<PixelShader> pixel_shader,
    std::shared_ptr<VertexShader> vertex_shader,
    std::shared_ptr<Texture> *textures,
    UINT texture_count
) : flags(flags), 
    mesh(mesh), 
    pixel_shader(pixel_shader), 
    vertex_shader(vertex_shader),
    textures(textures), 
    texture_count(texture_count) {
    constant cc;
    constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
}

Element::~Element() {}

void Element::Draw() {
    std::cout << flags << std::endl;
    GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState((flags & ELEMENTS_FLAGS_CULL_FRONT) != 0 && (flags & ELEMENTS_FLAGS_CULL_BACK) == 0);

    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(vertex_shader, constant_buffer);
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(pixel_shader, constant_buffer);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexShader(vertex_shader);
    GraphicsEngine::Get()->GetRenderSystem()->SetPixelShader(pixel_shader);
    
    GraphicsEngine::Get()->GetRenderSystem()->SetTexture(pixel_shader, textures, texture_count);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexBuffer(mesh->GetVertexBuffer());
    GraphicsEngine::Get()->GetRenderSystem()->SetIndexBuffer(mesh->GetIndexBuffer());

    GraphicsEngine::Get()->GetRenderSystem()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
}

void Element::UpdateConstantBuffer(const constant *cc) {
    constant_buffer->Update(cc);
}