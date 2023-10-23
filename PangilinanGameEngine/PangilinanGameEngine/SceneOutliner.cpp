#include "SceneOutliner.h"

SceneOutliner::SceneOutliner(std::string name) : AUIScreen(name)
{
}

SceneOutliner::~SceneOutliner()
{
}

void SceneOutliner::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
	flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::SetNextWindowContentSize(ImVec2(200, 800));
	ImGui::SetNextWindowPos(ImVec2(775, 20));
	ImGui::Begin("Scene Outliner", nullptr, flags);
	ImGui::End();
}
