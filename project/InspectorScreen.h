#pragma once
#include "UIScreen.h"

#include "GameObjectManager.h"

class InspectorScreen : public UIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	void draw() override;
};

