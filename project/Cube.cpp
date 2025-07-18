#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector2D.h"
#include <DirectXMath.h>
#include "SceneCameraHandler.h"
#include "InputSystem.h"



Cube::Cube(String name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	InputSystem::get()->addListener(this);

	/*m_worldCamera.setIdentity();
	m_worldCamera.setTranslation(Vector3D(0, 0, -2));*/

	Vector3D white = Vector3D(1, 1, 1);

	//OLDDDDDD
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


	UINT size_list = ARRAYSIZE(vertex_list);
	this->vb = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	//this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	//OLDDDD
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


	//index buffer
	UINT size_index_list = ARRAYSIZE(index_list);


	this->ib = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);
	//this->ib->load(index_list, size_index_list);

	//constant buffer
	constant cc;
	cc.m_time = 0;
	cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
//	cb->load(&cc, sizeof(constant));

	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	this->setLayer(this->getLayer() | Layer::DEBUG);
}

Cube::~Cube()
{
	InputSystem::get()->removeListener(this);
	//this->vb->release();
	//this->cb->release();
	//this->ib->release();
	//GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;

	if(animated)
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);
}

void Cube::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
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

void Cube::updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex)
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
	cc.m_time = this->ticks * 2000.0f;

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


	cb->update(deviceContext, &cc);
	//cc.m_proj = camera->getPerspective(width, height);


	//set constant buffer
	deviceContext->setConstantBuffer(vs, this->cb);
	deviceContext->setConstantBuffer(ps, this->cb);

	//set index and vertex buffer
	deviceContext->setIndexBuffer(this->ib);
	deviceContext->setVertexBuffer(this->vb);

	//draw
//	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);

	//if (!cam->isEnabled) {
	//	this->render();
	//}

}

void Cube::setAnimationSpeed(float speed)
{
	this->speed = speed;
}

void Cube::setIsAnimated(bool animated)
{
	this->animated = animated;
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

void Cube::render()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}
