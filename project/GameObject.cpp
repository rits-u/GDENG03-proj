#include "GameObject.h"
#include "Vector3D.h"

GameObject::GameObject(string name)
{
    this->name = name;
    this->localPosition = Vector3D::zeros();
    this->localScale = Vector3D::ones();
    this->localRotation = Vector3D::zeros();
    this->layer = Layer::DEFAULT;
    this->enabled = true;
}

GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
}

void GameObject::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{
}

void GameObject::setPosition(float x, float y, float z)
{
    this->localPosition = Vector3D(x, y, z);
}

void GameObject::setPosition(Vector3D pos)
{
    this->localPosition = pos;
}

Vector3D GameObject::getLocalPosition()
{
    return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
    this->localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
    this->localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
    return this->localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
    this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
    this->localRotation = rot;
}

Vector3D GameObject::getLocalRotation()
{
    return this->localRotation;
}

void GameObject::setLayer(unsigned int layer)
{
    this->layer = layer;
}

unsigned int GameObject::getLayer()
{
    return this->layer;
}

void GameObject::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

bool GameObject::isEnabled()
{
    return this->enabled;
}

string GameObject::getName()
{
    return this->name;
}
