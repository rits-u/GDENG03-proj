#include "MeshRenderer.h"

bool MeshRenderer::isInitialized = false;
VertexShaderPtr MeshRenderer::sharedVS = nullptr;
PixelShaderPtr MeshRenderer::sharedPS = nullptr;
VertexBufferPtr MeshRenderer::sharedVB = nullptr;
IndexBufferPtr MeshRenderer::sharedIB = nullptr;

MeshRenderer::MeshRenderer(const MeshPtr& mesh) : Renderer()
{
	this->m_mesh = mesh;
	this->hasTexture = false;
	this->setSize(1.1f);
	this->setName("Mesh Renderer");
}

MeshRenderer::~MeshRenderer()
{
	this->release();
}

void MeshRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	std::cout << "Vertices: " << m_mesh->getVertices().size()
		<< ", Indices: " << m_mesh->getIndices().size() << "\n";

	if (!isInitialized)
	{
		void* bytecode = nullptr;
		size_t sizeBytecode = 0;

		renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &bytecode, &sizeBytecode);
		sharedVS = renderSystem->createVertexShader(bytecode, sizeBytecode);

		//vertex buffer
		sharedVB = renderSystem->createVertexBuffer();
		sharedVB->Load(m_mesh->getVertices().data(), sizeof(VertexMesh), (UINT)m_mesh->getVertices().size(), bytecode, (UINT)sizeBytecode, renderSystem);
		renderSystem->releaseCompiledShader();

		//pixel shader
		renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &bytecode, &sizeBytecode);
		sharedPS = renderSystem->createPixelShader(bytecode, sizeBytecode);
		renderSystem->releaseCompiledShader();

		//index buffer
		sharedIB = renderSystem->createIndexBuffer();
		sharedIB->Load(m_mesh->getIndices().data(), (UINT)m_mesh->getIndices().size(), renderSystem);
		isInitialized = true;
	
	}

	constant cc;
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));

	this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);
	
}

void MeshRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
}

void MeshRenderer::update(constant cc, int width, int height, int camIndex)
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

void MeshRenderer::draw()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	deviceContext->setVertexShader(sharedVS);
	deviceContext->setPixelShader(sharedPS);

	if (hasTexture)
		deviceContext->setTexture(sharedPS, this->getTexture());

	deviceContext->setIndexBuffer(sharedIB);
	deviceContext->setVertexBuffer(sharedVB);

//	std::cout << "draw model" << std::endl;

	deviceContext->drawIndexedTriangleList(sharedIB->getSizeIndexList(), 0, 0);
}

void MeshRenderer::release()
{
	sharedVS.reset();
	sharedPS.reset();
	sharedVB.reset();
	sharedIB.reset();
}
