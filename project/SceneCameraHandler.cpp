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
 //   this->sceneCamera->update(EngineTime::getDeltaTime());
 //*   for (int i = 0; i < this->cameraList.size(); i++) {
 //       this->cameraList[i]->update(EngineTime::getDeltaTime());
 //   }*/

    //if (this->sceneCamera)
    //    this->sceneCamera->update(EngineTime::getDeltaTime());

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

    /*if (this->cameraList.size() > 0) {
        for (Camera* camera : this->cameraList) {
            camera->setWidthAndHeight(width, height);
        }
    }*/
}

void SceneCameraHandler::setScreenSizeForAllCameras(int width, int height)
{
    if (this->cameraList.size() > 0) {
        for (Camera* camera : this->cameraList) {
            camera->setWidthAndHeight(width, height);
        }
    }
}

//void SceneCameraHandler::createCameras(int num)
//{
//    for (int i = 0; i < num; i++)
//    {
//        Camera* cam = new Camera("Camera");
//        this->cameraList.push_back(cam);
//    }
//}

void SceneCameraHandler::addCameraToList(Camera* cam)
{
    this->cameraList.push_back(cam);
}

std::vector<Camera*>& SceneCameraHandler::getAllCameras()
{
    return this->cameraList;
}

void SceneCameraHandler::prepareSort()
{
    //sortedCameras = this->cameraList;
}


std::vector<Camera*> SceneCameraHandler::getCamerasSortedByDepth()
{
    std::vector<Camera*> sortedCameras = this->cameraList;
    //for (Camera* cam : this->cameraList) {
    //    if (cam->isEnabled == true)
    //        sortedCameras.push_back(cam);
    //}

    //std::cout << "Enabled: " << sortedCameras.size() << std::endl;

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

    return sortedCameras;
}

void SceneCameraHandler::setActiveCamera(Camera* camera)
{
    this->sceneCamera = camera;
}

Camera* SceneCameraHandler::getTestCamera()
{
    if (this->cameraList[0] != NULL)
        return this->cameraList[0];
}

Camera* SceneCameraHandler::getCamera()
{
    return this->sceneCamera;
}

Camera* SceneCameraHandler::getCameraByIndex(int index)
{
    return this->cameraList[index];
}

SceneCameraHandler::SceneCameraHandler()
{
  // this->sceneCamera = new Camera("SceneCamera");
  //  this->cameraList[0] = new C
}

SceneCameraHandler::~SceneCameraHandler()
{
    delete this->sceneCamera;
}
