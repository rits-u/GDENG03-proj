#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex vertex_list[] =
	{
		//CUBE
		//front face
		{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1,0,0),	Vector3D(0.5f, 0, 0)},		//pos1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.5f, 0.5f,1)},		//pos2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.5f, 0.5f,0)},		//pos3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),	Vector3D(0.5f, 0,1)},		//pos4

		//back face
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.5f, 0)},		//pos5
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, 0.5f)},		//pos6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.5f, 0.5f)},		//pos7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.5f, 0)},		//pos8


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
	this->cb->release();
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

	//float accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * 1.0f;
	//accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * speed;

	//cc.time = this->ticks;
	cc.time = static_cast<unsigned int>(this->ticks * 1000); // convert seconds to milliseconds


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
	//Matrix4x4 rotMatrix;
	//rotMatrix.setIdentity();
	//rotMatrix *= zRot;
	//rotMatrix *= yRot;
	//rotMatrix *= xRot;

	//allMatrix = scaleMatrix * rotMatrix;
	//allMatrix.multiply(scaleMatrix, rotMatrix);
	//allMatrix *= translationMatrix;

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	temp = zRot; allMatrix *= temp;
	temp.setIdentity();
	temp = yRot; allMatrix *= temp;
	temp.setIdentity();
	temp = xRot; allMatrix *= temp;
	cc.m_world = allMatrix;

	deltaScale += this->deltaTime / 0.85f;

	//	Matrix4x4 temp;
		//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1, 1, 0), (sin(delta_scale)+1.0f)/2.0f));
		//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5, 1.5, 0), delta_pos));
		//cc.m_world *= temp;

		/*cc.worldMatrix.setScale(Vector3D(1, 1, 1));

		temp.setIdentity();
		temp.setRotationZ(deltaScale);
		cc.worldMatrix *= temp;

		temp.setIdentity();
		temp.setRotationY(deltaScale);
		cc.worldMatrix *= temp;

		temp.setIdentity();
		temp.setRotationX(deltaScale);
		cc.worldMatrix *= temp;*/


		//	cc.m_view.setIdentity();
			//cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);




	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);

	this->cb->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(vs, this->cb);
	deviceContext->setConstantBuffer(ps, this->cb);

	deviceContext->setIndexBuffer(this->ib);
	deviceContext->setVertexBuffer(this->vb);

	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

void Cube::draw_(int width, int height, VertexShader* vs, PixelShader* ps)
{

	//RECT rc = this->getClientWindowRect();
	//UINT width = rc.right - rc.left;
	//UINT height = rc.bottom - rc.top;

	constant cc;
	//adjustSpeed();
//	ticks += EngineTime::getDeltaTime() * 1000.0f * 5.0f;

	//	cc.m_world.setTranslation(Vector3D(0, 0, 0));

	deltaPos += EngineTime::getDeltaTime() / 8.0f;
	//delta_pos += m_delta_time * 1.0f;

	if (deltaPos > 1.0f)
		deltaPos = 0.0f;

	accumulatedTime += deltaTime / 1000.0f;
	//cc.time = this->accumulatedTime;
	//cc.time = static_cast<unsigned int>(this->ticks * 1000); // convert seconds to milliseconds
	cc.time = this->ticks / 1000;


	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), delta_pos));

	deltaScale += EngineTime::getDeltaTime() / 0.85f;
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1, 1, 0), (sin(delta_scale)+1.0f)/2.0f));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5, 1.5, 0), delta_pos));
	//cc.m_world *= temp;



	//Matrix4x4 temp;
	//temp.setIdentity();
	//Matrix4x4 scaleMatrix;
	//scaleMatrix.setScale(this->getLocalScale());

	////cc.m_world.setScale(Vector3D(1, 1, 1));
	//cc.m_world.setScale(this->getLocalScale());
	//temp.setTranslation(this->getLocalPosition());
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationZ(deltaScale);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationY(deltaScale);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationX(deltaScale);
	//cc.m_world *= temp;

	Matrix4x4 scale, rotX, rotY, rotZ, translation, world;
	scale.setScale(this->getLocalScale());

	Vector3D rotation = this->getLocalRotation();

	rotX.setIdentity();
	//rotX.setRotationX(deltaScale);
	rotX.setRotationX(rotation.m_x);

	rotY.setIdentity();
	//rotY.setRotationY(deltaScale);
	rotY.setRotationY(rotation.m_y);

	rotZ.setIdentity();
	//rotZ.setRotationZ(deltaScale);
	rotZ.setRotationZ(rotation.m_z);

	translation.setIdentity();
	translation.setTranslation(this->getLocalPosition());


	world.setIdentity();
	world *= scale;
	world *= rotX;
	world *= rotY;
	world *= rotZ;
	world *= translation;

	cc.m_world = world;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);



	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, this->cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, this->cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);

	
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
