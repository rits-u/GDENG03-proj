#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{

public:
	MeshManager();
	~MeshManager();

	MeshPtr createMeshFromFile(const wchar_t* filePath);
	//MeshPtr createMeshFromFile(const wchar_t* filePath, void* shaderByteCode, size_t sizeShader);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);
	//virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath, void* shaderByteCode, size_t sizeShader);

};
