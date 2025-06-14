#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

#include <DirectXMath.h>



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex vertex_list[] =
	{
		//CUBE
		//front face
		{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.0f, 0, 0)},		//pos1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1.0f,1.0f,0.0f),	Vector3D(1.5f, -0.5f,1)},		//pos2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1.0f,1.0f,0.0f),	Vector3D(0.5f, 1.0f,0)},		//pos3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1.0f,0.0f,0.0f),	Vector3D(1.5f, 0,1)},		//pos4

		//back face
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(1,1.0f, 0)},		//pos5
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, -0.5f)},		//pos6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, 0.5f)},		//pos7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(-1,-0.5f, 1)},		//pos8


	};


	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

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
	this->ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	this->ib->load(index_list, size_index_list);

	//constant buffer
	constant cc;
	cc.m_time = 0;
	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->vb->release();
	this->cb->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;
	//this->setRotation(rotSpeed, rotSpeed, rotSpeed);
}

void Cube::draw(int width, int height, VertexShader* vs, PixelShader* ps, Camera* camera)
{
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

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
	
	//scale
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
	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);
	///////cc.m_proj.setPerspectiveFovLH(1.5708f, (float)width / (float)height, 0.1f, 100.0f);
	cc.m_time = this->ticks * 2000.0f;
	cb->update(deviceContext, &cc);

//	std::cout << "time: " << cc.m_time << std::endl;

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
