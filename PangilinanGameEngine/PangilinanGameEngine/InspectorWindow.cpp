#include "InspectorWindow.h"
#include "GameObjectManager.h"

InspectorWindow::InspectorWindow(std::string name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
	ImGui::SetNextWindowContentSize(ImVec2(200, 800));
	ImGui::SetNextWindowPos(ImVec2(775, 20));

	ImGui::Begin("Inspector Window", nullptr, flags);

	AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

	if(selectedObject == nullptr)
		ImGui::Text("No object selected. Select an object from the scene.");

	else 
	{
		std::string objName = "Selected Object: " + selectedObject->getName();
		ImGui::Text(objName.c_str());

		bool isActive = selectedObject->isGameObjectActive();
		if (ImGui::Checkbox("Enabled", &isActive))
		{
			selectedObject->setActive(isActive);
		}

		Vector3D pos = selectedObject->getLocalPosition();
		Vector3D rot = selectedObject->getLocalRotation();
		Vector3D scale = selectedObject->getScale();
		float position[] = { pos.m_x,pos.m_y,pos.m_z };
		float rotation[] = { rot.m_x,rot.m_y,rot.m_z };
		float scaler[] = { scale.m_x,scale.m_y,scale.m_z };
		ImGui::DragFloat3("Position", position, 0.1f);
		ImGui::DragFloat3("Rotation", rotation, 0.01f);
		ImGui::DragFloat3("Scale", scaler, 0.1f);
		selectedObject->setPosition(position[0], position[1], position[2]);
		selectedObject->setRotation(rotation[0], rotation[1], rotation[2]);
		selectedObject->setScale(scaler[0], scaler[1], scaler[2]);
	}
	ImGui::End();
}
