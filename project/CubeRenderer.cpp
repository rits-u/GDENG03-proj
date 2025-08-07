#include "CubeRenderer.h"

bool CubeRenderer::isInitialized = false;
VertexShaderPtr CubeRenderer::sharedVS = nullptr;
PixelShaderPtr CubeRenderer::sharedPS = nullptr;
VertexBufferPtr CubeRenderer::sharedVB = nullptr;
IndexBufferPtr CubeRenderer::sharedIB = nullptr;

CubeRenderer::CubeRenderer() : Renderer() {}

CubeRenderer::~CubeRenderer()
{
	this->release();
}

void CubeRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	if (!isInitialized) {
		vertex vertex_list[24] = {};		//v
		unsigned int index_list[36] = {};	//n
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

		std::cout << "banana" << std::endl;
	}


	constant cc;
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));

	this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);


	isInitialized = true;
	this->hasTexture = false;
}

void CubeRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
	int v = 24;
	int n = 36;

	Vector3D positionList[] =
	{
		//front face
		{ Vector3D(-0.5f * size, -0.5f  * size, -0.5f * size) },		//pos1
		{ Vector3D(-0.5f * size,  0.5f  * size, -0.5f * size) },		//pos2
		{ Vector3D(0.5f  * size,  0.5f  * size, -0.5f * size) },		//pos3
		{ Vector3D(0.5f  * size, -0.5f  * size, -0.5f * size) },		//pos4

		//back face
		{ Vector3D(0.5f  * size, -0.5f * size, 0.5f * size) },		//pos5
		{ Vector3D(0.5f  * size,  0.5f * size, 0.5f * size) },		//pos6
		{ Vector3D(-0.5f * size,  0.5f * size, 0.5f * size) },		//pos7
		{ Vector3D(-0.5f * size, -0.5f * size, 0.5f * size) },		//pos8
	};

	Vector2D texCoordList[] =
	{
		{ Vector2D(0.0f, 0.0f) },		//pos1
		{ Vector2D(0.0f, 1.0f) },		//pos2
		{ Vector2D(1.0f, 0.0f) },		//pos3
		{ Vector2D(1.0f, 1.0f) },		//pos4
	};

	vertex temp_vertexList[] =
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

	unsigned int temp_indexList[] =
	{
		//front side
		0, 1, 2, 2, 3, 0,	

		//back side
		4, 5, 6, 6, 7, 4,

		//top side
		8, 9, 10, 10, 11, 8,

		//bottom side
		12, 13, 14, 14, 15, 12,

		//right side
		16, 17, 18, 18, 19, 16,

		//left side
		20, 21, 22, 22, 23, 20
	};

	for (int i = 0; i < v; ++i)
		vertex_list[i] = temp_vertexList[i];

	for (int i = 0; i < n; ++i)
		index_list[i] = temp_indexList[i];

}

void CubeRenderer::update(constant cc, int width, int height, int camIndex)
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

void CubeRenderer::release()
{
	CubeRenderer::sharedVS.reset();
	CubeRenderer::sharedPS.reset();
	CubeRenderer::sharedVB.reset();
	CubeRenderer::sharedIB.reset();
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

	if (hasTexture) {
		deviceContext->setTexture(sharedPS, this->getTexture());
	}

	//set index and vertex buffer
	deviceContext->setIndexBuffer(sharedIB);
	deviceContext->setVertexBuffer(sharedVB);

	deviceContext->drawIndexedTriangleList(sharedIB->getSizeIndexList(), 0, 0);
}



