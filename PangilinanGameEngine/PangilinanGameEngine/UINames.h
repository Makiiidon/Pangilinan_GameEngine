#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"


class UINames
{
public:
	UINames() {
		PROFILER_SCREEN = "PROFILER_SCREEN";
		MENU_SCREEN = "MENU_SCREEN";
		INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
		HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	}
	~UINames() {}
	std::string PROFILER_SCREEN;
	std::string MENU_SCREEN;
	std::string INSPECTOR_SCREEN;
	std::string HIERARCHY_SCREEN;
};




