#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();		//initialize the GraphicsEngine and DirectX 11 Device
	bool release();		//release all the resources loaded
	~GraphicsEngine();
	RenderSystem* getRenderSystem();

public:
	static GraphicsEngine* get();

private:
	RenderSystem* m_render_system = nullptr;

//
//public: 
//	SwapChain* createSwapChain();
//	DeviceContext* getImmediateDeviceContext();
//	VertexBuffer* createVertexBuffer();
//	IndexBuffer* createIndexBuffer();
//	ConstantBuffer* createConstantBuffer();
//	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
//	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
//
//public:
//	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
//	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
//	void releaseCompiledShader();

	//default simple shaders
	//bool createShaders();
	//bool setShaders();
	//void getShaderBufferAndSize(void** bytecode, UINT* size);



//private:
//	DeviceContext* m_imm_device_context;
//
//private:
//	ID3D11Device* m_d3d_device;
//	D3D_FEATURE_LEVEL m_feature_level;
//
//	ID3D11DeviceContext* m_imm_context;
//
//private:
//	IDXGIDevice* m_dxgi_device;
//	IDXGIAdapter* m_dxgi_adapter;
//	IDXGIFactory* m_dxgi_factory;
//
//private:
//	ID3DBlob* m_blob = nullptr;
//
//
//	ID3DBlob* m_vsblob = nullptr;
//	ID3DBlob* m_psblob = nullptr;
//	ID3D11VertexShader* m_vs = nullptr;
//	ID3D11PixelShader* m_ps = nullptr;
//
//private:
//	friend class SwapChain;
//	friend class DeviceContext;
//	friend class VertexBuffer;
//	friend class IndexBuffer;
//	friend class ConstantBuffer;
//	friend class VertexShader;
//	friend class PixelShader;

};

