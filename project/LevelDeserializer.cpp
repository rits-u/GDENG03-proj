#include "LevelDeserializer.h"

LevelDeserializer::LevelDeserializer()
{
	this->folderName = "Levels/";
	this->levelName = "MyNewLevel";
}

void LevelDeserializer::LoadLevelFromFile()
{
    std::ifstream file(folderName + levelName + ".level");
    if (!file.is_open()) {
        std::cerr << "file cannot be loaded" << std::endl;
        return;
    }

    json j;
    file >> j;

    std::string levelName = j["levelName"];

    for (auto obj : j["gameObjects"]) {
        string name = obj["objectName"];
        GameObject* gameObject = new GameObject(name);

        auto pos = obj["transform"]["position"];
        Vector3D position = Vector3D(pos[0], pos[1], pos[2]);
        gameObject->setPosition(position);

        auto rot = obj["transform"]["rotation"];
        Vector3D rotation = Vector3D(rot[0], rot[1], rot[2]);
        gameObject->setRotation(rotation);

        auto sca = obj["transform"]["scale"];
        Vector3D scale = Vector3D(sca[0], sca[1], sca[2]);
        gameObject->setScale(scale);
        
        string type = obj["components"]["renderer"]["primitiveType"];
        addRendererComponent(gameObject, type);
       
        if(gameObject->getPrimitiveType() == PrimitiveType::CUBE)
            std::cout << "type: " << gameObject->getPrimitiveType() << std::endl;

        string physicsName = obj["components"]["physics"]["componentName"];
        if (physicsName != "") {
            gameObject->addComponent<PhysicsComponent>();
            PhysicsComponent* p6 = gameObject->getComponent<PhysicsComponent>();
            p6->mass = obj["components"]["physics"]["componentName"]["mass"];
            p6->useGravity = obj["components"]["physics"]["componentName"]["useGravity"];
            p6->shape = obj["components"]["physics"]["componentName"]["shape"];
        }        
    }
}

void LevelDeserializer::addRendererComponent(GameObject* obj, string type)
{
    GameObjectManager* manager = GameObjectManager::get();

    if (type == "CUBE") {
        obj->setPrimitiveType(PrimitiveType::CUBE);
        obj->addComponent<CubeRenderer>();
    }
    else if (type == "PLANE") {
        obj->setPrimitiveType(PrimitiveType::PLANE);
        obj->addComponent<PlaneRenderer>();
    }
    else if (type == "QUAD") {
        obj->setPrimitiveType(PrimitiveType::QUAD);
        obj->addComponent<QuadRenderer>();
    }
    else if (type == "SPHERE") {
        obj->setPrimitiveType(PrimitiveType::SPHERE);
        obj->addComponent<SphereRenderer>();
    }
    else if (type == "CYLINDER") {
        obj->setPrimitiveType(PrimitiveType::CYLINDER);
        obj->addComponent<CylinderRenderer>();
    }
    else if (type == "CAPSULE") {
        obj->setPrimitiveType(PrimitiveType::CAPSULE);
        obj->addComponent<CapsuleRenderer>();
    }

    manager->addObject(obj);
    manager->setSelectedObject(obj);
}

