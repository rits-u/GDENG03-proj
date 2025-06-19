#pragma once
#include "InputListener.h"
#include "Point.h"

#include <map>
#include <iostream>
#include <vector>



class InputSystem
{
private:
	InputSystem();
	~InputSystem();

public:
	typedef std::vector<InputListener*> List;

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

public:
	static InputSystem* get();
	static void create();
	static void release();

private:
	static InputSystem* m_system;
	std::map<InputListener*, InputListener*> mapListeners;
	unsigned char keys_state[256] = {};
	unsigned char old_keys_state[256] = {};
	Point old_mouse_pos;
	bool first_time = true;

};

