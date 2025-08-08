#include "PlaneRenderer.h"

VertexShaderPtr PlaneRenderer::sharedVS = nullptr;
PixelShaderPtr PlaneRenderer::sharedPS = nullptr;
VertexBufferPtr PlaneRenderer::sharedVB = nullptr;
IndexBufferPtr PlaneRenderer::sharedIB = nullptr;

PlaneRenderer::PlaneRenderer() : Renderer() {}

PlaneRenderer::~PlaneRenderer()
{
	this->release();
}

void PlaneRenderer::init()
{
	this->setSize(9.0f);
	this->hasTexture = false;
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	vertex vertex_list[4] = {};
	unsigned int index_list[6] = {};
	this->setUpVerticesAndIndices(vertex_list, index_list);

	sharedVB = renderSystem->createVertexBuffer();
	sharedIB = renderSystem->createIndexBuffer();

	UINT size_list = ARRAYSIZE(vertex_list);
	UINT size_index_list = ARRAYSIZE(index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	sharedVS = renderSystem->createVertexShader(shader_byte_code, size_shader);
	sharedVB->Load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader, renderSystem);
	sharedIB->Load(index_list, size_index_list, renderSystem);
	renderSystem->releaseCompiledShader();

	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	sharedPS = renderSystem->createPixelShader(shader_byte_code, size_shader);
	renderSystem->releaseCompiledShader();

	constant cc;
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));

	this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);
}

void PlaneRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
	int v = 4;
	int n = 6;
	float size = this->getSize();

	vertex temp_vertexList[] =
	{
		{ Vector3D(-0.5f * size, 0.0f, -0.5f * size),  Vector2D(0.0f, 1.0f) }, // 0
		{ Vector3D(-0.5f * size, 0.0f,  0.5f * size),  Vector2D(0.0f, 0.0f) }, // 1
		{ Vector3D(0.5f  * size, 0.0f,  0.5f * size),  Vector2D(1.0f, 0.0f) },  // 2
		{ Vector3D(0.5f  * size, 0.0f, -0.5f * size),  Vector2D(1.0f, 1.0f) }   // 3
	};

	unsigned int temp_indexList[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	for (int i = 0; i < v; ++i)
		vertex_list[i] = temp_vertexList[i];

	for (int i = 0; i < n; ++i)
		index_list[i] = temp_indexList[i];
}

void PlaneRenderer::update(constant cc, int width, int height, int camIndex)
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	cc.m_world = this->getOwner()->getWorldMatrix();

	Camera* cam = SceneCameraHandler::get()->getCameraByIndex(camIndex);
	if (cam->cullingMask & Layer::DEBUG)
	{
		cc.useWireColor = 1.0f;
	}
	else {
		cc.useWireColor = 0.0f;
	}

	if (cam->cullingMask & Layer::UI)
	{
		cc.m_view.setIdentity();
		cc.m_proj.setOrthoLH((float)width / 2.0f, (float)height / 2.0f, -1.0f, 1.0f);
	}
	else
	{
		cc.m_view = cam->getViewMatrix();
		cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(width / (float)height)), 0.1f, 100.0f);
	}

	cc.useTexture = hasTexture;

	this->cb->update(deviceContext, &cc);
}

void PlaneRenderer::release()
{
	PlaneRenderer::sharedVS.reset();
	PlaneRenderer::sharedPS.reset();
	PlaneRenderer::sharedVB.reset();
	PlaneRenderer::sharedIB.reset();
}

void PlaneRenderer::draw()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	deviceContext->setVertexShader(sharedVS);
	deviceContext->setPixelShader(sharedPS);

	//set constant buffer
	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	if (hasTexture) {
		deviceContext->setTexture(sharedPS, this->getTexture());
	}

	//set index and vertex buffer
	deviceContext->setIndexBuffer(sharedIB);
	deviceContext->setVertexBuffer(sharedVB);

	deviceContext->drawIndexedTriangleList(sharedIB->getSizeIndexList(), 0, 0);
}