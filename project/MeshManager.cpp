#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* filePath)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(filePath));
}

//MeshPtr MeshManager::createMeshFromFile(const wchar_t* filePath, void* shaderByteCode, size_t sizeShader)
//{
//	return std::static_pointer_cast<Mesh>(createResourceFromFile(filePath, shaderByteCode, sizeShader));
//}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(filePath);
	}
	catch (...) {}

	return mesh;
}

//Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath, void* shaderByteCode, size_t sizeShader)
//{
//	Mesh* mesh = nullptr;
//	try
//	{
//		mesh = new Mesh(filePath, shaderByteCode, sizeShader);
//	}
//	catch (...) {}
//
//	return mesh;
//}
