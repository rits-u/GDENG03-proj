#include "MyTransform.h"

MyTransform::MyTransform()
{
	this->localPosition = Vector3D::zeros();
	this->localScale = Vector3D::ones();
	this->localRotation = Vector3D::zeros();
}

Matrix4x4 MyTransform::getLocalMatrix()
{
	this->localMatrix = calculateMatrix();
	return this->localMatrix;
}

Matrix4x4 MyTransform::calculateMatrix()
{
	Matrix4x4 scale, rotX, rotY, rotZ, translation, world;

	scale.setIdentity();
	scale.setScale(this->localScale);

	//rotation
	Vector3D rotation = this->localRotation;
	rotX.setIdentity();
	rotX.setRotationX(rotation.m_x);

	rotY.setIdentity();
	rotY.setRotationY(rotation.m_y);

	rotZ.setIdentity();
	rotZ.setRotationZ(rotation.m_z);

	//translation
	translation.setIdentity();
	translation.setTranslation(this->localPosition);

	//matrix transformation
	world.setIdentity();
	world *= scale;
	world *= rotX;
	world *= rotY;
	world *= rotZ;
	world *= translation;

	return world;
}
