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

#include "Cube.h"

#include <iostream>
#include <vector>
#include <random>

class AppWindow : public Window
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	Cube* cubeObject;

private:
	SwapChain* m_swap_chain;
	//VertexBuffer* m_vb;
	//IndexBuffer* m_ib;
	//ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

private:
	double accumulatedTime;
	float speed;
	bool increaseSpeed;
	float delta_pos;
	float delta_scale;
	std::vector<Cube*> cubeList;


//private:
//	float m_old_delta;
//	float m_new_delta;
//	float m_delta_time;

private:
	void adjustSpeed();
	float generateRandomFloat(float min, float max);

};

