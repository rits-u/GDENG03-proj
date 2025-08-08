#include "SceneCameraHandler.h"
#include "EngineTime.h"


SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::get()
{
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    if (!SceneCameraHandler::sharedInstance)
        return;

    delete sharedInstance;
}

void SceneCameraHandler::updateAllCameras()
{  
    //update all cameras in the list
    for (Camera* cam : this->cameraList)
    {
        cam->update(EngineTime::getDeltaTime());
        
    }
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

void SceneCameraHandler::setScreenSize(int width, int height)
{
   this->sceneCamera->setWidthAndHeight(width, height);
}

void SceneCameraHandler::setScreenSizeForAllCameras(int width, int height)
{
    if (this->cameraList.size() > 0) {
        for (Camera* camera : this->cameraList) {
            camera->setWidthAndHeight(width, height);
        }
    }
}

void SceneCameraHandler::addCameraToList(Camera* cam)
{
    this->cameraList.push_back(cam);
}

std::vector<Camera*>& SceneCameraHandler::getAllCameras()
{
    return this->cameraList;
}

void SceneCameraHandler::sortCamerasByDepth()
{

    std::vector<Camera*> sortedCameras = this->cameraList;
    for (int i = 0; i < sortedCameras.size(); i++)
    {
        for (int j = i + 1; j < sortedCameras.size(); j++)
        {
            if (sortedCameras[i]->depth > sortedCameras[j]->depth)
            {
                Camera* temp = sortedCameras[i];
                sortedCameras[i] = sortedCameras[j];
                sortedCameras[j] = temp;
            }
        }
    }

    this->cameraList = sortedCameras;
    
}

void SceneCameraHandler::setActiveCamera(Camera* camera)
{
    this->sceneCamera = camera;
}


Camera* SceneCameraHandler::getCamera()
{
    return this->sceneCamera;
}

Camera* SceneCameraHandler::getCameraByIndex(int index)
{
    if(this->cameraList[index] != NULL)
        return this->cameraList[index];

    return nullptr;
}

SceneCameraHandler::SceneCameraHandler()
{
}

SceneCameraHandler::~SceneCameraHandler()
{
    for (int i = 0; i < this->cameraList.size(); i++) {
        delete this->cameraList[i];
    }
   // delete this->sceneCamera;
    cameraList.clear();
    SceneCameraHandler::sharedInstance = nullptr;
}