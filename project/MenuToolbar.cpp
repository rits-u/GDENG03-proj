#include "MenuToolbar.h"
#include <iostream>

MenuToolbar::MenuToolbar() : UIScreen("Menu Toolbar")
{
	//this->isActive = true;
    this->showColorPicker = false;
    this->levelSerializer = new LevelSerializer();
    this->levelDeserializer = new LevelDeserializer();
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
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save Level")) {
                levelSerializer->SaveLevelToFile(); 
            }
            if (ImGui::MenuItem("Load Level")) {
                levelDeserializer->LoadLevelFromFile();
            }
            ImGui::EndMenu();
        }

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
                obj->setPrimitiveType(PrimitiveType::CUBE);
                obj->addComponent<CubeRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            if (ImGui::MenuItem("Plane")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Plane"));
                obj->setPrimitiveType(PrimitiveType::PLANE);
                obj->addComponent<PlaneRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            if (ImGui::MenuItem("Quad")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Quad"));
                obj->setPrimitiveType(PrimitiveType::QUAD);
                obj->addComponent<QuadRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            if (ImGui::MenuItem("Sphere")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Sphere"));
                obj->setPrimitiveType(PrimitiveType::SPHERE);
                obj->addComponent<SphereRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            if (ImGui::MenuItem("Cylinder")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Cylinder"));
                obj->setPrimitiveType(PrimitiveType::CYLINDER);
                obj->addComponent<CylinderRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            if (ImGui::MenuItem("Capsule")) {
                GameObjectManager* manager = GameObjectManager::get();
                GameObject* obj = new GameObject(manager->adjustName("Capsule"));
                obj->setPrimitiveType(PrimitiveType::CAPSULE);
                obj->addComponent<CapsuleRenderer>();
                manager->addObject(obj);
                manager->setSelectedObject(obj);
            }
            
            ImGui::EndMenu();
        }



      /*  if (ImGui::BeginMenu("3D Objects")) {
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
        }*/

     /*   if (ImGui::BeginMenu("Color")) {
            if (ImGui::MenuItem("Show Color Picker")) {
                showColorPicker = !showColorPicker;
            }
            ImGui::EndMenu();
        }*/

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
