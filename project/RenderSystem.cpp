#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GameObject.h"

#include <vector>
#include <d3dcompiler.h>
#include <exception>

RenderSystem::RenderSystem()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	//ID3D11DeviceContext* m_imm_context;

	for (UINT driver_types_index = 0; driver_types_index < num_driver_types; )
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_types_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(res))
			break;

		++driver_types_index;
	}

	if (FAILED(res))
	{
		throw std::exception("RenderSystem not created successfully");
	}

	m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	//m_dxgi_factory->CreateSwapChain();
}

//bool RenderSystem::init()
//{
//	D3D_DRIVER_TYPE driver_types[] =
//	{
//		D3D_DRIVER_TYPE_HARDWARE,
//		D3D_DRIVER_TYPE_WARP,
//		D3D_DRIVER_TYPE_REFERENCE
//	};
//
//	UINT num_driver_types = ARRAYSIZE(driver_types);
//
//	D3D_FEATURE_LEVEL feature_levels[] =
//	{
//		D3D_FEATURE_LEVEL_11_0
//	};
//
//	UINT num_feature_levels = ARRAYSIZE(feature_levels);
//
//	HRESULT res = 0;
//	//ID3D11DeviceContext* m_imm_context;
//
//	for (UINT driver_types_index = 0; driver_types_index < num_driver_types; )
//	{
//		res = D3D11CreateDevice(NULL, driver_types[driver_types_index], NULL, NULL, feature_levels,
//			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
//
//		if (SUCCEEDED(res))
//			break;
//
//		++driver_types_index;
//	}
//
//	if (FAILED(res))
//	{
//		return false;
//	}
//
//	m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);
//
//	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
//	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
//	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
//	//m_dxgi_factory->CreateSwapChain();
//
//	return true;
//}

//bool RenderSystem::release()
//{
//	//if (m_vs) m_vs->Release();
//	//if (m_ps) m_ps->Release();
//
//	//if (m_vsblob) m_vsblob->Release();
//	//if (m_psblob) m_psblob->Release();
//
//	//m_dxgi_device->Release();
//	//m_dxgi_adapter->Release();
//	//m_dxgi_factory->Release();
//
//	//m_d3d_device->Release();
//
//	//return true;
//}

RenderSystem::~RenderSystem()
{
	if (m_vs) m_vs->Release();
	if (m_ps) m_ps->Release();

	if (m_vsblob) m_vsblob->Release();
	if (m_psblob) m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_d3d_device->Release();
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;
	try
	{
		//sc = new SwapChain(hwnd, width, height, this);
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
	}
	catch (...) {}
	return sc;
}

VertexBufferPtr RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	VertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch (...) {}
	return vb;
}

VertexBufferPtr RenderSystem::createVertexBuffer(std::vector<GameObject::vertex> list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	//std::vector<vertex> vertex_list;
	VertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch (...) {}
	return vb;
}

IndexBufferPtr RenderSystem::createIndexBuffer(void* list_indices, UINT size_list, RenderSystem* m_system)
{
	IndexBufferPtr ib = nullptr;
	try
	{
		ib = std::make_shared<IndexBuffer>(list_indices, size_list, this);
	}
	catch (...) {}
	return ib;
}

IndexBufferPtr RenderSystem::createIndexBuffer(std::vector<unsigned int> list_indices, UINT size_list, RenderSystem* m_system)
{
	IndexBufferPtr ib = nullptr;
	try
	{
		ib = std::make_shared<IndexBuffer>(list_indices, size_list, this);
	}
	catch (...) {}
	return ib;
}

ConstantBufferPtr RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBufferPtr cb = nullptr;
	try
	{
		cb = std::make_shared<ConstantBuffer>(buffer, size_buffer, this);
	}
	catch (...) {}
	return cb;
}

VertexShaderPtr RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShaderPtr vs = nullptr;
	try
	{
		vs = std::make_shared<VertexShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return vs;
}

PixelShaderPtr RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShaderPtr ps = nullptr;
	try
	{
		ps = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}

void RenderSystem::createRasterizerStates()
{
	D3D11_RASTERIZER_DESC solidDesc = {};
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.DepthClipEnable = true;
	m_d3d_device->CreateRasterizerState(&solidDesc, &m_solidState);

	//wireframe state
	D3D11_RASTERIZER_DESC wireDesc = {};
	wireDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireDesc.CullMode = D3D11_CULL_NONE;
	wireDesc.DepthClipEnable = true;
	m_d3d_device->CreateRasterizerState(&wireDesc, &m_wireframeState);
}

ID3D11RasterizerState* RenderSystem::getWireframeState()
{
	return this->m_wireframeState;
}
ID3D11RasterizerState* RenderSystem::getSolidState()
{
	return this->m_solidState;
}

//
//RenderSystem* RenderSystem::get()
//{
//	static RenderSystem renderSystem;
//	return &renderSystem;
//}
