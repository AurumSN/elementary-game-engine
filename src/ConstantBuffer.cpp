#include "graphics/components/buffers.h"

#include <stdexcept>

ConstantBuffer::ConstantBuffer(const void * buffer, UINT size_buffer,RenderSystem * system) : system(system), buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(system->dev->CreateBuffer(&buff_desc, &init_data, &this->buffer)))
		throw std::runtime_error("Constant Buffer was not created successfully");
}


void ConstantBuffer::Update(void * buffer)
{
	system->devcon->UpdateSubresource(this->buffer, 0, nullptr, buffer, 0, 0);
}


ConstantBuffer::~ConstantBuffer()
{
	if (buffer)
        buffer->Release();
}