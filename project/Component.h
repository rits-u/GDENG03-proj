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
	const ComponentType type;
	Component(ComponentType type) : type(type) {}
	//Component(ComponentType type, GameObject* newOwner) : Type(type), owner(newOwner) {}
	
	virtual void init() {};
	virtual void release() = 0;
	virtual void update() {};
	//virtual void update(constant cc, int width, int height, int camIndex) {};


	//virtual void draw() {};
public:
	inline GameObject* getOwner() { return this->owner; }
	void setOwner(GameObject* owner) { this->owner = owner; }

private:
	GameObject* owner = nullptr;

};

