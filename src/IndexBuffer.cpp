#include "graphics/components/buffers.h"

#include <stdexcept>

IndexBuffer::IndexBuffer(const void* index_list, UINT list_size, RenderSystem *system) : system(system) , buffer(0), list_size(list_size) {
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * list_size;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = index_list;

	if (FAILED(system->dev->CreateBuffer(&buff_desc, &init_data, &buffer)))
		throw std::runtime_error("Index Buffer was not created successfully");
}

UINT IndexBuffer::GetIndexListSize() {
	return list_size;
}

IndexBuffer::~IndexBuffer() {
	if (buffer)
	    buffer->Release();
}