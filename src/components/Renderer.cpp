#include "elementary/component.h"

#include <list>
#include "elementary/time.h"

void Renderer::Load(std::wstring arguments, ElementData &data,  Element *base) {
    flags = RENDERER_FLAGS_DEFAULT;
    std::list<std::shared_ptr<Texture>> t;
    std::wstringstream ss(arguments);

    std::wstring arg;
    int state = -1;
    //-1 - none
    // 0 - mesh
    // 1 - pixel shader
    // 2 - vertex shader
    // 3 - textures
    while (ss) {
        ss >> arg;
        switch (state) {
        case 0:
            mesh = data.meshes[arg];
            state = -1;
            break;
        case 1:
            pixel_shader = data.pixel_shaders[arg];
            state = -1;
            break;
         case 2:
            vertex_shader = data.vertex_shaders[arg];
            state = -1;
            break;
        case 3:
            if (arg.compare(L"-cf") == 0) {
                flags |= RENDERER_FLAGS_CULL_FRONT;
                flags &= ~RENDERER_FLAGS_CULL_BACK;
                state = -1;
            }
            else if (arg.compare(L"-cb") == 0) {
                flags |= RENDERER_FLAGS_CULL_BACK;
                flags &= ~RENDERER_FLAGS_CULL_FRONT;
                state = -1;
            }
            else if (arg.compare(L"-m") == 0)
                state = 0;
            else if (arg.compare(L"-ps") == 0)
                state = 1;
            else if (arg.compare(L"-vs") == 0)
                state = 2;
            else if (arg.compare(L"-t") == 0)
                state = 3;
            else
                t.push_back(data.textures[arg]);
            break;
        default:
            if (arg.compare(L"-cf") == 0) {
                flags |= RENDERER_FLAGS_CULL_FRONT;
                flags &= ~RENDERER_FLAGS_CULL_BACK;
                state = -1;
            }
            else if (arg.compare(L"-cb") == 0) {
                flags |= RENDERER_FLAGS_CULL_BACK;
                flags &= ~RENDERER_FLAGS_CULL_FRONT;
                state = -1;
            }
            else if (arg.compare(L"-m") == 0)
                state = 0;
            else if (arg.compare(L"-ps") == 0)
                state = 1;
            else if (arg.compare(L"-vs") == 0)
                state = 2;
            else if (arg.compare(L"-t") == 0)
                state = 3;
        }
    }

    texture_count = t.size();
    textures = new std::shared_ptr<Texture>[texture_count];
    auto iter = t.begin();
    for (UINT i = 0; i < texture_count && iter != t.end(); i++, iter++)
        textures[i] = *iter;

    constant cc;
    constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
}

void Renderer::Update() {
    constant cc;

    cc.world = _transform->GetModelMatrix();
    cc.view = Camera::GetViewMatrix();
    cc.proj = Camera::GetProjectionMatrix();
    cc.camera_position = Camera::GetCameraPosition();
    cc.light_direction = vec4::point(mat4x4::rotationY(0).getZDirection());
    cc.time = Time::GetTime();

    constant_buffer->Update(&cc);

    Render();
}

void Renderer::Render() {
    GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState((flags & RENDERER_FLAGS_CULL_FRONT) != 0 && (flags & RENDERER_FLAGS_CULL_BACK) == 0);

    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(vertex_shader, constant_buffer);
    GraphicsEngine::Get()->GetRenderSystem()->SetConstantBuffer(pixel_shader, constant_buffer);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexShader(vertex_shader);
    GraphicsEngine::Get()->GetRenderSystem()->SetPixelShader(pixel_shader);
    
    GraphicsEngine::Get()->GetRenderSystem()->SetTexture(pixel_shader, textures, texture_count);

    GraphicsEngine::Get()->GetRenderSystem()->SetVertexBuffer(mesh->GetVertexBuffer());
    GraphicsEngine::Get()->GetRenderSystem()->SetIndexBuffer(mesh->GetIndexBuffer());

    GraphicsEngine::Get()->GetRenderSystem()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
}

Renderer::Renderer( Element *base) : Component(base) {}
Renderer::~Renderer() {}