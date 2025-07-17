#pragma once


#include <string>
#include <vector>
#include <unordered_map>

class GameObject;

typedef std::string String;
typedef std::vector<GameObject*> List;
typedef std::unordered_map<std::string, GameObject*> HashTable;