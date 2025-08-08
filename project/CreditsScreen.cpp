#include "CreditsScreen.h"
#include <iostream>

CreditsScreen::CreditsScreen() : UIScreen("Credits")
{
    this->imageWidth = 0;
    this->imageHeight = 0;
    this->myTexture = NULL;
    bool ret = LoadTextureFromFile("../../../dlsu-logo.png", &this->myTexture, &this->imageWidth, &this->imageHeight);
    IM_ASSERT(ret);
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::draw()
{
	if (this->activeSelf) {
		ImGui::Begin(this->getName().c_str(), &this->activeSelf, ImGuiWindowFlags_MenuBar);
		ImGui::Image((ImTextureID)(intptr_t)this->myTexture, ImVec2(this->imageWidth * 0.20f, this->imageHeight * 0.20f));
		ImGui::NewLine();
		ImGui::Text("About \n\n");;
		ImGui::Text("Scene Editor v0.02");
		ImGui::Text("Developed by Andrea Legaspi \n\n");
		String text = (String)"Acknowledgements:\n" +
					  (String)"PardCode Game Engine Tutorial\n" +
					          "Doc Neil's GDENG03 Course";
		ImGui::Text(text.c_str());
		ImGui::End();
	}

	//reference:
	//https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-directx11-users
}
