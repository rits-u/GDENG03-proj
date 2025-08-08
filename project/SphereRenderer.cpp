#include "SphereRenderer.h"

bool SphereRenderer::isInitialized = false;
VertexShaderPtr SphereRenderer::sharedVS = nullptr;
PixelShaderPtr SphereRenderer::sharedPS = nullptr;
VertexBufferPtr SphereRenderer::sharedVB = nullptr;
IndexBufferPtr SphereRenderer::sharedIB = nullptr;

SphereRenderer::SphereRenderer() : Renderer() 
{
	this->setRadius(1.0f);
	this->hasTexture = false;
	this->setName("Sphere Renderer");
}

SphereRenderer::~SphereRenderer()
{
	this->release();
}

void SphereRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	if (!isInitialized) {
		vertex vertex_list[289] = {};
		unsigned int index_list[1536] = {};
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
	}

	constant cc;
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));

	this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);

	isInitialized = true;
}

void SphereRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
	float radius = this->getRadius();
	float pi = 3.14;
	Vector3D center = this->getOwner()->getPosition();

	int stacks = 16;
	int slices = 16;

	int index = 0;
	for (int i = 0; i <= stacks; i++) {
		float stack_angle = (float)i / stacks * pi;
		for (int j = 0; j <= slices; j++) {
			float slice_angle = (float)j / slices * 2 * pi;

			float x = radius * sin(stack_angle) * cos(slice_angle);
			float y = radius * cos(stack_angle);
			float z = radius * sin(stack_angle) * sin(slice_angle);

			Vector3D pos = center + Vector3D(x, y, z);
			Vector3D color1 = Vector3D(1, 0, 1);

			float u = (float)j / slices;
			float v = (float)i / stacks;
			Vector2D texCoord = Vector2D(u, v);

			vertex_list[index] = { pos, texCoord };
			index++;
		}
	}

	index = 0;
	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < slices; j++) {
			int top_left = i * (slices + 1) + j;
			int bot_left = top_left + (slices + 1);

			index_list[index + 0] = top_left;
			index_list[index + 1] = top_left + 1;
			index_list[index + 2] = bot_left;

			index_list[index + 3] = bot_left;
			index_list[index + 4] = top_left + 1;
			index_list[index + 5] = bot_left + 1;

			index = index + 6;
		}
	}
}

void SphereRenderer::update(constant cc, int width, int height, int camIndex)
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

void SphereRenderer::release()
{
	SphereRenderer::sharedVS.reset();
	SphereRenderer::sharedPS.reset();
	SphereRenderer::sharedVB.reset();
	SphereRenderer::sharedIB.reset();
}

void SphereRenderer::draw()
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



