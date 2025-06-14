#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	if (::GetKeyboardState(keys_state))
	{
		for (unsigned int i = 0; i < 256; i++) {

			// KEY IS DOWN - if value is 1 or 2, key is down
			if (keys_state[i] & 0x80)
			{
				//std::cout << "hi" << std::endl;
				std::map<InputListener*, InputListener*>::iterator it = mapListeners.begin();
				while (it != mapListeners.end())
				{
					it->second->onKeyDown(i);
					++it;
				}
				
			}
			else  //key is up
			{
				if (keys_state[i] != old_keys_state[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = mapListeners.begin();
					while (it != mapListeners.end())
					{
						it->second->onKeyUp(i);
						++it;
					}
				}
			}

		}

		//store current keys state to old keys state buffer
		::memcpy(old_keys_state, keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	mapListeners.insert(std::make_pair<InputListener*, InputListener*>
		(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = mapListeners.find(listener);
	if (it != mapListeners.end())
	{
		mapListeners.erase(it);
	}
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}
