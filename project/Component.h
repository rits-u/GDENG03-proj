#pragma once
//#include "Constant.h"
#include "GameObject.h"
#include <iostream>
#include <string>

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
	Component(std::string name, ComponentType type) : name(name), type(type) {}
	
	virtual void init() {};
	virtual void release() = 0;
	virtual void update() {};

public:
	inline GameObject* getOwner() { return this->owner; }
	void setOwner(GameObject* owner) { this->owner = owner; }

	inline std::string getName() { return this->name; }
	void setName(std::string name) { this->name = name; }

private:
	GameObject* owner = nullptr;
	std::string name;

};

