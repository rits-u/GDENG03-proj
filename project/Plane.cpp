#include "Plane.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	vertex vertex_list[] =
	{
	/*	{ Vector3D(-0.5f, -0.5f, 0.0f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(-0.5f,  0.5f, 0.0f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(0.5f,  0.5f, 0.0f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(0.5f, -0.5f, 0.0f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) }*/

		{ Vector3D(-0.5f, 0.0f, -0.5f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(-0.5f,  0.0f, 0.5f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(0.5f,  0.0f, 0.5f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) },
		{ Vector3D(0.5f, 0.0f, -0.5f), Vector3D(1, 1, 1), Vector3D(1.0f, 1.0f, 1.0f) }

	};

	UINT size_list = ARRAYSIZE(vertex_list);
	this->vb = renderSystem->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	//this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	//unsigned int index_list[] =
	//{
	//	////front side
	//	//0, 1, 2,	//first triangle
	//	//2, 3, 0,	//2nd

	//	0, 1, 2,
	//	0, 2, 3
	//};

	//unsigned int index_list[] = {
	//	0, 2, 1,
	//	0, 3, 2
	//};

	unsigned int index_list[] = {
	0, 1, 2,
	0, 2, 3
	};


	//index buffer
	UINT size_index_list = ARRAYSIZE(index_list);
	this->ib = renderSystem->createIndexBuffer(index_list, size_index_list, renderSystem);
	//this->ib->load(index_list, size_index_list);

	//constant buffer
	constant cc;
	cc.m_time = 0;
	cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
	//cb->load(&cc, sizeof(constant));
}


Plane::~Plane()
{
	//this->vb->release();
	//this->cb->release();
	//this->ib->release();
	GameObject::~GameObject();
}

void Plane::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

}

void Plane::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
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

	//scale
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
	cc.m_time = this->ticks / 1000;
	cb->update(deviceContext, &cc);

	//set constant buffer
	deviceContext->setConstantBuffer(vs, this->cb);
	deviceContext->setConstantBuffer(ps, this->cb);

	//set index and vexter buffer
	deviceContext->setIndexBuffer(this->ib);
	deviceContext->setVertexBuffer(this->vb);

	//draw
	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);

}

void Plane::setAnimationSpeed(float speed)
{
}
