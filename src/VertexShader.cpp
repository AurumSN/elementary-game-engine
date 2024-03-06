#include "graphics/components/shaders.h"

#include <stdexcept>

VertexShader::VertexShader(const void *shader_byte_code, size_t shader_byte_size, RenderSystem *system) : system(system) {
	if (FAILED(system->dev->CreateVertexShader(shader_byte_code, shader_byte_size, nullptr, &shader)))
		throw std::runtime_error("Vertex Shader was not created successfully");

}

VertexShader::~VertexShader() {
    if (shader)
	    shader->Release();
}