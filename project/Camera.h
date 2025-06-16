#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"

class Camera
{
public:
	Camera();
	~Camera();
	
	void setCamPosition(const Vector3D& pos);
	void setCamRotation(const Vector3D& rot);

	Vector3D getCamPosition();
	Vector3D getCamRotation();

	Matrix4x4 getViewMatrix();
	void updateViewMatrix();

	//float getForward();
	//void setForward(float forward);
	//float getRightward();
	//void setRightward(float rightward);


public:
	float forward = 0.0f;
	float rightward = 0.0f;
	Matrix4x4 worldCamera;


private:
	Vector3D m_position;
	Vector3D m_rotation;

	//Matrix4x4 m_worldCamera;
	Matrix4x4 m_viewMatrix;
	bool m_viewDirty = true;


};

//	void 


