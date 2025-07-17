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
		ImGui::Begin(this->getName().c_str(), &this->activeSelf, ImGuiWindowFlags_MenuBar);
		ImGui::End();
	}
}
