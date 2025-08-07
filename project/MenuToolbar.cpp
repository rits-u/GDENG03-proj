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

        if (ImGui::BeginMenu("Game Object")) {
            if (ImGui::MenuItem("Cube")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Cube"));
                obj->AddComponent<CubeRenderer>();
                manager->addObject(obj);
            }
            if (ImGui::MenuItem("Plane")) {
                GameObjectManager::get()->createObject(GameObjectManager::PrimitiveType::PLANE, this->shaderByteCode, this->sizeShader);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("3D Objects")) {
            if (ImGui::MenuItem("Teapot")) {
                GameObjectManager::get()->createModel("Teapot", this->shaderByteCode, this->sizeShader);
            }
            if (ImGui::MenuItem("Bunny")) {
                GameObjectManager::get()->createModel("Bunny", this->shaderByteCode, this->sizeShader);
            }
            if (ImGui::MenuItem("Armadillo")) {
                GameObjectManager::get()->createModel("Armadillo", this->shaderByteCode, this->sizeShader);
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


void MenuToolbar::setShaders(void* shaderByteCode, size_t sizeShader)
{
    this->shaderByteCode = shaderByteCode;
    this->sizeShader = sizeShader;
}
