#pragma once
#include <fstream>
#include <string>
#include <format>
#include "GameObjectManager.h"
//#include "Libs/json.hpp"
#include <nlohmann/json.hpp>
//using ordered_json = nlohmann::ordered_json;

class LevelSerializer
{
public:
	LevelSerializer();

public:
	void SaveLevelToFile();

private:
	std::string toString(PrimitiveType type);
	std::string toString(BodyType type);

private:
	std::string folderName;
	std::string levelName;
	//SaveScene
};

