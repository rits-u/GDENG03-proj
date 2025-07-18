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

void GameObjectManager::initialUpdateAll()
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

void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc)
{
    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();

    int index = 0; 

    for (Camera* cam : cameras) {
        if (cam->cullingMask & Layer::DEBUG) {
            context->setRasterizerState(renderSystem->getWireframeState());
            context->clearDepth(sc);
        }
        else {
            context->setRasterizerState(renderSystem->getSolidState());
        }

//        std::cout << cam->getLayer() << std::endl;

        //context->clearDepth(sc);

        for (GameObject* obj : gameObjectList) {
            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
                if (obj != NULL) {
                    obj->update(EngineTime::getDeltaTime());
                    obj->updateTransformAndBuffers(width, height, vs, ps, index);
                    if (cam->isEnabled())
                        obj->render();
                }
            }
        }

        index++;
    }
}


void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc, TexturePtr tex)
{
    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();

    int index = 0;

    for (Camera* cam : cameras) {
        if (cam->cullingMask & Layer::DEBUG) {
            context->setRasterizerState(renderSystem->getWireframeState());
            context->clearDepth(sc);
        }
        else {
            context->setRasterizerState(renderSystem->getSolidState());
        }

        //        std::cout << cam->getLayer() << std::endl;

                //context->clearDepth(sc);

        for (GameObject* obj : gameObjectList) {
            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
                if (obj != NULL) {
                    obj->update(EngineTime::getDeltaTime());
                    obj->updateTransformAndBuffers(width, height, vs, ps, index);
                    if (cam->isEnabled())
                        obj->render();
                }
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
        case PrimitiveType::CUBE: {
            Cube* cubeObject = new Cube(adjustGameObjectName("Cube"), shaderByteCode, sizeShader);
            this->addObject(cubeObject);
            std::cout << "Spawned Cube" << std::endl;
            break;
        }
   
        case PrimitiveType::PLANE: {
            Plane* planeObject = new Plane(adjustGameObjectName("Plane"), shaderByteCode, sizeShader);
            this->addObject(planeObject);
            std::cout << "Spawned Plane" << std::endl;
            break;
        }
    }

    //TEMP
}

void GameObjectManager::createModel(String model, void* shaderByteCode, size_t sizeShader)
{
    if (model == "Teapot") {
        MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
        Model* model = new Model("Teapot", mesh, shaderByteCode, sizeShader);
        this->addModel(model);
       // this->addModel((GameObject*)mesh);
    }
}

void GameObjectManager::addModel(Model* model)
{
    this->modelList.push_back(model);
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            std::cout << "Deleted " << gameObject->getName() << std::endl;
            if (dynamic_cast<InputListener*>(this->gameObjectList[i]))
                InputSystem::get()->removeListener((InputListener*)this->gameObjectList[i]);

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

void GameObjectManager::clearSelectedObject()
{
    this->selectedObject = nullptr;
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


string GameObjectManager::adjustGameObjectName(string name)
{
    string adjustedName;
    int count = 0;

    for (GameObject* obj : this->gameObjectList) {
        string temp = obj->getName();
        if (temp.find(name) != std::string::npos)
            count++;
    }

    if (count > 0)
        adjustedName = name + " " + to_string(count);
    else
        adjustedName = name;

    return adjustedName;
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
