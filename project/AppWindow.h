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

#include "UIManager.h"
#include "GameObjectManager.h"

#include "Types.h"

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

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
	void createCamera(Layer layer, float depth, bool enabled);


private:
	SwapChainPtr m_swap_chain;
	bool holding = false;
	std::vector<Camera*> sortedCameras;

};

