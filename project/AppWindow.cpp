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

//	void* shader_byte_code = nullptr;
//	size_t size_shader = 0;

	//renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &this->VS_ShaderByteCode, &this->VS_SizeShader);
	m_vs = renderSystem->createVertexShader(this->VS_ShaderByteCode, this->VS_SizeShader);

	//cubeObject = new Cube("TestCube", shader_byte_code, size_shader);
	////cubeObject->setAnimSpeed(1);
	//cubeObject->setPosition(Vector3D(0, 0, 0));
	//cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	//this->cubeList.push_back(cubeObject);

	int numCubes = 12;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-2.35f, 2.35f);
		float y = generateRandomFloat(-1.75f, 1.75f);
		float z = generateRandomFloat(-2.75f, 2.75f);

		Cube* cubeObject = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
		cubeObject->setAnimationSpeed(generateRandomFloat(-5.0f, 5.0f));
		//cubeObject->setAnimationSpeed(5.0f);
		//cubeObject->setPosition(Vector3D(x, y, z));
		//cubeObject->setRotation(Vector3D(convertToRadians(20), 0.0f, 0.0f));
		cubeObject->setPosition(Vector3D(0, 0, 0));
		cubeObject->setScale(Vector3D(1.0f, 1.5f, 0.00001f));
		this->cubeList.push_back(cubeObject);
	}

	std::cout << "cube list size: " << this->cubeList.size() << std::endl;

	//int numPlanes = 1;
	//for (int i = 0; i < numPlanes; i++) {
	//	Plane* planeObject = new Plane("Plane", this->VS_ShaderByteCode, this->VS_SizeShader);
	//	planeObject->setPosition(Vector3D::zeros());
	//	planeObject->setScale(Vector3D(8.0f, 10.0f, 9.0f));
	//	planeObject->setRotation(Vector3D(0.0f, 0.0f, 0.0f));
	//	this->planeList.push_back(planeObject);
	//}


	//CIRCLE
	//int numCircles = 5;
	//for (int i = 0; i < numCircles; i++) {
	//	//this->spawnCircle(this->shaderByteCode, this->sizeShader);
	//}
	//std::cout << "circles count: " << this->circleList.size() << std::endl;

	//RELEASE VERTEX SHADER
	//renderSystem->releaseCompiledShader();


	//PIXEL SHADER
	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &this->PS_ShaderByteCode, &this->PS_SizeShader);
	m_ps = renderSystem->createPixelShader(this->PS_ShaderByteCode, this->PS_SizeShader);
	//renderSystem->releaseCompiledShader();


	//this->cubeList[0]->setPosition(0.0f, 0.9f, 0.0f);
	//this->cubeList[1]->setPosition(-1.5f, 2.0f, 0.0f);
	//this->cubeList[2]->setPosition(-1.5f, 3.0f, -2.0f);

	int floor1_Stand = 6;
	int floor1_Down = 3;

	int floor2_Stand = 4;
	int floor2_Down = 2;

	int floor3_Stand = 2;
	int floor3_Down = 1;

	float toAddZ = 0.52;
	for (int i = 0; i < floor1_Stand; i++) {
		float z = 0;

		if(i > 0)
			z = this->cubeList[i-1]->getLocalPosition().m_z;


		if (i % 2 == 0)
			this->cubeList[i]->setRotation(Vector3D(convertToRadians(20), 0, 0.0f));

		else 
			this->cubeList[i]->setRotation(Vector3D(convertToRadians(20), convertToRadians(180), 0.0f));
		

		this->cubeList[i]->setPosition(Vector3D(0, 0, z + toAddZ));
	}


	this->cubeList[6]->setRotation(Vector3D(convertToRadians(-270), 0.0f, 0.0f));
	this->cubeList[6]->setPosition(Vector3D(0, 0.71, 1.3));
	this->cubeList[7]->setRotation(Vector3D(convertToRadians(-270), 0.0f, 0.0f));
	this->cubeList[7]->setPosition(Vector3D(0, 0.71, 2.3));

	toAddZ = 0.5;
	for (int i = 8; i < 12; i++) {
		float z = 0;

		if (i > 9)
			z = this->cubeList[i - 1]->getLocalPosition().m_z;


		if (i % 2 == 0)
			this->cubeList[i]->setRotation(Vector3D(convertToRadians(20), 0, 0.0f));

		else
			this->cubeList[i]->setRotation(Vector3D(convertToRadians(20), convertToRadians(180), 0.0f));


		this->cubeList[i]->setPosition(Vector3D(0, 1.3, toAddZ+z));
	}






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


	for (int i = 0; i < this->cubeList.size(); i++) {
		this->cubeList[i]->update(EngineTime::getDeltaTime());
		this->cubeList[i]->draw(width, height, m_vs, m_ps);
	}

	//for (int i = 0; i < this->planeList.size(); i++) {
	//	this->planeList [i] ->update(EngineTime::getDeltaTime());
	//	this->planeList[i]->draw(width, height, m_vs, m_ps);
	//}

	/*for (int i = 0; i < this->circleList.size(); i++) {
		this->circleList[i] ->update(EngineTime::getDeltaTime());
		this->circleList[i]->draw(width, height, m_vs, m_ps);
	}*/


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

	//SPACE
	else if (key == 32 && !this->holding)
	{
		this->spawnCircle(this->VS_ShaderByteCode, this->VS_SizeShader);
		this->holding = true;
		std::cout << "Spawned circle" << std::endl;
		std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	}

	//REMOVE RECENT
	else if (key == 8 && !this->holding)
	{
		if (this->circleList.size() > 0)
		{
			delete this->circleList.back();
			this->circleList.pop_back();
		}
		this->holding = true;
		std::cout << "Deleted recent circle" << std::endl;
		std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	}

	//REMOVE ALL
	else if (key == 46 && !this->holding)
	{
		for (int i = 0; i < this->circleList.size(); i++)
		{
			delete circleList[i];
			circleList[i] = nullptr;
		}
		this->circleList.clear();
		this->holding = true;
		std::cout << "Deleted all circles" << std::endl;
		std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	}

	//CLOSE
	else if (key == 27)
	{
		std::cout << "Closed application" << std::endl;
		GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();	
		::DestroyWindow(this->m_hwnd);
		::PostQuitMessage(0);
	}

	//std::cout << "Key: " << key << std::endl;
}

void AppWindow::onKeyUp(int key)
{
	this->holding = false;
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

void AppWindow::spawnCircle(void* shader_byte_code, size_t size_shader)
{
	//CIRCLE
	int numSegment = 32;
	int radius = 1;

	float r = generateRandomFloat(0.0f, 1.0f);
	float g = generateRandomFloat(0.0f, 1.0f);
	float b = generateRandomFloat(0.0f, 1.0f);
	float randX = generateRandomFloat(0, 1);
	float randY = generateRandomFloat(0, 1);

	bool goUp, goRight;

	if (randX <= 0.5f) goUp = false;
	else goUp = true;

	if (randY <= 0.5f) goRight = false;
	else goRight = true;


	//std::cout << "go UP: " << goUp << std::endl;
	//std::cout << "go RIGHT: " << goRight << std::endl;

	//Circle* circleObject = new Circle("Circle", shader_byte_code, size_shader, numSegment, radius, color);
	Circle* circleObject = new Circle("Circle", shader_byte_code, size_shader, numSegment, radius, Vector3D(r, g, b));

	circleObject->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	circleObject->setScale(Vector3D(0.25f, 0.25f, 0.25f));

	//rotation
	//float radians = 180.0f * (3.14f / 180.0f);	//flip the circle so that it faces the camera
	circleObject->setRotation(Vector3D(convertToRadians(180), 0.0f, 0.0f));
	circleObject->setAnimationSpeed(generateRandomFloat(1.0f, 8.0f));

	//direction
	//circleObject->setDirection(goUp, goRight);
	float dir = generateRandomFloat(0.0f, 2 * 3.14f);
	float x = cosf(dir);
	float y = sinf(dir);
	Vector3D direction = Vector3D(x, y, 0.0f);
	circleObject->setDirection(direction);

	this->circleList.push_back(circleObject);

}

float AppWindow::convertToRadians(float degrees)
{
	float radians = degrees * (3.14f / 180.0f);
	return radians;
}
