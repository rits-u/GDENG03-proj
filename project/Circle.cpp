#include "Circle.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "InputSystem.h"
#include <vector>

Circle::Circle(string name, void* shaderByteCode, size_t sizeShader, int numSegment, int radius) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	InputSystem::get()->addListener(this);

	m_worldCamera.setIdentity();
	m_worldCamera.setTranslation(Vector3D(0, 0, -2));

	//vertex vertex_list[] =
	//{
	//	//CUBE
	//	//front face
	//	{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.0f, 0, 0)},		//pos1
	//	{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1.0f,1.0f,0.0f),	Vector3D(1.5f, -0.5f,1)},		//pos2
	//	{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1.0f,1.0f,0.0f),	Vector3D(0.5f, 1.0f,0)},		//pos3
	//	{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.5f, 0,1)},		//pos4

	//	//back face
	//	{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(1,1.0f, 0)},		//pos5
	//	{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, -0.5f)},		//pos6
	//	{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, 0.5f)},		//pos7
	//	{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(-1,-0.5f, 1)},		//pos8


	//};
	//int segmentCount = 10;
	//int radius = 1;

	std::vector<vertex> vertex_list;
	vertex_list.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1, 1, 1), Vector3D(0, 1, 0) });

	for (int i = 0; i <= numSegment; i++) {
		float theta = (2.0f * 3.14159265f * i) / numSegment;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		vertex_list.push_back({ Vector3D(x, y, 0.0f), Vector3D(1, 1, 1), Vector3D(0, 1, 0) });
	}
	

	//UINT size_list = ARRAYSIZE(vertex_list);
	UINT size_list = vertex_list.size();
	this->vb = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	std::vector<unsigned int> index_list;

	for (int i = 1; i <= numSegment; i++) {
		index_list.push_back(0);        // Center
		index_list.push_back(i);        // Current edge
		index_list.push_back(i + 1);    // Next edge (wraps to 1 when i == segmentCount)
	}

	//unsigned int index_list[] =
	//{
	//	//front side
	//	0, 1, 2,	//first triangle
	//	2, 3, 0,	//2nd

	//	//back side
	//	4, 5, 6,	//3rd
	//	6, 7, 4,	//4th

	//	//top side
	//	1, 6, 5,
	//	5, 2, 1,

	//	//bottom side
	//	7, 0, 3,
	//	3, 4, 7,

	//	//right side
	//	3, 2, 5,
	//	5, 4, 3,

	//	//left side
	//	7, 6, 1,
	//	1, 0, 7
	//};


	//index buffer
	UINT size_index_list = index_list.size();
	//UINT size_index_list = ARRAYSIZE(index_list);

	this->ib = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);

	////constant buffer
	constant cc;
	cc.m_time = 0;
	cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
}

Circle::~Circle()
{
	GameObject::~GameObject();
}

void Circle::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;
}

void Circle::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	constant cc;

	deltaPos += EngineTime::getDeltaTime() / 8.0f;


	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}


	//deltaScale += EngineTime::getDeltaTime() / 0.85f;

	Matrix4x4 scale, rotX, rotY, rotZ, translation, world;

	scale.setIdentity();
	scale.setScale(this->getLocalScale());

	//rotation
	Vector3D rotation = this->getLocalRotation();
	rotX.setIdentity();
	rotX.setRotationX(rotation.m_x);

	rotY.setIdentity();
	rotY.setRotationY(rotation.m_y);

	rotZ.setIdentity();
	rotZ.setRotationZ(rotation.m_z);

	//translation
	translation.setIdentity();
	translation.setTranslation(this->getLocalPosition());

	//matrix transformation
	world.setIdentity();
	world *= scale;
	world *= rotX;
	world *= rotY;
	world *= rotZ;
	world *= translation;

	//update constant buffer
	cc.m_world = world;
	cc.m_view = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(width / (float)height)), 0.1f, 100.0f);
	cc.m_time = this->ticks * 2000.0f;
	cb->update(deviceContext, &cc);
	//cc.m_proj = camera->getPerspective(width, height);


	//set constant buffer
	deviceContext->setConstantBuffer(vs, this->cb);
	deviceContext->setConstantBuffer(ps, this->cb);

	//set index and vertex buffer
	deviceContext->setIndexBuffer(this->ib);
	deviceContext->setVertexBuffer(this->vb);

	//draw
	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

void Circle::setAnimationSpeed(float speed)
{
}

void Circle::onKeyDown(int key)
{
	if (key == 'D') {
		this->forward = 1.0f;
	}
}

void Circle::onKeyUp(int key)
{
}

void Circle::onMouseMove(const Point& mousePos)
{
}

void Circle::onLeftMouseDown(const Point& mousePos)
{
}

void Circle::onLeftMouseUp(const Point& mousePos)
{
}

void Circle::onRightMouseDown(const Point& mousePos)
{
}

void Circle::onRightMouseUp(const Point& mousePos)
{
}
