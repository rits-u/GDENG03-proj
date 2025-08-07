#pragma once
#include "UIScreen.h"

#include "GameObjectManager.h"

class InspectorScreen : public UIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	void draw() override;

private:
	void displayObjectName();
	void displayTransform();
	void displayTextureSection();

private:
	bool isRenaming = false;
	bool enableTextureSelection = false;
	//char objName[128];
	char currentName[128] = "";
	bool useUniformScale = false;
	int textureItem = 0;
	string currTexture = "None";
};

