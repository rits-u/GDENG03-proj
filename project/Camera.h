#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
private:
	XMVECTOR m_pos;
	XMVECTOR m_target;
	XMVECTOR m_up;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projMatrix;

	float m_fovY = DirectX::XM_PIDIV4; //45 degrees
	float m_aspectRatio = 1.0f;
	float m_nearZ = 0.1f;
	float m_farZ = 100.0f;

public:
	Camera();
	~Camera();
	void SetPosition(float x, float y, float z);
	void SetTarget(float x, float y, float z);
	void SetUp(float x, float y, float z);
	void SetPerspective(float fovY, float aspect, float zn, float zf);
	void SetOrtho(float width, float height, float zn, float zf);


	void UpdateViewMatrix();

	DirectX::XMMATRIX GetViewMatrix() const;
	DirectX::XMMATRIX GetProjMatrix() const;
	DirectX::XMMATRIX GetViewProjMatrix() const;
};

