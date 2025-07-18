#pragma once
#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
//public:
//	static ResourceManager* get();
//	static void initialize();
//	static void destroy();

public:
	ResourceManager();
	~ResourceManager();

public:
	ResourcePtr createResourceFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) = 0;

//private:
//	ResourceManager();
//	~ResourceManager();
//	ResourceManager(ResourceManager const&) {};
//	ResourceManager& operator=(ResourceManager const&) {};
//	static ResourceManager* sharedInstance;


private:
	std::unordered_map<std::wstring, ResourcePtr> mapResources;
};

