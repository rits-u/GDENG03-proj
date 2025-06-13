#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Camera.h"

using namespace std;

class VertexShader;
class PixelShader;

class GameObject
{

public:
	GameObject(string name);
	~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vs, PixelShader* ps, Camera* canmera) = 0;
	//virtual void draw_(int width, int height, VertexShader* vs, PixelShader* ps) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	string getName();

	struct vertex {
		Vector3D position;
	//	float padding;
		Vector3D color;
		Vector3D color2;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		float time;
		float padding[3]; // for 16-byte alignment
	};

protected:
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

};

