#pragma once
#include <d3d11.h>
#include <vector>
#include "Prerequisites.h"

class DeviceContext;

class IndexBuffer
{

public:
	IndexBuffer();
	IndexBuffer(void* list_indices, UINT size_list, RenderSystem* m_system);
	IndexBuffer(std::vector<unsigned int> list_indices, UINT size_list, RenderSystem* m_system);
	void Load(void* list_indices, UINT size_list, RenderSystem* m_system);
	UINT getSizeIndexList();
	~IndexBuffer();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

