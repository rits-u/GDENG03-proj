#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
//#include "Vector2D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "RenderSystem.h"

#include "Types.h"


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

	this->woodTex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	SceneCameraHandler::get()->initialize();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	UIManager::get()->initialize(this->m_hwnd);
	GameObjectManager::get()->initialize();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &this->VS_ShaderByteCode, &this->VS_SizeShader);
	m_vs = renderSystem->createVertexShader(this->VS_ShaderByteCode, this->VS_SizeShader);

	//PIXEL SHADER
	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &this->PS_ShaderByteCode, &this->PS_SizeShader);
	m_ps = renderSystem->createPixelShader(this->PS_ShaderByteCode, this->PS_SizeShader);


	//RELEASE VERTEX SHADER
	//renderSystem->releaseCompiledShader();


	renderSystem->createRasterizerStates();

	createCamera(Layer::DEBUG,   1, false);
	createCamera(Layer::UI,	     2, false);
	createCamera(Layer::DEFAULT, 0, true);

	cameraHandler->setScreenSizeForAllCameras(width, height);
	cameraHandler->sortCamerasByDepth();

	UINames uiNames;
	MenuToolbar* menuToolbar = (MenuToolbar*)UIManager::get()->getUIScreenByName(uiNames.MENU_TOOLBAR);
	menuToolbar->setShaders(this->VS_ShaderByteCode, this->VS_SizeShader);

	std::cout << "__cplusplus = " << __cplusplus << std::endl;

}

void AppWindow::onUpdate()
{
	//Window::onUpdate();

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();
	
	InputSystem::get()->update();

	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.05f, 0.05f, 0.05f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	renderSystem->getImmediateDeviceContext()->setViewPortSize(width, height);

	//set the default shader in the graphics pipeline to be able 
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);

	renderSystem->getImmediateDeviceContext()->setTexture(m_vs, this->woodTex);
	renderSystem->getImmediateDeviceContext()->setTexture(m_ps, this->woodTex);

	this->sortedCameras = cameraHandler->getAllCameras();
	cameraHandler->updateAllCameras();
	
	List gameObjectList = GameObjectManager::get()->getAllObjects();
	//GameObjectManager::get()->renderAllPerCamera(this->sortedCameras, width, height, m_vs, m_ps, m_swap_chain, this->woodTex);
	GameObjectManager::get()->renderAllPerCamera(this->sortedCameras, width, height, m_vs, m_ps, m_swap_chain);

	UIManager::get()->drawAllUI();


	m_swap_chain->present(false);
}


void AppWindow::onDestroy()
{
	InputSystem::get()->removeListener(this);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
	GameObjectManager::get()->destroy();
	SceneCameraHandler::get()->destroy();
	UIManager::get()->destroy();
	InputSystem::get()->release();
	GraphicsEngine::get()->release();
	Window::onDestroy();
	std::cout << "Closed Program" << std::endl;

}

void AppWindow::onFocus()
{
	Camera* camera = SceneCameraHandler::get()->getCamera();
	if(camera)
		InputSystem::get()->addListener(camera);
}

void AppWindow::onKillFocus()
{
	Camera* camera = SceneCameraHandler::get()->getCamera();
	if (camera)
		InputSystem::get()->removeListener(camera);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'T' && !this->holding) {
	
		bool isEnabled = SceneCameraHandler::get()->getCameraByIndex(1)->isEnabled();

		if (isEnabled) {
			isEnabled = false;
			std::cout << "Disabled DEBUG Camera" << "\n" << std::endl;
		}
		else {
			isEnabled = true;
			std::cout << "Enabled DEBUG Camera" << "\n" << std::endl;
		}

		SceneCameraHandler::get()->getCameraByIndex(1)->setEnabled(isEnabled);
		this->holding = true;
	}

	else if (key == 'Y' && !this->holding)
	{
		bool isEnabled = SceneCameraHandler::get()->getCameraByIndex(0)->isEnabled();
		if (isEnabled) {
			isEnabled = false;
			std::cout << "Disabled DEFAULT Camera" << "\n" << std::endl;
		}
		else {
			isEnabled = true;
			std::cout << "Enabled DEFAULT Camera" << "\n" << std::endl;
		}

		SceneCameraHandler::get()->getCameraByIndex(0)->setEnabled(isEnabled);
		this->holding = true;
	}

	else if (key == 'U' && !this->holding)
	{
		bool isEnabled = SceneCameraHandler::get()->getCameraByIndex(2)->isEnabled();
		if (isEnabled) {
			isEnabled = false;
			std::cout << "Disabled UI Camera" << "\n" << std::endl;
		}
		else {
			isEnabled = true;
			std::cout << "Enabled UI Camera" << "\n" << std::endl;
		}

		SceneCameraHandler::get()->getCameraByIndex(2)->setEnabled(isEnabled);
		this->holding = true;
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
	//else if (key == 32 && !this->holding)
	//{
	//	this->spawnCircle(this->VS_ShaderByteCode, this->VS_SizeShader);
	//	this->holding = true;
	//	std::cout << "Spawned circle" << std::endl;
	//	std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	//}

	////REMOVE RECENT
	//else if (key == 8 && !this->holding)
	//{
	//	if (this->circleList.size() > 0)
	//	{
	//		delete this->circleList.back();
	//		this->circleList.pop_back();
	//	}
	//	this->holding = true;
	//	std::cout << "Deleted recent circle" << std::endl;
	//	std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	//}

	////REMOVE ALL
	//else if (key == 46 && !this->holding)
	//{
	//	for (int i = 0; i < this->circleList.size(); i++)
	//	{
	//		delete circleList[i];
	//		circleList[i] = nullptr;
	//	}
	//	this->circleList.clear();
	//	this->holding = true;
	//	std::cout << "Deleted all circles" << std::endl;
	//	std::cout << "Circle count: " << this->circleList.size() << "\n" << std::endl;
	//}

	//CLOSE escape key
	else if (key == 27 && !this->holding)
	{
		this->holding = true;
		std::cout << "Closed application" << std::endl;
		::DestroyWindow(this->m_hwnd);
		::PostQuitMessage(0);
		return;

	}
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
	float radians = convertToRadians(180);
	circleObject->setRotation(Vector3D(radians, 0.0f, 0.0f));
	circleObject->setAnimationSpeed(generateRandomFloat(1.0f, 3.0f));

	//direction
	//circleObject->setDirection(goUp, goRight);
	float dir = generateRandomFloat(0.0f, 2 * 3.14);
	float x = cosf(dir);
	float y = sinf(dir);
	Vector3D direction = Vector3D(x, y, 0.0f);
	circleObject->setDirection(direction);
	circleObject->setLayer(Layer::DEFAULT | Layer::DEBUG);

	this->circleList.push_back(circleObject);

}

float AppWindow::convertToRadians(float degrees)
{
	float radians = degrees * (3.14f / 180.0f);
	return radians;
}

Vector3D AppWindow::convertPixelsToWorld(float scale, float px, float py, float width, float height)
{
	float x = (px - width / scale) / scale;
	float y = (height / scale - py) / scale;
	float z = 0.0f;

	return Vector3D(x, y, z);
}

void AppWindow::createCamera(Layer layer, float depth, bool enabled)
{
	Camera* cam = new Camera("Camera");
	cam->cullingMask = layer;
	cam->depth = depth;
	cam->setEnabled(enabled);
	SceneCameraHandler::get()->addCameraToList(cam);
}
