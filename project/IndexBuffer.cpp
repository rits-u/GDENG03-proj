#include "IndexBuffer.h"
#include "GraphicsEngine.h"


IndexBuffer::IndexBuffer()
{
}

bool IndexBuffer::load(void* buffer, UINT size_buffer)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = size_buffer;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = buffer;

	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&indexBufferDesc, &indexData, &m_buffer);
	if (FAILED(hr)) {
		return false;
	}

	this->m_size_indices = size_buffer;

	return true;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;

	return true;
}

UINT IndexBuffer::getSizeIndices()
{
	return this->m_size_indices;
}

IndexBuffer::~IndexBuffer()
{
}
