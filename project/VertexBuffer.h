#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "GameObject.h"
#include <vector>

class VertexBuffer
{

public: 
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, RenderSystem* m_system);
	VertexBuffer(std::vector<GameObject::vertex> list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, RenderSystem* m_system);
	UINT getSizeVertexList();
	~VertexBuffer();

private:
	UINT m_size_vertex;
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

