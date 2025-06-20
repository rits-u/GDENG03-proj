#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "RenderSystem.h"

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
	//GraphicsEngine::get()->init();

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	SceneCameraHandler::get()->initialize();
	SceneCameraHandler::get()->setScreenSize(width, height);

	//m_swap_chain->init(this->m_hwnd, width, height);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = renderSystem->createVertexShader(shader_byte_code, size_shader);

	//cubeObject = new Cube("TestCube", shader_byte_code, size_shader);
	////cubeObject->setAnimSpeed(1);
	//cubeObject->setPosition(Vector3D(0, 0, 0));
	//cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	//this->cubeList.push_back(cubeObject);

	//int numCubes = 2;
	//for (int i = 0; i < numCubes; i++) {
	//	float x = generateRandomFloat(-0.75f, 0.75f);
	//	float y = generateRandomFloat(-0.75f, 0.75f);

	//	Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
	//	//cubeObject->setAnimationSpeed(generateRandomFloat(-3.75f, 3.75f));
	//	cubeObject->setAnimationSpeed(5.0f);
	//	cubeObject->setPosition(Vector3D(x, y, 0.0f));
	////	cubeObject->setPosition(Vector3D::zeros());
	//	cubeObject->setScale(Vector3D(0.4, 0.4, 0.4));
	//	this->cubeList.push_back(cubeObject);

	//}

	//int numPlanes = 1;
	//for (int i = 0; i < numPlanes; i++) {
	//	Plane* planeObject = new Plane("Plane", shader_byte_code, size_shader);
	//	planeObject->setPosition(Vector3D::zeros());
	//	planeObject->setScale(Vector3D(3.0f, 3.0f, 3.0f));
	//	planeObject->setRotation(Vector3D(0.0f, 0.0f, 0.0f));
	//	this->planeList.push_back(planeObject);
	//}


	//CIRCLE
	int numCircles = 5;
	for (int i = 0; i < numCircles; i++) {
		float r = generateRandomFloat(0.0f, 1.0f);
		float g = generateRandomFloat(0.0f, 1.0f);
		float b = generateRandomFloat(0.0f, 1.0f);
		float randX = generateRandomFloat(0, 1);
		float randY = generateRandomFloat(0, 1);
		float speed = 1.0f;
		//std::cout << "go UP: " << goUp << std::endl;


		this->spawnCircle(shader_byte_code, size_shader, Vector3D(r ,g, b), randX, randY, speed);
	}
	std::cout << "circles count: " << this->circleList.size() << std::endl;

	//RELEASE VERTEX SHADER
	renderSystem->releaseCompiledShader();


	//PIXEL SHADER
	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = renderSystem->createPixelShader(shader_byte_code, size_shader);
	renderSystem->releaseCompiledShader();


	std::cout << "cube list size: " << this->cubeList.size() << std::endl;
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	InputSystem::get()->update();
	SceneCameraHandler::get()->update();

	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.0f, 0.0f, 0.0f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	renderSystem->getImmediateDeviceContext()->setViewPortSize(width, height);


	//set the default shader in the graphics pipeline to be able 
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);


	//for (int i = 0; i < this->cubeList.size(); i++) {
	//	this->cubeList[i]->update(EngineTime::getDeltaTime());
	//	this->cubeList[i]->draw(width, height, m_vs, m_ps);
	//}

	//for (int i = 0; i < this->planeList.size(); i++) {
	//	this->planeList [i] ->update(EngineTime::getDeltaTime());
	//	this->planeList[i]->draw(width, height, m_vs, m_ps);
	//}

	for (int i = 0; i < this->circleList.size(); i++) {
		this->circleList[i] ->update(EngineTime::getDeltaTime());
		this->circleList[i]->draw(width, height, m_vs, m_ps);
	}

	//this->circleList[0]->update(EngineTime::getDeltaTime());
	//this->circleList[0]->draw(width, height, m_vs, m_ps);


	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
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
	//	std::cout << "move A" << std::endl;
	}

	else if (key == 'D')
	{
	//	std::cout << "move D" << std::endl;
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

	//ESCAPE KEY
	else if (key == 27)
	{
		std::cout << "Closed application" << std::endl;
		::DestroyWindow(this->m_hwnd);
		::PostQuitMessage(0);
	}


//	std::cout << "Key: " << key << std::endl;
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

void AppWindow::spawnCircle(void* shader_byte_code, size_t size_shader, Vector3D color, float randX, float randY, float speed)
{
	//CIRCLE
	int numSegment = 32;
	int radius = 1;

	//float r = generateRandomFloat(0.0f, 1.0f);
	//float g = generateRandomFloat(0.0f, 1.0f);
	//float b = generateRandomFloat(0.0f, 1.0f);
	//float goUp = generateRandomFloat(0, 1);
	//float goDown = generateRandomFloat(0, 1);

	bool goUp;
	bool goRight;

	if (randX <= 0.5f) goUp = false;
	else goUp = true;

	if (randY <= 0.5f) goRight = false;
	else goRight = true;


	std::cout << "go UP: " << goUp << std::endl;
	std::cout << "go RIGHT: " << goRight << std::endl;

	Circle* circleObject = new Circle("Circle", shader_byte_code, size_shader, numSegment, radius, color, goUp, goRight);
	circleObject->setDirection(goUp, goRight);
	//circleObject->setPosition(Vector3D(-2.52f, 1.75f, 0));
	circleObject->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	circleObject->setScale(Vector3D(0.25f, 0.25f, 0.25f));

	//float goUp = generateRandomFloat(0, 1);
	//float goDown = generateRandomFloat(0, 1);
	//circleObject->setDirection(goUp, goRight);
	//circleObject->setDirection(goUp, goRight);



	//circleObject->setScale(Vector3D(1.0f, 1.0f, 1.0f));
	float radians = 180.0f * (3.14f / 180.0f);	//flip the circle so that it faces the camera
	circleObject->setRotation(Vector3D(radians, 0.0f, 0.0f));
	//circleObject->setAnimationSpeed(speed);
	circleObject->setAnimationSpeed(generateRandomFloat(1.0f, 5.0f));
	std::cout << "speed: " << speed << std::endl;

	this->circleList.push_back(circleObject);
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

