#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <vector>
#include <iostream>

struct vec3
{
	float x, y, z;
};
//
//struct vertex
//{
//	Vector3D position;
//	//Vector3D position1;
//	Vector3D color;
//	Vector3D color1;
//};
//
//__declspec(align(16))
//struct constant
//{
//	Matrix4x4 m_world;
//	Matrix4x4 m_view;
//	Matrix4x4 m_proj;
//	unsigned int m_time;
//};


AppWindow::AppWindow()
{
}

void AppWindow::updateQuadPosition()
{
	//RECT rc = this->getClientWindowRect();
	//UINT width = rc.right - rc.left;
	//UINT height = rc.bottom - rc.top;

	//constant cc;
	//accumulatedTime += EngineTime::getDeltaTime() * 1000.0f * 5.0f;


	//delta_pos += EngineTime::getDeltaTime() / 8.0f;

	//if (delta_pos > 1.0f)
	//	delta_pos = 0.0f;

	//Matrix4x4 temp;
	//delta_scale += EngineTime::getDeltaTime() / 0.85f;


	//cc.m_world.setScale(Vector3D(1, 1, 1));

	//temp.setIdentity();
	//temp.setRotationZ(delta_scale);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationY(delta_scale);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationX(delta_scale);
	//cc.m_world *= temp;


	//cc.m_view.setIdentity();
	//cc.m_proj.setOrthoLH(width/300.0f, height/300.0f, -4.0f, 4.0f);

	//cc.m_time = accumulatedTime;

	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

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

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);


	//cubeObject = new Cube("TestCube", shader_byte_code, size_shader);
	////cubeObject->setAnimSpeed(1);
	//cubeObject->setPosition(Vector3D(0, 0, 0));
	//cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	//this->cubeList.push_back(cubeObject);


	for (int i = 0; i < 100; i++) {
		float x = generateRandomFloat(-0.75f, 0.75f);
		float y = generateRandomFloat(-0.75f, 0.75f);

		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		cubeObject->setAnimSpeed(generateRandomFloat(-3.75f, 3.75f));
		cubeObject->setPosition(Vector3D(x, y, 0.0f));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->cubeList.push_back(cubeObject);

	}


	//RELEASE VERTEX SHADER
	GraphicsEngine::get()->releaseCompiledShader();



	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	accumulatedTime = 0.0f;
	speed = 0.1f;
	increaseSpeed = true;

	std::cout << "cube list size: " << this->cubeList.size() << std::endl;

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


	//set the default shader in the graphics pipeline to be able 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

//	cubeObject->update(EngineTime::getDeltaTime());
//	cubeObject->draw_(width, height, m_vs, m_ps);

	for (int i = 0; i < this->cubeList.size(); i++) {
		this->cubeList[i]->update(EngineTime::getDeltaTime());
		this->cubeList[i]->draw_(width, height, m_vs, m_ps);
	}

	

	m_swap_chain->present(false);


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
