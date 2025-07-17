#pragma once
#include "UIScreen.h"

class InspectorScreen : public UIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	void draw() override;
};

