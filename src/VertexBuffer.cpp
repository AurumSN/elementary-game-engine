#include "graphics/components/buffers.h"

#include <stdexcept>

VertexBuffer::VertexBuffer(
    const void *list_vertices,
    UINT vertex_size,
    UINT list_size,
	const void *shader_byte_code,
    size_t shader_byte_size,
	RenderSystem *system
) : system(system) , layout(0), buffer(0), vertex_size(vertex_size), list_size(list_size) {
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertex_size * list_size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	if (FAILED(system->dev->CreateBuffer(&buff_desc, &init_data, &buffer)))
		throw std::runtime_error("Vertex Buffer was not created successfully");
	
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->dev->CreateInputLayout(layout, size_layout, shader_byte_code, shader_byte_size, &this->layout)))
		throw std::runtime_error("Input Layout was not created successfully");

}

VertexBuffer::~VertexBuffer() {
	if (layout)
	    layout->Release();
	if (buffer)
	    buffer->Release();
}

UINT VertexBuffer::GetVertexListSize() {
	return this->list_size;
}