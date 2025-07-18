#include "ResourceManager.h"
#include <filesystem>

//ResourceManager* ResourceManager::sharedInstance = nullptr;
//
//ResourceManager* ResourceManager::get()
//{
//    return sharedInstance;
//}
//
//void ResourceManager::initialize()
//{
//    sharedInstance = new ResourceManager();
//}
//
//void ResourceManager::destroy()
//{
//    if (!ResourceManager::sharedInstance)
//        return;
//
//    delete ResourceManager::sharedInstance;
//}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* filePath)
{
    std::wstring fullPath = std::filesystem::absolute(filePath);
    auto it = mapResources.find(fullPath);

    if (it != mapResources.end())
        return it->second;

    Resource* rawResource = this->createResourceFromFileConcrete(fullPath.c_str());

    if (rawResource) {
        ResourcePtr resource(rawResource);
        mapResources[fullPath] = resource;
        return resource;
    }

    return nullptr;
}
//
//Resource* ResourceManager::createResourceFromFileConcrete(const wchar_t* filePath)
//{
//    return nullptr;
//}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
