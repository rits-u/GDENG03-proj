#pragma once
//#include "Constant.h"
#include "GameObject.h"
#include <iostream>

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
	const ComponentType type;
	Component(ComponentType type) : type(type) {}
	//Component(ComponentType type, GameObject* newOwner) : Type(type), owner(newOwner) {}

	virtual void update(constant cc) {};
	virtual void update(constant cc, int width, int height, int camIndex) {};
	virtual void release() = 0;
	virtual void init() {};
	virtual void draw() {};
};