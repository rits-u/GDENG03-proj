#pragma once
#include "Renderer.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "VertexMesh.h"
#include "Mesh.h"


class MeshRenderer : public Renderer 
{
public:
	MeshRenderer(const MeshPtr& mesh);
	~MeshRenderer();

public:
	void init() override;
	void setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list) override;
	void update(constant cc, int width, int height, int camIndex) override;
	void draw() override;
	void release() override;

private:
	MeshPtr m_mesh;

private:
	static bool isInitialized;
	static VertexShaderPtr sharedVS;
	static PixelShaderPtr sharedPS;
	static VertexBufferPtr sharedVB;
	static IndexBufferPtr sharedIB;
	ConstantBufferPtr cb;
};

