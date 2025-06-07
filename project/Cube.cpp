#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex vertex_list[] =
	{
		//CUBE
		//front face
		{Vector3D(-0.5f, -0.5f, -0.5f), 0, Vector3D(1,0,0),	Vector3D(0.2f, 0, 0)},		//pos1
		{Vector3D(-0.5f, 0.5f, -0.5f),  0, Vector3D(1,1,0),	Vector3D(0.2f, 0.2f,1)},		//pos2
		{Vector3D(0.5f, 0.5f, -0.5f),	0, Vector3D(1,1,0),	Vector3D(0.2f, 0.2f,0)},		//pos3
		{Vector3D(0.5f, -0.5f, -0.5f),	0, Vector3D(1,0,0),	Vector3D(0.2f, 0,1)},		//pos4

		//back face
		{Vector3D(0.5f, -0.5f, 0.5f),	0, Vector3D(0,1,0),	Vector3D(0,0.2f, 0)},		//pos5
		{Vector3D(0.5f, 0.5f, 0.5f),	0, Vector3D(0,1,1),	Vector3D(0,0.2f, 0.2f)},		//pos6
		{Vector3D(-0.5f, 0.5f, 0.5f),	0, Vector3D(0,1,1),	Vector3D(0,0.2f, 0.2f)},		//pos7
		{Vector3D(-0.5f, -0.5f, 0.5f),	0, Vector3D(0,1,0),	Vector3D(0,0.2f, 0)},		//pos8
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
	cc.time = 0;
	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->vb->release();
	this->ib->release();
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;
	this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	
}

void Cube::draw(int width, int height, VertexShader* vs, PixelShader* ps)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	constant cc = {};

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zRot; zRot.setRotationZ(rotation.m_z);
	Matrix4x4 xRot; xRot.setRotationX(rotation.m_x);
	Matrix4x4 yRot; yRot.setRotationY(rotation.m_y);

	Matrix4x4 temp;
	temp.setIdentity();

	//scale -> rotate -> transform
	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix *= zRot;
	rotMatrix *= yRot;
	rotMatrix *= xRot;

	//allMatrix = scaleMatrix * rotMatrix;
	allMatrix.multiply(scaleMatrix, rotMatrix);
	allMatrix *= translationMatrix;

	//Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	//temp = zRot; allMatrix *= temp;
	//temp.setIdentity();
	//temp = yRot; allMatrix *= temp;
	//temp.setIdentity();
	//temp = xRot; allMatrix *= temp;
	cc.worldMatrix = allMatrix;

	cc.viewMatrix.setIdentity();
	cc.projMatrix.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);

	this->cb->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(vs, this->cb);
	deviceContext->setConstantBuffer(ps, this->cb);

	deviceContext->setIndexBuffer(this->ib);
	deviceContext->setVertexBuffer(this->vb);

	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);


	//Matrix4x4 temp.setIdentity();
	//rotMatrix = rotMatrix.
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}


