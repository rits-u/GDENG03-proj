#pragma once
#include <string>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
#include "Types.h"
//#include "Camera.h"

//using namespace std;

class VertexShader;
class PixelShader;

	enum Layer : unsigned int {
		DEFAULT = 1 << 0,
		UI = 1 << 2,
		DEBUG = 1 << 1,
	};

/*
	bitmask with DEFAULT and DEBUG
	0 0 0 0   0 0 1 1

	with UI
	0 0 0 0   0 1 0 0

	DEFAULT ONLY
	0 0 0 0   0 0 0 1
*/



class GameObject
{

public:
	GameObject(String name);
	~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) = 0;
	virtual void updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex) = 0;
	//virtual void updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex) = 0;
	virtual void render() = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setLayer(unsigned int layer);
	unsigned int getLayer();

	void setEnabled(bool enabled);
	bool isEnabled();

	String getName();

	//void setMesh(MeshPtr mesh);

	//struct vertex {
	//	Vector3D position;
	////	float padding;
	//	Vector3D color;
	//	Vector3D color2;
	//};
	struct vertex {
		Vector3D position;
		Vector2D texCoord;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		float m_time;
		float useWireColor; //1 for true, //0 for false
		//float padding[3]; // for 16-byte alignment
		float padding[2];
		//float wireColor[4];
		Vector4D wireColor;
	};




protected:
	String name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	unsigned int layer;
	bool enabled;
	//MeshPtr mesh;
	//float rotX;
	//float rotY;
	//float royZ;

};

