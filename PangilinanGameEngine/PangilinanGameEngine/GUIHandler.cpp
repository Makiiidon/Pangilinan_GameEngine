#include "GUIHandler.h"
#include "imgui_stdlib.h"
#include <iostream>
#include <string>

GUIHandler* GUIHandler::sharedInstance = nullptr;

GUIHandler::GUIHandler()
{
}

GUIHandler::~GUIHandler()
{
}

bool GUIHandler::init(HWND hwnd, ID3D11Device *device, ID3D11DeviceContext *device_context)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, device_context);

	return true;
}

void GUIHandler::onUpdateStart()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool showDemoWindow = false;
	static bool isPlayAnimation = true;
	ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
	static float color[4] = {0,0,0,0};

	ImGui::Begin("Scene Settings");
	ImGui::Text("Below are settongs for configuring the Scene");

	ImGui::Checkbox("Show Demo Window", &showDemoWindow);

	if (showDemoWindow)
		ImGui::ShowDemoWindow(); // Show demo window! :)
	

	static ImGuiColorEditFlags colorEditFlag = ImGuiColorEditFlags_DisplayRGB;

	ImGui::ColorEdit4("Color", color, colorEditFlag);

	std::string animationButtonStr = "Play Animation";
	if (!isPlayAnimation) animationButtonStr = "Resume Animation";

	if (ImGui::Button( animationButtonStr.c_str()))
	{
		isPlayAnimation = !isPlayAnimation;
	}

	ImGui::End();
}

void GUIHandler::onUpdateEnd()
{
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

bool GUIHandler::release()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return true;
}


GUIHandler* GUIHandler::get()
{
	return nullptr;
}
