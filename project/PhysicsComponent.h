#pragma once
#include "reactphysics3d/reactphysics3d.h"
#include "Component.h"
#include "PhysicsSystem.h"
#include "GameObjectManager.h"

using namespace reactphysics3d;

class PhysicsSystem;
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(BodyType type);
	void init() override;
	void update() override;
	void release() override;

	RigidBody* getRigidBody();
	void setBodyType(BodyType type);
	BodyType getBodyType();

private:
	CollisionShape* createColliderShape(PrimitiveType type);
	Quaternion EulerToQuaternion(Vector3D euler);
	Vector3D QuaternionToEuler(reactphysics3d::Quaternion q);

public:
	bool hasRB = false;

private:
	float mass;
	RigidBody* rigidBody;
	BodyType bodyType;


};

