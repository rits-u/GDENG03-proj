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
	SceneCameraHandler::get()->initialize();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	//cameraHandler->initialize();
	//cameraHandler->createCameras(2);
	//cameraHandler->setScreenSize(width, height);
	//SceneCameraHandler::get

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

	int numCubes = 4;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-2.75f, 2.75f);
		float y = generateRandomFloat(-2.75f, 2.75f);

		Cube* cubeObject = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
		cubeObject->setAnimationSpeed(generateRandomFloat(0.5f, 3.0f));
		//cubeObject->setAnimationSpeed(5.0f);
		cubeObject->setPosition(Vector3D(x, y, 0.0f));
		//cubeObject->setPosition(Vector3D::zeros());
		cubeObject->setScale(Vector3D(0.7f, 0.7f, 0.7f));
		this->cubeList.push_back(cubeObject);
		cubeObject->setLayer(Layer::DEFAULT | Layer::DEBUG);

	}


	numCubes = 5;
	for (int i = 0; i < numCubes; i++) {
		float x = generateRandomFloat(-2.75f, 2.75f);
		float y = generateRandomFloat(-2.75f, 2.75f);

		Cube* cubeObject = new Cube("Cube", this->VS_ShaderByteCode, this->VS_SizeShader);
		cubeObject->setAnimationSpeed(generateRandomFloat(-0.5, 3.0f));
	//	cubeObject->setAnimationSpeed(5.0f);
		cubeObject->setPosition(Vector3D(x, y, 0.0f));
		//cubeObject->setPosition(Vector3D::zeros());
		cubeObject->setScale(Vector3D(0.4f, 0.4f, 0.4f));
		this->cubeList.push_back(cubeObject);
		//cubeObject->setLayer(Layer::DEFAULT);

	}



	int numPlanes = 1;
	for (int i = 0; i < numPlanes; i++) {
		Plane* planeObject = new Plane("Plane", this->VS_ShaderByteCode, this->VS_SizeShader);
		planeObject->setPosition(Vector3D::zeros());
		planeObject->setScale(Vector3D(4.0f, 4.0f, 4.0f));
		//planeObject->setRotation(Vector3D(0.0f, 0.0f, 0.0f));
		planeObject->setLayer(Layer::DEBUG);
		this->planeList.push_back(planeObject);
	}


	//CIRCLE
	Vector3D color = Vector3D(1.0, 1.0, 0.0);
	Circle* UIObject = new Circle("Circle", this->VS_ShaderByteCode, this->VS_SizeShader, 32, 1, color);
	UIObject->setScale(Vector3D(1.0f, 1.0f, 1.0f));
	UIObject->setRotation(Vector3D(convertToRadians(180), 0, 0));
	UIObject->setLayer(Layer::UI);

	float px = 900;
	float py = 100;
	float posX = (px - width / 2.0f) / 100.0f;
	float posY = (height / 2.0f - py) / 100.0f;
	float posZ = 0.0f;

	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;

//	circleObject->setPosition(3, 3, 0);
	UIObject->setPosition(posX, posY, 0);
	//circleObject->setPosition(Vector3D(960.0f, 540.0f, 0.0f));
	//this->circleList.push_back(circleObject);
	this->UIElements.push_back(UIObject);
	

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



	//set cameras
	//Camera* cam1 = new Camera("Camera", true);
	Camera* cam1 = new Camera("World Camera");
	cameraHandler->addCameraToList(cam1);
	cameraHandler->getCameraByIndex(0)->cullingMask = Layer::DEFAULT;
	cameraHandler->getCameraByIndex(0)->depth = 0;


	//
	//Camera* cam2 = new Camera("Camera", true);
	Camera* cam2 = new Camera("Debug Camera");
	cameraHandler->addCameraToList(cam2);
	cameraHandler->getCameraByIndex(1)->cullingMask = Layer::DEBUG;
	cameraHandler->getCameraByIndex(1)->depth = 1;
	cameraHandler->getCameraByIndex(1)->setEnabled(false);
	//std::cout << cameraHandler->getCameraByIndex(1)->isEnabled << std::endl;


	Camera* cam3 = new Camera("UI Camera");
	cam3->cullingMask = Layer::UI;
	cam3->depth = 2;
	cameraHandler->addCameraToList(cam3);

	//cameraHandler->getCameraByIndex(2)->cullingMask = Layer::UI;
	//cameraHandler->getCameraByIndex(2)->depth = 2;
//	cameraHandler->setScreenSize(width, height);



	cameraHandler->setScreenSizeForAllCameras(width, height);
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	SceneCameraHandler* cameraHandler = SceneCameraHandler::get();

	InputSystem::get()->update();
	cameraHandler->update();
	std::vector<Camera*> sortedCameras = cameraHandler->getCamerasSortedByDepth();


	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.0f, 0.0f, 0.0f, 1); // 1 0 0 1

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	renderSystem->getImmediateDeviceContext()->setViewPortSize(width, height);



	//set the default shader in the graphics pipeline to be able 
	renderSystem->getImmediateDeviceContext()->setVertexShader(m_vs);
	renderSystem->getImmediateDeviceContext()->setPixelShader(m_ps);

	int index = 0;

	for (Camera* cam : sortedCameras) {
		cameraHandler->setActiveCamera(cam);

		if (cam->cullingMask & Layer::DEBUG) 
			renderSystem->getImmediateDeviceContext()->setRasterizerState(renderSystem->getWireframeState());
		else
			renderSystem->getImmediateDeviceContext()->setRasterizerState(renderSystem->getSolidState());


		//if(cam->cullingMask & Layer::DEBUG)
			


	//	renderSystem->getImmediateDeviceContext()->setRasterizerState(renderSystem->getWireframeState());

		//clear depth only for debug camera 
		if (cam->cullingMask & Layer::DEBUG)
		    renderSystem->getImmediateDeviceContext()->clearDepth(this->m_swap_chain);


	/*	if (cam->cullingMask & Layer::UI) {
			renderSystem->getImmediateDeviceContext()->clearDepth(this->m_swap_chain);
			renderSystem->getImmediateDeviceContext()->disableDepth(this->m_swap_chain);
		}*/



		for (int i = 0; i < this->cubeList.size(); i++) {
			/*this->cubeList[i]->update(EngineTime::getDeltaTime());
			this->cubeList[i]->draw(width, height, m_vs, m_ps);*/

			if ((cam->cullingMask & this->cubeList[i]->getLayer()) != 0)
			{
				this->cubeList[i]->update(EngineTime::getDeltaTime());
				this->cubeList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cameraHandler->getCameraByIndex(index)->isEnabled()) {
					this->cubeList[i]->render();
				}
				//this->cubeList[i]->draw(width, height, m_vs, m_ps);
				//this->cubeList[i]->draw(width, height, m_vs, m_ps, index);
			}
		}

		for (int i = 0; i < this->planeList.size(); i++) {
			/*this->cubeList[i]->update(EngineTime::getDeltaTime());
			this->cubeList[i]->draw(width, height, m_vs, m_ps);*/

			if ((cam->cullingMask & this->planeList[i]->getLayer()) != 0)
			{
				this->planeList[i]->update(EngineTime::getDeltaTime());
				this->planeList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cameraHandler->getCameraByIndex(index)->isEnabled()) {
					this->planeList[i]->render();
				}
				//this->cubeList[i]->draw(width, height, m_vs, m_ps);
				//this->cubeList[i]->draw(width, height, m_vs, m_ps, index);
			}
		}

		//for (int i = 0; i < this->planeList.size(); i++) {
		//	this->planeList [i] ->update(EngineTime::getDeltaTime());
		//	this->planeList[i]->draw(width, height, m_vs, m_ps);
		//}

		for (int i = 0; i < this->circleList.size(); i++) {
			if ((cam->cullingMask & this->circleList[i]->getLayer()) != 0)
			{
				this->circleList[i]->update(EngineTime::getDeltaTime());
				this->circleList[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cameraHandler->getCameraByIndex(index)->isEnabled()) {
					this->circleList[i]->render();
				}
				//this->circleList[i]->draw(width, height, m_vs, m_ps);
			}
		}

		for (int i = 0; i < this->UIElements.size(); i++) {
			if ((cam->cullingMask & this->UIElements[i]->getLayer()) != 0)
			{
				this->UIElements[i]->update(EngineTime::getDeltaTime());
				this->UIElements[i]->updateTransformAndBuffers(width, height, m_vs, m_ps, index);

				if (cameraHandler->getCameraByIndex(index)->isEnabled()) {
					this->UIElements[i]->render();
				}
			}
		}

		//
		int test = 0;
		for (int i = 0; i < sortedCameras.size(); i++) {
			if (sortedCameras[i]->isEnabled())
				test++;
		}

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
	if (key == 'T' && !this->holding)
	{
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
