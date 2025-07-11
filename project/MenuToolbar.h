#pragma once
#include "UIScreen.h"
#include "UIManager.h"
#include "UINames.h"

class MenuToolbar : public UIScreen
{
public:
	MenuToolbar();
	~MenuToolbar();

	void draw() override;
	void toggleUIScreen(String name);
	void openColorPickerUI();

private:
//	bool isActive;
	bool showColorPicker;
	bool showCredits;

	float myColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

};

