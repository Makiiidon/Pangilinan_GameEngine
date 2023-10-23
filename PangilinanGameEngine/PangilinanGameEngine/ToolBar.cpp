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

	// FILE
	if (ImGui::BeginMenu("File")) {
		ImGui::MenuItem("New");
		ImGui::MenuItem("Save");
		ImGui::MenuItem("Open");
		ImGui::MenuItem("Exit");
		ImGui::EndMenu();
	}
	
	// GAME OBJECTS
	if (ImGui::BeginMenu("Game Object")) {
		ImGui::MenuItem("Create Cube");
		ImGui::MenuItem("Create Sphere");
		ImGui::MenuItem("Create Plane");

		// LIGHTS
		if (ImGui::BeginMenu("Light")) {
			ImGui::MenuItem("Create Point Light");
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

}
