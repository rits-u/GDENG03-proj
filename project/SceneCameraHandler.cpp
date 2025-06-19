#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::get()
{
  /*  if (sharedInstance == nullptr)
    {
        sharedInstance = new SceneCameraHandler();
    }*/
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::update()
{  
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

void SceneCameraHandler::setScreenSize(int width, int height)
{
    this->sceneCamera->setWidthAndHeight(width, height);
}

Camera* SceneCameraHandler::getCamera()
{
    return this->sceneCamera;
}

SceneCameraHandler::SceneCameraHandler()
{
    this->sceneCamera = new Camera("SceneCamera");
}

SceneCameraHandler::~SceneCameraHandler()
{
    delete this->sceneCamera;
}
