#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	Vector3D position;
	//Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


AppWindow::AppWindow()
{
}

//void AppWindow::updateQuadPosition()
//{
//	RECT rc = this->getClientWindowRect();
//	UINT width = rc.right - rc.left;
//	UINT height = rc.bottom - rc.top;
//
//	constant cc;
//	//adjustSpeed();
//	accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * 5.0f;
//
////	cc.m_world.setTranslation(Vector3D(0, 0, 0));
//
//	delta_pos += EngineTime::getDeltaTime() / 8.0f;
//	//delta_pos += m_delta_time * 1.0f;
//
//	if (delta_pos > 1.0f)
//		delta_pos = 0.0f;
//
//
//	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), delta_pos));
//
//	delta_scale += EngineTime::getDeltaTime() / 0.85f;
//
//	Matrix4x4 temp;
//	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1, 1, 0), (sin(delta_scale)+1.0f)/2.0f));
//	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5, 1.5, 0), delta_pos));
//	//cc.m_world *= temp;
//
//	cc.m_world.setScale(Vector3D(1, 1, 1));
//
//	temp.setIdentity();
//	temp.setRotationZ(delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationY(delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationX(delta_scale);
//	cc.m_world *= temp;
//
//
//	cc.m_view.setIdentity();
//	cc.m_proj.setOrthoLH(width/300.0f, height/300.0f, -4.0f, 4.0f);
//
//	cc.m_time = accumulatedTime;
//
//	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
//
//}

AppWindow::~AppWindow()
{
}

//void AppWindow::onCreate()
//{
//	Window::onCreate();
//	GraphicsEngine::get()->init();
////	std::cout << "Debug message" << std::endl;
//
//	m_swap_chain = GraphicsEngine::get()->createSwapChain();
//	RECT rc = this->getClientWindowRect();
//	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
//
//	vertex vertex_list[] =
//	{
//		//CUBE
//		//front face
//		{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1,0,0),	Vector3D(0.2f, 0, 0)},		//pos1
//		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.2f, 0.2f,1)},		//pos2
//		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.2f, 0.2f,0)},		//pos3
//		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),	Vector3D(0.2f, 0,1)},		//pos4
//
//		//back face
//		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.2f, 0)},		//pos5
//		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.2f, 0.2f)},		//pos6
//		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.2f, 0.2f)},		//pos7
//		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.2f, 0)},		//pos8
//
//
//	};
//
//	m_vb = GraphicsEngine::get()->createVertexBuffer();
//	UINT size_list = ARRAYSIZE(vertex_list);
//
//	unsigned int index_list[] =
//	{
//		//front side
//		0, 1, 2,	//first triangle
//		2, 3, 0,	//2nd
//
//		//back side
//		4, 5, 6,	//3rd
//		6, 7, 4,	//4th
//
//		//top side
//		1, 6, 5,
//		5, 2, 1,
//
//		//bottom side
//		7, 0, 3,
//		3, 4, 7,
//
//		//right side
//		3, 2, 5,
//		5, 4, 3,
//
//		//left side
//		7, 6, 1,
//		1, 0, 7
//	};
//
//
//
//	m_ib = GraphicsEngine::get()->createIndexBuffer();
//	UINT size_index_list = ARRAYSIZE(index_list);
//	m_ib->load(index_list, size_index_list);
//
//
//	void* shader_byte_code = nullptr;
//	size_t size_shader = 0;
//
//
//	//VERTEX SHADER
//	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
//
//	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
//	//old:
////	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
//	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);			//vertex buffer
//
//	GraphicsEngine::get()->releaseCompiledShader();
//
//
//	//PIXEL SHADER
//	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
//	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
//	GraphicsEngine::get()->releaseCompiledShader();
//
//	constant cc;
//	cc.m_time = 0;
//
//	//CONSTANT BUFFER
//	m_cb = GraphicsEngine::get()->createConstantBuffer();
//	m_cb->load(&cc, sizeof(constant));
//
//	accumulatedTime = 0.0f;
//	speed = 0.1f;
//	increaseSpeed = true;
//
//
//	//std::cout << "hi ahhaah: " << generateRandomFloat(0.5f, 0.75f) << std::endl;
//}

//NEW INITIALIZE ENGINE
void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	Cube* cubeObject = new Cube("TestCube", shader_byte_code, size_shader);
	cubeObject->setAnimSpeed(1);
	cubeObject->setPosition(Vector3D(0, 0, 0));
	cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	this->cubeList.push_back(cubeObject);


	//VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//old:
//	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	//m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);			//vertex buffer

	//for (int i = 0; i < 100; i++) {
	//	float x = generateRandomFloat(-0.75f, 0.75f);
	//	float y = generateRandomFloat(-0.75f, 0.75f);

	//	Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
	//	cubeObject->setAnimSpeed(generateRandomFloat(-3.75f, 3.75f));
	//	cubeObject->setPosition(Vector3D(x, y, 0.0f));
	//	cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
	//	this->cubeList.push_back(cubeObject);

	//}


	GraphicsEngine::get()->releaseCompiledShader();


	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}


void AppWindow::onUpdate()
{
	//Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(width, height);

	//EngineTime::
	//constant cc;

	////adjustSpeed();
	//accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * 1.0f;
	////accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * speed;
	//cc.m_time = accumulatedTime;

	//updateQuadPosition();


//	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

//	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	//set the default shader in the graphics pipeline to be able to draw
//	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//set the vertices to draw
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//set the indeces to draw
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//list mode
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	//draw
	//strip mode
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndewxedTriangleList(m_ib->getSizeIndexList(), 0, 0);


	for (int i = 0; i < this->cubeList.size(); i++) {
		this->cubeList[i]->update(EngineTime::getDeltaTime());
		this->cubeList[i]->draw_(width, height, m_vs, m_ps);
	}

	//astd::cout << this->cubeList.size() << std::endl;

	m_swap_chain->present(true);



	//m_old_delta = m_new_delta;
	//m_new_delta = ::GetTickCount();

	//m_delta_time = (m_old_delta)?((m_new_delta - m_old_delta) / 1000.0f) :0;

}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//m_vb->release();
	//m_ib->release();
	//m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::adjustSpeed()
{
	float maxSpeed = 10.0f;
	float minSpeed = 0.1f;

	if (increaseSpeed) {
		speed += 0.02f;
	}
	else {
		speed -= 0.02f;
	}

	if (speed >= maxSpeed) {
		increaseSpeed = false;
	}
	else if (speed <= minSpeed){
		increaseSpeed = true;
	}

//	std::cout << "SPEED: " << speed << std::endl;
		
}

float AppWindow::generateRandomFloat(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd()); 
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}
