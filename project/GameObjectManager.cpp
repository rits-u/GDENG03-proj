#include "GameObjectManager.h"
typedef std::vector<GameObject*> List;

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::get()
{
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
    if (!GameObjectManager::sharedInstance)
        return;

    delete GameObjectManager::sharedInstance;
}

GameObject* GameObjectManager::findObjectByName(string name)
{
    int index = 0;
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            index = i;
            break;
        }
    }
    return this->gameObjectList[index];
}

List GameObjectManager::getAllObjects()
{
    return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
    int activeObjs = 0;
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->isEnabled())
            activeObjs++;
    }
    return activeObjs;
}

void GameObjectManager::updateAll()
{
    for (GameObject* obj : this->gameObjectList) {
        if (obj->isEnabled())
            obj->update(EngineTime::getDeltaTime());
    }
}

void GameObjectManager::updateAllTransformAndBuffers(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader, int camIndex)
{
    for (GameObject* obj : this->gameObjectList) {
        if (obj->isEnabled())
            obj->updateTransformAndBuffers(viewportWidth, viewportHeight, vertexShader, pixelShader, camIndex);
    }
}

void GameObjectManager::renderAll()
{
    for (GameObject* obj : this->gameObjectList) {
        if (obj->isEnabled())
            obj->render();
    }
}

//void GameObjectManager::updateAllTransformAndBuffers()
//{
//    for (int i = 0; i < this->gameObjectList.size(); i++) {
//        if (this->gameObjectList[i]->isEnabled()) {
//            this->gameObjectList[i]->updateTransformAndBuffers()
//        }
//    }
//}
//
//void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader)
//{
//    for (int i = 0; i < this->gameObjectList.size(); i++) {
//        if (this->gameObjectList[i]->isEnabled()) {
//            this->gameObjectList[i]->draw(viewportWidth, viewportHeight, vertexShader, pixelShader);
//        }
//    }
//}

void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc)
{
    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();

    int index = 0; 

    for (Camera* cam : cameras) {
        if (!cam || !cam->isEnabled())
            continue;

        if (cam->cullingMask & Layer::DEBUG)
            context->setRasterizerState(renderSystem->getWireframeState());
        else
            context->setRasterizerState(renderSystem->getSolidState());

        context->clearDepth(sc);

        for (GameObject* obj : gameObjectList) {
            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
                obj->update(EngineTime::getDeltaTime());
                obj->updateTransformAndBuffers(width, height, vs, ps, index);
                obj->render();
            }
        }

        index++;
    }
}

void GameObjectManager::addObject(GameObject* gameObject)
{
    this->gameObjectList.push_back(gameObject);
    this->gameObjectTable[gameObject->getName()] = gameObject;
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
    switch (type) {
    case PrimitiveType::CUBE: 
        Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
        this->addObject(cubeObject);
        break;
    }
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            delete this->gameObjectList[i];
            this->gameObjectList.erase(this->gameObjectList.begin() + i);
            break;
        }
    }
}

void GameObjectManager::deleteObjectByName(string name)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            delete this->gameObjectList[i];
            this->gameObjectList.erase(this->gameObjectList.begin() + i);
            break;
        }
    }
}

void GameObjectManager::setSelectedObject(string name)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            this->selectedObject = this->gameObjectList[i];
            break;
        }
    }
}

void GameObjectManager::setSelectedObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            this->selectedObject = this->gameObjectList[i];
            break;
        }
    }
}

GameObject* GameObjectManager::getSelectedObject()
{
    return this->selectedObject;
}

GameObjectManager::GameObjectManager()
{
    this->selectedObject = nullptr;
    this->gameObjectList.clear();
    this->gameObjectTable.clear();
}

GameObjectManager::~GameObjectManager()
{
   for (int i = 0; i < this->gameObjectList.size(); i++) {
       delete this->gameObjectList[i];
   }

    gameObjectList.clear();
    gameObjectTable.clear();
    selectedObject = nullptr;

    GameObjectManager::sharedInstance = nullptr;
}
