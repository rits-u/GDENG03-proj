#include "Model.h"

Model::Model(String name, MeshPtr mesh, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	//RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	////InputSystem::get()->addListener(this);
	//this->setMesh(mesh);

	//constant cc;
	//cc.m_time = 0;
	//this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));

	//this->setPosition(0.0f, 0.0f, 0.0f);
	//this->setScale(1.0f, 1.0f, 1.0f);
	//this->setRotation(0.0f, 0.0f, 0.0f);
	//this->ib = mesh->getIndexBuffer();
	//this->vb = mesh->getVertexBuffer();
}

//Model::Model(String name, void* shaderByteCode, size_t sizeShader)
//{
//	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
//	InputSystem::get()->addListener(this);
//
//	if (name == "Teapot") {
//		MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj", shaderByteCode, &sizeShader);
//	}
//
//
//
//
//	this->setMesh(mesh);
//
//	constant cc;
//	cc.m_time = 0;
//	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
//
//	this->setPosition(0.0f, 0.0f, 0.0f);
//	this->setScale(1.0f, 1.0f, 1.0f);
//	this->setRotation(0.0f, 0.0f, 0.0f);
//	this->setLayer(this->getLayer() | Layer::DEBUG);
//	this->ib = mesh->getIndexBuffer();
//	this->vb = mesh->getVertexBuffer();
//}

Model::~Model()
{
	//InputSystem::get()->removeListener(this);
}

void Model::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;
}

void Model::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{

}

void Model::updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex)
{
	//DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	//constant cc;

	//deltaPos += EngineTime::getDeltaTime() / 8.0f;


	//if (this->deltaPos > 1.0f) {
	//	this->deltaPos = 0.0f;
	//}
	//else {
	//	this->deltaPos += this->deltaTime * 0.1f;
	//}


	////deltaScale += EngineTime::getDeltaTime() / 0.85f;

	//Matrix4x4 scale, rotX, rotY, rotZ, translation, world;

	//scale.setIdentity();
	//scale.setScale(this->getLocalScale());

	////rotation
	//Vector3D rotation = this->getLocalRotation();
	//rotX.setIdentity();
	//rotX.setRotationX(rotation.m_x);

	//rotY.setIdentity();
	//rotY.setRotationY(rotation.m_y);

	//rotZ.setIdentity();
	//rotZ.setRotationZ(rotation.m_z);

	////translation
	//translation.setIdentity();
	//translation.setTranslation(this->getLocalPosition());

	////matrix transformation
	//world.setIdentity();
	//world *= scale;
	//world *= rotX;
	//world *= rotY;
	//world *= rotZ;
	//world *= translation;

	////update constant buffer

	//cc.m_world = world;
	//cc.m_time = this->ticks * 2000.0f;

	//Camera* cam = SceneCameraHandler::get()->getCameraByIndex(camIndex);
	//if (cam->cullingMask & Layer::DEBUG)
	//{
	//	cc.useWireColor = 1.0f;
	//	cc.wireColor = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
	//}
	//else {
	//	cc.useWireColor = 0.0f;
	//}

	//if (cam->cullingMask & Layer::UI)
	//{
	//	cc.m_view.setIdentity();
	//	cc.m_proj.setOrthoLH((float)width / 2.0f, (float)height / 2.0f, -1.0f, 1.0f);
	//}
	//else
	//{
	//	cc.m_view = cam->getViewMatrix();
	//	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(width / (float)height)), 0.1f, 100.0f);
	//}


	//this->cb->update(deviceContext, &cc);
	////cc.m_proj = camera->getPerspective(width, height);


	////set constant buffer
	//deviceContext->setConstantBuffer(vs, this->cb);
	//deviceContext->setConstantBuffer(ps, this->cb);

	////set index and vertex buffer
	//deviceContext->setIndexBuffer(this->ib);

	//if (this->vb)
	//	deviceContext->setVertexBuffer(this->vb);
	//else
	//	std::cout << "[ERROR] Vertex buffer is null!" << std::endl;
}

void Model::render()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	deviceContext->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

void Model::setAnimationSpeed(float speed)
{
}

void Model::setIsAnimated(bool animated)
{
}

//void Model::onKeyDown(int key)
//{
//}
//
//void Model::onKeyUp(int key)
//{
//}
//
//void Model::onMouseMove(const Point& mousePos)
//{
//}
//
//void Model::onLeftMouseDown(const Point& mousePos)
//{
//}
//
//void Model::onLeftMouseUp(const Point& mousePos)
//{
//}
//
//void Model::onRightMouseDown(const Point& mousePos)
//{
//}
//
//void Model::onRightMouseUp(const Point& mousePos)
//{
//}

void Model::setMesh(MeshPtr mesh)
{
	this->mesh = mesh;
}
