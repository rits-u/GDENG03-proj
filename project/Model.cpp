#include "Model.h"

Model::Model(String name, MeshPtr mesh, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	InputSystem::get()->addListener(this);
	this->setMesh(mesh);
}

Model::~Model()
{
}

void Model::update(float deltaTime)
{
}

void Model::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{
}

void Model::updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex)
{
}

void Model::render()
{
}

void Model::setAnimationSpeed(float speed)
{
}

void Model::setIsAnimated(bool animated)
{
}

void Model::onKeyDown(int key)
{
}

void Model::onKeyUp(int key)
{
}

void Model::onMouseMove(const Point& mousePos)
{
}

void Model::onLeftMouseDown(const Point& mousePos)
{
}

void Model::onLeftMouseUp(const Point& mousePos)
{
}

void Model::onRightMouseDown(const Point& mousePos)
{
}

void Model::onRightMouseUp(const Point& mousePos)
{
}
