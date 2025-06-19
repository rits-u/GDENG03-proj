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

};

