#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "EngineTime.h"

#include "Matrix4x4.h"

#include <DirectXMath.h>
using namespace DirectX;


class Cube : public GameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vs, PixelShader* ps) override;

	void setAnimationSpeed(float speed);

//public:
//	VertexBuffer* vb;
//	IndexBuffer* ib;
//	ConstantBuffer* cb;

public:
	float forward = 0.0f;
	float rightward = 0.0f;

private:
	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float deltaScale = 0.0f;
	float speed = 10.0f;
	float accumulatedTime = 0.0f;

	Matrix4x4 m_worldCamera;

};

