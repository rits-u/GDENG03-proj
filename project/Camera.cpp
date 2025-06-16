#include "Camera.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

Camera::Camera()
{
	//this->m_position.setTranslation
}

Camera::~Camera()
{
}

void Camera::setCamPosition(const Vector3D& pos)
{
}

void Camera::setCamRotation(const Vector3D& rot)
{
    
}

Vector3D Camera::getCamPosition()
{
    return Vector3D();
}

Vector3D Camera::getCamRotation()
{
    return Vector3D();
}

Matrix4x4 Camera::getViewMatrix()
{
    if (m_viewDirty) updateViewMatrix();
    return m_viewMatrix;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 world_cam, rotX, rotY;
	world_cam.setIdentity();

	rotX.setIdentity();
	rotX.setRotationX(m_rotation.m_x);
	world_cam *= rotX;

	rotY.setIdentity();
	rotY.setRotationY(m_rotation.m_y);
	world_cam *= rotY;

	m_position = this->worldCamera.getTranslation() + this->worldCamera.getZDirection() * (this->forward * 0.3f);
	m_position = m_position + this->worldCamera.getXDirection() * (this->rightward * 0.3f);

	world_cam.setTranslation(m_position);

	//Vector3D newPos = m_worldCamera.getTranslation() + m_worldCamera.getZDirection() * (forward * 0.3f);
	//newPos = newPos + m_worldCamera.getXDirection() * (rightward * 0.3f);

	//world_cam.setTranslation(Vector3D(0, 0, -2));

	//world_cam.setTranslation(newPos);
	this->worldCamera = world_cam;

	world_cam.inverse();

	this->m_viewMatrix = world_cam;
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
