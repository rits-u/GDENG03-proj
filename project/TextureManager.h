#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
//public:
//	static TextureManager* get();
//	static void initialize();
//	static void destroy();

public:
	TextureManager();
	~TextureManager();

	TexturePtr createTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);

//private:
//	TextureManager();
//	~TextureManager();
//	TextureManager(TextureManager const&) {};
//	TextureManager& operator=(TextureManager const&) {};
//	static TextureManager* sharedInstance;


};

