#include "UIManager.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "ToolBar.h"
#include "SceneOutliner.h"
#include "InspectorWindow.h"
#include "EngineProfiler.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
}

void UIManager::destroy()
{

}

void UIManager::drawAllUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < uiList.size(); i++) 
	{
		uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	UINames uiNames;

	ToolBar* toolBar = new ToolBar(uiNames.MENU_SCREEN);
	uiList.push_back(toolBar);

	SceneOutliner* sceneOutliner = new SceneOutliner(uiNames.HIERARCHY_SCREEN);
	uiList.push_back(sceneOutliner);

	InspectorWindow* inspectorWindow = new InspectorWindow(uiNames.INSPECTOR_SCREEN);
	uiList.push_back(inspectorWindow);

	EngineProfiler* engineProfiler = new EngineProfiler(uiNames.PROFILER_SCREEN);
	uiList.push_back(engineProfiler);

	for (int i = 0; i < uiList.size(); i++)
	{
		std::cout << uiList[i]->getName() << " initialized\n";
	}
}

UIManager::~UIManager()
{

}
