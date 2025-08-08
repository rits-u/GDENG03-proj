#pragma once
#define NOMINMAX
#include "Windows.h"
#include "EngineTime.h"


class Window
{
public:
	Window();
	~Window();
	bool isRun();

	RECT getClientWindowRect();

	//EVENTS
	virtual void onCreate();			//prev was 
	virtual void onUpdate() = 0;
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool isRunning;
	bool isInitialized = false;
};

