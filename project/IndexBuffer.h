#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{

public:
	IndexBuffer();
	bool load(void* buffer, UINT size_buffer);
	bool release();
	UINT getSizeIndices();
	~IndexBuffer();

private:
	UINT m_size_indices;

private:
	ID3D11Buffer* m_buffer;

private:
	friend class DeviceContext;
};

