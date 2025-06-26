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

	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	SceneCameraHandler::get()->initialize();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &this->VS_ShaderByteCode, &this->VS_SizeShader);
	m_vs = renderSystem->createVertexShader(this->VS_ShaderByteCode, this->VS_SizeShader);

	
	//instantiate CUBES with DEBUG layer
	int numCubes = 4;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-2.75f, 2.75f);
		float y = generateRandomFloat(-2.75f, 2.75f);

		Cube* cubeObject = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
		cubeObject->setAnimationSpeed(generateRandomFloat(0.5f, 3.0f));
		cubeObject->setPosition(x, y, 0.0f);
		cubeObject->setScale(0.7f, 0.7f, 0.7f);
		this->cubeList.push_back(cubeObject);
		cubeObject->setLayer(cubeObject->getLayer() | Layer::DEBUG);

	}

	//instantiate CUBES without DEBUG layer
	numCubes = 5;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-2.75f, 2.75f);
		float y = generateRandomFloat(-2.75f, 2.75f);

		Cube* cubeObject = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
		cubeObject->setAnimationSpeed(generateRandomFloat(-0.5, 3.0f));
		cubeObject->setPosition(x, y, 0.0f);
		cubeObject->setScale(0.4f, 0.4f, 0.4f);
		this->cubeList.push_back(cubeObject);
		//cubeObject->setLayer(Layer::DEFAULT);

	}


	//instantiate PLANES with DEBUG layer
	int numPlanes = 1;
	for (int i = 0; i < numPlanes; i++) {
		Plane* planeObject = new Plane("Plane", this->VS_ShaderByteCode, this->VS_SizeShader);
		planeObject->setPosition(Vector3D::zeros());
		planeObject->setScale(4.0f, 4.0f, 4.0f);
		planeObject->setLayer(planeObject->getLayer() | Layer::DEBUG);
		this->planeList.push_back(planeObject);
	}


	//CIRCLE UI
	Vector3D color = Vector3D(1.0, 1.0, 0.0);
	Circle* UIObject = new Circle("Circle", this->VS_ShaderByteCode, this->VS_SizeShader, 32, 1, color);
	UIObject->setScale(50, 50, 1.0f);
	UIObject->setRotation(convertToRadians(180), 0, 0);
	Vector3D worldCoords = convertPixelsToWorld(2.0f, 900, 100, width, height);
	UIObject->setPosition(worldCoords);
	UIObject->setLayer(Layer::UI);
	this->UIElements.push_back(UIObject);

	
	Cube* UIObject1 = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
	UIObject1->setScale(40, 200, 1.0f);
	UIObject->setRotation(convertToRadians(180), 0, 0);
	worldCoords = convertPixelsToWorld(2.0f, 100, 350, width, height);
	UIObject1->setPosition(worldCoords);
	UIObject1->setLayer(Layer::UI);
	UIObject1->setIsAnimated(false);
	this->UIElements.push_back(UIObject1);
	


	//Plane* UIObject1 = new Plane("Plane", this->VS_ShaderByteCode, this->VS_SizeShader);
	//UIObject1->setScale(50, 50, 1.0f);
	//UIObject1->setRotation(convertToRadians(0), 0, 0);
	//worldCoords = convertPixelsToWorld(2.0f, 50, 100, width, height);
	//UIObject1->setPosition(worldCoords);
	//UIObject1->setLayer(Layer::UI);
	//this->UIElements.push_back(UIObject1);

	////pixel to world space
	//float temp = 2.0f;
	//float px = 900;
	//float py = 100;
	//float posX = (px - width / 2.0f) / temp;
	//float posY = (height / 2.0f - py) / temp;
	//float posZ = 0.0f;

	//std::cout << "width: " << width << std::endl;
	//std::cout << "height: " << height << std::endl;

	//UIObject->setPosition(posX, posY, posZ);

	

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

	renderSystem->createRasterizerStates();
	//std::cout << "cube list size: " << this->cubeList.size() << std::endl;


	//set cameraa
	//Camera* cam2 = new Camera("Debug Camera");
	//cam2->cullingMask = Layer::DEBUG;
	//cam2->depth = 1;
	//cam2->setEnabled(false);
	//cameraHandler->addCameraToList(cam2);

	//Camera* cam3 = new Camera("UI Camera");
	//cam3->cullingMask = Layer::UI;
	//cam3->depth = 2;
	//cameraHandler->addCameraToList(cam3);

	//Camera* cam1 = new Camera("World Camera");
	//cam1->cullingMask = Layer::DEFAULT;
	//cam1->depth = 0;
	//cameraHandler->addCameraToList(cam1);


	createCamera(Layer::DEBUG,   1, false);
	createCamera(Layer::UI,	     2, true);
	createCamera(Layer::DEFAULT, 0, true);

	cameraHandler->setScreenSizeForAllCameras(width, height);
	cameraHandler->sortCamerasByDepth();
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	InputSystem::get()->update();

	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.0f, 0.0f, 0.0f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	renderSystem->getImmediateDeviceContext()->setViewPortSize(width, height);

	//set the default shader in the graphics pipeline to be able 
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);


	this->sortedCameras = cameraHandler->getAllCameras();
	cameraHandler->update();

	int index = 0;
	for (Camera* cam : this->sortedCameras) {
		if (cam->cullingMask & Layer::DEBUG) {
			renderSystem->getImmediateDeviceContext()->setRasterizerState(renderSystem->getWireframeState());
			renderSystem->getImmediateDeviceContext()->clearDepth(this->m_swap_chain);
		}
		else {
			renderSystem->getImmediateDeviceContext()->setRasterizerState(renderSystem->getSolidState());
		}

		////clear depth only for debug camera 
		//if (cam->cullingMask & Layer::DEBUG)
	
		for (int i = 0; i < this->cubeList.size(); i++) {
			if ((cam->cullingMask & this->cubeList[i]->getLayer()) != 0)
			{
				this->cubeList[i]->update(EngineTime::getDeltaTime());
				this->cubeList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cam->isEnabled()) {
					this->cubeList[i]->render();
				}
			}
		}

		for (int i = 0; i < this->planeList.size(); i++) {
			if ((cam->cullingMask & this->planeList[i]->getLayer()) != 0)
			{
				this->planeList[i]->update(EngineTime::getDeltaTime());
				this->planeList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cam->isEnabled()) {
					this->planeList[i]->render();
				}
			}
		}


		for (int i = 0; i < this->circleList.size(); i++) {
			if ((cam->cullingMask & this->circleList[i]->getLayer()) != 0)
			{
				this->circleList[i]->update(EngineTime::getDeltaTime());
				this->circleList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cam->isEnabled()) {
					this->circleList[i]->render();
				}
			}
		}

		for (int i = 0; i < this->UIElements.size(); i++) {
			if ((cam->cullingMask & this->UIElements[i]->getLayer()) != 0)
			{
				this->UIElements[i]->update(EngineTime::getDeltaTime());
				this->UIElements[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cam->isEnabled()) {
					this->UIElements[i]->render();
				}
			}
		}

	//	std::cout << cam->getName() << std::endl;

		//
		/*int test = 0;
		for (int i = 0; i < sortedCameras.size(); i++) {
			if (sortedCameras[i]->isEnabled())
				test++;
		}*/

	//	std::cout << "COUNT: " << test << std::endl;
		index++;
	}


	//Camera* cam = cameraHandler->getTestCamera();
	//cameraHandler->setActiveCamera(cam);


	//	for (int i = 0; i < this->cubeList.size(); i++) {
	//		/*this->cubeList[i]->update(EngineTime::getDeltaTime());
	//		this->cubeList[i]->draw(width, height, m_vs, m_ps);*/

	//		if ((cam->cullingMask & this->cubeList[i]->getLayer()) != 0)
	//		{
	//			this->cubeList[i]->update(EngineTime::getDeltaTime());
	//			this->cubeList[i]->draw(width, height, m_vs, m_ps);
	//		}
	//	}


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
