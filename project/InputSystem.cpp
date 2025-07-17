#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_system = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
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

	if (currentMousePos.x != old_mouse_pos.m_x || currentMousePos.y != old_mouse_pos.m_y)
	{
		//there is mouse move event
		std::map<InputListener*, InputListener*> currentListeners = mapListeners;
		std::map<InputListener*, InputListener*>::iterator it = currentListeners.begin();
		while (it != currentListeners.end())
		{
			if (it->second && !it->second->isDestroyed)
				it->second->onMouseMove(Point(currentMousePos.x, currentMousePos.y));
			++it;
		}

		old_mouse_pos = Point(currentMousePos.x, currentMousePos.y);
	}
	if (::GetKeyboardState(keys_state))
	{
		for (unsigned int i = 0; i < 256; i++) {

			// KEY IS DOWN - if value is 1 or 2, key is down
			if (keys_state[i] & 0x80)
			{
				//std::cout << "hi" << std::endl;
				std::map<InputListener*, InputListener*> currentListeners = mapListeners;
				std::map<InputListener*, InputListener*>::iterator it = currentListeners.begin();
				while (it != currentListeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (keys_state[i] != old_keys_state[i]) {
							if(it->first && !it->first->isDestroyed)	
								it->first->onLeftMouseDown(Point(currentMousePos.x, currentMousePos.y));
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (keys_state[i] != old_keys_state[i]) {
							if (it->first && !it->first->isDestroyed)
								it->first->onRightMouseDown(Point(currentMousePos.x, currentMousePos.y));
						}
					}
					else 
					{
						if (it->second && !it->second->isDestroyed)
							it->second->onKeyDown(i);

					}

					++it;
				}
				
			}
			else  //key is up
			{
				if (keys_state[i] != old_keys_state[i])
				{
					std::map<InputListener*, InputListener*> currentListeners = mapListeners;
					std::map<InputListener*, InputListener*>::iterator it = currentListeners.begin();
					while (it != currentListeners.end())
					{
						if (i == VK_LBUTTON)
						{
							if(it->first && !it->first->isDestroyed)
								it->first->onLeftMouseUp(Point(currentMousePos.x, currentMousePos.y));
						}

						if (i == VK_RBUTTON)
						{
							if (it->first && !it->first->isDestroyed)
								it->first->onRightMouseUp(Point(currentMousePos.x, currentMousePos.y));
						}
						else
						{
							if (it->second && !it->second->isDestroyed)
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

void InputSystem::create()
{
	if (InputSystem::m_system)
		throw std::exception("InputSystem is already created");

	InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_system)
		return;

	delete InputSystem::m_system;
}
