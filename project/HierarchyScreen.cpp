#include "HierarchyScreen.h"

HierarchyScreen::HierarchyScreen() : UIScreen("Hierarchy")
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::draw()
{
	if (this->activeSelf) {
		ImGui::Begin(this->getName().c_str(), &this->activeSelf);

		List gameObjects = GameObjectManager::get()->getAllObjects();
		for (GameObject* gameObject : gameObjects) {
			if (gameObject) {

				bool isSelected = (GameObjectManager::get()->getSelectedObject() == gameObject);


				if (ImGui::Selectable(gameObject->getName().c_str(), isSelected)) {
					GameObjectManager::get()->setSelectedObject(gameObject);
				}
			}
		}

		ImGui::End();
	}
}
