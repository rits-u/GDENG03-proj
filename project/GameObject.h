#pragma once
#include <string>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
#include "Types.h"
#include "Constant.h"
#include "MyTransform.h"
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
	Vector3D getPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getRotation();
	Matrix4x4 getWorldMatrix();
	MyTransform getTransform();

	void setLayer(unsigned int layer);
	unsigned int getLayer();

	void setEnabled(bool enabled);
	bool isEnabled();

	String getName();




	struct vertex {
		Vector3D position;
		Vector2D texCoord;
	};



protected:
	String name;
	MyTransform transform;
	constant cc;
	unsigned int layer;
	bool enabled;
};

