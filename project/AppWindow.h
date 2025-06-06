#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

