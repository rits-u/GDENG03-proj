#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool createDSV(UINT width, UINT height);
	void depthTesting();
	bool present(bool vsync);

	bool release();
	~SwapChain();

//public:
//	static SwapChain* get();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;

private:
	friend class DeviceContext;
};

