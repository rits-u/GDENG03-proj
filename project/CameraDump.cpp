#include "CameraDump.h"

CameraDump::CameraDump()
{
	this->m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	this->m_target = XMVectorSet(0.0f, 0.0f, 0.0, 0.0f);
}
CameraDump::~CameraDump()
{
}

void CameraDump::SetPosition(float x, float y, float z)
{
	this->m_pos = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void CameraDump::SetTarget(float x, float y, float z)
{
	this->m_target = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void CameraDump::SetUp(float x, float y, float z)
{
	this->m_up = XMVectorSet(x, y, z, 0.0f);
	UpdateViewMatrix();
}

void CameraDump::SetPerspective(float fovY, float aspect, float zn, float zf)
{
	this->m_fovY = fovY;
	this->m_aspectRatio = aspect;
	this->m_nearZ = zn;
	this->m_farZ = zf;

	m_projMatrix = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
}

void CameraDump::SetOrtho(float width, float height, float zn, float zf)
{
	this->m_projMatrix = XMMatrixOrthographicLH(width, height, zn, zf);
}

void CameraDump::UpdateViewMatrix()
{
	m_viewMatrix = XMMatrixLookAtLH(m_pos, m_target, m_up);
}

DirectX::XMMATRIX CameraDump::GetViewMatrix() const
{
	return this->m_viewMatrix;
}

DirectX::XMMATRIX CameraDump::GetProjMatrix() const
{
	return this->m_projMatrix;
}

DirectX::XMMATRIX CameraDump::GetViewProjMatrix() const
{
	return m_viewMatrix * m_projMatrix;
}
