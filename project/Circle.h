#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "EngineTime.h"

#include "Matrix4x4.h"
#include "InputListener.h"

#include <DirectXMath.h>
using namespace DirectX;


class Circle : public GameObject, public InputListener
{
public:
	Circle(string name, void* shaderByteCode, size_t sizeShader, int numSegment, int radius);
	~Circle();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) override;

	void setAnimationSpeed(float speed);

	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	//MOUSE pure virtual callback functions
	virtual void onMouseMove(const Point& mousePos);
	virtual void onLeftMouseDown(const Point& mousePos);
	virtual void onLeftMouseUp(const Point& mousePos);
	virtual void onRightMouseDown(const Point& mousePos);
	virtual void onRightMouseUp(const Point& mousePos);

	//public:
	//	VertexBuffer* vb;
	//	IndexBuffer* ib;
	//	ConstantBuffer* cb;

public:
	float forward = 0.0f;
	float rightward = 0.0f;

private:
	VertexBufferPtr vb;
	IndexBufferPtr ib;
	ConstantBufferPtr cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float deltaScale = 0.0f;
	float speed = 10.0f;
	float accumulatedTime = 0.0f;

	Matrix4x4 m_worldCamera;

};

