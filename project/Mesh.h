#pragma once
#include "Resource.h"
#include <d3d11.h>
#include <Windows.h>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	~Mesh();
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

private:
	VertexBufferPtr vertexBuffer;
	IndexBufferPtr indexBuffer;

private:
	std::string WStringToString(const std::wstring& wstr);

private:
	friend class DeviceContext;
};

