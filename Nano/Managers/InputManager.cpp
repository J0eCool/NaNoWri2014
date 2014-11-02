#include "InputManager.h"

#include <SDL.h>

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

void InputManager::Update() {
	for (int i = 0; i < IT_NumTypes; ++i) {
		if (_inputStates[i] == IS_Down) {
			_inputStates[i] = IS_Held;
		}
	}

	SDL_Event event;
	InputType type;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_inputStates[IT_Quit] = IS_Down;
			break;
		case SDL_KEYDOWN:
			type = getInputForKey(event.key.keysym.sym);
			if (_inputStates[type] == IS_Up) {
				_inputStates[type] = IS_Down;
			}
			break;
		case SDL_KEYUP:
			type = getInputForKey(event.key.keysym.sym);
			_inputStates[type] = IS_Up;
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
