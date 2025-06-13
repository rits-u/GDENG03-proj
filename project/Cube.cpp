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

void Cube::draw(int width, int height, VertexShader* vs, PixelShader* ps, Camera* camera)
{
	constant cc;

	deltaPos += EngineTime::getDeltaTime() / 8.0f;


	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	cc.time = this->ticks / 1000;


	//deltaScale += EngineTime::getDeltaTime() / 0.85f;

	Matrix4x4 scale, rotX, rotY, rotZ, translation, world;
	scale.setScale(this->getLocalScale());

	Vector3D rotation = this->getLocalRotation();

	rotX.setIdentity();
	rotX.setRotationX(rotation.m_x);

	rotY.setIdentity();
	rotY.setRotationY(rotation.m_y);

	rotZ.setIdentity();
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


	//Matrix4x4 view, projection;
	//XMStoreFloat4x4((XMFLOAT4X4*)&cc.m_view, XMMatrixTranspose(camera->GetViewMatrix()));
	//XMStoreFloat4x4((XMFLOAT4X4*)&cc.m_proj, XMMatrixTranspose(camera->GetProjMatrix()));

	//XMMATRIX xmView = camera->GetViewMatrix();
	//XMMATRIX xmProj = camera->GetProjMatrix();

	//XMMATRIX transposedView = XMMatrixTranspose(xmView);
	//XMMATRIX transposedProj = XMMatrixTranspose(xmProj);

	//// Copy manually from transposedView to cc.m_view (assuming row-major layout)
	//memcpy(&cc.m_view, &transposedView, sizeof(Matrix4x4));
	//memcpy(&cc.m_proj, &transposedProj, sizeof(Matrix4x4));


	//Matrix4x4 view, projection;
	//XMMATRIX view = XMMatrixTranspose(camera->GetViewMatrix());
	//XMMATRIX proj = XMMatrixTranspose(camera->GetProjMatrix());
	//Matrix4x4::XMMatrixToMatrix4x4(view, cc.m_view);
	//Matrix4x4::XMMatrixToMatrix4x4(proj, cc.m_proj);




	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);
	///////cc.m_proj.setPerspectiveFovLH(1.5708f, (float)width / (float)height, 0.1f, 100.0f);


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
