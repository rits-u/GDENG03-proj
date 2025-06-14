#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

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

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//cubeObject = new Cube("TestCube", shader_byte_code, size_shader);
	////cubeObject->setAnimSpeed(1);
	//cubeObject->setPosition(Vector3D(0, 0, 0));
	//cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	//this->cubeList.push_back(cubeObject);

	int numCubes = 1;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-0.75f, 0.75f);
		float y = generateRandomFloat(-0.75f, 0.75f);

		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		cubeObject->setAnimationSpeed(generateRandomFloat(-3.75f, 3.75f));
	//	cubeObject->setPosition(Vector3D(x, y, 0.0f));
		cubeObject->setPosition(Vector3D::zeros());
		cubeObject->setScale(Vector3D(0.4, 0.4, 0.4));
		this->cubeList.push_back(cubeObject);

	}

	int numPlanes = 1;
	for (int i = 0; i < numPlanes; i++) {
		Plane* planeObject = new Plane("Plane", shader_byte_code, size_shader);
		planeObject->setPosition(Vector3D::zeros());
		planeObject->setScale(Vector3D(3.0f, 3.0f, 3.0f));
		planeObject->setRotation(Vector3D(0.05f, 0.0f, 0.0f));
		this->planeList.push_back(planeObject);
	}

	//RELEASE VERTEX SHADER
	GraphicsEngine::get()->releaseCompiledShader();


	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//accumulatedTime = 0.0f;
	//speed = 0.1f;
	//increaseSpeed = true;

	std::cout << "cube list size: " << this->cubeList.size() << std::endl;

	//camera = new Camera();
	//camera->SetPosition(0.0f, 0.0f, -5.0f);
	//camera->SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

	camera = new Camera();
	camera->SetPosition(0.0f, 0.0f, -5.0f);
	camera->SetTarget(0.0f, 0.0f, 0.0f); 
	camera->SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);


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


	for (int i = 0; i < this->cubeList.size(); i++) {
		this->cubeList[i]->update(EngineTime::getDeltaTime());
		this->cubeList[i]->draw(width, height, m_vs, m_ps, this->camera);
	}

	for (int i = 0; i < this->planeList.size(); i++) {
		this->planeList [i] ->update(EngineTime::getDeltaTime());
		this->planeList[i]->draw(width, height, m_vs, m_ps, this->camera);
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

//void AppWindow::adjustSpeed()
//{
//	float maxSpeed = 10.0f;
//	float minSpeed = 0.1f;
//
//	if (increaseSpeed) {
//		speed += 0.02f;
//	}
//	else {
//		speed -= 0.02f;
//	}
//
//	if (speed >= maxSpeed) {
//		increaseSpeed = false;
//	}
//	else if (speed <= minSpeed){
//		increaseSpeed = true;
//	}
//
////	std::cout << "SPEED: " << speed << std::endl;
//		
//}

float AppWindow::generateRandomFloat(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}
