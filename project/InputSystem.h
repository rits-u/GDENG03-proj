#pragma once
#include "InputListener.h"
#include <map>
#include <iostream>

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

public:
	static InputSystem* get();

private:
	std::map<InputListener*, InputListener*> mapListeners;
	unsigned char keys_state[256] = {};
	unsigned char old_keys_state[256] = {};

};

