#include "data/elements.h"

#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <list>
#include <memory>
#include "graphics/components/shaders.h"
#include "data/textures.h"

#include <iostream>

void ElementManager::Create() {
    tex_manager = new TextureManager();
    mesh_manager = new MeshManager();
}

void ElementManager::Release() {
    delete mesh_manager;
    delete tex_manager;
}

ElementManager::ElementManager(const wchar_t *file_path) {
    std::wstring full_path = std::filesystem::absolute(file_path);

    std::wifstream file(full_path.c_str());

    int category = -1;
    // 0 - textures
    // 1 - meshes
    // 2 - shaders
    // 3 - materials 
    // 4 - objects

    while(file) {
        std::wstring line;
        std::getline(file, line);
        std::wstringstream ss(line);

        if (!ss)
            continue;

        std::wstring cmd;
        ss >> cmd;

        if (cmd.compare(L".textures") == 0)
            category = 0;
        else if (cmd.compare(L".meshes") == 0)
            category = 1;
        else if (cmd.compare(L".shaders") == 0)
            category = 2;
        else if (cmd.compare(L".materials") == 0)
            category = 3;
        else if (cmd.compare(L".objects") == 0)
            category = 4;
        else {
            std::wstring arg;
            switch (category) {
            case 0:
                if (ss) {
                    ss >> arg;
                    textures[cmd] = tex_manager->CreateTextureFromFile(arg.c_str());
                }
                break;
            case 1:
                if (ss) {
                    ss >> arg;
                    meshes[cmd] = mesh_manager->CreateMeshFromFile(arg.c_str());
                }
                break;
            case 2:
                if (ss) {
                    ss >> arg;
                    shaders[cmd] = arg;
                }
                break;
            case 4:
                if (!ss)
                    break;

                UINT flags = ELEMENTS_FLAGS_NONE;
                std::wstring m;
                std::wstring ps;
                std::wstring vs;
                std::list<std::wstring> t;

                int state = -1;
                //-1 - none
                // 0 - mesh
                // 1 - pixel shader
                // 2 - vertex shader
                // 3 - textures
                while (ss) {
                    switch (state) {
                    case 0:
                        ss >> m;
                        state = -1;
                        break;
                    case 1:
                        ss >> ps;
                        state = -1;
                        break;
                    case 2:
                        ss >> vs;
                        state = -1;
                        break;
                    case 3:
                        ss >> arg;
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
                            t.push_back(arg);
                        break;
                    default:
                        ss >> arg;
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
                        break;
                    }
                }

                if ((flags & ELEMENTS_FLAGS_SKYBOX) == 0)
                    flags |= ELEMENTS_FLAGS_NOT_SKYBOX;
                if ((flags & ELEMENTS_FLAGS_CULL_FRONT) == 0)
                    flags |= ELEMENTS_FLAGS_CULL_BACK;

                // std::cout << flags << std::endl;

                void *shader_byte_code = nullptr;
                size_t shader_byte_size = 0;
                std::wcout << ps << std::endl;
                std::wcout << shaders[ps] << std::endl;
                std::wcout << vs << std::endl;
                std::wcout << shaders[vs] << std::endl;

                GraphicsEngine::Get()->GetRenderSystem()->CompileShader(shaders[ps].c_str(), "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
                std::shared_ptr<PixelShader> pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
                GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

                GraphicsEngine::Get()->GetRenderSystem()->CompileShader(shaders[vs].c_str(), "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
                std::shared_ptr<VertexShader> vertex_shader = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, shader_byte_size);
                GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

                UINT texture_count = t.size();
                std::shared_ptr<Texture> *texs = new std::shared_ptr<Texture>[texture_count];
                auto iter = t.begin();
                for (UINT i = 0; i < texture_count && iter != t.end(); i++, iter++)
                    texs[i] = textures[*iter];

                elements[cmd] = std::make_shared<Element>(
                    flags, 
                    meshes[m],
                    pixel_shader,
                    vertex_shader,
                    texs,
                    texture_count
                );
                break;
            }
        }
    }
}

ElementManager::~ElementManager() {}

void ElementManager::Draw(UINT flags) {
    for (auto& it : elements) {
        auto e = it.second.get();
        if ((e->flags & flags) == e->flags)
            e->Draw();
    }
}

void ElementManager::UpdateConstantBuffer(const constant *cc, UINT flags) {
    for (auto& it : elements) {
        auto e = it.second.get();
        if ((e->flags & flags) == e->flags)
            e->UpdateConstantBuffer(cc);
    }
}

TextureManager *ElementManager::tex_manager = nullptr;
MeshManager *ElementManager::mesh_manager = nullptr;