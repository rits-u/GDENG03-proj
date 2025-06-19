#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	//InputSystem::get()->initialize();
	InputSystem::get()->addListener(this);
	//InputSystem::get()->showCursor(false);
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	SceneCameraHandler::get()->initialize();
	SceneCameraHandler::get()->setScreenSize(width, height);

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

	int numCubes = 10;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-0.75f, 0.75f);
		float y = generateRandomFloat(-0.75f, 0.75f);

		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		cubeObject->setAnimationSpeed(generateRandomFloat(-3.75f, 3.75f));
		cubeObject->setPosition(Vector3D(x, y, 0.0f));
	//	cubeObject->setPosition(Vector3D::zeros());
		cubeObject->setScale(Vector3D(0.4, 0.4, 0.4));
		this->cubeList.push_back(cubeObject);

	}

	int numPlanes = 1;
	for (int i = 0; i < numPlanes; i++) {
		Plane* planeObject = new Plane("Plane", shader_byte_code, size_shader);
		planeObject->setPosition(Vector3D::zeros());
		planeObject->setScale(Vector3D(3.0f, 3.0f, 3.0f));
		planeObject->setRotation(Vector3D(0.0f, 0.0f, 0.0f));
		this->planeList.push_back(planeObject);
	}

	//RELEASE VERTEX SHADER
	GraphicsEngine::get()->releaseCompiledShader();


	//PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	std::cout << "cube list size: " << this->cubeList.size() << std::endl;
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();

	InputSystem::get()->update();
	SceneCameraHandler::get()->update();

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
		this->cubeList[i]->draw(width, height, m_vs, m_ps);
	}

	for (int i = 0; i < this->planeList.size(); i++) {
		this->planeList [i] ->update(EngineTime::getDeltaTime());
		this->planeList[i]->draw(width, height, m_vs, m_ps);
	}

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	//InputSystem::get()->addListener(this);
	InputSystem::get()->addListener(SceneCameraHandler::get()->getCamera());
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(SceneCameraHandler::get()->getCamera());
}

void AppWindow::onKeyDown(int key)
{
	//---------------------TRANSLATION----------------
	if (key == 'W')
	{
	}

	else if (key == 'S')
	{
	}

	else if (key == 'A')
	{
		std::cout << "move A" << std::endl;
	}

	else if (key == 'D')
	{
		std::cout << "move D" << std::endl;
	}


	//---------------------ROTATION----------------
	else if (key == 'I')
	{
		std::cout << "rotate I" << std::endl;
	}

	else if (key == 'K')
	{
		std::cout << "rotate K" << std::endl;
	}

	else if (key == 'J')
	{
		std::cout << "rotate J" << std::endl;
	}

	else if (key == 'L')
	{
		std::cout << "rotate L" << std::endl;
	}

	//---------------------SCALE----------------
	else if (key == 'Q')
	{
		std::cout << "scale Q" << std::endl;
	}

	else if (key == 'E')
	{
		std::cout << "scale E" << std::endl;
	}

	else if (key == 38)
	{
		std::cout << "translate UP" << std::endl;
	}

	else if (key == 40)
	{
		std::cout << "translate DOWN" << std::endl;
	}
	
	else if (key == 39)
	{
		std::cout << "translate RIGHT" << std::endl;
	}

	else if (key == 37)
	{
		std::cout << "translate LEFT" << std::endl;
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& mousePos)
{
}

void AppWindow::onLeftMouseDown(const Point& mousePos)
{
}

void AppWindow::onLeftMouseUp(const Point& mousePos)
{
}

void AppWindow::onRightMouseDown(const Point& mousePos)
{
}

void AppWindow::onRightMouseUp(const Point& mousePos)
{
}

float AppWindow::generateRandomFloat(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
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

