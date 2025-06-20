#include "Circle.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "InputSystem.h"
#include <vector>

Circle::Circle(string name, void* shaderByteCode, size_t sizeShader, int numSegment, int radius, Vector3D color, bool goUp, bool goRight) : GameObject(name)
{
	//float randX = generateRandomFloat(0.0f, 1.0f);
	//float randY = generateRandomFloat(0.0f, 1.0f);

	//if (randX <= 0.5f) this->goUp = false;
	//else this->goUp = true;

	//if (randY <= 0.5f) this->goRight = false;
	//else this->goRight = true;

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	InputSystem::get()->addListener(this);

	//float upBoundary = 1.75f;
	//float rightBoundary = 2.52f;
//	this->goUp = goUp;
//	this->goRight = goRight;

//	this->checkDirection();



	std::vector<vertex> vertex_list;
	float r = color.m_x;
	float g = color.m_y;
	float b = color.m_z;

	vertex_list.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Vector3D(r, g, b), Vector3D(r, g, b) });

	for (int i = 0; i <= numSegment; i++) {
		float theta = (2.0f * 3.14159265f * i) / numSegment;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		vertex_list.push_back({ Vector3D(x, y, 0.0f), Vector3D(r, g, b), Vector3D(r, g, b) });
	}

	UINT size_list = vertex_list.size();
	this->vb = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	std::vector<unsigned int> index_list;

	for (int i = 1; i <= numSegment; i++) {
		index_list.push_back(0);        // Center
		index_list.push_back(i);        // Current edge
		index_list.push_back(i + 1);    // Next edge (wraps to 1 when i == segmentCount)
	}

	UINT size_index_list = index_list.size();

	this->ib = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);

	//constant buffer
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

	//float upBoundary = 1.75f;
	//float rightBoundary = 2.52f;

//	std::cout << "UP: " << this->goUp << std::endl;
	//std::cout << "RI: " << this->goRight << std::endl;

	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = this->speed;

	if (this->goUp)
	{
		y += deltaTime * moveSpeed;
	//	this->checkDirection(upBoundary, rightBoundary);
		std::cout << "y: " << y << std::endl;
		//std::cout << "move up " << std::endl;
	}
	else if(!this->goUp)
	{
		y -= deltaTime * moveSpeed;
	//	this->checkDirection(upBoundary, rightBoundary);
	//	this->setPosition(x, y, z);
	//	this->checkDirection();
		std::cout << "move down " << std::endl;
	}

	if (this->goRight)
	{
		x += deltaTime * moveSpeed;
	//	this->checkDirection(upBoundary, rightBoundary);
	//	this->setPosition(x, y, z);
	//	this->checkDirection();
		std::cout << "move right " << std::endl;
	}
	else
	{
		x -= deltaTime * moveSpeed;
	//	this->checkDirection(upBoundary, rightBoundary);
	//	this->setPosition(x, y, z);
	//	this->checkDirection();
		std::cout << "move left " << std::endl;
	}

	//if (InputSystem::get()->isKeyDown('W'))
	//{
	//	y += deltaTime * moveSpeed;
	//	this->setPosition(x, y, z);
	//}
	//else if (InputSystem::get()->isKeyDown('S'))
	//{
	//	y -= deltaTime * moveSpeed;
	//	this->setPosition(x, y, z);
	//}
	//else if (InputSystem::get()->isKeyDown('A'))
	//{
	//	x -= deltaTime * moveSpeed;
	//	this->setPosition(x, y, z);
	//}
	//else if (InputSystem::get()->isKeyDown('D'))
	//{
	//	x += deltaTime * moveSpeed;
	//	this->setPosition(x, y, z);
	//}

//	this->checkDirection(upBoundary, rightBoundary);
	//this->setPosition(x, y, z);
//	this->checkDirection(upBoundary, rightBoundary);

	this->setPosition(x, y, z);
	this->checkDirection();

	Vector3D newPos = this->getLocalPosition();
	//std::cout << "Position: " << newPos.m_x << " " << newPos.m_y << " " << newPos.m_z << std::endl;
	//std::cout << "GAGO: " << moveSpeed << std::endl;
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
	this->speed = speed;
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

void Circle::setDirection(bool goUp, bool goRight)
{
	this->goUp = goUp;
	this->goRight = goRight;
}

void Circle::checkDirection()
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;;

	float radius = 1.0f * this->getLocalScale().m_x; // circle radius * scale
	float upBoundary = 1.75f;
	float rightBoundary = 2.52f;
	float epsilon = 0.001f; // small buffer to prevent jitter

	//this->checkDirection(upBoundary, rightBoundary);

	//float scaledRadius = this->getLocalScale().m_x;

	if (y > upBoundary)	//if y position exceeds upper boundary, inverse its direction
	{
		this->goUp = false;

	}
	else if (y < -upBoundary)	//if y position exceeds bottom boundary, inverse its direction
	{
		this->goUp = true;
		std::cout << "test: " << -upBoundary << std::endl;
	}

	if (x > rightBoundary)	//if x position exceeds right boundary, inverse its direction
	{
		this->goRight = false;
	}
	else if (x < -rightBoundary)	//if x position exceeds left boundary, inverse its direction
	{
		this->goRight = true;
	}

	//if (y + radius >= upBoundary - epsilon)
	//	this->goUp = false;
	//else if (y - radius <= -upBoundary + epsilon)
	//	this->goUp = true;

	//// Horizontal (X)
	//if (x + radius >= rightBoundary - epsilon)
	//	this->goRight = false;
	//else if (x - radius <= -rightBoundary + epsilon)
	//	this->goRight = true;
		
}
