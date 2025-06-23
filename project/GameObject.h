#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "CameraDump.h"
#include "Prerequisites.h"
//#include "Camera.h"

using namespace std;

class VertexShader;
class PixelShader;

enum Layer : uint32_t {
	DEFAULT = 1 << 0,
	UI = 1 << 1,
	ENEMY = 1 << 2,
	PLAYER = 1 << 3,
	DEBUG = 1 << 4,
};

class GameObject
{

public:
	GameObject(string name);
	~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) = 0;
	virtual void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, Matrix4x4 cameraViewMatrix) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setLayer(uint32_t layer);
	uint32_t getLayer();

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
		float m_time;
		float padding[3]; // for 16-byte alignment
	};



protected:
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	uint32_t layer = Layer::DEFAULT;
	//float rotX;
	//float rotY;
	//float royZ;

};

