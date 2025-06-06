#include "AppWindow.h"
#include <Windows.h>
#include "DrawManager.h"
#include <vector>
#include <iostream>
#include "Vertex.h"

//struct vec3
//{
//	float x, y, z;
//};
//
//struct vertex
//{
//	vec3 position;
//	vec3 position1;
//	vec3 color;
//	vec3 color1;
//};

//__declspec(align(16))
//struct constant
//{
//	unsigned int m_time;
//};


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();

	DrawManager::getInstance()->initialize();
//	std::cout << "Debug message" << std::endl;

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	std::vector<Vertex::vertex> A_list =
	{
		//pos - pos1 - color - color1
		{-0.2f, 0.0f, 0.0f,		-0.32f, -0.11f, 0.0f,	0,0,0,	0,1,0},		//pos1
		{-0.2f, 0.8f, 0.0f,		-0.11f, 0.78f, 0.0f,	1,1,0,	0,1,1},		//pos2
		{0.6f, 0.0f, 0.0f,		0.75f, -0.73f, 0.0f,	0,0,1,	1,0,0},		//pos3
		{0.6f, 0.8f, 0.0f,		0.88f, 0.77f, 0.0f,		1,1,1,	0,0,1}		//pos4
	};

	std::vector<Vertex::vertex> B_list =
	{
		{-0.8f, -0.8f, 0.0f,	-0.32f, -0.11f, 0.0f,	1,0,0,	0,1,0},		//pos1
		{-0.8f, -0.3f, 0.0f,	-0.11f, 0.78f, 0.0f,	1,1,0,	0,1,1},		//pos2
		{-0.3f, -0.8f, 0.0f,	0.75f, -0.73f, 0.0f,	1,0,0,	1,0,0},		//pos3
		{-0.3f, -0.3f, 0.0f,	0.88f, 0.77f, 0.0f,		1,0,1,	0,0,1},		//pos4
	};

	std::vector<Vertex::vertex> C_list =
	{
		{0.5f, -0.6f, -0.1f,		-0.32f, -0.11f, 0.0f,	0,0,0,	1,0,0},		//pos1
		{0.5f, -0.1f, -0.1f,		-0.11f, 0.78f, 0.0f,	1,0.5f,1,	1,0.5f,1},		//pos2
		{0.8f, -0.6f, 0.9f,		0.7f, -0.73f, 0.0f,		1.3f,0,0,	1.3f,0,0},		//pos3
		{0.8f, -0.1f, 0.9f,		0.8f, 0.77f, 0.0f,		0,0,1,	1,0,1},		//pos4


	};


	Quad A(A_list);
	DrawManager::getInstance()->addQuad(A);
	
	Quad B(B_list);
	DrawManager::getInstance()->addQuad(B);

	Quad C(C_list);
	DrawManager::getInstance()->addQuad(C);


	DrawManager::getInstance()->setUpShadersAndBuffers(m_vb, m_cb, m_vs, m_ps);
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1); // 1 0 0 1
	//GraphicsEngine::get()->getImmediateDeviceContext()->ClearDepthStencilView();


	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	DrawManager::getInstance()->updateShadersAndBuffers(m_vb, m_cb, m_vs, m_ps);

	DrawManager::getInstance()->drawAllQuads(m_vb);

	m_swap_chain->present(false);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
