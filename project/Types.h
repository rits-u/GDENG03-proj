#pragma once


#include <string>
#include <vector>
#include <unordered_map>

class GameObject;
class Component;

typedef std::string String;
typedef std::vector<GameObject*> List;
typedef std::unordered_map<std::string, GameObject*> HashTable;
typedef std::vector<Component*> ComponentList;

enum PrimitiveType {
	CUBE,
	PLANE,
	QUAD,
	SPHERE,
	CYLINDER,
	CAPSULE
};