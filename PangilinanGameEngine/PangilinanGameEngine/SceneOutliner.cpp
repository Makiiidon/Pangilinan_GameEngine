#include "SceneOutliner.h"
#include "GameObjectManager.h"

SceneOutliner::SceneOutliner(std::string name) : AUIScreen(name)
{
}

SceneOutliner::~SceneOutliner()
{
}

void SceneOutliner::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
	ImGui::SetNextWindowContentSize(ImVec2(200, 800));
	ImGui::SetNextWindowPos(ImVec2(560, 20));

	ImGui::Begin("Scene Outliner", nullptr, flags);

	for (int i = 0; i < GameObjectManager::getInstance()->getAllGameObjects().size(); i++) 
	{
		if (ImGui::Button(GameObjectManager::getInstance()->getAllGameObjects()[i]->getName().c_str(), ImVec2(190, 20)))
		{
			GameObjectManager::getInstance()->setSelectedObject(GameObjectManager::getInstance()->getAllGameObjects()[i]);
		}
	}
	ImGui::End();
}
