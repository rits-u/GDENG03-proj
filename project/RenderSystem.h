#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include "Prerequisites.h"
#include "GameObject.h"


class RenderSystem
{
public:
	RenderSystem();		//initialize the GraphicsEngine and DirectX 11 Device
	~RenderSystem();	//release all the resources loaded

public:
	DeviceContextPtr getImmediateDeviceContext();
	SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
	VertexBufferPtr createVertexBuffer();
	VertexBufferPtr createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	VertexBufferPtr createVertexBuffer(std::vector<vertex> list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	IndexBufferPtr createIndexBuffer();
	IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list, RenderSystem* m_system);
	IndexBufferPtr createIndexBuffer(std::vector<unsigned int> list_indices, UINT size_list, RenderSystem* m_system);
	ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
	VertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);

public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();
	void createRasterizerStates();
	ID3D11RasterizerState* getWireframeState();
	ID3D11RasterizerState* getSolidState();

public:
	ID3D11Device* m_d3d_device;
	ID3D11DeviceContext* m_imm_context;

private:
	DeviceContextPtr m_imm_device_context;

private:
	//ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

//	ID3D11DeviceContext* m_imm_context;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

private:
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	ID3D11RasterizerState* m_wireframeState = nullptr;
	ID3D11RasterizerState* m_solidState = nullptr;

private:
	friend class SwapChain;
	friend class DeviceContext;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class Texture;

};

