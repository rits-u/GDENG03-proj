#pragma once
#include "Windows.h"
#include "EngineTime.h"


class Window
{
	public:
		Window();
		bool init();
		bool broadcast();
		bool release();
		bool isRun();

		RECT getClientWindowRect();
		void setHWND(HWND hwnd);

		//EVENTS
		virtual void onCreate();			//prev was 
		virtual void onUpdate() = 0;
		virtual void onDestroy();
		virtual void onFocus();
		virtual void onKillFocus();

		~Window();

	protected:
		HWND m_hwnd;
		bool m_is_run;
};

