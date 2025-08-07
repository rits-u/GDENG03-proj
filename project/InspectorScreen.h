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

private:
	bool isRenaming = false;
	//char objName[128];
	char currentName[128] = "";
	bool useUniformScale = false;
};

