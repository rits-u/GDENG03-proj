#include "AppWindow.h"
#include <Windows.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	unsigned int m_time;          
	DirectX::XMMATRIX viewProj[4];   
};

//__declspec(align(16))
//struct constant
//{
//	unsigned int m_time;    // 4 bytes
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
//	std::cout << "Debug message" << std::endl;

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{

		//triangle w animation
		//{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,	0,0,0,	0,1,0},		//pos1
		//{0.5f, 0.5f, 0.0f,		-0.11f, 0.78f, 0.0f,	1,1,0,	0,1,1},		//pos2
		//{0.5f, -0.5f, 0.0f,		0.75f, -0.73f, 0.0f,	0,0,1,	1,0,0},		//pos3

		{-0.8f, -0.8f, 0.0f,	-0.32f, -0.11f, 0.0f,	0,0,0,	0,1,0},		//pos1
		{0.8f, 0.8f, 0.0f,		-0.11f, 0.78f, 0.0f,	1,1,0,	0,1,1},		//pos2
		{0.8f, -0.8f, 0.0f,		0.75f, -0.73f, 0.0f,	0,0,1,	1,0,0},		//pos3

	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	//GraphicsEngine::get()->createShaders();
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

//	std::cout << "hahahaha " << std::endl;


	//VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//old:
//	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	

	//if (FAILED(m_vs))
	//{
	//	wchar_t msg[128];
	//	swprintf(msg, 128, L"Failed to create vertex shader. HRESULT: 0x%08X\n");
	//	OutputDebugString(msg);
	//	//return false;
	//}


	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);			//vertex buffer

	GraphicsEngine::get()->releaseCompiledShader();


	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//GEOMETRY SHADER
	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "gsmain", &shader_byte_code, &size_shader);
	m_gs = GraphicsEngine::get()->createGeometryShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//INDEX BUFFER
	DWORD indices[3] = { 0, 1, 2 };
	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(&indices, sizeof(indices));


	constant cc;
	cc.m_time = 0;

	//CONSTANT BUFFER
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));


	//camera
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	//camera 1 - TOP LEFT
	cameras[0].SetPosition(0.0f, 0.0f, -1.5f);		//positioned at the center
	cameras[0].SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

	//camera 2 - TOP RIGHT
	cameras[1].SetPosition(0.0f, 4.0f, -3.0f);  //positioned a bit upwards, a bit far from origin
	cameras[1].SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

	//camera 3 - BOTTOM LEFT
	cameras[2].SetPosition(-8.0f, 10.0f, -10.0f);  //adjusted x y z coordinates
	cameras[2].SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

	//camera 4 - BOTTOM RIGHT
	cameras[3].SetPosition(-5.0f, 2.0f, -2.0f);  //adjusted x y z coordinates and modified camera eye/target
	cameras[3].SetTarget(0.1f, 1.5f, 0.0f);
	cameras[3].SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setMultipleViewPortSizes(rc.right - rc.left, rc.bottom - rc.top);

	constant cc;
	cc.m_time = ::GetTickCount();

	//hlsl file expects column-major matrices
	cc.viewProj[0] = XMMatrixTranspose(cameras[0].GetViewProjMatrix());
	cc.viewProj[1] = XMMatrixTranspose(cameras[1].GetViewProjMatrix());
	cc.viewProj[2] = XMMatrixTranspose(cameras[2].GetViewProjMatrix());
	cc.viewProj[3] = XMMatrixTranspose(cameras[3].GetViewProjMatrix());

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//set constant buffer for each shader
	//GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setTwoViewPortSize(rc.right - rc.left, rc.bottom - rc.top);
	

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_gs, m_cb);

	//set the default shader in the graphics pipeline to be able to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(m_gs);

	//set the vertices to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	
	//draw in multiple viewports
	GraphicsEngine::get()->getImmediateDeviceContext()->drawInMultipleViewports(m_ib);

	m_swap_chain->present(false);

	//list mode
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);


	//draw
	//strip mode
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);



}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	m_gs->release();
	GraphicsEngine::get()->release();
}
