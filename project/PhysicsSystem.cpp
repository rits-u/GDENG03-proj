#include "PhysicsSystem.h"
typedef std::vector<PhysicsComponent*> ComponentList;

PhysicsSystem::PhysicsSystem()
{
    this->componentList.clear();
    this->componentTable.clear();
    this->physicsCommon = nullptr;
    this->physicsWorld = nullptr;
}

PhysicsSystem::~PhysicsSystem()
{
    for (int i = 0; i < this->componentList.size(); i++) {
        delete this->componentList[i];
    }

    componentList.clear();
    componentTable.clear();
    this->physicsCommon = nullptr;
    this->physicsWorld = nullptr;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
    this->componentList.push_back(component);
    this->componentTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
    if (this->componentTable[component->getName()] != NULL) {
        this->componentTable.erase(component->getName());
        int index = -1;
        for (int i = 0; i < this->componentList.size(); i++) {
            if (this->componentList[i] == component) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            this->componentList.erase(this->componentList.begin() + index);
        }
    }
    else {
        std::cout << "Component " << component->getName() << " not registered in physics compononent. \n";
    }

   
}

void PhysicsSystem::unregisterComponentByName(String name)
{
    if (this->componentTable[name] != NULL) {
        this->unregisterComponent(this->componentTable[name]);
    }
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
    if (this->componentTable[name] == NULL) {
        std::cout << "Component " << name << " not registered in physics compononent. \n";
    }

    return this->componentTable[name];
}

ComponentList PhysicsSystem::getAllComponents()
{
    return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
    if (EngineTime::getDeltaTime() > 0.0f) {
        this->physicsWorld->update(EngineTime::getDeltaTime());
        for (int i = 0; i < this->componentList.size(); i++) {
            this->componentList[i]->perform(EngineTime::getDeltaTime());
        }
    }
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
    return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
    return this->physicsCommon;
}
