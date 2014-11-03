#pragma once

#include <SDL.h>

#include "Singleton.h"

enum InputType {
	IT_None,
	IT_Quit,
	IT_Left,
	IT_Right,
	IT_Jump,

	IT_COUNT // must be last
};

enum InputAxis {
	IA_None,
	IA_Horizontal,

	IA_COUNT // must be last
};

class InputManager : public Singleton<InputManager> {
private:
	enum InputState {
		IS_Up,
		IS_Held,
		IS_Down,
	};

	InputState _inputStates[IT_COUNT];
	float _inputAxes[IA_COUNT];
	SDL_Joystick *_joystick;
	
	void handleInput(InputType input, bool isDown);

public:
	void Init();
	void Deinit();
	void Update();

	bool IsHeld(InputType input);
	bool IsDown(InputType input);
	float GetAxis(InputAxis axis);
};
