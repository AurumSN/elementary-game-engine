#pragma once

#include <d3d11.h>
#include "graphics/directx11.h"


class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t shader_byte_size, RenderSystem *system);
	~VertexShader();
private:
	ID3D11VertexShader *shader = nullptr;
	RenderSystem *system = nullptr;
    
	friend class RenderSystem;
};

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t shader_byte_size, RenderSystem *system);
	~PixelShader();
private:
	ID3D11PixelShader *shader = nullptr;
	RenderSystem *system = nullptr;
    
	friend class RenderSystem;
};