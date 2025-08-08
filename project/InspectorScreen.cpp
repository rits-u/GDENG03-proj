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
		this->displayObjectName();
		this->displayTransform();

		ImGui::NewLine(); ImGui::Separator();
		if (selectedObject) {
			if (!selectedObject->getComponent<Renderer>()->hasTexture &&
				!selectedObject->getComponent<Renderer>()->enableTextureSelection)
			{
				if (ImGui::Button("Add Texture")) {
					selectedObject->getComponent<Renderer>()->enableTextureSelection = true;
				}
			}
			else {
				this->displayTextureSection();
			}
		}

		ImGui::NewLine(); ImGui::Separator();
		this->displayPhysicsComponent();

		ImGui::NewLine(); ImGui::Separator();
		if (ImGui::Button("Delete Object")) {
			GameObjectManager::get()->deleteObject(selectedObject);
			selectedObject = nullptr;
			GameObjectManager::get()->clearSelectedObject();
			ImGui::End();
			return;
		}
		
	}

	ImGui::End();
	
}

void InspectorScreen::displayObjectName()
{
	GameObject* selectedObject = GameObjectManager::get()->getSelectedObject();

	if (!this->isRenaming) {
		std::string temp = selectedObject->getName();
		
		strcpy_s(currentName, sizeof(currentName), temp.c_str());
		
		if (ImGui::Selectable(currentName, false, ImGuiSelectableFlags_AllowDoubleClick)) {
			if (ImGui::IsMouseDoubleClicked(0))
			{
				this->isRenaming = true;
				ImGui::SetKeyboardFocusHere();
			}
		}
	}
	else {
		ImGui::SetNextItemWidth(150);
		if (ImGui::InputText("##Rename", currentName, IM_ARRAYSIZE(currentName), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
		{
			selectedObject->setName(currentName);
			this->isRenaming = false;
		}
		if (!ImGui::IsItemActive())
		{
			selectedObject->setName(currentName);
			this->isRenaming = false;
		}
	}

	ImGui::NewLine();
	ImGui::Separator();

}

void InspectorScreen::displayTransform()
{
	GameObject* selectedObject = GameObjectManager::get()->getSelectedObject();

	ImGui::Text("Transform");

	Vector3D pos = selectedObject->getPosition();
	if (ImGui::DragFloat3("Position", &pos.m_x, 0.1f)) {
		selectedObject->setPosition(pos);
	}

	Vector3D rot = selectedObject->getRotation();
	if (ImGui::DragFloat3("Rotation", &rot.m_x, 0.1f)) {
		selectedObject->setRotation(rot);
	}

	ImGui::Checkbox("Uniform Scale", &this->useUniformScale);
	if (!this->useUniformScale) {
		Vector3D scale = selectedObject->getScale();
		if (ImGui::DragFloat3("Scale", &scale.m_x, 0.1f)) {
			selectedObject->setScale(scale);
		}
	}
	else {
		//Vector3D scale =
		float uni = selectedObject->getScale().m_x;
		if (ImGui::DragFloat("Scale", &uni, 0.1f)) {
			selectedObject->setScale(Vector3D(uni, uni, uni));
		}
	}
}

void InspectorScreen::displayTextureSection()
{
	GameObject* selectedObject = GameObjectManager::get()->getSelectedObject();
	Renderer* renderer = selectedObject->getComponent<Renderer>();

	std::vector<std::string> items = { "None", "Brick", "Wood", "Grass", "Ground", "Sand", "Wall" };

	static GameObject* prevSelectedObject = nullptr;
	if (selectedObject != prevSelectedObject) {
		prevSelectedObject = selectedObject;
		this->textureItem = 0;

		for (int i = 0; i < items.size(); ++i) {
			if (items[i] == renderer->texName) {
				this->textureItem = i;
				break;
			}
		}
	}

	ImGui::Text("Texture");

	if (ImGui::BeginCombo("##Texture", items[this->textureItem].c_str())) {
		for (int i = 0; i < items.size(); i++) {
			bool selected = (this->textureItem == i);
			if (ImGui::Selectable(items[i].c_str(), selected))
				this->textureItem = i;

			if (selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	renderer->setTexture(items[this->textureItem]);

	ImGui::NewLine();
	if (ImGui::Button("Remove Texture")) {
		renderer->setTexture("None");
		renderer->enableTextureSelection = false;
		this->textureItem = 0;
		
	}
}

void InspectorScreen::displayPhysicsComponent()
{
	GameObject* selectedObject = GameObjectManager::get()->getSelectedObject();
	PhysicsComponent* p6 = selectedObject->getComponent<PhysicsComponent>();

	if (!p6) {
		if (ImGui::Button("Add Physics Component")) {
			PhysicsComponent* newComp = selectedObject->addComponent<PhysicsComponent>(BodyType::STATIC);
		}
		return;
	}


	std::vector<std::string> items = { "STATIC", "DYNAMIC" };
	int currentRbItem = (p6->getBodyType() == reactphysics3d::BodyType::STATIC) ? 0 : 1;

	ImGui::Text("RigidBody");
	if (ImGui::BeginCombo("##Rigid Body", items[currentRbItem].c_str())) {
		for (int i = 0; i < items.size(); i++) {
			bool selected = (currentRbItem == i);
			if (ImGui::Selectable(items[i].c_str(), selected)) {
				if (i == 0)
					p6->setBodyType(reactphysics3d::BodyType::STATIC);
				else if (i == 1)
					p6->setBodyType(reactphysics3d::BodyType::DYNAMIC);
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (p6->getBodyType() == BodyType::DYNAMIC) {
		ImGui::Checkbox("Use Gravity", &p6->useGravity);
	}
}
