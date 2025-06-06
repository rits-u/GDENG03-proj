#include "Window.h"
#include "EngineTime.h"

//Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window* window = nullptr;

    switch (msg) 
    {
        case WM_CREATE:
        {
            //event fired when the window will be created
            Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
            window->setHWND(hwnd);
            window->onCreate();
            break;
        }

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

bool Window::init()
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
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if(!::RegisterClassEx(&wc))    //if the registration of class will fail, return false
        return false;

  //  if (!window)
    //    window = this;

    //creation of the window
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        NULL, NULL, NULL, this);

    //if the creation fails, return false 
    if (!m_hwnd)
        return false;

    //show up the window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    //set this flag to true to indicate that the window is initialized and running
    m_is_run = true;

    EngineTime::sharedInstance->initialize();
            
    return true;
}

bool Window::broadcast()
{
   
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

bool Window::release()
{
    //destroy the window
    if (!::DestroyWindow(m_hwnd))
        return false;

    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);

    return rc;
}

void Window::setHWND(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

void Window::onCreate()
{
   // m_is_run = false;
}


void Window::onDestroy()
{
    m_is_run = false;
}

Window::~Window()
{
}
