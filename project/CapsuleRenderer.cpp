#include "CapsuleRenderer.h"

bool CapsuleRenderer::isInitialized = false;
VertexShaderPtr CapsuleRenderer::sharedVS = nullptr;
PixelShaderPtr CapsuleRenderer::sharedPS = nullptr;
VertexBufferPtr CapsuleRenderer::sharedVB = nullptr;
IndexBufferPtr CapsuleRenderer::sharedIB = nullptr;

CapsuleRenderer::CapsuleRenderer() : Renderer()
{
	this->setSize(2.5f);
	this->setRadius(0.7f);
	this->hasTexture = false;
	this->setName("Capsule Renderer");
}

void CapsuleRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	if (!isInitialized) {
		vertex vertex_list[592] = {};
		unsigned int index_list[2808] = {};
		this->setUpVerticesAndIndices(vertex_list, index_list);

		std::cout << "adadas" << std::endl;

		UINT size_list = ARRAYSIZE(vertex_list);
		UINT size_index_list = ARRAYSIZE(index_list);

		sharedVB = renderSystem->createVertexBuffer();
		sharedIB = renderSystem->createIndexBuffer();

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

	std::cout << "???" << std::endl;
}

void CapsuleRenderer::update(constant cc, int width, int height, int camIndex)
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

void CapsuleRenderer::release()
{
	CapsuleRenderer::sharedVS.reset();
	CapsuleRenderer::sharedPS.reset();
	CapsuleRenderer::sharedVB.reset();
	CapsuleRenderer::sharedIB.reset();
}

void CapsuleRenderer::draw()
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

void CapsuleRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
	float radius = this->getRadius();
	float totalHeight = this->getSize(); 
	float pi = 3.14159265f;

	int slices = 36;
	int stacks = 6;

	float cylinderHeight = totalHeight - 2.0f * radius;
	Vector3D objectPos = this->getOwner()->getPosition();

	float halfCylinder = cylinderHeight / 2.0f;

	int curr_vertex = 0;
	int curr_index = 0;

	//side cylinder vertices
	for (int i = 0; i <= slices; ++i) {
		float theta = (float)i / slices * 2.0f * pi;
		float x = radius * cos(theta);
		float z = radius * sin(theta);
		float u = (float)i / slices;

		Vector3D top = objectPos + Vector3D(x, +halfCylinder, z);
		Vector3D bottom = objectPos + Vector3D(x, -halfCylinder, z);

		vertex_list[curr_vertex++] = { top, Vector2D(u, 0) };
		vertex_list[curr_vertex++] = { bottom, Vector2D(u, 1) };
	}

	int side_start_index = 0;
	int side_vertex_count = (slices + 1) * 2;

	//top hemisphere vertices
	for (int y = 0; y <= stacks; ++y) {
		float phi = (pi / 2.0f) * (float)y / stacks; 
		float sinPhi = sin(phi);
		float cosPhi = cos(phi);
		float v = 1.0f - ((float)y / stacks); //flip for top

		for (int i = 0; i <= slices; ++i) {
			float theta = (2 * pi * i) / slices;
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);

			float x = radius * sinPhi * cosTheta;
			float yPos = radius * cosPhi;
			float z = radius * sinPhi * sinTheta;

			Vector3D position = objectPos + Vector3D(x, halfCylinder + yPos, z);
			Vector2D texcoord = Vector2D((float)i / slices, v * 0.5f);

			vertex_list[curr_vertex++] = { position, texcoord };
		}
	}

	int top_hemisphere_start = side_vertex_count;
	int top_hemisphere_vert_count = (stacks + 1) * (slices + 1);


	//bottom hemisphere vertices
	for (int y = 0; y <= stacks; ++y) {
		float phi = (pi / 2.0f) * (float)y / stacks; 
		float sinPhi = sin(phi);
		float cosPhi = cos(phi);
		float v = (float)y / stacks;

		for (int i = 0; i <= slices; ++i) {
			float theta = (2 * pi * i) / slices;
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);

			float x = radius * sinPhi * cosTheta;
			float yPos = -radius * cosPhi;
			float z = radius * sinPhi * sinTheta;

			Vector3D position = objectPos + Vector3D(x, -halfCylinder + yPos, z);
			Vector2D texcoord = Vector2D((float)i / slices, 0.5f + v * 0.5f);

			vertex_list[curr_vertex++] = { position, texcoord };
		}
	}

	int bottom_hemisphere_start = top_hemisphere_start + top_hemisphere_vert_count;
	int bottom_hemisphere_vert_count = (stacks + 1) * (slices + 1);

	//side wall indices
	for (int i = 0; i < slices; ++i) {
		int top_curr = side_start_index + i * 2;
		int bottom_curr = top_curr + 1;
		int top_next = side_start_index + ((i + 1) % (slices + 1)) * 2;
		int bottom_next = top_next + 1;

		index_list[curr_index++] = top_curr;
		index_list[curr_index++] = bottom_next;
		index_list[curr_index++] = bottom_curr;

		index_list[curr_index++] = top_curr;
		index_list[curr_index++] = top_next;
		index_list[curr_index++] = bottom_next;
	}

	//top hemisphere
	for (int y = 0; y < stacks; ++y) {
		for (int i = 0; i < slices; ++i) {
			int curr = top_hemisphere_start + y * (slices + 1) + i;
			int next = curr + slices + 1;

			index_list[curr_index++] = curr;
			index_list[curr_index++] = next + 1;
			index_list[curr_index++] = next;

			index_list[curr_index++] = curr;
			index_list[curr_index++] = curr + 1;
			index_list[curr_index++] = next + 1;
		}
	}

	//bottom hemisphere
	for (int y = 0; y < stacks; ++y) {
		for (int i = 0; i < slices; ++i) {
			int curr = bottom_hemisphere_start + y * (slices + 1) + i;
			int next = curr + slices + 1;

			index_list[curr_index++] = curr;
			index_list[curr_index++] = next;
			index_list[curr_index++] = next + 1;

			index_list[curr_index++] = curr;
			index_list[curr_index++] = next + 1;
			index_list[curr_index++] = curr + 1;
		}
	}
}


