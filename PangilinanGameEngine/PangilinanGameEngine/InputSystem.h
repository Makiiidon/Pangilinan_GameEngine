#pragma once

#include "InputListener.h"

#include <iostream>
#include <vector>

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();

	bool isKeyUp(int key);
	bool isKeyDown(int key);

private:
	static InputSystem* sharedInstance;

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void callOnMouseMove(Point deltaPosition);
	void callOnLeftMouseDown(Point deltaPosition);
	void callOnLeftMouseUp(Point deltaPosition);
	void callOnRightMouseDown(Point deltaPosition);
	void callOnRightMouseUp(Point deltaPosition);

	std::vector<InputListener*> inputListenerList;

	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};

	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};

	Point oldMousePos;

	bool firstTimeCall = true;
};

