#include "Window.h"
#include "EngineTime.h"
#include <exception>

//Window* window = nullptr;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
        return false;


    Window* window = nullptr;

    switch (msg)
    {
    case WM_CREATE:
    {
        //event fired when the window will be created
        /*  Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
            window->setHWND(hwnd);
            window->onCreate();*/
        break;
    }
    case WM_SETFOCUS:
    {
        //event fired when the window will get focus
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if(window) window->onFocus();
        break;
    }
    case WM_KILLFOCUS:
    {
        //event fired when the window will lost focus
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onKillFocus();
        break;
    }

    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE)
        {
            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            ::DestroyWindow(hwnd);
            ::PostQuitMessage(0);
            return 0; 
        }
        break;
    case WM_DESTROY:
    {
        //event fired when the window will be destroyed
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }

    default:
    {
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }
    }

    return NULL;
}

Window::Window()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = "MyWindowClass";
    wc.lpszMenuName = "";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;


    if (!::RegisterClassEx(&wc))    //if the registration of class will fail, return false
        throw std::exception("Registration of Class failed Window not created successfully");

    //  if (!window)
      //    window = this;

      //creation of the window
    RECT rc = { 0, 0, 1200, 800 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    int windowWidth = rc.right - rc.left;
    int windowHeight = rc.bottom - rc.top;


    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        NULL, NULL, NULL, NULL);

    //if the creation fails, return false 
    if (!m_hwnd)
        throw std::exception("HWND creation failed. Window not created successfully");

    //show up the window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    //set this flag to true to indicate that the window is initialized and running
    isRunning = true;

    EngineTime::sharedInstance->initialize();

}


Window::~Window()
{
}

bool Window::broadcast()
{
    if (!this->isInitialized)
    {
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
        this->onCreate();
        this->isInitialized = true;
    }


    EngineTime::LogFrameStart();

    this->onUpdate();
    MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    Sleep(1);
    EngineTime::LogFrameEnd();  

    return true;
}

bool Window::isRun()
{
    if (isRunning)
        broadcast();

    return isRunning;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);

    return rc;
}


void Window::onCreate()
{
   // m_is_run = false;
}


void Window::onDestroy()
{
    isRunning = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
