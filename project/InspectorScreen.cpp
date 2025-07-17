#include "InspectorScreen.h"

InspectorScreen::InspectorScreen() : UIScreen("Inspector Screen")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::draw()
{
	if (this->activeSelf) {
		ImGui::Begin(this->getName().c_str(), &this->activeSelf, ImGuiWindowFlags_MenuBar);
		
		ImGui::End();
	}
}
