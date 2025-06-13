#include "Camera.h"

Camera::Camera()
{
	this->m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	this->m_target = XMVectorSet(0.0f, 0.0f, 0.0, 0.0f);
}
Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	this->m_pos = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void Camera::SetTarget(float x, float y, float z)
{
	this->m_target = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void Camera::SetUp(float x, float y, float z)
{
	this->m_up = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void Camera::SetPerspective(float fovY, float aspect, float zn, float zf)
{
	this->m_fovY = fovY;
	this->m_aspectRatio = aspect;
	this->m_nearZ = zn;
	this->m_farZ = zf;

	m_projMatrix = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
}

void Camera::SetOrtho(float width, float height, float zn, float zf)
{
	this->m_projMatrix = XMMatrixOrthographicLH(width, height, zn, zf);
}

void Camera::UpdateViewMatrix()
{
	m_viewMatrix = XMMatrixLookAtLH(m_pos, m_target, m_up);
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return this->m_viewMatrix;
}

DirectX::XMMATRIX Camera::GetProjMatrix() const
{
	return this->m_projMatrix;
}

DirectX::XMMATRIX Camera::GetViewProjMatrix() const
{
	return m_viewMatrix * m_projMatrix;
}
