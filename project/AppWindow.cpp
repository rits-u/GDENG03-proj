#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

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
//	std::cout << "Debug message" << std::endl;

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//triangle
		////X,     Y,    Z
		//{-0.5f, -0.5f, 0.0f},	//pos1
		//{0.0f, 0.5f, 0.0f},		//pos2
		//{0.5f, -0.5f, 0.0f}		//pos3

		//quad - triangle list
		//X,     Y,    Z
		//{-0.5f, -0.5f, 0.0f},		//pos1
		//{-0.5f, 0.5f, 0.0f},		//pos2
		//{0.5f,  0.5f, 0.0f},		//pos3

		//{0.5f, 0.5f, 0.0f},			//pos4
		//{0.5f, -0.5f, 0.0f},		//pos5
		//{-0.5f, -0.5f, 0.0f}		//pos6

		//quad - triangle strip
		//X,     Y,    Z
		{-0.5f, -0.5f, 0.0f},		//pos1
		{-0.5f, 0.5f, 0.0f},		//pos2
		{0.5f, -0.5f, 0.0f},		//pos3
		{0.5f, 0.5f, 0.0f},			//pos4

	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1); // 1 0 0 1

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//list mode
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	//strip mode
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	m_swap_chain->release();

	GraphicsEngine::get()->release();
}
