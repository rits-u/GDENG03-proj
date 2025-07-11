#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "Window.h"
#include "UIScreen.h"

class UINames {
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLOR_PICKER = "COLOR_PICKER";
	const String MENU_TOOLBAR = "MENU_TOOLBAR";
};
