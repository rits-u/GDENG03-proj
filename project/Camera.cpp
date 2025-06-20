#include "Camera.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

#include "InputSystem.h"
#include "EngineTime.h"

#include <iostream>

Camera::Camera(string name) : GameObject(name)
{
	//this->setPosition(0.0f, 0.0f, -4.0f);
	InputSystem::get()->addListener(this);
	this->worldCamera.setTranslation(Vector3D(0, 0, -2));
	this->updateViewMatrix();
	this->isNavigating = false;
}

Camera::~Camera()
{
	InputSystem::get()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	if (isNavigating) {
		Vector3D localPos = this->getLocalPosition();
		float x = localPos.m_x;
		float y = localPos.m_y;
		float z = localPos.m_z;
		float offset = 0.03f;

		if (InputSystem::get()->isKeyDown('W'))
		{
			//z += deltaTime * moveSpeed;
			//this->setPosition(x, y, z);
			this->forward = 1.0f * offset;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('S'))
		{
			//	z -= deltaTime * moveSpeed;
				//this->setPosition(x, y, z);
			this->forward = -1.0f * offset;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('A'))
		{
			//	x += deltaTime * moveSpeed;
			//	this->setPosition(x, y, z);
			this->rightward = -1.0f * offset;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('D'))
		{
			//	x -= deltaTime * moveSpeed;
			//	this->setPosition(x, y, z);
			this->rightward = 1.0f * offset;
			this->updateViewMatrix();
		}
	}

	if (InputSystem::get()->isKeyDown('R'))
	{
		this->resetCameraProperties();
		std::cout << "Camera has been reset" << std::endl;
		this->isNavigating = false;
	}
	
}

void Camera::draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	updateViewMatrix();
	return this->localMatrix;
}

void Camera::updateViewMatrix()
{
	if (isNavigating) {
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

		position = this->worldCamera.getTranslation() + this->worldCamera.getZDirection() * (this->forward);
		position = position + this->worldCamera.getXDirection() * (this->rightward);
		world_cam.setTranslation(position);
		this->setPosition(position.m_x, position.m_y, position.m_z);

		//pos.setIdentity();
		//pos.setTranslation(position);
		//world_cam *= pos;

		this->worldCamera = world_cam;
		world_cam.inverse();
		this->localMatrix = world_cam;
		//world_cam.inverse();

		//std::cout << "rotation: " << rotation.m_x << " " << rotation.m_y << " " << rotation.m_z << std::endl;
	}
}
void Camera::setWidthAndHeight(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Camera::onKeyDown(int key)
{
}
void Camera::onKeyUp(int key)
{
	this->rightward = 0.0f;
	this->forward = 0.0f;
}

void Camera::onMouseMove(const Point& mousePos)
{
	if (!isNavigating) return;

	float deltaX = (float)(mousePos.m_x - width / 2);
	float deltaY = (float)(mousePos.m_y - height / 2);

	Vector3D rotation = this->getLocalRotation();
	float offset = 0.08f;

	rotation.m_x += deltaY * EngineTime::getDeltaTime() * offset;
	rotation.m_y += deltaX * EngineTime::getDeltaTime() * offset;

	if (rotation.m_x > 1.5f) rotation.m_x = 1.5f;
	if (rotation.m_x < -1.5f) rotation.m_x = -1.5f;

	this->setRotation(rotation);
	this->updateViewMatrix();

	InputSystem::get()->setCursorPosition(Point(width / 2, height / 2));
}


void Camera::onLeftMouseDown(const Point& mousePos)
{
}

void Camera::onLeftMouseUp(const Point& mousePos)
{
}

void Camera::onRightMouseDown(const Point& mousePos)
{
	this->isNavigating = true;
	InputSystem::get()->showCursor(false);
}

void Camera::onRightMouseUp(const Point& mousePos)
{
	this->isNavigating = false;
	InputSystem::get()->showCursor(true);
}

void Camera::resetCameraProperties()
{
	this->worldCamera.setTranslation(Vector3D(0, 0, -2));
	this->setRotation(Vector3D(0, 0, 0));
	this->isNavigating = true;
	this->updateViewMatrix();
}
