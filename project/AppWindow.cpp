#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

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
	InputSystem::get()->showCursor(false);

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
		planeObject->setRotation(Vector3D(0.0f, 0.0f, 0.0f));
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

	//camera = new Camera();
	//camera->SetPosition(0.0f, 0.0f, -5.0f);
	//camera->SetTarget(0.0f, 0.0f, 0.0f); 
	//camera->SetPerspective(XM_PIDIV4, width / (float)height, 0.1f, 100.0f);

	camera = new Camera();
	camera->worldCamera.setTranslation(Vector3D(0, 0, -2));
	camera->updateViewMatrix();

}

void AppWindow::onUpdate()
{
	//Window::onUpdate();

	InputSystem::get()->update();
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

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	float rotX = cubeList[0]->getLocalRotation().m_x;
	float rotY = cubeList[0]->getLocalRotation().m_y;
	float rotZ = cubeList[0]->getLocalPosition().m_z;

	float transX = cubeList[0]->getLocalPosition().m_x;
	float transY = cubeList[0]->getLocalPosition().m_y;
	float transZ = cubeList[0]->getLocalPosition().m_z;

	float scale = cubeList[0]->getLocalScale().m_x;

	float forward = cubeList[0]->forward;
	float rightward = cubeList[0]->rightward;

	float offset = 3.0f;


	//---------------------TRANSLATION----------------
	if (key == 'W')
	{
		//transY += offset * EngineTime::getDeltaTime();
		//forward = 1.0f;
		this->camera->forward = 1.0f;
		std::cout << "move W" << std::endl;
	}

	else if (key == 'S')
	{
		//transY -= offset * EngineTime::getDeltaTime();
		//forward = -1.0f;
		this->camera->forward = -1.0f;
		std::cout << "move S" << std::endl;
	}

	else if (key == 'A')
	{
		//transX += offset * EngineTime::getDeltaTime();
		this->camera->rightward = -1.0f;
		//rightward = -1.0f;
		std::cout << "move A" << std::endl;
	}

	else if (key == 'D')
	{
	//	transX -= offset * EngineTime::getDeltaTime();
		//rightward = 1.0f;
		this->camera->rightward = 1.0f;
		std::cout << "move D" << std::endl;
	}


	//---------------------ROTATION----------------
	else if (key == 'I')
	{
		rotX += offset * EngineTime::getDeltaTime();
		std::cout << "rotate I" << std::endl;
	}

	else if (key == 'K')
	{
		rotX -= offset * EngineTime::getDeltaTime();
		std::cout << "rotate K" << std::endl;
	}

	else if (key == 'J')
	{
		rotY += offset * EngineTime::getDeltaTime();
		std::cout << "rotate J" << std::endl;
	}

	else if (key == 'L')
	{
		rotY -= offset * EngineTime::getDeltaTime();
		std::cout << "rotate L" << std::endl;
	}

	//---------------------SCALE----------------
	else if (key == 'Q')
	{
		scale -= offset * EngineTime::getDeltaTime();
		std::cout << "scale Q" << std::endl;
	}

	else if (key == 'E')
	{
		scale += offset * EngineTime::getDeltaTime();
		std::cout << "scale E" << std::endl;
	}

	else if (key == 38)
	{
		transY += offset * EngineTime::getDeltaTime();
		std::cout << "translate UP" << std::endl;
	}

	else if (key == 40)
	{
		transY -= offset * EngineTime::getDeltaTime();
		std::cout << "translate DOWN" << std::endl;
	}
	
	else if (key == 39)
	{
		transX += offset * EngineTime::getDeltaTime();
		std::cout << "translate RIGHT" << std::endl;
	}

	else if (key == 37)
	{
		transX -= offset * EngineTime::getDeltaTime();
		std::cout << "translate LEFT" << std::endl;
	}


	// cubeList[0]->setPosition(rotX, rotY, rotZ);
	//Vector3D rotation = Vector3D(rotX, rotY, rotZ);
	//camera->setCamRotation(rotation);

	cubeList[0]->setRotation(rotX, rotY, rotZ);
	cubeList[0]->setPosition(transX, transY, transZ);
	cubeList[0]->setScale(scale, scale, scale);
	//cubeList[0]->forward = forward;
	//cubeList[0]->rightward = rightward;
}

void AppWindow::onKeyUp(int key)
{
	cubeList[0]->forward = 0.0f;
	cubeList[0]->rightward = 0.0f;

	this->camera->rightward = 0.0f;
	this->camera->forward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mousePos)
{
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	//float rotX = cubeList[0]->getLocalRotation().m_x;
	//float rotY = cubeList[0]->getLocalRotation().m_y;
	//float rotZ = cubeList[0]->getLocalPosition().m_z;

	float rotX = camera->getCamRotation().m_x;
	float rotY = camera->getCamRotation().m_y;
	float rotZ = camera->getCamRotation().m_z;
	float offset = 0.1f;

	//rotX -= deltaMousePos.m_y * EngineTime::getDeltaTime() * offset;
	//rotY -= deltaMousePos.m_x * EngineTime::getDeltaTime() * offset;

	rotX += (mousePos.m_y - (height/2.0f)) * EngineTime::getDeltaTime() * offset;
	rotY += (mousePos.m_x - (width/2.0f)) * EngineTime::getDeltaTime() * offset;

	//cubeList[0]->setRotation(rotX, rotY, rotZ);

	Vector3D rotation = Vector3D(rotX, rotY, rotZ);
	camera->setCamRotation(rotation);

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onLeftMouseDown(const Point& mousePos)
{
	float temp = cubeList[0]->getLocalScale().m_x;
	float scale = temp / 2.0f;
	cubeList[0]->setScale(scale, scale, scale);
	std::cout << "scale: " << scale << std::endl;

}

void AppWindow::onLeftMouseUp(const Point& mousePos)
{
	float scale = cubeList[0]->getLocalScale().m_x;
	cubeList[0]->setScale(scale, scale, scale);
}

void AppWindow::onRightMouseDown(const Point& mousePos)
{
	float temp = cubeList[0]->getLocalScale().m_x;
	float scale = temp * 2.0f;
	cubeList[0]->setScale(scale, scale, scale);
	std::cout << "scale: " << scale << std::endl;
}

void AppWindow::onRightMouseUp(const Point& mousePos)
{
	float scale = cubeList[0]->getLocalScale().m_x;
	cubeList[0]->setScale(scale, scale, scale);
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
