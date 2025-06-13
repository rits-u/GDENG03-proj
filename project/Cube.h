#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "EngineTime.h"

class Cube : public GameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vs, PixelShader* ps) override;
	void draw_(int width, int height, VertexShader* vs, PixelShader* ps) override;

	void setAnimSpeed(float speed);

public:
	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;

private:
	//VertexBuffer* vb;
	//IndexBuffer* ib;
	//ConstantBuffer* cb;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float deltaScale = 0.0f;
	float speed = 10.0f;
	float accumulatedTime = 0.0f;
};

