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
	void onFocus() override;
	void onKillFocus() override;
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point& deltaMousePos) override;
	void onLeftMouseDown(const Point& mousePos) override;
	void onLeftMouseUp(const Point& mousePos) override;
	void onRightMouseDown(const Point& mousePos) override;
	void onRightMouseUp(const Point& mousePos) override;

public:
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

