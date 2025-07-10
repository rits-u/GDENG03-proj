#pragma once
#include <string>

typedef std::string String;
class UIManager;

class UIScreen
{
	protected:
		typedef std::string String;

		UIScreen(String name);
		~UIScreen();

		String getName();
		virtual void draw() = 0;

		String name;

		friend class UIManager;

};

