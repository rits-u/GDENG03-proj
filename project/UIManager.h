#pragma once
//#include <string>
//#include <vector>
#include "UINames.h"
#include "UIScreen.h"

#include "CreditsScreen.h"
#include "MenuToolbar.h"

#include "RenderSystem.h"
#include "GraphicsEngine.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<UIScreen*> UIList;
	typedef std::unordered_map<String, UIScreen*> UIMap;

	static UIManager* get();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	UIScreen* getUIScreenByName(String name);

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UIMap uiMap;

public:
	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;
};



