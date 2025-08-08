#pragma once
#include "UIScreen.h"

#include "GameObjectManager.h"

class HierarchyScreen : public UIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	void draw() override;
};

