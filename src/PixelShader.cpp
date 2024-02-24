#include "graphics/components/shaders.h"

#include <stdexcept>

PixelShader::PixelShader(const void *shader_byte_code, size_t shader_byte_size, RenderSystem *system) : system(system) {
	if (FAILED(system->dev->CreatePixelShader(shader_byte_code, shader_byte_size, nullptr, &shader)))
		throw std::runtime_error("Pixel Shader was not created successfully");

}

PixelShader::~PixelShader() {
    if (shader)
	    shader->Release();
}