#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "InputListener.h"
#include "GameObject.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <string>

using namespace std;
class GameObject;

class Camera : public GameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();
	
	//void setCamPosition(const Vector3D& pos);
	//void setCamRotation(const Vector3D& rot);

	//Vector3D getCamPosition();
	//Vector3D getCamRotation();
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height, VertexShader* vs, PixelShader* ps) override;

	Matrix4x4 getViewMatrix();
	void updateViewMatrix();
	void setWidthAndHeight(int width, int height);

	//Matrix4x4 getPerspective(int width, int height);
	//float getForward();
	//void setForward(float forward);
	//float getRightward();
	//void setRightward(float rightward);


	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	//MOUSE pure virtual callback functions
	virtual void onMouseMove(const Point& mousePos);
	virtual void onLeftMouseDown(const Point& mousePos);
	virtual void onLeftMouseUp(const Point& mousePos);
	virtual void onRightMouseDown(const Point& mousePos);
	virtual void onRightMouseUp(const Point& mousePos);



public:
	//float forward = 0.0f;
	//float rightward = 0.0f;
	//Matrix4x4 worldCamera;


private:
	//Vector3D m_position;
	//Vector3D m_rotation;
	Matrix4x4 localMatrix;
	int height;
	int width;


	//Matrix4x4 m_worldCamera;
	//Matrix4x4 m_viewMatrix;
	//Matrix4x4 m_projMatrix;
	bool m_viewDirty = true;


};

//	void 


