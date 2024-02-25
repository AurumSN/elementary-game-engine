#include "data/meshes.h"

//#include <C:/msys64/mingw64/include/DirectXTex.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>
#include <stdexcept>
#include "graphics/directx11.h"
#include "elementary/math.h"

Mesh::Mesh(const wchar_t *full_path) : Resource(full_path) {
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn;
    std::string err;

    std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

    bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!err.empty() || !res || shapes.size() > 1)
        throw std::runtime_error("Mesh was not created successfully");
    
    std::vector<VERTEX> vertex_list;
    std::vector<unsigned int> index_list;

    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        vertex_list.reserve(shapes[s].mesh.indices.size());
        index_list.reserve(shapes[s].mesh.indices.size());

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            unsigned char num_face_vertices = shapes[s].mesh.num_face_vertices[f];

            for (unsigned char v = 0; v < num_face_vertices; v++) {
                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
                tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
                tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

                tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
                tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

                tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
                tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
                tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];
            
                vertex_list.push_back({vec3(vx, vy, vz), vec2(tx, ty), vec3(nx, ny, nz)});
                index_list.push_back((unsigned int)index_offset + v);
            }

            index_offset += num_face_vertices;
        }
    }

    void *shader_byte_code = nullptr;
    size_t shader_byte_size = 0;
    GraphicsEngine::Get()->GetVertexMeshLayoutShader(&shader_byte_code, &shader_byte_size);
    vertex_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexBuffer(&vertex_list[0], sizeof(VERTEX), (UINT)vertex_list.size(), shader_byte_code, shader_byte_size);

    index_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateIndexBuffer(&index_list[0], (UINT)index_list.size());
}

Mesh::~Mesh() {
    //texture->Release();
}

std::shared_ptr<VertexBuffer> &Mesh::GetVertexBuffer() {
    return vertex_buffer;
}

std::shared_ptr<IndexBuffer> &Mesh::GetIndexBuffer() {
    return index_buffer;
}