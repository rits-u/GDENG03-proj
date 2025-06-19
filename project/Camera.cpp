#include "Camera.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

#include "InputSystem.h"
#include "EngineTime.h"

#include <iostream>

Camera::Camera(string name) : GameObject(name)
{
	//this->setPosition(0.0f, 0.0f, -4.0f);
	this->worldCamera.setTranslation(Vector3D(0, 0, -2));
	InputSystem::get()->addListener(this);
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
		float moveSpeed = 10.0f;

		if (InputSystem::get()->isKeyDown('W'))
		{
			//z += deltaTime * moveSpeed;
			//this->setPosition(x, y, z);
			this->forward = 1.0f;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('S'))
		{
			//	z -= deltaTime * moveSpeed;
				//this->setPosition(x, y, z);
			this->forward = -1.0f;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('A'))
		{
			//	x += deltaTime * moveSpeed;
			//	this->setPosition(x, y, z);
			this->rightward = -1.0f;
			this->updateViewMatrix();
		}
		else if (InputSystem::get()->isKeyDown('D'))
		{
			//	x -= deltaTime * moveSpeed;
			//	this->setPosition(x, y, z);
			this->rightward = 1.0f;
			this->updateViewMatrix();
		}

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

		position = this->worldCamera.getTranslation() + this->worldCamera.getZDirection() * (this->forward * 0.005f);
		position = position + this->worldCamera.getXDirection() * (this->rightward * 0.005f);
		world_cam.setTranslation(position);
		this->setPosition(position.m_x, position.m_y, position.m_z);

		//pos.setIdentity();
		//pos.setTranslation(position);
		//world_cam *= pos;

		this->worldCamera = world_cam;
		world_cam.inverse();
		this->localMatrix = world_cam;
		//world_cam.inverse();

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
//void Camera::onMouseMove(const Point& mousePos)
//{
//	if (isNavigating) {
//		if (firstMouseMove)
//		{
//			last_mouse_pos = mousePos;
//			firstMouseMove = false;
//			InputSystem::get()->setCursorPosition(last_mouse_pos); // force center
//			return; // Skip the first frame to avoid snapping
//		}
//
//
//
//		Vector3D rotation = this->getLocalRotation();
//		float rotX = rotation.m_x;
//		float rotY = rotation.m_y;
//		float rotZ = rotation.m_z;
//		float offset = 0.05f;
//
//		rotX += (mousePos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * offset;
//		rotY += (mousePos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * offset;
//		//float x_temp = mousePos.m_x;
//		//float y_temp = mousePos.m_y;
//
//		//float speed = 0.005f;
//		//rotX += y_temp * speed;
//		//rotY += x_temp * speed;
//		//std::cout << width << std::endl;
//		this->setRotation(rotX, rotY, rotZ);
//		this->updateViewMatrix();
//		last_mouse_pos = mousePos;
//
//		InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
//	}
//}

void Camera::onMouseMove(const Point& mousePos)
{
	if (!isNavigating) return;

	//if (firstMouseMove)
	//{
	//	firstMouseMove = false;
	//	skipNextMouseMove = true;
	//	last_mouse_pos = Point(width / 2, height / 2);
	//	InputSystem::get()->setCursorPosition(last_mouse_pos); // force center
	//	return;
	//}

	float deltaX = (float)(mousePos.m_x - width / 2);
	float deltaY = (float)(mousePos.m_y - height / 2);

	Vector3D rotation = this->getLocalRotation();
	float offset = 0.05f;

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