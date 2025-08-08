#include "CylinderRenderer.h"

bool CylinderRenderer::isInitialized = false;
VertexShaderPtr CylinderRenderer::sharedVS = nullptr;
PixelShaderPtr CylinderRenderer::sharedPS = nullptr;
VertexBufferPtr CylinderRenderer::sharedVB = nullptr;
IndexBufferPtr CylinderRenderer::sharedIB = nullptr;

CylinderRenderer::CylinderRenderer() : Renderer() 
{
	this->setSize(2.5f);
	this->setRadius(0.7f);
	this->hasTexture = false;
	this->setName("Cylinder Renderer");
}

void CylinderRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	if (!isInitialized) {
		vertex vertex_list[146] = {};
		unsigned int index_list[432] = {};
		this->setUpVerticesAndIndices(vertex_list, index_list);

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
}

void CylinderRenderer::update(constant cc, int width, int height, int camIndex)
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

void CylinderRenderer::release()
{
	CylinderRenderer::sharedVS.reset();
	CylinderRenderer::sharedPS.reset();
	CylinderRenderer::sharedVB.reset();
	CylinderRenderer::sharedIB.reset();
}

void CylinderRenderer::draw()
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

void CylinderRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
	float radius = this->getRadius();
	float height = this->getSize();
	float pi = 3.14f;

	Vector3D objectPos = this->getOwner()->getPosition();

	Vector3D circle1_center = Vector3D(objectPos.m_x, objectPos.m_y + (height / 2), objectPos.m_z);
	Vector3D circle2_center = Vector3D(objectPos.m_x, objectPos.m_y + -(height / 2), objectPos.m_z);

	int slices = 36;
	int curr_vertex = 0;
	int curr_index = 0;

	vertex_list[curr_vertex++] = { circle1_center, Vector2D(0.5, 0.5) };
	vertex_list[curr_vertex++] = { circle2_center, Vector2D(0.5, 0.5) };

	for (int i = 0; i < slices; i++) {
		float angle = (float)i / slices * 2.0f * pi;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		Vector3D circle1 = circle1_center + Vector3D(x, 0, z);
		Vector3D circle2 = circle2_center + Vector3D(x, 0, z);
																
		Vector2D cap_texcoord = Vector2D(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));

		vertex_list[curr_vertex++] = { circle1, cap_texcoord };
		vertex_list[curr_vertex++] = { circle2, cap_texcoord };
	}

	int side_start_index = curr_vertex;

	//retrieving uv or tex coords for sides//
	for (int i = 0; i < slices; ++i) {
		float angle = (float)i / slices * 2.0f * pi;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		Vector3D circle1 = circle1_center + Vector3D(x, 0, z);
		Vector3D circle2 = circle2_center + Vector3D(x, 0, z);

		float u = (float)i / slices;
		Vector2D texcoord1 = Vector2D(u, 0);
		Vector2D texcoord2 = Vector2D(u, 1);

		vertex_list[curr_vertex++] = { circle1, texcoord1 };
		vertex_list[curr_vertex++] = { circle2, texcoord2 };
	}

	//connecting circles//
	for (int i = 0; i < slices; ++i) {
		int top_center = 0;
		int top_curr_slice = 2 + i * 2;
		int top_next_slice = 2 + ((i + 1) % slices) * 2;

		index_list[curr_index++] = top_center;
		index_list[curr_index++] = top_next_slice;
		index_list[curr_index++] = top_curr_slice;

		int bottom_center = 1;
		int bottom_curr_slice = 2 + i * 2 + 1;
		int bottom_next_slice = 2 + ((i + 1) % slices) * 2 + 1;

		index_list[curr_index++] = bottom_center;
		index_list[curr_index++] = bottom_curr_slice;
		index_list[curr_index++] = bottom_next_slice;
	}

	//connecting side walls//
	for (int i = 0; i < slices; ++i) {
		int top_curr = side_start_index + i * 2;
		int bottom_curr = side_start_index + i * 2 + 1;
		int top_next = side_start_index + ((i + 1) % slices) * 2;
		int bottom_next = side_start_index + ((i + 1) % slices) * 2 + 1;

		index_list[curr_index++] = top_curr;
		index_list[curr_index++] = bottom_next;
		index_list[curr_index++] = bottom_curr;

		index_list[curr_index++] = top_curr;
		index_list[curr_index++] = top_next;
		index_list[curr_index++] = bottom_next;
	}

}
