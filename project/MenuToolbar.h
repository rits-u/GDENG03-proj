#pragma once
#include "UIScreen.h"
#include "UIManager.h"
#include "UINames.h"
#include "GameObjectManager.h"

class GameObjectManager;

class MenuToolbar : public UIScreen
{
public:
	MenuToolbar();
	~MenuToolbar();

	void draw() override;
	void toggleUIScreen(String name);
	void openColorPickerUI();
	void setShaders(void* shaderByteCode, size_t sizeShader);

private:
//	bool isActive;
	bool showColorPicker;
	void* shaderByteCode;
	size_t sizeShader;

	//bool showCredits;

	float myColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

};

