#pragma once
#include <fstream>
#include <string>
#include <format>
#include "GameObjectManager.h"
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;

class LevelDeserializer
{
public:
	LevelDeserializer();

public:
	void LoadLevelFromFile();

private:
	void addRendererComponent(GameObject* obj, string type);

private:
	std::string folderName;
	std::string levelName;
};