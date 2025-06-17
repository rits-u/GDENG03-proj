#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "EngineTime.h"

#include <DirectXMath.h>
using namespace DirectX;

class Plane : public GameObject
{
public:
	Plane(string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vs, PixelShader* ps) override;

	void setAnimationSpeed(float speed);

//public:
	//VertexBuffer* vb;
	//IndexBuffer* ib;
	//ConstantBuffer* cb;

private:
	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float deltaScale = 0.0f;
	float speed = 10.0f;
};

