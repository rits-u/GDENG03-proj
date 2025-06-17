#include "Camera.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

#include "InputSystem.h"
#include "EngineTime.h"

#include <iostream>

Camera::Camera(string name) : GameObject(name)
{
	this->setPosition(0.0f, 0.0f, -4.0f);
	InputSystem::get()->addListener(this);
	//this->m_position.setTranslation
}

Camera::~Camera()
{
}

//void Camera::setCamPosition(const Vector3D& pos)
//{
//	m_position = pos;
////	m_viewDirty = true;
//}
//
//void Camera::setCamRotation(const Vector3D& rot)
//{
//	m_rotation = rot;
//	//m_viewDirty = true;
//}
//
//Vector3D Camera::getCamPosition()
//{
//    return this->m_position;
//}
//
//Vector3D Camera::getCamRotation()
//{
//	return this->m_rotation;
//}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	if (InputSystem::get()->isKeyDown('W'))
	{
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('S'))
	{
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('A'))
	{
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('D'))
	{
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::draw(int width, int height, VertexShader* vs, PixelShader* ps)
{
}

Matrix4x4 Camera::getViewMatrix()
{
   // if (m_viewDirty) 
	updateViewMatrix();
	return this->localMatrix;
   // return m_viewMatrix;
}

void Camera::updateViewMatrix()
{
	Vector3D rotation = this->getLocalRotation();
	Vector3D position = this->getLocalPosition();
	Vector3D newPos;

	Matrix4x4 world_cam, rotX, rotY, pos;
	world_cam.setIdentity();

	rotX.setIdentity();
	rotX.setRotationX(rotation.m_x);
	world_cam *= rotX;

	rotY.setIdentity();
	rotY.setRotationY(rotation.m_y);
	world_cam *= rotY;

	position = this->worldCamera.getTranslation() + this->worldCamera.getZDirection() * (this->forward * 0.05f);
	position = position + this->worldCamera.getXDirection() * (this->rightward * 0.05f);
	world_cam.setTranslation(position);


	//pos.setIdentity();
	//pos.setTranslation(position);
	//world_cam *= pos;

	//Vector3D newPos = m_worldCamera.getTranslation() + m_worldCamera.getZDirection() * (forward * 0.3f);
	//newPos = newPos + m_worldCamera.getXDirection() * (rightward * 0.3f);

	//world_cam.setTranslation(Vector3D(0, 0, -2));

	//world_cam.setTranslation(newPos);
	//this->worldCamera = world_cam;
	world_cam.inverse();
	this->localMatrix = world_cam;
	//world_cam.inverse();

//	this->m_viewMatrix = world_cam;
//	m_viewDirty = false;
}
void Camera::setWidthAndHeight(int width, int height)
{
	this->width = width;
	this->height = height;
}
//Matrix4x4 Camera::getPerspective(int width, int height)
//{
//	m_projMatrix.setPerspectiveFovLH(1.57f, ((float)(width / (float)height)), 0.1f, 100.0f);
//	return m_projMatrix;
//}

void Camera::onKeyDown(int key)
{
	/*if (key == 'W')
		std::cout << "hi haha" << std::endl;

	
	if (InputSystem::get()->isKeyDown('W')) {
		std::cout << "yes cuh" << std::endl;
	}
	else if (InputSystem::get()->isKeyUp('W')) {
		std::cout << "no" << std::endl;
	}*/
}
void Camera::onKeyUp(int key)
{
}
void Camera::onMouseMove(const Point& mousePos)
{
	/*RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;*/

	//float rotX = cubeList[0]->getLocalRotation().m_x;
	//float rotY = cubeList[0]->getLocalRotation().m_y;
	//float rotZ = cubeList[0]->getLocalPosition().m_z;
	Vector3D rotation = this->getLocalRotation();
	float rotX = rotation.m_x;
	float rotY = rotation.m_y;
	float rotZ = rotation.m_z;
	float offset = 0.05f;

	//rotX -= deltaMousePos.m_y * EngineTime::getDeltaTime() * offset;
	//rotY -= deltaMousePos.m_x * EngineTime::getDeltaTime() * offset;

	rotX += (mousePos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * offset;
	rotY += (mousePos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * offset;
	//float x_temp = mousePos.m_x;
	//float y_temp = mousePos.m_y;

	//float speed = 0.005f;
	//rotX += y_temp * speed;
	//rotY += x_temp * speed;
	std::cout << width << std::endl;
	this->setRotation(rotX, rotY, rotZ);
	this->updateViewMatrix();

	//cubeList[0]->setRotation(rotX, rotY, rotZ);

//	Vector3D rotation = Vector3D(rotX, rotY, rotZ);
	//camera->setCamRotation(rotation);

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}
void Camera::onLeftMouseDown(const Point& mousePos)
{
}
void Camera::onLeftMouseUp(const Point& mousePos)
{
}
void Camera::onRightMouseDown(const Point& mousePos)
{
}
void Camera::onRightMouseUp(const Point& mousePos)
{
}
//
//float Camera::getForward()
//{
//	return this->forward;
//}
//
//void Camera::setForward(float forward)
//{
//	this->forward = forward;
//}
//
//float Camera::getRightward()
//{
//	return this->rightward;
//}
//
//void Camera::setRightward(float rightward)
//{
//	this->rightward = rightward;
//}

//Vector3D Camera::getZDirection()
//{
//    Matrix4x4 rot;
//    rot.setIdentity();
//    return rot.getXDirection();
//   // rot.setCamRotation(m_rotation, true);
// //   return Vector3D(rot.m_mat[2][0], rot.m_mat[2][1], rot.m_mat[2][2]);
//}
