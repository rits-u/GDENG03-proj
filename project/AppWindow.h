#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "InputListener.h"
#include "Point.h"

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Camera.h"

#include <iostream>
#include <vector>
#include <random>

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mousePos) override;
	virtual void onLeftMouseDown(const Point& mousePos) override;
	virtual void onLeftMouseUp(const Point& mousePos) override;
	virtual void onRightMouseDown(const Point& mousePos) override;
	virtual void onRightMouseUp(const Point& mousePos) override;

private:
	//void adjustSpeed();
	float generateRandomFloat(float min, float max);
	void spawnCircle(void* shader_byte_code, size_t size_shader, Vector3D color, float goUp, float goDown, float speed);


public:
	//Cube* cubeObject;
	//Camera* camera;

private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;

private:
	std::vector<Cube*> cubeList;
	std::vector<Plane*> planeList;
	std::vector<Circle*> circleList;


};

