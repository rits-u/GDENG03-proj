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
	//UINT m_size_vertex;
	//UINT m_size_list;
	//DWORD indices[3] = { 0, 1, 2 };
	UINT m_size_indices;

private:
	ID3D11Buffer* m_buffer;
	//ID3D11InputLayout* m_layout;

private:
	friend class DeviceContext;
};

