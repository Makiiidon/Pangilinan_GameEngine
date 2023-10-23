#include "ToolBar.h"

ToolBar::ToolBar(std::string name) : AUIScreen(name)
{

}

ToolBar::~ToolBar()
{
}

void ToolBar::drawUI()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("New")) {
		ImGui::MenuItem("Newer");
		ImGui::EndMenu();

	}
	

	ImGui::MenuItem("Test");
	ImGui::MenuItem("Old");

	ImGui::EndMainMenuBar();

}
