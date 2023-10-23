#include "InspectorWindow.h"

InspectorWindow::InspectorWindow(std::string name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
	flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 800));
	ImGui::SetNextWindowPos(ImVec2(565, 20));

	ImGui::Begin("Inspector Window", nullptr, flags);
	ImGui::Text("No object selected. Select an object from the scene.");
	ImGui::End();
}
