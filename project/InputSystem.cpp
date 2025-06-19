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
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	if (first_time)
	{
		old_mouse_pos = Point(currentMousePos.x, currentMousePos.y);
		first_time = false;
	}

	if(currentMousePos.x != old_mouse_pos.m_x || currentMousePos.y != old_mouse_pos.m_y)
	{
		//there is mouse move event
		std::map<InputListener*, InputListener*>::iterator it = mapListeners.begin();
		while (it != mapListeners.end())
		{
			it->second->onMouseMove(Point(currentMousePos.x, currentMousePos.y));
			++it;
		}
	}
	old_mouse_pos = Point(currentMousePos.x, currentMousePos.y);

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
					if (i == VK_LBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
							it->first->onLeftMouseDown(Point(currentMousePos.x, currentMousePos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keys_state[i] != old_keys_state[i])
							it->first->onRightMouseDown(Point(currentMousePos.x, currentMousePos.y));
					}
					else 
					{
						it->second->onKeyDown(i);

					}

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
						if (i == VK_LBUTTON)
						{
							it->first->onLeftMouseUp(Point(currentMousePos.x, currentMousePos.y));
						}

						if (i == VK_RBUTTON)
						{
							it->first->onRightMouseUp(Point(currentMousePos.x, currentMousePos.y));
						}
						else
						{
							it->second->onKeyUp(i);

						}

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

bool InputSystem::isKeyDown(int key)
{
	return (keys_state[key] & 0x80) != 0;
}

bool InputSystem::isKeyUp(int key)
{
	return (keys_state[key] & 0x80) == 0;
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}
