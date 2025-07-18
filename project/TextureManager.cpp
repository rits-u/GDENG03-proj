#include "TextureManager.h"
#include "Texture.h"

//TextureManager* TextureManager::sharedInstance = nullptr;
//
//TextureManager* TextureManager::get()
//{
//    return sharedInstance;
//}
//
//void TextureManager::initialize()
//{
//    sharedInstance = new TextureManager();
//}
//
//void TextureManager::destroy()
//{
//    if (!TextureManager::sharedInstance)
//        return;
//
//    delete TextureManager::sharedInstance;
//}

TextureManager::TextureManager() : ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	//return std::static_pointer_cast<Texture>(ResourceManager::createResourceFromFile(filePath));
	return std::static_pointer_cast<Texture>(createResourceFromFile(filePath));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...) {}

	return tex;
}


