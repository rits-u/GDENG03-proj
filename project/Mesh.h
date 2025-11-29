#pragma once
#include "Resource.h"
#include <d3d11.h>
#include <Windows.h>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"
#include "VertexMesh.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	
	~Mesh();
	//const VertexBufferPtr& getVertexBuffer();
	//const IndexBufferPtr& getIndexBuffer();

	std::vector<VertexMesh>& getVertices();
	std::vector<unsigned int>& getIndices();

private:
	std::vector<VertexMesh> m_vertices;
	std::vector<unsigned int> m_indices;
	//VertexBufferPtr vertexBuffer;
	//IndexBufferPtr indexBuffer;

private:
	std::string WStringToString(const std::wstring& wstr);

private:
	friend class DeviceContext;
};

