#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{

public:
	MeshManager();
	~MeshManager();

	MeshPtr createMeshFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);

};