#include "data/elements.h"

#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <list>
#include "elementary/component.h"

std::unordered_map<std::wstring, std::shared_ptr<Component> (*)(Element *base)> Element::generators = {
    {L"transform", [](Element *base) { return std::static_pointer_cast<Component>(std::make_shared<Transform>(base)); }},
    {L"renderer",  [](Element *base) { return std::static_pointer_cast<Component>(std::make_shared<Renderer>(base));  }},
    {L"camera",    [](Element *base) { return std::static_pointer_cast<Component>(std::make_shared<Camera>(base));    }},
    {L"skybox",    [](Element *base) { return std::static_pointer_cast<Component>(std::make_shared<Skybox>(base));    }}
};

void Element::Load(const wchar_t *file_path) {
    GraphicsEngine::Get()->GetElementManager()->CreateElementFromFile(file_path);
    element_count = global.elements.size();
    element_list = new std::shared_ptr<Element>[element_count];
    auto iter = global.elements.begin();
    for (UINT i = 0; i < element_count; i++, iter++) {
        element_list[i] = (*iter).second;
        element_list[i]->Init();
    }
}

void Element::UpdateElements() {
    for (UINT i = 0; i < element_count; i++)
        element_list[i]->Update();
}

Element::Element(const wchar_t *full_path) : Resource(full_path) {
    ElementData data;
    std::unordered_set<std::wstring> is_global;

    std::list<std::pair<std::shared_ptr<Component>, std::wstring>> comps;

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
                        data.textures[name] = t;
                        if (is_global.contains(name))
                            global.textures[name] = t;
                    }
                    break;
                case 1:
                    m = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(arg.c_str());
                    if (name.compare(L"")) {
                        data.meshes[name] = m;
                        if (is_global.contains(name))
                            global.meshes[name] = m;
                    }
                    break;
                case 2:
                    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(arg.c_str(), "psmain", "ps_5_0", &shader_byte_code, &shader_byte_size);
                    ps = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, shader_byte_size);
                    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();
                    if (name.compare(L"")) {
                        data.pixel_shaders[name] = ps;
                        if (is_global.contains(name))
                            global.pixel_shaders[name] = ps;
                    }
                    break;
                case 3:
                    GraphicsEngine::Get()->GetRenderSystem()->CompileShader(arg.c_str(), "vsmain", "vs_5_0", &shader_byte_code, &shader_byte_size);
                    vs = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, shader_byte_size);
                    GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();
                    if (name.compare(L"")) {
                        data.vertex_shaders[name] = vs;
                        if (is_global.contains(name))
                            global.vertex_shaders[name] = vs;
                    }
                    break;
                case 4:
                    e = GraphicsEngine::Get()->GetElementManager()->CreateElementFromFile(arg.c_str());
                    if (name.compare(L"")) {
                        data.elements[name] = e;
                        if (is_global.contains(name))
                            global.elements[name] = e;
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
                        data.textures[arg] = global.textures[arg];
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
                        data.meshes[arg] = global.meshes[arg];
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
                        data.pixel_shaders[arg] = global.pixel_shaders[arg];
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
                        data.vertex_shaders[arg] = global.vertex_shaders[arg];
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
                        data.elements[arg] = global.elements[arg];
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
        else {
            auto gen = generators.find(cmd);

            if (gen == generators.end())
                continue;
            
            std::shared_ptr<Component> c = generators[cmd](this);
            if (cmd.compare(L"transform") == 0)
                transform = std::static_pointer_cast<Transform>(c);
            else if (cmd.compare(L"renderer") == 0)
                renderer = std::static_pointer_cast<Renderer>(c);
            std::wstringstream s;
            s << ss.rdbuf();
            comps.push_back(std::pair<std::shared_ptr<Component>, std::wstring>(c, s.str()));
        }
    }

    component_count = comps.size();
    auto iter = comps.begin();
    components = new std::shared_ptr<Component>[component_count];

    for (UINT i = 0; i < component_count; i++, iter++) {
        components[i] = (*iter).first;
        components[i]->Load((*iter).second, data, this);
    }
}

Element::~Element() {}

void Element::Init() {
    for (UINT i = 0; i < component_count; i++)
        components[i]->Init();
}

void Element::Update() {
    for (UINT i = 0; i < component_count; i++)
        components[i]->Update();
}

std::shared_ptr<Transform> Element::GetTransform() {
    return transform;
}

std::shared_ptr<Renderer> Element::GetRenderer() {
    return renderer;
}

std::shared_ptr<Component> *Element::GetComponents() {
    return components;
}

UINT Element::GetComponentCount() {
    return component_count;
}

std::shared_ptr<Component> Element::GetComponent(UINT id) {
    if (id >= component_count)
        return nullptr;

    return components[id];
}

ElementData Element::global;

std::shared_ptr<Element> *Element::element_list = nullptr;
UINT Element::element_count = 0;