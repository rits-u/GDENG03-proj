#pragma once

#include <vector>
#include "reactphysics3d/reactphysics3d.h"
#include "PhysicsComponent.h"
#include "Vector3D.h"
#include "EngineTime.h"


using namespace reactphysics3d;

class PhysicsComponent;
class PhysicsSystem
{
public:
	static PhysicsSystem* get();
	static void initialize();
	static void destroy();
	void addPhysicsComponent(PhysicsComponent* component);
	void removePhysicsComponent(PhysicsComponent* component);
	std::vector<PhysicsComponent*> getAllPhysicsComponents();
	void updateAllPhysicsComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	PhysicsSystem();
	~PhysicsSystem();
	PhysicsSystem(PhysicsSystem const&) {};
	PhysicsSystem& operator=(PhysicsSystem const&) {};
	static PhysicsSystem* sharedInstance;

private:
	std::vector<PhysicsComponent*> physicsComponentList;
	reactphysics3d::PhysicsWorld* physicsWorld;
	reactphysics3d::PhysicsCommon* physicsCommon;
};
