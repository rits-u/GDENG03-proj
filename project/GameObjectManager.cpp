#include "GameObjectManager.h"
//typedef std::vector<GameObject*> List;

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

std::vector<GameObject*> GameObjectManager::getAllObjects()
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
//
//void GameObjectManager::initialUpdateAll()
//{
//    for (GameObject* obj : this->gameObjectList) {
//        if (obj->isEnabled())
//            obj->update(EngineTime::getDeltaTime());
//    }
//}
//
//void GameObjectManager::updateAllTransformAndBuffers(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader, int camIndex)
//{
//    for (GameObject* obj : this->gameObjectList) {
//        if (obj->isEnabled())
//            obj->updateTransformAndBuffers(viewportWidth, viewportHeight, vertexShader, pixelShader, camIndex);
//    }
//}
//
//void GameObjectManager::renderAll()
//{
//    for (GameObject* obj : this->gameObjectList) {
//        if (obj->isEnabled())
//            obj->render();
//    }
//}


//OLLLLLLLLLLLLLLLLLLLLLLLLLLLLD
//void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, SwapChainPtr sc)
//{
//    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
//    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();
//
//    int index = 0;
//
//    for (Camera* cam : cameras) {
//        if (cam->cullingMask & Layer::DEBUG) {
//            context->setRasterizerState(renderSystem->getWireframeState());
//            context->clearDepth(sc);
//        }
//        else {
//            context->setRasterizerState(renderSystem->getSolidState());
//        }
//
//        //        std::cout << cam->getLayer() << std::endl;
//
//                //context->clearDepth(sc);
//
//        for (GameObject* obj : gameObjectList) {
//            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
//                if (obj != NULL) {
//                    obj->update(EngineTime::getDeltaTime());
//                    obj->updateTransformAndBuffers(width, height, index);
//                    if (cam->isEnabled())
//                        obj->render();
//                }
//            }
//        }
//
//        index++;
//    }
//}

//void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc)
//{
//    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
//    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();
//
//    int index = 0; 
//
//    for (Camera* cam : cameras) {
//        if (cam->cullingMask & Layer::DEBUG) {
//            context->setRasterizerState(renderSystem->getWireframeState());
//            context->clearDepth(sc);
//        }
//        else {
//            context->setRasterizerState(renderSystem->getSolidState());
//        }
//
////        std::cout << cam->getLayer() << std::endl;
//
//        //context->clearDepth(sc);
//
//        for (GameObject* obj : gameObjectList) {
//            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
//                if (obj != NULL) {
//                    obj->update(EngineTime::getDeltaTime());
//                    obj->updateTransformAndBuffers(width, height, vs, ps, index);
//                    if (cam->isEnabled())
//                        obj->render();
//                }
//            }
//        }
//
//        index++;
//    }
//}


//void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc, TexturePtr tex)
//{
//    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
//    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();
//
//    int index = 0;
//
//    for (Camera* cam : cameras) {
//        if (cam->cullingMask & Layer::DEBUG) {
//            context->setRasterizerState(renderSystem->getWireframeState());
//            context->clearDepth(sc);
//        }
//        else {
//            context->setRasterizerState(renderSystem->getSolidState());
//        }
//
//        //        std::cout << cam->getLayer() << std::endl;
//
//                //context->clearDepth(sc);
//
//        for (GameObject* obj : gameObjectList) {
//            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
//                if (obj != NULL) {
//                    obj->update(EngineTime::getDeltaTime());
//                    obj->updateTransformAndBuffers(width, height, vs, ps, index);
//                    if (cam->isEnabled())
//                        obj->render();
//                }
//            }
//        }
//
//        index++;
//    }
//}

void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, SwapChainPtr sc)
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
                    /*obj->update(EngineTime::getDeltaTime());
                    obj->updateTransformAndBuffers(width, height, index);
                    if (cam->isEnabled())
                        obj->render();*/

                    
                    ComponentList components = obj->getComponents();
                    for (int i = 0; i < components.size(); i++) {
                        if (components[i]->type == ComponentType::PHYSICS) {
                            Component* p6 = (PhysicsComponent*)components[i];
                            p6->update();
                        }
                        else if (components[i]->type == ComponentType::RENDERER) {
                            Renderer* renderer = (Renderer*)components[i];
                            renderer->update(obj->getConstant(), width, height, index);
                            if (cam->isEnabled())
                                renderer->draw(); 

                           /* components[i]->update(obj->getConstant(), width, height, index);
                            if (cam->isEnabled()) components[i]->draw();*/
                               
                        }
                    }
                    

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
            Cube* cubeObject = new Cube(adjustName("Cube"), shaderByteCode, sizeShader);
            this->addObject(cubeObject);
            std::cout << "Spawned Cube" << std::endl;
            break;
        }
   
        /*case PrimitiveType::PLANE: {
            Plane* planeObject = new Plane(adjustGameObjectName("Plane"), shaderByteCode, sizeShader);
            this->addObject(planeObject);
            std::cout << "Spawned Plane" << std::endl;
            break;
        }*/
    }
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            std::cout << "Deleted " << gameObject->getName() << std::endl;
            if (dynamic_cast<InputListener*>(this->gameObjectList[i]))
                InputSystem::get()->removeListener((InputListener*)this->gameObjectList[i]);

            //PhysicsComponent* p6component = gameObject->getComponent<PhysicsComponent>();
            ComponentList& components = this->gameObjectList[i]->getComponents();
            for (Component* c : components) {
                if (c) {
                    if (auto* p6component = dynamic_cast<PhysicsComponent*>(c))
                        PhysicsSystem::get()->removePhysicsComponent(p6component);

                    delete c;
                    c = nullptr;
                }
            }
            components.clear();

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

void GameObjectManager::createModel(String model, void* shaderByteCode, size_t sizeShader)
{
    /*if (model == "Teapot") {
        MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
        Model* model = new Model(adjustGameObjectName("Teapot"), mesh, shaderByteCode, sizeShader);
        this->addObject(model);
        std::cout << "Spawned Teapot" << std::endl;
    }
    else if (model == "Bunny") {
        MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
        Model* model = new Model(adjustGameObjectName("Bunny"), mesh, shaderByteCode, sizeShader);
        this->addObject(model);
        std::cout << "Spawned Bunny" << std::endl;
    }
    else if (model == "Armadillo") {
        MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
        Model* model = new Model(adjustGameObjectName("Armadillo"), mesh, shaderByteCode, sizeShader);
        this->addObject(model);
        std::cout << "Spawned Bunny" << std::endl;
    }*/
}

string GameObjectManager::adjustName(string name)
{
    string adjustedName;
    int count = 0;
    bool rootExists = true;


    for (GameObject* obj : this->gameObjectList) {
        string temp = obj->getName();
        if (temp.find(name) != std::string::npos) {
            count++;
        }
    }

    if (count > 0)
        adjustedName = name + " " + to_string(count);
    else
        adjustedName = name;

    return adjustedName;
}

void GameObjectManager::processDeletions()
{
    for (int i = 0; i < this->pendingDeletion.size(); i++) {
        if (InputListener* listener = dynamic_cast<InputListener*>(this->pendingDeletion[i])) {
            InputSystem::get()->removeListener(listener);
        }
        ComponentList& components = this->pendingDeletion[i]->getComponents();
        for (Component* c : components) {
            delete c;
        }
        components.clear();

        delete this->pendingDeletion[i];
        this->gameObjectList.erase(this->gameObjectList.begin() + i);
        this->pendingDeletion.clear();
    }
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
