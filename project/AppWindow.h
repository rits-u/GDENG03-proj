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

#include "Cube.h"
#include "Plane.h"
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
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

public:
	Camera* camera;
	//Cube* cubeObject;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

private:
	std::vector<Cube*> cubeList;
	std::vector<Plane*> planeList;


private:
	void adjustSpeed();
	float generateRandomFloat(float min, float max);

};

