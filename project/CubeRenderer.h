#pragma once
#include "Component.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
//#include "Prerequisites.h"

class CubeRenderer : public Component
{
public:
	CubeRenderer();

	void update(constant cc) override;
	void release() override;

public:
	void init() override;
	void update(constant cc, int width, int height, int camIndex) override;
	void draw() override;


private:
	static VertexShaderPtr sharedVS;
	static PixelShaderPtr sharedPS;
	static VertexBufferPtr sharedVB;
	static IndexBufferPtr sharedIB;
	ConstantBufferPtr cb;
	TexturePtr texture;
};