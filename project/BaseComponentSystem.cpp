#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::get()
{
    return nullptr;
}

void BaseComponentSystem::initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
	if (!BaseComponentSystem::sharedInstance)
		return;

	delete BaseComponentSystem::sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	if (this->physicsSystem)
		return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	try
	{
		physicsSystem = new PhysicsSystem();
	}
	catch (...) { throw std::exception("PhysicsSystem not created successfully"); }
}

BaseComponentSystem::~BaseComponentSystem()
{
    BaseComponentSystem::sharedInstance = nullptr;
}
