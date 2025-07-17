#include "MenuToolbar.h"
#include <iostream>

MenuToolbar::MenuToolbar() : UIScreen("Menu Toolbar")
{
	//this->isActive = true;
    this->showColorPicker = false;
   // this->showCredits = false;

}

MenuToolbar::~MenuToolbar()
{
	
}

void MenuToolbar::draw()
{
    UINames uiNames;

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("Credits")) {
                this->toggleUIScreen(uiNames.CREDITS_SCREEN);
            }
            ImGui::EndMenu();
        }   

        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Hierarchy")) {
                this->toggleUIScreen(uiNames.HIERARCHY_SCREEN);
            }
            if (ImGui::MenuItem("Inspector")) {
                this->toggleUIScreen(uiNames.INSPECTOR_SCREEN);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Color")) {
            if (ImGui::MenuItem("Show Color Picker")) {
                showColorPicker = !showColorPicker;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGuiIO& io = ImGui::GetIO();
    if (io.KeyCtrl && ImGui::IsKeyPressed('C', false))
    {
        this->toggleUIScreen(uiNames.CREDITS_SCREEN);   
    }

    if (showColorPicker)
        this->openColorPickerUI();

}

void MenuToolbar::toggleUIScreen(String name)
{
    UIScreen* ui = UIManager::get()->getUIScreenByName(name);
    if (ui->isActive())
        ui->setActive(false);
    else
        ui->setActive(true);
}


void MenuToolbar::openColorPickerUI()
{
    if (showColorPicker) {
        ImGui::Begin("Color Picker Screen", &this->showColorPicker, ImGuiWindowFlags_MenuBar);
        ImGui::ColorPicker3("Color", this->myColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
        ImGui::End();
    }
}
