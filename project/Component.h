#pragma once
//#include "Constant.h"
#include "GameObject.h"

enum class ComponentType {
	RENDERER,
	PHYSICS
};

class GameObject;
class Component
{
public:
	GameObject* owner = nullptr;

public:
	const ComponentType Type;
	Component(ComponentType type) : Type(type) {}
	Component(ComponentType type, GameObject* newOwner) : Type(type), owner(newOwner) {}

	//inline virtual Component* CreateSnapshot() = 0;

	virtual void update(constant cc) = 0;
	virtual void release() = 0;
	virtual void init() {}
};