#include "data/elements.h"

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <memory>
#include <stdexcept>
#include <unordered_set>

#include <iostream>

void Element::Load(const wchar_t *file_path) {
    GraphicsEngine::Get()->GetElementManager()->CreateElementFromFile(file_path);
    element_count = global_elements.size();
    element_list = new std::shared_ptr<Element>[element_count];
    auto iter = global_elements.begin();
    for (UINT i = 0; i < element_count; i++, iter++)
        element_list[i] = (*iter).second;

    global_textures.clear();
    global_meshes.clear();
    global_pixel_shaders.clear();
    global_vertex_shaders.clear();
    global_elements.clear();
}

void Element::Draw(UINT flags) {
    for (UINT i = 0; i < element_count; i++)
        if ((element_list[i]->flags & flags) == element_list[i]->flags)
            element_list[i]->Draw();
}

void Element::UpdateConstantBuffer(const constant *cc, UINT flags) {
    for (UINT i = 0; i < element_count; i++)
        if ((element_list[i]->flags & flags) == element_list[i]->flags)
            element_list[i]->UpdateConstantBuffer(cc);
}

Element::Element(const wchar_t *full_path) : Resource(full_path) {
    std::unordered_map<std::wstring, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::wstring, std::shared_ptr<Mesh>> meshes;
    std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> pixel_shaders;
    std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> vertex_shaders;
    std::unordered_map<std::wstring, std::shared_ptr<Element>> elements;
    std::unordered_set<std::wstring> is_global;

    std::wifstream file(full_path);

    while(file) {
        std::wstring line;
        std::getline(file, line);
        std::wstringstream ss(line);

        if (!ss)
            continue;

        std::wstring cmd;
        ss >> cmd;

        if (cmd[0] == L'.')
            continue;

        if (cmd.compare(L"load") == 0) {
            int state = -1;
            //-1 - name
            // 0 - tex
            // 1 - mesh
            // 2 - ps
            // 3 - vs
            // 4 - element
            std::wstring name;
            void *shader_byte_code = nullptr;
            size_t shader_byte_size = 0;
            std::wstring arg;
            std::shared_ptr<Texture> t;
            std::shared_ptr<Mesh> m;
            std::shared_ptr<PixelShader> ps;
            std::shared_ptr<VertexShader> vs;
            std::shared_ptr<Element> e;
            while (ss) {
                ss >> arg;
                switch (state) {
                case 0:
                    t = GraphicsEngine::Get()->GetTexManager()->CreateTextureFromFile(arg.c_str());
                    if (name.compare(L"")) {
                        textures[name] = t;
                        if (is_global.contains(name))
                            global_textures[name] = t;
                    }
                    break;
                case 1:
                    m = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(arg.c_str());
                    if (name.compare(L"")) {
                        meshes[name] = m;
                        if (is_global.contains(name))
                            global_meshes[name] = m;
                    }
                    break;
                case 2:
                    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(arg.c_str(), "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
                    ps = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
                    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();
                    if (name.compare(L"")) {
                        pixel_shaders[name] = ps;
                        if (is_global.contains(name))
                            global_pixel_shaders[name] = ps;
                    }
                    break;
                case 3:
                    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(arg.c_str(), "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
                    vs = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, shader_byte_size);
                    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();
                    if (name.compare(L"")) {
                        vertex_shaders[name] = vs;
                        if (is_global.contains(name))
                            global_vertex_shaders[name] = vs;
                    }
                    break;
                case 4:
                    e = GraphicsEngine::Get()->GetElementManager()->CreateElementFromFile(arg.c_str());
                    if (name.compare(L"")) {
                        elements[name] = e;
                        if (is_global.contains(name))
                            global_elements[name] = e;
                    }
                    break;
                default:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else {
                        name = arg;
                        state = -1;
                    }
                }
            }
        }
        else if (cmd.compare(L"global") == 0) {
            int state = -1;
            //-1 - none
            // 0 - tex
            // 1 - mesh
            // 2 - ps
            // 3 - vs
            // 4 - element
            std::wstring arg;
            while (ss) {
                ss >> arg;
                is_global.insert(arg);
            }
        }
        else if (cmd.compare(L"extern") == 0) {
            int state = -1;
            //-1 - none
            // 0 - tex
            // 1 - mesh
            // 2 - ps
            // 3 - vs
            // 4 - element
            std::wstring arg;
            while (ss) {
                ss >> arg;
                switch (state) {
                case 0:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else
                        textures[arg] = global_textures[arg];
                    break;
                case 1:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else
                        meshes[arg] = global_meshes[arg];
                    break;
                case 2:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else
                        pixel_shaders[arg] = global_pixel_shaders[arg];
                    break;
                case 3:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else
                        vertex_shaders[arg] = global_vertex_shaders[arg];
                    break;
                case 4:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                    else
                        elements[arg] = global_elements[arg];
                    break;
                default:
                    if (arg.compare(L"-t") == 0)
                        state = 0;
                    else if (arg.compare(L"-m") == 0)
                        state = 1;
                    else if (arg.compare(L"-ps") == 0)
                        state = 2;
                    else if (arg.compare(L"-vs") == 0)
                        state = 3;
                    else if (arg.compare(L"-e") == 0)
                        state = 4;
                }
            }
        }
        else if (cmd.compare(L"mesh") == 0) {
            flags = ELEMENTS_FLAGS_DEFAULT;
            std::list<std::shared_ptr<Texture>> t;

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
                    mesh = meshes[arg];
                    state = -1;
                    break;
                case 1:
                    pixel_shader = pixel_shaders[arg];
                    state = -1;
                    break;
                case 2:
                    vertex_shader = vertex_shaders[arg];
                    state = -1;
                    break;
                case 3:
                    if (arg.compare(L"-sb") == 0) {
                        flags |= ELEMENTS_FLAGS_SKYBOX;
                        flags &= ~ELEMENTS_FLAGS_NOT_SKYBOX;
                        state = -1;
                    }
                    else if (arg.compare(L"-nsb") == 0) {
                        flags |= ELEMENTS_FLAGS_NOT_SKYBOX;
                        flags &= ~ELEMENTS_FLAGS_SKYBOX;
                        state = -1;
                    }
                    else if (arg.compare(L"-cf") == 0) {
                        flags |= ELEMENTS_FLAGS_CULL_FRONT;
                        flags &= ~ELEMENTS_FLAGS_CULL_BACK;
                        state = -1;
                    }
                    else if (arg.compare(L"-cb") == 0) {
                        flags |= ELEMENTS_FLAGS_CULL_BACK;
                        flags &= ~ELEMENTS_FLAGS_CULL_FRONT;
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
                        t.push_back(textures[arg]);
                    break;
                default:
                    if (arg.compare(L"-sb") == 0) {
                        flags |= ELEMENTS_FLAGS_SKYBOX;
                        flags &= ~ELEMENTS_FLAGS_NOT_SKYBOX;
                        state = -1;
                    }
                    else if (arg.compare(L"-nsb") == 0) {
                        flags |= ELEMENTS_FLAGS_NOT_SKYBOX;
                        flags &= ~ELEMENTS_FLAGS_SKYBOX;
                        state = -1;
                    }
                    else if (arg.compare(L"-cf") == 0) {
                        flags |= ELEMENTS_FLAGS_CULL_FRONT;
                        flags &= ~ELEMENTS_FLAGS_CULL_BACK;
                        state = -1;
                    }
                    else if (arg.compare(L"-cb") == 0) {
                        flags |= ELEMENTS_FLAGS_CULL_BACK;
                        flags &= ~ELEMENTS_FLAGS_CULL_FRONT;
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
            this->textures = new std::shared_ptr<Texture>[texture_count];
            auto iter = t.begin();
            for (UINT i = 0; i < texture_count && iter != t.end(); i++, iter++)
                this->textures[i] = *iter;

            constant cc;
            constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
        }
        // else if (cmd.compare(L"set") == 0) {
        //     std::wstring arg;
        //     std::wstring name;
        //     int state = -1;
        //     //-1 - none
        //     // 0 - element
        //     while (ss) {
        //         ss >> arg;
        //         switch (state) {
        //         case 0:
        //             if (arg.compare(L"this") == 0) {
        //                 if (name.compare(L"")) {
        //                     elements[name] = std::shared_ptr<Element>(this);//shared_from_this();
        //                     if (is_global.contains(name))
        //                         global_elements[name] = std::shared_ptr<Element>(this);//shared_from_this();
        //                 }
        //                 state = -1;
        //             }
        //             else if (arg.compare(L"-e") == 0)
        //                 state = 0;
        //             else {
        //                 name = arg;
        //                 state = -1;
        //             }
        //             break;
        //         default:
        //             if (arg.compare(L"-e") == 0)
        //                 state = 0;
        //             else {
        //                 name = arg;
        //                 state = -1;
        //             }
        //         }
        //     }
        // }
    }
}

Element::~Element() {}

void Element::Draw() {
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

std::unordered_map<std::wstring, std::shared_ptr<Texture>> Element::global_textures;
std::unordered_map<std::wstring, std::shared_ptr<Mesh>> Element::global_meshes;
std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> Element::global_pixel_shaders;
std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> Element::global_vertex_shaders;
std::unordered_map<std::wstring, std::shared_ptr<Element>> Element::global_elements;

std::shared_ptr<Element> *Element::element_list = nullptr;
UINT Element::element_count = 0;