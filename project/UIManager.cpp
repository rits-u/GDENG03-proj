#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::get()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
    if (!UIManager::sharedInstance)
        return;

    delete UIManager::sharedInstance;
}

void UIManager::drawAllUI()
{
}

UIManager::UIManager(HWND windowHandle)
{
   // IMGUI_ch    
}

UIManager::~UIManager()
{
    UIManager::sharedInstance = nullptr;
}
