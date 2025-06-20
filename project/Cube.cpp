#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

#include <DirectXMath.h>
#include "SceneCameraHandler.h"
#include "InputSystem.h"



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	InputSystem::get()->addListener(this);

	m_worldCamera.setIdentity();
	m_worldCamera.setTranslation(Vector3D(0, 0, -2));

	Vector3D white = Vector3D(1, 1, 1);
	Vector3D darkGray = Vector3D(0.8, 0.8, 0.8);
	Vector3D lightGray = Vector3D(0.2, 0.2, 0.2);

	//vertex vertex_list[] =
	//{
	//	//CUBE
	//	//front face
	//	{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.0f,0.0f,0.0f)},		//pos1
	//	{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1.0f,0.5f,0.0f),	Vector3D(1.0f,0.5f,0.0f)},		//pos2
	//	{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1.0f,1.0f,0.0f),	Vector3D(1.0f,1.0f,0.0f)},		//pos3
	//	{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.0f,0.0f,0.0f)},		//pos4

	//	//back face
	//	{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0.0f,1.0f,0.0f),	Vector3D(0.0f,1.0f,0.0f)},		//pos5
	//	{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0.0f,0.0f,1.0f),	Vector3D(0.0f,0.0f,1.0f)},		//pos6
	//	{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0.0f,0.0f,1.0f),	Vector3D(0.0f,0.0f,1.0f)},		//pos7
	//	{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0.0f,0.0f,1.0f),	Vector3D(0.0f,0.0f,1.0f)},		//pos8

	//};

	//vertex vertex_list[] =
	//{
	//	//CUBE
	//	//front face
	//	{Vector3D(-0.5f, -0.5f, -0.5f), white,	white},		//pos1
	//	{Vector3D(-0.5f, 0.5f, -0.5f),	white,	white},		//pos2
	//	{Vector3D(0.5f, 0.5f, -0.5f),	white,	white},		//pos3
	//	{Vector3D(0.5f, -0.5f, -0.5f),	white,	white},		//pos4

	//	//back face
	//	{Vector3D(0.5f, -0.5f, 0.5f),	white,	white},		//pos5
	//	{Vector3D(0.5f, 0.5f, 0.5f),	white,	white},		//pos6
	//	{Vector3D(-0.5f, 0.5f, 0.5f),	white,	white},		//pos7
	//	{Vector3D(-0.5f, -0.5f, 0.5f),	white,	white},		//pos8

	//};

	vertex vertex_list[] =
	{
		//CUBE
		//front face
		{Vector3D(-0.5f, -0.5f, -0.5f), darkGray,	darkGray},		//pos1
		{Vector3D(-0.5f, 0.5f, -0.5f),	darkGray,	darkGray},		//pos2
		{Vector3D(0.5f, 0.5f, -0.5f),	darkGray,	darkGray},		//pos3
		{Vector3D(0.5f, -0.5f, -0.5f),	darkGray,	darkGray},		//pos4

		//back face
		{Vector3D(0.5f, -0.5f, 0.5f),	lightGray,	lightGray},		//pos5
		{Vector3D(0.5f, 0.5f, 0.5f),	lightGray,	lightGray},		//pos6
		{Vector3D(-0.5f, 0.5f, 0.5f),	lightGray,	lightGray},		//pos7
		{Vector3D(-0.5f, -0.5f, 0.5f),	lightGray,	lightGray},		//pos8

	};


	UINT size_list = ARRAYSIZE(vertex_list);
	this->vb = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	//this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		//front side
		0, 1, 2,	//first triangle
		2, 3, 0,	//2nd

		//back side
		4, 5, 6,	//3rd
		6, 7, 4,	//4th

		//top side
		1, 6, 5,
		5, 2, 1,

		//bottom side
		7, 0, 3,
		3, 4, 7,

		//right side
		3, 2, 5,
		5, 4, 3,

		//left side
		7, 6, 1,
		1, 0, 7
	};


	//index buffer
	UINT size_index_list = ARRAYSIZE(index_list);


	this->ib = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);
	//this->ib->load(index_list, size_index_list);

	//constant buffer
	constant cc;
	cc.m_time = 0;
	cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
//	cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	InputSystem::get()->removeListener(this);
	//this->vb->release();
	//this->cb->release();
	//this->ib->release();
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;
	//this->setRotation(rotSpeed, rotSpeed, rotSpeed);

	if (InputSystem::get()->isKeyDown('R'))
	{
		this->resetProperties();
		std::cout << "Properties has been reset" << std::endl;
	}

	if (InputSystem::get()->isKeyDown('1'))
	{
		this->animation = 1;
		std::cout << "Horizontal" << std::endl;
	}
	else if (InputSystem::get()->isKeyDown('2'))
	{
		this->animation = 2;
		std::cout << "Vertical" << std::endl;
	}
	else if (InputSystem::get()->isKeyDown('3'))
	{
		this->animation = 3;
		std::cout << "Diagonal 1" << std::endl;
	}
	else if (InputSystem::get()->isKeyDown('4'))
	{
		this->animation = 4;
		std::cout << "Diagonal 2" << std::endl;
	}
}

void Cube::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	constant cc;

	this->deltaPos += EngineTime::getDeltaTime();


	/*if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}*/
	/*else {
		this->deltaPos += this->deltaTime * 0.1f;
	}*/


	this->deltaScale += EngineTime::getDeltaTime() / 2.0f;

	Matrix4x4 scale, rotX, rotY, rotZ, translation, world, temp;
	
	scale.setIdentity();
	//scale.setScale(Vector3D::lerp(Vector3D(0.8f, 0.8f, 0.8f), Vector3D(2.5, 2.5, 0.0001), (sin(this->deltaScale) + 1.0f) / 2.0f));
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

	//switch (this->animation)
	//{
	//	case 1:
	//		translation.setTranslation(Vector3D::lerp(Vector3D(-1.5, 0, 0), Vector3D(1.5, 0, 0), (sin(this->deltaPos) + 1.0f) / 2.0f));
	//		break;

	//	case 2:
	//		translation.setTranslation(Vector3D::lerp(Vector3D(0, -1.5, 0), Vector3D(0, 1.5, 0), (sin(this->deltaPos) + 1.0f) / 2.0f));
	//		break;

	//	case 3:
	//		translation.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5, 1.5, 0), (sin(this->deltaPos) + 1.0f) / 2.0f));
	//		break;

	//	case 4:
	//		translation.setTranslation(Vector3D::lerp(Vector3D(-1.5, 1.5, 0), Vector3D(1.5, -1.5, 0), (sin(this->deltaPos) + 1.0f) / 2.0f));
	//		break;

	//}
	//std::cout << this->ticks << std::endl;

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

void Cube::setAnimationSpeed(float speed)
{
	this->speed = speed;
}

void Cube::onKeyDown(int key)
{

	//float rotX, rotY, rotZ;
	//rotX = this->getLocalRotation().m_x;
	//rotY = this->getLocalRotation().m_y;
	//rotZ = this->getLocalRotation().m_z;
	//float offset = 3.0f;

	//if (key == 'W') {
	//	rotX += EngineTime::getDeltaTime() * this->speed * offset;
	//	rotY += EngineTime::getDeltaTime() * this->speed * offset;
	//}
	//else if (key == 'S') {
	//	rotX -= EngineTime::getDeltaTime() * this->speed * offset;
	//	rotY -= EngineTime::getDeltaTime() * this->speed * offset;
	//}

	//this->setRotation(rotX, rotY, rotZ);
}

void Cube::onKeyUp(int key)
{
}

void Cube::onMouseMove(const Point& mousePos)
{
}

void Cube::onLeftMouseDown(const Point& mousePos)
{
}

void Cube::onLeftMouseUp(const Point& mousePos)
{
}

void Cube::onRightMouseDown(const Point& mousePos)
{
}

void Cube::onRightMouseUp(const Point& mousePos)
{
}

void Cube::resetProperties()
{
	this->setPosition(Vector3D(0, 0, 0));
	float radians = -270 * (3.14f / 180.0f);	//flip the circle so that it faces the camera
	this->setRotation(Vector3D(radians, 0.0f, 0.0f));
//	this->setRotation(Vector3D(radians, 0, 0));
	this->setScale(Vector3D(1, 1, 1));
	//Matrix4x4 translation;
	//translation.setIdentity();
}
