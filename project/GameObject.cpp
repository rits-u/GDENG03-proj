#include "GameObject.h"
#include "Vector3D.h"

GameObject::GameObject(String name)
{
    this->name = name;
    //this->localPosition = Vector3D::zeros();
    //this->localScale = Vector3D::ones();
    //this->localRotation = Vector3D::zeros();
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
    this->transform.localPosition = Vector3D(x, y, z);
}

void GameObject::setPosition(Vector3D pos)
{
    this->transform.localPosition = pos;
}

Vector3D GameObject::getPosition()
{
    return this->transform.localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
    this->transform.localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
    this->transform.localScale = scale;
}

Vector3D GameObject::getScale()
{
    return this->transform.localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
    this->transform.localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
    this->transform.localRotation = rot;
}

Vector3D GameObject::getRotation()
{
    return this->transform.localRotation;
}

Matrix4x4 GameObject::getWorldMatrix()
{
   return this->transform.getLocalMatrix();
}

MyTransform GameObject::getTransform()
{
    return this->transform;
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

String GameObject::getName()
{
    return this->name;
}

//void GameObject::setMesh(MeshPtr mesh)
//{
//    this->mesh = mesh;
//}
