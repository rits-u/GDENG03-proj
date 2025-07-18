#include "InspectorScreen.h"

InspectorScreen::InspectorScreen() : UIScreen("Inspector Screen")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::draw()
{
	if (!activeSelf) return;

	GameObject* selectedObject = GameObjectManager::get()->getSelectedObject();
	
	ImGui::Begin(this->getName().c_str(), &this->activeSelf);

	if(selectedObject) {
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), selectedObject->getName().c_str());
		ImGui::Separator();
		ImGui::Text("Transform");

		Vector3D pos = selectedObject->getLocalPosition();
		if (ImGui::DragFloat3("Position", &pos.m_x, 0.1f)) {
			selectedObject->setPosition(pos);
		}

		Vector3D rot = selectedObject->getLocalRotation();
		if (ImGui::DragFloat3("Rotation", &rot.m_x, 0.1f)) {
			selectedObject->setRotation(rot);
		}

		ImGui::Checkbox("Uniform Scale", &this->useUniformScale);
		if (!this->useUniformScale) {
			Vector3D scale = selectedObject->getLocalScale();
			if (ImGui::DragFloat3("Scale", &scale.m_x, 0.1f)) {
				selectedObject->setScale(scale);
			}
		}
		else {
			//Vector3D scale =
			float uni = selectedObject->getLocalScale().m_x;
			if (ImGui::DragFloat("Scale", &uni, 0.1f)) {
				selectedObject->setScale(Vector3D(uni, uni, uni));
			}
		}
	
	/*	if (ImGui::DragFloat3("Scale", &scale.m_x, 0.1f)) {
			selectedObject->setScale(scale);
		}*/
		ImGui::NewLine(); ImGui::Separator();

		if (ImGui::Button("Delete")) {
			GameObjectManager::get()->deleteObject(selectedObject);
			selectedObject = nullptr;
		
			//GameObjectManager::get()->markDeletion(selectedObject);
			//selectedObject = nullptr;
			GameObjectManager::get()->clearSelectedObject();

		}
		
	}

	ImGui::End();
	
}
