#include "MenuToolbar.h"
#include <iostream>

MenuToolbar::MenuToolbar() : UIScreen("Menu Toolbar")
{
	//this->isActive = true;
    this->showColorPicker = false;
    this->showCredits = false;

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
                //howCredits = !showCredits;
            }
            //if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Handle Open */ }
            //if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Handle Save */ }
            ImGui::EndMenu();
        }

        //if (ImGui::MenuItem("Color")) {
        //   // showColorPicker = !showColorPicker;
        //}
        //ImGui::EndMenu();

        if (ImGui::BeginMenu("Color")) {
            if (ImGui::MenuItem("Show Color Picker")) {
                showColorPicker = !showColorPicker;
            }
            ImGui::EndMenu();
        }

        //if (ImGui::BeginMenu("Edit"))
        //{
        //    if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Handle Undo */ }
        //    if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { /* Disabled item */ }
        //    ImGui::EndMenu();
        //}

        //if (ImGui::BeginMenu("Help"))
        //{
        //    if (ImGui::MenuItem("About")) { /* Handle About */ }
        //    ImGui::EndMenu();
        //}

        ImGui::EndMainMenuBar();
    }

    ImGuiIO& io = ImGui::GetIO();
    if (io.KeyCtrl && ImGui::IsKeyPressed('C', false))
    {
        this->toggleUIScreen(uiNames.CREDITS_SCREEN);   
       // showCredits = !showCredits;
       // UIScreen* ui = UIManager::get()->getUIScreenByName(name);
     /*   if (!UIManager::get()->getUIScreenByName(uiNames.CREDITS_SCREEN)->isActive())
            showCredits = 
        else
            this->deactivateUIScreen(uiNames.CREDITS_SCREEN);*/

          // Keyboard triggers this
    }

    if (showColorPicker)
        this->openColorPickerUI();

    //if (showCredits)
    //    this->activateUIScreen(uiNames.CREDITS_SCREEN);
    //else
    //    this->deactivateUIScreen(uiNames.CREDITS_SCREEN);

}

void MenuToolbar::toggleUIScreen(String name)
{
    UIScreen* ui = UIManager::get()->getUIScreenByName(name);
    if (ui->isActive())
        ui->setActive(false);
    else
        ui->setActive(true);
}

//void MenuToolbar::deactivateUIScreen(String name)
//{
//    UIScreen* ui = UIManager::get()->getUIScreenByName(name);
//    ui->setActive(false);
//    //std::cout << "?" << std::endl;
//}

void MenuToolbar::openColorPickerUI()
{
    if (showColorPicker) {
        ImGui::Begin("Color Picker Screen", &this->showColorPicker, ImGuiWindowFlags_MenuBar);
        ImGui::ColorPicker3("Color", this->myColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
        ImGui::End();
    }
}
