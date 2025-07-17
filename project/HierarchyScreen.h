#pragma once
#include "UIScreen.h"

class HierarchyScreen : public UIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	void draw() override;
};

