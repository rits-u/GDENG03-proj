#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

PhysicsSystem* PhysicsSystem::sharedInstance = nullptr;

PhysicsSystem* PhysicsSystem::get()
{
    return sharedInstance;
}

void PhysicsSystem::initialize()
{
    sharedInstance = new PhysicsSystem();
    sharedInstance->physicsCommon = new reactphysics3d::PhysicsCommon();
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
    sharedInstance->physicsWorld = sharedInstance->physicsCommon->createPhysicsWorld(settings);
}

void PhysicsSystem::destroy()
{
    if (!PhysicsSystem::sharedInstance)
        return;

    delete PhysicsSystem::sharedInstance;
}

void PhysicsSystem::addPhysicsComponent(PhysicsComponent* component)
{
    for (auto* pc : physicsComponentList)
        if (pc == component)
            return; 

    this->physicsComponentList.push_back(component);
}

void PhysicsSystem::removePhysicsComponent(PhysicsComponent* component)
{
    for (int i = 0; i < physicsComponentList.size(); i++) {
        std::cout << "Component at " << i << ": " << physicsComponentList[i] << std::endl;
    }

    int index = -1;
    for (int i = 0; i < physicsComponentList.size(); i++) {
        if (component == physicsComponentList[i]) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        physicsComponentList.erase(physicsComponentList.begin() + index);
    }

    std::cout << "index: " << index << std::endl;

}

std::vector<PhysicsComponent*> PhysicsSystem::getAllPhysicsComponents()
{
    return this->physicsComponentList;
}


void PhysicsSystem::updateAllPhysicsComponents()
{
    if (EngineTime::getDeltaTime() > 0.0f) {
        physicsWorld->update(EngineTime::getDeltaTime());
        for (PhysicsComponent* pc : physicsComponentList) {
            if(pc)
                pc->update();
        }
    }
}

reactphysics3d::PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
    return this->physicsWorld;
}

reactphysics3d::PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
    return this->physicsCommon;
}

PhysicsSystem::PhysicsSystem()
{
    this->physicsComponentList.clear();
    PhysicsWorld* physicsWorld = nullptr;
    PhysicsCommon* physicsCommon = nullptr;
}

PhysicsSystem::~PhysicsSystem()
{
    for (int i = 0; i < this->physicsComponentList.size(); i++) {
        delete this->physicsComponentList[i];
    }

    physicsComponentList.clear();
    PhysicsSystem::sharedInstance = nullptr;
}
