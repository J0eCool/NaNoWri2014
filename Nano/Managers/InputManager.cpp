#include "InputManager.h"

#include <SDL.h>

void InputManager::Update() {
	// Reset last frame's flags
	for (int i = 0; i < IN_NumTypes; ++i) {
		_downInputs[i] = false;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_downInputs[IN_Quit] = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				_downInputs[IN_Quit] = true;
			}
			break;
		}
	}
}

bool InputManager::IsDown(InputType type) {
	return _downInputs[type];
}
