#include "InputManager.h"

#include <SDL.h>
#include "../Util/Math.h"

struct InputAxisInfo {
	InputAxis axis;
	float value;
};

InputType getInputForKey(SDL_Keycode key) {
	InputType input = IT_None;

	switch (key) {
	case SDLK_ESCAPE:
		input = IT_Quit;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		input = IT_Left;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		input = IT_Right;
		break;
	case SDLK_SPACE:
		input = IT_Jump;
		break;
	}

	return input;
}

InputType getInputForButton(Uint8 buttonCode) {
	InputType input = IT_None;

	/*
	Xbox Controller cheatsheet:
		0 - Up
		1 - Down
		2 - Left
		3 - Right
		4 - Start
		5 - Back
		6 - L3
		7 - R3
		8 - LB
		9 - RB
		10- A
		11- B
		12- X
		13- Y
		14- Home
	*/

	switch (buttonCode) {
	case 2:
		input = IT_Left;
		break;
	case 3:
		input = IT_Right;
		break;
	case 10:
		input = IT_Jump;
		break;
	}

	return input;
}

InputAxisInfo getAxisForInput(InputType type) {
	InputAxisInfo info;
	info.axis = IA_None;

	switch (type) {
	case IT_Left:
		info.axis = IA_Horizontal;
		info.value = -1.0f;
		break;
	case IT_Right:
		info.axis = IA_Horizontal;
		info.value = 1.0f;
		break;
	}

	return info;
}

void InputManager::Init() {
	if (SDL_NumJoysticks() > 0) {
		_joystick = SDL_JoystickOpen(0);
	}
}

void InputManager::Deinit() {
	SDL_JoystickClose(_joystick);
}

void InputManager::handleInput(InputType input, bool isDown) {
	InputAxisInfo axis = getAxisForInput(input);
	if (isDown && _inputStates[input] == IS_Up) {
		_inputStates[input] = IS_Down;
		_inputAxes[axis.axis] += axis.value;
	}
	else if (!isDown) {
		if (_inputStates[input] != IS_Up) {
			_inputAxes[axis.axis] -= axis.value;
		}
		_inputStates[input] = IS_Up;
	}
}

void InputManager::Update() {
	for (int i = 0; i < IT_COUNT; ++i) {
		if (_inputStates[i] == IS_Down) {
			_inputStates[i] = IS_Held;
		}
	}

	SDL_Event event;
	InputType type;
	InputAxisInfo axis;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_inputStates[IT_Quit] = IS_Down;
			break;
		case SDL_KEYDOWN:
			type = getInputForKey(event.key.keysym.sym);
			handleInput(type, true);
			break;
		case SDL_KEYUP:
			type = getInputForKey(event.key.keysym.sym);
			handleInput(type, false);
			break;
		case SDL_JOYAXISMOTION:
			if (_joystick && event.jaxis.which == 0) {
				axis.value = event.jaxis.value / 32767.0f;
				if (axis.value * axis.value < 0.1f) {
					axis.value = 0.0f;
				}
				if (event.jaxis.axis == 0) {
					axis.axis = IA_Horizontal;
					_inputAxes[axis.axis] = axis.value;
				}
			}
			break;
		case SDL_JOYBUTTONDOWN:
			if (_joystick && event.jbutton.which == 0) {
				type = getInputForButton(event.jbutton.button);
				handleInput(type, true);
			}
			break;
		case SDL_JOYBUTTONUP:
			if (_joystick && event.jbutton.which == 0) {
				type = getInputForButton(event.jbutton.button);
				handleInput(type, false);
			}
			break;
		}
	}
}

bool InputManager::IsDown(InputType type) {
	return _inputStates[type] == IS_Down;
}

bool InputManager::IsHeld(InputType type) {
	return _inputStates[type] == IS_Down
		|| _inputStates[type] == IS_Held;
}

float InputManager::GetAxis(InputAxis axis) {
	return clamp(_inputAxes[axis], -1.0f, 1.0f);
}
