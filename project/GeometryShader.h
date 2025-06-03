#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class GeometryShader
{
public:
	GeometryShader();
	void release();
	~GeometryShader();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

private:
	ID3D11GeometryShader* m_gs;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

