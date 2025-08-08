#include "AppWindow.h"

#include <Windows.h>
#include "Vector3D.h"
//#include "Vector2D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "RenderSystem.h"
#include "Mesh.h"

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
	InputSystem::get()->addListener(this);
	PhysicsSystem::get()->initialize();
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	SceneCameraHandler::get()->initialize();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	UIManager::get()->initialize(this->m_hwnd);
	GameObjectManager::get()->initialize();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	renderSystem->createRasterizerStates();

	createCamera(Layer::DEBUG,   1, false);
	createCamera(Layer::UI,	     2, false);
	createCamera(Layer::DEFAULT, 0, true);

	cameraHandler->setScreenSizeForAllCameras(width, height);
	cameraHandler->sortCamerasByDepth();
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	PhysicsSystem* physicsSystem = PhysicsSystem::get();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();
	
	InputSystem::get()->update();

	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.05f, 0.05f, 0.05f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	renderSystem->getImmediateDeviceContext()->setViewPortSize(width, height);
	physicsSystem->updateAllPhysicsComponents();

	this->sortedCameras = cameraHandler->getAllCameras();
	cameraHandler->updateAllCameras();
	
	List gameObjectList = GameObjectManager::get()->getAllObjects();
	GameObjectManager::get()->renderAllPerCamera(this->sortedCameras, width, height, m_swap_chain);

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

void AppWindow::createCamera(Layer layer, float depth, bool enabled)
{
	Camera* cam = new Camera("Camera");
	cam->cullingMask = layer;
	cam->depth = depth;
	cam->setEnabled(enabled);
	SceneCameraHandler::get()->addCameraToList(cam);
}
