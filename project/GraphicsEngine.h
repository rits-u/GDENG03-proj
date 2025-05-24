#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();		//initialize the GraphicsEngine and DirectX 11 Device
	bool release();		//release all the resources loaded
	~GraphicsEngine();

public: 
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

public:
	static GraphicsEngine* get();

private:
	DeviceContext* m_imm_device_context;

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	ID3D11DeviceContext* m_imm_context;

	ID3DBlob* m_vsblob;
	ID3DBlob* m_psblob;

	ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;



private:
	friend class SwapChain;
	friend class DeviceContext;
	friend class VertexBuffer;
};

