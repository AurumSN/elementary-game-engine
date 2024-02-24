#pragma once

#include <d3d11.h>
#include "graphics/directx11.h"

class VertexBuffer
{
public:
	VertexBuffer(const void *vertex_list, UINT vertex_size, UINT list_size, const void *shader_byte_code, size_t shader_byte_size, RenderSystem *system);
	~VertexBuffer();

	UINT GetVertexListSize();
private:
	UINT vertex_size;
	UINT list_size;

	ID3D11Buffer *buffer = nullptr;
	ID3D11InputLayout *layout = nullptr;
	RenderSystem *system = nullptr;
    
	friend class RenderSystem;
};

class IndexBuffer
{
public:
	IndexBuffer(const void* index_list, UINT list_size, RenderSystem *system);
	~IndexBuffer();

	UINT GetIndexListSize();
private:
	UINT list_size;

	ID3D11Buffer *buffer = nullptr;
	RenderSystem *system = nullptr;

	friend class RenderSystem;
};

class ConstantBuffer
{
public:
	ConstantBuffer(const void *buffer, UINT buffer_size, RenderSystem *system);
	~ConstantBuffer();

	void Update(void *buffer);
private:
	ID3D11Buffer *buffer = nullptr;
	RenderSystem *system = nullptr;

	friend class RenderSystem;
};