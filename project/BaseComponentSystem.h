#pragma once
#include <string>
#include "PhysicsSystem.h"

class PhysicsSystem;
class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* get();
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};
	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
};

