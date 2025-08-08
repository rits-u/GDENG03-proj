#pragma once
#include "UIScreen.h"
#include "UIManager.h"
#include "UINames.h"
#include "GameObjectManager.h"
#include "LevelSerializer.h"
#include "LevelDeserializer.h"

class GameObjectManager;

class MenuToolbar : public UIScreen
{
public:
	MenuToolbar();
	~MenuToolbar();

	void draw() override;

private:
	void toggleUIScreen(String name);
	void openColorPickerUI();

private:
	LevelSerializer* levelSerializer;
	LevelDeserializer* levelDeserializer;
	
	bool showColorPicker;
	void* shaderByteCode;
	size_t sizeShader;

	float myColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

};

