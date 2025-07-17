#include "UIManager.h"
#include <iostream>

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::get()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
;   sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
    if (!UIManager::sharedInstance)
        return;

    delete UIManager::sharedInstance;
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++) {
        this->uiList[i]->draw();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIScreen* UIManager::getUIScreenByName(String name)
{
    return this->uiMap[name];
    //return UIMap();
}

UIManager::UIManager(HWND windowHandle)
{
    //initialize IMGUI interface
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //enable keyboard controls
   // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    //setup dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    //setup platform/renderer bindings
    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(renderSystem->m_d3d_device, renderSystem->m_imm_context);

    //populate UI table;
    UINames uiNames;
    //UIScreen* creditsScreen = new
    MenuToolbar* menuToolbar = new MenuToolbar();
    this->uiMap[uiNames.MENU_TOOLBAR] = menuToolbar;
    this->uiList.push_back(menuToolbar);

    CreditsScreen* creditsScreen = new CreditsScreen();
    this->uiMap[uiNames.CREDITS_SCREEN] = creditsScreen;
    this->uiList.push_back(creditsScreen);

    InspectorScreen* inspectorScreen = new InspectorScreen();
    this->uiMap[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
    this->uiList.push_back(inspectorScreen);

    HierarchyScreen* hierarchyScreen = new HierarchyScreen();
    this->uiMap[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
    this->uiList.push_back(hierarchyScreen);

   // CreditsSreen* 
}

UIManager::~UIManager()
{
    UIManager::sharedInstance = nullptr;
}
