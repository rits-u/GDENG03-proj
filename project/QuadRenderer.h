#pragma once
#include "Renderer.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"

class QuadRenderer : public Renderer
{
public:
	QuadRenderer();
	~QuadRenderer();

public:
	void init() override;
	void setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list) override;
	void update(constant cc, int width, int height, int camIndex) override;
	void draw() override;
	void release() override;

private:
	static bool isInitialized;
	static VertexShaderPtr sharedVS;
	static PixelShaderPtr sharedPS;
	static VertexBufferPtr sharedVB;
	static IndexBufferPtr sharedIB;
	ConstantBufferPtr cb;
	float size = 9.0f;
};

