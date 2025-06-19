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
	
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) override;

	Matrix4x4 getViewMatrix();
	void updateViewMatrix();
	void setWidthAndHeight(int width, int height);

	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	//MOUSE pure virtual callback functions
	virtual void onMouseMove(const Point& mousePos);
	virtual void onLeftMouseDown(const Point& mousePos);
	virtual void onLeftMouseUp(const Point& mousePos);
	virtual void onRightMouseDown(const Point& mousePos);
	virtual void onRightMouseUp(const Point& mousePos);



public:


private:
	Matrix4x4 localMatrix;
	int height;
	int width;
	bool isNavigating;
	bool firstMouseMove = true;
	Point last_mouse_pos;
	bool skipNextMouseMove = false;

	float forward = 0.0f;
	float rightward = 0.0f;
	Matrix4x4 worldCamera;

};

//	void 


