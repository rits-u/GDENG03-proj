#include "CubeRenderer.h"

VertexShaderPtr CubeRenderer::sharedVS = nullptr;
PixelShaderPtr CubeRenderer::sharedPS = nullptr;
VertexBufferPtr CubeRenderer::sharedVB = nullptr;
IndexBufferPtr CubeRenderer::sharedIB = nullptr;

CubeRenderer::CubeRenderer() : Component(ComponentType::RENDERER)
{
}

void CubeRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	Vector3D positionList[] =
	{
		//CUBE
		//front face
		{ Vector3D(-0.5f, -0.5f, -0.5f)},		//pos1
		{ Vector3D(-0.5f, 0.5f, -0.5f) },		//pos2
		{ Vector3D(0.5f, 0.5f, -0.5f)  },		//pos3
		{ Vector3D(0.5f, -0.5f, -0.5f) },		//pos4

		//back face
		{ Vector3D(0.5f, -0.5f, 0.5f) },		//pos5
		{ Vector3D(0.5f, 0.5f, 0.5f)  },		//pos6
		{ Vector3D(-0.5f, 0.5f, 0.5f) },		//pos7
		{ Vector3D(-0.5f, -0.5f, 0.5f)},		//pos8
	};

	Vector2D texCoordList[] =
	{
		{ Vector2D(0.0f, 0.0f) },		//pos1
		{ Vector2D(0.0f, 1.0f) },		//pos2
		{ Vector2D(1.0f, 0.0f) },		//pos3
		{ Vector2D(1.0f, 1.0f) },		//pos4
	};

	vertex vertex_list[] =
	{
		//front face
		{ positionList[0], texCoordList[1] },
		{ positionList[1], texCoordList[0] },
		{ positionList[2], texCoordList[2] },
		{ positionList[3], texCoordList[3] },

		//back face
		{ positionList[4], texCoordList[1] },
		{ positionList[5], texCoordList[0] },
		{ positionList[6], texCoordList[2] },
		{ positionList[7], texCoordList[3] },

		{ positionList[1], texCoordList[1] },
		{ positionList[6], texCoordList[0] },
		{ positionList[5], texCoordList[2] },
		{ positionList[2], texCoordList[3] },

		{ positionList[7], texCoordList[1] },
		{ positionList[0], texCoordList[0] },
		{ positionList[3], texCoordList[2] },
		{ positionList[4], texCoordList[3] },

		{ positionList[3], texCoordList[1] },
		{ positionList[2], texCoordList[0] },
		{ positionList[5], texCoordList[2] },
		{ positionList[4], texCoordList[3] },

		{ positionList[7], texCoordList[1] },
		{ positionList[6], texCoordList[0] },
		{ positionList[1], texCoordList[2] },
		{ positionList[0], texCoordList[3] },

	};

	unsigned int index_list[] =
	{
		//front side
		0, 1, 2,	//first triangle
		2, 3, 0,	//2nd

		//back side
		4, 5, 6,	//3rd
		6, 7, 4,	//4th

		//top side
		8, 9, 10,
		10, 11, 8,

		//bottom side
		12, 13, 14,
		14, 15, 12,

		//right side
		16, 17, 18,
		18, 19, 16,

		//left side
		20, 21, 22,
		22, 23, 20
	};


	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");

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
	//	cb->load(&cc, sizeof(constant));

	this->owner->setLayer(this->owner->getLayer() | Layer::DEBUG);
}

void CubeRenderer::update(constant cc, int width, int height, int camIndex)
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	//constant cc = this->owner->getConstant();

	//update constant buffer

	cc.m_world = this->owner->getWorldMatrix();
	//this->cc.m_time = this->ticks * 2000.0f;

	Camera* cam = SceneCameraHandler::get()->getCameraByIndex(camIndex);
	if (cam->cullingMask & Layer::DEBUG)
	{
		cc.useWireColor = 1.0f;
		cc.wireColor = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
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

	this->cb->update(deviceContext, &cc);
}

void CubeRenderer::update(constant cc)
{
}

void CubeRenderer::release()
{
}

void CubeRenderer::draw()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	deviceContext->setVertexShader(sharedVS);
	deviceContext->setPixelShader(sharedPS);

	//set constant buffer
	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	deviceContext->setTexture(sharedPS, this->texture);

	//set index and vertex buffer
	deviceContext->setIndexBuffer(sharedIB);
	deviceContext->setVertexBuffer(sharedVB);

	deviceContext->drawIndexedTriangleList(sharedIB->getSizeIndexList(), 0, 0);
}



