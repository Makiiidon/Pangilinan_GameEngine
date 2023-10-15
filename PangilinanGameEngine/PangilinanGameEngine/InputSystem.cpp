#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	delete sharedInstance;
}

void InputSystem::addListener(InputListener* listener)
{
	this->inputListenerList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	int index = -1;
	for (int i = 0; i < inputListenerList.size(); i++) 
	{
		if (this->inputListenerList[i] == listener)
		{
			index = i;
			break;
		}
	}

	if (index > -1) 
	{
		this->inputListenerList.erase(this->inputListenerList.begin() + index);
	}

}

void InputSystem::update()
{
	POINT currentPosition = {};
	GetCursorPos(&currentPosition);

	if (this->firstTimeCall) 
	{
		this->firstTimeCall = false;
		this->oldMousePos = Point(currentPosition.x, currentPosition.y);
	}

	if (this->oldMousePos.getX() != currentPosition.x || 
		this->oldMousePos.getY() != currentPosition.y)
	{
		Point deltaPosition = Point(
			currentPosition.x - this->oldMousePos.getX(),
			currentPosition.y - this->oldMousePos.getY());

		this->callOnMouseMove(deltaPosition);
	}

	this->oldMousePos = Point(currentPosition.x, currentPosition.y);

	if (GetKeyboardState(keyStates)) //update keyStates
	{
		for (int i = 0; i < ARRAYSIZE(keyStates); i++)
		{
			// this->keyStates[i] & 0x80 checks whether a key has been pressed (regardless of whether it is toggled / untoggled)
			if (this->keyStates[i] & 0x80 && this->keyStates[i] != this->oldKeyStates[i])
			{
				if (VK_LBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPosition.x - this->oldMousePos.getX(), currentPosition.y - this->oldMousePos.getY());
					this->callOnLeftMouseDown(deltaPt);
				}
				else if (VK_RBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPosition.x - this->oldMousePos.getX(), currentPosition.y - this->oldMousePos.getY());
					this->callOnRightMouseDown(deltaPt);
				}
				else
					callOnKeyDown(i);
			}
			else if (this->keyStates[i] != this->oldKeyStates[i])
			{
				if (VK_LBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPosition.x - this->oldMousePos.getX(), currentPosition.y - this->oldMousePos.getY());
					this->callOnLeftMouseUp(deltaPt);
				}
				else if (VK_RBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPosition.x - this->oldMousePos.getX(), currentPosition.y - this->oldMousePos.getY());
					this->callOnRightMouseUp(deltaPt);
				}
				else
					callOnKeyUp(i);
			}
		}

		// store current keys to old states
		::memcpy(this->oldKeyStates, this->keyStates, sizeof(unsigned char) * 256);
	}
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
		if (!(this->keyStates[i] & 0x80) && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}

	return false;


	return false;
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) 
	{
		if (!(this->keyStates[i] & 0x80) && i == key) 
		{
			return true;
		}
		else if (i == key) 
		{
			return false;
		}
	}

	return false;
}

void InputSystem::callOnKeyDown(int key)
{
	for (int i = 0; i < inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onKeyUp(key);
	}
}

void InputSystem::callOnMouseMove(Point deltaPosition)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onMouseMove(deltaPosition);
	}
}

void InputSystem::callOnLeftMouseDown(Point deltaPosition)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseDown(deltaPosition);
	}
}

void InputSystem::callOnLeftMouseUp(Point deltaPosition)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseUp(deltaPosition);
	}
}

void InputSystem::callOnRightMouseDown(Point deltaPosition)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseDown(deltaPosition);
	}
}

void InputSystem::callOnRightMouseUp(Point deltaPosition)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseUp(deltaPosition);
	}
}

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}
