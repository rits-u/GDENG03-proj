#pragma once
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "Mesh.h"

class Model : public GameObject, public InputListener
{
public:
	Model(String name, MeshPtr mesh, void* shaderByteCode, size_t sizeShader);
	~Model();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) override;
	void updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex) override;
	void render() override;

	void setAnimationSpeed(float speed);
	void setIsAnimated(bool animated);

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
	bool animated = false;
	//Matrix4x4 m_worldCamera;

};

